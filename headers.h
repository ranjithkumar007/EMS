#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXLEN 30
#define MAXT 10
#define MAXLENQB 150
#define MAXQUES 100
#define MAXCAPACITY 100

/// Enumerate Choices ///
// Welcome Page
enum CHOICE { RC = 1, RS, LC, LS, AD, EXIT };

//homepage for company
enum homeC {VL = 1,QB,TE,CP,LO};

///this is a Custom bool type , C doesn't support bool(C99 supports but it's a sanity typedef in that case) .///
typedef enum { false, true } bool;

struct _company {
  char name[MAXLEN];
  char emailid[MAXLEN];
  char address[MAXLEN];
  char pswrd[MAXLEN];
  char mobno[10];
  // TO-DO
  // char *AboutMe;
};

typedef struct _company company;

struct _student {
  company stud;
  char rollno[10];
  // TO-DO
  // char *AboutMe;
};

typedef struct _student student;

struct _ques{
	int quesno;
	char question[MAXLENQB];
	char opt[4][MAXLENQB];
	int correctAns;
};

typedef struct _ques ques;

struct _timeslot {
	char starttime[MAXT];
	char endtime[MAXT];
};

typedef struct _timeslot timeslot;

struct _exam {
	company Cmpy;
	student st[MAXCAPACITY];
	char coursename[MAXLEN];
	int courseID;
	int countSt;
	ques Q[MAXQUES];
	int countQues;
	//24-hour format
	timeslot tS[MAXT];
	int countTslots;
};

typedef struct _exam exam;