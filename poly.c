#include<stdio.h>
#include<stdlib.h>
struct node
{
	int pow,coe;
	struct node *next;
};
typedef struct node * NODE;
NODE getnode()
{
	NODE p=(NODE)malloc(sizeof(struct node));
	return p;
}
void add_p(NODE h1,NODE h2,NODE h3)
{
	h3=getnode();
	while((!h1->next)&&(!h2->next))
	{
		if(h1->pow>h2->pow)
		{
			h3->pow=h1->pow;
			h3->coe=h1->coe;
			h1=h1->next;
		}
		
		if(h1->pow<h2->pow)
		{
			h3->pow=h2->pow;
			h3->coe=h2->coe;
			h2=h2->next;
		}
		
		if(h1->pow>h2->pow)
		{
			h3->pow=h1->pow;
			h3->coe=h2->coe+h1->coe;
			h1=h1->next;h2=h2->next;
		}
		h3->next=getnode();
		h3=h3->next;
		h3->next=NULL;
	}
}
NODE insertfront(NODE head,int item1,int item2)
{
	NODE p=getnode();
	p->pow=item1;
	p->coe=item2;
	if(head ==NULL)
		{p->next=NULL;
		head=p;}
	else
		{p->next=head->next;
		head=p;}
	return p;
}
void display(NODE head)
{
	NODE p=head;
	while(p!=NULL)
		{ printf("(%d,%d) ",p->coe,p->pow);
			p=p->next;
		}
}
int main()
{
	NODE h1=NULL,h2=NULL;
	NODE h3=NULL;
	int i,a,b,n;printf("Length 1: ");
	scanf("%d",&n);
	printf("Enter coefficient and degree 1: ");
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		h1=insertfront(h1,a,b);
	}
	printf("Length 2: ");
	scanf("%d",&n);
	printf("Enter coefficient and degree 2: ");
	
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		h2=insertfront(h2,a,b);
	}
	add_p(h1,h2,h3);
	display(h3);printf("\n");
	display(h1);printf("\n");
display(h2);
	return 0;
}
