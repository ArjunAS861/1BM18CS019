#include<stdio.h>
#include<conio.h>
struct student
{
	int age,marks;
	char id[15];
};
int main()
{
	struct student s;
	clrscr();
	printf("Enter Student details (ID,Age & Marks): \n");
	scanf("%s%d%d",&s.id,&s.age,&s.marks);
	if(s.age>20 && s.marks>=0 && s.marks<=100)
	{
		printf("Data is valid.\n");

	  if(s.marks>=65)
		printf("Student is eligible for admission.\n");
	  else
		printf("Student is NOT eligible for admission.\n");
	}
	else
		printf("Data is INVALID.\n");

	 getch();
	 return 0;
}