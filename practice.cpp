#define _CRT_SECURE_NO_WARNINGS 1
#if 0
#include<iostream>
using namespace std;
class MyClass
{
public:
	virtual void fun1()
	{}
	virtual void fun2()
	{}
private:
	int a;
};
void test(){
	MyClass a1;
}

int main(){

	test();
	system("pause");
	return 0;
	
}
#endif

#include<iostream>
using namespace std;

class person
{
public:
	virtual void fun1(){
		cout << "买票" << endl;
	}
	void fun2()
	{
		printf("wo  shi  fu lei\n");
	}
private:
	string _name;
};

class student:public person
{
public:
	void fun1(){
		cout << "买票-半价" << endl;
	}
	void fun2()
	{
		printf("我是重定义\n");
	}
private:
	string _id;
};

void test(person& p){
	p.fun1();

}



int main(){
    
	person p;
	student s;
	person *q = &p;
	q->fun2();
	q->fun1();
	q = &s;
	q->fun2();
	q->fun1();

	//test(p);
	//test(s);
	//s.fun2();
	//p.fun2();
	system("pause");
	return 0;
}

