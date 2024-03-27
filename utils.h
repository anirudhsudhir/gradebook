#include "gradebook.h"

extern int totalSubs;
extern int totalInternals;
extern int totalExternals;
extern int maxStudents;
extern int MAX_STUDENTS;
extern int currentStudentPointer;

extern char **subjects;
extern GradeBook **gradeBook;

void freeMemory(GradeBook *gradeBook[]);
