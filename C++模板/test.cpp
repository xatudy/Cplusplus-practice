#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

#include "Vector.h"
#include "stack.h"
void test(){
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);

	Vector<string> v2;
	v2.PushBack("11111111111111111111111111111111111111111111111111111111111111111111111111111");
	v2.PushBack("11111111111111111111111111111111111111111111111111111111111111111111");
	v2.PushBack("222222222222222222222222222222222222222222222222222222222222222222222222222222222");
	v2.PushBack("222222222222222222222222222222222222222222222222222222222222222222222222222222222");
	v2.PushBack("222222222222222222222222222222222222222222222222222222222222222222222222222222222");

	//for (size_t i = 0; i < v1.Size(); ++i){

	//	cout << v1[i] << endl;
	//}
	for (size_t i = 0; i < v2.Size(); ++i){
		cout << v2[i] << " ";
	}
	cout << endl;
}

int main(){

	//test();
	test2();
	system("pause");
	return 0;
}