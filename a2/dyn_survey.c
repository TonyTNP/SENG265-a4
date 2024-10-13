#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX_FILE 6000

#define MAX_QUESTIONS 38   // Max number of questions
#define MAX_QUESTION_LEN 512 // Max length for each question

#define MAX_TYPES 6   // Max number of questions likert 
#define MAX_TYPES_LEN 512 // Max length for each question

#define NUMBER_RESPONDANTS 5  // how many answer sets

#define MAX_LINES 512   // Max number of lines
#define MAX_LINE_LEN 3000 // Max length for line

#define MAX_CONFIG_BITS 12

// call numbers 
// calculate in print funciton

/*

Reads the input file with the test configuration, question descriptions, question types (direct or reverse), answer types, number of responses, responses per se, and the filtering options, and stores data appropriately.

When coding the system, don’t forget to modularize everything, separate data input handling from statistics calculations, separate calculation for each statistic, separate printing output data. Use different files for different categories of functions. You know, those things to make maintainers’ lives easier in the future."
*/

void calculate_average(int scores_array[MAX_QUESTIONS][NUMBER_RESPONDANTS]) {
    //LOOP THROUGH ANSWERS AND CALCULATE AVERAGE
    int a=0;
    float av_C = 0, av_I = 0, av_G = 0, av_U =0, av_P = 0;
    while (a < NUMBER_RESPONDANTS) {
        float sum_C = 0, sum_I = 0, sum_G = 0, sum_U = 0, sum_P = 0;
        int i =0;
        // SUM C QUESTIONS
        while (i < 8) {
            sum_C += scores_array[i][a];
            i++;
        }
        av_C += sum_C/8;

        // SUM I QUESTIONS
        while (i>=8 && i<18) {            
            sum_I += scores_array[i][a];
            i++;
        }
        av_I += sum_I/10;

        // SUM G QUESTIONS
        while (i>=18 && i<28) {
            sum_G += scores_array[i][a];
            i++;
        }
        av_G += sum_G/10;

        // SUM U QUESTIONS
        while (i>=28 && i<34) {
            sum_U += scores_array[i][a];
            i++;
        }
        av_U += sum_U/6;

        // SUM P QUESTIONS
        while (i>=34 && i<38) {
            sum_P += scores_array[i][a];
            i++;
            // printf("%d ")
        }
        av_P += sum_P/4;

        a++;
    }

    printf("C:%.2f,", av_C/5);
    printf("I:%.2f,", av_I/5);
    printf("G:%.2f,", av_G/5);
    printf("U:%.2f,", av_U/5);
    printf("P:%.2f\n", av_P/5);

    if (a < NUMBER_RESPONDANTS - 1) {
        printf("\n");
    }
}

void calculate_scores(int scores_array[MAX_QUESTIONS][NUMBER_RESPONDANTS]) {
    //LOOP THROUGH ANSWERS AND CALCULATE SCORE
    int a=0;
    while (a < NUMBER_RESPONDANTS) {
        float sum_C = 0, sum_I = 0, sum_G = 0, sum_U = 0, sum_P = 0;
        int i =0;
        // SUM C QUESTIONS
        while (i < 8) {
            sum_C += scores_array[i][a];
            i++;
        }
        printf("C:%.2f,", sum_C/8);

        // SUM I QUESTIONS
        while (i>=8 && i<18) {            
            sum_I += scores_array[i][a];
            i++;
        }
        printf("I:%.2f,",sum_I/10);

        // SUM G QUESTIONS
        while (i>=18 && i<28) {
            sum_G += scores_array[i][a];
            i++;
        }
        printf("G:%.2f,",sum_G/10);

        // SUM U QUESTIONS
        while (i>=28 && i<34) {
            sum_U += scores_array[i][a];
            i++;
        }
        printf("U:%.2f,",sum_U/6);

        // SUM P QUESTIONS
        while (i>=34 && i<38) {
            sum_P += scores_array[i][a];
            i++;
        }
        printf("P:%.2f\n",sum_P/4);
        a++;
    }
    if (a < NUMBER_RESPONDANTS - 1) {
        printf("\n");
    }
}

void print_output(int config_bits[MAX_CONFIG_BITS], char questions[MAX_QUESTIONS][MAX_QUESTION_LEN], char likert_array[MAX_TYPES][MAX_TYPES_LEN], int reverse_array[MAX_QUESTIONS], int frequencies[MAX_QUESTIONS][MAX_TYPES], int num_respondants, int scores_array[MAX_QUESTIONS][NUMBER_RESPONDANTS]) {
    printf("Examining Science and Engineering Students' Attitudes Towards Computer Science\n");
    printf("SURVEY RESPONSE STATISTICS\n");
    printf("\n");
    printf("NUMBER OF RESPONDENTS: ");
    printf("%d\n", num_respondants);
    // printf("\n");

    // First bit is for showing relative frequencies; second bit for individual scores; and finally third bit is for average scores. If more than one bit is on, then combine print output.
        // /* 

    if (config_bits[0] == 1){

        printf("\nFOR EACH QUESTION BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");
        
        int i =0;
        while (i < MAX_QUESTIONS) {
            printf("%s\n", questions[i]);
            for (int k=0; k<MAX_TYPES; k++) {

                float percentage;
                int value = frequencies[i][k];
                percentage = (value / 5.0) * 100;

                printf("%.2f: ", percentage);
                // printf("Q:%d  %d: ", i,k);
                printf("%s\n",likert_array[k]);
            }
            if (i < MAX_QUESTIONS - 1) {
                printf("\n");
            }
            i++;
        }
    }
        
    if (config_bits[1]) {
        printf("\nSCORES FOR ALL THE RESPONDENTS\n");
        printf("\n");
        calculate_scores(scores_array);
    }
    if (config_bits[2]) {
        printf("\nAVERAGE SCORES PER RESPONDENT\n");
        printf("\n");
        calculate_average(scores_array);
    }
    // */

}

int num_responses(char *data) {
    char *token;
    token = strtok(data, ",\n");
    int responses = atoi(token);
    return responses;

}
void parse_config_bits(char *data, int config_bits[MAX_CONFIG_BITS]){

    // printf("%s\n", data);
    char *token;
    token = strtok(data, ",\n");
    // printf("%s\n", token);
    int i=0;

    while (token != NULL) { 
        config_bits[i] = atoi(token);        // assign them to the array
        token = strtok(NULL, ",\n");     // here is next token
        i++;
        // printf("%s\n", token);
    }

}

int parse_questions(char *data, char questions[MAX_QUESTIONS][MAX_QUESTION_LEN]) {
    // printf("%s\n", data);
    // // first token 
    char *token = strtok(data, ";\n");
    int question_index = 0;
    // printf("%s\n", token);

    // // returns null at the end
    while (token != NULL && question_index < 38) { 
        //copy into array
        strncpy(questions[question_index], token, MAX_QUESTION_LEN-1);
        // increase index for array position
        question_index++;

        // Get the next token using existing string
        // printf("%s\n", token);
        token = strtok(NULL, ";\n");
        // printf("%i\n", question_index);
    }
    // // Set the number of parsed questions return question index
    return question_index;
}

void reverse_flag(char *data, int reverse_array[MAX_QUESTIONS]) {
    char *token;
    token = strtok(data, ";\n");
    int i = 0;

    // stored in parallel array, if Direct => 0, if Reverse => 1
    while (token != NULL) { 

        if (strcmp(token, "Direct") == 0) {
            // printf("%s: 0, ", token);
            reverse_array[i] = 0;
        } else {
            // printf("%s: 1, ", token);
            reverse_array[i] = 1;
        }
        token = strtok(NULL, ";\n");
        i++;
    }
}

void likert_scale(char *data, char likert_array[MAX_TYPES][MAX_TYPES_LEN]){
    char *token;
    token = strtok(data, ",\n");
    int i =0;

    // store in array containing all options
    while(token != NULL) {
        strncpy(likert_array[i], token, MAX_TYPES_LEN);
        token = strtok(NULL, ",\n");
        i++;
    }
}

int parse_frequenciess(char *data, int frequencies[MAX_QUESTIONS][MAX_TYPES], int num_respondants, int reverse_array[MAX_QUESTIONS], int scores_array[MAX_QUESTIONS][NUMBER_RESPONDANTS]){
    // printf("%s", data);
    char *token;
    int i = 0;
    num_respondants++;
    // printf("%d",num_respondants);

    // what are these good for ??
    token = strtok(data, ",\n");        // faulty   
    token = strtok(NULL, ",\n");        // yes or no
    token = strtok(NULL, ",\n");        // date
    token = strtok(NULL, ",\n");        // first answer

    // STORING THE SCORE IN A BIDIRECTIONAL ARRAY, parrallels the questions array X the respondat, each set of answerss are stored. store them all and calculate scores after
    // FREQUENCIES INCREASES by 1 every time is selected.  storing number of times selected in paralell with questions, organized 
    while(token!=NULL) {
        // printf("Respondant: %d  -  ", num_respondants);
        // printf("Reversed: %d  -  ", reverse_array[i]);
        // printf("Question: %d  -  ", i);
        // printf("%s  -  ", token);
        if (reverse_array[i] == 0){
            // printf("\ndirect: %s , %d", token, i);
            if (strcmp(token, "fully disagree") == 0) {
                frequencies[i][0]++;
                // printf("1 points\n");
                scores_array[i][num_respondants-1] = 1;
            } else if (strcmp(token, "disagree") == 0) {
                frequencies[i][1]++;
                // printf("2 points\n");
                scores_array[i][num_respondants-1] = 2;
            } else if (strcmp(token, "partially disagree") == 0) {
                frequencies[i][2]++;
                // printf("3 points\n");
                scores_array[i][num_respondants-1] = 3;
            } else if (strcmp(token, "partially agree") == 0) {
                frequencies[i][3]++;
                // printf("4 points\n");
                scores_array[i][num_respondants-1] = 4;
            } else if (strcmp(token, "agree") == 0) {
                frequencies[i][4]++;
                // printf("5 points\n");
                scores_array[i][num_respondants-1] = 5;
            } else if (strcmp(token, "fully agree") == 0) {
                frequencies[i][5]++;
                // printf("6 points\n");
                scores_array[i][num_respondants-1] = 6;
            }
            token = strtok(NULL, ",\n");
            i++;
        }else {
            // printf("\nreverse: %s , %d", token, i);
            if (strcmp(token, "fully disagree") == 0) {
                frequencies[i][0]++;
                // printf("6 points\n");
                scores_array[i][num_respondants-1] = 6;
            } else if (strcmp(token, "disagree") == 0) {
                frequencies[i][1]++;
                scores_array[i][num_respondants-1] = 5;
            } else if (strcmp(token, "partially disagree") == 0) {
                frequencies[i][2]++;
                // printf("4 points\n");
                scores_array[i][num_respondants-1] = 4;
            } else if (strcmp(token, "partially agree") == 0) {
                frequencies[i][3]++;
                // printf("3 points\n");
                scores_array[i][num_respondants-1] = 3;
            } else if (strcmp(token, "agree") == 0) {
                frequencies[i][4]++;
                // printf("2 points\n");
                scores_array[i][num_respondants-1] = 2;
            } else if (strcmp(token, "fully agree") == 0) {
                frequencies[i][5]++;
                // printf("1 points\n");
                scores_array[i][num_respondants-1] = 1;
            }
            token = strtok(NULL, ",\n");
            i++;
        }
    }
    return num_respondants;
}

/*
 Thus, they decided to change the input file format, adding one line for the number of survey responses before the survey responses per se. Then, they also added one or more lines after the survey responses to describe one or more filtering options. For the given filtering configuration, the statistics should be computed and written to the output for the selected subset of respondents.
*/

/* loops over stdin lines */
int main() {

    char data[MAX_FILE];                                // string array for entire fdocument
    int config_bits[MAX_CONFIG_BITS];                   // Array to store config
    char questions[MAX_QUESTIONS][MAX_QUESTION_LEN];    // Array to store parsed questions
    char likert_array[MAX_TYPES][MAX_TYPES_LEN];        // Array to store likert answers
    int reverse_array[MAX_QUESTIONS];                   // Array to store reverse flag
    int frequencies[MAX_QUESTIONS][MAX_TYPES];                    // store answers
    int scores_array[MAX_QUESTIONS][NUMBER_RESPONDANTS];
    int given_responses;                                // given int responses from input

    int num_questions = 0;   // number of questions
    int num_lines = 0;      // variable used for fgets read lines
    int num_respondants = 0;      // variable used for fgets read lines
    
    // read in the file
    while ( fgets(data, MAX_FILE, stdin) != NULL ) {
        // // Skip the comment lines
        if (data[0] == '#') {
            continue;
        } 
        if (num_lines == 0) {
            // printf("%s\n", data);
            parse_config_bits(data, config_bits);
            num_lines++;
            continue;
        }
        if (num_lines == 1) {
            // printf("%s\n", data);
            num_questions = parse_questions(data, questions);
            num_lines++;
            continue;
        }
        if (num_lines == 2) {
            // printf("%s\n", data);
            reverse_flag(data, reverse_array);
            num_lines++;
            continue;
        }
        if (num_lines == 3) {
            // printf("%s\n", data);
            likert_scale(data, likert_array);
            num_lines++;
            continue;
        }

        // new function - number of responses
        if (num_lines == 4) { 
            // printf("%s\n", data);
            given_responses = num_responses(data);
            // calculate_scores(data);
            num_lines++;
            continue;
        }

        if (num_lines == 5) { 
            // printf("%s\n", data);
            num_respondants = parse_frequenciess(data, frequencies, num_respondants, reverse_array, scores_array);
            // calculate_scores(data);
            num_lines++;
            continue;
            
        }
        if (num_lines == 6) { 
            // printf("%s\n", data);
            num_respondants = parse_frequenciess(data, frequencies, num_respondants, reverse_array, scores_array );
            // calculate_scores();
            num_lines++;
            continue;
        }
        if (num_lines == 7) { 
            // printf("%s\n", data);
            num_respondants = parse_frequenciess(data, frequencies, num_respondants, reverse_array, scores_array);
            // calculate_scores();
            num_lines++;
            continue;
        }
        if (num_lines == 8) { 
            // printf("%s\n", data);
            num_respondants = parse_frequenciess(data, frequencies, num_respondants, reverse_array, scores_array);
            // calculate_scores();
            num_lines++;
            continue;
        }
        if (num_lines == 9) { 
            // printf("%s\n", data);
            num_respondants = parse_frequenciess(data, frequencies, num_respondants, reverse_array, scores_array);
            // calculate_scores();
            num_lines++;
            continue;
        }
    }

    print_output(config_bits, questions, likert_array, reverse_array, frequencies, num_respondants, scores_array);



    exit(0);
}