#include "headers.h"

void run();

int main(int argv, char **argc) {
  run();
  return 0;
}

bool checkValiditymob(char *mob) {
	int j;
	bool ch = true;
	if (strlen(mob) != 10) {
		ch = false;
	} else {
	    for (j = 0; j < strlen(mob); j++) {
	      if(!(((mob[j] - '0') >= 0) && ((mob[j] - '0') <= 9))) {
	        ch = false;
	        break;
	      }
	    }
	}
    return ch;
}

void registerUser(company* newbie,char *cname) {
  // company* newbie = (company *)malloc(sizeof(company));
  strcpy(newbie->name, cname);

  printf("\nEnter your eMail-ID  :  ");
  scanf("%s", newbie->emailid);

  bool ch = true;
  printf("\nEnter your Contact Number  :  ");

  do {
    if (!ch)
      printf("\nPlease Enter a Valid Contact Number  :  ");
    scanf("%s", newbie->mobno);
    ch = checkValiditymob(newbie->mobno);
  } while (!ch);

  printf("\nEnter your Address  :  ");
  fgets(newbie->address, MAXLEN, stdin);
  fgets(newbie->address, MAXLEN, stdin);

  char *t1, *t2;
  do {
    // encrypted password feature
    t1 = getpass("\nSet your Password (Password won't be shown to maintain "
                 "Secrecy) :  ");
    t2 = getpass("\nRe-Type your Password again to Confirm :  ");
  } while (strcmp(t1, t2) != 0);

  strcpy(newbie->pswrd, t1);
  // return newbie;
}

int authenticate(bool chc,char* getKey) {
  if (!chc) {
    printf("User not registered\n");
    printf("\nRe-Directed to Welcome Page");
    printf("\n");
    sleep(3);
    return -1;
  }

  char *t1 = getpass("\nEnter your Password  : ");
  int k = 1;
  while (strcmp(t1, getKey) != 0) {
    t1 = getpass("password entered didn't match...Please try again  : ");
    k++;
    if (k >= 3) {
      printf("\nAuthentication Failed");
      printf("\nRe-Directed to Welcome Page");
      printf("\n");
      sleep(3);
      return -1;
    }
  }
  return 0;
}

void registerCompany() {
  system("clear");

  printf("Sign Up as a Company/University\n");
  printf("\n-------------------------------------------\n\n");
  printf("Please Enter following details");
  printf("\nEnter name of your company  :  ");

  char cname[MAXLEN];
  fgets(cname, MAXLEN, stdin);
  fgets(cname, MAXLEN, stdin);

  company *newbie = (company *)malloc(sizeof(company));

  // Check in database file ,if company is Already registered
  FILE *cf = fopen(".databaseC", "rb");
  while (!feof(cf)) {
    fread(newbie, sizeof(company), 1, cf);
    if (strcmp(newbie->name, cname) == 0) {
      fclose(cf);
      free(newbie);
      printf("\nCompany already registered \
    				\nRe-Directed to Welcome Page");
      printf("\n");
      sleep(3);
      return;
    }
  }
  fclose(cf);
  registerUser(newbie,cname);

  FILE *file = fopen(".databaseC", "a");
  if (file != NULL) {
    fwrite(newbie, sizeof(company), 1, file);
    fclose(file);
  }

  return;
}

void homepageC() {
  system("clear");
  printf("\nLogin Successful\n");
  return;
}

void loginCompany() {
  system("clear");
  char em[MAXLEN];
  printf("Enter your eMail-ID  :  ");
  scanf("%s", em);

  char *getKey;
  bool chc = false;
  company *user = (company *)malloc(sizeof(company));

  FILE *cf = fopen(".databaseC", "rb");
  while (!feof(cf)) {
    fread(user, sizeof(company), 1, cf);
    if (strcmp(user->emailid, em) == 0) {
      getKey = user->pswrd;
      chc = true;
      break;
    }
  }

  fclose(cf);
  int status = authenticate(chc,getKey);
  if (status == -1) 
    return;
  return homepageC();
}

void registerStudent() {
  system("clear");
  char sname[MAXLEN];

  printf("Sign Up as a Sudent\n");
  printf("\n-------------------------------------------\n\n");
  printf("Please Enter following details");
  printf("\nEnter your name  :  ");

  fgets(sname, MAXLEN, stdin);
  fgets(sname, MAXLEN, stdin);

  student *newbie = (student *)malloc(sizeof(student));

  // Check in database file ,if student is Already registered
  FILE *cf = fopen(".databaseS", "rb");
  while (!feof(cf)) {
    fread(newbie, sizeof(student), 1, cf);
    printf("%s\n", newbie->stud.name);
    if (strcmp(newbie->stud.name, sname) == 0) {
      fclose(cf);
      free(newbie);
      printf("\nStudent already registered \
    				\nRe-Directed to Welcome Page");
      printf("\n");
      sleep(3);
      return;
    }
  }
  fclose(cf);

  registerUser(&newbie->stud,sname);
  printf("\nEnter your Roll-No  :  ");
  scanf("%s", newbie->rollno);

  FILE *file = fopen(".databaseS", "a");
  if (file != NULL) {
    fwrite(newbie, sizeof(student), 1, file);
    fclose(file);
  }

  return;
}

void homepageS() {
  system("clear");
  printf("\nLogin Successful\n");
  return;
}

void loginStudent() {
  system("clear");
  char em[MAXLEN];
  printf("Enter your eMail-ID  :  ");
  scanf("%s", em);

  char *getKey;
  bool chc = false;
  student *user = (student *)malloc(sizeof(student));

  FILE *cf = fopen(".databaseS", "rb");
  while (!feof(cf)) {
    fread(user, sizeof(student), 1, cf);
    if (strcmp(user->stud.emailid, em) == 0) {
      getKey = user->stud.pswrd;
      chc = true;
      break;
    }
  }

  fclose(cf);
  int status = authenticate(chc,getKey);
  if (status == -1) 
    return;
  return homepageS();
}

int printWelcome() {
  int choice;
  system("clear");
  printf("Welcome to EMS...");
  printf("\n1.Sign Up as a Company or University");
  printf("\n2.Sign Up as a Student");
  printf("\n3.Login as a Company");
  printf("\n4.Login as a Student");
  printf("\n5.Exit\nChoose an Option from the above  :  ");
  scanf("%d", &choice);
  return choice;
}

void run() {
  int choice;
  while (1) {
    choice = printWelcome();

    switch (choice) {
	    case RC:
	      registerCompany();
	      break;

	    case RS:
	      registerStudent();
	      break;

	    case LC:
	      loginCompany();
	      break;

	    case LS:
	      loginStudent();
	      break;

	    case EXIT:
	      printf("\nGood Bye from EMS..\n");
	      return;

	    default:
	      printf("\nPlease Enter Valid Chocie");
    }
  }
}