#include<iostream>
using namespace std;

int count = 0;
//memoµÝ¹é°æ
int fast_fib(int n, int* memo)
{
	count++;
	if(memo[n] == -1)
		memo[n] = fast_fib(n-1, memo) + fast_fib(n-2, memo);
	return memo[n];
}

int fib(int n)
{
	int *memo = new int[n+1];
	memo[0] = memo[1] = 1;
	for(int i=2; i<n+1; i++)
		memo[i] = -1;
	int result = fast_fib(n, memo);
	delete memo;
	return result;
}




/*ÆÕÍ¨°æ
fib(int n)
{
	count++;
	if(n<=1)
		return 1;
	return fib(n-1)+fib(n-2);
}
*/

//µü´ú°æ
/*int fib(int n)
{
	int *memo = new int[n+1];
	memo[0] = memo[1] = 1;
	for(int i=2;  i<=n; i++)
	{
		memo[i] = memo[i-1] + memo[i-2];
	}

	int result = memo[n];
	delete memo;
	return result;
}
*/
int main()
{
	cout<<"fib(30) = "<<fib(30)<<endl;
	cout<<"count = "<<count<<endl;
	return 0;
}
