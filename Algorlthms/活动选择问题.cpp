/*
    DJ.W 2012.8.3
	问题描述: 《算法导论》P223
*/
#include<iostream>
using namespace std;

#define N 14
#define M 11

typedef struct tagActiv
{
	int start;
	int end;
} Activ, *PActiv;

//=====================================动态规划—递归版============================================================================//
/*
   注意如何通过参数描述子问题情形  在这里由于活动终止时间有序 因此用参数i j来减小递归查找范围 提高效率 对于乱序活动 则不应有此参数
   如何跟踪子问题路径 由于动态规划子问题具有重叠性 因此最优解跟踪必须能够充分描述子问题情形 这里按照k探索的顺序来跟踪活动序号
*/
/*
int count;
int Dynamic_Select(int start, int end, PActiv pActiv, int i, int j, int memo[N+1][N+1], int res[N+1][N+1])
{
	count++;
	if(memo[start][end] != -1)
		return memo[start][end];

	int temp, temp_k=-1;
	int numAct = 0;
	//注意临时值的初始化 因为有可能在i!=j的情况下没有活动满足条件而让循环内部并不执行 而这些临时值在循环外部用到了
    while(pActiv[j].end>end)
		j--;
	//去掉不必要的探索(因为活动终止时间有序)
	for(int k=i; k<=j; k++)
	{
		if(pActiv[k].start>=start)
		//不同于矩阵相乘的探索 这里的i!=j也可以使递归终止
		{
			temp = 1 + Dynamic_Select(start, pActiv[k].start, pActiv, i, k-1, memo, res)
				+ Dynamic_Select(pActiv[k].end, end, pActiv, k+1, j, memo, res);

			if(temp > numAct)
			{
				numAct = temp;
				temp_k = k;
			}
		}
	}
	memo[start][end] = numAct;
	res[start][end] = temp_k;
	return numAct;
}

void Display(int res[N+1][N+1], int i, int j, PActiv pAc)
{
	int k = res[i][j];
	if(k == -1)
		return;
	Display(res, i, pAc[k].start, pAc);
	cout<<"A"<<k<<" ";
	Display(res, pAc[k].end, j, pAc);
}
void Dynamic_Select_memo(int start, int end, PActiv pActiv, int first_activ, int last_activ)
{
	int memo[N+1][N+1];
	int res[N+1][N+1];
	//初始化res是为了方便Display中的递归终止 因为在该问题中 i!=j也可以使递归终止 因此可用特殊值来检测

	for(int i=0; i<N+1; i++)
		for(int j=0; j<N+1; j++)
		{
			memo[i][j] = -1;
			res[i][j] = -1;
		}
	

	cout<<"最大兼容活动数目为:"<<Dynamic_Select(start, end, pActiv, first_activ, last_activ, memo, res)<<endl;
	cout<<"选中的活动序号有:"<<endl;
	Display(res, 0, N, pActiv);
}
*/

//======================================动态规划—迭代版============================================================================//
//该算法对无序活动序列有效
/*
    如何通过子问题逐步扩展 根据最优子结构 在逐步划分为两个子问题的过程中 和矩阵相乘类似 结合memo的记录形式 
	    采用长度逐步扩展的方式来扩展子问题
	在对memo进行记忆时 要保证对每一个子问题memo都有一个确定的值 
	    在这里 如果对于i j没有适合的活动 那么memo不会通过temp赋值 而是利用默认值 如果memo默认值为-1等其他值 这需要对temp判断并重新赋值
	在递归转为迭代时 最好根据递归的memo形式和子问题的分解形式来设定嵌套循环
*/
/*
void Display(int res[N+1][N+1], int i, int j, PActiv pAc)
{
	int k = res[i][j];
	if(k == -1)
		return;
	Display(res, i, pAc[k].start, pAc);
	cout<<"A"<<k<<" ";
	Display(res, pAc[k].end, j, pAc);
}

void Dynamic_Select_memo(int start, int end, PActiv pActiv, int first_activ, int last_activ)
{
	int memo[N+1][N+1];
	int res[N+1][N+1];
	for(int i=0; i<N+1; i++)
		for(int j=0; j<N+1; j++)
		{
				memo[i][j] = 0;
			    res[i][j] = -1;
		}
	int j, temp = 0;
	for(int len=1; len<=end-start; len++)
		for(int i=start; i<end-len+1; i++)
		{
			j = i+len;
			for(int k=first_activ; k<=last_activ; k++)
			//由于处于两层循环之内 不方便根据结束时间有序的活动序列进行逐步收缩 因此采用遍历
			{
				if(pActiv[k].start>=i && pActiv[k].end<=j)
				{
					temp = 1+memo[i][pActiv[k].start]+memo[pActiv[k].end][j];
					if(temp>memo[i][j])
					{
						memo[i][j] = temp;
						res[i][j] = k;
					}
				}
			}
		}
	cout<<"numAct = "<<memo[0][N]<<endl;
	Display(res, 0, N, pActiv);
	cout<<endl;
}
*/
//===============================================贪心算法—递归版===================================================================//
/*
void Greedy_Select(int start, int end, PActiv pAc, int f_ac, int e_ac)
{
	while( (pAc[f_ac].start<start || pAc[f_ac].end>end) && f_ac<=e_ac)
		f_ac++;
	if(f_ac <= e_ac)
	{
		cout<<"A"<<f_ac<<" ";
		Greedy_Select(pAc[f_ac].end, end, pAc, f_ac, e_ac);
	}
}
*/
//===============================================贪心算法—迭代版===================================================================//
/*
void Greedy_Select(int start, int end, PActiv pAc, int f_ac, int e_ac)
{
	for(int i=f_ac; i<=e_ac; i++)
	{
		if(pAc[i].start>=start && pAc[i].end<=end)
		{
			start = pAc[i].end;
			cout<<"A"<<i<<" ";
		}
	}
}
*/
int main()
{
	Activ ac[M] = {{1,4}, {3,5}, {0,6}, {5,7}, {3,8}, {5,9}, {6,10}, {8,11}, {8,12}, {2,13}, {12,N}};
	//Dynamic_Select_memo(0, N, ac, 0, 10);
	Greedy_Select(0, N, ac, 0, 10);
	return 0;
}