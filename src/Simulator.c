/********************************************************************************
*********************************************************************************
**  Created by Yiheng Gao, 2/20/2018                                           **
**                                                                             **
**  Combine memory, CPU to simulate a computer                                 **
**  Create two processes: one simulates memory, another one simulates CPU      **
**  Using pipe to communicate                                                  **
*********************************************************************************
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
	// Create pipe
	int rdpd[2];				// Read pipe descriptors, rdpd[0]: read - CPU, rdpd[1]: write - Memory
	int wtpd[2];				// Write pipe descriptors, wtpd[0]: read - Memory, wtpd[1]: write - CPU
	if(pipe(rdpd) == -1 || pipe(wtpd) == -1)  // Create pipe
	{
		printf("pipe() failed!\n");
		exit(1);
	} 
	
	// Create two process: CPU, Memory
	int pid = fork();
	switch(pid)
	{
		case -1:
			/* Here pid is -1, the fork failed */
			/* Some possible reasons are that you're */
			/* out of process slots or virtual memory */
			printf("The fork failed!");
			exit(-1);	

		case 0:	
			// pid == 0 is child
			MemoryInit();
			runMemory(rdpd[1], wtpd[0]);	// Param:(write pd, read pd)
			exit(0);
			
		default:
			// pid > 0 is Parent
			CPUInit();
			runCPU(wtpd[1], rdpd[0]);		// Param:(write pd, read pd)
			waitpid(pid, NULL, 0);			// Waiting for memory process exit
			exit(0);
	}
}