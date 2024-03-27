#pragma once

typedef struct {
  float *subjectGPA;
  float GPA;
} Result;

typedef struct {
  char *name;
  int **marks;
  int roll_no;
  char section;
  int sem;
  long int phone_no;
  Result *result;
} GradeBook;
