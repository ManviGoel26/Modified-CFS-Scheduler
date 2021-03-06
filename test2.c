#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

void Testfunction()
{
	struct timespec start, finish; 
	clock_gettime(CLOCK_REALTIME, &start); 
	
	printf("Computation started\n");
	
	int i, j; 
	
	for (i = 0, j = 0; i < 10000000; i++) 
	{ 
		j += i*i; 
	} 

	printf("Computation finished\n");
	
	clock_gettime(CLOCK_REALTIME, &finish); 

	long seconds = finish.tv_sec - start.tv_sec; 
	long ns = finish.tv_nsec - start.tv_nsec; 

	if (start.tv_nsec > finish.tv_nsec) 
	{ 
		--seconds; 
		ns += 1000000000; 
	} 
	printf("Seconds without ns: %ld\n", seconds); 
	printf("nanoseconds: %ld\n", ns); 
	printf("Total seconds: %e\n", (double)seconds + (double)ns/(double)1000000000); 
}

int main(int argc, char** argv)
{ 
 	// Without real time requirements
	printf("-----Starting Testfunction() without real-time requirements-----\n");
	int pid = getpid();
	Testfunction();
	printf("-----Completed Testfunction()-----\n");
	

	unsigned long timeslice = 2000000;
	int pid1 = getpid();
	
	if (pid != pid1)
	{
		return 0;
	}
	
	printf("-----Starting Testfunction() with real-time requirements-----\n");
	int pid2 = getpid();
	printf("PID of this task = %d\n", pid2);
	long int status = syscall(440, pid2, timeslice); // Setting the real time requirements via the system call.
	
	// Process with real time requirements
	if(status == 0) 
	{
		Testfunction();
		printf("-----Completed Testfunction()-----\n");
	}
	else 
	{
		printf("System call rtnice did not execute as expected\n");
		printf("Error No.: %d\n", errno);
	}

	return 0;
}
