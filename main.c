/* 
 * File:   main.c
 * Author: Adha Ranjith Kumar
 * Roll No: 15CS30002
 * Project : P14: Examination Management System
 * TA: Satendra Kumar
 * Created on January 16, 2017, 12:19 PM
 */

#include "headers.h"

// run is a function to provoke welcome page
void run();

int main(int argv, char **argc)
{
    // main function is generally an outer layer to a inner function call.
    run();
    return 0;
}

//Clang-Format 3.7 is applied in this directory to improve 
//indentation and fix whitespace issues.

//inline specifier to save the overhead of a function call.
//simp converts string to corresponding integer
inline int simp(char c[])
{
    int n = 0, i, len = strlen(c);
    for (i = 0; i < len; i++) {
        if (c[i] != ' ' && c[i] != '\n' && c[i] != ':')
            n = c[i] - '0' + 10 * n;
        if (c[i] == ':') {
            return n;
        }
    }
    return n;
}

//checks validity of mobile number
bool checkValiditymob(char *mob)
{
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

//removes non-ascii characters and vague characters
inline char *simplify(char str[])
{
    int i, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == '\n' || str[i] == '\t' || str[i] > 122
            || (str[i] < 65 && (str[i] < 48 || str[i] > 57)) && str[i]!='+')
            str[i] = ' ';
    }
    return str;
}

//checks validity of email-id
inline bool checkGmail(char *mail) {
    int i =0,len = strlen(mail);
    for (;i <len;i++) {
        if (mail[i]=='@') {
            if (!(i>0 && i<(len-5))) {
                return false;
            }
        } 
    }
    if (mail[len-1] == 'm' && mail[len-2] == 'o' && mail[len-3] == 'c' && mail[len-4] == '.') {
        return true;
    } else {
        return false;
    }
}

//for registering user 
//user can be a student or a company
void registerUser(company *newbie, char *cname)
{
    strcpy(newbie->name, cname);

    printf("\nEnter your eMail-ID  :  ");
    bool temp = true;
    do {
        scanf("%s", newbie->emailid);
        temp = checkGmail(newbie->emailid);
        if (!temp) {
            printf("\nPlease enter a Valid Email-ID  :  ");
        }
    }while(!temp);

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

//asks password using getpass and authenticates the user
int authenticate(bool chc, char *getKey)
{
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

//ADT for company's register user
void registerCompany()
{
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
    FILE *cf = fopen(".databasebin/.databaseC", "rb");
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

    FILE *file = fopen(".databasebin/.databaseC", "ab");
    if (file != NULL) {
        fwrite(newbie, sizeof(company), 1, file);
        fclose(file);
    }

    return;
}

//adds a question and fills in Q
void addQuestion(ques *Q)
{
    printf("Enter the question  (press ? to end question):  \n");
    int cp = 0;
    char c;
    while ((c = getchar()) != '?' && cp < MAXLENQB) {
        if (c == '\n')
            c = ' ';
        Q->question[cp++] = c;
    }

    int o = 0;
    for (; o < 4; o++) {
        printf("\nEnter Option %d : ", o + 1);
        int cp = 0;
        while ((c = getchar()) != ';' && cp < MAXLENQB) {
            if (c == '\n')
                c = ' ';
            Q->opt[o][cp++] = c;
        }
        while (cp < 20) {
            Q->opt[o][cp++] = ' ';
        }
    }
    printf("\nEnter correct answer (option no) for this question  :  ");
    scanf("%d", &Q->correctAns);
}

//Outer Layer for making a question paper
int makeQuestionPaper(ques Q[])
{
    system("clear");
    printf("\nSetting a New Question Paper\n");
    printf("\n-------------------------------------------\n\n");
    printf("Enter number of questions  :  ");
    int k = 0, countQues;
    scanf("%d", &countQues);

    for (; k < countQues; k++) {
        system("clear");
        printf("\nQuestion Number - %d\n", k + 1);
        printf("\n-------------------------------------------\n\n");
        addQuestion(&Q[k]);
    }
    return countQues;
}

//for making an exam by a company
void makeexam(company *user)
{
    system("clear");
    printf("Making an exam\n");
    printf("\n-------------------------------------------\n\n");
    exam *newexam = (exam *)malloc(sizeof(exam));
    FILE *file = fopen(".databasebin/.databaseExam", "rb");
    while (!feof(file)) {
        fread(newexam, sizeof(exam), 1, file);
        if (strcmp(user->emailid, newexam->Cmpy.emailid) == 0) {
            printf("\nYou have already made an exam ....Go to Question Bank "
                   "for changes\n");
            fclose(file);
            sleep(3);
            return;
        }
    }
    fclose(file);
    file = fopen(".databasebin/.databaseExam", "ab");
    printf("\nEnter coursename of the Exam  :  ");
    fgets(newexam->coursename, MAXLEN, stdin);
    fgets(newexam->coursename, MAXLEN, stdin);

    int i, len = strlen(newexam->coursename);
    for (i = 0; i < len; i++) {
        if (newexam->coursename[i] == '\n' || newexam->coursename[i] == '\t'
            || newexam->coursename[i] > 122 || (newexam->coursename[i] < 65))
            newexam->coursename[i] = ' ';
    }

    // Update Course -IDs
    FILE *fp = fopen(".databasebin/.lastSeenCID", "rb");
    int lCID = 0;
    if (fp != NULL) {
        fread(&lCID, sizeof(int), 1, fp);
    }
    fclose(fp);
    lCID++;

    fp = fopen(".databasebin/.lastSeenCID", "wb");
    if (fp != NULL) {
        fwrite(&lCID, sizeof(int), 1, fp);
        fclose(fp);
    }

    newexam->courseID = lCID;
    newexam->Cmpy = *user;

    printf("\nEnter number of timeslots for the exam  :  ");
    scanf("%d", &newexam->countTslots);
    int k = 1;
    char tSlot[MAXT];
    for (; k != newexam->countTslots + 1; k++) {
        printf("\nEnter Duration for %d slot (in hours) :  ",k);
        scanf("%Ld",&newexam->totaltime);
        printf("\nEnter start time for time slot %d (HH:MM format and in "
               "24-hour type):  ",
               k);
        scanf("%s", tSlot);
        strcpy(newexam->tS[k - 1].starttime, tSlot);
        printf("\nEnter end time for time slot %d (HH:MM format and in 24-hour "
               "type):  ",
               k);
        scanf("%s", tSlot);
        strcpy(newexam->tS[k - 1].endtime, tSlot);
        printf("\nEnter date of this slot  :  ");
        scanf("%s", newexam->tS[k - 1].date);
        printf("\nEnter month of this slot  :  ");
        scanf("%s", newexam->tS[k - 1].month);
        printf("\nEnter year of this slot  :  ");
        scanf("%s", newexam->tS[k - 1].year);
        // TO-DO
        // Add Validity Check
        // Find duration of exam
    }
    newexam->countQues = makeQuestionPaper(newexam->Q);

    printf("\nEnter marks weightage for correct answer ");
    scanf("%d", &newexam->markscorr);

    printf("\nEnter marks weightage for negative answer ");
    scanf("%d", &newexam->marksneg);

    if (file != NULL) {
        fwrite(newexam, sizeof(exam), 1, file);
        fclose(file);
    }

    printf("Done making question paper with %d questions", newexam->countQues);
    printf("\n");
    sleep(1);
    return;
}


//Company can also edit a question bank using edit QB
int editQB(company *user)
{
    system("clear");
    printf("Question Bank");
    printf("\n-------------------------------------------\n\n");

    exam *lsexam = (exam *)malloc(sizeof(exam));
    FILE *file = fopen(".databasebin/.databaseExam", "rb+");

    bool chc = false;
    if (file != NULL) {
        while (!feof(file)) {
            fread(lsexam, sizeof(exam), 1, file);
            if (strcmp(lsexam->Cmpy.emailid, user->emailid) == 0) {
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
        sleep(1);
        return -1;
    }
    int k;
    printf("\nEnter the question number you want to change  :  ");
    scanf("%d", &k);
    if (k > lsexam->countQues) {
        printf("\nQuestion number %d not found", k);
        sleep(1);
        return -1;
    }

    system("clear");
    printf("\nQuestion Number - %d\n", k);
    printf("\n-------------------------------------------\n\n");
    ques QQ;
    addQuestion(&QQ);
    lsexam->Q[k - 1] = QQ;
    printf("%s", lsexam->Q[k - 1].question);

    fseek(file, -sizeof(exam), SEEK_CUR);
    fwrite(lsexam, sizeof(exam), 1, file);
    fclose(file);

    printf("\n");
    system("clear");
    printf("Question Paper Updated Successfully\n");
    sleep(1);
    return 0;
}

//Company can also view the question paper using view QB
int viewQB(company *user)
{
    exam *lsexam = (exam *)malloc(sizeof(exam));
    system("clear");
    printf("Question Bank");
    printf("\n-------------------------------------------\n\n");
    FILE *file = fopen(".databasebin/.databaseExam", "rb");
    bool chc = false;
    if (file != NULL) {
        while (!feof(file)) {
            fread(lsexam, sizeof(exam), 1, file);
            if (strcmp(lsexam->Cmpy.emailid, user->emailid) == 0) {
                chc = true;
                break;
            }
        }
    }
    if (!chc) {
        printf("\nYou didn't Set a question paper yet...Go to Set an Exam");
        printf("\n");
        sleep(1);
        fclose(file);
        return -1;
    }
    fclose(file);
    int k;
    for (k = 0; k < lsexam->countQues; k++) {
        printf("\n\nQuestion %d.", k + 1);
        printf("\n%s?", simplify(lsexam->Q[k].question));
        int o = 0;
        for (; o < 4; o++)
            printf("\n%c)%s", 'A' + o, simplify(lsexam->Q[k].opt[o]));
    }
    char c;
    printf("\nPress Any Key to go back");
    fflush(stdin);
    while ((c = getchar()) != '\n')
        ;
    getchar();
    return 0;
}

//Outer Layer of question bank details
void questionbank(company *user)
{
    while (1) {
        system("clear");
        printf("Question Bank");
        printf("\n-------------------------------------------\n\n");
        printf("\n1.Edit Question Paper");
        printf("\n2.View Question Paper");
        printf("\n3.Go Back");
        printf("\nChoose an option from the above  :  ");
        int ch, k;
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                k = editQB(user);
                if (k == -1)
                    return;
                break;
            case 2:
                k = viewQB(user);
                if (k == -1)
                    return;
                break;
            case 3:
                return;
            default:
                printf("\nEnter a Valid Choice");
                sleep(1);
        }
    }
    return;
}


//function to change password 
//rewrites file to update password
void changePassword(company *user, char filename[])
{
    system("clear");
    printf("Changing Password(Security Settings)");
    printf("\n-------------------------------------------\n\n");
    company *u = (company *)malloc(sizeof(company));
    FILE *file = fopen(filename, "rb+");
    if (file != NULL) {
        while (!feof(file)) {
            fread(u, sizeof(company), 1, file);
            if (strcmp(u->emailid, user->emailid) == 0) {
                char *t1, *t2;
                do {
                    // encrypted password feature
                    t1 = getpass("\nSet your new Password (Password won't be "
                                 "shown to maintain "
                                 "Secrecy) :  ");
                    t2 = getpass(
                        "\nRe-Type your new Password again to Confirm :  ");
                } while (strcmp(t1, t2) != 0);
                strcpy(u->pswrd, t1);
                fseek(file, -sizeof(company), SEEK_CUR);
                fwrite(u, sizeof(company), 1, file);
                fclose(file);
                system("clear");
                printf("\nPassword Updated Successfully");
                printf("\n");
                sleep(1);
                return;
            }
        }
    }
    printf("\nError While Changing Password...Please try again");
    return;
}

//opens a list of students enrolled for the company
void viewListStudents(company *user)
{
    exam *lsexam = (exam *)malloc(sizeof(exam));
    FILE *file = fopen(".databasebin/.databaseExam", "rb");
    bool chc = false;
    if (file != NULL) {
        int cnt = 0;
        system("clear");
        printf("\nList of Students Enrolled for your exam");
        printf("\n-------------------------------------------\n\n");
        while (!feof(file)) {
            fread(lsexam, sizeof(exam), 1, file);
            if (strcmp(lsexam->Cmpy.emailid, user->emailid) == 0) {
                int i = 0;
                for (; i < lsexam->countSt; i++) {
                    chc = true;
                    cnt++;
                    printf("\n%d.StudentName = %s , Roll No = %s ", cnt,
                           simplify(lsexam->st[i].stud.name),
                           simplify(lsexam->st[i].rollno));
                }
                break;
            }
        }
        if (cnt == 0) {
            printf("\nNo student enrolled in your course as of now");
        }
        getchar();
        printf("\n\nPress Any Key to continue");
        getchar();
        printf("\n");
        fclose(file);
    }
}

//Homepage for the company
void homepageC(company *user)
{
    bool done = false;

    while (1) {
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

        scanf("%d", &choice);
        switch (choice) {
            case VL:
                viewListStudents(user);
                break;
            case QB:
                questionbank(user);
                break;
            case TE:
                makeexam(user);
                break;
            case CP:
                changePassword(user, ".databasebin/.databaseC");
                break;
            case LO:
                return;
            default:
                "\nPlease Enter a Valid Choice";
                sleep(1);
        }
    }
    return;
}

//Login Page for the company
void loginCompany()
{
    system("clear");
    char em[MAXLEN];

    printf("Login as a Company\n");
    printf("\n-------------------------------------------\n\n");

    printf("Enter your eMail-ID  :  ");
    scanf("%s", em);

    char *getKey;
    bool chc = false;
    company *user = (company *)malloc(sizeof(company));

    FILE *cf = fopen(".databasebin/.databaseC", "rb");
    while (!feof(cf)) {
        fread(user, sizeof(company), 1, cf);
        if (strcmp(user->emailid, em) == 0) {
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

//registers a student (outer layer)
void registerStudent()
{
    system("clear");
    char sname[MAXLEN];

    printf("Sign Up as a Sudent\n");
    printf("\n-------------------------------------------\n\n");
    printf("Please Enter following details");
    printf("\nEnter your name  :  ");

    fgets(sname, MAXLEN, stdin); //fake fgets to skip endl character
    fgets(sname, MAXLEN, stdin);

    student *newbie = (student *)malloc(sizeof(student));

    // Check in database file ,if student is Already registered
    FILE *cf = fopen(".databasebin/.databaseS", "rb");
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

    FILE *file = fopen(".databasebin/.databaseS", "ab");
    if (file != NULL) {
        fwrite(newbie, sizeof(student), 1, file);
        fclose(file);
    }

    return;
}

//list of courses that a student enrolled in
int viewListCourses(student *user, bool isdirectCall)
{
    exam *lsexam = (exam *)malloc(sizeof(exam));
    FILE *file = fopen(".databasebin/.databaseExam", "rb");
    bool chc = false;
    if (file != NULL) {
        int cnt = 0;
        bool usedUpID[2000] = {false};
        int storeID[2000];
        system("clear");
        printf("\nList of Courses Enrolled");
        printf("\n-------------------------------------------\n\n");
        while (!feof(file)) {
            fread(lsexam, sizeof(exam), 1, file);
            int i = 0;
            for (; i < lsexam->countSt; i++) {
                if (lsexam->courseID < 2000
                    && strcmp(lsexam->st[i].stud.emailid, user->stud.emailid)
                           == 0) {
                    if (!usedUpID[lsexam->courseID]) {
                        chc = true;
                        cnt++;
                        printf("\n%d.CourseName = %s , CourseID = %d ", cnt,
                               lsexam->coursename, lsexam->courseID);
                        usedUpID[lsexam->courseID] = true;
                        storeID[cnt] = lsexam->courseID;
                        break;
                    }
                }
            }
        }
        if (isdirectCall) {
            getchar();
            printf("\n\nPress Any Key to continue");
            getchar();
            printf("\n");
            fclose(file);
        } else {
            getchar();
            if (cnt == 0) {
                printf("\nYou haven't enrolled for any exam yet");
                sleep(1);
                return -1;
            }
            printf("\n\nPlease Choose the Course for taking the exam  :  ");
            int j;
            do {
                scanf("%d", &j);
                if (j <= cnt && j > 0) {
                    return storeID[j];
                } else {
                    printf("\nPlease Enter a Valid Choice  :  ");
                }
            } while (j >= cnt);
        }
    }
    return 0;
}

//student : for enrolling in a exam
void enroll4exam(student *user)
{
    system("clear");

    char cname[MAXLEN];
    printf("\nEnter name of the course for exam  :  ");
    fgets(cname, MAXLEN, stdin);
    fgets(cname, MAXLEN, stdin);
    int i, len = strlen(cname);
    for (i = 0; i < len; i++) {
        if (cname[i] == '\n' || cname[i] == '\t' || cname[i] > 122
            || (cname[i] < 65 && (cname[i] < 48 || cname[i] > 57)))
            cname[i] = ' ';
    }

    exam *lsexam = (exam *)malloc(sizeof(exam));
    FILE *file = fopen(".databasebin/.databaseExam", "rb+");
    bool chc = false;
    if (file != NULL) {
        while (!feof(file)) {
            fread(lsexam, sizeof(exam), 1, file);
            if (strcmp(lsexam->coursename, cname) == 0) {
                chc = true;
                break;
            }
        }
    }
    if (!chc) {
        printf(
            "\nSorry ..We couldn't find any course that matches your choice");
        printf("\nPlease Try after some time");
        printf("\n");
        fclose(file);
        sleep(1);
        return;
    }

    lsexam->st[lsexam->countSt] = *user;
    lsexam->st[lsexam->countSt].stud.doneExam = false;
    int k = 0;
    for (; k < lsexam->countTslots; k++) {
        printf("\nTime Slot %d", k + 1);
        printf("\nStart Time - %s , End Time - %s On %c%c/%s/%s",
               lsexam->tS[k].starttime, lsexam->tS[k].endtime,
               lsexam->tS[k].date[0], lsexam->tS[k].date[1],
               lsexam->tS[k].month, lsexam->tS[k].year);
        printf("\n---------------------o-------------------------");
    }
    printf("\n Choose any time slot from the above  :  ");
    scanf("%d", &k);
    lsexam->st[lsexam->countSt++].chosenSlot = k;

    if (file != NULL) {
        fseek(file, -sizeof(exam), SEEK_CUR);
        fwrite(lsexam, sizeof(exam), 1, file);
        fclose(file);
    }
    printf("\n");
    printf("Student Successfully Enrolled for the exam");
    system("clear");
    printf("\n");
    sleep(1);
    return;
}

//Instructions before starting exam
void showInstructions(exam *lsexam)
{
    printf("\nInstructions for this exam");
    printf("\n1.Total number of questions in the exam - %d", lsexam->countQues);
    printf("\n2.Weightage of marks for correct answers - %d",
           lsexam->markscorr);
    printf("\n3.Weightage of marks for wrong answers - %d", lsexam->marksneg);
    printf("\n4.you can change your answer as many times as you wish before "
           "time ends- %d",
           lsexam->countQues);
    printf("\n5.you have choice to jump to any question you want");
    printf("\nPress any key to start exam");
    getchar();
    getchar();
    return;
}

void startExamActual(student *user, exam *lsexam)
{
    showInstructions(lsexam);
    printf("\n");
    system("clear");
    printf("\nEXAM STARTS!!");
    printf("\n\n-------------------------------------------\n\n");
    printf("\n");
    sleep(1);
    int i, k;
    bool usedUpAns[MAXQUES] = {false};
    
    time_t start_exam,temp;
    time(&start_exam);
    
    
    for (k = 0; k < lsexam->countQues; k++) {
        system("clear");
        printf("\n\nQuestion %d.", k + 1);
        printf("\n%s?", simplify(lsexam->Q[k].question));
        int o = 0;
        for (; o < 4; o++)
            printf("\n%c)%s", 'A' + o, simplify(lsexam->Q[k].opt[o]));
        printf("\nPlease tell your option (Enter 0 to switch to a different "
               "question) :  ");
        char ch;
        while(scanf("%c", &ch)) {
            if (ch == '0' || ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D')
                break;
            if (ch!='\n')
                printf("\nEnter a Valid Choice  :  ");
        }
        
        if (o == '0') {
            printf("\nEnter the question number you want to jump to  :  ");
            scanf("%d", &o);
            k = o - 1;
        } else {
            if (lsexam->Q[k].correctAns - 1 + 'A' == ch) {
                usedUpAns[k] = true;
            }
            printf("\nSaving your option and going to next question\n");
            printf("\n");
            time(&temp);
            long double tt= difftime(temp ,start_exam);
            printf("%Ld time is \n", tt);
            if (tt >= lsexam->totaltime*36000) {
                printf("\n\nTime - UP......");
                sleep(1);
                break;
            } else {
                printf("\n Time Left - %d hours",(tt/3600));
            }
            sleep(1);
        }
    }
    int numcorr = 0;
    for (i = 0; i < lsexam->countQues; i++) {
        if (usedUpAns[i])
            numcorr++;
    }
    system("clear");
    printf("\nYour Exam is Completed ...thanks for Choosing our site for exam");
    printf("\nPress ENTER to View your results\n\n");
    getchar();
    getchar();
    
    printf("\n\n Exam on %s", lsexam->coursename);
    printf("\n\n You Got (%d) out of (%d) marks", numcorr * lsexam->markscorr,
           lsexam->countQues * lsexam->markscorr);
    printf("\n Total Number of Questions - (%d)", lsexam->countQues);
    printf("\n Total Number of Correct Answers - (%d)", numcorr);
    printf("\n Total Number of Wrong Questions - (%d)",
           lsexam->countQues - numcorr);
    printf("\n");
    printf("\nEnter 1 to print the results in a local txt file");
    printf("\nEnter 2 t Go Back\n : ");
    
    char c = getchar();
    if (c == '1') {
        printf("\nSaving to results.txt file\n");
        sleep(1);
        system("touch results.txt");
        FILE *file = fopen("results.txt","w");
        if (file != NULL) {
            fprintf(file,"\n\n Exam on %s", lsexam->coursename);
            fprintf(file,"\n\n You Got (%d) out of (%d) marks", numcorr * lsexam->markscorr,
                   lsexam->countQues * lsexam->markscorr);
            fprintf(file,"\n Total Number of Questions - (%d)", lsexam->countQues);
            fprintf(file,"\n Total Number of Correct Answers - (%d)", numcorr);
            fprintf(file,"\n Total Number of Wrong Questions - (%d)",
                   lsexam->countQues - numcorr);
            fprintf(file,"\n");
            fclose(file);
        } else {
            printf("Error while writing to file \n");
        }
    }
    return;
}

void startexam(student *user)
{
    system("clear");
    int courseID = viewListCourses(user, false);
    if (courseID < 0) {
        return;
    }
    system("clear");
    printf("EXAM ZONE");
    printf("\n-------------------------------------------\n\n");

    exam *lsexam = (exam *)malloc(sizeof(exam));
    FILE *file = fopen(".databasebin/.databaseExam", "rb");

    int chSlot;
    bool ok = false, ok1 = false;
    if (file != NULL) {
        while (!feof(file)) {
            fread(lsexam, sizeof(exam), 1, file);
            if (lsexam->courseID == courseID) {
                int i = 0;
                for (; i < lsexam->countSt; i++) {
                    // printf("\n%s",lsexam->tS[i].date);
                    if (strcmp(lsexam->st[i].stud.emailid, user->stud.emailid)
                        == 0) {
                        chSlot = lsexam->st[i].chosenSlot;
                        ok = true;
                        ok1 = lsexam->st[i].stud.doneExam;
                        if (ok1) {
                            printf("\nYou have already took this exam...Please "
                                   "try after some days");
                            return;
                        }
                        lsexam->st[i].stud.doneExam = true;
                        break;
                    }
                }
            }
            if (ok)
                break;
        }
    }
    if (!ok) {
        printf("\nYou haven't enrolled for this exam");
        return;
    }
    startExamActual(user, lsexam);
    // Check if this time is the correct time slot
    time_t rawtime;
    struct tm *info;
    char buffer[5][80];
    char fullbuff[80];
    time(&rawtime);

    info = localtime(&rawtime);
    strftime(buffer[0], 80, "%Y", info);
    strftime(buffer[1], 80, "%m", info);
    strftime(buffer[2], 80, "%d", info);
    strftime(buffer[3], 80, "%R", info);
    chSlot--;
    if (simp(buffer[0]) == simp(lsexam->tS[chSlot].year)
        && simp(buffer[1]) == simp(lsexam->tS[chSlot].month)
        && (buffer[2][0] == lsexam->tS[chSlot].date[0])
        && (buffer[2][1] == lsexam->tS[chSlot].date[1])) {
        if (strcmp(buffer[3], lsexam->tS[chSlot].starttime) >= 0
            && strcmp(buffer[3], lsexam->tS[chSlot].endtime) <= 0) {
            printf("\nStarting your exam on %s....",lsexam->coursename);
            printf("\n");
            sleep(1);
            startExamActual(user, lsexam);
            return;
        }
    }
    // printf("\n%s",lsexam->tS[chSlot].date);
    printf("\nExam is on %c%c.%s.%s at time from %s to %s",
           lsexam->tS[chSlot].date[0], lsexam->tS[chSlot].date[1],
           lsexam->tS[chSlot].month, lsexam->tS[chSlot].year,
           lsexam->tS[chSlot].starttime, lsexam->tS[chSlot].endtime);
    printf("\n");
    sleep(2);
    return;
}

//homepage for student
void homepageS(student *user)
{
    bool done = false;

    while (1) {
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
        int choice, k;

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                k = viewListCourses(user, true);
                break;
            case 2:
                enroll4exam(user);
                break;
            case 3:
                startexam(user);
                break;
            case 4:
                changePassword(&user->stud, ".databasebin/.databaseS");
                break;
            case 5:
                return;
            default:
                "\nPlease Enter a Valid Choice";
                sleep(1);
        }
    }
    return;
}

void loginStudent()
{
    system("clear");
    char em[MAXLEN];
    //
    printf("Login as a Student\n");
    printf("\n-------------------------------------------\n\n");
    printf("Enter your eMail-ID  :  ");
    scanf("%s", em);

    char *getKey;
    bool chc = false;
    student *user = (student *)malloc(sizeof(student));

    FILE *cf = fopen(".databasebin/.databaseS", "rb");
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

//clears all the data in the database
void resetDB()
{
    char filenames[4][30];
    strcpy(filenames[0], ".databasebin/.databaseS");
    strcpy(filenames[1], ".databasebin/.databaseC");
    strcpy(filenames[2], ".databasebin/.databaseExam");
    strcpy(filenames[3], ".databasebin/.lastSeenCID");

    FILE *fp;
    int i;
    for (i = 0; i < 4; i++) {
        fp = fopen(filenames[i], "wb");
        if (fp != NULL) {
            fclose(fp);
        }
    }
    system("clear");
    printf("\nDataBase reset Successfully");
    printf("\n");
    sleep(1);
    return;
}

//homepage for admin
void homepageA()
{
    system("clear");
    printf("\nHome Page - Admin");
    printf("\n-------------------------------------------\n\n");

    while (1) {
        printf("\n1.ReSet Everything on the DataBase(Warning !!)");
        printf("\n2.Change Password");
        printf("\n3.Log out");
        int ch;
        printf("\nEnter your Choice from the above :  ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                resetDB();
                break;
            case 2:
                printf("\nAdmin Password can't be changed at a higher "
                       "level...It needs to be changed at a lower "
                       "level(Security Reasons)");
                /*changePassword();*/ break;
            case 3:
                return;
            default:
                printf("\nEnter a Valid Choice");
        }
    }
}

void loginAdmin()
{
    system("clear");
    printf("Login - Admin");
    printf("\n-------------------------------------------\n\n");

    // (username,"ranjiasadmin");
    // (userPassword,"aimskyhigh");

    char A[25], B[25];
    printf("\nEnter username  :  ");
    scanf("%s", A);

    char adminPassword[25];

    FILE *fp = fopen(".databasebin/.admin", "rb");
    if (fp != NULL) {
        fread(B, sizeof(char) * 25, 1, fp);
        fread(adminPassword, sizeof(char) * 25, 1, fp);
        fclose(fp);
    }

    if (strcmp(B, A) != 0) {
        printf("\nEntered username doesn't match Admin's username");
        return;
    }

    bool chc = true;
    int status = authenticate(chc, adminPassword);
    if (status == -1)
        return;
    printf("\nSuccessfully Logged in\n");
    return homepageA();
}

int printWelcome()
{
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

void run()
{
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