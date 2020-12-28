# Modified-CFS-Scheduler
Modified CFS Scheduler to prioritize processes with soft real-time requirements.

## Usage
1. To patch the diff file to a linux kernel, then enter the kernel directory and run the command: `patch -p1 -R < diff.txt`.
2. Compile and install the kernel.
3. To run the test.c file run `gcc -o test test2.c` and `./test` which prints the time taken by the same process with and without the real-time requirements.

4. To set the real-time requirements use the system call number *440* named rtnice using `syscall(440, pid, timeslice)` in the c program with *pid* as the PID of the process and *timeslice* as the real-time requirements.


## Assignment Details
Course Project for Operating Systems (CSE231) 
Instructor : Dr. Arani Bhattacharya

This assignment is based on modifying the CFS Scheduler based on soft real-time requirements. This task requires adding soft real time requirements to a process. So, for each call to the scheduler it needs to check if the real-time guarantees of the process with soft real-time requirements are being met and also giving higher priority to the soft-realtime requirement of a process as compared to the vruntime that is normally considered. 

**Skills Used** : C Programming Language, Linux
