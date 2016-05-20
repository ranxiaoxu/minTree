#pragma once 

#include"Heap.h"
#include"UnionFindSet.h"
using namespace std;

template<class V,class E>
struct EdgeNode{
	EdgeNode<V,E>* _next;
	E _w;                     //权值
	size_t _srcIndex;         //源顶点的下标
	size_t _dstIndex;         //目标顶点的下标

	EdgeNode(const E &w,size_t srcIndex,size_t dstIndex)
		:_w(w)
		,_next(NULL)
		,_srcIndex(srcIndex)
		,_dstIndex(dstIndex)
	{}
};
template<class V,class E>
class GraphLink{
	typedef EdgeNode<V,E> Edge;
public:
	GraphLink(size_t size,bool isDict = false)
		:_size(size)
		,_vArray(new V[size])
		,_isDict(isDict )
	{}

	GraphLink(V* vArray,const size_t size,bool isDict = false)
		:_size(size)
		,_vArray(new V[size])
		,_isDict(isDict)
	{
		Create(vArray,size);
	}
	void AddEdge(const size_t &src,const size_t &dst,const E &w)
	{
		size_t srcIndex = GetIndex(src);
		size_t dstIndex = GetIndex(dst);
		if(_isDict == true)
		{
			_AddEdge(srcIndex,dstIndex,w);
		}
		else
		{
			_AddEdge(srcIndex,dstIndex,w);
			_AddEdge(dstIndex,srcIndex,w);
		}
	}

	bool Kruskal(GraphLink<V,E> &minTree)
	{
		minTree.Create(_vArray,_size);

		struct CompareEdge
		{
			bool operator()(Edge *l,Edge *r)
			{
				return l->_w < r->_w;
			}
		};
		
		Heap<Edge *,CompareEdge> hp;     //建一个小堆，把边都Push到堆中
		for(size_t i = 0;i < _size;i++)
		{
			Edge *cur = _edges[i];
			while(cur)
			{
				hp.Push(cur);
				cur = cur->_next;
			}
		}

		UnionFindSet uf(_size);

		int count = 1;
		while(count < _size)     //只需要添加n-1条边
		{
			if(hp.Empty() == true)
				return false;

			Edge *top = hp.top();
			hp.Pop();

			int root1 = uf.FindRoot(top->_srcIndex);
			int root2 = uf.FindRoot(top->_dstIndex);

			if(root1 != root2)
			{
				minTree._AddEdge(top->_srcIndex,top->_dstIndex,top->_w);
				minTree._AddEdge(top->_dstIndex,top->_srcIndex,top->_w);

				uf.Combine(root1,root2);
				++count;
			}
		}
		return true;
	}

	void Prime(GraphLink<V,E> &minTree)
	{
		minTree.Create(_vArray,_size);

		struct CompareEdge
		{
			bool operator()(Edge *l,Edge *r)
			{
				return l->_w < r->_w;
			}
		};
		
		bool visited[_size] = new bool[_size]();   //用来标记顶点是否被访问过

		Heap<Edge *,CompareEdge> hp;     //建一个小堆
		int src = 0;
		int count = 1;
		while(count < _size)     //只需要添加n-1条边
		{
			if(visited[src] == false)   //
			{
				Edge* cur = _edges[src];
				while(cur != NULL)
				{
					hp.Push(cur);
					cur = cur->_next;
				}
				visited[src] = true;
			}

			if(hp.Empty() == true)
				return false;

			Edge *top = hp.top();
			hp.Pop();

			if(!(top->_dstIndex == true && top->_srcIndex == true))
			{
				minTree._AddEdge(top->_srcIndex,top->_dstIndex,top->_w);
				minTree._AddEdge(top->_dstIndex,top->_srcIndex,top->_w);

				++count;
			}
		}
		return true;
	}

	void Display()
	{
		//打印顶点
		for(int i = 0;i < _size;++i)
		{
			cout<<i<<":"<<_vArray[i]<<" ";
		}
		cout<<endl;
		//打印临接表
		for(int i = 0;i < _size;++i)
		{
			Edge *cur = _edges[i];
			cout<<_vArray[i]<<"["<<i<<"]"<<"->";
			while(cur)
			{
				cout<<cur->_w<<"["<<cur->_dstIndex<<"]"<<"->";
				cur = cur->_next;
			}
			cout<<"NULL"<<endl;
		}
	}
protected:
	void Create(V* vArray,const size_t size)
	{
		for(int i = 0;i < _size;++i)
		{
			_vArray[i] = vArray[i];
		}
		_edges = new Edge*[size]();
	}
	void _AddEdge(const size_t &src,const size_t &dst,const E &w)
	{
		Edge *tmp = new Edge(w,src,dst);
		//进行头插
		tmp->_next = _edges[src];
		_edges[src] = tmp;
	}
	size_t GetIndex(const V &v)
	{
		for(int i = 0;i < _size;++i)
		{
			if(_vArray[i] == v)
				return i;
		}
	}
private:
	V *_vArray;     //顶点集合
	size_t _size;   //顶点的个数
    Edge **_edges;  //边集合
	bool _isDict;   //标志是无向图还是有向图
};