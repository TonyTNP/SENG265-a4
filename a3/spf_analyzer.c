/**
 * @file spf_analyzer.c
 * @brief A program to process student performance data and generate filtered outputs.
 *
 * This program reads a CSV file containing student performance data, processes the data 
 * based on a specified task, and writes the filtered results to an output file.
 *
 * Supported tasks:
 * - Task 1: Extracts and outputs `Record_ID` and `Exam_Score`
 * - Task 2: Filters students who studied more than 40 hours, sorts by `Exam_Score` (DESC), limits output to 10
 * - Task 3: Filters students with `Exam_Score` >= 85, sorts by `Exam_Score` (ASC) and `Record_ID` (ASC), limits output to 10
 *
 * @author Ashton Majachani
 * @date March 20, 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include "list.h"
 #include "emalloc.h"
 #include "student.h"
 
 #define MAX_LINE_LEN 256  ///< Maximum length of a line in the CSV file
 
 /**
  * @brief Determines the number of columns in the CSV file.
  * 
  * @param filename Name of the input file.
  * @return Number of columns detected.
  */
 int detect_column_count(const char *filename) {
     FILE *file = fopen(filename, "r");
     if (!file) {
         perror("Error opening file");
         exit(EXIT_FAILURE);
     }
 
     char line[MAX_LINE_LEN];
     fgets(line, MAX_LINE_LEN, file);  // Read header line
 
     int count = 0;
     char *token = strtok(line, ",");
     while (token) {
         count++;
         token = strtok(NULL, ",");
     }
 
     fclose(file);
     return count;
 }
 
 /**
  * @brief Reads student data from a CSV file and filters it based on the task criteria.
  * 
  * @param filename Name of the CSV file.
  * @param list Pointer to the linked list of students.
  * @param task_id ID of the task to determine filtering criteria.
  */
 void process_csv(const char *filename, student_t **list, int task_id) {
     FILE *file = fopen(filename, "r");
     if (!file) {
         perror("Error opening file");
         exit(EXIT_FAILURE);
     }
 
     char line[MAX_LINE_LEN];
     fgets(line, MAX_LINE_LEN, file);  // Skip header
 
     int column_count = detect_column_count(filename);
     printf("Processing file: %s\nDetected column count: %d\n", filename, column_count);
 
     while (fgets(line, MAX_LINE_LEN, file)) {
         int record_id = 0, attendance = 0, hours_studied = 0, exam_score = 0;
         char extracurricular[10] = "No"; // Default value
 
         int parsed = 0;
         if (column_count == 2) {
             parsed = sscanf(line, "%d,%d", &record_id, &exam_score);
         } else if (column_count == 3) { 
             parsed = sscanf(line, "%d,%d,%d", &record_id, &hours_studied, &exam_score);
         } else if (column_count == 5) {
             parsed = sscanf(line, "%d,%d,%9s,%d,%d", &record_id, &attendance, extracurricular, &hours_studied, &exam_score);
         }
 
         if (parsed < 2) {
             printf("Warning: Skipping malformed line: %s\n", line);
             continue;
         }
 
         bool extra = (strcmp(extracurricular, "Yes") == 0);
 
         printf("Parsed: ID=%d, Attendance=%d, Extra=%d (%s), Hours=%d, Score=%d\n", 
                record_id, attendance, extra, extracurricular, hours_studied, exam_score);
 
         // Apply task-specific filtering criteria
         if ((task_id == 1 && column_count == 2) ||  
             (task_id == 2 && column_count >= 3 && hours_studied > 40) ||
             (task_id == 3 && exam_score >= 85)) {
 
             student_t *new = new_student(record_id, attendance, extra, hours_studied, exam_score);
 
             if (task_id == 1) {
                 *list = add_student_end(*list, new);  // Maintain order for Task 1
             } else {
                 *list = add_student_sorted(*list, new, task_id);  // Sort Task 2 (DESC) & Task 3 (ASC)
             }
         }
     }
 
     fclose(file);
 }
 
 /**
  * @brief Writes the filtered student data to an output CSV file.
  * 
  * @param list Pointer to the linked list of students.
  * @param task_id ID of the task to determine the output format.
  */
 void write_output(student_t *list, int task_id) {
     FILE *file = fopen("output.csv", "w");
     if (!file) {
         perror("Error opening output file");
         return;
     }
 
     // Write correct headers based on task
     if (task_id == 1) {
         fprintf(file, "Record_ID,Exam_Score\n");
     } else if (task_id == 2 || task_id == 3) {
         fprintf(file, "Record_ID,Hours_Studied,Exam_Score\n");
     }
 
     int count = 0;
     while (list != NULL) {
         if (task_id == 1) {
             fprintf(file, "%d,%d\n", list->record_id, list->exam_score);
         } else if ((task_id == 2 || task_id == 3) && count < 10) {
             fprintf(file, "%d,%d,%d\n", list->record_id, list->hours_studied, list->exam_score);
             count++;
         }
         list = list->next;
     }
 
     fclose(file);
 }
 
 /**
  * @brief Main function to process student data.
  * 
  * @param argc Number of command-line arguments.
  * @param argv Array of command-line arguments.
  * @return int Program exit status.
  */
 int main(int argc, char *argv[]) {
     if (argc != 3) {
         fprintf(stderr, "Usage: %s <input_file.csv> <task_id>\n", argv[0]);
         return EXIT_FAILURE;
     }
 
     student_t *list = NULL;
     int task_id = atoi(argv[2]);
 
     process_csv(argv[1], &list, task_id);
     write_output(list, task_id);
     free_student_list(list);
 
     return EXIT_SUCCESS;
 }
 