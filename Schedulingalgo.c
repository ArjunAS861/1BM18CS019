//program to implement Scheduling Algorithm
#include<stdio.h>
float process(int bt[],int ct[],int tat[],int wt[],int n);
int main()
{
	int bt[10]={0},ct[10]={0},wt[10]={0};
	int n,sum=0,total=0,tat[10]={0};
	float atat;
	printf("Enter No. of Processes : ");
	scanf("%d",&n);
	printf("Enter the BURST TIME for each Process : ");
	for(int i=0;i<n;i++)
	scanf("%d",&bt[i]);
	atat =process(bt,ct,tat,n);
	for(int i=0;i<n;i++)
	{	printf("Process %d started at %d and ended at %d\t",i+1,ct[i],ct[i+1]);
		printf("Turn around time =%d\t",tat[i]);
		printf("waiting Time=%d\n",wt[i]);
	}
	printf("Average TURN AROUND Time= %f",atat);
	return 0;
}
float process(int bt[],int ct[],int tat[],int wt[],int n)
{
int i,sum,total;
float atat;
for(i=0;i<n;i++)
	{	sum+=bt[i];
		ct[i+1]+=sum;
		tat[i]=ct[i+1];
		wt[i]=tat[i]-bt[i];
		total+=tat[i];
	}

atat=(float)total/n;
return atat;
}
