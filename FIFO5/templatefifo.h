#ifndef _TEMPLATEFIFO_H_
#define _TEMPLATEFIFO_H_
#include <iostream>
#include <thread>
#include <mutex>
#include<condition_variable>
#include <queue> 

using namespace std;

const int MAXSIZE = 6;

template<class T>
class Fifo
{
	private:
	//T buffer[MAXSIZE];
	queue<T> buffer;
	
	mutex bufferLock;
	condition_variable buffer_not_full;
	condition_variable buffer_not_empty;
	public:
	Fifo();
	Fifo(const Fifo&);
	T Pop();
	T Pop_Try();
	void Push(T newdata);
	
};

#endif
