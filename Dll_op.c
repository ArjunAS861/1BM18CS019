#include<stdio.h>
#include<stdlib.h>
struct node
{
	int d;
	struct node* next;
	struct node* prev;
};
typedef struct node* NODE;
NODE getnode()
{
    NODE p=(NODE)malloc(sizeof(struct node));
    return p;
}
NODE insertfront(NODE head,int e)
{
    NODE p=getnode();
    p->d=e;
    p->next=NULL;
    p->prev=NULL;
    if(head==NULL)
        return p;
    else
    {
        p->next=head;
        head->prev=p;
        p->prev=NULL;
        head=p;
        return head;
    }
}
NODE insertend(NODE head,int e)
{
    NODE p=getnode();
    p->d=e;
    p->prev=NULL;
    p->next=NULL;
    if(head==NULL)
        return p;
    else{
        NODE q=head;
        while(q->next!=NULL)
            q=q->next;
        q->next=p;
        p->prev=q;
        return head;
    }
}
void display(NODE head)
{
    if(head==NULL)
        printf("Empty LIst\n");
    else{
        NODE p=head;
        while(p!=NULL)
        {
            printf("%d ",p->d);
            p=p->next;
        }
    }
}

NODE delval(NODE head,int v)
{
    int f=0;
    if(head==NULL)
    {
        printf("Empty list\n");
        return NULL;
    }
   else if(head->d==v&&head->next==NULL)
    {
        printf("Deleted element is %d\n",head->d);
        free(head);
        return NULL;
    }
    else if(head->d==v)
    {
        NODE p=head;
        printf("Deleted element is %d\n",head->d);
        head=head->next;
        free(p);
        return head;
    }
    else{
        NODE p=head;
        while(p->next!=NULL)
        {
            if(p->d==v)
            {
                f=1;
                break;
            }
            p=p->next;
        }
        if(f==1)
	{
        printf("Deleted element is %d\n",p->d);
        p->next->prev=p->prev;
        p->prev->next=p->next;
        }
        else if(p->d==v)
        {
            printf("Deleted element is %d\n",p->d);
            p->prev->next=NULL;
            free(p);
            return head;
        }
        else
            printf("Value not found\n");
    }
}

NODE insertleft(NODE head,NODE n,int e)
{
 
 NODE p=getnode();
 p->d=e;
 if(head==NULL)
 {
  printf("Empty list\n");
  return head;
 }
if(head==n)
{
 p->next=n;
 n->prev=p;
 p->prev=NULL;
 head=p;
 return head;
}
n->prev->next=p;
p->prev=n->prev;
p->next=n;
n->prev=p;
return head;
}
 
int main()
{
    NODE h=NULL,p=NULL;
    int ch,ch_q,b,c,item,f=0;
    do
    {
       printf("Press 1: INSERT FRONT\nPress 2: INSERT REAR\nPress 3: INSERT LEFT of node\nPress 4: DELETE VALUE\nPress 5 : DISPLAY\n");  
	printf("Enter your choice : ");
        scanf("%d",&ch);
        switch(ch)        
        {  case 1:  printf("Enter element\n");
            	   scanf("%d",&item);
            	   h=insertfront(h,item);
			break;
          case 2 : printf("Enter element\n");
                   scanf("%d",&item);
                   h=insertend(h,item);
			break;
        
       	  case 3 :printf("Enter the NODE\n");
                 scanf("%d",&b);
		  printf("Enter element\n");
            	   scanf("%d",&item);
		
		  c=0;p=h;
		 while(p!=NULL)
		{
			c++;
			if(c==b)
			{ h=insertleft(h,p,item);
				f=1;
			 break;
			}
			p=p->next;
		}
		if(f==0)
			printf("Invalid NODE.");

		break;
	  case 4 : printf("Enter a value\n");
                 scanf("%d",&item);
		h=delval(h,item);
                break;
       	 case 5 : display(h);
		break;
	default: printf("Invalid Choice.");
	}         
        printf("\nDo you wan to continue(1/0)?\n");
        scanf("%d",&ch_q);
    }while(ch_q!=0);
	return 0;

}

