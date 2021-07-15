long fun_b(unsigned long x)
{
	long val = 0;
	long i;
	for ( i = 64; i != 0; i--)
	{
		val <<= 1;
		val |= (x&0x1);
		x>>1;
	}
	return val;
}