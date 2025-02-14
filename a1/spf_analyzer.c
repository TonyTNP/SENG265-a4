#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>  // Needed for strcasecmp()

#define MAX_RECORDS 6608

typedef struct {
    int record_id;
    int hours_studied;
    int attendance;
    int tutoring_sessions;
    int exam_score;
    char extracurricular_activities[10];
    int physical_activity;
    int sleep_hours;
} CurricularData;

/**
 * Function: read_csv_file
 * -----------------------
 * Reads data from the CSV file and populates CurricularData array.
 */
int read_csv_file(const char *filename, CurricularData data[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return -1;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), file); // Skip the header

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
 * Function: read_yaml_file
 * ------------------------
 * Reads extracurricular data from a YAML file and updates the array.
 */
int read_yaml_file(const char *filename, CurricularData data[], int num_records) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file: %s\n", filename);
        return -1;
    }

    char key[250], value[250];
    int record_id = -1;

    while (fscanf(file, " %249[^:]: %249[^\n]\n", key, value) != EOF) {
        if (key[0] == '-' && key[1] == ' ') {
            memmove(key, key + 2, strlen(key) - 1);
        }

        size_t len = strlen(value);
        if ((value[0] == '\'' || value[0] == '"') && (value[len - 1] == '\'' || value[len - 1] == '"')) {
            value[len - 1] = '\0';
            memmove(value, value + 1, len - 1);
        }

        if (strcmp(key, "Record_ID") == 0) {
            record_id = atoi(value);
        } else if (record_id >= 0) {
            for (int i = 0; i < num_records; i++) {
                if (data[i].record_id == record_id) {
                    if (strcmp(key, "Extracurricular_Activities") == 0) {
                        if (strcasecmp(value, "Yes") == 0 || strcmp(value, "1") == 0) {
                            strcpy(data[i].extracurricular_activities, "Yes");
                        } else {
                            strcpy(data[i].extracurricular_activities, "No");
                        }
                    } else if (strcmp(key, "Physical_Activity") == 0) {
                        int activity_level = atoi(value);
                        if (activity_level < 0 || activity_level > 10) {
                            printf("Warning: Record %d has invalid Physical_Activity=%d. Setting to 0.\n",
                                   record_id, activity_level);
                            data[i].physical_activity = 0;
                        } else {
                            data[i].physical_activity = activity_level;
                        }
                    } else if (strcmp(key, "Sleep_Hours") == 0) {
                        data[i].sleep_hours = atoi(value);
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < num_records; i++) {
        if (strlen(data[i].extracurricular_activities) == 0) {
            strcpy(data[i].extracurricular_activities, "No");
        }
    }

    fclose(file);
    return 0;
}

/**
 * Function: process_task
 * ----------------------
 * Processes the task and writes results to output.csv.
 */
void process_task(int task, CurricularData data[], int num_records) {
    FILE *output = fopen("output.csv", "w");
    if (output == NULL) {
        printf("Error: Could not create or open output.csv\n");
        return;
    }

    switch(task) {
        case 1:
            fprintf(output, "Record_ID,Exam_Score\n");
            for (int i = 0; i < num_records; i++) {
                if (data[i].exam_score > 90) {
                    fprintf(output, "%d,%d\n", data[i].record_id, data[i].exam_score);
                }
            }
            break;

        case 2:
            fprintf(output, "Extracurricular_Activities,Physical_Activity,Record_ID,Sleep_Hours\n");
            for (int i = 0; i < num_records; i++) {
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
                if (data[i].exam_score > 90) {
                    fprintf(output, "%d,%d,%s\n",
                            data[i].record_id,
                            data[i].exam_score,
                            data[i].extracurricular_activities);
                }
            }
            break;

        case 4:
            fprintf(output, "Record_ID,Exam_Score\n");
            for (int i = 0; i < num_records; i++) {
                if (data[i].attendance == 100) {
                    fprintf(output, "%d,%d\n", data[i].record_id, data[i].exam_score);
                }
            }
            break;

        case 5:
            fprintf(output, "Record_ID,Exam_Score\n");
            for (int i = 0; i < num_records; i++) {
                if (data[i].sleep_hours >= data[i].hours_studied) {
                    fprintf(output, "%d,%d\n", data[i].record_id, data[i].exam_score);
                }
            }
            break;

            case 6:
            fprintf(output, "Record_ID,Exam_Score,Extracurricular_Activities\n");
            
            for (int i = 0; i < num_records; i++) {
                if (data[i].exam_score < 60) {  
                    // Ensures extracurricular activities is either "Yes" or "No"
                    if (strlen(data[i].extracurricular_activities) == 0) {
                        strcpy(data[i].extracurricular_activities, "No");
                    }
        
                    // Writes to CSV with correct format
                    fprintf(output, "%d,%d,%s\n",
                            data[i].record_id,
                            data[i].exam_score,
                            data[i].extracurricular_activities);
                    
                    // Debug output to verify correctness
                    //printf("DEBUG: Writing Record_ID=%d, Exam_Score=%d, Extracurricular_Activities=%s\n",
                           //data[i].record_id, data[i].exam_score, data[i].extracurricular_activities);
                }
            }
            break;
        

        default:
            printf("Error: Task %d not implemented.\n", task);
            break;
    }

    fclose(output);
}

/**
 * Function: main
 * --------------
 * Entry point of the program.
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

    process_task(task, data, num_records);
    return 0;
}