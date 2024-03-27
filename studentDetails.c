#include "studentDetails.h"
#include "gradebook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addStudent() {
  GradeBook *student = (GradeBook *)malloc(sizeof(GradeBook));
  student->name = (char *)malloc(1024);
  printf("Enter the name of the student\n");
  char dummy_space;
  scanf("%c", &dummy_space);
  fgets(student->name, 1024, stdin);
  student->name[strlen(student->name) - 1] = '\0';
  student->name = realloc(student->name, strlen(student->name) + 1);
  printf("Enter the roll number of the student\n");
  scanf("%d", &student->roll_no);
  printf("Enter the section of the student\n");
  scanf("%c", &dummy_space);
  scanf("%c", &student->section);
  printf("Enter the semester the student is in\n");
  scanf("%d", &student->sem);
  printf("Enter the phone number of the student\n");
  scanf("%ld", &student->phone_no);

  student->marks = NULL;
  gradeBook[currentStudentPointer++] = student;
}

void updateStudentScores() {
  for (int h = 0; h < currentStudentPointer; h++) {
    printf("Enter the marks of student %d\n", h + 1);
    int **marks = (int **)malloc(sizeof(int *));

    for (int i = 0; i < totalSubs; i++) {
      printf("Enter the marks of the student in %s\n", subjects[i]);
      int *subMarks = (int *)malloc(sizeof(int));

      for (int j = 0; j < totalInternals; j++) {
        printf("Enter the marks of the student in internal %d\n", j + 1);
        scanf("%d", &subMarks[j]);
      }
      for (int j = totalInternals; j < totalInternals + totalExternals; j++) {
        printf("Enter the marks of the student in external %d\n",
               j + 1 - totalInternals);
        scanf("%d", &subMarks[j]);
      }

      marks[i] = subMarks;
    }

    gradeBook[h]->marks = marks;
  }
}

void calculateStudentScores() {}

void displayStudentData() {
  printf("%-15s %-8s %-8s %-13s %-8s\n", "Name", "Roll No", "Semester",
         "Phone Number", "Section");
  for (int i = 0; i < currentStudentPointer; i++) {
    printf("%-15s %-8d %-8d %-13ld %c\n", gradeBook[i]->name,
           gradeBook[i]->roll_no, gradeBook[i]->sem, gradeBook[i]->phone_no,
           gradeBook[i]->section);
    if (gradeBook[i]->marks != NULL) {
      for (int j = 0; j < totalSubs; j++) {
        printf("%s Scores\n", subjects[j]);
        for (int k = 0; k < totalInternals; k++) {
          printf("Internal %d - %d\n", k + 1, subjects[j][k]);
        }
        for (int k = totalInternals; k < totalInternals + totalExternals; k++) {
          printf("External %d - %d\n", k + 1 - totalInternals, subjects[j][k]);
        }
      }
    } else {
      printf("Scores of this student has not been added\n");
    }
  }
}
