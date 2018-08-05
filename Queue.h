#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
//���е������� 
//�Ƚ��ȳ� �������� ���� ɾ�� ��С �Ƿ�Ϊ�� 

//���ȼ�����������
#include"Vector.h"
#include"List.h"

template <class T, class Container>
class Queue{
public:
	void Push(const T& x)
	{
		return _con.PushBack(x);
	}
	void Pop_front()
	{
		return _con.PopFront();
	}
	bool Empty(){
		return _con.Empty();
	}
	size_t Size(){
		return _con.Size();
	}
	T& Front(){
		return _con.Front();
	}



protected:
	Container _con;
};


void test3()
{
	//Queue<string, List<string>> s;
	//s.Push("11");
	//s.Push("222222222222222222222222222222222222");
	//s.Push("33");
	Queue<int, List<int>> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	while (!s.Empty())
	{
		cout << s.Front() << " ";
		s.Pop_front();
	}
	cout << endl;
}
