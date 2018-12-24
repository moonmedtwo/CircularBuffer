#include <stdio.h>
#include <stdbool.h>

#include "circularBuffer.h"

circular_buffer_t Buffer
;
#define PARSING_DEFAULT							0
#define PARSING_HASHMAP							1

#define ESCAPE_CHARACTER_PARSING_METHOD 		PARSING_HASHMAP

#if (ESCAPE_CHARACTER_PARSING_METHOD == PARSING_DEFAULT)
char cEscapeLetters[] = {'E','e'};
#elif (ESCAPE_CHARACTER_PARSING_METHOD == PARSING_HASHMAP)
bool bEscapeLetters[] = { 	false, // A, a
							false, // B, b
							false, // C, c
							false, // D, d
							true, // E, e
							false, // F, f
							false, // G, g
							false, // H, h
							false, // I, i
							false, // J, j
							false, // K, k
							false, // L, l
							false, // M, m
							false, // N, n
							false, // O, o
							false, // P, p
							false, // Q, q
							false, // R, r
							false, // S, s
							false, // T, t
							false, // U, u
							false, // V, v
							false, // X, x
							false, // Y, y
							false, // Z, z
};
#else
#error("No parsing method for escape character");
#endif

int GetUserInput_Interger(void);
char GetUserInput_Char(void);
void InitializeBufferFromUserInput(void);
bool UserWantsToExit(char cInput);
bool IsBufferInitialized(void);

int main(void)
{
	setbuf(stdout, NULL);
	printf("Circular buffer demo\r\n");

	char cUserInput = 0;
	while( !UserWantsToExit(cUserInput) )
	{
		if(IsBufferInitialized() == false)
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

bool UserWantsToExit(char cInput)
{
#if (ESCAPE_CHARACTER_PARSING_METHOD == PARSING_DEFAULT)
	char * pcEscapeLetter = cEscapeLetters;
	while(*pcEscapeLetter != 0)
	{
		if(*pcEscapeLetter == cInput)
		{
			return true;
		}
		pcEscapeLetter++;
	}
#elif (ESCAPE_CHARACTER_PARSING_METHOD == PARSING_HASHMAP)
	if(cInput >= 'a' && cInput <= 'z')
	{
		return bEscapeLetters[cInput - 'a'];
	}
	else if(cInput >= 'A' && cInput <= 'Z')
	{
		return bEscapeLetters[cInput - 'A'];
	}
#endif
	return false;
}

bool IsBufferInitialized(void)
{
	return Buffer.piData != 0;
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
