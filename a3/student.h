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

// Two constructors: Full and Task 2 specific
student_t *new_student(int record_id, int attendance, bool extra, int hours_studied, int exam_score);
student_t *new_student_task2(int record_id, int hours_studied, int exam_score);

void free_student_list(student_t *head);

#endif
