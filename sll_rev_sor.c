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
NODE reverse_sll(NODE head);
void sort_sll(NODE head);
NODE concatenate(NODE h1,NODE h2);
void display(NODE head);
int main()
{
	NODE head1=NULL,head2=NULL;
	int ch,item,ch_q;
	do
	{
	printf("Press 1: INSERT List1\nPress 2: INSERT List2\nPress 3: REVERSE List1\nPress 4: REVERSE List2\nPress 5: SORT List1\nPress 6: SORT List2\nPress 7: CONCATENATION\nPress 8: DISPLAY List1\nPress 9: DISPLAY List2\n");
		printf("Enter your choice :");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: printf("Enter the Element: ");
				scanf("%d",&item);
				head1=insert_front(item,head1);
				break;
			case 2: printf("Enter the Element: ");
				scanf("%d",&item);
				head2=insert_front(item,head2);
				break;
			case 3:	head1=reverse_sll(head1);
				break;
			case 4:	head2=reverse_sll(head2);
				break;
			case 5: sort_sll(head1);
				break;
			case 6: sort_sll(head2);
				break;
			case 7 : head1=concatenate(head1,head2);
				break;
			case 8 : display(head1);
				break;
			case 9 : display(head2);
				break;
			default: printf("Invalid choice.");
		}
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
NODE insert_front(int item,NODE head)
{
	NODE p;
	p=getnode();
	p->data=item;
	p->next=head;
	head=p;
	return head;
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
NODE reverse_sll(NODE head)
{
	NODE curr=head,prev=NULL,nextn=NULL;
	if(head==NULL)
	{
		printf("List is EMPTY.\n");
		return head;
	}
	if(head->next==NULL)
		return head;
	while(curr!=NULL)
	{
		nextn=curr->next;
		curr->next=prev;
		prev=curr;
		curr=nextn;
	}
	head=prev;
	return head;
}
void sort_sll(NODE head)
{
	NODE p=head,q=NULL;
	if(head==NULL)
		return;
	while(p->next!=NULL)
	{
		q=p->next;
		while(q!=NULL)
		{
			if(p->data>q->data)
			{
				p->data=(p->data)+(q->data);
				q->data=(p->data)-(q->data);
				p->data=(p->data)-(q->data);
			}
			q=q->next;
		}
	p=p->next;
	}
}
NODE concatenate(NODE h1,NODE h2)
{
	if(h1==NULL)
		return h2;
	if(h2==NULL)
		return h1;
	NODE p=h1;
	while(p->next!=NULL)
		p=p->next;
	p->next=h2;
	return h1;
}
/*OUTPUT :
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :1
Enter the Element: 34
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :1
Enter the Element: 56
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :4
List is EMPTY.
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :2
Enter the Element: 12
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :2
Enter the Element: 3
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :3
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :8
Contents of List are :
34
56
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :5
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :8
Contents of List are :
34
56
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :9
Contents of List are :
3
12
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :7
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :8
Contents of List are :
34
56
3
12
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :5
Do you want to continue(1/0)?
1
Press 1: INSERT List1
Press 2: INSERT List2
Press 3: REVERSE List1
Press 4: REVERSE List2
Press 5: SORT List1
Press 6: SORT List2
Press 7: CONCATENATION
Press 8: DISPLAY List1
Press 9: DISPLAY List2
Enter your choice :8
Contents of List are :
3
12
34
56
Do you want to continue(1/0)?
0
*/
