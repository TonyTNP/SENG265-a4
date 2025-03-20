#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "student.h"
#include "emalloc.h"

// Function to create a new student node
student_t* new_student(int record_id, int attendance, bool extra, int hours_studied, int exam_score) {
    student_t *new = (student_t*)emalloc(sizeof(student_t));
    new->record_id = record_id;
    new->attendance = attendance;
    new->extra = extra;
    new->hours_studied = hours_studied;
    new->exam_score = exam_score;
    new->next = NULL;
    return new;
}

// Function to free the student list
void free_student_list(student_t *head) {
    student_t *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
