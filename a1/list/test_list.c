// Sample test routine for the list module.
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <stdlib.h>


/*
 * Main()
 */
int main(int argc, char** argv)
{
	printf("Starting tests...\n");

	// //////////////////////// insert only 1 head //////////////////////////////

	// struct nodeStruct *insert1 = NULL;

	// assert(List_countNodes(insert1) == 0);

	// struct nodeStruct *theOne;

	// theOne = List_createNode(69420);
	// List_insertHead(&insert1,theOne);
	// assert(List_countNodes(insert1) == 1);
	// assert(List_findNode(insert1, 69420) != NULL);
	// assert((insert1->item) == 69420);

	// // delete one and only node

	// List_deleteNode(&insert1,theOne);
	// assert(List_countNodes(insert1) == 0);
	// assert(List_findNode(insert1, 69420) == NULL);
	// assert((insert1) == NULL);


	// //////////////////////// insert only 1 tail ////////////////////////////////

	// struct nodeStruct *insertONE = NULL;

	// assert(List_countNodes(insertONE) == 0);

	// struct nodeStruct *spicyOne;
	// spicyOne = List_createNode(21);
	// List_insertTail(&insertONE,spicyOne);
	// assert(List_countNodes(spicyOne) == 1);
	// assert(List_findNode(insertONE, 21) != NULL);
	// assert((insertONE->item) == 21);

	// // delete one and only node 

	// List_deleteNode(&insertONE,spicyOne);
	// assert(List_countNodes(insertONE) == 0);
	// assert(List_findNode(insertONE, 21) == NULL);
	// assert((insertONE) == NULL);


	//////////////////////////// insert head only test ////////////////////////////

	// struct nodeStruct *testingList = NULL;

	// assert(List_countNodes(testingList) == 0);

	// int i = 0;
	// struct nodeStruct *node;
	// for (i = 0; i < 500;i++)
	// {
	// 	node = List_createNode(i);
	// 	List_insertHead(&testingList,node);
	// 	assert(List_countNodes(testingList) == i+1); //number of nodes
	// 	assert(List_findNode(testingList,i)); //if the node has been inserted correctly
	// 	assert((testingList->item) == i); //checking if head is the node that has been inserted 
	// }

	// delete node at tail

	// struct nodeStruct *found;
	// found = List_findNode(testingList,0);
	// List_deleteNode(&testingList,found);
	// assert((testingList->item) == i-1);
	// assert(List_countNodes(testingList) == i-1);
	// assert(List_findNode(testingList,0) == NULL);

	// delete node at head

	// found = List_findNode(testingList,499);
	// List_deleteNode(&testingList,found);
	// printf("%d\n", List_countNodes(testingList));
	// printf("%d\n", testingList->item);
	// assert(List_findNode(testingList,499) == NULL); 
	// assert(List_countNodes(testingList) == i-1); 
	// assert((testingList->item) == 498); 


	// delete node in the middle

	// found = List_findNode(testingList,256);
	// List_deleteNode(&testingList,found);
	// assert((testingList->item) == 499);
	// assert(List_countNodes(testingList) == i-1);
	// assert(List_findNode(testingList,256) == NULL);
	// List_sort(&testingList);

	// int j = 0;
	// struct nodeStruct *tmp;
	// tmp = testingList;
	// while(tmp)
	// {
	// 	printf("%d\n", tmp->item);
	// 	tmp = tmp->next;
	// 	j++;
	// }

	////////////////////////// insert tail only test ///////////////////////////////

	// struct nodeStruct *testingTail = NULL;

	// assert(List_countNodes(testingTail) == 0);

	// int j = 0;
	// int saved = 0;
	// struct nodeStruct *tailnode;
	// for (j = 0; j < 500; j++)
	// {
	// 	tailnode = List_createNode(j);
	// 	List_insertTail(&testingTail,tailnode);
	// 	assert(List_countNodes(testingTail) == j+1);
	// 	assert(List_findNode(testingTail,j));
	// 	saved = testingTail->item;
	// 	assert((saved) == 0);
	// }


	//////////////////////// insert head and then tail test //////////////////////////


	//struct nodeStruct *testingHT = NULL;

	//assert(List_countNodes(testingHT) == 0);

	// int k = 0;
	// int l = 0;
	// struct nodeStruct *head = 0;
	// struct nodeStruct *tail = 0;
	// for (k = 0; k < 100; k++)
	// {
	// 	head = List_createNode(k);
	// 	List_insertHead(&testingHT,head);
	// 	assert(List_countNodes(testingHT) == k+1);
	// 	assert(List_findNode(testingHT,k));
	// 	assert((testingHT->item) == k);
		
	// }

	// for (l = 100; l < 200; l++)
	// {
	// 	tail = List_createNode(l);
	// 	List_insertTail(&testingHT,tail);
	// 	assert(List_countNodes(testingHT) == l-100+k+1);
	// 	assert(List_findNode(testingHT,l));
	// 	assert((testingHT->item) == k-1); 
	// }

	/////////////////////// insert tail and then head test //////////////////////////

	// struct nodeStruct *testingTailHead = NULL;

	// assert(List_countNodes(testingTailHead) == 0); 

	// int m = 0;
	// int n = 0;
	// int saved = 0;
	// struct nodeStruct *tail;
	// struct nodeStruct *head;
	// for (m = 0; m < 100; m++)
	// {
	// 	tail = List_createNode(m);
	// 	List_insertTail(&testingTailHead,tail);
	// 	assert(List_countNodes(testingTailHead) == m+1);
	// 	assert(List_findNode(testingTailHead,m) != NULL);
	// 	saved = testingTailHead->item;
	// 	assert(saved == 0);
	// }

	// for (n = 100; n < 200; n++)
	// {
	// 	head = List_createNode(n);
	// 	List_insertHead(&testingTailHead,head);
	// 	assert(List_countNodes(testingTailHead) == n-100+m+1);
	// 	assert(List_findNode(testingTailHead,n));
	// 	assert((testingTailHead->item) == n);
	// }

	////////////////////////// alternate insert head and tail test //////////////////

	// struct nodeStruct *testingalt = NULL;

	// assert(List_countNodes(testingalt) == 0);

	// int a = 0;
	// struct nodeStruct *tail;
	// struct nodeStruct *head;
	// for (a = 0; a < 200; a++)
	// {
	// 	if ((a%2) == 0) // even insert head
	// 	{
	// 		head = List_createNode(a);
	// 		List_insertHead(&testingalt,head);
	// 		assert((testingalt->item) == a);
	// 	}
	// 	else
	// 	{
	// 		tail = List_createNode(a);
	// 		List_insertTail(&testingalt,tail);
	// 	}
	// 	assert(List_countNodes(testingalt) == a+1);
	// 	assert(List_findNode(testingalt,a) != NULL);
	// 	if ((a%2) == 0)
	// 	{
	// 		assert((testingalt->item) == a);
	// 	}
	// 	else
	// 	{
	// 		assert((testingalt->item) == a-1);
	// 	}
	// }

	////////////////////////// alternate insert tail and head test ////////////////////

	// struct nodeStruct *alternate = NULL;

	// assert(List_countNodes(alternate) == 0);

	// int b = 0;
	// struct nodeStruct *tail;
	// struct nodeStruct *head;
	// for (b = 0; b < 200; b++)
	// {
	// 	if((b%2) == 0)
	// 	{
	// 		tail = List_createNode(b);
	// 		List_insertTail(&alternate,tail);
	// 	}
	// 	else
	// 	{
	// 		head = List_createNode(b);
	// 		List_insertHead(&alternate,head);
	// 	}
	// 	assert(List_countNodes(alternate) == b+1);
	// 	assert(List_findNode(alternate,b) != NULL);
	// 	if ((b%2) == 0 && b == 0)
	// 	{
	// 		assert((alternate->item) == 0);
	// 	}
	// 	else if ((b%2) == 0)
	// 	{
	// 		assert((alternate->item) == b-1);
	// 	}
	// 	else
	// 	{
	// 		assert((alternate->item) == b);
	// 	}
	// }

	//////////////////////// Sorting random numbers ///////////////////////////////////////
	
	// struct nodeStruct *randomList = NULL;

	// assert(List_countNodes(randomList) == 0);

	///////////////////////////////////// sort one number/////////////////////////////////////////

	// struct nodeStruct *randnode;

	// int a,b;

	// for(a = 0; a < 1; a++)
	// {
	// 	b = rand() % 100;
	// 	//printf("%d\n", b);
	// 	randnode = List_createNode(b);
	// 	List_insertTail(&randomList,randnode);
	// }

	// List_sort(&randomList);

	// struct nodeStruct *temp;
	// temp = randomList;
	// int g = 0;
	// while(g < 1)
	// {
	// 	printf("%d\n", temp->item);
	// 	//printf("%d\n", temp->next->item);
	// 	//assert((temp->item) <= (temp->next->item));
	// 	//temp = temp->next;
	// 	g++;
	// }

	//////////////////////////////////////// sort no numbers ////////////////////////////////////

	// struct nodeStruct *randnode;

	// int a,b;

	// for(a = 0; a < 0; a++)
	// {
	// 	b = rand() % 100;
	// 	//printf("%d\n", b);
	// 	randnode = List_createNode(b);
	// 	List_insertTail(&randomList,randnode);
	// }

	// List_sort(&randomList);
	// assert(List_countNodes(randomList) == 0);

	// struct nodeStruct *temp;
	// temp = randomList;
	// int g = 0;
	// while(g < 0)
	// {
	// 	printf("%d\n", temp->item);
	// 	//printf("%d\n", temp->next->item);
	// 	//assert((temp->item) <= (temp->next->item));
	// 	//temp = temp->next;
	// 	g++;
	// }

	///////////////////////////////////////////// sort more than 1 number ////////////////////////

	// struct nodeStruct *randnode;

	// int a,b;

	// for(a = 0; a < 100; a++)
	// {
	// 	b = rand() % 100;
	// 	//printf("%d\n", b);
	// 	randnode = List_createNode(b);
	// 	List_insertTail(&randomList,randnode);
	// }

	// List_sort(&randomList);
	// assert(List_countNodes(randomList) == 100);

	// struct nodeStruct *temp;
	// temp = randomList;

	// int num = 0;
	// for (num = 0; num < 100; num++)
	// {
	// 	printf("%d\n", temp->item);
	// 	if(num != 99)
	// 	{
	// 		assert((temp->item) <= (temp->next->item));
	// 	}
	// 	temp = temp->next;
	// }

	printf("\nExecution finished.\n");
	return 0;
}