#ifndef LIST_H
#define LIST_H

#include "student.h"

student_t *add_student_sorted(student_t *head, student_t *new_student, int task_id);
student_t *add_student_end(student_t *head, student_t *new_student);
student_t *sort_students(student_t *head, int task_id);
void free_student_list(student_t *head);

#endif
