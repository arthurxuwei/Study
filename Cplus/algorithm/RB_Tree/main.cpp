
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iomanip>
//#include <random>
#include <ctime>

#include <windows.h>
using namespace std;


#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include "RB_Tree.h"
#include "RB_Tree.cpp"
#include "OS_RBTree.h"
#include "OS_RBTree.cpp"

#define SAMPLE_SIZE 30000


void CreateSample (string str)
{
	fstream fs;
	fs.open(str.c_str(), ios_base::out);
	if (fs.good())
	{
		int temp;
		cin >> temp;
		while (cin.get () != '\n')
		{
			fs << temp << " ";
			cin >> temp;
		}
		fs << temp << " ";
		fs.close();

	//生成300，000个数
/*
		srand((unsigned)time(0));
		for (int i = 0; i < SAMPLE_SIZE; ++i)
		{
			fs << 1 + rand() % 300000 << " ";
		}
		fs.close();
*/
	}
	else
	{
		cout << "File open fail!" << endl;
	}
}


void ReadSample (string str, vector<int> &temp)
{//读取样本
	fstream fs;
	int db = 0;
	fs.open(str.c_str());
	if (fs.good())
	{
		while(fs >> db)
		{		
			temp.push_back(db); 
		}
	}
	else
	{
		cout << "File open fail!" << endl;
	}
}


/************************************************************************/
/* 无敌分割线又来了~~~~~~~~~                                                                  */
/************************************************************************/


int main()  
{  
	RB_Tree<int, int> rbTree;  //红黑树
//	BinarySearchTree<int> searchTree;//二叉搜索树

	vector<int> v;  

	cout << "Input key to contruct a rb-tree : ";
	CreateSample ("sample.data");



//	random_shuffle(v.begin(), v.end());  

 
	ReadSample ("sample.data", v);

//	copy(v.begin(), v.end(), ostream_iterator<int>(cout," "));  


	//添加结点
	for(unsigned int i=0; i < v.size(); ++i)  
	{  
		rbTree.Insert(v[i], 1);
//		searchTree.insert(v[i]);
	}  
	rbTree.PrintTree();
	cout << "Tree Height : " <<	rbTree.GetBlackHeight() ;
//	searchTree.printTree();

	rbTree.Delete( 15 );
	cout << "Delete key = 15 node!\n";
	rbTree.PrintTree();
	cout << "Tree Height : " <<	rbTree.GetBlackHeight() << endl ;
/*  时间精度不够
	time_t timeBegin, timeEnd;
	timeBegin = clock();
	rbTree.Find(15000);
//	Sleep(111);
	timeEnd = clock();
	printf("RB Tree search time : %f\n",	(double)(timeEnd - timeBegin)/CLOCKS_PER_SEC);

	timeBegin = clock();
	searchTree.contains(15000);
	timeEnd = clock();
	printf("search Tree search time : %f\n", (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC);
*/

/*

	LARGE_INTEGER  large_interger;  
	double dff;  
	__int64  c1, c2;  
	QueryPerformanceFrequency(&large_interger);  
	dff = large_interger.QuadPart;  
	QueryPerformanceCounter(&large_interger);  
	c1 = large_interger.QuadPart;  
	rbTree.Find(15000);
	QueryPerformanceCounter(&large_interger);  
	c2 = large_interger.QuadPart;   
	printf("RB tree : %lfms\n", (c2 - c1) * 1000 / dff);  

	QueryPerformanceFrequency(&large_interger);  
	dff = large_interger.QuadPart;  
	QueryPerformanceCounter(&large_interger);  
	c1 = large_interger.QuadPart;  
	searchTree.contains(15000);
	QueryPerformanceCounter(&large_interger);  
	c2 = large_interger.QuadPart;  
	printf("search Tree : %lfms\n", (c2 - c1) * 1000 / dff);  

*/
	OS_RBTree<int> osTree;  
	for(int i=1;i<=8;++i)  
		osTree.Insert(i);  
	osTree.PrintFormat(osTree.GetRoot(),0);  
	cout << endl;  
	cout << "the rank value is " << osTree.OS_Key_Rank(6) << endl;  

	return 0;  


}  