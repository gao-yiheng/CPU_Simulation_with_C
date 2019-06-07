# CPU Simulation

This project is simulate a simple computer system consisting of a CPU and Memory. The CPU and Memory are simulated by separate processes that communicate. Memory contains one program that the CPU will execute and then the simulation will end.


For CPU:

- It will have these registers:  PC, SP, IR, AC, X, Y.
- It will support the instructions shown below.
- It will run the user program at address 0.
- Instructions are fetched into the IR from memory. The operand can be fetched into a local variable.
- Each instruction should be executed before the next instruction is fetched.
- The user stack resides at the end of user memory and grows down toward address 0.
- The system stack resides at the end of system memory and grows down toward address 0.
- There is no hardware enforcement of stack size.
- The program ends when the End instruction is executed. The 2 processes should end at that time.
- The user program cannot access system memory (exits with error message).

For Memory:
- It will consist of 2000 integer entries, 0-999 for the user program, 1000-1999 for system code.
- It will support two operations:
       read(address) - returns the value at the address; 
       write(address, data) - writes the data to the address  
- Memory will initialize itself by reading a program file.

For Timer:
- A timer will interrupt the processor after every X instructions, where X is a command-line parameter.

For Interrupt Processing:
- There are two forms of interrupts:  the timer and a system call using the int instruction.
- In both cases the CPU should enter kernel mode.
- The stack pointer should be switched to the system stack.
- SP and PC registers should be saved on the system stack. (The handler may save additional registers). 
- A timer interrupt should cause execution at address 1000.
- The int instruction should cause execution at address 1500.
- Interrupts should be disabled during interrupt processing to avoid nested execution.
- The iret instruction returns from an interrupt.
     
Instruction Set:

--> 1 = Load value                  # Load the value into the AC

--> 2 = Load addr                   # Load the value at the address into the AC
    
--> 3 = LoadInd addr                # Load the value from the address found in the given address into the AC. (for example, if LoadInd 500, and 500 contains 100, then load from 100).   
                                    
--> 4 = LoadIdxX addr               # Load the value at (address+X) into the AC. (for example, if LoadIdxX 500, and X contains 10, then load from 510).
                                    
--> 5 = LoadIdxY addr               # Load the value at (address+Y) into the AC
    
--> 6 = LoadSpX                     # Load from (Sp+X) into the AC (if SP is 990, and X is 1, load from 991).
    
--> 7 = Store addr                  # Store the value in the AC into the address
    
--> 8 = Get                         # Gets a random int from 1 to 100 into the AC
    
--> 9 = Put port                    # If port=1, writes AC as an int to the screen; If port=2, writes AC as a char to the screen
                                    
--> 10 = AddX                        # Add the value in X to the AC
   
--> 11 = AddY                        # Add the value in Y to the AC
   
--> 12 = SubX                        # Subtract the value in X from the AC
   
--> 13 = SubY                        # Subtract the value in Y from the AC
   
--> 14 = CopyToX                     # Copy the value in the AC to X
   
--> 15 = CopyFromX                   # Copy the value in X to the AC
   
--> 16 = CopyToY                     # Copy the value in the AC to Y
   
--> 17 = CopyFromY                   # Copy the value in Y to the AC
   
--> 18 = CopyToSp                    # Copy the value in AC to the SP
   
--> 19 = CopyFromSp                  # Copy the value in SP to the AC
   
--> 20 = Jump addr                   # Jump to the address
   
--> 21 = JumpIfEqual addr            # Jump to the address only if the value in the AC is zero
   
--> 22 = JumpIfNotEqual addr         # Jump to the address only if the value in the AC is not zero
   
--> 23 = Call addr                   # Push return address onto stack, jump to the address
   
--> 24 = Ret                         # Pop return address from the stack, jump to the address
   
--> 25 = IncX                        # Increment the value in X
   
--> 26 = DecX                        # Decrement the value in X
   
--> 27 = Push                        # Push AC onto stack
   
--> 28 = Pop                         # Pop from stack into AC
   
--> 29 = Int                         # Perform system call
   
--> 30 = IRet                        # Return from system call
   
--> 50 = End	                       # End execution

===============================================================================

sample folder contains 5 sample file. 

sample1.txt 
- Tests the indexed load instructions.
- Prints two tables, one of A-Z, the other of 1-10.

sample2.txt
- Tests the call/ret instructions.
- Prints a face where the lines are printed using subroutine calls.

sample3.txt 
- Tests the int/iret instructions.
- The main loop is printing the letter A followed by a number that is being periodically incremented by the timer.
- The number will increment faster if the timer period is shorter.

sample4.txt
- Tests the proper operation of the user stack and system stack, and also tests that accessing system memory in user mode gives an error and exits.

sample5.txt
- This is one you should create.  Be sure to include comments so the grader knows what the program is doing.
   
   
===============================================================================

Step for compiling and executing the project:
- S1: Copy the source files into Linux system.
- S2: Change the direct to source files
- S3: Run the following command: gcc Memory.c CPU.c Simulator.c
- S4: Run the program: ./a.out
- S5: According to output info, input the timer parameter X, file name that you want to run respectively. Each item ends with "Enter".
    eg: 10 (\n)
        sample2.txt
- S6: Repeat S4 for the remaining sample test files to get the various outputs 
