//program to implement linear QUEUE
#include<stdio.h>
#define size 10
void insert(int item,int *r,int q[]);
int delete(int q[],int *f,int *r);
void display(int q[],int f,int r);
int main()
{
int f=0,r=-1;
int q[size];
int ch,item;
int ch_q;
do
{
	printf("Press 1: INSERTION\nPress 2: DELETION\nPress 3: DISPLAY\n");
	printf("Enter your choice :");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1 : printf("Enter the Element :\n");
				scanf("%d",&item);
				insert(item,&r,q);
				break;
		case 2 : item=delete(q,&f,&r);
				if(item!=-9999)
				printf("Deleted Element is %d\n",item);
				break;
		case 3: display(q,f,r);
				break;
		default : printf("Invalid Choice.");
				break;
	};
	printf("Do you want to Continue (1/0) ? \n");
	scanf("%d",&ch_q);
}while(ch_q!=0);
return 0;
}

			

void insert(int item,int *r,int q[])
{
	if(*r==size-1)
	{
	printf("Queue Overflow.\n");
		return;
	}
	*r=*r+1;
	q[*r]=item;
}
int delete(int q[],int *f,int *r)
{
	int item;
	if(*f>*r)
	{
	printf("Queue Underflow.\n");
	return -9999;
	}
	item=q[*f];
	*f=*f+1;
	return item;
}
void display(int q[],int f,int r)
{
	int i;
	if(f>r)
	{
	printf("Queue is Empty.\n");
	return;
	}
	printf("Contents of Queue are:\n");
	for(i=f;i<=r;i++)
	printf("%d\n",q[i]);
}

