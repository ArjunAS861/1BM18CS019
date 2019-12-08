#include<stdio.h>
#include<stdlib.h>
struct node
{	int data;
	struct node *next;
};
typedef struct node *NODE;
NODE chead()
{
	NODE p=(NODE)malloc(sizeof(struct node));
	p->next=p;
	p->data=-1;
	return p;
}
NODE getnode()
{
	
	NODE p=(NODE)malloc(sizeof(struct node));
	return p;
}
NODE insertfront(NODE head,int item)
{
	NODE p=getnode();
	p->data=item;
	p->next=head->next;
	head->next=p;
	return head;
}
NODE insertrear(NODE head,int item)
{
	NODE q;
	NODE p=getnode();
	p->data=item;
	q=head->next;
	while(q->next!=head)
		q=q->next;
	q->next=p;
	p->next=head;
	return head;
}
NODE add_long(NODE n1,NODE n2)
{	NODE num1=n1->next;
	NODE num2=n2->next;
	NODE n=chead();
	int pn1,pn2,sum=0,carry=0;
	while(num1!=n1||num2!=n2)
	{
		if(num1==n1)
			pn1=0;
		else
			pn1=num1->data;
		if(num2==n2)  pn2=0;
		else
			pn2=num2->data;
		sum=pn1+pn2+carry;
		carry=sum/10;
		n=insertrear(n,sum%10);
		if(num1!=n1)
			num1=num1->next;
		if(num2!=n2)
			num2=num2->next;
	}
	if(carry>0)
		n=insertrear(n,carry);
	return n;
}
void display(NODE head)

{	NODE p=head;
	 p=head->next;
	
	while(p!=head)
		{
			printf("%d",p->data);
			p=p->next;
		}
}

int  main()
{		int l1,l2,i,j,a;
		NODE n1=chead();
		NODE n2=chead();
		NODE n3=NULL;
		printf("Enter length 1:");
		scanf("%d",&l1);		
		printf("Enter the Number:");
		for(i=0;i<l1;i++)
		{
			scanf("%d",&a);
			n1=insertfront(n1,a);
		}
		printf("Enter length 2: ");
		scanf("%d",&l2);
		printf("Enter the Number:");
		for(i=0;i<l2;i++)
		{
			scanf("%d",&a);
			n2=insertfront(n2,a);
		}
		n3=add_long(n1,n2);
		printf("Sum is ");printf("\n");
		display(n3);printf("\n");
		display(n1);printf("\n");
		display(n2);
	return 0;
}
	
		
