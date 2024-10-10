#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


struct Student {
    int student_ID;
    char name[100];
    char faculty[100];
};
//enum ExamType {
//     WRITTEN,
//     DIGITAL
// };

struct Exam {
    int exam_ID;
    enum ExamType {
        WRITTEN,
        DIGITAL
    }type;
    union ExamInfo {
        int duration;
        char software[100];
    }info;
};

struct ExamGrade {
    int exam_ID;
    int student_ID;
    int grade;
};

// union ExamInfo {
//     int duration;
//     char software[100];
// };

int contains_digit(const char *str) {
    while (*str) {
        if (isdigit(*str)) {
            return 1; // Если нашли цифру, возвращаем 1
        }
        str++; // Переход к следующему символу
    }
    return 0; // Если цифр нет, возвращаем 0
}
int contains_char(const char *str) {
    while (*str) {
        if (isalpha(*str)) {
            return 1; // Если найдена буква, возвращаем 1
        }
        str++; // Переход к следующему символу строки
    }
    return 0; // Если букв нет, возвращаем 0
}




#define MAX_NAME_LENGTH 20
#define MAX_RECORDS 100

struct Student database_student[MAX_RECORDS];
struct Exam database_exam[MAX_RECORDS];
struct ExamGrade database_grade[MAX_RECORDS];

int record_count_students = 0;
int record_count_exam = 0;
int record_count_grade = 0;

void ADD_STUDENT(int id, const char* name,  const char* faculty) {
    if (record_count_students < MAX_RECORDS) {
        database_student[record_count_students].student_ID = id;
        strncpy(database_student[record_count_students].name, name, MAX_NAME_LENGTH - 1);
        //database_student[record_count_students].name[MAX_NAME_LENGTH - 1] = '\0'; // защита от переполнения
        strncpy(database_student[record_count_students].faculty, faculty, MAX_NAME_LENGTH - 1);
        //database_student[record_count_students].faculty[MAX_NAME_LENGTH - 1] = '\0'; // защита от переполнения
        record_count_students++;
    } else {
        printf("База данных полна.\n");
    }
}

void ADD_EXAM(int id, const char* type, int duration, char* name) {
     if (record_count_exam < MAX_RECORDS) {
         database_exam[record_count_exam].exam_ID = id;
         //database_exam[record_count_exam].type, type, MAX_NAME_LENGTH - 1;

         if (strcmp(type,"WRITTEN") == 0) {
             database_exam[record_count_exam].info.duration = duration;
             database_exam[record_count_exam].type =  WRITTEN;
         }else if(strcmp(type,"DIGITAL") == 0){
             //database_exam[record_count_exam].info.software, name, MAX_NAME_LENGTH - 1;
             strcpy(database_exam[record_count_exam].info.software, name);
             //atabase_exam[record_count_exam].info.software = name, MAX_NAME_LENGTH - 1;
             database_exam[record_count_exam].type =  DIGITAL;

         }

         record_count_exam++;
     } else {
         printf("База данных полна.\n");
     }
 }


void ADD_Grade(int exam_id, int student_id, int grade) {
    if (record_count_exam < MAX_RECORDS) {
        database_grade[record_count_grade].exam_ID = exam_id;
        database_grade[record_count_grade].student_ID = student_id;
        database_grade[record_count_grade].grade = grade;

        record_count_grade++;
    } else {
        printf("База данных полна.\n");
    }
}



struct Student* find_person(int id) {
    for (int i = 0; i < record_count_students; i++) {  // Проходим по всем записям
        if (database_student[i].student_ID == id) {  // Если найдено совпадение по ID
            return &database_student[i];  // Возвращаем указатель на найденную запись
        }
    }
    return NULL;  // Если запись не найдена, возвращаем NULL
}

struct Exam* find_exam(int id) {
    for (int i = 0; i < record_count_exam; i++) {  // Проходим по всем записям
        if (database_exam[i].exam_ID == id) {  // Если найдено совпадение по ID
            return &database_exam[i];  // Возвращаем указатель на найденную запись
        }
    }
    return NULL;  // Если запись не найдена, возвращаем NULL
}

struct Student* SearchStudent(int id, FILE *fileout) {
    for (int i = 0; i < record_count_students; i++) {  // Проходим по всем записям
        if (database_student[i].student_ID == id) {  // Если найдено совпадение по ID
            fprintf(fileout, "ID: %d, Name: %s, Faculty: %s\n", database_student[i].student_ID, database_student[i].name, database_student[i].faculty);
            return &database_student[i];  // Возвращаем указатель на найденную запись
        }
    }
    return NULL;
}

struct Student* SearchGrade(int id_student, int id_exam, FILE *fileout) {

    for (int i = 0; i < record_count_students; i++) {  // Проходим по всем записям
        if (database_student[i].student_ID == id_student) {

            for (int j = 0; j < record_count_exam; j++) {
                if (database_exam[j].exam_ID == id_exam) {

                    for (int k = 0; k < record_count_grade; k++) {
                        if (database_grade[k].exam_ID == id_exam && database_grade[k].student_ID == id_student) {
                            if (database_exam[j].type == WRITTEN) {
                                fprintf(fileout, "Exam: %d, Student: %d, Name: %s, Grade: %d, Type: WRITTEN, Info: %d\n", database_exam[j].exam_ID, database_student[i].student_ID,  database_student[i].name, database_grade[k].grade, database_exam[j].info.duration);
                            }else if((database_exam[j].type == DIGITAL)){
                                fprintf(fileout, "Exam: %d, Student: %d, Name: %s, Grade: %d, Type: DIGITAL, Info: %s\n", database_exam[j].exam_ID, database_student[i].student_ID,  database_student[i].name, database_grade[k].grade, database_exam[j].info.software);
                            }

                        }
                    }
                }
            }

        }
    }
    return NULL;
}


void UPDATE_EXAM(int id, const char* type, int duration, char* name) {

    if (record_count_exam < MAX_RECORDS) {

        if (strcmp(type,"WRITTEN") == 0) {
            database_exam[id].info.duration = duration;
            database_exam[id].type =  WRITTEN;
        }else if(strcmp(type,"DIGITAL") == 0){
            strcpy(database_exam[id].info.software, name);
            database_exam[id].type =  DIGITAL;
        }
    } else {
        printf("База данных полна.\n");
    }
}


void UPDATE_GRADE(int exam_id ,int student_id, int grade) {
    for (int i = 0; i < record_count_grade; i++) {
        if (database_grade[i].exam_ID == exam_id && database_grade[i].student_ID == student_id) {
            database_grade[i].grade = grade;
        }



    }
}



void delete_person(int id) {
    for (int i = 0; i < record_count_students; i++) {  // Ищем запись по ID
        if (database_student[i].student_ID == id) {  // Если найдено
            for (int j = i; j < record_count_students - 1; j++) {  // Сдвигаем все последующие записи на одно место назад
                database_student[j] = database_student[j + 1];
            }
            record_count_students--;  // Уменьшаем счетчик записей

            break;
        }
    }
    for(int i = 0; i < record_count_grade; i++) {
        if (database_grade[i].student_ID == id) {
            for (int j = i; j < record_count_grade - 1; j++) {  // Сдвигаем все последующие записи на одно место назад
                database_grade[j] = database_grade[j + 1];
            }
            record_count_grade --;
        }
    }

}

    void print_Student_database(FILE *fileout) {

        for (int i = 0; i < record_count_students; i++) {  // Проходим по всем записям
            if (database_student[i].faculty[strlen(database_student[i].faculty) - 1] == '\n') {
                database_student[i].faculty[strlen(database_student[i].faculty) - 1] = '\0';

            }

            fprintf(fileout, "ID: %d, Name: %s, Faculty: %s\n", database_student[i].student_ID, database_student[i].name, database_student[i].faculty);
        }
    }



// void print_Grades_database() {
//     for (int i = 0; i < record_count_grade; i++) {  // Проходим по всем записям
//         printf("exaam_ID: %d, student_id: %d, grade: %d\n", database_grade[i].exam_ID, database_grade[i].student_ID, database_grade[i].grade);
//     }
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void print_Exam_database() {
//     for (int i = 0; i < record_count2; i++) {  // Проходим по всем записям
//         printf("ExamID: %d, Type: %s, Info: %s\n", database_exam[i].exam_ID, database_exam[i].type, database_exam[i].info);
//     }
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void) {
    FILE *file;
    FILE *fileout = fopen("output.txt", "w");

    // Открываем файл для чтения
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    char current_command[100];
    char ch;

    while (fgets(current_command, sizeof(current_command), file)) {
        //current_command[strlen(current_command) - 1] = '\0';
        char *arr_a[4];
        int i = 0;

        // Split the string 'S' into separate numbers (as strings)
        char *token2 = strtok(current_command, " ");

        // Save each substring to the 'arr_s' array
        while (token2 != NULL) {
            arr_a[i] = token2;
            i++;
            token2 = strtok(NULL, " ");
        }



        //printf("%s\n", arr_a[0]);
        if(strcmp(arr_a[0], "ADD_STUDENT") == 0) {
            if (find_person(atoi(arr_a[1])) == NULL) {
                if ((contains_digit(arr_a[2]) == 0) && (strlen(arr_a[2])  <=  20)){
                    if ((contains_digit(arr_a[3]) == 0) && (4 <= strlen(arr_a[3])) && ( strlen(arr_a[3]) <=  30)) {
                        printf("%s %d\n", arr_a[3], strlen(arr_a[3]));
                        if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1]) ) && (atoi(arr_a[1])<= 1000)) {

                            ADD_STUDENT(atoi(arr_a[1]), arr_a[2], arr_a[3]);
                            fprintf(fileout, "Student: %d added\n", atoi(arr_a[1]));

                        }else {
                            fprintf(fileout, "Invalid id\n");
                        }
                    }else {
                        fprintf(fileout, "Invalid faculty\n");
                    }
                }else {
                    fprintf(fileout, "Invalid name\n");
                }
            }else {
                fprintf(fileout, "Student: %d already exists\n", atoi(arr_a[1]));
            }


        }else if(strcmp(arr_a[0], "ADD_EXAM") == 0 ){
            if (find_exam(atoi(arr_a[1])) == NULL) {

                if (strcmp(arr_a[2], "WRITTEN") == 0) {
                    if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1]) <= 500)) {
                        if ((contains_char(arr_a[3]) == 0) && (40 <= atoi(arr_a[1]) <= 180)) {
                            ADD_EXAM(atoi(arr_a[1]), arr_a[2], atoi(arr_a[3]), NULL);
                            fprintf(fileout, "Exam: %d added\n", atoi(arr_a[1]));
                        }else {
                            fprintf(fileout, "Invalid info\n");
                        }
                    }else {
                        fprintf(fileout, "Invalid id\n");
                    }


                }else if(strcmp(arr_a[2], "DIGITAL") == 0 ){
                    if ((contains_char(arr_a[1]) == 0 )&& (0 <= atoi(arr_a[1]) <= 500)) {
                        if ((contains_digit(arr_a[3]) == 0) &&( 2 <= strlen(arr_a[3])  <=  20) ){
                            ADD_EXAM(atoi(arr_a[1]), arr_a[2], NULL, arr_a[3]);
                            fprintf(fileout, "Exam: %d added\n", atoi(arr_a[1]));
                        }else {
                            fprintf(fileout, "Invalid info\n");
                        }
                    }else {
                        fprintf(fileout, "Invalid id\n");
                    }

                }else {
                    fprintf(fileout, "Invalid exam type\n");
                }
            }else {
                fprintf(fileout, "Exam: %d already exists\n", atoi(arr_a[1]));
            }



        }else if(strcmp(arr_a[0], "ADD_GRADE") == 0) {



                    if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1]) <= 500))  {
                        if ((contains_char(arr_a[2]) == 0) && (0 <= atoi(arr_a[2]) <= 1000))  {
                            if ((contains_char(arr_a[3]) == 0) && (atoi(arr_a[3]) <= 100) && (atoi(arr_a[3]) >= 0)) {

                                if(find_exam(atoi(arr_a[1])) != NULL) {
                                    if (find_person(atoi(arr_a[2])) != NULL) {


                                        ADD_Grade(atoi(arr_a[1]), atoi(arr_a[2]), atoi(arr_a[3]));
                                        fprintf(fileout, "Grade %d added for the student: %d\n", atoi(arr_a[3]), atoi(arr_a[2]));

                                    }else{

                                        fprintf(fileout, "Student not found\n");
                                    }
                                }else {
                                    fprintf(fileout, "Exam not found\n");
                                }

                            }else {
                                fprintf(fileout, "Invalid grade\n");
                            }

                        }else {
                            fprintf(fileout, "Invalid student id\n");
                        }

                    }else {
                        fprintf(fileout, "Invalid exam id\n");
                    }



        }else if(strcmp(arr_a[0], "SEARCH_STUDENT") == 0) {
            if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1]) <= 1000)) {
                if (find_person(atoi(arr_a[1])) != NULL) {
                    SearchStudent(atoi(arr_a[1]), fileout);
                }else {
                    fprintf(fileout, "Student not found\n");
                }

            }else {
                fprintf(fileout, "Invalid student id\n");
            }
        }else if(strcmp(arr_a[0], "SEARCH_GRADE") == 0) {
            if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1]) <= 1000)) {
                if ((contains_char(arr_a[2]) == 0) && (0 <= atoi(arr_a[2]) <= 500)) {
                    if (find_person(atoi(arr_a[2])) != NULL) {
                        if (find_exam(atoi(arr_a[1])) != NULL) {
                            SearchGrade(atoi(arr_a[2]), atoi(arr_a[1]), fileout);
                        }else {
                            fprintf(fileout, "Exam not found\n");
                        }

                    }else {
                        fprintf(fileout, "Student not found\n");
                    }

                }else {
                    fprintf(fileout, "Invalid exam id\n");
                }

            }else {
                fprintf(fileout, "Invalid student id\n");
            }

        }else if(strcmp(arr_a[0], "UPDATE_EXAM") == 0) {
            //UPDATE_EXAM 202 DIGITAL Eclipse
            //UPDATE_EXAM 202 WRITTEN 120
            if (strcmp(arr_a[2], "WRITTEN") == 0 ) {
                if((contains_char(arr_a[3]) == 0) && (40 <= atoi(arr_a[1]) <= 180)) {
                    UPDATE_EXAM(atoi(arr_a[1]), arr_a[2], atoi(arr_a[3]), NULL );
                    fprintf(fileout, "Exam: %d updated\n", atoi(arr_a[1]));

                }else {
                    fprintf(fileout, "Invalid duration\n");
                }

            }else if((strcmp(arr_a[2], "DIGITAL") == 0)){
                if((contains_digit(arr_a[3]) == 0) &&( 2 <= strlen(arr_a[3])  <=  20)) {
                    UPDATE_EXAM(atoi(arr_a[1]), arr_a[2], NULL, arr_a[3]) ;
                    fprintf(fileout, "Exam: %d updated\n", atoi(arr_a[1]));
                }else {
                    fprintf(fileout, "Invalid software\n");
                }


            }else {
                fprintf(fileout, "Invalid exam type\n");
            }
        }else if(strcmp(arr_a[0], "UPDATE_GRADE") == 0) {
            if((contains_char(arr_a[3]) == 0) && (atoi(arr_a[3]) <= 100) && (atoi(arr_a[3]) >= 0)) {
                UPDATE_GRADE(atoi(arr_a[1]), atoi(arr_a[2]), atoi(arr_a[3]));
                fprintf(fileout, "Grade %d updated for the student: %d\n", atoi(arr_a[3]), atoi(arr_a[2]));

            }else {
                fprintf(fileout, "Invalid grade\n");
            }
        }else if(strcmp(arr_a[0], "LIST_ALL_STUDENTS") == 0) {
            print_Student_database(fileout);
        }else if(strcmp(arr_a[0], "DELETE_STUDENT") == 0) {
            delete_person(atoi(arr_a[1]));
            fprintf(fileout, "Student: %d deleted\n", atoi(arr_a[1]));
        }else if(strcmp(arr_a[0], "DELETE_STUDENT") == 0) {
            break;
        }


        //print_Student_database();
        //print_Exam_database();

    }

//delete_person(101);
    //print_Student_database(fileout);

    //print_Grades_database();
        fclose(file);
        fclose(fileout);
        return 0;

}