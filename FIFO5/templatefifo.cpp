#include "templatefifo.h"


template<class T>
Fifo<T>::Fifo()
{
}
template<class T>
Fifo<T>::Fifo(const Fifo&)
{
}
template<class T>
T Fifo<T>::Pop()
{
	T data;
	unique_lock<mutex> lock(bufferLock);
	buffer_not_empty.wait(lock,[this](){return (!buffer.empty());});
	data = buffer.front();
	buffer.pop();
	cout<<"Retrieving Data from Buffer: Pop()"<<endl;
	buffer_not_full.notify_one();
	return data;
}

template<class T>
T Fifo<T>::Pop_Try()
{
	T data;
	lock_guard<mutex> lock(bufferLock);
	if(buffer.empty())
	{
		cout<<"Buffer is Empty"<<endl;
		return 0;
	}
	
	cout<<"Retrieving Data from Buffer: Pop try"<<endl;
	data = buffer.front();
	buffer.pop();
	buffer_not_full.notify_one();
	return data;
}

template<class T>
void Fifo<T>::Push(T newData)
{
	unique_lock<mutex> lock(bufferLock);
	buffer_not_full.wait(lock,[this](){return(buffer.size()<MAXSIZE);});
	if(buffer.size() < MAXSIZE)
	{
		buffer.push(newData);
		cout<<"Number of Items in Buffer:"<< buffer.size()<<endl;
	}
	else{
	
			cout<<"Buffer is full"<<endl;
			return;
	}
	
	buffer_not_empty.notify_all();
}


