#include "dyn_survey.h"
#include "output.h"
#include "processing.h"
// #include "emalloc.h"
// #include "input_handling.h"

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