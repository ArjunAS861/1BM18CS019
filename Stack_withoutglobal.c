#include<stdio.h>

void push(int e,int s[5],int *t);
int pop(int s[5],int *t);
void display(int s[5],int t);
int main()
{
 int stack[5];
int x,a,v;
int top=-1;
do
{printf(" Press 1 : PUSH\n Press 2 : POP \n Press 3 : DISPLAY \n Press 4  : Exit\n");
scanf("%d",&x);
switch(x)
{case 1: printf("Enter the element you want to PUSH :\n");
		scanf("%d",&v);
		push(v,stack,&top);
		break;

case 2 : a=pop(stack,&top);
	if(a!=-9999)
		printf("The popped element is%d\n",a);
		break;
case 3 : display(stack,top);
	  break;
case 4 : break;
default : printf("Invalid INPUT.\n");
	  break;
};
}while(x!=4);
return 0;
}
void push(int e,int s[5],int *t)
{
	if(*t==4)
	{
		printf("Stack Overflow.\n");
		return;
}
*t=*t+1;
s[*t]=e;
}
int pop(int s[5],int *t)
{
int e;
	if(*t==-1)
{
printf("Stack Underflow.\n");
return -9999;
}
e=s[*t];
*t=*t-1;
return e;
}

void display(int s[5],int t)
{
 if (t==-1)
{
printf("Stack is Empty.\n");
return;
}
printf("Elements Inside Stack are :\n");
for(int i=t;i>=0;i--)
 printf("%d\n",s[i]);
}
	
