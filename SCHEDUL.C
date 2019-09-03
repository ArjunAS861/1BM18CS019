#include<stdio.h>
#include<conio.h>
int main()
{
	int bt[10]={0},ct[10]={0};
	int n,sum=0,total=0,tat[10]={0};
	float atat;
	printf("Enter No. of Processes : ");
	scanf("%d",&n);
	Printf("Enter the BURST TIME for each Process : ");
	for(int i=0;i<n;i++)
	scanf("%d",&bt[i]);
	for(i=0;i<n;i++)
	{	sum+=bt[i];
		ct[i+1]+=sum;
		tat[i]=ct[i+1];
		total+=tat[i];
	}
	atat=total/n;
	for(i=0;i<n;i++)
	printf("Process %d started at %d and ended at %d",i+1,ct[i],ct[i+1]);
	printf("Turn around time =%d",tat[i]);
	printf("Average TURN AROUND Time=%d",atat);
	getch();
	return 0;
}
	