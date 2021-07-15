
void cond(long a, long *p)
{
	if (p && a > *p)
	{
		*p = a;
	}
}

void condalt(long a, long *p)
{
	if (p == 0)
		goto end;
	if (a <= *p)
		goto end;
	*p = a;
end:
	return;
}