/* by DiaN.x
 * 程序输出最长递增子序列
 * 注释部分为LCS算法
 */
#include <windows.h>
#include <iostream>
//#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;
//#define STRING_LENGTH 20

#define  N_LENGTH 10000
//获取指定长度的字符串
/*
void getRandomStrings(int length, string &str)
{
//	variate_generator<mt19937 &, uniform_smallint<>> rad(rng, ui);
	for (int i = 0; i < length; ++i)
	{
		str.push_back((char)(rand() % 26 + 97));
	}

}
*/

void getIntVector(vector<int> &v)
{
	for (unsigned int i = 0; i < N_LENGTH; ++i)
	{
		v.push_back(i);
	}

}

int main( int argc, char* argv[] )
{
//	srand((unsigned)time(0)); 
//	string x;
//	string y;
//	getRandomStrings(STRING_LENGTH, x);
//	getRandomStrings(STRING_LENGTH, y);
	vector<int> vec1;
	vector<int> vec2;
	getIntVector(vec1);
	getIntVector(vec2);

	random_shuffle( vec2.begin(), vec2.end() );


	//计时
	LARGE_INTEGER  large_interger;  
	double dff;  
	__int64  c1, c2;  
	QueryPerformanceFrequency(&large_interger);  
	dff = large_interger.QuadPart;  
	QueryPerformanceCounter(&large_interger);  
	c1 = large_interger.QuadPart;  
	//计时


	
/*显示随机后结果
	cout << "input integer array is : \n";
	for (unsigned int i = 0; i < vec2.size(); ++i)
	{
		cout << vec2[i] << " ";
	}
*/
	//二维数组记录子问题x[i]和y[i]的LCS的长度
/*
	int opt[STRING_LENGTH + 1][STRING_LENGTH + 1];
	//动态规划计算所有子问题
	for (int i = STRING_LENGTH - 1; i >= 0; --i)
	{
		for (int j = STRING_LENGTH - 1; j >= 0; --j)
		{
			if (x[i] == y[j])
				opt[i][j] = opt[i + 1][j + 1] + 1;
			else
				opt[i][j] = max(opt[i + 1][j], opt[i][j + 1]);
		}
	}
*/
	int **opt = new int *[N_LENGTH + 1];
	for (int i = 0; i < N_LENGTH + 1; ++i)
	{
		opt[i] = new int[N_LENGTH + 1];
	}
	//动态规划计算所有子问题
	for (int i = N_LENGTH - 1; i >= 0; --i)
	{
		for (int j = N_LENGTH - 1; j >= 0; --j)
		{
			if (vec1[i] == vec2[j])
				opt[i][j] = opt[i + 1][j + 1] + 1;
			else
				opt[i][j] = max(opt[i + 1][j], opt[i][j + 1]);
		}
	}
	/*
	 *如果我们记字符串Xi和Yj的LCS的长度为c[i,j]，我们可以递归地求c[i,j]：  
     *
     *            /      0                               if i<0 or j<0  
     *  c[i,j]=          c[i-1,j-1]+1                    if i,j>=0 and xi=xj  
     *           /       max(c[i,j-1],c[i-1,j]           if i,j>=0 and xi≠xj  
     *
	 */
//	cout << "substring1: " << x << endl;
//	cout << "substring2: " << y << endl;

/*
	int i = 0, j = 0;
	while (i < STRING_LENGTH && j < STRING_LENGTH)
	{
		if (x[i] == y[j])
		{
			cout << x[i];
			++i;
			++j;
		}else if (opt[i + 1][j] >= opt[i][j + 1])
		{
			++i;
		}
		else
			++j;
	}*/

	cout << "result is : \n";
	int i = 0, j = 0;
	while (i < N_LENGTH && j < N_LENGTH)
	{
		if (vec1[i] == vec2[j])
		{
			cout << vec1[i] << " ";
			++i;
			++j;
		}else if (opt[i + 1][j] >= opt[i][j + 1])
		{
			++i;
		}
		else
			++j;
	}


	//计时
	QueryPerformanceCounter(&large_interger);  
	c2 = large_interger.QuadPart;   
	printf("\nelaspe time : %lfms\n", (c2 - c1) * 1000 / dff);  



	for (int i = 0; i < N_LENGTH + 1; ++i)
	{
		delete[] opt[i];
	}
	delete opt;
}