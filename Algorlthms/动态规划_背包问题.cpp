/*
    DJ.W 2012.7.23
*/

/*制作memo的注意事项:
  一次函数调用只能得到一个memo 因为对于当前函数参数对应的情况只能有一个最优化选择
  唯一的memo产生于该函数的各个返回处

  此次犯错: 对于一次maxval函数的情形 产生了maxmemo[i-1][remain]和maxmemo[i-1][remain-weight[i]]
  为什么应该是i而不是i-1 i才是此次函数对应的最优解 i取决于此次函数参数 而不是得到memo调用的下级函数
  同样remain-weight[i] 是下级子问题对应的最优解 应该有下级子问题来求对应问题的开始就对memo进行了检测

  之所以不在函数中的每一处调用子问题时对子问题memo进行检测 是因为一个子问题产生一个最优解 在每个子问题中判断
  该问题是否已经被解决是一种最清晰的递归模式 如果在调用下级子问题每一处都进行检测 会使代码显得臃肿难懂

*/
#include<iostream>
using namespace std;

#define N 20
#define M 100
#define max(a, b) (a>b?a:b)

//============================================递归版==============================================================================//
/*
int count = 0;
int fast_maxval(int weight[], int value[], int i, int remain, int maxmemo[N][M+1], int result[N][M+1])
{

	
    count++;

	if(maxmemo[i][remain] != -1)
		return maxmemo[i][remain];
    
	if(i==0)
	{
		if(weight[i] <= remain)
		{
			maxmemo[i][remain] = value[i];
			result[i][remain] = 1;
			return maxmemo[i][remain];
		}
		else
		{
			maxmemo[i][remain] = 0;
			result[i][remain] = 0;
			return 0;
		}
	}
	int with_i;

	int without_i = fast_maxval(weight, value, i-1, remain, maxmemo, result);
	if(weight[i] > remain)
	{
		maxmemo[i][remain] = without_i;
		result[i][remain] = 0;
		return without_i;
	}
	else
			with_i = value[i] + fast_maxval(weight, value, i-1, remain-weight[i], maxmemo, result);

	if(with_i > without_i)
	{
		maxmemo[i][remain] =  with_i;
		result[i][remain] = 1;
	}
	else
	{
		maxmemo[i][remain] =  without_i;
		result[i][remain] = 0;
	}
	return maxmemo[i][remain];
}

void Display(int result[N][M+1], int i, int remain, int weight[N])
{

	if(i>0)
	{
		Display(result, i-1, remain-result[i][remain]*weight[i], weight);
	}
	cout<<result[i][remain];
}


int maxval(int weight[], int value[], int i, int remain)
{
	//为什么是M+1：物品的最初剩余容量即为背包容量 为了便于理解 不宜将背包容量定为从0开始
	int maxmemo[N][M+1];
    int result[N][M+1];
	for(int a=0; a<N; a++)
		for(int b=0; b<M+1; b++)
			maxmemo[a][b] = -1;
	int maxvalue = fast_maxval(weight, value, i, remain, maxmemo, result);
	cout<<"选取方案:";
	Display(result, N-1, M, weight);
	cout<<endl;
	return maxvalue;
}
*/

//============================================普通版===============================================================================//
/*int count;

int maxval(int weight[], int value[], int i, int remain)
{
    count++;
	if(i==0)
	{
		if(weight[i] <= remain)
			return value[i];
		else
			return 0;
	}

	int without_i = maxval(weight, value, i-1, remain);
	
	int with_i;
	if(weight[i] > remain)
		return without_i;
	else
		with_i = value[i] + maxval(weight, value, i-1, remain-weight[i]);
	return with_i > without_i ? with_i:without_i;
}
*/

//==================================================迭代版=========================================================================//
/*
	迭代版需要解决的最大的问题就是 如何保证一个物品只被装入一次 根据这个特殊性 我们将对物品的迭代放在对容量的迭代的外层
	这样还不够 还需要将容量自大到小迭代 这样可以避免一个物品在子问题的最优解中被装入以后 又在上级问题的最优解中被装入
	这样就形成了迭代版1

    迭代版2和迭代版1主要有两点不同: 
	1.在迭代版2中 j并没有倒序迭代背包容量 这是因为迭代版2中memo是一个二维数组 它同时记录了当前遍历到的物品数 每装下一个物品时
		当前价值量均由memo[i-1][j-wei[i]]+value[i]产生 即物品i不可能在memo[i-1][]中出现 从而保证了物品i只被装入一次 这种特性使得
		迭代版2 可以将对物品的迭代放到里层 但这样使得该代码的局部性变得很差 效率变低

	2.迭代版2中 物品i没有装下时 当前价值量memo[i][j] = memo[i-1][j] 而在迭代版1中 没有memo[j] = memo[j-1] 这是因为在迭代版1中
	    没有记录物品标号 那么memo[j]来自于各个i 不能因为某一个i没装 而否认前面的i找到最优解 也可以这么看 物品i装不下时 memo[j]
		没有变化 是默认使用了前面i所产生的最优解 因为i按从小到大遍历
		对于迭代版2 它记录了i 描述当前子问题的更具体形式 如果物品i没装 memo[i][j]默认自动等于memo[i-1][j]的 所以要显示赋值

 
   
*/

void Display(int scheme[N][M+1], int i, int remain, int weight[N])
{

	if(i>0)
	{
		Display(scheme, i-1, remain-scheme[i][remain]*weight[i], weight);
	}
	cout<<scheme[i][remain];
}


int maxval(int wei[N], int val[N])
{
 //==========迭代版1
 /*
	int memo[M+1];
	int scheme[N][M+1];

	for(int i=0; i<M+1; i++)
		memo[i] = 0;

	for(i=0; i<N; i++)
	{
		//由于要处理是否装得下的问题 因此将循环隔为两段
		//能装下
		for(int j=M; j>=wei[i]; j--)
		{
			if(memo[j-wei[i]]+val[i] > memo[j])
			{
				memo[j] = memo[j-wei[i]]+val[i];
				scheme[i][j] = 1;
			}
			else
				scheme[i][j] = 0;
		}
		//不能装下
		for(; j>0; j--)
			scheme[i][j] = 0;
	}
	int result = memo[M];

	Display(scheme, N-1, M, wei);
	cout<<endl;
	return result;

*/

//==========迭代版2	

	int memo[N][M+1];
	int scheme[N][M+1];

    for(int i=0; i<N; i++)
		for(int j=0; j<M+1; j++)
			memo[i][j] = 0;
	
	//优先处理边界 以用于memo[i-1]的调用 避免在i=0时调用到memo[-1][]
	for(int j=0; j<=M; j++)
	{
		if(j<wei[0])
			scheme[0][j] = 0;
		else
		{
			memo[0][j] = val[0];
			scheme[0][j] = 1;
		}
	}

	for(i=1; i<N; i++)
		for(int j=1; j<=M; j++)
		{
			if(j<wei[i])
			{
				memo[i][j] = memo[i-1][j];
				scheme[i][j] = 0;
				continue;
			}
			if(memo[i-1][j] >= memo[i-1][j-wei[i]]+val[i])
			{
				memo[i][j] = memo[i-1][j];
				scheme[i][j] = 0;
			}
			else
			{
				memo[i][j] = memo[i-1][j-wei[i]] + val[i];
				scheme[i][j] = 1;
			}
			
		}
	Display(scheme, N-1, M, wei);
	cout<<endl;
    return memo[N-1][M];

}


int main()
{
	int value[N] = {3, 15, 26, 14, 19, 44, 122, 60, 77, 21, 30, 11, 41, 32, 9, 12, 14, 54, 43, 22};
	int weight[N] = {1, 6, 13, 5, 9, 22, 50, 18, 33, 10, 12, 4, 19, 15, 3, 5, 5, 25, 20, 9};
	cout<<"背包最多能装价值量: "<<maxval(weight, value)<<endl;
	cout<<"调用次数: "<<count<<endl;
	return 0;//267 211012 2223
	         //458
}