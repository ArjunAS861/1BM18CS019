//program to implement stack using linked list
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};
typedef struct node * NODE;
NODE getnode();
NODE insert_front(int item,NODE head);
NODE delete_front(NODE head);
void display(NODE head);
int main()
{
	NODE head=NULL;
int ch,item;
int ch_q;
do
{
	printf("Press 1:PUSH\nPress 2: POP\nPress 3: DISPLAY\n");
	printf("Enter your choice :");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1 : printf("Enter the Element :\n");
				scanf("%d",&item);
				head=insert_front(item,head);
				break;
		case 2 : head=delete_front(head);
				break;
		case 3: display(head);
				break;
		default : printf("Invalid Choice.\n");
			
	}
	printf("Do you want to Continue (1/0) ? \n");
	scanf("%d",&ch_q);
}while(ch_q!=0);
return 0;
}
NODE getnode()
{
	NODE p;
	p=(NODE)malloc(sizeof(struct node));
	if(p!=NULL)
		return p;
	else
	{
		printf("Memory could not be allocated.\n");
		exit(0);
	}
}
NODE insert_front(int item,NODE head)
{
	NODE p;
	p=getnode();
	p->data=item;
	p->next=head;
	head=p;
	return head;
}
NODE delete_front(NODE head)
{
	NODE p=head;
	if(head==NULL)
	{
		printf("Stack Underflow.\n");
		return head;
	}
	printf("Deleted Element = %d \n",p->data);
	head=p->next;
	free(p);
	return head;
}
void display(NODE head)
{
	NODE p;
	if(head==NULL)
	{
		printf("Stack is Empty.\n");
		return;
	}
	p=head;
	printf("Contents of Stack are :\n");
	while(p!=NULL)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
}
/*OUTPUT:
Press 1:PUSH
Press 2: POP
Press 3: DISPLAY
Enter your choice :1
Enter the Element :
6
Do you want to Continue (1/0) ? 
1
Press 1:PUSH
Press 2: POP
Press 3: DISPLAY
Enter your choice :2
Deleted Element = 6 
Do you want to Continue (1/0) ? 
1
Press 1:PUSH
Press 2: POP
Press 3: DISPLAY
Enter your choice :2
Stack Underflow.
Do you want to Continue (1/0) ? 
1
Press 1:PUSH
Press 2: POP
Press 3: DISPLAY
Enter your choice :3
Stack is Empty.
Do you want to Continue (1/0) ? 
0
*/

