/**
 * @file student.c
 * @brief Defines student node structure and provides memory management functions.
 * 
 * This file contains the implementation of functions for creating and managing 
 * student nodes in a linked list. It ensures memory allocation safety and 
 * proper cleanup of student records.
 * 
 * @author Your Name
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include "student.h"
 #include "emalloc.h"
 
 /**
  * @brief Creates a new student node.
  *
  * This function dynamically allocates memory for a new student node, initializes
  * its fields, and returns a pointer to the newly created node.
  *
  * @param record_id The unique identifier for the student.
  * @param attendance The student's attendance percentage.
  * @param extra Indicates whether the student participated in extracurricular activities.
  * @param hours_studied The number of hours the student studied.
  * @param exam_score The student's exam score.
  * @return Pointer to the newly allocated student node.
  */
 student_t* new_student(int record_id, int attendance, bool extra, int hours_studied, int exam_score) {
     student_t *new = (student_t*)emalloc(sizeof(student_t));
     if (!new) {
         fprintf(stderr, "Memory allocation failed for new student node.\n");
         exit(EXIT_FAILURE);
     }
     
     new->record_id = record_id;
     new->attendance = attendance;
     new->extra = extra;
     new->hours_studied = hours_studied;
     new->exam_score = exam_score;
     new->next = NULL;
 
     return new;
 }
 
 /**
  * @brief Frees the allocated memory for the student list.
  *
  * This function iterates through the linked list of students and frees the 
  * allocated memory for each node to prevent memory leaks.
  *
  * @param head Pointer to the head of the student list.
  */
 void free_student_list(student_t *head) {
     student_t *temp;
     while (head) {
         temp = head;
         head = head->next;
         free(temp);
     }
 }
 