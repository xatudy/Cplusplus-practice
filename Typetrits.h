#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
//类型萃取
struct __Truetype
{};
struct __Falsetype
{};


template<class T>
struct __Typetraits
{
	typedef __Falsetype IsPodType;
};

template<>//特化
struct __Typetraits<int>
{
	typedef __Truetype IsPodType;
};

//内置类型
template<class T>
T*__TypeCopy(T*dst, const T*src, size_t n,__Truetype){
	return (T*)memcpy(dst,src,sizeof(T)*n);
}
//自定义类型
template<class T>
T*__TypeCopy(T*dst, T*src, size_t n,__Falsetype){
	for (size_t i = 0; i < n; i++){
		dst[i] = src[i];
	}
	return dst;
}

template<class T>
T*TypeCopy(T*dst, T*src, size_t n){
	return __TypeCopy(dst, src,n, __Typetraits<T>::IsPodType());
}
void TestType(){
	int src[3] = { 1, 2, 3 };
	int dst[3] = { 0 };

	string src2[3] = { "11", "22" };
	string dst2[3] = { "0" };

	TypeCopy(src,dst,3);
	TypeCopy(src2, dst2,3);
}