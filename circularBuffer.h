#include <stdbool.h>

typedef struct {
	bool bIsFull;
	int iHead;
	int iTail;
	int iCapacity;
	int * piData;
} circular_buffer_t;

extern void InitializeBuffer(circular_buffer_t * pBuffer,int iBufferCapacity);
extern void DestroyBuffer(circular_buffer_t * pBuffer);
extern void Push(int value, circular_buffer_t * pBuffer);
extern int  Pop(circular_buffer_t * pBuffer);

// Debug purpose
extern void PrintBufferElements(circular_buffer_t * pBuffer);
