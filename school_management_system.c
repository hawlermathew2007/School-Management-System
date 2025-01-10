# include <stdio.h>
# include <string.h>
# define MAX_STUDENTS 100

typedef struct{
    int rollNumber;
    char firstName[64];
    char fullName[100];
    int age;
    char course[64];

} Student;

typedef union {
    int number;
    char text[64];
} Union;

void showStudentsDetails(Student[], int);
void addStudentDetails(Student[], int*);
void findBy_(char, Student[], int, Union);
void deleteStudent(Student[], int*);
void updateStudent(Student[], int);

int main() {
    Student students[MAX_STUDENTS] = {
        { 121, "Mathew", "Hawler Mathew", 17, "Foundation"},
        { 198, "Mathew", "Han Mathew", 21, "Master"},
        { 111, "Aristina", "Gay Aristina", 18, "Foundation"},
        { 101, "Den", "Hemwock Den", 25, "PhD"}
    };
    int studentsNo = 4;
    int choice;

    do {
        printf("\nSchool Management System Menu\n");
        printf("1. Add Student\n");
        printf("2. View all Students\n");
        printf("3. Find Students\n");
        printf("4. Delete Students\n");
        printf("5. Update Students\n");
        printf("6. Exit\n");
        printf("Enter your choice (1 - 6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudentDetails(students, &studentsNo);
                break;
            case 2:
                showStudentsDetails(students, studentsNo);
                break;
            case 3:
                int responseForFind;
                printf("\nHow do you want to find the students by? (1, 2, 3)");
                printf("\n1. Roll Number");
                printf("\n2. First Name");
                printf("\n3. Course Name");
                printf("\nEnter your choice: ");
                scanf("%d", &responseForFind);

                Union data;

                switch (responseForFind)
                {
                case 1:
                    int userResponseForRn;
                    printf("\nType Roll Number: ");
                    scanf("%d", &userResponseForRn);
                    data.number = userResponseForRn;
                    findBy_('R', students, studentsNo, data);
                    break;
                case 2:
                    char userResponseForFn[64];
                    printf("\nType First Name: ");
                    getchar();
                    fgets(userResponseForFn, sizeof(userResponseForFn), stdin);
                    userResponseForFn[strcspn(userResponseForFn, "\n")] = '\0';
                    strcpy(data.text, userResponseForFn);
                    findBy_('N', students, studentsNo, data);
                    break;
                case 3:
                    char userResponseForC[64];
                    printf("\nType Course Name: ");
                    getchar();
                    fgets(userResponseForC, sizeof(userResponseForC), stdin);
                    userResponseForC[strcspn(userResponseForC, "\n")] = '\0';
                    strcpy(data.text, userResponseForC);
                    findBy_('C', students, studentsNo, data);
                    break;
                default:
                    printf("\nWarning: Please type the related response!");
                    break;
                }
                
                break;
            case 4:
                deleteStudent(students, &studentsNo);
                break;
            case 5:
                updateStudent(students, studentsNo);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void printAstudent(Student student){
    printf("Roll Number: %d\n", student.rollNumber);
    printf("First Name: %s\n", student.firstName);
    printf("Full Name: %s\n", student.fullName);
    printf("Age: %d\n", student.age);
    printf("Course: %s", student.course);
}

void showStudentsDetails(Student students[], int studentsNo){
    if(studentsNo == 0){
        printf("\n==================================\n");
        printf(">>> There is currently 0 Students.");
        printf("\n==================================\n");
        return;
    }
    printf("\nDETAILS OF ALL STUDENTS");
    for(int i = 0; i < studentsNo; i ++){
        printf("\n==================================\n");
        printAstudent(students[i]);
    };
    printf("\n==================================\n");
}

void addStudentDetails(Student students[], int * studentsNo){
    
    if(*studentsNo == MAX_STUDENTS){
        printf("\n==================================\n");
        printf("Maximum Students is Reached!");
        printf("\n==================================\n");
        return;
    }

    Student newStudent;
    int allowPassRn = 1;

    printf("\nTYPE STUDENT DETAILS");
    do {
        printf("\n- Roll Number: ");
        scanf("%d", &newStudent.rollNumber);

        for(int i = 0; i < *studentsNo; i++){
            if(students[i].rollNumber == newStudent.rollNumber){
                printf("Warning: This roll number has already been taken!");
                allowPassRn = 0;
                break;
            } else {
                allowPassRn = 1;
            }
        }

    }while(allowPassRn == 0);
    
    printf("- First Name: ");
    scanf("%49s", newStudent.firstName);

    getchar();

    printf("- Full Name: ");
    fgets(newStudent.fullName, sizeof(newStudent.fullName), stdin);
    newStudent.fullName[strcspn(newStudent.fullName, "\n")] = '\0';

    printf("- Age: ");
    scanf("%d", &newStudent.age);
    
    getchar();

    printf("- Course: ");
    fgets(newStudent.course, sizeof(newStudent.course), stdin);
    newStudent.course[strcspn(newStudent.course, "\n")] = '\0';

    students[*studentsNo] = newStudent;
    (*studentsNo) ++;

    printf("\n===================================\n");
    printf("Successfully added the new student!");
    printf("\n===================================\n");

}

void findBy_(char this, Student students[], int studentsNo, Union data){

    if(studentsNo == 0){
        printf("\n==================================\n");
        printf("\nThere is currently 0 students to probably search.\n");
        printf("\n==================================\n");
        return;
    }

    Student targetStudents[MAX_STUDENTS];
    int targetStudentsNo = 0;

    printf("\n==================================\n");
    for(int i = 0; i < studentsNo; i++){
        switch (this)
        {
        case 'R':
            if(i == 0) printf("FIND STUDENT BY ROLL NUMBER");
            if(students[i].rollNumber == data.number){
                targetStudents[targetStudentsNo] = students[i];
                targetStudentsNo ++;
            }
            break;
        case 'N':
            if(i == 0) printf("FIND STUDENT BY FIRST NAME");
            if(strcmpi(students[i].firstName, data.text) == 0){
                targetStudents[targetStudentsNo] = students[i];
                targetStudentsNo ++;
            }
            break;
        case 'C':
            if(i == 0) printf("FIND STUDENT BY COURSE NAME");
            if(strcmpi(students[i].course, data.text) == 0){
                targetStudents[targetStudentsNo] = students[i];
                targetStudentsNo ++;
            }
            break;
        default:
            printf("\nThe Dev is clumsy!");
            break;
        }
    }
    
    if(targetStudentsNo == 0){
        printf("\n==================================\n");
        printf(">>> No student with this data!");
        printf("\n==================================\n");
        return;
    }

    printf("\n>>> Number of Students: %d", targetStudentsNo);
    
    for(int i = 0; i <  targetStudentsNo; i ++){
        printf("\n==================================\n");
        printAstudent(targetStudents[i]);
    }
    printf("\n==================================\n");

}

void deleteStudent(Student students[], int *studentsNo){

    if(*studentsNo == 0){
        printf("\n==================================\n");
        printf(">>> There is 0 Students, so cannot delete.");
        printf("\n==================================\n");
        return;
    }

    int userRollNumber;

    printf("\nDELETE STUDENT");

    printf("\n- Enter the Student\'s Roll Number: ");
    scanf("%d", &userRollNumber);


    for(int i = 0; i < *studentsNo; i++){
        if(students[i].rollNumber == userRollNumber){

            printf("\n========= DELETED STUDENT =========\n");
            printAstudent(students[i]);
            printf("\n===================================\n");

            students[i] = students[--(*studentsNo)];
            printf("\nSuccessfully deleted the student!");
            
            return;
        }
    }

    printf("\n===================================\n");
    printf(">>> No student with this Roll Number!");
    printf("\n===================================\n");

}

void updateStudent(Student students[], int studentsNo){

    if(studentsNo == 0){
        printf("\n==================================\n");
        printf(">>> There is 0 Students, so cannot update.");
        printf("\n==================================\n");
        return;
    }

    int userRollNumber;

    printf("\nUPDATE STUDENT");

    printf("\n- Enter the Student\'s Roll Number: ");
    scanf("%d", &userRollNumber);

    for(int i = 0; i < studentsNo; i++){
        if(students[i].rollNumber == userRollNumber){

            int userChoice = 0;
            Union userUpdate;

            printf("\n========== FOUND STUDENT ==========\n");
            printAstudent(students[i]);
            printf("\n===================================\n");
            
            printf("\nWhat attribute of this student do you want update? (1 - 5)\n");
            printf("1. Roll Number\n");
            printf("2. First Name\n");
            printf("3. Full Name\n");
            printf("4. Age\n");
            printf("5. Course\n");
            printf("6. Cancel Updating Student Process\n");


            printf("\nEnter your choice: ");
            scanf("%d", &userChoice);
            
            if (userChoice == 6){
                printf("\n===================================\n");
                printf("Cancel successfully!");
                printf("\n===================================\n");
                return;
            }

            printf("Enter your Update: ");
            if(userChoice == 1 || userChoice == 4){
                scanf("%d", &userUpdate.number);

            } else{
                getchar();
                fgets(userUpdate.text, sizeof(userUpdate.text), stdin);
                userUpdate.text[strcspn(userUpdate.text, "\n")] = '\0';
            }

            switch (userChoice)
            {
            case 1:
                students[i].rollNumber = userUpdate.number;
                break;
            case 2:
                strcpy(students[i].firstName, userUpdate.text);
                break;
            case 3:
                strcpy(students[i].fullName, userUpdate.text);
                break;
            case 4:
                students[i].age = userUpdate.number;
                break;
            case 5:
                strcpy(students[i].course, userUpdate.text);
                break;
            
            default:
                printf("Please type the related response!");
                return;
                break;
            }
            printf("\n===================================\n");
            printf("Update Student successfully!");
            printf("\n===================================\n");
            return;
        }
    }

    printf("\n===================================\n");
    printf(">>> No student with this Roll Number!");
    printf("\n===================================\n");

}