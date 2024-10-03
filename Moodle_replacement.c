#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


struct Student {
    int student_ID;
    char name[100];
    char faculty[100];
};

struct Exam {
    int exam_ID;
    char exam_type[100];
    char exam_info[100];

};

struct ExamGrade {
    int exam_ID;
    int student_ID;
    int grade;
};

union ExamInfo {
    int duration;
    char software[100];
};

#define MAX_NAME_LENGTH 20
#define MAX_RECORDS 100

struct Student database_student[MAX_RECORDS];
int record_count = 0;


void ADD_STUDENT(int id, const char* name,  const char* faculty) {
    if (record_count < MAX_RECORDS) {
        database_student[record_count].student_ID = id;
        strncpy(database_student[record_count].name, name, MAX_NAME_LENGTH - 1);
        database_student[record_count].name[MAX_NAME_LENGTH - 1] = '\0'; // защита от переполнения
        strncpy(database_student[record_count].faculty, faculty, MAX_NAME_LENGTH - 1);
        database_student[record_count].faculty[MAX_NAME_LENGTH - 1] = '\0'; // защита от переполнения
        record_count++;
    } else {
        printf("База данных полна.\n");
    }
}

//void ADD_EXAM(int id, const char* name,  const char* faculty) {
//     if (record_count < MAX_RECORDS) {
//         database[record_count].student_ID = id;
//         strncpy(database[record_count].name, name, MAX_NAME_LENGTH - 1);
//         database[record_count].name[MAX_NAME_LENGTH - 1] = '\0'; // защита от переполнения
//         strncpy(database[record_count].faculty, faculty, MAX_NAME_LENGTH - 1);
//         database[record_count].faculty[MAX_NAME_LENGTH - 1] = '\0'; // защита от переполнения
//         record_count++;
//     } else {
//         printf("База данных полна.\n");
//     }
// }


int main(void) {
    printf("Hello World!\n");
}