#pragma once

#include<assert.h>

class UnionFindSet{
public:
	UnionFindSet(size_t size)
		:_a(new int[size])
		,_size(size)
	{
		for(int i = 0;i < _size;++i)
		{
			_a[i] = -1;
		}
	}

	void Combine(int root1,int root2)   //合并两个集合
	{
		assert(_a[root1] < 0);
		assert(_a[root2] < 0);

		_a[root1] += _a[root2];
		_a[root2] = root1;
	}

	int FindRoot(int child)    //寻找祖先结点
	{
		while(_a[child] >= 0)
		{
			child = _a[child];
		}

		return child;
	}
private:
	int *_a;
	size_t _size;
};
