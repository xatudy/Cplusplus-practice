#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include"Vector.h"
#include"List.h"
//适配器模式  拿一个东西适配出我想要的东西
//栈的适配器
template<class T,class Container>
class Stack{
public:

	void Push(const T& x){
		_con.PushBack(x);
    }
	
	void Pop(){
		_con.PopBack();
	}
	size_t Size(){
		return _con.Size();
	}
	bool Empty(){
		return _con.Empty();
	}
	T& Top(){
		return _con.Back();
	}
protected:
	Container _con;

};

void test2(){
	Stack<int, List<int>> s1;
	//Stack<int,Vector<int>> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(2);
	s1.Push(2);

	while (!s1.Empty())
	{
		cout << s1.Top() << "";
		s1.Pop();
	}
}
