//IMPLEMENTATION OF XOR LINKED LIST
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

// Node structure of a memory efficient doubly linked list
struct node {
    int data;
    struct node* npx; /* XOR of next and previous node */
};

/* returns XORed value of the node addresses */
struct node* XOR(struct node *a, struct node *b) {
	int x= (unsigned int)a;
	int y=(unsigned int)b;
	int z= (x^y);
	struct node* n;
	n=(struct node*)z;
    return n;
}

/* Insert a node at the begining of the XORed linked list and makes the
 newly inserted node as head */
void insert_front(struct node **head_ref, int data) {
     // Allocate memory for new node
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = data;

    /* Since new node is being inserted at the begining, npx of new node
     will always be XOR of current head and NULL */
    new_node->npx = XOR(*head_ref, NULL);

    /* If linked list is not empty, then npx of current head node will be XOR
     of new node and node next to current head */
    if (*head_ref != NULL) {
	// *(head_ref)->npx is XOR of NULL and next. So if we do XOR of
	// it with NULL, we get next
	struct node* next = XOR((*head_ref)->npx, NULL);
	(*head_ref)->npx = XOR(new_node, next);

    }

    // Change head
    *head_ref = new_node;
}

void insert_end(struct node **head_ref, int data)
{
  // Allocate memory for new node
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = data;
   //struct node *ptr=NULL;
    if(*head_ref==NULL)
    {
     new_node->npx = XOR(*head_ref, NULL);
     }
    else
    {
    struct node *curr,*previous,*next;
    curr=*head_ref;
    previous=NULL;
    while(curr!=NULL)
    {
    next= XOR(previous,curr->npx);
    if(next==NULL)
    {
    break;
    }
    else
    {
    previous=curr;
    curr=next;
    }
    }
    new_node->npx=XOR(curr,NULL);
    curr->npx=XOR(previous,new_node);
    }
}

void insert(struct node **head_ref,int data)
{ struct node *ptr1;
  struct node *ptr2;
  struct node *new_node;
  struct node *curr;
  struct node *previous;
  struct node *next;
  int count=0;
  int k;
  printf("Enter the Position\n");
  scanf("%d",&k);
  // Allocate memory for new node
    new_node= (struct node *) malloc(sizeof(struct node));
    if(new_node==NULL)
    {
      printf("Insufficient memory\n"); return;
    }
  new_node->data = data;
  if(k==1)
  {
  
  		/* Since new node is being inserted at the begining, npx of new node
     	will always be XOR of current head and NULL */
    	new_node->npx = XOR(*head_ref, NULL);

    	/* If linked list is not empty, then npx of current head node will be XOR
     	of new node and node next to current head */
    	if (*head_ref != NULL) {
		// *(head_ref)->npx is XOR of NULL and next. So if we do XOR of
		// it with NULL, we get next
		 next = XOR((*head_ref)->npx, NULL);
		(*head_ref)->npx = XOR(new_node, next);
	}
	 *head_ref = new_node;
		return;
}
else
  curr=*head_ref;
  previous=NULL;
  next=NULL;
  while((count<k-1) && (curr!=NULL))
  {
    next=XOR(previous, curr->npx);
    previous=curr;
    curr=next;
   ++count;
  }

  ptr1 = XOR(previous, curr->npx);
  ptr2=XOR(previous->npx,curr);
  new_node->npx=XOR(previous, curr);
  curr->npx=XOR(new_node, ptr1);
  previous->npx=XOR(new_node, ptr2);
}



// prints contents of doubly linked list in forward direction
void printList(struct node *head) {
    struct node *curr = head;
    struct node *prev = NULL;
    struct node *next;

    printf("Following are the nodes of Linked List: \n");
    if(curr==NULL)
    {
    	printf("List is Empty\n");
	}
	else
    while (curr != NULL) {
	// print current node
	printf("%d ", curr->data);

	// get address of next node: curr->npx is next^prev, so curr->npx^prev
	// will be next^prev^prev which is next
	next = XOR(prev, curr->npx);

	// update prev and curr for next iteration
	prev = curr;
	curr = next;
    }
}
void delete_front(struct node **head_ref)
{
  struct node *ptr;
  struct node *next;
  struct node *current;
  current= *head_ref;
  if(*head_ref==NULL)
  {
    printf("List is Empty\n");
  }
  else
     ptr=XOR(current->npx, NULL);
     next= XOR(ptr->npx, current);
     ptr->npx=XOR(NULL, next);
     current->npx= XOR(NULL,NULL);
     *head_ref=ptr;
 }
void delete_end(struct node **head_ref)
{
  struct node *current, *previous, *next, *ptr;
  if(*head_ref==NULL)
  {
  printf("List is Empty\n"); return;
  }
    current= *head_ref;
    previous= NULL;
    while(current!=NULL)
    {
      next= XOR(previous,current->npx);
      if(next==NULL)
      {
	break;
      }
      else
      previous= current;
      current= next;
    }

    ptr= XOR(previous->npx, current);
    previous->npx= XOR(ptr,NULL);
    current->npx= XOR(NULL, NULL);
}

void delet(struct node **head_ref)
{
  int count, k;
  struct node *next, *current, *previous, *ptr1, *ptr2, *ptr3;
  if(*head_ref==NULL)
  {
  printf("List is Empty\n"); return;
  }
  else
  count=0;
  printf("\nEnter the Position for Deletion\n");
  scanf("%d",&k);
  current= *head_ref;
  previous= NULL;
  if(k==1)
  {
     ptr1=XOR(current->npx, NULL);
     next= XOR(ptr1->npx, current);
     ptr1->npx=XOR(NULL, next);
     current->npx= XOR(NULL,NULL);
     *head_ref=ptr1;
     return;
  }
  else
  {

	while((count<k-1) && (current!=NULL))
  {
    next= XOR(current->npx, previous);
    if(next==NULL)
    {
     break;
    }
    else
    {
      previous= current;
      current= next;
      ++count;
    }
  }
  ptr2= XOR(current->npx, previous);
  ptr1= XOR(previous->npx, current);
  ptr3=  XOR(ptr2->npx, current);
  current->npx= XOR(NULL, NULL);
  previous->npx= XOR(ptr1, ptr2);
  ptr2->npx= XOR(previous, ptr3);

      printf("Previous: %d\n",previous->data);
      printf("Ptr1: %d\n",ptr1->data);
      printf("Ptr2: %d\n",ptr2->data);
      printf("Ptr3: %d\n",ptr3->data);
}
}
// Driver program to test above functions
void main() {

    int n;
	   int choice,x,position;
    struct node *head ;
    head=NULL;
    printf("\n 1. Insertion\n");
    printf("\n 2. Deletion\n");
    printf("\n 3. Display()\n");
    scanf("%d", &choice);
    switch(choice)
    {
    	case 1:
    	{
    		 printf("Now Insert for a random position within the current length of list\n\n");
       printf("\nEnter the data for the new node to be inserted\n");
       scanf("%d",&x);
       insert(&head, x);
       printList(head);
       printf("\n");
       break;
    	}

    	case 2:
    	{
    		//Delete at any position
       printf("Now Delete at any random position within the current length of the list:\n");
       printList(head);
       printf("\n");
       delet(&head);
       printList(head);
       break;

    	}

    	case 3:
    	{
    		 printList(head);
    		 break;	
    	}

    }
    /*

      insert_front(&head, 1);
      insert_front(&head, 2);
      insert_front(&head, 3);
      insert_front(&head, 4);
      insert_front(&head, 5);
      printf("\nInitially the list is:\n");
      printList(head);

	//Insert at End
       printf("\nEnter new node to be inserted in End\n");
       scanf("%d",&n);
       insert_end(&head, n);
       printList(head);
       printf("\n");

	//Insert at any random position
       printf("Now Insert for a random position within the current length of list\n\n");
       printf("\nEnter the data for the new node to be inserted\n");
       scanf("%d",&x);
       insert(&head, x);
       printList(head);
       printf("\n");

    //Deletion at front
       printf("Now Deletion at Front is going to happen:\n\n");
       delete_front(&head);
       printList(head);
       printf("\n");

    //Delete at end
       printf("Now Deletion at end is going to happen:\n\n");
       delete_end(&head);
       printList(head);
       printf("\n");

    //Delete at any position
       printf("Now Delete at any random position within the current length of the list:\n");
       printList(head);
       printf("\n");
       delet(&head);
       printList(head);
       */


   getch();

}
