#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	bool bIsFull;
	int iHead;
	int iTail;
	int iCapacity;
	int * piData;
} circular_buffer_t;

typedef enum {
	ACTION_POP,
	ACTION_PUSH,
	
	TOTAL_ACTION,
} eCircularBufferAction;

void InitializeBuffer(circular_buffer_t * pBuffer,int iBufferCapacity);
void DestroyBuffer(circular_buffer_t * pBuffer);
void Push(int value, circular_buffer_t * pBuffer);
int  Pop(circular_buffer_t * pBuffer);
void UpdateBufferStateBasedOnAction(eCircularBufferAction action, circular_buffer_t *pBuffer);

// Debug purpose
void PrintBufferElements(circular_buffer_t * pBuffer);

void InitializeBuffer(circular_buffer_t *pBuffer, int iBufferCapacity)
{
	pBuffer->bIsFull = false;
	pBuffer->iCapacity = iBufferCapacity;
	pBuffer->piData = (int*)calloc(pBuffer->iCapacity, sizeof(int));
	pBuffer->iHead = 0;
	pBuffer->iTail = 0;
}

void DestroyBuffer(circular_buffer_t * pBuffer)
{
	free(pBuffer->piData);
}

bool IsBufferFull(circular_buffer_t * pBuffer)
{
	return pBuffer->bIsFull;
}

bool IsBufferEmpty(circular_buffer_t * pBuffer)
{
	if(IsBufferFull(pBuffer) == false)
	{
		return pBuffer->iHead == pBuffer->iTail;
	}
	return false;
}

void Push(int value, circular_buffer_t * pBuffer)
{
	if(IsBufferFull(pBuffer))
	{
		printf("Try to add %d to a full buffer and failed\r\n", value);
		return;
	}

	int * piData = pBuffer->piData;
	piData[pBuffer->iTail] = value;
	UpdateBufferStateBasedOnAction(ACTION_PUSH, pBuffer);

	printf("Added %d to buffer\r\n", value);
	PrintBufferElements(pBuffer);
}

int Pop(circular_buffer_t *pBuffer)
{
	if(IsBufferEmpty(pBuffer))
	{
		printf("Try to pop from an empty buffer and failed\r\n");
		return 0;
	}

	int *piData = pBuffer->piData;
	int iRet = piData[pBuffer->iHead];
	UpdateBufferStateBasedOnAction(ACTION_POP, pBuffer);

	printf("Pop %d from buffer\r\n", iRet);
	PrintBufferElements(pBuffer);
	return iRet;
}

void UpdateBufferStateBasedOnAction(eCircularBufferAction action, circular_buffer_t *pBuffer)
{
	switch(action)
	{
		case ACTION_POP:
			pBuffer->piData[pBuffer->iHead] = 0;
		 	pBuffer->bIsFull = false;
			pBuffer->iHead = (pBuffer->iHead + 1) % pBuffer->iCapacity;
			break;
		case ACTION_PUSH:
			pBuffer->iTail = (pBuffer->iTail + 1) % pBuffer->iCapacity;
			pBuffer->bIsFull = (pBuffer->iTail == pBuffer->iHead);
			break;
		default:
			break;
	}
}

// Debug-purpose
void PrintHeadTail(circular_buffer_t * pBuffer)
{
	printf("Head-Tail-Both ---");
	if(pBuffer->iHead == pBuffer->iTail)
	{
		for(int i = 0; i < pBuffer->iCapacity; i++)
		{
			if(i == pBuffer->iHead) 
			{
				printf(" B ");
			}
			else
			{
				printf("   ");
			}
		}	
	}
	else
	{
		for(int i = 0; i < pBuffer->iCapacity; i++) {
			if(i == pBuffer->iHead)
			{
				printf(" H ");
			}
			else if(i == pBuffer->iTail)
			{
				printf(" T ");
			}
			else
			{
				printf("   ");
			}
		}
	}
	printf("\r\n");
}

void PrintBufferElements(circular_buffer_t * pBuffer)
{
	PrintHeadTail(pBuffer);
	printf("Buffer Data ------");
	int * piData = pBuffer->piData;
	int nodesLeft = pBuffer->iCapacity;
	while(nodesLeft--)
	{
		printf(" %d ",*piData);
		piData++;
	}
	printf("\r\n");
}
