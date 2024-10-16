#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "dyn_survey.h"

void print_output(int config_bits[MAX_CONFIG_BITS], char questions[MAX_QUESTIONS][MAX_QUESTION_LEN], char likert_array[MAX_TYPES][MAX_TYPES_LEN], int reverse_array[MAX_QUESTIONS], int **frequencies, int num_respondents, int **scores_array);

#endif
