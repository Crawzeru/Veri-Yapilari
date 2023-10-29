#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a structure for student information
struct Student {
    int number;
    char name[50];
    int age;
    int id;
    struct Student* next;
};

// Define a structure for a linked list node to hold numbers
struct Node {
    int data;
    struct Node* next;
};

// Function to add a student to the linked list
struct Student* addStudent(struct Student* head, int number, const char name[], int age, int id) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->number = number;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->id = id;
    newStudent->next = head;
    return newStudent;
}

// Function to print all student records in the list
void printStudents(struct Student* head) {
    struct Student* current = head;
    int count = 1;
    while (current != NULL) {
        printf("%d- %s %d %d\n", current->number, current->name, current->age, current->id);
        current = current->next;
        count++;
    }
}

// Function to search for a student by name
struct Student* searchStudentByName(struct Student* head, const char searchName[]) {
    struct Student* current = head;
    while (current != NULL) {
        if (strcmp(current->name, searchName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to delete the next node after the node with the searched student name
void deleteNextStudent(struct Student* head, const char searchName[]) {
    struct Student* current = head;
    while (current != NULL && current->next != NULL) {
        if (strcmp(current->name, searchName) == 0) {
            struct Student* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

// Function to find and print the record with the longest name
void findLongestName(struct Student* head) {
    struct Student* current = head;
    char longestName[50] = "";
    int maxLength = 0;

    while (current != NULL) {
        if (strlen(current->name) > maxLength) {
            maxLength = strlen(current->name);
            strcpy(longestName, current->name);
        }
        current = current->next;
    }

    if (maxLength > 0) {
        printf("The longest name in the list: %s\n", longestName);
        printf("Length: %d\n", maxLength);
    } else {
        printf("No student records in the list.\n");
    }
}

// Function to add a new node with the given data at the end of the list
struct Node* append(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// Function to sort the list of numbers in descending order
struct Node* sortList(struct Node* head) {
    struct Node* current = head;
    int tempData;
    while (current != NULL) {
        struct Node* runner = current->next;
        while (runner != NULL) {
            if (current->data < runner->data) {
                tempData = current->data;
                current->data = runner->data;
                runner->data = tempData;
            }
            runner = runner->next;
        }
        current = current->next;
    }
    return head;
}

// Function to print the list of numbers
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf("->");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Student* studentList = NULL;
    struct Node* numberList = NULL;
    int studentNumber = 1;
    int inputNumber, age, id;
    char name[50];
    char searchName[50];

    int choice;
    while (1) {
        int tempData; // Degişken tanumı burda yaptım

        printf("Menu:\n");
        printf("1- Add a student\n");
        printf("2- Print all students\n");
        printf("3- Search for a student by name\n");
        printf("4- Delete the next student by name\n");
        printf("5- Find the student with the longest name\n");
        printf("6- Add random numbers to the list\n");
        printf("7- Sort and print the number list\n");
        printf("8- Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student name: ");
                scanf("%s", name);
                printf("Enter student age: ");
                scanf("%d", &age);
                printf("Enter student id: ");
                scanf("%d", &id);
                studentList = addStudent(studentList, studentNumber, name, age, id);
                studentNumber++;
                break;
            case 2:
                printStudents(studentList);
                break;
            case 3:
                printf("Enter student name to search: ");
                scanf("%s", searchName);
                struct Student* foundStudent = searchStudentByName(studentList, searchName);
                if (foundStudent != NULL) {
                    printf("Student found: %d %s %d %d\n", foundStudent->number, foundStudent->name, foundStudent->age, foundStudent->id);
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 4:
                printf("Enter student name to delete next student: ");
                scanf("%s", searchName);
                deleteNextStudent(studentList, searchName);
                break;
            case 5:
                findLongestName(studentList);
                break;
            case 6:
                // Add random numbers to the list
                srand(time(NULL)); // Seed for random number generation
                for (int i = 0; i < 100; i++) {
                    int randomNumber = rand() % 100; // Change the range as needed
                    numberList = append(numberList, randomNumber);
                }
                printf("Random numbers added to the list.\n");
                break;
            case 7:
                // Sort and print the number list
                numberList = sortList(numberList);
                printf("Sorted Number List: ");
                printList(numberList);
                break;
            case 8:
                // Free allocated memory for student list
                while (studentList != NULL) {
                    struct Student* temp = studentList;
                    studentList = studentList->next;
                    free(temp);
                }

                // Free allocated memory for number list
                while (numberList != NULL) {
                    struct Node* temp = numberList;
                    numberList = numberList->next;
                    free(temp);
                }

                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

