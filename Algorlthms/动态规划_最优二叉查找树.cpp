/*
	DJ.W 2012.7.28
	问题描述：《算法导论》P212
		在这个问题中 由于最优查找二叉树有键值和虚拟键两种结点 所以很容易弄混
	其实虚拟键只是一种称谓 可以将其看作普通叶子结点来处理  因此在递归版和二叉
	树构造Output_tree的时候均以i i-1 作为终止条件 而至于键值在那里去了 为什么
	不给i==j返回键值概率 其实键值概率已经被w[i][j]统筹了:
	         w[i][i] = 2 * (pNode[i-1] + pNode[i]) + pKey[i];

    在递归版中 也可以不初始化memo 直接在终止条件处给最基本memo赋值

    
*/
#include<iostream>
using namespace std;

#define N 5
#define MAX_EP 123456789.0f

//===================================================迭代版========================================================================//
/*
void Output_tree(int root[N+1][N+1], int i, int j)
{
	if(i-1 == j)
	{
		cout<<"d"<<j<<endl;
		return;
	}
	if(i == j)
		cout<<"k"<<i<<endl;
	else cout<<"k"<<root[i][j]<<endl;

	cout<<"k"<<root[i][j]<<"的左孩子为:";
	Output_tree(root, i, root[i][j]-1);
	
	cout<<"k"<<root[i][j]<<"的右孩子为:";
	Output_tree(root, root[i][j]+1, j);

}
//由于要用到e[i][i-1]来表征叶子节点 因此将有效的键值移至pKey[1...N]
void optimal_tree(float pKey[N+1], float pNode[N+1])
{
	float e[N+2][N+1];
	float w[N+2][N+1];
	int root[N+1][N+1];
	for(int i=1; i<N+2; i++)
	{
		//初始化memo
		e[i][i-1] = pNode[i-1];
		w[i][i-1] = pNode[i-1];
	}

	for(i=0; i<N+1; i++)
		for(int j=0; j<N+1; j++)
			root[i][j] = -1;

	int j;
	float temp;
	for(int len=1; len<=N; len++)//长度规模
		for(int i=1; i<N-len+2; i++)//起始点
		{
			j = i+len-1;//截至点
			e[i][j] = MAX_EP;
			w[i][j] = w[i][j-1]+pKey[j]+pNode[j];
			for(int k=i; k<=j; k++)
			{
				temp = e[i][k-1] + e[k+1][j] + w[i][j];
				if(temp < e[i][j])
				{
					e[i][j] = temp;
					root[i][j] = k;
				}
			}
		}
	cout<<"最优二叉树期望值: "<<e[1][N]<<endl;
	Output_tree(root, 1, N);
}
*/
//=============================================递归版===============================================================================//

int count;
float optimal_tree_memo(float pKey[N+1], float pNode[N+1], int i, int j, 
						float memo[N+1][N+1], float w[N+2][N+1], int root[N+1][N+1])
{
	count++;
	//此处memo有备忘检查和递归终止两个功能 因为memo[i][i-1]有初值 i i-1即为最基本子问题
	if(memo[i][j] != MAX_EP)
		return memo[i][j];

	float temp;
	for(int k=i; k<=j; k++)
	{
		temp = optimal_tree_memo(pKey, pNode, i, k-1, memo, w, root)
			+ optimal_tree_memo(pKey, pNode, k+1, j, memo, w, root) + w[i][j];
		if(temp < memo[i][j])
		{
			root[i][j] = k;
			memo[i][j] = temp;
		}
	}
	return memo[i][j];
}

void Output_tree(int root[N+1][N+1], int i, int j)
{
	if(i-1 == j)
	{
		cout<<"d"<<j<<endl;
		return;
	}
	if(i == j)
		cout<<"k"<<i<<endl;
	else cout<<"k"<<root[i][j]<<endl;

	cout<<"k"<<root[i][j]<<"的左孩子为:";
	Output_tree(root, i, root[i][j]-1);
	
	cout<<"k"<<root[i][j]<<"的右孩子为:";
	Output_tree(root, root[i][j]+1, j);

}

void optimal_tree(float pKey[N+1], float pNode[N+1])
{
	float memo[N+1][N+1];
	float w[N+2][N+1];
	int root[N+1][N+1];

	for(int i=0; i<N+1; i++)
		for(int j=0; j<N+1; j++)
			memo[i][j] = MAX_EP;

	for(i=1; i<N+2; i++)
	{
		w[i][i-1] = pNode[i-1];
		memo[i][i-1] = pNode[i-1];
	}

    //注意j从i开始 否则w[i][i-1]将被覆盖
	for(i=0; i<N+2; i++)
		for(int j=i; j<N+1; j++)
			w[i][j] = w[i][j-1] + pNode[j] + pKey[j];

	optimal_tree_memo(pKey, pNode, 1, N, memo, w, root);

	cout<<"最优二叉树期望值:"<<memo[1][N]<<endl;
	cout<<"调用次数: "<<count<<endl;
	cout<<"二叉树构造: "<<endl;
	Output_tree(root, 1, N);
}


/*
int count;
float optimal_tree_o(float pKey[N+1], float pNode[N+1], int i, int j, float w[N+2][N+1])
{
    count++;
    if(i-1 == j)
		return pNode[i-1];

    float temp;
	float ep = MAX_EP;
	for(int k=i; k<=j; k++)
	{
		temp = optimal_tree_o(pKey, pNode, i, k-1, w) + optimal_tree_o(pKey, pNode, k+1, j, w) + w[i][j];
		if(temp < ep)
			ep = temp;
	}
	return ep;
}

void optimal_tree(float pKey[N+1], float pNode[N+1])
{

	float w[N+2][N+1];

    for(int i=1; i<N+2; i++)
	{
		w[i][i-1] = pNode[i-1];
	}


	for(i=0; i<N+2; i++)
		for(int j=i; j<N+1; j++)
			w[i][j] = w[i][j-1] + pNode[j] + pKey[j];

	
    cout<<"最优二叉树期望值:"<<optimal_tree_o(pKey, pNode, 1, N, w)<<endl;
	cout<<"调用次数: "<<count<<endl;
}
*/

int main()
{
	float pKey[N+1] = {0.0f, 0.15f, 0.10f, 0.05f, 0.10f, 0.20f};
	float pNode[N+1] = {0.05f, 0.10f, 0.05f, 0.05f, 0.05f, 0.10f};
	optimal_tree(pKey, pNode);
	return 0;
}

