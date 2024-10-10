#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Structure to represent a student
struct Student {
    int student_ID;          // Unique ID for the student
    char name[100];          // Name of the student
    char faculty[100];       // Faculty of the student
};

// Structure to represent an exam
struct Exam {
    int exam_ID;            // Unique ID for the exam
    enum ExamType {         // Enumeration to define exam types
        WRITTEN,            // Written exam
        DIGITAL             // Digital exam
    } type;
    union ExamInfo {        // Union to hold exam-specific information
        int duration;       // Duration of written exam
        char software[100]; // Software used for digital exam
    } info;
};

// Structure to represent the grades of students in exams
struct ExamGrade {
    int exam_ID;            // ID of the exam
    int student_ID;         // ID of the student
    int grade;              // Grade obtained by the student
};

// Function to check if a string contains any digits
int contains_digit(const char *str) {
    while (*str) {
        if (isdigit(*str)) {
            return 1; // Return 1 if a digit is found
        }
        str++; // Move to the next character
    }
    return 0; // Return 0 if no digits are found
}

// Function to check the validity of the exam duration
int contains_char(char duration_1[]) {
    int k = 0; // Counter for invalid characters
    int m = 0; // Counter for digits
    for (int i = 0; i < strlen(duration_1) - 1; i++) { // Loop through the duration string
        switch (duration_1[i]) {
            case '0': m++; break; // Count digits
            case '1': m++; break;
            case '2': m++; break;
            case '3': m++; break;
            case '4': m++; break;
            case '5': m++; break;
            case '6': m++; break;
            case '7': m++; break;
            case '8': m++; break;
            case '9': m++; break;
            default: k++; break; // Increment k for non-digit characters
        }
    }
    return k; // Return count of invalid characters
}

// Function to check the validity of a string (only alphabetic characters)
int string_check(char str[]) {
    int k = 0; // Counter for invalid characters
    for (int i = 0; i < strlen(str) - 1; i++) {
        if (!((65 <= str[i] && str[i] <= 90) || (97 <= str[i] && str[i] <= 122))) {
            k++; // Increment k for non-alphabetic characters
            break; // Exit loop if an invalid character is found
        }
    }
    return k; // Return count of invalid characters
}

#define MAX_NAME_LENGTH 100 // Define maximum length for names
#define MAX_RECORDS 500      // Define maximum number of records

// Declare arrays to hold student, exam, and grade records
struct Student database_student[MAX_RECORDS];
struct Exam database_exam[MAX_RECORDS];
struct ExamGrade database_grade[MAX_RECORDS];

// Counters for the number of records
int record_count_students = 0;
int record_count_exam = 0;
int record_count_grade = 0;

// Function to add a student record
void ADD_STUDENT(int id, const char* name, char* faculty) {
    if (faculty[strlen(faculty) - 1] == '\n') {
        faculty[strlen(faculty) - 1] = '\0'; // Remove newline character from faculty name
    }
    // Set student ID, name, and faculty in the database
    database_student[record_count_students].student_ID = id;
    strcpy(database_student[record_count_students].name, name);
    strcpy(database_student[record_count_students].faculty, faculty);
    record_count_students++; // Increment student record count
}

// Function to add an exam record
void ADD_EXAM(int id, const char* type, int duration, char* name) {
    database_exam[record_count_exam].exam_ID = id; // Set exam ID
    // Determine the type of exam and set relevant information
    if (strcmp(type, "WRITTEN") == 0) {
        database_exam[record_count_exam].info.duration = duration; // Set duration for written exams
        database_exam[record_count_exam].type = WRITTEN; // Set type to WRITTEN
    } else if (strcmp(type, "DIGITAL") == 0) {
        strcpy(database_exam[record_count_exam].info.software, name); // Set software for digital exams
        database_exam[record_count_exam].type = DIGITAL; // Set type to DIGITAL
    }
    record_count_exam++; // Increment exam record count
}

// Function to add a grade record
void ADD_Grade(int exam_id, int student_id, int grade) {
    // Set exam ID, student ID, and grade in the grade database
    database_grade[record_count_grade].exam_ID = exam_id;
    database_grade[record_count_grade].student_ID = student_id;
    database_grade[record_count_grade].grade = grade;
    record_count_grade++; // Increment grade record count
}

// Function to find a student by ID
struct Student* find_person(int id) {
    for (int i = 0; i < record_count_students; i++) {  // Loop through all student records
        if (database_student[i].student_ID == id) {  // Check for matching student ID
            return &database_student[i];  // Return pointer to the found student record
        }
    }
    return NULL;  // Return NULL if not found
}

// Function to find an exam by ID
struct Exam* find_exam(int id) {
    for (int i = 0; i < record_count_exam; i++) {  // Loop through all exam records
        if (database_exam[i].exam_ID == id) {  // Check for matching exam ID
            return &database_exam[i];  // Return pointer to the found exam record
        }
    }
    return NULL;  // Return NULL if not found
}

// Function to search for a student and print their information
struct Student* SearchStudent(int id, FILE *fileout) {
    for (int i = 0; i < record_count_students; i++) {  // Loop through all student records
        if (database_student[i].student_ID == id) {  // Check for matching student ID
            // Print student details to the output file
            fprintf(fileout, "ID: %d, Name: %s, Faculty: %s\n", database_student[i].student_ID, database_student[i].name, database_student[i].faculty);
            return &database_student[i];  // Return pointer to the found student record
        }
    }
    return NULL; // Return NULL if not found
}

// Function to search for a student's grade in an exam and print details
struct Student* SearchGrade(int id_student, int id_exam, FILE *fileout) {
    int found = 0; // Flag to check if a record was found
    for (int i = 0; i < record_count_students; i++) {  // Loop through all student records
        if (database_student[i].student_ID == id_student) { // Check for matching student ID
            for (int j = 0; j < record_count_exam; j++) { // Loop through all exam records
                if (database_exam[j].exam_ID == id_exam) { // Check for matching exam ID
                    for (int k = 0; k < record_count_grade; k++) { // Loop through all grade records
                        if (database_grade[k].exam_ID == id_exam && database_grade[k].student_ID == id_student) { // Check for matching exam and student ID
                            found = 1; // Set found flag
                            // Clean up software name if it has a newline character
                            if (database_exam[j].info.software[strlen(database_exam[j].info.software) - 1] == '\n') {
                                database_exam[j].info.software[strlen(database_exam[j].info.software) - 1] = '\0';
                            }
                            // Print grade information based on the exam type
                            if (database_exam[j].type == WRITTEN) {
                                fprintf(fileout, "Exam: %d, Student: %d, Name: %s, Grade: %d, Type: WRITTEN, Info: %d\n", database_exam[j].exam_ID, database_student[i].student_ID, database_student[i].name, database_grade[k].grade, database_exam[j].info.duration);
                            } else if (database_exam[j].type == DIGITAL) {
                                fprintf(fileout, "Exam: %d, Student: %d, Name: %s, Grade: %d, Type: DIGITAL, Info: %s\n", database_exam[j].exam_ID, database_student[i].student_ID, database_student[i].name, database_grade[k].grade, database_exam[j].info.software);
                            }
                        }
                    }
                }
            }
        }
    }
    if (!found) {
        fprintf(fileout, "Student not found\n"); // Print if student is not found
    }
}

// Function to update exam information
void UPDATE_EXAM(int id, const char* type, int duration, char* name) {
    if (record_count_exam < MAX_RECORDS) { // Check if there is space for more records
        if (strcmp(type, "WRITTEN") == 0) {
            database_exam[id].info.duration = duration; // Update duration for written exams
            database_exam[id].type = WRITTEN; // Set type to WRITTEN
        } else if (strcmp(type, "DIGITAL") == 0) {
            strcpy(database_exam[id].info.software, name); // Update software for digital exams
            database_exam[id].type = DIGITAL; // Set type to DIGITAL
        }
    } else {
        printf("База данных полна.\n"); // Print message if the database is full
    }
}

// Function to update a grade record
void UPDATE_GRADE(int exam_id, int student_id, int grade) {
    for (int i = 0; i < record_count_grade; i++) { // Loop through all grade records
        if (database_grade[i].exam_ID == exam_id && database_grade[i].student_ID == student_id) { // Check for matching exam and student ID
            database_grade[i].grade = grade; // Update the grade
        }
    }
}

// Function to delete a student record
void delete_person(int id) {
    for (int i = 0; i < record_count_students; i++) { // Loop through all student records
        if (database_student[i].student_ID == id) { // Check for matching student ID
            for (int j = i; j < record_count_students - 1; j++) { // Shift subsequent records left
                database_student[j] = database_student[j + 1];
            }
            record_count_students--; // Decrement student record count
            break; // Exit the loop after deletion
        }
    }
    for (int i = 0; i < record_count_grade; i++) { // Loop through all grade records
        if (database_grade[i].student_ID == id) { // Check for matching student ID
            for (int j = i; j < record_count_grade - 1; j++) { // Shift subsequent records left
                database_grade[j] = database_grade[j + 1];
            }
            record_count_grade--; // Decrement grade record count
        }
    }
}

// Function to print all student records to an output file
void print_Student_database(FILE *fileout) {
    for (int i = 0; i < record_count_students; i++) { // Loop through all student records
        if (database_student[i].faculty[strlen(database_student[i].faculty) - 1] == '\n') {
            database_student[i].faculty[strlen(database_student[i].faculty) - 1] = '\0'; // Clean up faculty name
        }
        // Print student details to the output file
        fprintf(fileout, "ID: %d, Name: %s, Faculty: %s\n", database_student[i].student_ID, database_student[i].name, database_student[i].faculty);
    }
}
 int main(void) {
    FILE *file; // File pointer for input file
    FILE *fileout = fopen("output.txt", "w"); // Open output file for writing

    // Open the input file for reading
    file = fopen("input.txt", "r");

    char current_command[100]; // Buffer to store the current command
    char ch; // Variable to store characters (not used in this snippet)

    // Read each line from the input file until EOF
    while (fgets(current_command, sizeof(current_command), file)) {
        // Prepare to split the current command into separate tokens
        char *arr_a[4]; // Array to hold command parts
        int i = 0; // Token index

        // Split the string 'current_command' into separate words
        char *token2 = strtok(current_command, " ");

        // Save each substring into the 'arr_a' array
        while (token2 != NULL) {
            arr_a[i] = token2; // Store token in array
            i++;
            token2 = strtok(NULL, " "); // Get the next token
        }

        // Command handling based on the first token (command type)
        if (strcmp(arr_a[0], "ADD_STUDENT") == 0) {
            // Check if student already exists
            if (find_person(atoi(arr_a[1])) == NULL) {
                // Validate student name
                if ((contains_digit(arr_a[2]) == 0) && (strlen(arr_a[2]) <= 20) && string_check(arr_a[2]) == 0) {
                    // Validate faculty name
                    if ((contains_digit(arr_a[3]) == 0) && (4 <= strlen(arr_a[3])) && (strlen(arr_a[3]) <= 30) && string_check(arr_a[3]) == 0) {
                        // Validate student ID
                        if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1])) && (atoi(arr_a[1]) <= 1000)) {
                            // Add the student to the database
                            ADD_STUDENT(atoi(arr_a[1]), arr_a[2], arr_a[3]);
                            fprintf(fileout, "Student: %d added\n", atoi(arr_a[1])); // Log the addition
                        } else {
                            fprintf(fileout, "Invalid student id\n"); // Log invalid student ID error
                        }
                    } else {
                        fprintf(fileout, "Invalid faculty\n"); // Log invalid faculty error
                    }
                } else {
                    fprintf(fileout, "Invalid name\n"); // Log invalid name error
                }
            } else {
                fprintf(fileout, "Student: %d already exists\n", atoi(arr_a[1])); // Log existing student error
            }
        } else if (strcmp(arr_a[0], "ADD_EXAM") == 0) {
            // Check if exam already exists
            if (find_exam(atoi(arr_a[1])) == NULL) {
                // Check for WRITTEN exam type
                if (strcmp(arr_a[2], "WRITTEN") == 0) {
                    // Validate exam ID
                    if ((contains_char(arr_a[1]) == 0) && (0 < atoi(arr_a[1])) && (atoi(arr_a[1]) < 500)) {
                        // Validate exam duration
                        if ((contains_char(arr_a[3]) == 0) && (40 <= atoi(arr_a[3])) && (atoi(arr_a[3]) <= 180)) {
                            ADD_EXAM(atoi(arr_a[1]), arr_a[2], atoi(arr_a[3]), NULL); // Add WRITTEN exam
                            fprintf(fileout, "Exam: %d added\n", atoi(arr_a[1])); // Log the addition
                        } else {
                            fprintf(fileout, "Invalid duration\n"); // Log invalid duration error
                        }
                    } else {
                        fprintf(fileout, "Invalid exam id\n"); // Log invalid exam ID error
                    }
                } else if (strcmp(arr_a[2], "DIGITAL") == 0) {
                    // Check for DIGITAL exam type
                    if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1])) && (atoi(arr_a[1]) < 500)) {
                        // Validate software name
                        if ((contains_digit(arr_a[3]) == 0) && (2 <= strlen(arr_a[3])) && (strlen(arr_a[3]) <= 20) && string_check(arr_a[3]) == 0) {
                            ADD_EXAM(atoi(arr_a[1]), arr_a[2], NULL, arr_a[3]); // Add DIGITAL exam
                            fprintf(fileout, "Exam: %d added\n", atoi(arr_a[1])); // Log the addition
                        } else {
                            fprintf(fileout, "Invalid software\n"); // Log invalid software error
                        }
                    } else {
                        fprintf(fileout, "Invalid exam id\n"); // Log invalid exam ID error
                    }
                } else {
                    fprintf(fileout, "Invalid exam type\n"); // Log invalid exam type error
                }
            } else {
                fprintf(fileout, "Exam: %d already exists\n", atoi(arr_a[1])); // Log existing exam error
            }
        } else if (strcmp(arr_a[0], "ADD_GRADE") == 0) {
            // Check for valid exam ID
            char *endptr;
            if ((contains_char(arr_a[1]) == 0) && (0 <= strtol(arr_a[1], &endptr, 10)) && (strtol(arr_a[1], &endptr, 10) <= 500)) {
                // Validate student ID
                if ((contains_char(arr_a[2]) == 0) && (0 <= atoi(arr_a[2])) && (atoi(arr_a[2]) <= 1000)) {
                    // Validate grade
                    if ((contains_char(arr_a[3]) == 0) && (atoi(arr_a[3]) <= 100) && (atoi(arr_a[3]) >= 0)) {
                        // Check if exam and student exist
                        if (find_exam(atoi(arr_a[1])) != NULL) {
                            if (find_person(atoi(arr_a[2])) != NULL) {
                                ADD_Grade(atoi(arr_a[1]), atoi(arr_a[2]), atoi(arr_a[3])); // Add grade
                                fprintf(fileout, "Grade %d added for the student: %d\n", atoi(arr_a[3]), atoi(arr_a[2])); // Log the addition
                            } else {
                                fprintf(fileout, "Student not found\n"); // Log student not found error
                            }
                        } else {
                            fprintf(fileout, "Exam not found\n"); // Log exam not found error
                        }
                    } else {
                        fprintf(fileout, "Invalid grade\n"); // Log invalid grade error
                    }
                } else {
                    fprintf(fileout, "Invalid student id\n"); // Log invalid student ID error
                }
            } else {
                fprintf(fileout, "Invalid exam id\n"); // Log invalid exam ID error
            }
        } else if (strcmp(arr_a[0], "SEARCH_STUDENT") == 0) {
            // Validate student ID for searching
            if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1])) && (atoi(arr_a[1]) <= 1000)) {
                if (find_person(atoi(arr_a[1])) != NULL) {
                    SearchStudent(atoi(arr_a[1]), fileout); // Perform student search
                } else {
                    fprintf(fileout, "Student not found\n"); // Log student not found error
                }
            } else {
                fprintf(fileout, "Invalid student id\n"); // Log invalid student ID error
            }
        } else if (strcmp(arr_a[0], "SEARCH_GRADE") == 0) {
            // Validate exam ID for searching grades
            if ((contains_char(arr_a[1]) == 0) && (0 <= atoi(arr_a[1])) && (atoi(arr_a[1]) <= 500)) {
                // Validate student ID
                if ((contains_char(arr_a[2]) == 0) && (0 <= atoi(arr_a[2])) && (atoi(arr_a[2]) <= 1000)) {
                    if (find_person(atoi(arr_a[2])) != NULL) {
                        if (find_exam(atoi(arr_a[1])) != NULL) {
                            SearchGrade(atoi(arr_a[2]), atoi(arr_a[1]), fileout); // Perform grade search
                        } else {
                            fprintf(fileout, "Exam not found\n"); // Log exam not found error
                        }
                    } else {
                        fprintf(fileout, "Student not found\n"); // Log student not found error
                    }
                } else {
                    fprintf(fileout, "Invalid student id\n"); // Log invalid student ID error
                }
            } else {
                fprintf(fileout, "Invalid exam id\n"); // Log invalid exam ID error
            }
        } else if (strcmp(arr_a[0], "UPDATE_EXAM") == 0) {
            // Check if the exam type is WRITTEN
            if (strcmp(arr_a[2], "WRITTEN") == 0) {
                // Validate exam duration
                if ((contains_char(arr_a[3]) == 0) && (40 <= atoi(arr_a[3])) && (atoi(arr_a[3]) <= 180)) {
                    UPDATE_EXAM(atoi(arr_a[1]), arr_a[2], atoi(arr_a[3]), NULL); // Update WRITTEN exam
                    fprintf(fileout, "Exam: %d updated\n", atoi(arr_a[1])); // Log the update
                } else {
                    fprintf(fileout, "Invalid duration\n"); // Log invalid duration error
                }
            } else if (strcmp(arr_a[2], "DIGITAL") == 0) {
                // Check for DIGITAL exam type
                if ((contains_digit(arr_a[3]) == 0) && (2 <= strlen(arr_a[3])) && (strlen(arr_a[3]) <= 20) && string_check(arr_a[3]) == 0) {
                    UPDATE_EXAM(atoi(arr_a[1]), arr_a[2], NULL, arr_a[3]); // Update DIGITAL exam
                    fprintf(fileout, "Exam: %d updated\n", atoi(arr_a[1])); // Log the update
                } else {
                    fprintf(fileout, "Invalid software\n"); // Log invalid software error
                }
            } else {
                fprintf(fileout, "Invalid exam type\n"); // Log invalid exam type error
            }
        } else if (strcmp(arr_a[0], "UPDATE_GRADE") == 0) {
            // Validate grade for update
            if ((contains_char(arr_a[3]) == 0) && (atoi(arr_a[3]) <= 100) && (atoi(arr_a[3]) >= 0)) {
                UPDATE_GRADE(atoi(arr_a[1]), atoi(arr_a[2]), atoi(arr_a[3])); // Update grade
                fprintf(fileout, "Grade %d updated for the student: %d\n", atoi(arr_a[3]), atoi(arr_a[2])); // Log the update
            } else {
                fprintf(fileout, "Invalid grade\n"); // Log invalid grade error
            }
        } else if (strcmp(arr_a[0], "LIST_ALL_STUDENTS\n") == 0) {
            print_Student_database(fileout); // List all students in the database
        } else if (strcmp(arr_a[0], "DELETE_STUDENT") == 0) {
            delete_person(atoi(arr_a[1])); // Delete student from database
            fprintf(fileout, "Student: %d deleted\n", atoi(arr_a[1])); // Log the deletion
        } else if (strcmp(arr_a[0], "END\n") == 0) {
            fclose(file); // Close input file
            fclose(fileout); // Close output file
            return 0; // Exit the program
        }
    }

    fclose(file); // Ensure the input file is closed
    fclose(fileout); // Ensure the output file is closed
    return 0; // Exit the program successfully
}