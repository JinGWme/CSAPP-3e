

int funcA(int x) {
	return x << 4 + x;
}

int funcB(int x)
{
	return (-x) << 3 + x;
}

int funcC(int x)
{
	return x << 6 - x << 2;
}

int funcD(int x)
{
	return (-x) << 7 + x << 4;
}