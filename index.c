#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <fstream>
// #include <time.h>
#include <unistd.h>
// #include <conio.h>

#define MAXLEN 30

/// Enumerate Choices ///
enum CHOICE {
	RC = 1,
	RS,
	LC,
	LS,
	EXIT
};

/// C doesn't support bool .So this is a Custom bool type ///
typedef enum { false, true } bool;

struct _company {
	int id;
	char name[MAXLEN];
	char emailid[MAXLEN];
	char address[MAXLEN];
	char pswrd[MAXLEN];
	//TO-DO 
	//char *AboutMe;
};

typedef struct _company company;

void registerCompany() 
{
	system("clear");
	char cname[MAXLEN];

	printf("Sign Up as a Company/University\n");
	printf("\n-------------------------------------------\n\n");
	printf("Please Enter following details");
	printf("\nEnter name of your company  :  ");

	fgets(cname,MAXLEN,stdin);
	fgets(cname,MAXLEN,stdin);

	company* newbie =(company *) malloc(sizeof(company));

	// Check in database file ,if company is Already registered
	FILE * cf= fopen("databaseC", "rb");
    while (!feof(cf)) {
        fread(newbie, sizeof(company), 1, cf);
        printf("%s\n",newbie->name);
    	if (strcmp(newbie->name,cname) == 0) {
    		fclose(cf);		
    		free(newbie);
    		printf("\nCompany already registered \
    				\nRe-Directed to Login Page");
    		printf("\n");
    		sleep(3);
    		return ;
    	}	
    }
    fclose(cf);

	strcpy(newbie->name,cname);

	printf("\nEnter your eMail-ID  :  ");
	scanf("%s",newbie->emailid);

	printf("\nEnter your Address  :  ");
	fgets(newbie->address,MAXLEN,stdin);
	fgets(newbie->address,MAXLEN,stdin);

	char *t1,*t2;
	do {
		// encrypted password feature
		t1 = getpass("\nSet your Password (Password won't be shown to maintain Secrecy) :  ");
		t2 = getpass("\nRe-Type your Password again to Confirm :  ");
			break;
	} while(strcmp(t1,t2) == 0);

	strcpy(newbie->pswrd,t1);

	FILE * file= fopen("databaseC", "a");
	if (file != NULL) {
	    fwrite(newbie, sizeof(company), 1, file);
	    fclose(file);
	}

	return;
}

void registerStudent()
{
	
}

int printWelcome()   // Use reference to avoid multiple local variables
{
	int choice;
	system("clear");
	printf("Welcome to EMS...");
	printf("\n1.Sign Up as a Company or University");
	printf("\n2.Sign Up as a Student");
	printf("\n3.Login as a Company");
	printf("\n4.Login as a Student");
	printf("\n5.Exit\nChoose an Option from the above  :  ");
	scanf("%d",&choice);
	return choice;
}

void run()
{
	int choice;
	while (1) {
		choice = printWelcome();

		switch (choice) {
			case RC  : registerCompany();
					   break;

			case RS  : "rs";
					   break;

			case LC  : "rc";
					   break;

			case LS  : "rs";
					   break;

			case EXIT: printf("\nGood Bye from EMS..\n");
					   return ;
			
			default : "\nPlease Enter Valid Chocie";		
		}
	}
}

struct date {
    char day[80];
    int month;
    int year;
};

int main(int argv,char **argc) 
{
	run();
	// struct date *object=malloc(sizeof(struct date));
	// strcpy(object->day,"Good day");
	// object->month=6;
	// object->year=2013;
	// FILE * file= fopen("output", "a");
	// if (file != NULL) {
	//     fwrite(object, sizeof(struct date), 1, file);
	//     fclose(file);
	// }

	   //  struct date *object2=malloc(sizeof(struct date));
    // FILE * file= fopen("output", "rb");
    // if (file != NULL) {
    //     fread(object2, sizeof(struct date), 1, file);
    //     fclose(file);
    // }
    // printf("%s/%d/%d\n",object2->day,object2->month,object2->year);

	return 0;
}