# include <stdio.h>
# include <string.h>
# define MAX_STUDENT 100

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
int giveNoStudents();
void deleteStudent(char);
void updateStudent(char);

int main() {
    Student students[MAX_STUDENT] = {
        { 121, "Mathew", "Hawler Mathew", 17, "Foundation"}
    };
    int studentsNo = 1;
    showStudentsDetails(students, studentsNo);

    addStudentDetails(students, &studentsNo);

    showStudentsDetails(students, studentsNo);

    Union data;
    strcpy(data.text, "Jack");
    findBy_('N', students, studentsNo, data);

    return 0;
}

void showStudentsDetails(Student students[], int studentsNo){
    if(studentsNo == 0){
        printf("\nThere is currently 0 Students.\n");
        return;
    }
    printf("\nDETAILS OF ALL STUDENTS");
    for(int i = 0; i < studentsNo; i ++){
        printf("\n==================================\n");
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("First Name: %s\n", students[i].firstName);
        printf("Full Name: %s\n", students[i].fullName);
        printf("Age: %d\n", students[i].age);
        printf("Course: %s", students[i].course);
    };
    printf("\n==================================\n");
}

void addStudentDetails(Student students[], int * studentsNo){
    
    if((*studentsNo + 1) == MAX_STUDENT){
        printf("\nThere is currently 0 Students.\n");
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

    printf("\n==================================\n");
    printf("Successfully added the new student!");
    printf("\n==================================\n");

}

// temporary return 1 student only
void findBy_(char this, Student students[], int studentsNo, Union data){

    if(studentsNo == 0){
        printf("\nThere is currently 0 students to probably search.\n");
        return;
    }

    Student targetStudent = {-1, "", "", 0, ""};

    for(int i = 0; i < studentsNo; i++){
        switch (this)
        {
        case 'R':
            if(i == 0) printf("FIND STUDENT BY ROLL NUMBER");
            if(students[i].rollNumber == data.number){
                targetStudent = students[i];
            }
            break;
        case 'N':
            if(i == 0) printf("FIND STUDENT BY FIRST NAME");
            if(strcmpi(students[i].firstName, data.text) == 0){
                targetStudent = students[i];
            }
            break;
        case 'C':
            if(i == 0) printf("FIND STUDENT BY COURSE NAME");
            if(strcmpi(students[i].course, data.text) == 0){
                targetStudent = students[i];
            }
            break;
        default:
            printf("\nThe Dev is clumsy!");
            break;
        }
        if (targetStudent.rollNumber != -1){
            break;
        }
    }
    
    if(targetStudent.rollNumber == -1){
        printf("\n>>>No student with this data!");
        return;
    }
    
    printf("\n==================================\n");
    printf("Roll Number: %d\n", targetStudent.rollNumber);
    printf("First Name: %s\n", targetStudent.firstName);
    printf("Full Name: %s\n", targetStudent.fullName);
    printf("Age: %d\n", targetStudent.age);
    printf("Course: %s", targetStudent.course);
    printf("\n==================================\n");

}