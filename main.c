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
      if (!(((mob[j] - '0') >= 0) && ((mob[j] - '0') <= 9))) {
        ch = false;
        break;
      }
    }
  }
  return ch;
}

void registerUser(company *newbie, char *cname) {
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
}

int authenticate(bool chc, char *getKey) {
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
  registerUser(newbie, cname);

  FILE *file = fopen(".databaseC", "a");
  if (file != NULL) {
    fwrite(newbie, sizeof(company), 1, file);
    fclose(file);
  }

  return;
}

int makeQuestionPaper(ques Q[]) {
	system("clear");
	printf("\nSetting a New Question Paper\n");
	printf("\n-------------------------------------------\n\n");
	printf("Enter number of questions  :  ");
	int k = 0,countQues;
	scanf("%d",&countQues);

	for (;k<countQues;k++) {
		system("clear");
		printf("\nQuestion Number - %d\n",k+1);
		printf("\n-------------------------------------------\n\n");
		printf("Enter the question  (press ? to end question):  \n");
		int cp  = 0;
		char c;
		while((c = getchar() )!= '?' && cp<MAXLENQB) {
			Q[k].question[cp++] = c;
		}
		Q[k].quesno = k;
		int o = 0;
		for (;o<4;o++) {
			printf("\nEnter Option %d : ",o+1);
			int cp  = 0;
			while((c = getchar() )!= ';' && cp<MAXLENQB) {
				Q[k].opt[o][cp++] = c;
			}
		}
		printf("\nEnter correct answer (option no) for this question  :  ");
		scanf("%d",&Q[k].correctAns);
	}
	// TO-DO 
	// Add a preview
	return countQues;
}

void makeexam(company *user) {
	system("clear");
	printf("Making an exam\n");
	printf("\n-------------------------------------------\n\n");
	exam *newexam = (exam *)malloc(sizeof(exam));
	FILE *file = fopen(".databaseExam","rb");
	while(!feof(file)) {
		fread(newexam,sizeof(exam),1,file);
		if(strcmp(user->emailid,newexam->Cmpy.emailid) == 0) {
			printf("\nYou have already made an exam ....Go to Question Bank for changes\n");
			fclose(file);
			sleep(3);
			return ;
		}
	}
	fclose(file);

	printf("\nEnter coursename of the Exam  :  ");
	fgets(newexam->coursename, MAXLEN, stdin);
  	fgets(newexam->coursename, MAXLEN, stdin);

  	//Update Course -IDs
  	file = fopen(".lastSeenCID","rb");
  	int lCID = 0;
  	if(file!=NULL) {
  		fread(&lCID,sizeof(int),1,file);
  	}
  	fclose(file);
  	lCID++;

  	file = fopen(".lastSeenCID","w");
  	if (file != NULL) {
  		fwrite(&lCID,sizeof(int),1,file);
  		fclose(file);
  	}

  	newexam->courseID = lCID;
  	newexam->Cmpy = *user;

  	printf("\nEnter number of timeslots for the exam  :  ");
  	scanf("%d",&newexam->countTslots);
  	int k = 1;
  	char tSlot[MAXT];
  	for (;k!=newexam->countTslots+1;k++) {
  		printf("\nEnter start time for time slot %d (HH:MM format and in 24-hour type):  ",k);
  		scanf("%s",tSlot);
  		strcpy(newexam->tS[k-1].starttime,tSlot);
  		printf("\nEnter end time for time slot %d (HH:MM format and in 24-hour type):  ",k);
  		scanf("%s",tSlot);
  		strcpy(newexam->tS[k-1].endtime,tSlot);
  		// TO-DO
  		// Add Validity Check
  		// Find duration of exam
  	}
  	newexam->countQues = makeQuestionPaper(newexam->Q);

  	//write exam to a file
  	file = fopen(".databaseExam","a");
  	if (file != NULL) {
  		fwrite(newexam,sizeof(exam),1,file);
  		fclose(file);
  	}

  	printf("Done making question paper with %d questions",newexam->countQues);
  	printf("\n");
  	sleep(2);
  	return;
}

// void ViewQB(company *user) {
// 	system("clear");

// }

// void questionbank(company *user) {
// 	while(1) {
// 		system("clear");
// 		printf("\n1.Edit Question Paper");
// 		printf("\n2.View Question Paper");
// 		printf("\n3.Go Back");
// 		printf("\nChoose an option from the above  :  ");
// 		int ch;
// 		scanf("%d",&ch);
// 		switch(ch) {
// 			case 1 : break;
// 			case 2 : break;
// 			case 3 : return ;
// 			default :printf("\nEnter a Valid Choice");
// 					sleep(2);
// 		}
// 	}
// 	return ;
// }

void homepageC(company *user) {
  bool done = false;

  while(1) {
    system("clear");
    if (!done) {
      done = !done;
      printf("\nLogin Successful\n");
    }
    printf("\n1.View Lists of Students enrolled for the exam");
    printf("\n2.Open Question Bank");
    printf("\n3.make an Exam");
    printf("\n4.Change Password");
    printf("\n5.Log out");
    printf("\nEnter a choice from the above  :  ");
    int choice;
    
    scanf("%d",&choice);
    switch (choice) {
      case VL: 
              break;
      case QB: //questionbank(user);break;
      case TE : makeexam(user);
              break;
      case CP : 
              break;
      case LO: return ;
      default :"\nPlease Enter a Valid Choice";
      			sleep(2);
    }
  }
  return;
}

void loginCompany() {
  system("clear");
  char em[MAXLEN];

  printf("Login as a Company\n");
  printf("\n-------------------------------------------\n\n");

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
  int status = authenticate(chc, getKey);
  if (status == -1)
    return;
  return homepageC(user);
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

  registerUser(&newbie->stud, sname);
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

  printf("Login as a Sudent\n");
  printf("\n-------------------------------------------\n\n");
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
  int status = authenticate(chc, getKey);
  if (status == -1)
    return;
  return homepageS();
}

void loginAdmin() {
  system("clear");
  char *adminPassword = "aimskyhigh";
  bool chc = true;
  int status = authenticate(chc, adminPassword);
  if (status == -1)
    return;
  // return homepageA(); 
}

int printWelcome() {
  int choice;
  system("clear");
  printf("Welcome to EMS...");
  printf("\n1.Sign Up as a Company or University");
  printf("\n2.Sign Up as a Student");
  printf("\n3.Login as a Company");
  printf("\n4.Login as a Student");
  printf("\n5.Login as Admin");
  printf("\n6.Exit\nChoose an Option from the above  :  ");
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

        case AD:
          loginAdmin();
          break;

        case EXIT:
          printf("\nGood Bye from EMS..\n");
          return;

        default:
          printf("\nPlease Enter Valid Chocie");
    }
  }
}