#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

typedef struct student {
    int record_id;
    int attendance;
    bool extra;
    int hours_studied;
    int exam_score;
    struct student *next;
} student_t;

// Function prototypes
student_t *new_student(int record_id, int attendance, bool extra, int hours_studied, int exam_score);
student_t *add_student_sorted(student_t *list, student_t *new_student, int task_id);  
void free_student_list(student_t *list);  

#endif // STUDENT_H
