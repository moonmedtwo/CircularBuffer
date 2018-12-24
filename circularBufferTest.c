#include <stdio.h>

#include "circularBuffer.h"

#define ESCAPE_CHARACTER (0x1B)

circular_buffer_t Buffer;

int GetUserInput_Interger(void);
char GetUserInput_Char(void);
void InitializeBufferFromUserInput(void);

int main(void)
{
	setbuf(stdout, NULL);
	printf("Circular buffer demo\r\n");

	char cUserInput = 0;
	while(cUserInput != 'E' &&   cUserInput != 'e')
	{

		if(Buffer.piData == 0)
		{
			InitializeBufferFromUserInput();
			continue;
		}

		printf("Do what: [I]nsert / [P]op / [E]scape \n");
		cUserInput = GetUserInput_Char();
		switch(cUserInput)
		{
		case 'I':
		case 'i':
		{
			printf("Enter value to insert: \r\n");
			int iInput = GetUserInput_Interger();
			Push(iInput, &Buffer);
		}
			break;
		case 'p':
		case 'P':
		{
			Pop(&Buffer);
		}
			break;
		default:
			printf("You entered \"%c\"\r\n", (int)cUserInput);
			break;
		}
	}


	if(Buffer.piData)
	{
		DestroyBuffer(&Buffer);
	}
	printf("Exiting \r\n");
	return 0;
}


int GetUserInput_Interger(void)
{
	char line[100];         /* a line to be read from the terminal */
	int answer;             /* an integer chosen by the user */
	fgets (line, sizeof(line), stdin);      /* read in a line */
	sscanf (line, "%d", &answer);           /* scan for the integer */
	return answer;
}

char GetUserInput_Char(void)
{
	char line[100];
	char answer;
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%c", &answer);
	return answer;
}

void InitializeBufferFromUserInput(void)
{
	printf("Enter the capacity of the buffer: ");
	int iCapacity = GetUserInput_Interger();
	if( iCapacity <= 0 )
	{
		printf("Invalid parameter! \r\n");
	}
	else
	{
		InitializeBuffer(&Buffer, iCapacity);
		printf("Created circular buffer with %d elements\r\n", iCapacity);
	}
}
