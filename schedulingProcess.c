#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int printingContents();

//the difference between the end time and the arrival time)
/* optional: define a function that finds the maximum of two integers */
/***************************************************************/
/////// void "PROCEDURE TO PRINT THE CONTENTS OF THE SCHEDULING TABLE"() {
struct Q{

	int id;
	int arrival; 
	int total_CPU;
	int start_time;
	int total_remaining; // the amount of CPU time remaining for a process to complete (used for SRT scheduling only)
	int end_time; //the time when the process has been completed by the CPU
	int turnaround_time; // the sum of the total CPU time and the waiting time (alternatively:
	int num_processes;
	int nextIndex;
	bool already_started;
	bool done;

};
	struct Q *Process;
	int maxProcesses;
#define max(a,b) (a > b ? a:b) 

int parameter(){

	printf("Enter total number of processes: ");
	scanf("%d", &maxProcesses);

	Process = (struct Q *)calloc(sizeof(struct Q), maxProcesses);
	//Process[0].arrival = -1; 

	for (int i = 0; i < maxProcesses; i++)
	{
		Process[i].arrival = -1;
		Process[i].id = -1;
		Process[i].total_CPU = -1;
	} 
	
	int i = 0;
	while(i < maxProcesses){
		Process->nextIndex = i+1;
		printf("Enter process id: ");
		scanf("%d", &Process[i].id);
		printf("Enter arrival cycle for process P[%d]: ", Process->nextIndex);
		scanf("%d", &Process[i].arrival);
		printf("Enter total cycles for process P[%d]: ", Process->nextIndex);
		scanf("%d", &Process[i].total_CPU);
		i++;
	}
    printf("\n");
	return 0;
}

int menu(){

	int option;
	printf("Batch Scheduling\n");
	printf("-----------------\n");
	printf("1) Enter parameters\n"); 
	printf("2) Schedule processes with FIFO algorithm\n");\
	printf("3) Schedule processes with SJF algorithm (non-preemptive)\n");
	printf("4) Schedule processes with SRT algorithm (preemptive version of SJF)\n");
    printf("5) Quit and free memory \n");
    printf("\n");

	printf("Enter selection: ");
	scanf("%d", &option);
	return option; 
} 

//////void "PROCEDURE FOR OPTION #1"() {
void FIFO(){ 
	
	int i = 0;
	int firstVal = Process[0].arrival;
	int endQueue = Process[0].total_CPU;
	while(i <= maxProcesses){
		if(i == 0 ) {
			Process[i].start_time = firstVal; 
			Process[i].end_time = endQueue;
		}
		if (i == 1) {  
			Process[i].start_time = firstVal + endQueue; 
			Process[i].end_time = endQueue + Process[i].total_CPU;
		}
		if(i > 1){  // adds the values of the previous indexes 
			Process[i].start_time = Process[i-1].total_CPU + Process[i-2].total_CPU;
			Process[i].end_time = Process[i-1].end_time + Process[i].total_CPU;
		}
		// sub: End - Arrival
			Process[i].turnaround_time = Process[i].end_time - Process[i].arrival;
		i++;
	}
}

int SJF(){ // 3
	
	int numDone = 0;
	int minIndex; 
	int currCycle = 0;
	int minCycles;
	int atLeastOne;

	int i;
	for(i = 0; i < maxProcesses; i++){      /* for each process, reset "done" field to 0 */
		Process[i].done = 0;        // flag
	}   /* for each process not yet scheduled */
		while(numDone < maxProcesses){
			minCycles = INT_MAX;          /* initilize the lowest total cycle time to INT_MAX (largest integervalue) */
			atLeastOne = 0;
			for(i = 0; i < maxProcesses; i++){      
				if (Process[i].done == 0 && Process[i].arrival <= currCycle) {
					//if(Process[i].total_CPU < Process[i+1].total_CPU){  /* check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update */
						minCycles = Process[i].total_CPU;
						minIndex = i;   // currect min
						atLeastOne = 1; //found minimum!
				}  
			}

			if(atLeastOne == 0){ // if it has not find the minimum, increase the currCycle
				currCycle++;
			}
			else{ 
				Process[minIndex].start_time = max(currCycle,Process[minIndex].arrival);    
				Process[minIndex].end_time = Process[minIndex].start_time + Process[minIndex].total_CPU;
				Process[minIndex].turnaround_time = Process[minIndex].end_time - Process[minIndex].arrival;
				Process[minIndex].done = 1;
				currCycle = Process[minIndex].end_time;
				numDone++;
			}  
		}
 
}

int SRF(){	// 4 

	int numDone = 0;
    int currCycle = 0;
    int minCycles;
    int atLeastOne;
    int minIndex;
    int i;

    for (i = 0; i < maxProcesses; i++) {
        Process[i].done = 0;
        Process[i].already_started = 0;
        Process[i].total_remaining = Process[i].total_CPU; // Initialize remaining time
    }

    while (numDone < maxProcesses) { /* while there are still processes to schedule */
        minCycles = INT_MAX;	
        atLeastOne = 0;
        minIndex = 0;

		/* for each process not yet scheduled */
        for (i = 0; i < maxProcesses; i++) {                                                          
            if (Process[i].arrival <= currCycle && Process[i].done == 0){ /* check if process has lower total remaining time than current lowest and has arrival time less than current cycle time*/
             	if(Process[i].total_remaining < minCycles){		// Finds the process with the shortest remaining time that at arrival time
                minCycles = Process[i].total_remaining;         // updating 
                minIndex = i;     // lowest index
                atLeastOne = 1; // At least one process is available to schedule
            	}
            }
        }

        // check if there is a process to schedule
        if (atLeastOne == 1) {                              
            if (!Process[minIndex].already_started) {
                Process[minIndex].start_time = currCycle;
                //printf("CurreCycle is: %d", currCycle);
                Process[minIndex].already_started = 1;
            }

            // Decrement the remaining time of the selected process
            Process[minIndex].total_remaining--;
            //printf("%d", Process[minIndex].total_remaining);
        
            // Check if the process is finished
            if (Process[minIndex].total_remaining == 0) {
                Process[minIndex].done = 1;
                Process[minIndex].end_time = currCycle + 1; // when cycle becomes zero indexed, add one for completion
                Process[minIndex].turnaround_time = Process[minIndex].end_time - Process[minIndex].arrival;
                numDone++;
            }
        }

        currCycle++; // Move to the next cycle
    }

	printingContents();
    return 0;



}

int printing(){
	printf("ID   Arrival    Total  Start   End  Turnaround\n");
	printf("----------------------------------------------\n");
	
	int i = 0;
	while(i < maxProcesses){
		printf("%d      	", Process[i].id);
		printf("%d         ", Process[i].arrival);
		printf("%d    	", Process[i].total_CPU); 
		printf("\n");
		i++;
	}
	return 0;
}

//int printingContents();
int printingContents(){

	printf("ID   Arrival    Total  Start   End  Turnaround\n");
	printf("----------------------------------------------\n");

	int i = 0;
	while(i < maxProcesses){
		printf("%d      	", Process[i].id);
		printf("%d         ", Process[i].arrival);
		printf("%d    	", Process[i].total_CPU); 
	
		printf("%d   	", Process[i].start_time);
		printf("%d    	", Process[i].end_time);
		printf("%d     ", Process[i].turnaround_time); 
		printf("\n");
		i++;
	}
	return 0;
}
/***************************************************************/

//int printingContents();
int main() {
/* declare local vars */
	int selection; // = menu();
	
	selection = menu();

	while(selection != 5){      /* while user has not chosen to quit */
		switch(selection)
		{
			case 1: 
				parameter();
				printing();
                printf("\n");
				break;
			case 2: 
				FIFO();
				printingContents();
                printf("\n");
				break;
			case 3:
				SJF();
				printingContents();
                printf("\n");
				break;
			case 4: 
				SRF();
				//printingContents();
                printf("\n");
                break;
			default:
                printf("Invalid option! Try it again.\n");
				break;
		}
	   selection = menu();
	}
	return 0;
} 