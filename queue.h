#include <stdio.h>
#include <stdlib.h>


/* Struct for task nodes */
struct tsk_node_s {
	int task_num; //starting from 0
	char* value;
	struct tsk_node_s* next;
};

typedef struct tsk_node_s Tsk_node_s;
typedef Tsk_node_s *TskNodePtr;

TskNodePtr headPtr = NULL;
TskNodePtr tailPtr = NULL;
Tsk_node_s task_node;

/* Task queue functions */
void Task_queue(char* command_string); //generate n random tasks for the task queue
void Task_enqueue(TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node); //insert a new task into task queue
int Task_dequeue(TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node); //take a task from task queue
