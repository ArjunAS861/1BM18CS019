#include<stdio.h>
#include<ctype.h>
void push(char e,char s[100],int *t);
char pop(char s[100],int *t);
int prec(char e);
void display(char ot[100]);

int main()
{
 char in[100],ot[100],s[100];
int j;
int top=-1;
printf("Enter the expression:");
gets(in);
for(int i=0;in[i]!='\0';i++)
{
	
	 if(in[i]=='('|| prec(in[i])>prec(s[top]) || top==-1)
	push(in[i],s,&top);
	else
	{      if(isalpha(in[i])||isdigit(in[i]))
	        ot[i]=in[i];
		for(j=i;(prec(in[i])<=prec(s[top]);j++)
		{
		ot[j]=pop(s,&top);
		}
	if(in[i]=='(')
	push(in[i],s,&top);
	}
	if(in[i]==')')
	{
	while(s[top]!='(')
	{
		
		ot[j]=pop(s,&top);
		j++;
	top=top-1;
	}
	}
	for(;s[top]!=-1;j++)
	{ot[j]=pop(s,&top);
	}
	ot[j]='\0';
	display(ot);
}
return 0;
}
void push(char e,char s[100],int *t)
{
	if(*t==99)
	{
	printf("Stack overflow.");
	}
	*t=*t+1;
	s[*t]=e;
}
char pop(char s[100],int *t)
{
int e;
if(*t==-1)
	{
	printf("Stack Underflow.");
	return n;
	}
e=s[*t];
*t=*t-1;
return e;
}
void display(char ot[100])
{
	for(int i=0;ot[i]!='\0';i++)
	printf("%c ",ot[i]);
}
