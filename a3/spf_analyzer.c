#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "emalloc.h"
#include "student.h"

#define MAX_LINE_LEN 256

// Function to detect the number of columns in the CSV file
int detect_column_count(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char line[MAX_LINE_LEN];
    fgets(line, MAX_LINE_LEN, file); // Read header

    int count = 0;
    char *token = strtok(line, ",");
    while (token) {
        count++;
        token = strtok(NULL, ",");
    }

    fclose(file);
    return count;
}

// Function to process the CSV file
void process_csv(const char *filename, student_t **list, int task_id) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char line[MAX_LINE_LEN];
    fgets(line, MAX_LINE_LEN, file); // Skip header

    int column_count = detect_column_count(filename);
    printf("Processing file: %s\nDetected column count: %d\n", filename, column_count);

    int count = 0;

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

        // Task-specific selection criteria
        if ((task_id == 1 && column_count == 2) ||  
            (task_id == 2 && column_count >= 3 && hours_studied > 40) ||
            (task_id == 3 && exam_score >= 85)) {

            student_t *new = new_student(record_id, attendance, extra, hours_studied, exam_score);

            if (task_id == 1) {
                // Append Task 1 records in input order
                *list = add_student_end(*list, new);
            } else {
                // Task 2 & 3: Ensure sorting (highest score first)
                *list = add_student_sorted(*list, new, task_id);
            }

            count++;
        }
    }

    fclose(file);
    printf("Total matching records for Task %d: %d\n", task_id, count);
}

// Function to write the output CSV file
void write_output(student_t *list, int task_id) {
    FILE *file = fopen("output.csv", "w");
    if (!file) {
        perror("Error opening output file");
        return;
    }

    // Ensure correct headers for each task
    if (task_id == 1) {
        fprintf(file, "Record_ID,Exam_Score\n");
    } else if (task_id == 2) {
        fprintf(file, "Record_ID,Hours_Studied,Exam_Score\n");
    } else if (task_id == 3) {
        fprintf(file, "Record_ID,Attendance,Extra,Hours_Studied,Exam_Score\n");
    }

    // Ensure sorting for Task 2 by Exam Score (descending)
    if (task_id == 2) {
        list = sort_students(list, task_id);
    }

    // Write data
    int count = 0;
    while (list != NULL) {
        if (task_id == 1) {
            // Task 1: Output should match `tests/test01.csv`
            fprintf(file, "%d,%d\n", list->record_id, list->exam_score);
        } else if (task_id == 2) {
            // Task 2: Ensure proper format (`Record_ID,Hours_Studied,Exam_Score`)
            if (count >= 10) break;  // Ensure max 10 records
            fprintf(file, "%d,%d,%d\n", list->record_id, list->hours_studied, list->exam_score);
            count++;
        } else if (task_id == 3) {
            fprintf(file, "%d,%d,%d,%d,%d\n",
                    list->record_id,
                    list->attendance,
                    list->extra,
                    list->hours_studied,
                    list->exam_score);
        }
        list = list->next;
    }

    fclose(file);
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file.csv> <task_id>\n", argv[0]);
        return 1;
    }

    student_t *list = NULL;
    int task_id = atoi(argv[2]);

    process_csv(argv[1], &list, task_id);
    write_output(list, task_id);
    free_student_list(list);

    return 0;
}
