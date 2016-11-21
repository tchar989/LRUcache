//Implements LRU cache
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	struct Node *last, *next;
	char* fileName;
	char* fileContents;
} Node;

typedef struct Queue{
	Node *first, *last;
	int size;
	int currentNum;
} Queue;

Node* createNode(char* fileName, char* fileContents);
Queue* queueInit(int size);
int isQueueEmpty(Queue *queue);
int isQueueFull(Queue *queue);
void deQueue(Queue *queue);
void enQueue(Queue *queue, char* fileName, char* fileContents);
Node* isInQueue(Queue *queue, char* fileName);


Node* createNode(char* fileName, char* fileContents)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->fileName = fileName;
	newNode->fileContents = fileContents;
	newNode->last = newNode->next = NULL;
	return newNode;
}


Queue* queueInit(int size)
{
	Queue *newQueue = (Queue *)malloc(sizeof(Queue));
	newQueue->size = size;
	newQueue->currentNum = 0;
	newQueue->first = newQueue->last = NULL;
	return newQueue;
}

int isQueueEmpty(Queue *queue)
{
	if(queue->currentNum == 0)
		return 1;
	else
		return 0;
}

int isQueueFull(Queue *queue)
{
	if(queue->currentNum == queue->size)
		return 1;
	else
		return 0;
}

void deQueue(Queue *queue)
{
	printf("Dequeuing...\n");
	Node *temp = queue->last;
	queue->last->last->next = NULL;
	queue->last = queue->last->last;
	queue->currentNum -= 1;
	free(temp);
}


void enQueue(Queue *queue, char* fileName, char* fileContents)
{
	if(isQueueFull(queue))
	{
		deQueue(queue);
	}
	Node *newNode = createNode(fileName, fileContents);
	Node *temp = queue->first;
	if(temp == NULL)
	{
		queue->first = newNode;
		queue->last = newNode;
	}
	else
	{
		temp->last = newNode;
		newNode->next = queue->first;
		queue->first->last = newNode;
		queue->first = newNode;
	}
	queue->currentNum += 1;
}

Node* isInQueue(Queue *queue, char* fileName)
{
	Node *temp = queue->first;
	while(temp != NULL)
	{
		if(strcmp(temp->fileName,fileName)==0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

int main(int argc, char** argv)
{
	Queue *queue = queueInit(3);
	enQueue(queue, "1", "firstOne");
	enQueue(queue, "2", "secondOne");
	enQueue(queue, "3", "thirdOne");
	enQueue(queue, "4", "fourthOne");
	Node *temp = isInQueue(queue, "3");
	if(temp == NULL)
	{
		printf("uh oh, couldn't find the node!");
		return 1;
	}
	printf("Found node: %s\n", temp->fileName);
	return 0;
}


