#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
void push(int e,int s[100],int *t);
int pop(int s[100],int *t);
 int result(char x,int m, int n);
int main()
{
	char in[100];
	int s[100];
	int top=-1;
	int i,a,b;
	int value;
	char x;
	printf("Enter the POSTFIX Expression:");
	scanf("%s",in);
	in[strlen(in)]='\0';
	for(i=0;in[i]!='\0';i++)
	{
		x=in[i];
		if(isdigit(in[i]))
		push(in[i]-'0',s,&top);
		else
		{
		b=pop(s,&top);
		a=pop(s,&top);
		value=result(x,a,b);
		push(value,s,&top);
		}
	}

	printf("The answer is= %d",pop(s,&top));
	return 0;
}
void push(int e,int s[100],int *t)
{
	if(*t==99)
	printf("Stack OVERFLOW.\n");
	*t=*t+1;
	s[*t]=e;
}

int pop(int s[100],int *t)
{
	int e;
	if(*t==-1)
	{
		printf("Stack UNDERFLOW.\n");
		return -9999;
	}
	e=s[*t];
	*t=*t-1;
	return e;
}

 int result(char x,int m, int n)
{  int y;
	switch(x)
	{
	case '+' : y=(m+n);
			break;
	case '-' : y=(m-n);
			break;
	case '*' : y=(m*n);
			break;
	case '/' : y=(m/n);
			break;
	case '^' : y=pow(m,n);
			break;
	};
  return y;
}
	
	
