#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "student.h"
#include "emalloc.h"

// Function to swap two student nodes
void swap_students(student_t *a, student_t *b) {
    int temp_id = a->record_id;
    int temp_hours = a->hours_studied;
    int temp_score = a->exam_score;

    a->record_id = b->record_id;
    a->hours_studied = b->hours_studied;
    a->exam_score = b->exam_score;

    b->record_id = temp_id;
    b->hours_studied = temp_hours;
    b->exam_score = temp_score;
}

// Function to add a student to the end of the list (for Task 1)
student_t* add_student_end(student_t *head, student_t *new_student) {
    if (!head) return new_student;

    student_t *current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_student;
    return head;
}

// Function to add a student in sorted order (for Task 2 and Task 3)
student_t* add_student_sorted(student_t *head, student_t *new_student, int task_id) {
    if (!head || 
        (task_id == 2 && new_student->exam_score > head->exam_score) || 
        (task_id == 3 && (new_student->exam_score < head->exam_score || 
                          (new_student->exam_score == head->exam_score && new_student->record_id < head->record_id)))) {
        new_student->next = head;
        return new_student;
    }

    student_t *current = head;
    while (current->next && 
           ((task_id == 2 && new_student->exam_score <= current->next->exam_score) || 
            (task_id == 3 && (new_student->exam_score > current->next->exam_score || 
                              (new_student->exam_score == current->next->exam_score && new_student->record_id > current->next->record_id))))) {
        current = current->next;
    }

    new_student->next = current->next;
    current->next = new_student;
    return head;
}

// Function to sort students (bubble sort for Task 2 and 3)
student_t* sort_students(student_t *head, int task_id) {
    if (!head) return NULL;

    bool swapped;
    student_t *ptr1;
    student_t *lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if ((task_id == 2 && ptr1->exam_score < ptr1->next->exam_score) ||  
                (task_id == 3 && (ptr1->exam_score > ptr1->next->exam_score ||
                                 (ptr1->exam_score == ptr1->next->exam_score && ptr1->record_id > ptr1->next->record_id)))) {
                swap_students(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    
    return head;
}
