#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "emalloc.h"

// Full constructor for Task 1 & 3
student_t *new_student(int record_id, int attendance, bool extra, int hours_studied, int exam_score) {
    student_t *new = emalloc(sizeof(student_t));
    new->record_id = record_id;
    new->attendance = attendance;
    new->extra = extra;
    new->hours_studied = hours_studied;
    new->exam_score = exam_score;
    new->next = NULL;
    return new;
}

// Minimal constructor for Task 2
student_t *new_student_task2(int record_id, int hours_studied, int exam_score) {
    student_t *new = emalloc(sizeof(student_t));
    new->record_id = record_id;
    new->hours_studied = hours_studied;
    new->exam_score = exam_score;
    new->attendance = 0;  // Not used in Task 2
    new->extra = false;   // Not used in Task 2
    new->next = NULL;
    return new;
}


