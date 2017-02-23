/*
    DJ.W 2012.7.25
	代码功能:
	  给定两个字符串str1, str2 找出它们的最大公共子串
	备注:
	     在制作程序的memo和路径跟踪时,需要弄清二维数组需要分配的维数
		 在本程序中memo和lcs均分配了比字符串长度多一的维数 这是因为memo和lcs记录的是当前子问题情形
		 此处即为由后至前遍历两个字符串时 两个字符串的长度 而字符串长度和字符串下标是有区别的
		 因此在之后的输出字符中需要减一

         还有就是如何通过lcs记录并输出公共字符串 由于对于每个子问题区别于i和j的大小 因此分配一个二维数组lcs[N1+1][N2+1]
		 是无可厚非的 有些不同于背包问题的是 这里的每个子问题可能有三种情形 背包问题对于每个物品只有装和不装两种情况
		 因此很容易找到跟踪路线 针对于这里的三种情况 我们可以知道 只有在str1[i]==str2[j]时 才有一个输出
		 对于其他两种情况的路线跟踪可用标记实现 因此有了'-' '\\' '|' 三个方向 对应于最终选择的遍历路径 最后通过Display输出

         其实也可以不通过lcs来输出最长子串 直接由尾到头比较str1, str2 如果相等 输出 如果不等 去memo[i-1][j] memo[i][j-1]
		 中长的一边来继续跟踪  需要O(N1+N2)时间
*/
#include<iostream>
using namespace std;

#define N1 7
#define N2 6

#define max(a, b) (a>b?a:b)


int count;
/*int Find(char* str1, int n1, char* str2, int n2)
{
    count++;

	int res1, res2;
	if(n1==0 || n2 ==0)
		return 0;

	if(str1[n1-1] == str2[n2-1])
	{
		return 1 + Find(str1, n1-1, str2, n2-1);
	}
	else
	{
		res1 = Find(str1, n1, str2, n2-1);
		res2 = Find(str1, n1-1, str2, n2);
		if(res1>res2)
			return res1;
		else
			return res2;
	}
}
*/
//===============================================递归版=============================================================================//
/*
int find_fast(char* str1, int i, char* str2, int j, int memo[N1+1][N2+1], char lcs[N1+1][N2+1])
{
    count++;

	if(memo[i][j] != -1)
		return memo[i][j];

	int res1, res2;
	if(i==0 || j ==0)
	{
		memo[i][j] = 0;
		return 0;
	}

	if(str1[i-1] == str2[j-1])
	{
		memo[i][j]  = 1 + find_fast(str1, i-1, str2, j-1, memo, lcs);
        lcs[i][j]   = '\\';
		return memo[i][j];
	}
	else
	{
		res1 = find_fast(str1, i, str2, j-1, memo, lcs);
		res2 = find_fast(str1, i-1, str2, j, memo, lcs);
		if(res1>res2)
		{
			memo[i][j] = res1;
			lcs[i][j] = '|';
			return res1;
		}
		else
		{
			memo[i][j] = res2;
			lcs[i][j] = '-';
			return res2;
		}
	}
}

void Display(char lcs[N1+1][N2+1], int i, int j, char* str1)
{
	if(i == 0 || j == 0)
		return;
	if(lcs[i][j] == '-')
		Display(lcs, i-1, j, str1);
	else if(lcs[i][j] == '|')
		Display(lcs, i, j-1, str1);
	else
	{
		Display(lcs, i-1, j-1, str1);
		cout<<str1[i-1];
    }
}

int Find(char* str1, int n1, char* str2, int n2)
{
	char lcs[N1+1][N2+1];
	int memo[N1+1][N2+1];
	for(int i=0; i<N1+1; i++)
		for(int j=0; j<N2+1; j++)
		{
			memo[i][j] = -1;
			lcs[i][j] = ' ';
		}
	for(i=1; i<N1+1; i++)
		lcs[i][0] = str1[i-1];
	for(int j=1; j<N2+1; j++)
		lcs[0][j] = str2[j-1];

	int len = find_fast(str1, n1, str2, n2, memo, lcs);

	for(i=0; i<N1+1; i++)
	{
		for(j=0; j<N2+1; j++)
		{
			cout<<lcs[i][j]<<" ";
		}
		cout<<endl;
	}

    
	Display(lcs, N1, N2, str1);
	cout<<endl;
    return len;
}
*/
//============================================================迭代版================================================================//

void Display(char lcs[N1+1][N2+1], int i, int j, char* str1)
{
	if(i == 0 || j == 0)
		return;
	if(lcs[i][j] == '-')
		Display(lcs, i-1, j, str1);
	else if(lcs[i][j] == '|')
		Display(lcs, i, j-1, str1);
	else
	{
		Display(lcs, i-1, j-1, str1);
		cout<<str1[i-1];
    }
}

int Find(char* str1, int n1, char* str2, int n2)
{
	//为了较好的处理边界条件 这里将str在memo中从1开始
    int memo[N1+1][N2+1];
	char lcs[N1+1][N2+1];
	for(int i=0; i<N1+1; i++)
		memo[i][0] = 0;
	for(int j=0; j<N2+1; j++)
		memo[0][j] = 0;

	for(i=1; i<N1+1; i++)
		for(int j=1; j<N2+1; j++)
		{
			if(str1[i-1] == str2[j-1])
			{
				memo[i][j] = 1 + memo[i-1][j-1];
				lcs[i][j] = '\\';
			}
			else if(memo[i-1][j]>memo[i][j-1])
			{
				memo[i][j] = memo[i-1][j];
				lcs[i][j] = '-';
			}
			else
			{
				memo[i][j] = memo[i][j-1];
				lcs[i][j] = '|';
			}
		}
		Display(lcs, N1, N2, str1);
		cout<<endl;
	return memo[N1][N2];
}
int main()
{
	char* str1 = "ABCBDAB";
	char* str2 = "BDCABA";
	cout<<"最长公共子串数: "<<Find(str1, N1, str2, N2)<<endl;
	cout<<"调用次数: "<<count<<endl;
	return 0;
}