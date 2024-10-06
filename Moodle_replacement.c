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
struct Person* find_person(int id) {
    for (int i = 0; i < record_count; i++) {  // Проходим по всем записям
        if (database_student[i].student_ID == id) {  // Если найдено совпадение по ID
            return &database_student[i];  // Возвращаем указатель на найденную запись
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
void print_database() {
    for (int i = 0; i < record_count; i++) {  // Проходим по всем записям
        printf("ID: %d, Name: %s, Age: %s\n", database_student[i].student_ID, database_student[i].name, database_student[i].faculty);
    }
}


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


            if(strcmp(arr_a[0], "ADD_STUDENT\n")) {
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
            }

        }





        fclose(file);
        fclose(fileout);
        return 0;
 }
