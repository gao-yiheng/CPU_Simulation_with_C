/********************************************************************************
*********************************************************************************
**  Created by Yiheng Gao, 2/20/2018                                           **
**                                                                             **
**  Simulate Memory: read, write data                                          **
**  Function:                                                                  **
**    - External:                                                              **
**       void MemoryInit();               // Initial data in Memory            **
**       void runMemory(int, int);        // Simulate Memory                   **
**    - Internal:                                                              **
**       void loadMemoryTest();           // Get the data for the whole memory **
**                                        // help debug                        **
*********************************************************************************
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// Function declare
void MemoryInit(void);
void runMemory(int wtpd, int rdpd);
static void loadMemoryTest();


#define MEMORY_SIZE 2000       // Total size of memory
#define LINE_BUFFER_SIZE 100   // Max size for each line in a specific file


// Memory space
// 0-999: user program, 1000-1999: system area
int memory[MEMORY_SIZE];	


/****************************************************************
* Func:   Initialize Memory, Load data into memory              *
* Param:  none                                                  *
* Return: none                                                  *
*****************************************************************/
void MemoryInit( )
{
	// Load a program into memory
	int offset = 0;

	printf("Input file name\n");
	char fileName[20];	
	scanf("%s", fileName);       // Get file name from user
	while(getchar() != '\n');    // Clear rest buffer in stdin
	
	FILE *fp = fopen(fileName, "r");
	while(fp == NULL)			// Make sure the file open correctly.
	{
		printf("Error! File does not exist\nInput file name again!\n");
		scanf("%s", fileName);
		while(getchar() != '\n');
		fp = fopen(fileName, "r");
	}

	while(!feof(fp))	// Load the whole file into memory, end until EOF appears
	{
		char buff[LINE_BUFFER_SIZE] = "";
		fgets(buff, sizeof(buff), fp);         // Read line into buffer
		// Data line
		if(buff[0] >= '0' && buff[0] <= '9')
			memory[offset++] = atoi(buff);	   // Transfer char into instruction & store
		else if(buff[0] == '.')
			offset = atoi(&buff[1]);
	}

	// Test the content of memory
	//loadMemoryTest();
}

/****************************************************************
* Func:   Read/Write memory according to control signal         *
* Param:  int wtpd: write pipe description                      *
*         int rdpd: read pipe description                       *
* Return: none                                                  *
*                                                               *
* Step1: Read control signal -> 'r', 'w', 'E'                   *
* Step2: Read address                                           *
* Step3: Store/Send data                                        *
*****************************************************************/
void runMemory(int wtpd, int rdpd)
{
	char command;        // 'r': read from memory; 'w': write into memory; 'E': end process
	int address, data;
	
	// read command from pipe
	read(rdpd, &command, sizeof(command));
	
	while(command != 'E')
	{
		switch(command)
		{
			// Read instruction/data from memory
			case 'r':
				read(rdpd, &address, sizeof(address));                   // Read PC from pipe
				write(wtpd, &memory[address], sizeof(memory[address]));  // Write the content of address into pipe
				break;
			
			// Write data into memory
			case 'w':
				read(rdpd, &address, sizeof(address));   // Read address from pipe
				read(rdpd, &data, sizeof(address));		 // Read the data that processor want to save from pipe
				memory[address] = data;						
				break;
				
			default:
				printf("Unexpected command: %c\n", command);
				exit(-1);
				break;
		}
		read(rdpd, &command, sizeof(command));				// Read next command from CPU
	}
}


/****************************************************************
* Func:   Test if memory load correctly                         *
*         Output the value of mem[i]                            *
* Param:  none                                                  *
* Return: none                                                  *
*****************************************************************/
void loadMemoryTest(){
	printf(" Test Memory Now: \n");
	int offset = 0;
	printf("size of Memory is: %d\n", sizeof(memory)/sizeof(int));
	while(offset < sizeof(memory)/sizeof(int))
		printf("%d, %d\n", offset++, memory[offset]);
}
