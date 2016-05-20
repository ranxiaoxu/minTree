#include"minTree.h"
#include<stdio.h>
#include<iostream>
using namespace std;

void testGraphLink()
{
	char *a="ABCDE";
	GraphLink<char,int> gm(a,5);

	gm.AddEdge('A','D',10);
	gm.AddEdge('A','E',20);
	gm.AddEdge('B','C',10);
	gm.AddEdge('B','D',20);
	gm.AddEdge('B','E',30);
	gm.AddEdge('C','E',40);

	gm.Display();

	GraphLink<char,int> minTree(5);

	bool ret = gm.Kruskal(minTree);
	cout<<"�Ƿ�������С��������"<<ret<<endl;
	minTree.Display();

	GraphLink<char,int> minTree1(5);
	bool ret1 = gm.Kruskal(minTree1);
	cout<<"�Ƿ�������С��������"<<ret1<<endl;
	minTree1.Display();
}

int main()
{
	testGraphLink();
	system("pause");
	return 0;
}