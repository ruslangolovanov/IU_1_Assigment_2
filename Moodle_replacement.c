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
int record_count = 0;
int record_count2 = 0;

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

void ADD_EXAM(int id, const char* type, int duration, char* name) {
     if (record_count2 < MAX_RECORDS) {
         database_exam[record_count2].exam_ID = id;
         database_exam[record_count2].type, type, MAX_NAME_LENGTH - 1;

         if (type == WRITTEN) {
             database_exam[record_count2].info.duration = duration;
         }else {
             database_exam[record_count2].info.software, name, MAX_NAME_LENGTH - 1;
         }

         record_count2++;
     } else {
         printf("База данных полна.\n");
     }
 }


struct Student* find_person(int id) {
    for (int i = 0; i < record_count; i++) {  // Проходим по всем записям
        if (database_student[i].student_ID == id) {  // Если найдено совпадение по ID
            return &database_student[i];  // Возвращаем указатель на найденную запись
        }
    }
    return NULL;  // Если запись не найдена, возвращаем NULL
}

struct Exam* find_exam(int id) {
    for (int i = 0; i < record_count2; i++) {  // Проходим по всем записям
        if (database_exam[i].exam_ID == id) {  // Если найдено совпадение по ID
            return &database_exam[i];  // Возвращаем указатель на найденную запись
        }
    }
    return NULL;  // Если запись не найдена, возвращаем NULL
}

void delete_person(int id) {
    for (int i = 0; i < record_count; i++) {  // Ищем запись по ID
        if (database_student[i].student_ID == id) {  // Если найдено
            for (int j = i; j < record_count - 1; j++) {  // Сдвигаем все последующие записи на одно место назад
                database_student[j] = database_student[j + 1];
            }
            record_count--;  // Уменьшаем счетчик записей
            printf("Запись удалена.\n");
            return;
        }
    }
    printf("Запись с id %d не найдена.\n", id);  // Сообщаем, если запись не найдена
}
void print_Student_database() {
    for (int i = 0; i < record_count; i++) {  // Проходим по всем записям
        printf("ID: %d, Name: %s, faculty: %s\n", database_student[i].student_ID, database_student[i].name, database_student[i].faculty);
    }
}
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
        current_command[strlen(current_command) - 1] = '\0';
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
// if (strcmp(arr_a[0], "ADD_EXAM\n")) {
//     printf("%s t\n", arr_a[0]);
// }else {
//     printf("%s f\n", arr_a[0]);
// }
        //printf("%d", strcmp(arr_a[0], "ADD_STUDENT"));
        printf("%s\n", arr_a[0]);
            if(strcmp(arr_a[0], "ADD_STUDENT") == 0) {
                if (find_person(atoi(arr_a[1])) == NULL) {
                    if (contains_digit(arr_a[2]) == 0){
                        if (contains_digit(arr_a[3]) == 0) {
                            if (contains_char(arr_a[1]) == 0) {

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
                        if (contains_char(arr_a[1]) == 0) {
                            if (contains_char(arr_a[3]) == 0) {
                                ADD_EXAM(atoi(arr_a[1]), arr_a[2], atoi(arr_a[3]), NULL);
                                fprintf(fileout, "Exam: %d added\n", atoi(arr_a[1]));
                            }else {
                                fprintf(fileout, "Invalid info\n");
                            }
                        }else {
                            fprintf(fileout, "Invalid id\n");
                        }


                    }else if(strcmp(arr_a[2], "DIGITAL") == 0 ){
                        if (contains_char(arr_a[1]) == 0) {
                            if (contains_digit(arr_a[3]) == 0) {
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



            }

            }


        print_Student_database();
        //print_Exam_database();


        fclose(file);
        fclose(fileout);
        return 0;
 }
