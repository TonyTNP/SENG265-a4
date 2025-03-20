#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "student.h"
#include "emalloc.h"

// Append student at the end of the list (For Task 1)
student_t *add_student_end(student_t *head, student_t *new_student) {
    if (head == NULL) {
        return new_student;
    }
    student_t *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_student;
    return head;
}

// Sort and insert a student into the list (For Task 2 & 3)
student_t *add_student_sorted(student_t *head, student_t *new_student, int task_id) {
    if (head == NULL || new_student->exam_score > head->exam_score) {
        new_student->next = head;
        return new_student;
    }

    student_t *current = head;
    while (current->next != NULL && current->next->exam_score >= new_student->exam_score) {
        current = current->next;
    }

    new_student->next = current->next;
    current->next = new_student;

    return head;
}

// Bubble sort students by exam score (For Task 2)
student_t *sort_students(student_t *head, int task_id) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    int swapped;
    student_t *ptr1;
    student_t *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->exam_score < ptr1->next->exam_score) {
                int temp_id = ptr1->record_id;
                int temp_score = ptr1->exam_score;
                int temp_hours = ptr1->hours_studied;

                ptr1->record_id = ptr1->next->record_id;
                ptr1->exam_score = ptr1->next->exam_score;
                ptr1->hours_studied = ptr1->next->hours_studied;

                ptr1->next->record_id = temp_id;
                ptr1->next->exam_score = temp_score;
                ptr1->next->hours_studied = temp_hours;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return head;
}

// Free student list
void free_student_list(student_t *head) {
    student_t *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
