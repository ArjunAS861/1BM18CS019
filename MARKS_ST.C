#include<stdio.h>
#include<conio.h>


 struct marks
 {
 char name[30];
 int mark[6];
 }s1;
 void main()
 {

 int i;
clrscr();
 printf("Enter the name of the student\n");
 gets(s1.name);
 printf("Enter the marks of the student\n");
 for (i=0;i<6;i++)
 scanf("%d",&s1.mark[i]);



 printf("The marks of the student  %s is\n",s1.name);
 for (i=0;i<6;i++)
 printf(" %d",s1.mark[i]);


 getch();
 }



