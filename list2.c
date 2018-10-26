//LOL list
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stud{
		int Roll_No;
		char Name[20];
		float CGPA;
		struct stud*next;
}*head=NULL,*temp,*save,*save2;
void ins_beg()
{
	char name[20];
	int roll;
    float cg;
	printf("Enter Student Roll no.:\n");
	scanf("%d",&roll);
	printf("Enter Student Name:\n");
	scanf("%s",name);
	printf("Enter Student CGPA:\n");
	scanf("%f",&cg);
	temp=(struct stud*)malloc(sizeof(struct stud));
	temp->Roll_No=roll;	
	strcpy(temp->Name,name);
	temp->CGPA=cg;
	temp->next=NULL;	
	if(head==NULL||head->Roll_No >= temp->Roll_No)
	{
		temp->next=head;
		head=temp;
	
	}
	else
	{
		save=head;
		while(save->next!=NULL&&(save->next->Roll_No)<(temp->Roll_No))
            		save=save->next;
		temp->next=save->next;
        	save->next=temp;
	}
}
void del_beg()
{
	if(head==NULL)
		printf("Underflow\n");
	else
		head=head->next;
}
void del_pos()
{
	int pos;
    printf("Enter Position:\n");
	scanf("%d",&pos);
    if(head==NULL)
		printf("Underflow\n");
	else
    {
        save=head;
        pos--;
        while(--pos)
            save=save->next;
        save->next=save->next->next;
        
    }
}
void del_end()
{
	if(head==NULL)
		printf("Underflow\n");
	else
    {
        temp=head;
        while(temp->next->next!=NULL)
            temp=temp->next;
        temp->next=NULL;
    }
}
void disp()
{
	temp=head;
	while(temp!=NULL)
	{
		printf("Student Roll no.:%d\n",temp->Roll_No);
		printf("Student Name:%s\n",temp->Name);
		printf("Student CGPA:%f\n",temp->CGPA);
		temp=temp->next;
	}
}
void search()
{
    int s;
    int flag=0;
    printf("Enter Roll no:\n");
    scanf("%d",&s);
    temp=head;
    while(temp!=NULL)
    {
        if(s==temp->Roll_No)
        {
            flag=1;
            save=temp;
            break;            
        }
        else
            flag=0;
        temp=temp->next;
    }
    if(flag==1)
    {
        printf("Student Roll no.:%d\n",save->Roll_No);
        printf("Student Name:%s\n",save->Name);
        printf("Student CGPA:%f\n",save->CGPA);
    }
    else
        printf("Not Found\n");
            
}
int main()
{
        printf("This program creates linear ordered linked list.\n");
	int choice=0;
	while(choice!=7)
	{
		printf("1.Insert Beginning\n");
		printf("2.Delete Beginning\n");
        printf("3.Delete between\n");
        printf("4.Delete End\n");
        printf("5.Search\n");
		printf("6.Display\n");
		//printf("4.Peek\n");
		printf("7.Exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:ins_beg();break;
			case 2:del_beg();break;
            case 3:del_pos();break;
            case 4:del_end();break;
            case 5:search();break;
            case 6:disp();break;
            //case 9:exit(0);break;    
        }
	}
    return 0;
}















