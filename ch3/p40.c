
#define N 16
typedef int fix_matrix[N][N];


void fix_set_diag(fix_matrix A, int val)
{
	long i;
	for (i = 0; i < N; i++)
	{
		A[i][i] = val;
	}
}

void fix_set_diag_opt(fix_matrix A, int val)
{
	int *begin = &A[0][0];
	int *end = begin + N*(N+1);

	do{
		*begin = val;
		begin += N+1;
	}while(begin != end);
}