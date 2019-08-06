#include<stdio.h>
#include<conio.h>


 struct marks
 {
 char name[30];
 int mark[6];
 int grade[6];
 }s1;
 void main()
 {

 int i;float sum=0;float sgpa;
clrscr();
 printf("Enter the name of the student\n");
 gets(s1.name);
 printf("Enter the marks of the student\n");
 for (i=0;i<6;i++)
 scanf("%d",&s1.mark[i]);
 for (i=0;i<6;i++)
 {
 if ((s1.mark[i]<100) && (s1.mark[i]>89))
 s1.grade[i]=10;
 else if  ((s1.mark[i]<90) && (s1.mark[i]>74))
 s1.grade[i]=9;
 else if ((s1.mark[i]<75) && (s1.mark[i]>59))
 s1.grade[i]=8;
 else if  ((s1.mark[i]<60) && (s1.mark[i]>49))
 s1.grade[i]=7;
 else if  ((s1.mark[i]<50) && (s1.mark[i]>39))
 s1.grade[i]=6;
 else
 s1.grade[i]=0;
 }


 for (i=0;i<6;i++)
 {
 sum=sum+s1.grade[i];
 sgpa=sum/6.0;
 }

 printf("The marks of the student  %s is\n",s1.name);
 for (i=0;i<6;i++)
 printf(" %d",s1.mark[i]); printf("\nThe grades are\n");
 for(i=0;i<6;i++)
 printf("%d ",s1.grade[i]);
 printf("\nThe sgpa is ");
 printf("%f",sgpa);


 getch();
 }



