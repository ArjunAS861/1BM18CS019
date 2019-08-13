#include<stdio.h>

void push(int e,int s[100],int *t);
int pop(int s[100],int *t);
void display(int s[100],int t);
int main()
{
 int stack[100];
int top=-1;int a;	
push(2,stack,&top);
push(5,stack,&top);
push(6,stack,&top);
push(7,stack,&top);
push(8,stack,&top);
display(stack,top);
a=pop(stack,&top);
if(a!=-9999)
printf("Popped element is %d\n",a);
display(stack,top);
return 0;





}
void push(int e,int s[100],int *t)
{
	if(*t==99)
	{
		printf("Stack Overflow.\n");
		return;
}
*t=*t+1;
s[*t]=e;
}
int pop(int s[100],int *t)
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

void display(int s[100],int t)
{
 if (t==-1)
{
printf("Stack is Empty.\n");
return;
}
for(int i=t;i>=0;i--)
 printf("%d\n",s[i]);
}
	
