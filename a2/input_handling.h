#ifndef _INPUT_HANDLING_H_
#define _INPUT_HANDLING_H_

#include "dyn_survey.h"

void parse_frequenciess(char *data, int **frequencies, int num_respondents, int *reverse_array, int **scores_array, int respondent_index);
void parse_config_bits(char *data, int config_bits[MAX_CONFIG_BITS]);
int parse_questions(char *data, char questions[MAX_QUESTIONS][MAX_QUESTION_LEN]);
void reverse_flag(char *data, int reverse_array[MAX_QUESTIONS]);
void likert_scale(char *data, char likert_array[MAX_TYPES][MAX_TYPES_LEN]);

#endif
