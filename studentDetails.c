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
  student->result = NULL;

  gradeBook = (GradeBook **)realloc(gradeBook, (currentStudentPointer + 1) *
                                                   sizeof(GradeBook *));
  gradeBook[currentStudentPointer++] = student;
}

void updateStudentScores() {
  for (int h = 0; h < currentStudentPointer; h++) {
    int **marks = (int **)malloc(sizeof(int *));
    screenSep();
    for (int i = 0; i < totalSubs; i++) {
      printf("Enter %s's marks in %s\n", gradeBook[h]->name, subjects[i]);
      int *subMarks = (int *)malloc(sizeof(int));

      for (int j = 0; j < totalInternals; j++) {
        printf("Internal %d: ", j + 1);
        scanf("%d", &subMarks[j]);
      }
      for (int j = totalInternals; j < totalInternals + totalExternals; j++) {
        printf("External %d: ", j + 1 - totalInternals);
        scanf("%d", &subMarks[j]);
      }

      marks[i] = subMarks;
    }

    gradeBook[h]->marks = marks;
  }
}

void calculateStudentScores() {
  for (int i = 0; i < currentStudentPointer; i++) {
    if (gradeBook[i]->marks == NULL) {
      printf("Scores cannot be calculated as marks have not been added yet\n");
      waitClear();
      return;
    }
    Result *result = (Result *)malloc(sizeof(Result));
    float *calculatedSubjectPercent =
        (float *)malloc(totalSubs * sizeof(float));
    int MAX_SCORE = totalInternals * max_internal_marks +
                    totalExternals * max_external_marks;
    int calculatedTotalScore = 0;

    for (int j = 0; j < totalSubs; j++) {
      int calculatedSubScore = 0;
      for (int k = 0; k < totalInternals + totalExternals; k++) {
        calculatedSubScore += gradeBook[i]->marks[j][k];
        calculatedTotalScore += gradeBook[i]->marks[j][k];
      }
      calculatedSubjectPercent[j] =
          ((float)calculatedSubScore / MAX_SCORE) * 100;
    }

    result->GPA = ((float)calculatedTotalScore / (MAX_SCORE * totalSubs)) * 10;
    result->subjectGPA = calculatedSubjectPercent;
    gradeBook[i]->result = result;
  }
}

void displayStudentData() {
  screenSep();
  printf("%-7s | %-15s | %-8s | %-8s | %-13s | %-8s\n", "Sl. No.", "Name",
         "Roll No", "Semester", "Phone Number", "Section");
  for (int i = 0; i < currentStudentPointer; i++) {
    screenSep();
    printf("%-7d | %-15s | %-8d | %-8d | %-13ld | %c\n", i + 1,
           gradeBook[i]->name, gradeBook[i]->roll_no, gradeBook[i]->sem,
           gradeBook[i]->phone_no, gradeBook[i]->section);
    if (gradeBook[i]->marks != NULL) {
      for (int j = 0; j < totalSubs; j++) {
        printf("%s Scores\n", subjects[j]);
        for (int k = 0; k < totalInternals; k++) {
          printf("Internal %d - %d\n", k + 1, gradeBook[i]->marks[j][k]);
        }
        for (int k = totalInternals; k < totalInternals + totalExternals; k++) {
          printf("External %d - %d\n", k + 1, gradeBook[i]->marks[j][k]);
        }
      }
      if (gradeBook[i]->result != NULL) {
        for (int k = 0; k < totalSubs; k++) {
          printf("Percentage in %s is %f%%\n", subjects[k],
                 gradeBook[i]->result->subjectGPA[k]);
        }
        printf("%s's GPA is %f\n", gradeBook[i]->name,
               gradeBook[i]->result->GPA);
      } else {
        printf("The GPA of this student has not been calculated\n");
      }
    } else {
      printf("Scores of this student have not been added\n");
    }
  }
}
