#include<stdio.h>
#include<stdlib.h>

struct node{
char name[20];
int rollno;
float cgpa;
struct node* link;
};
struct node* ptr;

void display(struct node* head)
{
	if(head==NULL)
	{
	printf("The linked list is empty\n");
	}
	else if(head->link==head)
	{
		printf("%s\n",head->name);
		printf("%d\n",head->rollno);
		printf("%f\n\n",head->cgpa);
	}

	else
	{
	struct node* ptr;
	ptr=head;
	int c=1;
		while(ptr->link!=head)
		{
		printf("%d\n",c);
		printf("%s\n",ptr->name);
		printf("%d\n",ptr->rollno);
		printf("%f\n\n",ptr->cgpa);
		ptr=ptr->link;
		c=c+1;
		}
		printf("%d\n",c);
		printf("%s\n",ptr->name);
		printf("%d\n",ptr->rollno);
		printf("%f\n\n",ptr->cgpa);
	}

}


struct node* insertatend(struct node* head)
{
struct node* new=(struct node*)malloc(sizeof(struct node));
printf("enter the name of the student:- ");
scanf("%s",new->name);
printf("enter the roll no. of the student:-");
scanf("%d",&(new->rollno));
printf("enter the cgpa of the student:-");
scanf("%f",&(new->cgpa));

new->link=head;

if(head==NULL)
{
	head=new;

}
else if(head->link==head)
{
head->link=new;
new->link=head;
}

else
{
	struct node* ptr;
	ptr=head->link;
	while(ptr->link!=head)
	{
	ptr=ptr->link;
	}
	ptr->link=new;
	new->link=head;
}
return head;
}


struct node* insertatfront(struct node* head)
{
struct node* new=(struct node*)malloc(sizeof(struct node));
printf("enter the name of the student:- ");
scanf("%s",(new->name));
printf("enter the roll no. of the student:-");
scanf("%d",&(new->rollno));
printf("enter the cgpa of the student:-");
scanf("%f",&(new->cgpa));
new->link=head;
struct node* ptr;

	if(head==NULL)
	{
	head=new;
	head->link=head;
	}

	else if(head->link==head)
	{
	head->link=new;
	new->link=head;
	head=new;
	}
	else
	{
	ptr=head->link;
	while(ptr->link!=head)
	{
	ptr=ptr->link;
	}
	ptr->link=new;
	new->link=head;
	head=new;
	}
return head;
}


void searchrollno(struct node* head , int r)
{
if(head==NULL)
	{
	printf("The linked list is empty!!\n");
	}

else if(head->link=head)
{
if(head->rollno==r)
{
		printf("The Record is = >>\n");
		printf("%s\n",head->name);
		printf("%d\n",head->rollno);
		printf("%f\n\n",head->cgpa);
}
else
printf("Record not found\n");

}
	else
	{
	int ci=0;
	struct node* ptr;
	ptr=head->link;
	if(head->rollno==r)
	{
		printf("The Record is = >>\n");
		printf("%s\n",head->name);
		printf("%d\n",head->rollno);
		printf("%f\n\n",head->cgpa);
		ci=1;

	}

		while(ci!=1 && ptr->rollno!=r && ptr!=head)
		{
		ptr=ptr->link;
		}
		if(ptr!=head)
		{
		printf("The Record is = >>\n");
		printf("%s\n",ptr->name);
		printf("%d\n",ptr->rollno);
		printf("%f\n\n",ptr->cgpa);
		}
		else
		printf("Node not found!!!\n");
	}

}

struct node* insertinbetween(struct node* head)
{
int count=0,c;
struct node* new=(struct node* )malloc(sizeof(struct node));
printf("Enter the name of the student:- ");
scanf("%s",(new->name));
printf("Enter the roll no. of the student:-");
scanf("%d",&(new->rollno));
printf("Enter the cgpa of the student:-");
scanf("%f",&(new->cgpa));
new->link=head;
struct node* ptr;
struct node* ptr1;
printf("Enter the node where you want to add a new node:- ");
scanf("%d",&c);
	if(head==NULL)
	{
	printf("The linked list is empty");
	}

	else
	{
	ptr=head;
	count=1;
	while(count!=c && ptr!=head)
	{
	ptr=ptr->link;
	count++;
	}
	if(ptr==NULL)
	printf("Node not found");
	else
	{
	ptr1=ptr->link;
	ptr->link=new;
	new->link=ptr1;

	}
	}
return head;
}


void searchname(struct node* head, char* s)
{
if(head==NULL)
{
printf("The record not found!!!\n");
}

else if(head->link==head)
{
int i,co=0;
	for(i=0;s[i]!='\0';i++)
	{
		if(head->name[i]!=s[i])
		{
		printf("The Record is not found!!\n");
		co=1;
		break;
		}

	}
if(co==0)
printf("Record found at node number 1\n");

}

else
{
ptr=head->link;
int no=1,ci=0,i;

for(i=0;s[i]!='\0';i++)
{
	if(head->name[i]!=s[i])
	{
	break;
	}

}
if(s[i]=='\0')
{
printf("The record found at head node!!!\n");
ci=1;
}

while(ci!=1 && ptr!=head)
{
int i,co=0;
	for(i=0;s[i]!='\0';i++)
	{
		if(ptr->name[i]!=s[i])
		{
		co=1;
		break;
		}

	}
if(co==1 && ci==0)
{
ptr=ptr->link;
no++;
}
else
{
printf("Record found at node number %d \n",no+1);
break;
}
}

}

}

void searchcgpa(struct node* head,float p){

if(head==NULL)
{
printf("The record not found!!!\n");
}

else if(head->link==head)
{
	if(head->cgpa==p)
	{
	printf("Record found at node number 1\n");

	}
	else{
	printf("Record not found\n");
}
}

else{
int co=0,no=1,ci=0;
ptr=head->link;
if(head->cgpa==p)
{
printf("Record found at node number 1");
ci=1;
}
while(ci!=1 && ptr!=head)
{
	if(ptr->cgpa==p)
	{
	printf("Record found at node number %d \n",no+1);
	co++;
	break;
	}
	else
	{
	ptr=ptr->link;
	no++;
	}
}
if(co==0 && ci==0)
printf("record not found\n");

}
}




struct node* deleteatfront(struct node* head)
{
	if(head==NULL)
	{
	printf("the linked list is empty\n");
	}

	else if(head->link==head)
	{
	head=NULL;
	}

	else
	{
	struct node* ptr=head->link;
	while(ptr->link!=head)
	{
	ptr=ptr->link;
	}
	ptr->link=head->link;
	head=head->link;
	}
return head;
}


struct node* deleteatend(struct node* head)
{
	if(head==NULL)
	{
	printf("the linked list is empty\n");
	}

	else if(head->link==head)
	{
	head=NULL;
	}

	else
	{
	struct node* ptr;
	ptr=head;
	while((ptr->link)->link!=head)
	{
	ptr=ptr->link;
	}
	ptr->link=head;
	}
return head;
}
struct node* deleteinbetween(struct node* head , int pos)
{
if(head==NULL)
printf("The linked list is empty!!\n");

else if(pos==1 && head->link==NULL)
{
return NULL;
}
else
{
if(pos==1)
{
	return head->link;
}
else
{
	ptr=head;
	int count=1;
	while(count+1!=pos)
	{
	ptr=ptr->link;
	count++;
	}

	ptr->link=(ptr->link)->link;
}
}
return head;
}

void main()
{
struct node* head=NULL;
int ch,y=1,r;
float cg;
char s1[20];
do
{

printf("1.Insert an element in the front of circular linked list\n");
printf("2.Insert an element in the end of circular linked list\n");
printf("3.Delete an element from the front of the circular linked list\n");
printf("4.Delete an element from the end of the circular linked list\n");
printf("5.Display the circular linked list\n");
printf("6.Search for a record by Roll no.\n");
printf("7.Search for a record by Name.\n");
printf("8.Search for a record by CGPA.\n");
printf("9.Exit\n");
printf("10.Intertion in between nodes\n");
printf("11.Deletion in between nodes\n");


printf("Enter your choice : -");
scanf("%d",&ch);
switch(ch)
{
	case 1:
	head=insertatfront(head);
	break;

	case 2:
	head=insertatend(head);
	break;

	case 3:
	head=deleteatfront(head);
	break;

	case 4:
	head=deleteatend(head);
	break;
case 11:
printf("Enter pos to delete:-");
scanf("%d",&r);
deleteinbetween(head,r);
	case 5:
	display(head);
	break;

	case 6:
	printf("enter the roll no. you want the search:-");
	scanf("%d",&r);
	searchrollno(head,r);
	break;

	case 7:
	printf("enter the Name you want the search:-");
	scanf("%s",&s1);
	searchname(head,s1);
	break;

	case 8:
	printf("enter the CGPA you want the search:-");
	scanf("%f",&cg);
	searchcgpa(head,cg);
	break;
	case 10:
	head=insertinbetween(head);
	break;

case 9:
break;
	default:
	printf("you entered the wrong choice\n");
	break;
}

}
while(ch!=9);
}
