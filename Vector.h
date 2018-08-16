#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

//顺序表的两大缺点 增容 
// 头上  尾上 中间的插入 时间复杂度为O(n)
//优点是 随机访问
typedef int DataType;
class Vector
{
public:
	Vector()
		: _start(NULL)
		, _finish(NULL)
		, _endofstorage(NULL)
	{}
	Vector(const Vector& v)
	{
		_start = new DataType[v.Size()];
		memcpy(_start, v._start, sizeof(DataType)*v.Size());
		_finish = _start + v.Size();
		_endofstorage = _start + v.Size();
	}
	//v1=v2
	Vector& operator=(Vector v)
	{
		//swap(_start, v._start);
		//swap(_finish, v._finish);
		//swap(_endofstorage, v._endofstorage);
		Swap(v);
		return *this;

	}
		~Vector()
	   { 
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = NULL;
			}

		}
		void Swap(Vector& v){
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endofstorage, v._endofstorage);
		}

		size_t Size() const
		{
			return _finish - _start;
		}
		size_t Capacity() const
		{
			return  _endofstorage - _start;
		}
		void Reserve(size_t n)
		{
			Expand(n);
		}
		void Resize(size_t n,DataType value=DataType()){
			if (n < Size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n>Capacity()){
					Expand(n);
				}
				for (size_t i = Size(); i < n; ++i)
				{
					_start[i] = value;
				}
			}
		}
		void PushBack(DataType x)  //效率最高
		{
			if (_finish ==_endofstorage)
			{
				size_t  newcapacity = Capacity() == 0 ? 3 : Capacity() * 2;
				Expand(newcapacity);
			}
			*_finish = x;
			++_finish;
		}
		DataType& operator[](size_t pos){
			assert(pos<Size());
			return _start[pos];
		}

private:
	void Expand(size_t n)
	{
		if (n > Capacity()){
			size_t size = Size();
		
			DataType* tmp = new DataType[n];
			if (_start){
				memcpy(tmp, _start, sizeof(DataType)*size);
				delete[] _start;
			}
			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_endofstorage = _start + n;
		}
	}
	void PopBack();
	void Insert();
private:
	//DataType* _a;
	//size_t _size;
	//size_t _capacity;
	DataType* _start;
	DataType* _finish;
	DataType* _endofstorage;
};


void test(){
	Vector v1;
	v1.PushBack(1);
	v1.PushBack(2);

	for (size_t i = 0; i < v1.Size(); ++i){
		cout << v1[i] << " ";
	}
	cout << endl;
}