#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *lchild;
	struct node *rchild;
};
typedef struct node * NODE;
NODE getnode(int item)
{
	NODE p;
	p=(NODE)malloc(sizeof(struct node));
	p->data=item;
	p->lchild=NULL;
	p->rchild=NULL;
	return p;
}
NODE insert(NODE root, int item)
{
	if(root==NULL)
		return getnode(item);
	if(item<root->data)
		root->lchild=insert(root->lchild,item);
	else if(item>root->data)
		root->rchild=insert(root->rchild,item);
	return root;
}
void inorder(NODE root)
{
	if(root==NULL)
		return;
	inorder(root->lchild);
	printf("%d ",root->data);
	inorder(root->rchild);
}
void preorder(NODE root)
{
	if(root==NULL)
		return;
	printf("%d ",root->data);
	preorder(root->lchild);
	
	preorder(root->rchild);
}
void postorder(NODE root)
{
	if(root==NULL)
		return;
	postorder(root->lchild);
	
	postorder(root->rchild);
	printf("%d ",root->data);
}
void levelorder(NODE root)
{
}
int main()
{
	NODE r=NULL;
	int ch,ch_q,c,item;
	do
	{	printf("Press 1 :INSERT\nPress 2 :DISPLAY\n");
		printf("Enter your choice : ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1 : printf("Enter the Element : ");
			 scanf("%d",&item);
			 r=insert(r,item);
			 break;
		case 2 : printf("Press 1 :PREORDER\nPress 2 :POSTORDER\nPress 3 :INORDER\nPress 4:LEVELORDER\n");
			 scanf("%d",&c);
			 switch(c)
			{
				case 1 : preorder(r);
					break;
				case 2 : postorder(r);
					break;
				case 3 :inorder(r);
					break;
				case 4 :levelorder(r);
					break;
				default: printf("Invalid choice.\n");
			}
			break;
		default: printf("Invalid choice.\n");
	}
	printf("Do you want to continue(1/0)?\n");
	scanf("%d",&ch_q);
	}while(ch_q!=0);
	return 0;
}
