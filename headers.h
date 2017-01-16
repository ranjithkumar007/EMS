#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXLEN 30

/// Enumerate Choices ///
enum CHOICE { RC = 1, RS, LC, LS, EXIT };

/// C doesn't support bool(C99 supports but it's a sanity typedef in that case) .So this is a Custom bool type ///
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