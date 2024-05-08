
procedure main (void)
{
	int n;
	int sum;

	n = 2;
	sum = 0;
	if (n >= 1)
	{
		sum = n * (n + 1) * (2 * n + 1) / 6;
	}
	printf("Sum is: %d", sum);
	return sum;
}
