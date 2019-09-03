void insert(int item,int *r,int q[]),int *f)
{
	if((*f==*r+1)||(*f==0 && *r==size-1))
	{
	printf("Queue Overflow.\n");
		return;
	}
	if(*f==-1)
	*f=0;
	*r=(*r+1)%size;
	q[*r]=item;
}
int delete(int q[],int *f,int *r)
{
	int item;
	if(*f==-1)
	{
	printf("Queue Underflow.\n");
	return -9999;
	}
	item=q[*f];
	if(*f==*r)
	{
		*f=-1;
		*r=-1;
	}
	else
		*f=(*f+1)%size;
	return item;
	
}
void display(int q[],int f,int r)
{
	int i;
	if(f==-1)
	{
	printf("Queue is Empty.\n");
	return;
	}
	printf("Contents of Queue are:\n");
	for(i=f;i!=r;i=(i+1)%size)
	printf("%d\n",q[i]);
	printf(%d",q[i]);

}

