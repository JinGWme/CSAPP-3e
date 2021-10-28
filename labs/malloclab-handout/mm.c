/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"
#include "csapp.h"
#include "config.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "team A",
    /* First member's full name */
    "Jing W",
    /* First member's email address */
    "jingw@gmail.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE   4   // Word and header/footer size (bytes)
#define DSIZE   8   // Double word size (bytes)
#define CHUNKSIZE   (2<<12) // Extend heap by this amount

#define MAX(x, y) ((x) > (y)? (x):(y))

// Pack a size a anllocated bit into a word
#define PACK(size, alloc)   ((size)|(alloc))

//Read and write a word at address p
#define GET(p)      (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

// Read the size and allocated fields from address p
#define GET_SIZE(p)     (GET(p) & ~0x7)
#define GET_ALLOC(p)    (GET(p) & 0x1)

// Given block ptr bp, compute address of its header and footer
#define HDRP(bp)    ((char *)(bp) - WSIZE)
#define FTRP(bp)    ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

// Given block ptr bp, compute address of next and previous blocks
#define NEXT_BLKP(bp)   ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp)   ((char *)(bp) - GET_SIZE(HDRP(bp)-WSIZE))

#define VERBOSE 0

static void *heap_listp;
static void *heap_lastp;
static int nblocks = 0;
// Merge free blocks
static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    // 前后都分配了
    if (prev_alloc && next_alloc)
    {
        return bp;
    }

    else if ( prev_alloc && !next_alloc)
    {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }

    else if (!prev_alloc && next_alloc)
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    
    else
    {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp))) + GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    return bp;
    
}
// Size is aligned to DSIZE (8 bytes)
static void *find_first_fit(size_t asize)
{
    void *sp = heap_listp;
    void *bp = NULL;
    while (GET_SIZE(HDRP(sp)) != 0)
    {
        if (GET_ALLOC(HDRP(sp)))
        {
            sp = NEXT_BLKP(sp);
            continue;
        }
        if (GET_SIZE(HDRP(sp)) < asize)
        {
            sp = NEXT_BLKP(sp);
            continue;
        }
        bp = sp;
        break;        
    }
    return bp;
}
// Size is aligned to DSIZE (8 bytes)
static void *find_next_fit(size_t asize)
{
    // find from last alloc block to epilogure
    void *sp = heap_lastp;
    void *bp = NULL;
    while (GET_SIZE(HDRP(sp)) != 0)
    {

        if (GET_ALLOC(HDRP(sp)))
        {
            sp = NEXT_BLKP(sp);
            continue;
        }
        if (GET_SIZE(HDRP(sp)) < asize)
        {
            sp = NEXT_BLKP(sp);
            continue;
        }
        bp = sp;
        heap_lastp = sp;        
        if (VERBOSE)
        {
            printf("Last alloc pointer %p\n", HDRP(heap_lastp));
        }
        
        return bp;
    }

    sp = heap_listp;
    // find from progoure to last alloc
    while ( sp != heap_lastp )
    {
        if (GET_ALLOC(HDRP(sp)))
        {
            sp = NEXT_BLKP(sp);
            continue;
        }
        if (GET_SIZE(HDRP(sp)) < asize)
        {
            sp = NEXT_BLKP(sp);
            continue;
        }
        bp = sp;
        heap_lastp = sp;
        if (VERBOSE)
        {
            printf("Last alloc pointer %p\n", HDRP(heap_lastp));
        }
        break;
    }
    return bp;
    
}

static void place(void *bp, size_t asize)
{
    size_t oldsize = GET_SIZE(HDRP(bp));
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    // Mark remaining space as free block
    if (oldsize > asize)
    {
        PUT(HDRP(NEXT_BLKP(bp)), PACK((oldsize - asize), 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK((oldsize - asize), 0));
    }
}
static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;    // in bytes

    // Allocate an even number of words to maintain aglignment
    size = (words%2) ? (words+1)*WSIZE : words*WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;
    
    // Initialize free block header/footer and the epilogure header
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    nblocks += 1;
    return coalesce(bp);
}

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    // Create the initial empty heap
    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp, 0);
    PUT(heap_listp+(1*WSIZE), PACK(DSIZE, 1));  //prologue header
    PUT(heap_listp+(2*WSIZE), PACK(DSIZE, 1));  //prologue footer
    PUT(heap_listp+(3*WSIZE), PACK(0, 1));      //epilogue header, 
                                                //the only bock with size 0
    heap_listp += (2*WSIZE);
    heap_lastp = heap_listp;

    // Extend the empty heap with free block of CHUNKSIZE bytes
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
        return -1;
    nblocks += 2;
    heap_walker();
    return 0;
}

void heap_walker(void)
{
    if(!VERBOSE)
        return;
    int block_cnt = 0;
    char *bp = heap_listp;
    while (1)
    {
        size_t size = GET_SIZE(HDRP(bp));
        if (size == 0)
        {
            printf("Epilogure block encoutered @ %p\n", HDRP(bp));
            block_cnt++;
            break;
        }
        
        if (GET_ALLOC(HDRP(bp)) && 0x1)
        {
            printf("BUSY BLOCK %d START %p, END %p, SIZE %d\n", block_cnt, HDRP(bp), FTRP(bp), GET_SIZE(HDRP(bp)));
        }
        else
        {
            printf("free block %d start %p, end %p, size %d\n", block_cnt, HDRP(bp), FTRP(bp), GET_SIZE(HDRP(bp)));
        }
        bp = NEXT_BLKP(bp);
        block_cnt++;
    }
    printf("Totally %d blocks allocated.  Press [Enter] to continue . . .\n", block_cnt);
    fflush(stdout);
    getchar();
}


/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 * size: user data size without mm header/footer
 */
void *mm_malloc(size_t size)
{
    size_t asize;
    
    if (VERBOSE)
    {
        printf("Request raw size %d \n", size);
    }

    char *bp;

    if (size == 0)
    {
        return NULL;
    }

    // Adjust block size to include overhead and alignment reqs
    if (size <= DSIZE)
        asize = 2*DSIZE;
    else
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
    
    // Search free list for a fit
    if ((bp = find_first_fit(asize)) != NULL)
    {
        place(bp, asize);
        if (VERBOSE)
        {
            printf("Alloc at %p raw size %d \n", HDRP(bp), size);
        }
        heap_walker();
        return bp;
    }

    // No fit found, Get more memory and place the block
    size_t extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    if (VERBOSE)
    {
        printf("Alloc at %p raw size %d after extending heap.\n", HDRP(bp), size);
    }
    heap_walker();
    return bp;
}


/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    if (VERBOSE)
    {
        printf("Free memory %p\n", HDRP(ptr));
    }
    size_t size = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr);
    heap_walker();
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 * JingW - Update to firstly check if current allocation can be extended
 * size : user data size (not DSIZE aligned) without mm header/footer
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    int next_alloced = GET_ALLOC(HDRP(NEXT_BLKP(ptr)));
    if (!next_alloced)
    {
        size_t this_size = GET_SIZE(HDRP(ptr));            // DSIZE aligned
        size_t next_size = GET_SIZE(HDRP(NEXT_BLKP(ptr))); // DSIZE aligned
        size_t merge_size = this_size + next_size;
        if(merge_size - DSIZE >= size) // enough space, merge
        {
            PUT(HDRP(ptr), PACK(merge_size, 1));
            PUT(FTRP(ptr), PACK(merge_size, 1));
            return ptr;
        }
    }    
    
    // can't merge in place, we malloc and copy
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}














