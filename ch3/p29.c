long sum()
{
	long sum = 0;
	long i;
	for ( i = 0; i < 10; i++)
	{
		sum += i;
	}
	return sum;
}

long sum_c()
{
	long sum = 0;
	long i;
	for ( i = 0; i < 10; i++)
	{
		if (i & 1)
		{
			continue; //跳过奇数
		}
		
		sum += i;
	}
	return sum;
}