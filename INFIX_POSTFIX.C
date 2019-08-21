//program to convert an INFIX expression to POSTFIX expression
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
void push(char e,char s[100],int *t);
char pop(char s[100],int *t);
void display(char ot[100]);
int prec(char e);
int main()
{
	char in[100],s[100],ot[100];
	int i,j,top;
	top=-1;
	j=0;
	clrscr();
	printf("Enter the INFIX Expression : \n");
	scanf("%s",&in);
	in[strlen(in)]='\0';
	for(i=0;in[i]!='\0';i++)
	{
		if(isalpha(in[i])||isdigit(in[i]))
		{
		ot[j]=in[i];
		j++;
		}
		else if(top==-1)
		push(in[i],s,&top);
		else if(in[i]=='(')
		push(in[i],s,&top);
		else if(s[top]=='(')
		push(in[i],s,&top);
		else if(in[i]!=')')
		{
		  while(prec(in[i])<=prec(s[top]))
		  {
		    ot[j]=pop(s,&top);
		    j++;
		  }
		  if(prec(in[i])>prec(s[top]))
		     push(in[i],s,&top);
		 }
		 if(in[i]==')')
		 {
			while(s[top]!='(')
			{
				ot[j]=pop(s,&top);
				j++;
			}
			top=top-1;
		 }
	}
	for(;top!=-1;j++)
	ot[j]=pop(s,&top);
	ot[j]='\0';
	printf("POSTFIX Expression:\n");
	display(ot);
	getch();
	return 0;
}
void push(char e,char s[100],int *t)
{
	if(*t==99)
	printf("Stack OVERFLOW.\n");
	*t=*t+1;
	s[*t]=e;
}
char pop(char s[100],int *t)
{
	int e;
	if(*t==-1)
	{
		printf("Stack UNDERFLOW.\n");
		return 'n';
	}
	e=s[*t];
	*t=*t-1;
	return e;
}
void display(char ot[100])
{       int a;
	for(a=0;ot[a]!='\0';a++)
	printf("%c",ot[a]);
}
int prec(char e)
{
	if(e=='^')
	return 3;
	if(e=='*' || e=='/')
	return 2;
	if(e=='+' || e=='-')
	return 1;
}
















































