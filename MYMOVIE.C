#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>

void addMovie();
void delMovie();
void showMovie();
void transaction();
void showTrans();
void showAvail();
void expressBook();
void showAllSeats();
void save(int, int, int,int ,int,int);

struct date d;

struct movie
{
 struct movie *l,*r;
 char mname[15];//movie name
 int seat[12];//respective movie seats
};
struct movie *s=NULL;//start

void admin()
{
 int ch,i=0;
 char password[5],p[5]="1q1q";//PASSWORD
 char c,choice;

 textcolor(YELLOW);
 clrscr();
 printf("Enter password to continue\n");
 scanf("%s",password);
 printf("password entered successfully");
 if(strcmp(password,p)!=0)//it will return 0 if same string
  {
   printf("Invalid password!!!\n");
   system("pause");
   admin();
  }
 do
 {
  clrscr();
  printf("Enter\n1.Add a movie\n2.Delete a movie\n3.Show all movies\n4.See full transaction history\n");
  scanf("%d",&ch);

  switch(ch)
  {
   case 1:
	clrscr();
	addMovie();
	break;
   case 2:
	clrscr();
	delMovie();
	break;
   case 3:
	clrscr();
	showMovie();
	break;

   case 4:
	clrscr();
	transaction();
   default:
	printf("Invalid choice!\n");
  }
 printf("\n Press Y for Admin menu \n Any other key for Main menu\n");
 choice=getch();
 }while(choice=='y'||choice=='Y');
}


void addMovie()
{
 int i;
 char name[15];
 struct movie *temp;
 textcolor(GREEN);
 temp=(struct movie *)malloc(sizeof(struct movie));
 printf("Enter movie name\n");
 scanf("%s",name);
 strlwr(name);
 strcpy(temp->mname,name);
 temp->l=temp->r=NULL;
 for(i=0;i<12;i++)//marking seat 1 to indicate its available for every movie
  temp->seat[i]=1;
 if(s==NULL)
 {
  printf("Adding first movie name\n");
  s=temp;
 }
 else
 {
  s->l=temp;
  temp->r=s;
  s=temp;
 }
 printf("Name addded successfully\n");
}


void delMovie()
{
 char name[20];
 struct movie *p;
 showMovie();
 p=s;
 if(p==NULL)
 printf("No movie added\n");

 else
 {
  printf("Enter movie name to be deleted\n");
  scanf("%s",name);
  strlwr(name);//converts name to full lower case

  while(strcmp(p->mname,name)!=0)//searching name
  {
   p=p->r;
   if(p==NULL)//when p reaches
    break;
  }
  if(p==NULL)
   {
    printf("Movie Not found\n");
   }
  else
  {
   if(p==s)//if first node
   {
    s=s->r;
    if(s!=NULL)//first but not the only one
     s->l=NULL;
   }
   else
   {
    if(p->r==NULL)//if last node
      (p->l)->r=NULL;

    else
    {
     (p->l)->r=p->r;
     (p->r)->l=p->l;
    }
   }
   printf("Movie deleted successfully\n");
  }
 }
}

void transaction()
{
 FILE *fptr;
 clrscr();
 fptr=(fopen("movie.txt","r"));
 if(fptr==NULL)
 printf("No transactions found!\n");
 else
  {
   int ch = getc(fptr);
   while (ch != EOF)
   {
    /* display contents of file on screen */
    putchar(ch);
    ch = getc(fptr);
    }
  if(feof(fptr)) //feof returnns non zero when end of file is reached
   printf("\n End of file reached.");
  else
   printf("\n Something went wrong.");
 }
 fclose(fptr);
}


void showMovie()
{
 int i=1;
 struct movie *p;
 p=s;
 if(s==NULL)
  printf("No movie found!\n");
 while(p!=NULL)
 {
  printf("%d. %s \n",i,p->mname);
  i++;
  p=p->r;
 }
}

void save(int d,int m,int y,int count,int amt,int extra_amt)
{
 FILE *fptr;
 fptr=fopen("movie.txt","a");
 if(fptr==NULL)
  printf("file not found\n");
 fprintf(fptr,"\n\n FOR DATE: %d-%d-%d\n",d,m,y);
 fprintf(fptr,"\n No. Of seats booked =%d",count);
 fprintf(fptr,"\n Movie ticket Total =%d",amt);
 fprintf(fptr,"\n Extra orders Total =%d",extra_amt);
 fprintf(fptr,"\n ------------------------");
 fprintf(fptr,"\n Total Amount       =%d",amt+extra_amt);
 fclose(fptr);
}

void customer()
{
 int ch;
 char choice;
 clrscr();
 printf("\n-----WELCOME TO WATCH-IT MOVIE THEATRE------\n");
 do{
  clrscr();
  printf("Please Enter \n1.Express Booking\n2.Show available seats \n3.Show seats arrangement\n" );
  scanf("%d",&ch);
  switch(ch)
  {
   case 1:
    clrscr();
    expressBook();
    break;

   case 2:
    clrscr();
    showAvail();
    break;

   case 3:
    clrscr();
    showAllSeats();
    break;

   default:
    clrscr();
    printf("Invalid statement \n");
  }
 printf("\n Press Y to show booking menu \n Any other key to return to previous menu\n");
 choice=getch();
 }while(choice=='y'||choice=='Y');
}


void expressBook()
{
 int no,i,j,seatNo=1,c,dd,mm,yy;
 int count=0,amt=0,extra_amt=0;
 int bookedseats[12];
 char name[15],ch;
 struct movie *p;
   getdate(&d);
 p=s;
 clrscr();
 if(p==NULL)
 {
  printf("No movie added to list!\n");
  return;
 }
 printf("Movies available are:\n");
 showMovie();
 printf("Enter the movie name to be booked\n");
 scanf("%s",name);
 strlwr(name);//converts name to full lower case
 while(strcmp(p->mname,name)!=0)//searching name
 {
  p=p->r;
  if(p==NULL)//end reached
   break;
 }
 if(p==NULL)
 {
  printf("Movie not found!\n");
  return;
 }
 do
 {
  clrscr();
  printf("\nCost per seat is Rs.100\n");
  printf("Total number of seats are 12 \nFrom 1-12.\n");
  printf("The seat arrangement is as follows: \n \n ");
  showAllSeats();

  printf("Enter the seat number you want to book\n");
  scanf("%d",&no);
  if(no<=12&&no>=1)
  {
   if(p->seat[no-1]==1)
   {
    printf("Seat booked succssfully\n");
    p->seat[no-1]=0;
    amt=amt+60;
    count++;
   }
   else
   {
    printf("Sorry the seat is already booked\n");
    printf("The available seats are\n");
    printf("-------------SCREEN-------------\n");
    for(i=0;i<3;i++)
    {
     for(j=0;j<2;j++,seatNo++)
     {
      if(p->seat[seatNo-1]==1)//seatNo-1 because the seat is a array from 0-11
       printf("(%d)",seatNo);
      else
       printf("(XX)");
     }
     printf("\t\t\t");
     for(j=0;j<2;j++,seatNo++)
     {
      if(p->seat[seatNo-1]==1)
       printf("(%d)",seatNo);
      else
       printf("(XX)");
     }
     printf("\n");
    }
    printf("------------ENTRY/EXIT------------\n");
   }
  }
  else
   printf("\n Invalid choice!\n");
  printf("\nPress Y to continue booking more tickets of the same movie\nElse press any other key");
  ch=getch();
 }while(ch=='Y'||ch=='y');
 clrscr();
 printf("Do want some extra side items\n");
 printf("Press Y if yes\n");
 ch=getch();
 if(ch=='Y'||ch=='y')
 {
  do
  {
   clrscr();
   printf("\nWe also serve the following items: \n \n");
   printf("\nITEMS\t \t      PRICE \n");
   printf("1.Diet Coke \t         25 \n");
   printf("2.Popcorn   \t         20 \n");
   printf("3.Packaged water 1l \t 20 \n");
   printf("\n \nPlease enter the serial number of your choice.\nEnter any other key if you don't wish anything\n  ");

   scanf("%d",&c);
   switch(c)
   {
    case 1:
	extra_amt=extra_amt+25;
	printf("Order for 1 Diet coke  successfully placed\n");
	break;

    case 2:
	extra_amt=extra_amt+25;
	printf("Order for 1 popcorn successfully placed\n");
	break;
    case 3:
	extra_amt=extra_amt+25;
	printf("Order for 1 water bottle successfully placed\n");
	break;
    default:
	printf("Invalid Choice\n") ;
   }
   printf(" Press Y if you wish to continue ordering\n Else press any other key.");
   ch=getch();
  }while(ch=='Y'||ch=='y');
 }
 clrscr();
 dd=d.da_day;
 mm=d.da_mon;
 yy=d.da_year;

 save(dd,mm,yy,count,amt,extra_amt);
 printf("\n---------------BILL----------------\n");
 printf("\n Date: %d/%d/%d ", d.da_day, d.da_mon, d.da_year);
 printf("\n No. Of seats booked \t \t=%d\n",count);

 printf("\n Movie ticket Total \t \t =%d",amt);
 printf("\n Extra orders Total \t \t =%d",extra_amt);
 printf("\n--------------------------------------");
 printf("\n Total Amount      \t \t  =%d",amt+extra_amt);
 printf("\n \n Please pay the amount at counter");
 printf("\n \n Enjoy your Movie \n Visit again \n \t :) :) :) ");

}



void showAllSeats()
{
	int i,j,seatNo=1;
	printf("Our threater map is \n");
	printf("------------SCREEN------------\n");
	for(i=0;i<3;i++)
	{
	 for(j=0;j<2;j++,seatNo++)
	  printf("(%d)",seatNo);
	 printf("\t\t\t");

	  for(j=0;j<2;j++,seatNo++)
	   printf("(%d)",seatNo);
	  printf("\n");
	 }
	 printf("------------ENTRY/EXIT--------------\n");
}


void showAvail()
{
 int i,j,k=1,seatNo=1;
 struct movie *p;
 p=s;
 if(p==NULL)
	 printf("No movies added!/n");
 else
 {
  printf("The available seats in all movies are\n ");
  while(p!=NULL)
  {
   printf("\n \n For %d. %s \n",k,p->mname);
  k++;
   printf("The available seats are\n");
     printf("-------------SCREEN-------------\n");
    for(i=0;i<3;i++)
    {
     for(j=0;j<2;j++,seatNo++)
     {
      if(p->seat[seatNo-1]==1)//seatNo-1 because the seat is a array from 0-11
       printf("(%d)",seatNo);
      else
       printf("(XX)");
     }
     printf("\t\t\t");
     for(j=0;j<2;j++,seatNo++)
     {
      if(p->seat[seatNo-1]==1)
       printf("(%d)",seatNo);
      else
       printf("(XX)");
     }
     printf("\n");
    }

  p=p->r;
  seatNo=1;//reset seat number to 1
  }
 }
}


int main()
{
 int ch,i;
 char choice;
 clrscr();
 textcolor(CYAN);



 do
 {
  clrscr();

  printf("Enter  \n1.Admin\n2.Customer\n");
  scanf("%d",&ch);
  switch(ch)
  {
   case 1:
	admin();
	break;
   case 2:
	customer();
	break;
   default:
	printf("Invalid statement\n");

  }
  printf("\n Press Y for main menu \n Any other key to EXIT\n");
  choice=getch();
 }while(choice=='y'||choice=='Y');
 return 0;
}

