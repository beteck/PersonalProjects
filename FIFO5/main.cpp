#include "templatefifo.h"
#include "templatefifo.cpp"


int main()
{
	Fifo<int> fifoBuffer;
	
	thread readThread;
	thread writeThread;
	thread readThread2;
	
	while(1<10)
	{
	readThread = thread(&Fifo<int>::Pop,&fifoBuffer);
	writeThread = thread(&Fifo<int>::Push,&fifoBuffer,9);
	readThread2 = thread(&Fifo<int>::Pop_Try,&fifoBuffer);
	//i++;
	readThread.join();
	readThread2.join();
	writeThread.join();
	}
	cout<<"Main thread"<<endl;
	
	
	
	return 0;
}
