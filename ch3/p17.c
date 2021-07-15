long lt_cnt = 0;
long gt_cnt = 0;

long absdiff_se (long x, long y)
{
	long result;
	if (x < y) 
		goto then;
	gt_cnt++;
	return y - x;
then:
  lt_cnt++;
	return x - y;
}