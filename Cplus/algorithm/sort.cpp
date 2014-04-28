#include <boost/random.hpp>
#include <algorithm>
using namespace boost;
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>//控制精度所需头文件
using namespace std;
#include "newtimer.cpp"

#define SIZE10       10
#define SIZE1000     1000
#define SIZE10000    10000
#define SIZE100000   100000

#define  FILE_IN_10      "sample10.data"
#define  FILE_IN_1000    "sample1000.data"
#define  FILE_IN_10000   "sample10000.data"
#define  FILE_IN_100000  "sample100000.data"

#define  FILE_OUT_10      "result10.data"
#define  FILE_OUT_1000    "result1000.data"
#define  FILE_OUT_10000   "result10000.data"
#define  FILE_OUT_100000  "result100000.data"


void CreateSample(int size, string str)
{//创建样本文件
	cout << "Sample file " << str << "begin creating!" << endl;
	fstream fs;
	fs.open(str.c_str(), ios_base::out);
	if (fs.good())
	{
		mt19937 rng((unsigned)time(0));
		uniform_01<mt19937 &> u01(rng);

		for (int i = 0; i < size; ++i)
		{
			fs << u01() << " ";
			if (i % 10 == 9)
			{
				fs << "\n";
			}
		}
		fs.close();
		cout << "Sample file " << str << " created!" << endl;
	}
	else
	{
		cout << "File open fail!" << endl;
	}
}


void ReadSample(string str, vector<double> &temp)
{//读取样本
	fstream fs;
	double db = 0.0;
	fs.open(str.c_str());
	if (fs.good())
	{
		//发现读出11个数，很是郁闷，最后一个数，读了两遍~
		//发现最后多个空格，他判断文件不为空，所以决定放弃这种读取文件方式
/*
		while(!fs.eof())
		{
			fs >> db;
			temp.push_back(db); 
		}*/
		//我不是很喜欢这种方式，但没办法
		while(fs >> db)
		{		
			temp.push_back(db); 
		}
		cout << "Read " << str << " Over!\n" << endl;
	}
	else
	{
		cout << "File open fail!" << endl;
	}
}

void SaveResult(string str, vector<double> &temp)
{//保存排序结果
	fstream fs;
	fs.open(str.c_str(), ios_base::out);
	if (fs.good())
	{
		for (vector<double>::iterator re = temp.begin(); re != temp.end(); re++)
		{
			fs << *re << " ";
		}
		cout << str <<" resule output complete!\n" << endl;
		fs.close();
	}
	else
	{
		cout << "File open fail!\n" << endl;
	}
}

//以上是辅助函数
//--------------------------------无敌分界线 ：> ---------------------------------
//一下是排序函数
//在刚写完快排的时候，发现犯了一个重大错误，突然意识到这是个双精度浮点数...不能这样直接比较
//但是，根据排序结果，我暂时不决定自己写比较函数。结果看似差别不大，因为生成的浮点数位数比较小

//先实现牛b的QuickSort
int Partion(vector<double> &temp, int low, int high)
{//快排划分
	double pivotkey;
	pivotkey = temp[low];
	while (low < high)
	{
		while (low < high && temp[high] >= pivotkey)
		{
			high--;
		}
		temp[low] = temp[high];
		while (low < high && temp[low] <= pivotkey)
		{
			low++;
		}
		temp[high] = temp[low];
	}
	temp[low] = pivotkey;
	return low;
}

void QuickSort(vector<double> &temp, int left, int right)
{
	if (left < right)
	{
		int i = Partion(temp, left, right);
		QuickSort(temp, left, i - 1);
		QuickSort(temp, i + 1, right);
	}
}
//快排函数
void Quick_Sort(string strin, int size, string strout)
{//为了防止代码重复，写这个函数，本来想用函数指针将所有排序统一调用，但排序参数不同。囧
	vector<double> sample;
	ReadSample(strin, sample);
	//排序
	string str("elapse time:");
	cout << str;
	{	
		new_progress_timer<4> time;
		QuickSort(sample, 0, size - 1);		
	}
	//保存排序结果
	//输出的东西太多了。。每个排序一个文件夹吧
	strout = "QuickSort\\" + strout;
	SaveResult(strout, sample);
	sample.clear();
}
//以上是快排
//--------------------------------无敌分界线 ：> ---------------------------------
//合并排序
void Merge(vector<double> &temp, int start, int mid, int end)
{
	/*vector<double> arr1(0);
	vector<double> arr2(0);
	for (int i = 0; i <= mid - start; ++i)
	{
		arr1.push_back(temp[start + i]);
		cout << arr1[i];
	}
	for (int i = 0; i <= end - mid - 1; ++i)
	{
		arr2.push_back(temp[mid + i]);
		cout << arr2[i];
	}

	int i = 0, j = 0, k = 0;
	for (int k = start; k <=end; ++k)
	{
		if (arr1[i] <= arr2[j] && i <= mid - start && j <= end - mid - 1)
		{
			temp[k] = arr1[i];
			++i;
		}
		else
		{
			temp[k] = arr2[j];
			++j;
		}
	}

	for (;i <= mid - start; ++i)
	{
		temp[k] = arr1[i];
		++k;
	}
	for (;j <= end - mid - 1; ++j)
	{
		temp[k] = arr1[j];
		++k;
	}
	*/


	int j, k, l;
	vector<double> arr(temp);
	for (j = mid + 1, k = start; start <= mid && j <= end; ++k)
	{
		if (arr[start] < arr[j])
		{
			temp[k] = arr[start++];
		}
		else
		{
			temp[k] = arr[j++];
		}
	}
	if (start <= mid)
	{
		for (l = 0; l <= mid - start; ++l)
			temp[k + l] = arr[start + l];
	} 
	if (j <= end)
	{
		for (l = 0; l <= end - j; ++l)
			temp[k + l] = arr[j + l];
	}
	
/*
	int i = start, j = mid + 1;
	int m = mid, n = end;
	int k = 0;
	vector<double> helper(temp.size());
	while (i <= m && j <= n)
	{
		if (temp[i] < temp[j])
		{
			helper[k++] = temp[i++];
		}
		else
		{
			helper[k++] = temp[j++];
		}
	}

	while (i <= m)
	{
		helper[k++] = temp[i++];
	}
	while (j <= n)
	{
		helper[k++] = temp[j++];
	}

	for (i = 0; i < k; ++i)
	{
		temp[start + i] = helper[i];
	}*/

}

void MergeSort(vector<double> &temp, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
//		cout << mid << endl;
		MergeSort(temp, start, mid);
		MergeSort(temp, mid + 1, end);
		Merge(temp, start, mid, end);
	}
}

void Merge_Sort(string strin, int size, string strout)
{
	vector<double> sample;
	ReadSample(strin, sample);
	//排序
	string str("elapse time:");
	cout << str;
	{	
		new_progress_timer<4> time;
		MergeSort(sample, 0, size - 1);		
	}
	strout = "MergeSort\\" + strout;
	SaveResult(strout, sample);
	sample.clear();
}
//--------------------------------无敌分界线 ：> ---------------------------------
//插入排序
void InsertSort(vector<double> &temp)
{
	int j;
	double key;

	for (unsigned int i = 1; i < temp.size(); ++i)
	{
		key = temp[i];
		j = i - 1;
		while(j >= 0 && temp[j] > key)
		{
			temp[j + 1] = temp[j];
			--j;
		}
		temp[j + 1] = key;
//		cout << i <<"\n";
	}
}

void Insert_Sort(string strin, int size, string strout)
{
	vector<double> sample;
	ReadSample(strin, sample);
	//排序
	string str("elapse time:");
	cout << str;
	{	
		new_progress_timer<4> time;
		InsertSort(sample);		
	}
	strout = "InsertSort\\" + strout;
	SaveResult(strout, sample);
	sample.clear();
}
//-
//--------------------------------无敌分界线 ：> ---------------------------------
//希尔排序
void ShellSort(vector<double> &temp)
{
	for (int incr = 3; incr > 0;  --incr)
	{
		for (unsigned int i = 0; i < (temp.size() - 1) / incr; ++i)
		{
			for (unsigned int j = i + incr; i < temp.size(); i += incr)
			{
				double db = temp[i];
				int k = i - incr;
				while(k >= 0 && temp[k] > db)
				{
					temp[k + incr] = temp[k];
					k -= incr;
				}
				temp[k + incr] = db;
			}
		}
	}
}
void Shell_Sort(string strin, int size, string strout)
{
	vector<double> sample;
	ReadSample(strin, sample);
	//排序
	string str("elapse time:");
	cout << str;
	{	
		new_progress_timer<4> time;
		ShellSort(sample);		
	}
	strout = "ShellSort\\" + strout;
	SaveResult(strout, sample);
	sample.clear();
}
//--------------------------------无敌分界线 ：> ---------------------------------
//冒泡排序
void BubbleSort(vector<double> &temp)
{
	bool exchange;
	for (unsigned int i = 0; i < temp.size(); ++i)
	{
		exchange = false;
		for (unsigned int j = temp.size() - 1; j > i; --j)
		{
			if (temp[j - 1] > temp[j])
			{
				swap(temp[j - 1], temp[j]);
				exchange = true;
			}
		}
		if (!exchange)
		{
			return;
		}
	}
}

void Bubble_Sort(string strin, int size, string strout)
{
	vector<double> sample;
	ReadSample(strin, sample);
	//排序
	string str("elapse time:");
	cout << str;
	{	
		new_progress_timer<4> time;
		BubbleSort(sample);		
	}
	strout = "BubbleSort\\" + strout;
	SaveResult(strout, sample);
	sample.clear();
}

//--------------------------------无敌分界线 ：> ---------------------------------
//桶排序算法
void BucketSort(vector<double> &temp)
{
	vector<double> bucket[10];
	double key;
	int pos;
	for (unsigned int i = 0; i < temp.size(); ++i)
	{
		key = temp[i];
		pos = key * 10;
//		cout << key << ":" << pos << endl;
		bucket[pos].push_back(key);

		//插入排序排桶


		int j = bucket[pos].size() - 2;
		while(j >= 0 && bucket[pos][j] > key)
		{
			bucket[pos][j + 1] = bucket[pos][j];
			--j;
		}
		bucket[pos][j + 1] = key;
		//		cout << i <<"\n";


		//STL sort
//		sort(bucket[pos].begin(), bucket[pos].end());
	}

/*
	for (int i = 0; i < 10; ++i)
	{
		for (unsigned int j = 0; j < bucket[i].size(); ++j)
		{
			cout << bucket[i][j] << " ";
		}
		cout << "\n";
	}	
*/

	
	int k = 0;
	for (int m = 0; m < 10; ++m)
	{
		for (unsigned int n = 0; n < bucket[m].size(); ++n)
		{
			temp[k++] = bucket[m][n];
		}
	}
}

void Bucket_Sort(string strin, int size, string strout)
{
	vector<double> sample;
	ReadSample(strin, sample);
	//排序
	string str("elapse time:");
	cout << str;
	{	
		new_progress_timer<4> time;
		BucketSort(sample);		
	}
	strout = "BucketSort\\" + strout;
	SaveResult(strout, sample);
	sample.clear();
}
//--------------------------------无敌分界线 ：> ---------------------------------
int main( int argc, char* argv[] )
{


	//创建不同样本
	CreateSample(SIZE10, FILE_IN_10);
	CreateSample(SIZE1000, FILE_IN_1000);
	CreateSample(SIZE10000, FILE_IN_10000);
	CreateSample(SIZE100000, FILE_IN_100000);



	//四个版本快排



	Quick_Sort(FILE_IN_10, SIZE10, FILE_OUT_10);
	Quick_Sort(FILE_IN_1000, SIZE1000, FILE_OUT_1000);
	Quick_Sort(FILE_IN_10000, SIZE10000, FILE_OUT_10000);
	Quick_Sort(FILE_IN_100000, SIZE100000, FILE_OUT_100000);





	//合并排序


	Merge_Sort(FILE_IN_10, SIZE10, FILE_OUT_10);
	Merge_Sort(FILE_IN_1000, SIZE1000, FILE_OUT_1000);
	Merge_Sort(FILE_IN_10000, SIZE10000, FILE_OUT_10000);
	Merge_Sort(FILE_IN_100000, SIZE100000, FILE_OUT_100000);





	//插入排序

	Insert_Sort(FILE_IN_10, SIZE10, FILE_OUT_10);
	Insert_Sort(FILE_IN_1000, SIZE1000, FILE_OUT_1000);
	Insert_Sort(FILE_IN_10000, SIZE10000, FILE_OUT_10000);
	Insert_Sort(FILE_IN_100000, SIZE100000, FILE_OUT_100000);


	//冒泡排序


	Bubble_Sort(FILE_IN_10, SIZE10, FILE_OUT_10);
	Bubble_Sort(FILE_IN_1000, SIZE1000, FILE_OUT_1000);
	Bubble_Sort(FILE_IN_10000, SIZE10000, FILE_OUT_10000);
	Bubble_Sort(FILE_IN_100000, SIZE100000, FILE_OUT_100000);


	//希尔排序

	Shell_Sort(FILE_IN_10, SIZE10, FILE_OUT_10);
	Shell_Sort(FILE_IN_1000, SIZE1000, FILE_OUT_1000);
	Shell_Sort(FILE_IN_10000, SIZE10000, FILE_OUT_10000);
	Shell_Sort(FILE_IN_100000, SIZE100000, FILE_OUT_100000);



	//桶排序



	Bucket_Sort(FILE_IN_10, SIZE10, FILE_OUT_10);
	Bucket_Sort(FILE_IN_1000, SIZE1000, FILE_OUT_1000);
	Bucket_Sort(FILE_IN_10000, SIZE10000, FILE_OUT_10000);
	Bucket_Sort(FILE_IN_100000, SIZE100000, FILE_OUT_100000);


	system("pause");
	return 0;
}