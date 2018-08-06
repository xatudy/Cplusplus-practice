#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//静态内存用来保存局部static对象 类static数据成员 以及定义在任何函数之外的变量
//栈内存用来保存定义在函数内的非static对象  以上两内存中的对象由编译器自动创建销毁
//对于栈对象仅仅在其定义的程序块运行时才存在 static对象在使用之前分配在程序结束时销毁
#if 0
/*于编译器来说，智能指针实际上是一个栈对象，并非指针类型，
在栈对象生命期即将结束时，智能指针通过析构函数释放有它管理的
堆内存。所有智能指针都重载了“operator->”操作符，直接返回对象的引用，
用以操作对象。访问智能指针原来的方法则使用“.”
操作符。先抛开智能指针的几个版本不说，我们先来讲一下它里面的 * 和 -> 是如何进行运算符重载的*/
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
	//调用*a 其实是a.operator(&a) 返回值是T& 而不是T 这是因为 *a=10 返回值为T时返回的是
	//空间里存的10 是一个常量 常量不能作为左值  而T&则是返回装着10 的这段空间
	cout << (ap2->aa) << "  " << (ap2->bb) << endl;
	//ap2->aa实际上是ap2.operator->()->aa
	system("pause");
	return 0;
}
#endif
//常见三个版本
//1管理权线转移（C++11 已放弃） 2防拷贝 3引用计数

//管理权限转移 auto_ptr
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
	Autoptr(Autoptr<T>& ap){ //拷贝构造
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
			cout << "释放空间le" << endl;
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
	cout << *ap1 << endl;//调试到这一步程序崩溃了，罪魁祸首就是AutoPtr<int>ap2(ap1)，
	//这里原因就是ap2完全的夺取了ap1的管理权。然后
    //导致ap1无家可归，访问它的时候程序就会崩溃。
	//如果在这里调用ap2 = ap1程序一样会崩溃原因还是ap1被彻彻底底的夺走一切，
	system("pause");
	return 0;
}
#endif
//Scoped_ptr 独占资源
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
	//Scoped_ptr<int> sp2(sp1);  不可以进行拷贝构造 此函数设置为私有 不可进行访问
	//system("pause");
	//return 0;

//}


//shared_ptr 允许多个指针指向同一个对象
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
	//当进行拷贝或赋值操作时 每个shared_ptr都会有一个计数器 记录着和它指向相同空间的shared_ptr的个数

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
//让p1的next指向p2 让p2的prev指向p1 （p1这块结点有两个指针在管理 p1 和 p2的_prev）同理p2也是一样的
//因此pCount为2  出了函数作用域 要销毁p1和p2结点空间  就要销毁指向它们结点的所以指针  
//prev的要释放的前提是next释放，而next的释放又依赖于prev的释放。最后就形成了循环引用(内存泄露)，谁都释放不了。   

//循环引用问题    
//怎么解决 （弱引用智能指针） weak_ptr 这种的指针不能单独管理资源 它是以shared_ptr助手的身份出现的（解决循环引用问题）
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