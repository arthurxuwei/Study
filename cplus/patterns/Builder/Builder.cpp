#include "Builder.h"
#include <iostream>

void ConcreateBuilder1::BuilderPartA()
{
	
	std::cout << " BuilderPartA by ConcreateBuilder1n " <<std::endl;

}

void ConcreateBuilder1::BuilderPartB()
{
	
	std::cout << " BuilderPartB by ConcreateBuilder1n " <<std::endl;
	
}

void ConcreateBuilder2::BuilderPartA()
{
	
	std::cout << " BuilderPartA by ConcreateBuilder2n " <<std::endl;
	
}

void ConcreateBuilder2::BuilderPartB()
{
	
	std::cout << " BuilderPartB by ConcreateBuilder2n " <<std::endl;
	
}

Director::Director(Builder * pBuilder)
	: m_pBuilder(pBuilder)
{
	
}

Director:: ~Director()
{
	
	delete m_pBuilder;
	m_pBuilder = NULL;
	
}

//�� Construct������ʾһ�������������������,��ͬ�Ĳ���֮���װ�䷽ʽ����һ�µ�,
//�� ���ȹ���PartA�����PartB,ֻ�Ǹ��ݲ�ͬ�Ĺ����߻��в�ͬ�ı�ʾ
void Director::Construct()
{
	
	m_pBuilder -> BuilderPartA();
	
	m_pBuilder -> BuilderPartB();
	
}