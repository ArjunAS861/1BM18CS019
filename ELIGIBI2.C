#include<stdio.h>
#include<conio.h>
struct student
{
	int age,marks;
	char id[15];
};
int main()
{
	struct student s[10];
	int i;
	clrscr();
	for(i=0;i<10;i++)
	{
	printf("Enter Student details (ID,Age & Marks): \n");
	scanf("%s%d%d",&s[i].id,&s[i].age,&s[i].marks);
	if(s[i].age>20 && s[i].marks>=0 && s[i].marks<=100)
	{
		printf("Data is valid.\n");

	  if(s[i].marks>=65)
		printf("Student is eligible for admission.\n");
	  else
		printf("Student is NOT eligible for admission.\n");
	}
	else
		printf("Data is INVALID.\n");

	}
	 getch();
	 return 0;
}