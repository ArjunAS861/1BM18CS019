//program to implement Linked list only Insertion
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};
typedef struct node * NODE;
NODE getnode();
NODE insert_first(int item,NODE head);
void insert_end(int item,NODE head);
NODE insert_pos(NODE head,int item,int pos);
void display(NODE head);
int main()
{
	NODE head=NULL;
	int ch,item,ch_q,pos;
	do
	{
		printf("Press 1: INSERT FIRST\nPress 2 : INSERT END\nPress 3: INSERT POSITION\nPress 4: DISPLAY\n");
		printf("Enter your choice :");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: printf("Enter the Element:\n");
				scanf("%d",&item);
				head=insert_first(item,head);
				break;
			case 2: printf("Enter the Element:\n");
				scanf("%d",&item);
				insert_end(item,head);
				break;
			case 3: printf("Enter the Element and Position :\n");
				scanf("%d %d",&item,&pos);
				head=insert_pos(head,item,pos);
				break;
			case 4: display(head);
				break;
			default: printf("Invalid choice.");
		};
		printf("Do you want to continue(1/0)?\n");
		scanf(" %d",&ch_q);
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
NODE insert_first(int item,NODE head)
{
	NODE p;
	p=getnode();
	p->data=item;
	p->next=head;
	head=p;
	return head;
}
void insert_end(int item,NODE head)
{	if(head==NULL)
	{
		printf("Cannot Insert at the End (NO NODE).\n");
		return;
	}
	NODE p,q;
	q=getnode();
	q->data=item;
	p=head;
	while(p->next!=NULL)
	p=p->next;
	p->next=q;
	q->next=NULL;
}
NODE insert_pos(NODE head,int item,int pos)
{
	NODE q,p,newn;
	p=NULL;
	int c=1;
	newn=getnode();
	newn->data=item;
	newn->next=NULL;
	if(head==NULL)
	{
		if(pos==1)
			return newn;
		else
		{
			printf("Invalid Position.\n");
			return head;
		}
	}
	if(pos==1)
	{
		newn->next=head;
		head=newn;
		return head;
	}
	
	else{
		q=head;

		while(q!=NULL && c!=pos)
		{
			p=q;
			q=q->next;
			c++;
		}
		if(c==pos)
		{
			p->next=newn;
			newn->next=q;
			return head;
		}
		else
		{
			printf("Invalid position.\n");
			return head;
		}
	}
}
void display(NODE head)
{
	NODE p;
	if(head==NULL)
	{
		printf("List is Empty.\n");
		return;
	}
	p=head;
	printf("Contents of List are :\n");
	while(p!=NULL)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
}



