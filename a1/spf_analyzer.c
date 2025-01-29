#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int read_yaml_file(const char *filename, CurricularData data[], int num_records){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Error: Could not open file: %s\n", filename);
        return -1;
    }

    char key[50], value[50];
    int record_id = -1;
    while (fscanf(file, " %49[^:]: %49[^\n]\n", key, value)!=EOF){
        if(strcmp(key, "Record_ID") == 0){
            record_id = atoi(value);
        } else if (record_id >= 0){
            for (int i = 0; i < num_records; i++){
                if(data[i].record_id==record_id){
                    if(strcmp(key, "Extracurricular_Activities") == 0){
                        strncpy(data[i].extracurricular_activities, value, sizeof(data[i].extracurricular_activities)-1);
                        data[i].extracurricular_activities[sizeof(data[i].extracurricular_activities)-1] = '\0'; // Null terminator
                    } else if(strcmp(key, "Physical_Activity") == 0){
                        data[i].physical_activity=atoi(value);
                    } else if (strcmp(key, "Sleep_Hours") == 0){
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
    FILE *output = fopen("output.csv", "w");
    if(output==NULL) {
        printf("Error: Could not create output.csv\n");
        return;
    }

    switch(task) {
        case 1:
        fprintf(output, "Record_ID, Exam_Score\n");
        for (int i = 0; i < num_records; i++) {
            if(data[i].exam_score > 90) {
                fprintf(output, "%d, %d\n", 
                data[i].record_id, 
                data[i].exam_score);
            }
        }
        break;

        case 2:
        fprintf(output, "Record_ID, Extracurricular_Activities, Physical_Activity, Sleep_Hours\n");
        for (int i = 0; i < num_records; i++) {
            fprintf(output, "%d, %s, %d, %d\n", 
            data[i].record_id, 
            data[i].extracurricular_activities, 
            data[i].physical_activity, 
            data[i].sleep_hours);
        }
        break;
        
        case 3:
        fprintf(output, "Record_ID, Exam_Score, Extracurricula_Activities\n");
        for (int i = 0; i < num_records; i++) {
            if(data[i].exam_score > 90){
            fprintf(output, "%d, %d, %s\n", 
            data[i].record_id, 
            data[i].exam_score, 
            data[i].extracurricular_activities);
            }
        }
        break;

        case 4:
        fprintf(output, "Record_ID, Exam_Score\n");
        for (int i = 0; i < num_records; i++) {
            if(data[i].attendance == 100){
            fprintf(output, "%d, %d\n", 
            data[i].record_id, 
            data[i].exam_score);
            }
        }
        break;

        case 5:
        fprintf(output, "Record_ID, Exam_Score\n");
        for(int i = 0; i < num_records; i++){
            if(data[i].sleep_hours >= data[i].hours_studied){
                fprintf(output, "%d, %d\n", 
                data[i].record_id, 
                data[i].exam_score);
            }
        }
        break;

        case 6:
        fprintf(output, "Record_ID, Exam_Score, Extracurricular_Activities\n");
        for(int i = 0; i < num_records; i++){
            if(data[i].exam_score < 60){
                fprintf(output, "%d, %d, %s\n", 
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
    if(argc < 2){
        printf("Usage: ./spf_analyzer --TASK=\"X\"\n");
        return -1;
    }

    int task = 0; //Defaults to zero in case of failure
    if(strncmp(argv[1], "--TASK=", 7) == 0) {
        task = atoi(argv[1]+7); //extract the number after "--TASK"
    } else {
        printf("Error: Invalid argument format. Expected --TASK = X\n");
        return 1;
    }

    CurricularData data[MAX_RECORDS];  // Array to hold all rows from the CSV
    //const char *filename = "data/a1-data-curricular.csv";

    int num_records = read_csv_file("data/a1-data-curricular.csv", data);
    read_yaml_file("data/a1-data-extracurricular.yaml", data, num_records);
    process_task(task, data, num_records);
    printf("Task %d completed. Output written to output.csv\n",task);
    return 0;
    
    // if (num_records < 0) {
    //     return 1; // Error occurred while reading the file
    // }

    // printf("\nSuccessfully read %d records from %s\n\n", num_records, filename);
    // print_data(data, num_records);

    return 0;
}
