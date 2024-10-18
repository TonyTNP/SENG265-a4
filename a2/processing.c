#include "dyn_survey.h"
#include "output.h"
#include "processing.h"
#include "emalloc.h"
#include "input_handling.h"

void calculate_average(int **scores_array, int num_respondents) { //calculates average scores
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