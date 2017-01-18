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

char * simplify(char str[]) {
	int i,len = strlen(str);
	for (i = 0;i<len;i++) {
		if (str[i] == '\n' || str[i] == '\t' || str[i] >122 || (str[i] < 65 && (str[i]<48 || str[i] > 57))) 
			str[i] = ' ';
	}
	return str;
}

void registerUser(company *newbie, char *cname) {
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
  // newbie->revision = 1;
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

void addQuestion(ques *Q) {
	printf("Enter the question  (press ? to end question):  \n");
	int cp  = 0;
	char c;
	while((c = getchar() )!= '?' && cp<MAXLENQB) {
		Q->question[cp++] = c;
	}

	int o = 0;
	for (;o<4;o++) {
		printf("\nEnter Option %d : ",o+1);
		int cp  = 0;
		while((c = getchar() )!= ';' && cp<MAXLENQB) {
			Q->opt[o][cp++] = c;
		}
		while(cp<20) {
			Q->opt[o][cp++] = ' ';	
		}
	}
	printf("\nEnter correct answer (option no) for this question  :  ");
	scanf("%d",&Q->correctAns);

	// return Q;
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
		addQuestion(&Q[k]);
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

int checkQB(company *user,exam *lsexam) {
	system("clear");
	printf("Question Bank");
	printf("\n-------------------------------------------\n\n");
	FILE *file = fopen(".databaseExam","rb+");
	bool chc = false;
	if (file != NULL) {
		while(!feof(file)) {
			fread(lsexam,sizeof(exam),1,file);
			if (strcmp(lsexam->Cmpy.emailid,user->emailid) ==0) {
				chc = true;
			}
		}
	}
	if (!chc) {
		printf("\nYou didn't Set a question paper yet...Go to Set an Exam");
		printf("\n");
		sleep(2);
		return -1;
	}
	return 0;
}

int editQB(company *user) {
	system("clear");
	printf("Question Bank");
	printf("\n-------------------------------------------\n\n");
	
	exam *lsexam = (exam *)malloc(sizeof(exam));
	FILE *file = fopen(".databaseExam","rb+");
	
	bool chc = false;
	if (file != NULL) {
		while(!feof(file)) {
			fread(lsexam,sizeof(exam),1,file);
			if (strcmp(lsexam->Cmpy.emailid,user->emailid) ==0) {
				chc = true;
				break;
			}
		}
	} else {
		return -1;
	}

	if (!chc) {
		printf("\nYou didn't Set a question paper yet...Go to Set an Exam");
		printf("\n");
		sleep(2);
		return -1;
	}
	int k;
	printf("\nEnter the question number you want to change  :  ");
	scanf("%d",&k);
	if (k>lsexam->countQues) {
		printf("\nQuestion number %d not found",k);
		sleep(2);
		return -1;
	}
	system("clear");
	printf("\nQuestion Number - %d\n",k);
	printf("\n-------------------------------------------\n\n");
	ques QQ;
	addQuestion(&QQ);
	lsexam->Q[k-1] = QQ;
	printf("%s",lsexam->Q[k-1].question);

	fseek(file,-sizeof(exam),SEEK_CUR);
	fwrite(lsexam,sizeof(exam),1,file);
	fclose(file);

	printf("\n");
	system("clear");
	printf("Question Paper Updated Successfully\n");
	sleep(2);
	return 0;
}

int viewQB(company *user) {
	exam *lsexam = (exam *)malloc(sizeof(exam));
	system("clear");
	printf("Question Bank");
	printf("\n-------------------------------------------\n\n");
	FILE *file = fopen(".databaseExam","rb+");
	bool chc = false;
	if (file != NULL) {
		while(!feof(file)) {
			fread(lsexam,sizeof(exam),1,file);
			if (strcmp(lsexam->Cmpy.emailid,user->emailid) ==0) {
				chc = true;
			}
		}
	}
	if (!chc) {
		printf("\nYou didn't Set a question paper yet...Go to Set an Exam");
		printf("\n");
		sleep(2);
		fclose(file);
		return -1;
	}
	fclose(file);
	int k;
	for (k = 0;k<lsexam->countQues;k++) {
		printf("\n\nQuestion %d.",k+1);
		printf("\n%s?",simplify(lsexam->Q[k].question));
		int o = 0;
		for (;o<4;o++)
			printf("\n%c)%s",'A'+o,simplify(lsexam->Q[k].opt[o]));
	}
	char c;
	printf("\nPress Any Key to go back");
	fflush(stdin);
	while((c = getchar()) != '\n');
	getchar();
	return 0;
}

void questionbank(company *user) {
	while(1) {
		system("clear");
		printf("Question Bank");
		printf("\n-------------------------------------------\n\n");
		printf("\n1.Edit Question Paper");
		printf("\n2.View Question Paper");
		printf("\n3.Go Back");
		printf("\nChoose an option from the above  :  ");
		int ch,k;
		scanf("%d",&ch);
		switch(ch) {
			case 1 : k = editQB(user);
					if(k == -1) return ;break;
			case 2 : k = viewQB(user);
					if (k == -1) return ;break;
			case 3 : return ;
			default :printf("\nEnter a Valid Choice");
					sleep(2);
		}
	}
	return ;
}

void changePassword(company *user,char filename[]) {
	system("clear");
	printf("Changing Password(Security Settings)");
	printf("\n-------------------------------------------\n\n");
	company *u = (company *)malloc(sizeof(company));
	FILE *file = fopen(filename,"rb+");
	if (file != NULL) {
		while(!feof(file)) {
			fread(u,sizeof(company),1,file);
			if (strcmp(u->emailid,user->emailid) == 0) {
				char *t1, *t2;
				do {
			  		 // encrypted password feature
				    t1 = getpass("\nSet your new Password (Password won't be shown to maintain "
				                 "Secrecy) :  ");
				    t2 = getpass("\nRe-Type your new Password again to Confirm :  ");
				} while (strcmp(t1, t2) != 0);
				strcpy(u->pswrd,t1);
				fseek(file,-sizeof(company),SEEK_CUR);
				fwrite(u,sizeof(company),1,file);
				fclose(file);
				system("clear");
				printf("\nPassword Updated Successfully");
				printf("\n");
				sleep(2);
				return ;
			}
		}
	}
	printf("\nError While Changing Password...Please try again");
	return ;
}

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
    printf("\n3.Set an Exam");
    printf("\n4.Change Password");
    printf("\n5.Log out");
    printf("\nEnter a choice from the above  :  ");
    int choice;
    
    scanf("%d",&choice);
    switch (choice) {
      case VL: 
              break;
      case QB: questionbank(user);break;
      case TE : makeexam(user);
              break;
      case CP : changePassword(user,".databaseC");
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
    if (strcmp(user->emailid, em) == 0 ) {
      getKey = user->pswrd;
      chc = true;
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

void enroll4exam(student *user) {
	system("clear");

	char cname[MAXLEN];
	printf("\nEnter name of the course for exam  :  ");
	fgets(cname,MAXLEN,stdin);
	fgets(cname,MAXLEN,stdin);
	
	exam *lsexam = (exam *)malloc(sizeof(exam));
	FILE *file = fopen(".databaseExam","rb");
	bool chc = false;
	if (file != NULL) {
		while(!feof(file)) {
			fread(lsexam,sizeof(exam),1,file);
			if (strcmp(lsexam->coursename,cname) ==0) {
				chc = true;
			}
		}
	}
	if (!chc) {
		printf("\nSorry ..We couldn't find any course that matches your choice");
		printf("\nPlease Try after some time");
		printf("\n");
		fclose(file);
		sleep(2);
		return ;
	}
	fclose(file);

	lsexam->st[lsexam->countSt] = *user;
	int k = 0;
	for (;k<lsexam->countTslots;k++) {
		printf("\nTime Slot %d",k+1);
		printf("\nStart Time - %s , End Time - %s",lsexam->tS[k].starttime,lsexam->tS[k].endtime);
		printf("\n---------------------o-------------------------");
	}
	printf("\n Choose any time slot from the above  :  ");
	scanf("%d",&k);
	lsexam->st[lsexam->countSt++].chosenSlot = k;

	file = fopen(".databaseExam", "a");
	  if (file != NULL) {
	    fwrite(lsexam, sizeof(exam), 1, file);
	    fclose(file);
	  }
	printf("\n");
	system("clear");
	printf("Student Successfully Enrolled for the exam");
	sleep(2);
	return;
}

void homepageS(student *user) {
  bool done = false;

  while(1) {
    system("clear");
    if (!done) {
      done = !done;
      printf("\nLogin Successful\n");
    }
    printf("\n1.View List of Courses enrolled for the exam");
    printf("\n2.Enroll for an exam");
    printf("\n3.Start Exam");
    printf("\n4.Change Password");
    printf("\n5.Log out");
    printf("\nEnter a choice from the above  :  ");
    int choice;
    
    scanf("%d",&choice);
    switch (choice) {
      case 1: /*viewListC(user);*/
              break;
      case 2: //enroll4exam(user);break;
      case 3 : /*startexam(user);*/
              break;
      case 4 : changePassword(&user->stud,".databaseS");
              break;
      case 5: return ;
      default :"\nPlease Enter a Valid Choice";
      			sleep(2);
    }
  }
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
  return homepageS(user);
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