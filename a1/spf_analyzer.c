#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>  // Needed for strcasecmp()


#define MAX_RECORDS 6608

/**
 * Struct: CurricularData
 * ----------------------
 * @brief Represents a row from the a1-data-curricular.csv file.
 */
typedef struct {
    int record_id;           // Maps to the "Record_ID" column
    int hours_studied;       // Maps to the "Hours_Studied" column
    int attendance;          // Maps to the "Attendance" column
    int tutoring_sessions;   // Maps to the "Tutoring_Sessions" column
    int exam_score;          // Maps to the "Exam_Score" column
    char extracurricular_activities[10];
    int physical_activity;   
    int sleep_hours;
} CurricularData;

/**
 * Function: read_csv_file
 * -----------------------
 * @brief Reads data from the a1-data-curricular.csv file and populates an array of CurricularData structs.
 *
 * @param filename The name of the CSV file to read.
 * @param data Array of CurricularData where the CSV data will be stored.
 * @return int The number of records successfully read.
 */
int read_csv_file(const char *filename, CurricularData data[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return -1;
    }

    // Skip the header line
    char buffer[256];
    fgets(buffer, sizeof(buffer), file); //skips header

    int index = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL && index < MAX_RECORDS) {
        sscanf(buffer, "%d,%d,%d,%d,%d", 
               &data[index].record_id, 
               &data[index].hours_studied, 
               &data[index].attendance, 
               &data[index].tutoring_sessions, 
               &data[index].exam_score);

               //printf("Debug: Read from CSV -> Record_ID=%d\n", data[index].record_id); // debug print, this prints
        index++;
    }

    fclose(file);
    return index;
}

/** 
*Function: read_yaml_file
---------------------------
*Reads data from a1-data-extracurricular.yaml and updates CurricularData array.
* @brief Reads extracurricular data from a YAML file and updates the data array.
 * @param filename The name of the YAML file.
 * @param data The array of student records to update.
 * @param num_records The number of records in the data array.
 * @return int Returns 0 if successful, -1 if file opening fails.
*/

int read_yaml_file(const char *filename, CurricularData data[], int num_records) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file: %s\n", filename);
        return -1;
    }

    char key[250], value[250];
    
    int record_id = -1;

    while (fscanf(file, " %49[^:]: %49[^\n]\n", key, value) != EOF) {
        if (strcmp(key, "Record_ID") == 0) {
            record_id = atoi(value);
            printf("Debug: RAW YAML Record_ID='%s' -> Parsed=%d\n", value, record_id);
        } 
        else if (record_id >= 0) {
            for (int i = 0; i < num_records; i++) {
                if (data[i].record_id == record_id) {  // mapping check
                    if (strcmp(key, "Extracurricular_Activities") == 0) {
                        strncpy(data[i].extracurricular_activities, value, sizeof(data[i].extracurricular_activities) - 1);
                        data[i].extracurricular_activities[sizeof(data[i].extracurricular_activities) - 1] = '\0';

                        // Fixes issue where "Yes" is not being assigned properly
                        if (strcasecmp(data[i].extracurricular_activities, "Yes") == 0) {
                            strcpy(data[i].extracurricular_activities, "Yes");
                        } else {
                            strcpy(data[i].extracurricular_activities, "No");
                        }

                        printf("Debug: Updated Record_ID=%d -> Extracurricular_Activities=%s\n",
                               data[i].record_id, data[i].extracurricular_activities);
                    } 
                    else if (strcmp(key, "Physical_Activity") == 0) {
                        data[i].physical_activity = atoi(value);
                    } 
                    else if (strcmp(key, "Sleep_Hours") == 0) {
                        data[i].sleep_hours = atoi(value);
                    }
                    break;
                }
            }
        }
    }
    fclose(file);
    return 0;
}


/**
* Function: process_task
---------------------------
* Processes the specified task and writes to output.csv
* @brief Processes the given task and writes results to output.csv.
 * @param task The task number to execute.
 * @param data The array of student records.
 * @param num_records The number of records in the array.
*/ 

void process_task(int task, CurricularData data[], int num_records) {
    FILE *output = fopen("output.csv", "w"); //Ensures file is created and accessible for read/write
    if(output==NULL) {
        printf("Error: Could not create or open output.csv\n");
        return;
    }

    switch(task) {

        case 1:
        fprintf(output,"Record_ID,Exam_Score\n");
        for (int i = 0; i < num_records; i++) {
            if(data[i].exam_score > 90) {
                fprintf(output,"%d,%d\n",data[i].record_id,data[i].exam_score);
            }
        }
        break;

        case 2:
            fprintf(output, "Extracurricular_Activities,Physical_Activity,Record_ID,Sleep_Hours\n");

            for (int i = 0; i < num_records; i++) {
                // Ensure extracurricular_activities is "Yes" or "No"
                if (strncmp(data[i].extracurricular_activities, "Yes", 3) != 0) {
                    strcpy(data[i].extracurricular_activities, "No");
                }

                // Validate data before writing
                if (data[i].physical_activity < 0 || data[i].sleep_hours < 0) {
                    printf("Warning: Skipping invalid record %d\n", data[i].record_id);
                    continue;
                }

                fprintf(output, "%s,%d,%d,%d\n",
                        data[i].extracurricular_activities,
                        data[i].physical_activity,
                        data[i].record_id,
                        data[i].sleep_hours);
            }
            break;
        
        case 3:
        fprintf(output, "Record_ID,Exam_Score,Extracurricular_Activities\n");
        for (int i = 0; i < num_records; i++) {
            if (data[i].exam_score > 90) {  // Ensure we filter scores > 90

                // Ensure the extracurricular field contains only "Yes" or "No"
                if (strcasecmp(data[i].extracurricular_activities, "Yes") != 0) {
                    strcpy(data[i].extracurricular_activities, "No");
                }

                // Debug print to verify each entry
                printf("Debug: Writing to CSV -> Record_ID=%d, Exam_Score=%d, Extracurricular_Activities=%s\n",
                    data[i].record_id, data[i].exam_score, data[i].extracurricular_activities);

                // Write the validated data to the CSV
                fprintf(output, "%d,%d,%s\n", 
                        data[i].record_id, 
                        data[i].exam_score, 
                        data[i].extracurricular_activities);
            }
        }
        break;


        case 5:
        fprintf(output,"Record_ID,Exam_Score\n");
        for(int i = 0; i < num_records; i++){
            if(data[i].sleep_hours >= data[i].hours_studied){
                fprintf(output,"%d,%d\n",data[i].record_id,data[i].exam_score);
            }
        }
        break;

        case 6:
        fprintf(output, "Record_ID,Exam_Score,Extracurricular_Activities\n");
        for (int i = 0; i < num_records; i++) {
            if (data[i].exam_score < 60) {
                if (strcasecmp(data[i].extracurricular_activities, "Yes") != 0) { //To check "Yes" case-insensitively
                    strcpy(data[i].extracurricular_activities, "No");
                }
                printf("Debug: Writing to CSV -> Record_ID=%d, Exam_Score=%d, Extracurricular_Activities=%s\n", //Debug print to check each record before writing
                    data[i].record_id, data[i].exam_score, data[i].extracurricular_activities);

                fprintf(output, "%d,%d,%s\n", 
                        data[i].record_id, 
                        data[i].exam_score, 
                        data[i].extracurricular_activities);
            }
        }
        break;


    }
    fclose(output);
}

/**
 * Function: print_data
 * --------------------
 * @brief Prints the contents of the array of CurricularData.
 *
 * @param data Array of CurricularData to print.
 * @param size The number of records in the array.
 */
void print_data(const CurricularData data[], int size) {
    printf("Record_ID | Hours_Studied | Attendance | Tutoring_Sessions | Exam_Score\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%10d | %13d | %10d | %17d | %10d\n", 
            data[i].record_id, 
            data[i].hours_studied, 
            data[i].attendance, 
            data[i].tutoring_sessions, 
            data[i].exam_score);
    }
}

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @return int 0: No errors; 1: Errors produced.
 */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./spf_analyzer --TASK=\"X\"\n");
        return -1;
        }

        int task = 0;
        if (strncmp(argv[1], "--TASK=", 7) == 0) {
            task = atoi(argv[1] + 7);
        } else {
            printf("Error: Invalid argument format. Expected --TASK=X\n");
            return 1;
        }

        CurricularData data[MAX_RECORDS];
        int num_records = read_csv_file("data/a1-data-curricular.csv", data);
        if (num_records <= 0) {
            printf("Error: No records found or failed to read CSV.\n");
            return 1;
        }

        if (read_yaml_file("data/a1-data-extracurricular.yaml", data, num_records) < 0) {
            printf("Warning: Could not read YAML file.\n");
        }

        printf("Debug: Processing %d records...\n", num_records); // Debugging log
        process_task(task, data, num_records);
        printf("Task %d completed. Output written to output.csv\n", task);

        return 0;
    }