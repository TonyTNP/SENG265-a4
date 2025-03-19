#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "student.h"

//Creates a new student node
student_t *new_student(int record_id, int attendance, bool extra, int hours_studied, int exam_score) {
    student_t *new_node = (student_t *)malloc(sizeof(student_t));
    if (!new_node) {
        perror("Memory allocation failed");
        exit(1);
    }

    new_node->record_id = record_id;
    new_node->attendance = attendance;
    new_node->extra = extra;
    new_node->hours_studied = hours_studied;
    new_node->exam_score = exam_score;
    new_node->next = NULL;

    return new_node;
}

//Adds a student node while maintaining sorted order based on `task_id`
student_t *add_student_sorted(student_t *list, student_t *new, int task_id) {
    if (list == NULL || new->exam_score > list->exam_score || 
       (new->exam_score == list->exam_score && new->record_id < list->record_id)) {
        new->next = list;
        return new;
    }

    student_t *curr = list;
    while (curr->next != NULL &&
           (curr->next->exam_score > new->exam_score ||
           (curr->next->exam_score == new->exam_score && curr->next->record_id < new->record_id))) {
        curr = curr->next;
    }

    new->next = curr->next;
    curr->next = new;

    return list;
}


//Frees the student list
void free_student_list(student_t *list) {
    student_t *temp;
    while (list) {
        temp = list;
        list = list->next;
        free(temp);
    }
}
