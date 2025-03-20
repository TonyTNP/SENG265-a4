/**
 * @file list.h
 * @brief Header file for linked list operations.
 * 
 * This file declares functions for managing a linked list of student records.
 * 
 * @author Ashton Majachani
 * @date March 20, 2025
 */

 #ifndef LIST_H
 #define LIST_H
 
 #include "student.h"
 
 /* Function declarations for linked list operations */
 student_t *add_student_sorted(student_t *head, student_t *new_student, int task_id);
 student_t *add_student_end(student_t *head, student_t *new_student);
 student_t *sort_students(student_t *head, int task_id);
 void free_student_list(student_t *head);
 
 #endif
 