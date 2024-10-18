#include "dyn_survey.h"
#include "output.h"
#include "processing.h"
#include "emalloc.h"
#include "input_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char data[MAX_FILE];
    int config_bits[MAX_CONFIG_BITS];
    char questions[MAX_QUESTIONS][MAX_QUESTION_LEN];
    char likert_array[MAX_TYPES][MAX_TYPES_LEN];
    int reverse_array[MAX_QUESTIONS];
    int num_lines = 0;
    int num_respondents = 0;  // Properly track the number of respondents

    int **frequencies;
    int **scores_array;

    // Reading input
    while (fgets(data, MAX_FILE, stdin) != NULL) {
        if (data[0] == '#') continue;  // Skip comment lines

        if (num_lines == 0) {
            parse_config_bits(data, config_bits);
        } if (num_lines == 1) {
            parse_questions(data, questions);
        } if (num_lines == 2) {
            reverse_flag(data, reverse_array);
        } if (num_lines == 3) {
            likert_scale(data, likert_array);
        } if (num_lines == 4) {
            // Attempt to parse the number of respondents from the 5th line
            num_respondents = atoi(data);  // Convert the string to an integer

            // Debug: print the parsed number of respondents
            printf("DEBUG: Parsed number of respondents = %d\n", num_respondents);

            // Ensure that the number of respondents is greater than 0
            if (num_respondents <= 0) {
                fprintf(stderr, "ERROR: Invalid number of respondents: %d\n", num_respondents);
                return 1;
            }

            // Allocate memory for frequencies and scores based on number of respondents
            frequencies = (int **)malloc(MAX_QUESTIONS * sizeof(int *));
            scores_array = (int **)malloc(MAX_QUESTIONS * sizeof(int *));
            for (int i = 0; i < MAX_QUESTIONS; i++) {
                frequencies[i] = (int *)calloc(MAX_TYPES, sizeof(int));
                scores_array[i] = (int *)calloc(num_respondents, sizeof(int));  // Use num_respondents here
            }
        } if (num_lines >= 5 && num_lines <= (5 + num_respondents - 1)) {
            // Process respondent data starting from line 6
            parse_frequenciess(data, frequencies, num_respondents, reverse_array, scores_array, num_lines - 5);
        }

        num_lines++;
    }

    // Print output
    print_output(config_bits, questions, likert_array, reverse_array, frequencies, num_respondents, scores_array);

    // Free dynamically allocated memory
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        free(frequencies[i]);
        free(scores_array[i]);
    }
    free(frequencies);
    free(scores_array);

    return 0;
}
