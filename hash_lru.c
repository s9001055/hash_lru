#include <stdio.h>
#include <stdlib.h>

#define char	int8_t
#define int 	int32_t
#define long	int64_t

#define nodeCount 5
#define intMax 2147483647
#define numOfEntry 10

typedef struct tableNode{
	int32_t id;
	struct tableNode *next;
	struct linkNode *link;
}tableNode;

typedef struct linkNode{
	int32_t data; //change to data
	struct linkNode *next;
}linkNode;

void victim();
void *insertNode();
void moveToMru();
void initTable();
int32_t hashFunt();
int32_t searchKey();
void insertKey();
void removeKey();

void *head = NULL; 
int32_t numOfNode = 0; 
struct tableNode table[numOfEntry];


void victim()
{
	struct linkNode *victNode = head;
	struct linkNode *prevNode;
	while (victNode -> next != NULL){
		prevNode = victNode;
		victNode = victNode -> next;
	}
	prevNode -> next = NULL;
	removeKey(victNode -> data);
	free(victNode);
	numOfNode--;
}

void* insertNode(int32_t data)
{
	if (numOfNode == nodeCount)
		victim();
	
	struct linkNode *newNode = malloc(sizeof(linkNode));
	newNode -> data = data;
	newNode -> next = head;
	head = newNode;
	numOfNode++;
	return (struct linkNode*)newNode;
}

void moveToMru(int32_t data)
{
	struct linkNode *keyNode = head;
	struct linkNode *prevNode = head;
	while (keyNode != NULL){
		if (keyNode -> data == data){
			prevNode -> next = keyNode -> next;
			keyNode -> next = head;
			head = keyNode;
		}
		prevNode = keyNode;
		keyNode = keyNode -> next;
	}
}


/************************************************************/
/*********************** hash table *************************/
/************************************************************/

void initTable(struct tableNode table[])
{
	int32_t i;
	for (i = 0; i < numOfEntry; i++){
		//table += i;
		table[i].id = intMax;
		table[i].next = NULL;
		table[i].link = NULL;
	}
}

int32_t hashFunt(int id)
{
	if (id < 0)
		id = -id;
	return id % numOfEntry;
}

int32_t searchKey(int32_t id)
{
	int32_t index = hashFunt(id);
	//table += index;
	if (table[index].id == id){
		moveToMru(table[index].link -> data);
		return table[index].link -> data;
	}
	else{
		struct tableNode *nextNode = table[index].next;
		while (nextNode != NULL){
			if (nextNode -> id == id){
				moveToMru(nextNode -> link -> data);
				return nextNode -> link -> data;
			}
			nextNode = nextNode -> next;
		}
	}

	insertKey(id);
	return 0;
}

void insertKey(int32_t id)
{
	int32_t index = hashFunt(id);
	//table += index;
	
	if (table[index].id == intMax){
		table[index].id = id;
		table[index].link = insertNode(id);
	}
	else{
		struct tableNode *nextNode;
		struct tableNode *newNode = malloc(sizeof(struct tableNode));

		nextNode = table[index].next;
		table[index].next = newNode;
		newNode -> id = id;
		newNode -> next = nextNode;
		newNode -> link = insertNode(id);
	}
}

void removeKey(int32_t id)
{
	int32_t index = hashFunt(id);
	if(table[index].id == id){
		table[index].id = intMax;
		table[index].link = NULL;
	}
	else{
		struct tableNode *currNode = table[index].next;
		struct tableNode *prevNode = &table[index];
		while (currNode != NULL){
			if (currNode -> id == id){
				prevNode -> next = currNode -> next;
				free(currNode);
				break;
			}
			prevNode = currNode;
			currNode = currNode -> next;
		}
	}
}











void testPrintLRU()
{
	struct linkNode *thisNode;
	
	thisNode = head;
	while (thisNode != NULL){
		printf("%d -> ",thisNode -> data);
		thisNode = thisNode -> next;
	}
	printf("NULL\n");
}

void printHashTable(struct tableNode table[])
{
	for (int i = 0; i < numOfEntry; i++){
		//table += (sizeof(struct tableNode) * i);
		//table += i;
		printf("entry %d \t %d", i, table[i].id);
		
		struct tableNode *nextLink;
		nextLink = table[i].next;
		while (nextLink != NULL){
			printf(" -> %d",nextLink -> id);
			nextLink = nextLink -> next;
		}
		printf(" -> NULL\n");
	}
	printf("\n");
}

int32_t main()
{
	initTable(table);
	int32_t input;
	while(1){
		printf("input your id\n");
		scanf("%d",&input);
		searchKey(input);
		testPrintLRU();
		printHashTable(table);	
	}


	return 0;
}
