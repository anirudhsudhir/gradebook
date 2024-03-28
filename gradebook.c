#include "gradebook.h"
#include "studentDetails.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_INTERNAL_MARKS = 40;
const int MAX_EXTERNAL_MARKS = 100;

int totalSubs = 0;
int totalInternals = 0;
int totalExternals = 0;
int currentStudentPointer = 0;
GradeBook **gradeBook;

char **subjects;

int choiceEntry() {
  printf("Enter 1 to add a student\n");
  printf("Enter 2 to update student scores\n");
  printf("Enter 3 to calculate marks data\n");
  printf("Enter 4 to display student data along with marks\n");
  printf("Enter 5 to quit the application\n");
  int option;
  scanf("%d", &option);

  switch (option) {
  case 1:
    addStudent();
    break;
  case 2:
    updateStudentScores();
    break;
  case 3:
    calculateStudentScores();
    break;
  case 4:
    displayStudentData();
    break;
  case 5:
    return 1;
  }
  return 0;
}

void readSubjects() {
  for (int i = 0; i < totalSubs; i++) {
    printf("Enter the name of subject %d\n", i + 1);
    subjects[i] = (char *)malloc(1024);
    fgets(subjects[i], 1024, stdin);
    subjects[i][strlen(subjects[i]) - 1] = '\0';
    subjects[i] = realloc(subjects[i], strlen(subjects[i]));
  }
}

void bootstrapGradebook() {
  printf("Enter the total number of subjects\n");
  scanf("%d", &totalSubs);
  subjects = (char **)malloc(totalSubs * sizeof(char *));
  char dummy_space;
  scanf("%c", &dummy_space);
  readSubjects();

  printf("Enter the total number of internals\n");
  scanf("%d", &totalInternals);
  printf("Enter the total number of externals\n");
  scanf("%d", &totalExternals);
}

int main() {
  bootstrapGradebook();

  while (1) {
    if (choiceEntry())
      break;
  }
  freeMemory(gradeBook);
}
