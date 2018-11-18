#include <stdio.h>
#include <string.h>
#include "queue.h"

#define OK		0
#define ERR 	1

int Task_dequeue( TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node)
{
	TskNodePtr tempPtr;

	node->task_num = (*headPtr)->task_num;		//we take first node because of FIFO
	node->value = (*headPtr)->value;

	tempPtr = *headPtr;							//taking node is took out from queue
	*headPtr = ( *headPtr ) -> next;

	if (*headPtr == NULL){						//if queue is empty
		*tailPtr = NULL;
	}

	free(tempPtr);
	return 0;
}

void Task_enqueue(TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node)
{
	TskNodePtr newPtr;

	newPtr = malloc(sizeof(Tsk_node_s));		//create new ptr for task

	if(newPtr != NULL){				//if malloc is successful
		newPtr->value = node->value;		//my task data assingning...
		newPtr->task_num = node->task_num;
		newPtr->next = NULL;			//nextPtr is not certain yet.

		printf("Enqueue newPtr->task_num = %d , Enqueue newPtr->value = %s\n",newPtr->task_num,newPtr->value);

		if(*headPtr == NULL){			//control whether first node is exist
			*headPtr = newPtr;			//this is head of queue
		}
		else {
			(*tailPtr)->next = newPtr;		//this is not first, it should connect to tail
		}

		*tailPtr = newPtr;	//our node should be tail
	}
	else {
		printf("%s not inserted.No memory available.\n", node->value );	//malloc is unsuccessful
	}

}

void Task_queue(char* command_string){
	//normalde global şimdilik local tanımlıyoruz.
	int history_count=0;

	task_node.task_num = history_count++;
	//strcpy(task_node.value ,command_string);

	Task_enqueue(&headPtr,&tailPtr,&task_node);


	while(headPtr!=NULL){			//taking task nodes with dequeue from queue
		Task_dequeue(&headPtr,&tailPtr,&task_node);
		printf("\n[%d] %s",task_node.task_num,task_node.value);
	}

}
