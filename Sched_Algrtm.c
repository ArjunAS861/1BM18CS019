//program to implement Scheduling Algorithm

#include<stdio.h>
void insert(int ele,int *r,int q[]);
int main()

{

	int bt[10],ct[10]={0},wt[10]={0};

	int x,n,sum=0,total=0,tat[10]={0},r=-1,f=0;

	float atat;

	printf("Enter No. of Processes : ");

	scanf("%d",&n);

	

	for(int i=0;i<n;i++)
    {
        printf("Enter the BURST TIME for  Process %d :  ",i+1);
	    scanf("%d",&x);
	    insert(x,&r,bt);
    }
	

	for(int i=0;i<n;i++)

	{	sum+=bt[i];

		ct[i+1]+=sum;

		tat[i]=ct[i+1];

		wt[i]=tat[i]-bt[i];

		total+=tat[i];

	}



atat=(float)total/n;


	for(int i=0;i<n;i++)

	{	printf("Process %d started at %d and ended at %d\t",i+1,ct[i],ct[i+1]);

		printf("Turn around time =%d\t",tat[i]);

		printf("waiting Time=%d\n",wt[i]);

	}

	printf("Average TURN AROUND Time= %f",atat);

	return 0;

}

void insert(int ele,int *r,int q[])
{
    if(*r==1)
    {
        printf("Ready Queue Overflow.\n");
        return;
    }
    *r=*r+1;
    q[*r]=ele;
}