/**
 * @file list.c
 * @brief Implementation of linked list operations for student data management.
 * 
 * This file contains functions for adding students to a linked list, 
 * sorting them based on task requirements, and swapping list nodes.
 * 
 * @author Ashton Majachani
 * @date March 20, 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include "list.h"
 #include "student.h"
 #include "emalloc.h"
 
 /**
  * @brief Swaps the data between two student nodes.
  * 
  * Used in sorting operations to rearrange nodes without modifying list links.
  * 
  * @param a First student node.
  * @param b Second student node.
  */
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
 
 /**
  * @brief Adds a student to the end of the linked list.
  * 
  * This function maintains input order and is used specifically for Task 1.
  * 
  * @param head Head of the linked list.
  * @param new_student New student node to be appended.
  * @return student_t* Updated head of the list.
  */
 student_t* add_student_end(student_t *head, student_t *new_student) {
     if (!head) return new_student;
 
     student_t *current = head;
     while (current->next) {
         current = current->next;
     }
     current->next = new_student;
     return head;
 }
 
 /**
  * @brief Inserts a student node in sorted order.
  * 
  * This function ensures Task 2 sorts in descending order by `Exam_Score` 
  * and Task 3 sorts in ascending order by `Exam_Score` (and `Record_ID` for ties).
  * 
  * @param head Head of the linked list.
  * @param new_student Student node to insert.
  * @param task_id Task identifier (2 or 3).
  * @return student_t* Updated head of the list.
  */
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
 
 /**
  * @brief Sorts the linked list of students.
  * 
  * Uses a simple bubble sort algorithm to order students by `Exam_Score`.
  * Task 2 sorts in descending order, while Task 3 sorts in ascending order.
  * 
  * @param head Head of the list.
  * @param task_id Task identifier (2 or 3).
  * @return student_t* Sorted head of the list.
  */
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
 