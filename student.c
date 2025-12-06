#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"
#define MAX_NAME_LENGTH 50
#define MAX_BUFFER 100

struct Student {
    int roll;
    char name[MAX_NAME_LENGTH];
    float marks;
};

char currentRole[10];
char currentName[MAX_NAME_LENGTH];

/* -------------------------------------------------------
                    FUNCTION DECLARATIONS
--------------------------------------------------------*/
int loginSystem();
void mainMenu();
void clearInputBuffer();
int getValidInteger(const char* prompt, int min, int max);
float getValidFloat(const char* prompt, float min, float max);
void getValidString(const char* prompt, char* str, int maxLen);
int fileExists(const char* filename);
void initializeFiles();
int isDuplicateRoll(int roll);

void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void showStatistics();

/* -------------------------------------------------------
                        MAIN FUNCTION
--------------------------------------------------------*/
int main() {
    initializeFiles();
    printf("\n========================================\n");
    printf("  STUDENT MANAGEMENT SYSTEM\n");
    printf("========================================\n\n");
    
    if (loginSystem()) {
        printf("\nLogin Successful! Welcome, %s (%s)\n", currentName, currentRole);
        mainMenu();
        printf("\nThank you for using the system. Goodbye!\n");
    } else {
        printf("\nAccess Denied. Exiting...\n");
    }
    return 0;
}

/* -------------------------------------------------------
                        LOGIN SYSTEM
--------------------------------------------------------*/
int loginSystem() {
    char username[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];
    printf("===== LOGIN =====\n");
    printf("Username: ");
    if (scanf("%49s", username) != 1) {
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer();
    
    int attempts = 3;
    while (attempts > 0) {
        printf("Password: ");
        int i = 0;
        char ch;
        while ((ch = _getch()) != '\r' && ch != '\n' && i < MAX_NAME_LENGTH - 1) {
            if (ch == '\b' && i > 0) {
                i--;
                printf("\b \b");
            } else if (ch != '\b' && ch != '\r' && ch != '\n') {
                password[i++] = ch;
                printf("*");
            }
        }
        password[i] = '\0';
        printf("\n");
        
        if (strlen(password) == 0) {
            printf("Password cannot be empty!\n");
            attempts--;
            if (attempts > 0) {
                printf("%d attempts left.\n", attempts);
            }
            continue;
        }
        
        FILE *fp = fopen(CREDENTIAL_FILE, "r");
        if (!fp) {
            printf("Error: credentials.txt missing!\n");
            return 0;
        }
        
        char fileUser[MAX_NAME_LENGTH], filePass[MAX_NAME_LENGTH], fileRole[10];
        int found = 0;
        while (fscanf(fp, "%49s %49s %9s", fileUser, filePass, fileRole) == 3) {
            if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
                strncpy(currentRole, fileRole, sizeof(currentRole) - 1);
                currentRole[sizeof(currentRole) - 1] = '\0';
                strncpy(currentName, fileUser, sizeof(currentName) - 1);
                currentName[sizeof(currentName) - 1] = '\0';
                found = 1;
                break;
            }
        }
        fclose(fp);
        
        if (found) {
            return 1;
        } else {
            attempts--;
            if (attempts > 0) {
                printf("Incorrect password. %d attempts left.\n", attempts);
            } else {
                printf("Too many failed attempts. Access denied.\n");
                return 0;
            }
        }
    }
    return 0;
}

/* -------------------------------------------------------
                       MAIN MENU ROUTER
--------------------------------------------------------*/
void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else if (strcmp(currentRole, "USER") == 0)
        userMenu();
    else
        guestMenu();
}

/* -------------------------------------------------------
                          ADMIN MENU
--------------------------------------------------------*/
void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. View Statistics\n");
        printf("7. Logout\n");

        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear input buffer
            choice = 0;
            continue;
        }
        while(getchar() != '\n'); // Clear input buffer

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: showStatistics(); break;
            case 7: break;
            default: printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 7);
}

/* -------------------------------------------------------
                      STAFF MENU (Limited)
--------------------------------------------------------*/
void staffMenu() {
    int choice;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Update Student Marks Only\n");
        printf("4. View Statistics\n");
        printf("5. Logout\n");

        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = 0;
            continue;
        }
        while(getchar() != '\n');

        switch(choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
            case 4: showStatistics(); break;
            case 5: break;
            default: printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5);
}

/* -------------------------------------------------------
                       USER MENU (View Only)
--------------------------------------------------------*/
void userMenu() {
    int choice;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. View Statistics\n");
        printf("4. Logout\n");

        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = 0;
            continue;
        }
        while(getchar() != '\n');

        switch(choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: showStatistics(); break;
            case 4: break;
            default: printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 4);
}

/* -------------------------------------------------------
                       GUEST MENU (View Only)
--------------------------------------------------------*/
void guestMenu() {
    printf("\n===== GUEST ACCESS =====\n");
    printf("Limited to viewing only.\n\n");
    displayStudents();
}

/* -------------------------------------------------------
                      ADD STUDENT
--------------------------------------------------------*/
void addStudent() {
    struct Student s;
    
    printf("\n===== ADD NEW STUDENT =====\n");
    
    // Get and validate roll number
    s.roll = getValidInteger("Enter Roll Number: ", 1, 999999);
    
    // Check for duplicate roll number
    if (isDuplicateRoll(s.roll)) {
        printf("Error: Roll number %d already exists!\n", s.roll);
        return;
    }
    
    // Get name
    getValidString("Enter Name (no spaces): ", s.name, MAX_NAME_LENGTH);
    
    // Get marks
    s.marks = getValidFloat("Enter Marks (0-100): ", 0.0, 100.0);
    
    FILE *fp = fopen(STUDENT_FILE, "a");
    if (!fp) {
        printf("Error: Unable to open file for writing!\n");
        return;
    }

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("\n*** Student Added Successfully! ***\n");
    printf("Roll: %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
}

/* -------------------------------------------------------
                    DISPLAY STUDENTS
--------------------------------------------------------*/
void displayStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n===== STUDENT LIST =====\n");
    printf("%-10s %-20s %-10s\n", "Roll", "Name", "Marks");
    printf("--------------------------------------------\n");

    // Skip header line if it exists
    char buffer[MAX_BUFFER];
    if (fgets(buffer, sizeof(buffer), fp)) {
        // Check if first line is header
        int testRoll;
        float testMarks;
        char testName[MAX_NAME_LENGTH];
        if (sscanf(buffer, "%d %s %f", &testRoll, testName, &testMarks) != 3) {
            // It's a header, continue
        } else {
            // First line is data, print it
            printf("%-10d %-20s %-10.2f\n", testRoll, testName, testMarks);
        }
    }

    int count = 0;
    while (fscanf(fp, "%d %49s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("%-10d %-20s %-10.2f\n", s.roll, s.name, s.marks);
        count++;
    }

    fclose(fp);
    
    if (count == 0 && feof(fp)) {
        printf("No student records to display.\n");
    }
    printf("--------------------------------------------\n");
    printf("Total Students: %d\n", count);
}

/* -------------------------------------------------------
                     SEARCH STUDENT
--------------------------------------------------------*/
void searchStudent() {
    struct Student s;
    int roll, found = 0;

    roll = getValidInteger("\nEnter Roll Number to Search: ", 1, 999999);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("Error: Unable to open student file.\n");
        return;
    }

    // Skip header line if exists
    char buffer[MAX_BUFFER];
    if (fgets(buffer, sizeof(buffer), fp)) {
        int testRoll;
        float testMarks;
        char testName[MAX_NAME_LENGTH];
        if (sscanf(buffer, "%d %s %f", &testRoll, testName, &testMarks) == 3) {
            // First line is data, check it
            if (testRoll == roll) {
                printf("\n===== RECORD FOUND =====\n");
                printf("Roll Number: %d\n", testRoll);
                printf("Name: %s\n", testName);
                printf("Marks: %.2f\n", testMarks);
                printf("========================\n");
                found = 1;
            }
        }
    }

    if (!found) {
        while (fscanf(fp, "%d %49s %f", &s.roll, s.name, &s.marks) == 3) {
            if (s.roll == roll) {
                printf("\n===== RECORD FOUND =====\n");
                printf("Roll Number: %d\n", s.roll);
                printf("Name: %s\n", s.name);
                printf("Marks: %.2f\n", s.marks);
                printf("========================\n");
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("\n*** Student with Roll Number %d not found. ***\n", roll);
    }

    fclose(fp);
}

/* -------------------------------------------------------
                     UPDATE STUDENT
--------------------------------------------------------*/
void updateStudent() {
    struct Student s;
    int roll, found = 0;

    roll = getValidInteger("\nEnter Roll Number to Update: ", 1, 999999);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp) {
        printf("Error: Unable to open student file.\n");
        if (temp) fclose(temp);
        return;
    }
    
    if (!temp) {
        printf("Error: Unable to create temporary file.\n");
        fclose(fp);
        return;
    }

    // Handle header line
    char buffer[MAX_BUFFER];
    if (fgets(buffer, sizeof(buffer), fp)) {
        int testRoll;
        float testMarks;
        char testName[MAX_NAME_LENGTH];
        if (sscanf(buffer, "%d %s %f", &testRoll, testName, &testMarks) == 3) {
            // First line is data, check if it needs update
            if (testRoll == roll) {
                printf("\nCurrent Record:\n");
                printf("Roll: %d, Name: %s, Marks: %.2f\n", testRoll, testName, testMarks);
                
                if (strcmp(currentRole, "STAFF") == 0) {
                    // Staff can only update marks
                    float newMarks = getValidFloat("Enter New Marks (0-100): ", 0.0, 100.0);
                    fprintf(temp, "%d %s %.2f\n", testRoll, testName, newMarks);
                } else {
                    // Admin can update name and marks
                    getValidString("Enter New Name: ", testName, MAX_NAME_LENGTH);
                    float newMarks = getValidFloat("Enter New Marks (0-100): ", 0.0, 100.0);
                    fprintf(temp, "%d %s %.2f\n", testRoll, testName, newMarks);
                }
                found = 1;
            } else {
                fprintf(temp, "%s", buffer);
            }
        } else {
            // It's a header
            fprintf(temp, "%s", buffer);
        }
    }

    while (fscanf(fp, "%d %49s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll && !found) {
            printf("\nCurrent Record:\n");
            printf("Roll: %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
            
            if (strcmp(currentRole, "STAFF") == 0) {
                // Staff can only update marks
                s.marks = getValidFloat("Enter New Marks (0-100): ", 0.0, 100.0);
            } else {
                // Admin can update name and marks
                getValidString("Enter New Name: ", s.name, MAX_NAME_LENGTH);
                s.marks = getValidFloat("Enter New Marks (0-100): ", 0.0, 100.0);
            }
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(STUDENT_FILE);
        rename("temp.txt", STUDENT_FILE);
        printf("\n*** Record Updated Successfully! ***\n");
    } else {
        remove("temp.txt");
        printf("\n*** Student with Roll Number %d not found. ***\n", roll);
    }
}

/* -------------------------------------------------------
                     DELETE STUDENT
--------------------------------------------------------*/
void deleteStudent() {
    struct Student s;
    int roll, found = 0;

    roll = getValidInteger("\nEnter Roll Number to Delete: ", 1, 999999);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp) {
        printf("Error: Unable to open student file.\n");
        if (temp) fclose(temp);
        return;
    }
    
    if (!temp) {
        printf("Error: Unable to create temporary file.\n");
        fclose(fp);
        return;
    }

    // Handle header line
    char buffer[MAX_BUFFER];
    if (fgets(buffer, sizeof(buffer), fp)) {
        int testRoll;
        float testMarks;
        char testName[MAX_NAME_LENGTH];
        if (sscanf(buffer, "%d %s %f", &testRoll, testName, &testMarks) == 3) {
            // First line is data
            if (testRoll == roll) {
                found = 1;
                printf("\nDeleting: Roll %d, Name: %s, Marks: %.2f\n", testRoll, testName, testMarks);
            } else {
                fprintf(temp, "%s", buffer);
            }
        } else {
            // It's a header
            fprintf(temp, "%s", buffer);
        }
    }

    while (fscanf(fp, "%d %49s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            found = 1;
            printf("\nDeleting: Roll %d, Name: %s, Marks: %.2f\n", s.roll, s.name, s.marks);
        } else {
            fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove(STUDENT_FILE);
        rename("temp.txt", STUDENT_FILE);
        printf("\n*** Record Deleted Successfully! ***\n");
    } else {
        remove("temp.txt");
        printf("\n*** Student with Roll Number %d not found. ***\n", roll);
    }
}

/* -------------------------------------------------------
                  GRADE STATISTICS
--------------------------------------------------------*/
void showStatistics() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n");
    printf("============================================================\n");
    printf("          GRADE STATISTICS & ANALYTICS                     \n");
    printf("============================================================\n\n");

    // Variables for statistics
    float totalMarks = 0.0;
    float highest = -1.0;
    float lowest = 101.0;
    int count = 0;
    int gradeA = 0, gradeB = 0, gradeC = 0, gradeD = 0, gradeF = 0;
    char topperName[MAX_NAME_LENGTH] = "";
    int topperRoll = 0;
    
    // Skip header line if exists
    char buffer[MAX_BUFFER];
    if (fgets(buffer, sizeof(buffer), fp)) {
        int testRoll;
        float testMarks;
        char testName[MAX_NAME_LENGTH];
        if (sscanf(buffer, "%d %s %f", &testRoll, testName, &testMarks) == 3) {
            // First line is data
            totalMarks += testMarks;
            count++;
            
            if (testMarks > highest) {
                highest = testMarks;
                strncpy(topperName, testName, MAX_NAME_LENGTH - 1);
                topperRoll = testRoll;
            }
            if (testMarks < lowest) lowest = testMarks;
            
            // Grade classification
            if (testMarks >= 90) gradeA++;
            else if (testMarks >= 80) gradeB++;
            else if (testMarks >= 70) gradeC++;
            else if (testMarks >= 60) gradeD++;
            else gradeF++;
        }
    }

    // Process remaining records
    while (fscanf(fp, "%d %49s %f", &s.roll, s.name, &s.marks) == 3) {
        totalMarks += s.marks;
        count++;
        
        if (s.marks > highest) {
            highest = s.marks;
            strncpy(topperName, s.name, MAX_NAME_LENGTH - 1);
            topperRoll = s.roll;
        }
        if (s.marks < lowest) lowest = s.marks;
        
        // Grade classification
        if (s.marks >= 90) gradeA++;
        else if (s.marks >= 80) gradeB++;
        else if (s.marks >= 70) gradeC++;
        else if (s.marks >= 60) gradeD++;
        else gradeF++;
    }

    fclose(fp);

    if (count == 0) {
        printf("No student records to analyze.\n");
        return;
    }

    float average = totalMarks / count;

    // Display statistics
    printf(">> OVERALL STATISTICS:\n");
    printf("------------------------------------------------------------\n");
    printf("   Total Students:        %d\n", count);
    printf("   Average Marks:         %.2f\n", average);
    printf("   Highest Marks:         %.2f\n", highest);
    printf("   Lowest Marks:          %.2f\n", lowest);
    printf("   Pass Rate:             %.1f%% (%d/%d)\n", 
           (count - gradeF) * 100.0 / count, count - gradeF, count);
    printf("\n");

    printf(">> TOP PERFORMER:\n");
    printf("------------------------------------------------------------\n");
    printf("   Roll: %d  |  Name: %s  |  Marks: %.2f\n", 
           topperRoll, topperName, highest);
    printf("\n");

    printf(">> GRADE DISTRIBUTION:\n");
    printf("------------------------------------------------------------\n");
    printf("   Grade A (90-100):      %d students  (%.1f%%)\n", 
           gradeA, gradeA * 100.0 / count);
    printf("   Grade B (80-89):       %d students  (%.1f%%)\n", 
           gradeB, gradeB * 100.0 / count);
    printf("   Grade C (70-79):       %d students  (%.1f%%)\n", 
           gradeC, gradeC * 100.0 / count);
    printf("   Grade D (60-69):       %d students  (%.1f%%)\n", 
           gradeD, gradeD * 100.0 / count);
    printf("   Grade F (Below 60):    %d students  (%.1f%%)\n", 
           gradeF, gradeF * 100.0 / count);
    printf("\n");

    // Visual bar chart
    printf(">> VISUAL GRADE DISTRIBUTION:\n");
    printf("------------------------------------------------------------\n");
    
    int maxBars = 50;
    int maxCount = gradeA;
    if (gradeB > maxCount) maxCount = gradeB;
    if (gradeC > maxCount) maxCount = gradeC;
    if (gradeD > maxCount) maxCount = gradeD;
    if (gradeF > maxCount) maxCount = gradeF;
    
    if (maxCount > 0) {
        printf("   A: ");
        for (int i = 0; i < (gradeA * maxBars / maxCount); i++) printf("#");
        printf(" %d\n", gradeA);
        
        printf("   B: ");
        for (int i = 0; i < (gradeB * maxBars / maxCount); i++) printf("#");
        printf(" %d\n", gradeB);
        
        printf("   C: ");
        for (int i = 0; i < (gradeC * maxBars / maxCount); i++) printf("#");
        printf(" %d\n", gradeC);
        
        printf("   D: ");
        for (int i = 0; i < (gradeD * maxBars / maxCount); i++) printf("#");
        printf(" %d\n", gradeD);
        
        printf("   F: ");
        for (int i = 0; i < (gradeF * maxBars / maxCount); i++) printf("#");
        printf(" %d\n", gradeF);
    }
    
    printf("\n");
    printf("============================================================\n");
}

/* -------------------------------------------------------
                    UTILITY FUNCTIONS
--------------------------------------------------------*/
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidInteger(const char* prompt, int min, int max) {
    int value;
    int validInput = 0;
    
    while (!validInput) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clearInputBuffer();
            if (value >= min && value <= max) {
                validInput = 1;
            } else {
                printf("Error: Please enter a number between %d and %d.\n", min, max);
            }
        } else {
            clearInputBuffer();
            printf("Error: Invalid input. Please enter a number.\n");
        }
    }
    return value;
}

float getValidFloat(const char* prompt, float min, float max) {
    float value;
    int validInput = 0;
    
    while (!validInput) {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1) {
            clearInputBuffer();
            if (value >= min && value <= max) {
                validInput = 1;
            } else {
                printf("Error: Please enter a number between %.2f and %.2f.\n", min, max);
            }
        } else {
            clearInputBuffer();
            printf("Error: Invalid input. Please enter a number.\n");
        }
    }
    return value;
}

void getValidString(const char* prompt, char* str, int maxLen) {
    int validInput = 0;
    
    while (!validInput) {
        printf("%s", prompt);
        char format[20];
        snprintf(format, sizeof(format), "%%%ds", maxLen - 1);
        if (scanf(format, str) == 1) {
            clearInputBuffer();
            
            // Check if string contains only alphanumeric characters
            int valid = 1;
            for (int i = 0; str[i] != '\0'; i++) {
                if (!isalnum(str[i]) && str[i] != '_' && str[i] != '-') {
                    valid = 0;
                    break;
                }
            }
            
            if (valid && strlen(str) > 0) {
                validInput = 1;
            } else {
                printf("Error: Name should contain only letters, numbers, underscore or hyphen.\n");
            }
        } else {
            clearInputBuffer();
            printf("Error: Invalid input.\n");
        }
    }
}

int fileExists(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}

void initializeFiles() {
    // Check if students.txt exists, if not create with header
    if (!fileExists(STUDENT_FILE)) {
        FILE *fp = fopen(STUDENT_FILE, "w");
        if (fp) {
            fprintf(fp, "roll name marks\n");
            fclose(fp);
        }
    }
    
    // Check if credentials.txt exists
    if (!fileExists(CREDENTIAL_FILE)) {
        FILE *fp = fopen(CREDENTIAL_FILE, "w");
        if (fp) {
            fprintf(fp, "admin admin123 ADMIN\n");
            fprintf(fp, "staff staff123 STAFF\n");
            fprintf(fp, "user user123 USER\n");
            fprintf(fp, "guest guest123 GUEST\n");
            fclose(fp);
        }
    }
}

int isDuplicateRoll(int roll) {
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) return 0;
    
    struct Student s;
    char buffer[MAX_BUFFER];
    
    // Skip/check first line
    if (fgets(buffer, sizeof(buffer), fp)) {
        int testRoll;
        float testMarks;
        char testName[MAX_NAME_LENGTH];
        if (sscanf(buffer, "%d %s %f", &testRoll, testName, &testMarks) == 3) {
            if (testRoll == roll) {
                fclose(fp);
                return 1;
            }
        }
    }
    
    while (fscanf(fp, "%d %49s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
    return 0;
}
