#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void freeMemory(GradeBook *gradeBook[]) {
  printf("Freeing memory\n");
  for (int i = 0; i < currentStudentPointer; i++) {
    if (gradeBook[i] != NULL) {

      if (gradeBook[i]->marks != NULL) {
        for (int j = 0; j < totalSubs; j++) {
          if (gradeBook[i]->marks[j] != NULL)
            free(gradeBook[i]->marks[j]);
        }
        free(gradeBook[i]->marks);
      }

      free(gradeBook[i]->name);
      free(gradeBook[i]);
    }
  }

  free(gradeBook);

  for (int i = 0; i < totalSubs; i++) {
    free(subjects[i]);
  }

  free(subjects);
}
