/*
   DJ.W
   2012.7.20
   问题描述: 《算法导论p193》
*/
#include<iostream>
using namespace std;

#define N 6

//=====================================================迭代版======================================================================//

void OutPut(int path[2][N], int Prior, int n)
{
	if(n<1)
		return;
	OutPut(path, path[Prior][n-1], n-1);
	cout<< "line: "<<Prior<<"  station: "<<n-1<<endl;
}

void Fastest_Way(int A0[N], int A1[N], int e[2], int x[2], int T[2][N])
{

	int path[2][N];
    //用于保存中间结果(即到达某一站最快的时间)
	int F[2][N];
	//初始化起点站
    F[0][0] = e[0] + A0[0];
	F[1][0] = e[1] + A1[0];
	//由最底层逐步向上求最优解
	for(int j=1; j<N; j++)
	{
	    //针对第一条装配线 第j+1站求最优解
		if(F[0][j-1] < F[1][j-1]+T[1][j-1])
		{
			F[0][j] = F[0][j-1]+A0[j];
			path[0][j] = 0;
		}
		else
		{
			F[0][j] = F[1][j-1]+T[1][j-1]+A0[j];
			path[0][j] = 1;
		}

        //针对第二条装配线 第j+1站求最优解
		if(F[1][j-1] < F[0][j-1]+T[0][j-1])
		{
			F[1][j] = F[1][j-1]+A1[j];
			path[1][j] = 1;
		}
		else
		{
			F[1][j] = F[0][j-1]+T[0][j-1]+A1[j];
			path[1][j] = 0;
		}
	}
	//由最终站最优解加上终止代价进行最后一次比较
    if(F[0][5]+x[0]>F[1][5]+x[1])
	{
		OutPut(path, 1, N);
		cout<<"the Fastest_Way cost: "<<F[1][5]+x[1]<<endl;
	}
	else
	{
		OutPut(path, 0, N);
        cout<<"the Fastest_Way cost: "<<F[0][5]+x[0]<<endl;
	}
}

//=======================================================递归版===================================================================//
/*
int count;
int Fastest_Way_memo(int A0[N], int A1[N], int e[2],  int T[2][N], int line, int station, int memo[2][N], int path[2][N])
{
	count++;
	if(memo[line][station])
		return memo[line][station];

	//递归终止到0号站台即终止条件时 要加上入站代价
	if(station == 0 && line == 0)
	{
		memo[0][0] = A0[0] + e[0];
	    return A0[0] + e[0];
	}
	if(station == 0 && line == 1)
	{
		memo[1][0] = A1[0] + e[1];
		return A1[0] + e[1];
	}
    
	int from_line0;
	int from_line1;
	if(line == 1)
	{
		from_line0 = Fastest_Way_memo(A0, A1, e,  T, 0, station-1, memo, path) + A1[station] + T[0][station-1];
		from_line1 = Fastest_Way_memo(A0, A1, e,  T, 1, station-1, memo, path) + A1[station];
	}
    else
	{
		from_line0 = Fastest_Way_memo(A0, A1, e,  T, 0, station-1, memo, path) + A0[station];
		from_line1 = Fastest_Way_memo(A0, A1, e,  T, 1, station-1, memo, path) + A0[station] + T[1][station-1];
	}

	if(from_line0 > from_line1)
	{
		memo[line][station] = from_line1;
		path[line][station] = 1;
		return from_line1;
	}
	else
	{
		memo[line][station] = from_line0;
		path[line][station] = 0;
		return from_line0;
	}
}

void OutPut(int path[2][N], int Prior, int n)
{
	if(n == 0)
		return;
	OutPut(path, path[Prior][n-1], n-1);
	cout<< "line: "<<Prior<<"  station: "<<n-1<<endl;
	
}

void Fastest_Way(int A0[N], int A1[N], int e[2], int x[2], int T[2][N])
{
	int memo[2][N];
	int path[2][N];
	for(int i=0; i<2; i++)
		for(int j=0; j<N; j++)
			memo[i][j] = 0;

	//为了便于递归统筹 将出战代价提出来 并且初始调用时应该确定line的取值 因此有两次调用
    int line0 = Fastest_Way_memo(A0, A1, e, T, 0, N-1, memo, path) + x[0];
	int line1 = Fastest_Way_memo(A0, A1, e, T, 1, N-1, memo, path) + x[1];

	cout<<"the best scheme: "<<endl;
	//根据最终选择不同 整体代价和OutPut初始调用也不同
	if(line0<line1)
	{
		OutPut(path, 0, N);
		cout<<"Fastest_Way cost : "<< line0 <<endl;
	}
	else
	{
		OutPut(path, 1, N);
	    cout<<"Fastest_Way cost : "<< line0 <<endl;
	}
	cout<<"count = "<<count<<endl;
	
}
*/

//---------------------------------------------------------------------------------------------------------------------------------//

int main()
{
	int A0[N] = {7,9,3,4,8,4};
	int A1[N] = {8,5,6,4,5,7};
	int e[2] = {2,4};
	int x[2] = {3,2};
	int T[2][N] = {{2,3,1,3,4},
					{2,1,2,2,1}};

	Fastest_Way(A0, A1, e, x, T);

	return 0;
}