/* 
 * File:   headers.h
 * Author: Adha Ranjith Kumar
 * Roll No: 15CS30002
 * Project : P14: Examination Management System
 * TA: Satendra Kumar
 * Created on January 16, 2017, 12:19 PM
 */

#ifndef HEADERS_H
#define	HEADERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


//Good Practise to keep hash defines instead of using const numbers in "DEBUG" mode
#define MAXLEN 30
#define MAXT 10
#define MAXLENQB 50
#define MAXQUES 20
#define MAXCAPACITY 10
#define MAXENROLL 10

/// Enumerating Choices ///
// Welcome Page
enum CHOICE { RC = 1, RS, LC, LS, AD, EXIT };

// homepage for company
enum homeC { VL = 1, QB, TE, CP, LO };

/// this is a Custom bool type , C doesn't support bool(C99 supports but it's a
/// sanity typedef in that case) .///
typedef enum { false, true } bool;


//all details of company in this struct
//this struct is used in student also to erase redundancy
struct _company {
    char name[MAXLEN];
    char emailid[MAXLEN];
    char address[MAXLEN];
    char pswrd[MAXLEN];
    char mobno[10];
    bool doneExam;
    // TO-DO additional
    // char *AboutMe;  // Not needed I guess
};

typedef struct _company company;

//Student details also include rollno and chosenslot for exam
struct _student {
    company stud;
    char rollno[10];
    int chosenSlot;
};

typedef struct _student student;

struct _ques {
    char question[MAXLENQB];
    char opt[4][MAXLENQB];
    int correctAns;
};

typedef struct _ques ques;

struct _timeslot {
    char starttime[MAXT];
    char endtime[MAXT];
    char date[2];
    char month[2];
    char year[4];
};

typedef struct _timeslot timeslot;

//Struct for exam
struct _exam {
    company Cmpy;
    student st[MAXCAPACITY];
    char coursename[MAXLEN];
    int courseID;
    int countSt;
    ques Q[MAXQUES];
    int countQues;
    timeslot tS[MAXT]; // 24-hour format
    int countTslots;
    long double totaltime;
    int markscorr;
    int marksneg;
};

typedef struct _exam exam;

#endif	/* HEADERS_H */

