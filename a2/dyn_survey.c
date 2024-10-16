#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE 6000
#define MAX_QUESTIONS 38
#define MAX_QUESTION_LEN 512
#define MAX_TYPES 6
#define MAX_TYPES_LEN 512
#define NUMBER_RESPONDANTS 20
#define MAX_LINES 512
#define MAX_LINE_LEN 3000
#define MAX_CONFIG_BITS 12

void calculate_average(int **scores_array, int num_respondents) {
    float av_C = 0, av_I = 0, av_G = 0, av_U = 0, av_P = 0;

    for (int a = 0; a < num_respondents; a++) {
        float sum_C = 0, sum_I = 0, sum_G = 0, sum_U = 0, sum_P = 0;
        for (int i = 0; i < 8; i++) sum_C += scores_array[i][a];  // C questions
        for (int i = 8; i < 18; i++) sum_I += scores_array[i][a]; // I questions
        for (int i = 18; i < 28; i++) sum_G += scores_array[i][a]; // G questions
        for (int i = 28; i < 34; i++) sum_U += scores_array[i][a]; // U questions
        for (int i = 34; i < 38; i++) sum_P += scores_array[i][a]; // P questions

        av_C += sum_C / 8;
        av_I += sum_I / 10;
        av_G += sum_G / 10;
        av_U += sum_U / 6;
        av_P += sum_P / 4;
    }

    printf("C:%.2f,I:%.2f,G:%.2f,U:%.2f,P:%.2f\n", av_C / num_respondents, av_I / num_respondents, av_G / num_respondents, av_U / num_respondents, av_P / num_respondents);
}

void calculate_scores(int **scores_array, int num_respondants) {
    // LOOP THROUGH ANSWERS AND CALCULATE SCORE
    for (int a = 0; a < num_respondants; a++) {
        float sum_C = 0, sum_I = 0, sum_G = 0, sum_U = 0, sum_P = 0;
        int i = 0;

        for (i = 0; i < 8; i++) sum_C += scores_array[i][a];  // C questions
        printf("C:%.2f,", sum_C / 8);

        for (i = 8; i < 18; i++) sum_I += scores_array[i][a]; // I questions
        printf("I:%.2f,", sum_I / 10);

        for (i = 18; i < 28; i++) sum_G += scores_array[i][a]; // G questions
        printf("G:%.2f,", sum_G / 10);

        for (i = 28; i < 34; i++) sum_U += scores_array[i][a]; // U questions
        printf("U:%.2f,", sum_U / 6);

        for (i = 34; i < 38; i++) sum_P += scores_array[i][a]; // P questions
        printf("P:%.2f\n", sum_P / 4);
    }
}

void print_output(int config_bits[MAX_CONFIG_BITS], char questions[MAX_QUESTIONS][MAX_QUESTION_LEN], char likert_array[MAX_TYPES][MAX_TYPES_LEN], int reverse_array[MAX_QUESTIONS], int **frequencies, int num_respondents, int **scores_array) {
    printf("Examining Science and Engineering Students' Attitudes Towards Computer Science\n");
    printf("SURVEY RESPONSE STATISTICS\n\n");
    printf("NUMBER OF RESPONDENTS: %d\n", num_respondents);  // Now properly printing the number of respondents

    if (config_bits[0] == 1) {
        printf("\nFOR EACH QUESTION BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");

        for (int i = 0; i < MAX_QUESTIONS; i++) {
            printf("%s\n", questions[i]);
            // printf("I-INDEX: %d\n", i);
            for (int j = 0; j < MAX_TYPES; j++) {
            // printf("J-INDEX: %d\n", j);
                float percentage = ((float) frequencies[i][j] / num_respondents) * 100;
                printf("%.2f: %s\n", percentage, likert_array[j]);
            }
            printf("\n");
        }
    }

    if (config_bits[1] == 1) {
        printf("SCORES FOR ALL THE RESPONDENTS\n\n");
        // printf("\n");
        calculate_scores(scores_array, num_respondents);
        printf("\n");
    }

    if (config_bits[2] == 1) {
        printf("AVERAGE SCORES PER RESPONDENT\n\n");
        calculate_average(scores_array, num_respondents);
        // printf("\n");
    }
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

int parse_frequenciess(char *data, int **frequencies, int num_respondents, int *reverse_array, int **scores_array, int respondent_index) {
    char *token = strtok(data, ",\n");
    int i = 0;

    token = strtok(NULL, ",\n");
    token = strtok(NULL, ",\n");
    token = strtok(NULL, ",\n");

    while (token != NULL && i < MAX_QUESTIONS) {
        // printf("Token: %s\n", token);
        if (reverse_array[i] == 0) {
            // printf("RESPONDANT: %d;  INDEX: %d\n", respondent_index, i);
            if (strcmp(token, "fully disagree") == 0) {
                frequencies[i][0]++;
                scores_array[i][respondent_index] = 1;
            } else if (strcmp(token, "disagree") == 0) {
                frequencies[i][1]++;
                scores_array[i][respondent_index] = 2;
            } else if (strcmp(token, "partially disagree") == 0) {
                frequencies[i][2]++;
                scores_array[i][respondent_index] = 3;
            } else if (strcmp(token, "partially agree") == 0) {
                frequencies[i][3]++;
                scores_array[i][respondent_index] = 4;
            } else if (strcmp(token, "agree") == 0) {
                frequencies[i][4]++;
                scores_array[i][respondent_index] = 5;
            } else if (strcmp(token, "fully agree") == 0) {
                frequencies[i][5]++;
                scores_array[i][respondent_index] = 6;
            }
        } else { 
            // printf("RESPONDANT: %d;  INDEX: %d\n", respondent_index, i);
            if (strcmp(token, "fully disagree") == 0) {
                frequencies[i][0]++;
                scores_array[i][respondent_index] = 6;
            } else if (strcmp(token, "disagree") == 0) {
                frequencies[i][1]++;
                scores_array[i][respondent_index] = 5;
            } else if (strcmp(token, "partially disagree") == 0) {
                frequencies[i][2]++;
                scores_array[i][respondent_index] = 4;
            } else if (strcmp(token, "partially agree") == 0) {
                frequencies[i][3]++;
                scores_array[i][respondent_index] = 3;
            } else if (strcmp(token, "agree") == 0) {
                frequencies[i][4]++;
                scores_array[i][respondent_index] = 2;
            } else if (strcmp(token, "fully agree") == 0) {
                frequencies[i][5]++;
                scores_array[i][respondent_index] = 1;
            }
        }
        token = strtok(NULL, ",\n");
        i++;
    }

    return respondent_index;
}

int main() {
    char data[MAX_FILE];
    int config_bits[MAX_CONFIG_BITS];
    char questions[MAX_QUESTIONS][MAX_QUESTION_LEN];
    char likert_array[MAX_TYPES][MAX_TYPES_LEN];
    int reverse_array[MAX_QUESTIONS];
    int num_lines = 0;
    int num_respondents = 0;

    int **frequencies;
    int **scores_array;

    while (fgets(data, MAX_FILE, stdin) != NULL) {
        if (data[0] == '#') continue;

        if (num_lines == 0) {
            parse_config_bits(data, config_bits);
        }
        if (num_lines == 1) {
            parse_questions(data, questions);
        }
        if (num_lines == 2) {
            reverse_flag(data, reverse_array);
        }
        if (num_lines == 3) {
            likert_scale(data, likert_array);
        }
        if (num_lines == 4) {
            num_respondents = atoi(data);
            frequencies = (int **)malloc(MAX_QUESTIONS * sizeof(int *));
            scores_array = (int **)malloc(MAX_QUESTIONS * sizeof(int *));
            for (int i = 0; i < MAX_QUESTIONS; i++) {
                frequencies[i] = (int *)calloc(MAX_TYPES, sizeof(int));
                scores_array[i] = (int *)calloc(NUMBER_RESPONDANTS, sizeof(int));
            }
        }
        if (num_lines >= 5) {
            parse_frequenciess(data, frequencies, num_respondents, reverse_array, scores_array, num_lines - 5);
        }
        num_lines++;
    }

    print_output(config_bits, questions, likert_array, reverse_array, frequencies, num_respondents, scores_array);

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        free(frequencies[i]);
        free(scores_array[i]);
    }
    free(frequencies);
    free(scores_array);
    return 0;
}
