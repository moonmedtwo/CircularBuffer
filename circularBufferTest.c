#include "circularBuffer.h"

int main(void)
{
	circular_buffer_t Buffer;
	InitializeBuffer(&Buffer, 10);

	PrintBufferElements(&Buffer);
	for(int i = 0; i < 5; i++)
	{
		Push(i % 10,&Buffer);
	}
	for(int i = 0; i < 6; i++)
	{
		Pop(&Buffer);
	}

	DestroyBuffer(&Buffer);
	return 0;
}

