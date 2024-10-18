#include "dyn_survey.h"
// #include "output.h"
// #include "processing.h"
// #include "emalloc.h"
#include "input_handling.h"

void parse_frequenciess(char *data, int **frequencies, int num_respondents, int *reverse_array, int **scores_array, int respondent_index) {
    char *token = strtok(data, ",\n");
    int i = 0;

    //printf("Token1: %s\n", token);
    token = strtok(NULL, ",\n");
    //printf("Token2: %s\n", token);
    token = strtok(NULL, ",\n");
    //printf("Token3: %s\n\n", token);
    token = strtok(NULL, ",\n");

    // if the filter variable is set

    while (token != NULL && i < MAX_QUESTIONS) {
        // printf("Token: %s\n", token);
        if (reverse_array[i] == 0) {
            // printf("RESPONDANT: %d;  INDEX: %d\n", respondent_index, i);

            //comparing tokens with responses and updating the frequencies array
            if (strcmp(token, "fully disagree") == 0) {
                frequencies[i][0]++;
                scores_array[i][respondent_index] = 1;
            } if (strcmp(token, "disagree") == 0) {
                frequencies[i][1]++;
                scores_array[i][respondent_index] = 2;
            } if (strcmp(token, "partially disagree") == 0) {
                frequencies[i][2]++;
                scores_array[i][respondent_index] = 3;
            } if (strcmp(token, "partially agree") == 0) {
                frequencies[i][3]++;
                scores_array[i][respondent_index] = 4;
            } if (strcmp(token, "agree") == 0) {
                frequencies[i][4]++;
                scores_array[i][respondent_index] = 5;
            } if (strcmp(token, "fully agree") == 0) {
                frequencies[i][5]++;
                scores_array[i][respondent_index] = 6;
            }
        } else { 
            // printf("RESPONDANT: %d;  INDEX: %d\n", respondent_index, i);
            if (strcmp(token, "fully disagree") == 0) {
                frequencies[i][0]++;
                scores_array[i][respondent_index] = 6;
            } if (strcmp(token, "disagree") == 0) {
                frequencies[i][1]++;
                scores_array[i][respondent_index] = 5;
            } if (strcmp(token, "partially disagree") == 0) {
                frequencies[i][2]++;
                scores_array[i][respondent_index] = 4;
            } if (strcmp(token, "partially agree") == 0) {
                frequencies[i][3]++;
                scores_array[i][respondent_index] = 3;
            } if (strcmp(token, "agree") == 0) {
                frequencies[i][4]++;
                scores_array[i][respondent_index] = 2;
            } if (strcmp(token, "fully agree") == 0) {
                frequencies[i][5]++;
                scores_array[i][respondent_index] = 1;
            }
        }
        token = strtok(NULL, ",\n");
        i++;
    }

    // return respondent_index;
}

void parse_config_bits(char *data, int config_bits[MAX_CONFIG_BITS]) {
    char *token = strtok(data, ",\n");
    int i = 0;

    while (token != NULL && i < MAX_CONFIG_BITS) {
        config_bits[i] = atoi(token);
        token = strtok(NULL, ",\n");
        i++;
    }
}

int parse_questions(char *data, char questions[MAX_QUESTIONS][MAX_QUESTION_LEN]) {
    char *token = strtok(data, ";\n");
    int question_index = 0;

    while (token != NULL && question_index < MAX_QUESTIONS) {
        strncpy(questions[question_index], token, MAX_QUESTION_LEN - 1);
        token = strtok(NULL, ";\n");
        question_index++;
    }
    return question_index;
}

void reverse_flag(char *data, int reverse_array[MAX_QUESTIONS]) {
    char *token = strtok(data, ";\n");
    int i = 0;

    while (token != NULL && i < MAX_QUESTIONS) {
        reverse_array[i] = (strcmp(token, "Direct") == 0) ? 0 : 1;
        token = strtok(NULL, ";\n");
        i++;
    }
}

void likert_scale(char *data, char likert_array[MAX_TYPES][MAX_TYPES_LEN]) {
    char *token = strtok(data, ",\n");
    int i = 0;

    while (token != NULL && i < MAX_TYPES) {
        strncpy(likert_array[i], token, MAX_TYPES_LEN - 1);
        token = strtok(NULL, ",\n");
        i++;
    }
}
