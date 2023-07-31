#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // ... (all the necessary header files and definitions)
#include <time.h>
#include <stdbool.h>

#define MAX_STUDENTS 1000
#define MAX_NAME_LENGTH 50
#define MAX_GROUPS 500

// Structure to represent a student with name and group number
typedef struct {
    char name[MAX_NAME_LENGTH];
    int group;
} Student;


// Function to clear the console (works for both Windows and macOS/Linux)
void clearConsole() {
#ifdef _WIN32
    // For Windows
    system("cls");
#else
    // For macOS and Linux
    printf("\033[2J\033[H");
#endif
}

// Function to generate random groups for the students
void generateGroups(Student students[], int numStudents, int numGroups) {
    for (int i = 0; i < numStudents; i++) {
        students[i].group = i % numGroups + 1;
    }

    // Shuffle the groups randomly
    for (int i = 0; i < numStudents; i++) {
        int j = rand() % numStudents;
        int temp = students[i].group;
        students[i].group = students[j].group;
        students[j].group = temp;
    }
}


// Function to print the group assignments
void printGroups(Student students[], int numStudents, int numGroups) {
    printf("\nGROUP ASSIGNMENTS:\n");
    for (int groupNum = 1; groupNum <= numGroups; groupNum++) {
        printf("GROUP %d:\n", groupNum);
        int membersInGroup = 0; // Counter to track the number of members in the group
        for (int i = 0; i < numStudents; i++) {
            if (students[i].group == groupNum) {
                printf("- %s\n", students[i].name);
                membersInGroup++;
            }
        }
        printf("Number of members in group %d: %d\n", groupNum, membersInGroup);
        printf("\n");
    }
}


// Function to display current student data
void displayCurrentStudentData(Student students[], int numStudents, int numGroups) {
    printf("\n-------- CURRENT STUDENT DATA --------\n");
    printGroups(students, numStudents, numGroups);
    printf("\nNUMBER OF STUDENTS: %d\n", numStudents);
    printf("NUMBER OF GROUPS: %d\n", numGroups);
    printf("-------------------------------------\n");
}


// Function to save group assignments to a file
void saveToFile(char filename[], Student students[], int numStudents, int numGroups) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("ERROR OPENING FILE!\n");
        return;
    }

    fprintf(file, "GROUP ASSIGNMENTS:\n");
    for (int groupNum = 1; groupNum <= numGroups; groupNum++) {
        fprintf(file, "GROUP %d:\n", groupNum);
        int membersInGroup = 0; // Counter to track the number of members in the group
        for (int i = 0; i < numStudents; i++) {
            if (students[i].group == groupNum) {
                fprintf(file, "- %s\n", students[i].name);
                membersInGroup++;
            }
        }
        fprintf(file, "NUMBER OF MEMBERS IN GROUP %d: %d\n", groupNum, membersInGroup);
        fprintf(file, "\n");
    }

    // Write the total number of students and groups to the file
    fprintf(file, "NUMBER OF STUDENTS: %d\n", numStudents);
    fprintf(file, "NUMBER OF GROUPS: %d\n", numGroups);

    fclose(file);
    printf("\nYOUR FILE <%s> HAS BEEN GENERATED!\n", filename);
}

// Function to read an integer input from the user
int readIntInput() {
    int input;
    char ch;
    while (1) {
        if (scanf("%d", &input) != 1) {
            // Clear input buffer
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("INVALID INPUT! PLEASE ENTER 0 OR 1 : ");
        } else {
            // Clear input buffer if needed
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            return input;
        }
    }
}

// Function to read student names from a file and populate the students array
int readStudentsFromFile(char filename[], Student students[], int *numStudents) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR OPENING FILE '%s'!\n", filename);
        return 0;
    }

    *numStudents = 0;
    while ((*numStudents < MAX_STUDENTS) && (fscanf(file, "%s", students[*numStudents].name) == 1)) {
        (*numStudents)++;
    }

    fclose(file);
    return 1;
}
// Function to read an integer input in a specific range
int readIntInputInRange(int min, int max) {
    int input;
    char ch;
    while (1) {
        if (scanf("%d", &input) != 1) {
            // Clear input buffer
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("\nINVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (%d-%d): ", min, max);
        } else if (input < min || input > max) {
            printf("\nINVALID INPUT! PLEASE ENTER A VALUE IN THE RANGE (%d-%d): ", min, max);
        } else {
            // Clear input buffer if needed
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            return input;
        }
    }
}



int main() {
    // Variable declarations
    char filename[100];
    int userInput;
    Student students[MAX_STUDENTS];
    int numStudents, numGroups;
    bool flag1 = true;

    // Welcome message
    printf("\n-------------  WELCOME TO THE VIRTUAL GROUP CREATOR  -------------\n\n\n");

    do{

    // Ask the user whether to add names using a text file or by typing manually
    printf("ARE YOU WANT TO ADD NAMES USING TEXT FILES OR BY BY TYPING ? \n");
    printf("IF YOU USING TEXT FILE ENTER 1 ELSE ENTER 0 : ");
    userInput = readIntInputInRange(0,1);

    switch(userInput){
    case 1: // Case 1: Read student names from a file
        printf("\nENTER THE FILE NAME TO SAVE THE GROUP ASSIGNMENTS (THIS FILE WILL BE CREATED IN THE PROJECT FOLDER. NAME SHOULD BE LIKE THIS - name.txt ): ");
        scanf("%s", filename);

                char newFilename[100]; // New variable to store the latest file name

                printf("\nENTER THE FILE NAME TO READ STUDENT NAMES FROM (name.txt): ");
                scanf("%s", newFilename); // Use newFilename to store the latest file name

                int numStudentsFromFile;
                if (readStudentsFromFile(newFilename, students, &numStudentsFromFile)) {
                    printf("\nREAD %d STUDENT NAMES FROM FILE '%s':\n", numStudentsFromFile, newFilename);
                    for (int i = 0; i < numStudentsFromFile; i++) {
                        printf("%s\n", students[i].name);
                    }

                    printf("\nENTER THE NUMBER OF GROUPS : ");
                    while (scanf("%d", &numGroups) != 1 || numGroups < 1 || numGroups > MAX_GROUPS) {
                        printf("\nINVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (1-%d): ", MAX_GROUPS);
                        while (getchar() != '\n'); // Clear input buffer
                    }

                    generateGroups(students, numStudentsFromFile, numGroups);
                    printGroups(students, numStudentsFromFile, numGroups);
                    numStudents = numStudentsFromFile; // Update the numStudents value for other options
                    saveToFile(filename, students, numStudents, numGroups);
                }

                flag1 =false;
        break;
    case 0: // Case 0: Manually input student names
        printf("\nENTER THE FILE NAME TO SAVE THE GROUP ASSIGNMENTS (NAME SHOULD BE LIKE THIS - name.txt): ");
        scanf("%s", filename);

        printf("\nENTER THE NUMBER OF STUDENTS (NUMERIC) : ");
    while (scanf("%d", &numStudents) != 1 || numStudents < 1 || numStudents > MAX_STUDENTS) {
        printf("INVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (1-%d): ", MAX_STUDENTS);
        while (getchar() != '\n'); // Clear input buffer
    }
    printf("\n");

    for (int i = 0; i < numStudents; i++) {
        printf("ENTER THE NAME/NUMBER OF STUDENT %d : ", i + 1);
        scanf("%s", students[i].name);
    }

    printf("\nENTER THE NUMBER OF GROUPS : ");
    while (scanf("%d", &numGroups) != 1 || numGroups < 1 || numGroups > MAX_GROUPS) {
        printf("INVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (1-%d) : ", MAX_GROUPS);
        while (getchar() != '\n'); // Clear input buffer
    }

    generateGroups(students, numStudents, numGroups);
    printGroups(students, numStudents, numGroups);
    saveToFile(filename, students, numStudents, numGroups);
    flag1 =false;
        break;
        default:
            printf("\n\nPLEASE ENTER VALID INPUT (0 or 1)...!\n\n");
        break;
    }
    }while(flag1);


    int choice;
    do {
        // Main menu options
        printf("\n\nOPTIONS :\n");
        printf("    1. REGENERATE THE GROUPS FROM THE EXISTING STUDENTS.\n");
        printf("    2. ADD NEW STUDENTS AND UPDATE THE GROUPS.\n");
        printf("    3. FIND A STUDENT.\n");
        printf("    4. RESTART PROCESS INPUT NAMES BY TYPING.\n");
        printf("    5. RESTART THE PROCESS BY INPUT STUDENT NAMES FROM A FILE.\n");
        printf("    6. EXIT.\n\n");

        printf("ENTER YOUR OPTION (1, 2, 3, 4, 5, OR 6) : ");
        while (scanf("%d", &choice) != 1) {
            printf("INVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE : ");
            while (getchar() != '\n'); // Clear input buffer
        }

        switch (choice) {
            case 1:
                // Regenerate groups from the existing students
                clearConsole();
                generateGroups(students, numStudents, numGroups);
                printf("\nRegenerated ");
                printGroups(students, numStudents, numGroups);
                printf("\n");
                saveToFile(filename, students, numStudents, numGroups);
                break;
            case 2: {
                // Add new students and update groups
                clearConsole();
                int additionalStudents, newNumGroups;

                displayCurrentStudentData(students, numStudents, numGroups);

                printf("\nENTER THE NUMBER OF ADDITIONAL STUDENTS TO ADD (NUMERIC) : ");
                while (scanf("%d", &additionalStudents) != 1 || additionalStudents < 1 || numStudents + additionalStudents > MAX_STUDENTS) {
                    printf("INVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (1-%d) : ", MAX_STUDENTS - numStudents);
                    while (getchar() != '\n'); // Clear input buffer
                }

                for (int i = 0; i < additionalStudents; i++) {
                    printf("ENTER THE NAME/NUMBER STUDENT OF STUDENT %d : ", numStudents + i + 1);
                    scanf("%s", students[numStudents + i].name);
                }

                printf("\nENTER THE NEW NUMBER OF GROUPS (NUMERIC, SHOULD BE LESS THAN OR EQUAL TO THE NUMBER OF STUDENTS) : ");
                while (scanf("%d", &newNumGroups) != 1 || newNumGroups < 1 || newNumGroups > numStudents + additionalStudents) {
                    printf("INVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (1-%d): ", numStudents + additionalStudents);
                    while (getchar() != '\n'); // Clear input buffer
                }

                generateGroups(students, numStudents + additionalStudents, newNumGroups);
                printGroups(students, numStudents + additionalStudents, newNumGroups);
                numStudents += additionalStudents;
                numGroups = newNumGroups;

                printf("ENTER THE FILE NAME TO SAVE THE GROUP ASSIGNMENTS (NAME SHOULD BE LIKE THIS - name.txt): ");
                scanf("%s", filename);
                saveToFile(filename, students, numStudents, numGroups);
                break;
            }
            case 3:
                // Find a student by name
                clearConsole();
                char searchName[MAX_NAME_LENGTH];
                int found = 0;

                do {
                    printf("ENTER STUDENT NAME TO FIND : ");
                    scanf("%s", searchName);

                    printf("\nSearch Result:\n");

                    // Count the number of students with the given name in each group
                    int countByGroup[MAX_GROUPS] = {0};
                    for (int i = 0; i < numStudents; i++) {
                        if (strcmp(students[i].name, searchName) == 0) {
                            countByGroup[students[i].group - 1]++;
                            found = 1;
                        }
                    }

                    if (found) {
                        printf("%s - ", searchName);
                        int firstPrinted = 0;
                        for (int groupNum = 1; groupNum <= numGroups; groupNum++) {
                            if (countByGroup[groupNum - 1] > 0) {
                                if (firstPrinted) {
                                    printf(" & ");
                                }
                                printf("%d MEMBERS IN GROUP %d", countByGroup[groupNum - 1], groupNum);
                                firstPrinted = 1;
                            }
                        }
                        printf("\n");
                    } else {
                        printf("STUDENT %s NOT FOUND!\n", searchName);
                    }

                    int continueSearch;
                    do {
                        printf("\nDO YOU WANT TO FIND MORE STUDENTS? (1 FOR YES, 0 FOR NO) : ");
                        continueSearch = readIntInput();
                        if (continueSearch != 1 && continueSearch != 0) {
                            printf("INVALID INPUT! PLEASE ENTER EITHER 1 OR 0.\n");
                        }
                    } while (continueSearch != 1 && continueSearch != 0);

                    if (continueSearch != 1) {
                        break;
                    }
                } while (1);

                break;
            case 4:
                // Restart the process of inputting names manually
                clearConsole();
                printf("ENTER THE FILE NAME TO SAVE THE GROUP ASSIGNMENTS (NAME SHOULD BE LIKE THIS - name.txt): ");
                scanf("%s", filename);

                printf("\nENTER THE NUMBER OF STUDENTS (NUMERIC) : ");
                while (scanf("%d", &numStudents) != 1 || numStudents < 1 || numStudents > MAX_STUDENTS) {
                    printf("INVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (1-%d): ", MAX_STUDENTS);
                    while (getchar() != '\n'); // Clear input buffer
                }
                printf("\n");

                for (int i = 0; i < numStudents; i++) {
                    printf("ENTER THE NAME/NUMBER STUDENT OF STUDENT %d : ", i + 1);
                    scanf("%s", students[i].name);
                }

                printf("\nENTER THE NUMBER OF GROUPS : ");
                while (scanf("%d", &numGroups) != 1 || numGroups < 1 || numGroups > MAX_GROUPS) {
                    printf("INVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (1-%d): ", MAX_GROUPS);
                    while (getchar() != '\n'); // Clear input buffer
                }

                generateGroups(students, numStudents, numGroups);
                printGroups(students, numStudents, numGroups);
                saveToFile(filename, students, numStudents, numGroups);
                break;
            case 5:
                // Restart the process by inputting student names from a file
                clearConsole();
                char newFilename[100]; // New variable to store the latest file name

                printf("ENTER THE FILENAME TO READ STUDENT NAMES (NAME SHOULD BE LIKE THIS - name.txt): ");
                scanf("%s", newFilename); // Use newFilename to store the latest file name

                int numStudentsFromFile;
                if (readStudentsFromFile(newFilename, students, &numStudentsFromFile)) {
                    printf("\nRead %d student names from file '%s':\n", numStudentsFromFile, newFilename);
                    for (int i = 0; i < numStudentsFromFile; i++) {
                        printf("%s\n", students[i].name);
                    }

                    printf("\nENTER THE NUMBER OF GROUPS : ");
                    while (scanf("%d", &numGroups) != 1 || numGroups < 1 || numGroups > MAX_GROUPS) {
                        printf("INVALID INPUT! PLEASE ENTER A VALID NUMERIC VALUE (1-%d): ", MAX_GROUPS);
                        while (getchar() != '\n'); // Clear input buffer
                    }

                    generateGroups(students, numStudentsFromFile, numGroups);
                    printGroups(students, numStudentsFromFile, numGroups);

                    numStudents = numStudentsFromFile; // Update the numStudents value for other options

                    // Update the filename variable with the latest file name
                    strcpy(filename, newFilename);

                    printf("\nENTER THE FILENAME TO SAVE THE GROUP ASSIGNMENTS : ");
                    scanf("%s", filename);
                    saveToFile(filename, students, numStudents, numGroups);
                }

                break;

            case 6:
                 // Exit the program
                printf("\n\n-----  EXITING THE PROGRAM. GOODBYE!  -----\n\n\n");
                break;
            default:
                printf("INVALID CHOICE! PLEASE ENTER A VALID OPTION.\n\n");
                break;
        }
    } while (choice != 6);

    return 0;
}
