#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//��̬�ڴ���������ֲ�static���� ��static���ݳ�Ա �Լ��������κκ���֮��ı���
//ջ�ڴ��������涨���ں����ڵķ�static����  �������ڴ��еĶ����ɱ������Զ���������
//����ջ����������䶨��ĳ��������ʱ�Ŵ��� static������ʹ��֮ǰ�����ڳ������ʱ����
#if 0
/*�ڱ�������˵������ָ��ʵ������һ��ջ���󣬲���ָ�����ͣ�
��ջ���������ڼ�������ʱ������ָ��ͨ�����������ͷ����������
���ڴ档��������ָ�붼�����ˡ�operator->����������ֱ�ӷ��ض�������ã�
���Բ������󡣷�������ָ��ԭ���ķ�����ʹ�á�.��
�����������׿�����ָ��ļ����汾��˵������������һ��������� * �� -> ����ν�����������ص�*/
struct MyStruct
{
	int aa = 10;
	int bb = 20;
};

template<class T>
class Myclass{

public:	
	Myclass(T* ptr)
		:_ptr(ptr)
	{}
	T& operator*(){
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	~Myclass(){
		delete _ptr;
	}

private:
	T* _ptr;
};

int main(){
	Myclass<int>a(new int);
	*a = 10;
	Myclass<MyStruct>ap2(new MyStruct);
	cout << *a << endl;  
	//����*a ��ʵ��a.operator(&a) ����ֵ��T& ������T ������Ϊ *a=10 ����ֵΪTʱ���ص���
	//�ռ�����10 ��һ������ ����������Ϊ��ֵ  ��T&���Ƿ���װ��10 ����οռ�
	cout << (ap2->aa) << "  " << (ap2->bb) << endl;
	//ap2->aaʵ������ap2.operator->()->aa
	system("pause");
	return 0;
}
#endif
//���������汾
//1����Ȩ��ת�ƣ�C++11 �ѷ����� 2������ 3���ü���

//����Ȩ��ת�� auto_ptr
template<class T>
class Autoptr
{
public:
	Autoptr(T* ptr=NULL)
		:_ptr(ptr)
	{}
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
	Autoptr(Autoptr<T>& ap){ //��������
		this->_ptr = ap._ptr;
		ap._ptr = NULL;
	}

	Autoptr<T>& operator=(Autoptr<T>& ap){
		if (this != &ap){
			delete this->_ptr;
			this->_ptr = ap._ptr;
			ap._ptr = NULL;
		}
		return *this;
	}
	~Autoptr(){
		if (_ptr){
			cout << "�ͷſռ�le" << endl;
			delete _ptr;
		}
	}

private:
	T* _ptr;
};
#if 0
int main(){

	//Autoptr<int>ap1(new int);
	//*ap1 = 10;
	//Autoptr<int>ap2(ap1);
	//Autoptr<int>ap3(ap2);
	//*ap3 = 20;
	//ap2 = ap3;
	//cout << *ap2 << endl;
	Autoptr<int>ap1(new int);
	*ap1 = 10;
	Autoptr<int>ap2(ap1);
	cout << *ap1 << endl;//���Ե���һ����������ˣ�������׾���AutoPtr<int>ap2(ap1)��
	//����ԭ�����ap2��ȫ�Ķ�ȡ��ap1�Ĺ���Ȩ��Ȼ��
    //����ap1�޼ҿɹ飬��������ʱ�����ͻ������
	//������������ap2 = ap1����һ�������ԭ����ap1�������׵׵Ķ���һ�У�
	system("pause");
	return 0;
}
#endif
//Scoped_ptr ��ռ��Դ
template<class T>
class Scoped_ptr
{
public:
	Scoped_ptr(T* _Ptr=NULL)
		:_ptr(ptr)
	{}
	T& operator*(){
		return *_ptr;
	}
	T* operator->(){
		return _ptr;
	}
	~Scoped_ptr()
	{
		if (_ptr){
			delete _ptr;
		}
	}
private:
	Scoped_ptr(const Scoped_ptr<T>&);
	//{}
	Scoped_ptr<T>& operator=(Scoped_ptr<T>& ap);
  
private:
	T* _ptr;
};

//int main(){
	//Scoped_ptr<int> sp1(new int);
	//Scoped_ptr<int> sp2(sp1);  �����Խ��п������� �˺�������Ϊ˽�� ���ɽ��з���
	//system("pause");
	//return 0;

//}


//shared_ptr ������ָ��ָ��ͬһ������
template<class T>
class Shared_ptr{
public:
	Shared_ptr(T* ptr = NUll)
		:_ptr(ptr)
		, _pCount(new int(1))
	{}
	/*{
		if (_ptr){
			_pCount = new int(1);
		}
	}*/
	Shared_ptr(const Shared_ptr<T>& sp)
		:_ptr(sp._ptr)
		,_pCount(sp._pCount)
	{
		++GetRef();
	}
	//�����п�����ֵ����ʱ ÿ��shared_ptr������һ�������� ��¼�ź���ָ����ͬ�ռ��shared_ptr�ĸ���

	Shared_ptr<T>& operator=(const Shared_ptr<T>& sp){
		if (this != &sp)
		{
			Release();
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			++GetRef();
		}
		return *this;
	}
	T& operator*(){
		return *_ptr;
	}
	T* operator->(){
		return _ptr;
	}
	~Shared_ptr(){
		Release();
	}
	int Usecount(){
		return GetRef();
	}
private:
	void Release(){
		if (0 == --*_pCount &&_ptr){
			delete _ptr;
			delete _pCount;
			_ptr = NULL;
			_pCount = NULL;

		}
	}
	int& GetRef(){
		return *_pCount;
	}
private:
	T* _ptr;
	T* _pCount;
};

/*int main(){

	Shared_ptr<int> sp1(new int(10));
	Shared_ptr<int> sp2(sp1);

	*sp1 = 10;
	*sp2 = 20;
	cout << sp1.Usecount() << endl;
	cout << sp2.Usecount() << endl;

	Shared_ptr<int> sp3(new int(30));
	Shared_ptr<int> sp4(sp3);
	sp4 = sp2;
	*sp4 = 40;
	cout << sp3.Usecount() << endl;
	cout << sp4.Usecount() << endl;

	system("pause");
	return 0;
}*/
//��p1��nextָ��p2 ��p2��prevָ��p1 ��p1�����������ָ���ڹ��� p1 �� p2��_prev��ͬ��p2Ҳ��һ����
//���pCountΪ2  ���˺��������� Ҫ����p1��p2���ռ�  ��Ҫ����ָ�����ǽ�������ָ��  
//prev��Ҫ�ͷŵ�ǰ����next�ͷţ���next���ͷ���������prev���ͷš������γ���ѭ������(�ڴ�й¶)��˭���ͷŲ��ˡ�   

//ѭ����������    
//��ô��� ������������ָ�룩 weak_ptr ���ֵ�ָ�벻�ܵ���������Դ ������shared_ptr���ֵ���ݳ��ֵģ����ѭ���������⣩
//
#include<memory>
template<class T>
struct ListNode{
	//ListNode<T>* _next;
	weak_ptr<ListNode<T>> _next;
	//shared_ptr<ListNode<T>> _next;
	//ListNode<T>* _prev;
	weak_ptr<ListNode<T>> _prev;
	//shared_ptr<ListNode<T>> _prev;

	T _data;

	ListNode(const T& data = T())
		/*:_next(NULL)
		, _prev(NULL)
		, _data(data)*/
		:_data(data)
	{
		cout << "LisNode(const T& data):" << this << endl;
	}
	~ListNode(){
		cout << "~ListNode():" << this << endl;
	}
};

void Testshared_ptr(){

	shared_ptr<ListNode<int>> p1(new ListNode<int>(10));
	shared_ptr<ListNode<int>> p2(new ListNode<int>(20));

	cout << p1.use_count() << endl;
	cout << p2.use_count() << endl;

	p1->_next = p2;
	p2->_prev = p1;
	cout << p1.use_count() << endl;
	cout << p2.use_count() << endl;
}

int main(){

	Testshared_ptr();
	system("pause");
	return 0;
}