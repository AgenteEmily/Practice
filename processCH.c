#include <stdio.h>
#include <stdlib.h>

struct PCBst
{
    int parent;
    int children;
    int isParent; // used to know if PCB is a parent
};

struct Children{
    int child;
};

int maxNumfProcesses = 0;
int parentProcess = 0;
struct PCBst *PCB;
struct Children *ChildList;

void printHirarchy(int currentIndex);

/**************************************************************/
// PROCEDURE TO PRINT HIERARCHY OF PROCESSES

void printLevelHirarchy()
{
    int i = 0;
    while (i < maxNumfProcesses)
    {
        if (PCB[i].isParent == 1) // check for current parent
        {
            printf("PCB[%d] is parent of: ", i); // i is the index(parent of the array)
            printHirarchy(i);
        }
        i++;
    }
}

void printHirarchy(int currentIndex)
{
    int i = 0;
    while (i < maxNumfProcesses)
    {
        if (PCB[i].parent == currentIndex && i != currentIndex)
        {
            printf("PCB[%d] ", i); // prints children which is the next index
        }
        i++;
    }
    printf("\n");
}

void parameters()
{

    printf("Enter maximum number of processes: ");
    scanf("%d", &maxNumfProcesses); // prompt for maximum number of processes

    PCB = (struct PCBst *)calloc(sizeof(struct PCBst), maxNumfProcesses);
    ChildList = (struct Children *)calloc(sizeof(struct Children), maxNumfProcesses);
    /*PCB[0].parent = 0;
    PCB[0].children = NULL;
    for (int i = 1; i < maxNumfProcesses; i++)
    {
        PCB[i].parent = -1;
       // PCB[i].children = -1;
        PCB[i].isParent = 0;
    } */

    for (int i = 1; i < maxNumfProcesses; i++)
    {
        PCB[i].parent = -1;
        //PCB[i].children = -1;
        PCB[i].isParent = 0;
        ChildList[i].child = -1;
    } 
}

void create()
{

    printf("Enter the parent process index: ");
    scanf("%d", &parentProcess);

    if (parentProcess < 0 || parentProcess >= maxNumfProcesses)
    {
        printf("Invalid parent index!\n");
        return;
    }
    
    int i = parentProcess;
    while (PCB[i].parent != -1 || i == parentProcess)
        i = (i + 1) % maxNumfProcesses; // store in i itself
        PCB[i].parent = parentProcess;
        PCB[parentProcess].isParent = 1;                // define that        su padre es ya su apdre
        ChildList[i].child = i++;           // nextIndex as a child


}

void destroyChild(int child) // delete the  child,
{
    if (PCB[child].parent != -1)
    {
        PCB[child].parent = -1;
        PCB[child].children = -1;
        PCB[child].isParent  = 0;
        ////return; //esta ya destruido
    }
   

}

void destroyParents(int parentIndex){
 
  int i = 0;

  while(i < maxNumfProcesses)
  {
        if (PCB[i].parent == parentIndex)
        {
            //printf("Result: %d", PCB[indexOf].children);
            //destroyProcesses(ChildList[i].child, indexOf);
           destroyChild(i); //destruye el hijo encontrado
           if(PCB[i].isParent == 1){
               destroyParents(i);
            }        
        }
        i++;
    }

}

/***************************************************************/
// void "PROCEDURE FOR OPTION #4"()
void destroy() // destroy(int loc, int ))
{
    int indexOf;
    printf("Enter the index of the process whose descendants are to be destroyed: ");
    scanf("%d", &indexOf);

    destroyParents(indexOf);
    
    destroyChild(indexOf); //it destroys from el padre at the end 
    free(PCB);
}

int menu()
{
    int selectOption;
    printf("Process creation and destruction\n");
    printf("--------------------------------\n");
    printf("1) Enter parameters\n"); /* prompt for menu selection */
    printf("2) Create a new child process\n");
    printf("3) Destroy all descendants of a process\n");
    printf("4) Quit program and free memory\n");
    scanf("%d", &selectOption);

    return selectOption;
}

/**************************************************************/
int main()
{
    int option;
    option = menu();

    while (option != 4)
    {
        switch (option)
        {
        case 1:
            parameters();
            break;
        case 2:
            create();
            printLevelHirarchy();
            break;
        case 3:
            destroy();
           /// printLevelHirarchy();
            break;
        default:
            printf("Invalid option! Try it again.\n");
            break;
        }
        option = menu();
    }
    printf("Exiting program.\n");
    return 0;
}