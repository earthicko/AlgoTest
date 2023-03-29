#include <cstdio>

#define MAX_N 1000000

int n;
int a[MAX_N];
int b, c;

int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	scanf("%d%d", &b, &c);

	unsigned long long counter = 0;
	for (int i = 0; i < n; i++)
	{
		counter++;
		a[i] -= b;
		if (a[i] <= 0)
			continue;
		counter += a[i] / c;
		if (a[i] % c)
			counter++;
	}

	printf("%lld\n", counter);

	return (0);
}
