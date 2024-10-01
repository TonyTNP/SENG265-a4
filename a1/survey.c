#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_FILE 6000

#define MAX_TYPES 6   // Max number of questions likert 
#define MAX_TYPES_LEN 512 // Max length for each question

#define MAX_QUESTIONS 38   // Max number of questions
#define MAX_QUESTION_LEN 512 // Max length for each question

#define NUMBER_OF_RESPONDANTS 5  // how many answer sets

#define MAX_CONFIG_BITS 12

#define MAX_LINES 512  //Max number of lines
#define MAX_LINE_LEN 4000 // Max length for line


//Cannot figure out how to get input tests 1,2&4 to print the type of response corresponding each question;
//The scores match, and the code parses through the text file. 
//However I still cannot figure this out!!!

void calcAvg(int scoresArray[MAX_QUESTIONS][NUMBER_OF_RESPONDANTS]) { //loops through answers and calculates average

    int y = 0;
    float avg_C = 0, avg_I = 0, avg_G = 0, avg_U =0, avg_P = 0;
    while (y < NUMBER_OF_RESPONDANTS) {
        float sum_C = 0, sum_I = 0, sum_G = 0, sum_U = 0, sum_P = 0;
        int i =0;
        // SUM C QUESTIONS
        while (i < 8) {
            sum_C = sum_C + scoresArray[i][y];
            i++;
        }
        avg_C += (sum_C/8);

        // SUM I QUESTIONS
        while (i >= 8 && i < 18) {            
            sum_I = sum_I + scoresArray[i][y];
            i++;
        }
        avg_I += sum_I/10;

        // SUM G QUESTIONS
        while (i >= 18 && i < 28) {
            sum_G = sum_G + scoresArray[i][y];
            i++;
        }
        avg_G = avg_G + sum_G/10;

        // SUM U QUESTIONS
        while (i >= 28 && i < 34) {
            sum_U += scoresArray[i][y];
            i++;
        }
        avg_U = avg_U + sum_U/6;

        // SUM P QUESTIONS
        while (i >= 34 && i < 38) {
            sum_P = sum_P + scoresArray[i][y];
            i++;
            
        }
        avg_P = avg_P + sum_P/4;

        y++;
    }

    printf("C:%.2f,", avg_C/5);
    printf("I:%.2f,", avg_I/5);
    printf("G:%.2f,", avg_G/5);
    printf("U:%.2f,", avg_U/5);
    printf("P:%.2f\n", avg_P/5);

    if (y < NUMBER_OF_RESPONDANTS - 1) {
        printf("\n");
    }
}


void calcScores(int scoresArray[MAX_QUESTIONS][NUMBER_OF_RESPONDANTS]) { //loops through answers and calculates the score

    int y = 0;
    while (y < NUMBER_OF_RESPONDANTS) {
        float sum_C = 0, sum_I = 0, sum_G = 0, sum_U = 0, sum_P = 0;
        int i = 0;

        //sum_C questions

        while (i < 8) {
            sum_C += scoresArray[i][y];
            i++;
        }

        printf("C:%.2f,", sum_C/8);

        //sum_I questions

        while (i >= 8 && i < 18) {            
            sum_I += scoresArray[i][y];
            i++;
        }

        printf("I:%.2f,",sum_I/10);

        //sum_G questions

        while (i >= 18 && i < 28) {
            sum_G += scoresArray[i][y];
            i++;
        }

        printf("G:%.2f,",sum_G/10);

        //sum_U questions

        while (i>=28 && i<34) {
            sum_U += scoresArray[i][y];
            i++;
            }

        printf("U:%.2f,",sum_U/6);

        //sum_P questions

        while (i>=34 && i<38) {
            sum_P += scoresArray[i][y];
            i++;
           }

        printf("P:%.2f\n",sum_P/4);
        y++;

        }

    if (y < NUMBER_OF_RESPONDANTS - 1) {
        printf("\n");

        }
    }

void printOut(int configBits[MAX_CONFIG_BITS], char questions[MAX_QUESTIONS][MAX_QUESTION_LEN], char likert_array[MAX_TYPES][MAX_TYPES_LEN], int reverseArray[MAX_QUESTIONS], int freqs[MAX_QUESTIONS][MAX_TYPES], int numRespondants, int scoresArray[MAX_QUESTIONS][NUMBER_OF_RESPONDANTS]) {
    printf("Examining Science and Engineering Students' Attitudes Towards Computer Science\n");
    printf("SURVEY RESPONSE STATISTICS\n");
    printf("\n");
    printf("NUMBER OF RESPONDENTS: ");
    printf("%d\n", numRespondants);
    // printf("\n");

    if (configBits[0] == 1 || configBits[1] == 1 ){

        printf("\nFOR EACH QUESTION BELOW, RELATIVE PERCENTUAL FREQUENCIES ARE COMPUTED FOR EACH LEVEL OF AGREEMENT\n\n");
        
        int i =0;

        while (i < MAX_QUESTIONS) {

            printf("%s\n", questions[i]);
            for (int j=0; j<MAX_TYPES; j++) {

                float percentage;
                int val = freqs[i][j];
                percentage = (val / 5.0)*100;

                printf("%.2f: ", percentage);
                
		//switch (likert_array[i])
		  //  case 1: print fully disagree
		//case 2: print ...
		//case 3: print fully agree
			
                printf("%s\n",likert_array[j]);

                }

            if (i < MAX_QUESTIONS - 1) {
                printf("\n");
            }

            i++;
        }
    }
        
    if (configBits[2]) {
        printf("\nSCORES FOR ALL THE RESPONDENTS\n");
        printf("\n");
        calcScores(scoresArray);

    }

    if (configBits[3]) {
        printf("\nAVERAGE SCORES PER RESPONDENT\n");
        printf("\n");
        calcAvg(scoresArray);
    }

}

void parse_configBits(char *data, int configBits[MAX_CONFIG_BITS]){
    

    char *tok;
    tok = strtok(data, ",\n");
    
    int i=0;

    while (tok != NULL) { 
        configBits[i] = atoi(tok); //assign tokens to the array
        tok = strtok(NULL, ",\n"); //next token
        i++;
        
        }

    }


int parse_questions(char *data, char questions[MAX_QUESTIONS][MAX_QUESTION_LEN]) {
    
    // // first token 
    char *tok = strtok(data, ";\n");
    int questionIndex = 0;
    

    // returns null at the end
    while (tok != NULL && questionIndex < 38) { 

        //copy into array
        strncpy(questions[questionIndex], tok, MAX_QUESTION_LEN-1);

        
        questionIndex++; //increment array position index 

        // Get the next token using existing string
        
        tok = strtok(NULL, ";\n");
        

        }

    

    return questionIndex;
    }

void reverseFlag(char *data, int reverseArray[MAX_QUESTIONS]) {
    char *tok;
    tok = strtok(data, ";\n");
    int i = 0;

    //if Direct => 0, if Reverse => 1
    while (tok != NULL) { 
        if (strcmp(tok, "Direct") == 0) {
            reverseArray[i] = 0;
        } else {
            reverseArray[i] = 1;
        }
        tok = strtok(NULL, ";\n");
        i++;
    }
}

void likert_scale(char *data, char likert_array[MAX_TYPES][MAX_TYPES_LEN]){

    char *tok;
    tok = strtok(data, ",\n");
    int i =0;
 
    // store in array containing all options
    while(tok != NULL) {
        strncpy(likert_array[i], tok, MAX_TYPES_LEN);
        tok = strtok(NULL, ",\n");
        i++;
	
	}
    
}

int parse_freqs(char *data, int freqs[MAX_QUESTIONS][MAX_TYPES], int numRespondants, int reverseArray[MAX_QUESTIONS], int scoresArray[MAX_QUESTIONS][NUMBER_OF_RESPONDANTS]){
    
    char *tok;
    int i = 0;
    numRespondants++;
    
    
    tok = strtok(data, ",\n"); //faulty   
    tok = strtok(NULL, ",\n"); //yes or no
    tok = strtok(NULL, ",\n"); //date
    tok = strtok(NULL, ",\n"); //first answer

    // Storing the score in a bidirectional array, each set of answers are stored and scores are calculated after
    
    while(tok != NULL) {
        

        if (reverseArray[i] == 0){
            if (strcmp(tok, "fully disagree") == 0) {
                freqs[i][0]++;
                
                scoresArray[i][numRespondants-1] = 1;

            } else if (strcmp(tok, "disagree") == 0) {
                freqs[i][1]++;
                
                scoresArray[i][numRespondants-1] = 2;

            } else if (strcmp(tok, "partially disagree") == 0) {
                freqs[i][2]++;
                
                scoresArray[i][numRespondants-1] = 3;

            } else if (strcmp(tok, "partially agree") == 0) {
                freqs[i][3]++;
                
                scoresArray[i][numRespondants-1] = 4;

            } else if (strcmp(tok, "agree") == 0) {
                freqs[i][4]++;
                
                scoresArray[i][numRespondants-1] = 5;

            } else if (strcmp(tok, "fully agree") == 0) {
                freqs[i][5]++;
                
                scoresArray[i][numRespondants-1] = 6;
            }

            tok = strtok(NULL, ",\n");
            i++;

            } else {

            if (strcmp(tok, "fully disagree") == 0) {
                freqs[i][5]++;
                
                scoresArray[i][numRespondants-1] = 6;

            } else if (strcmp(tok, "disagree") == 0) {
                freqs[i][4]++;
                
                scoresArray[i][numRespondants-1] = 5;

            } else if (strcmp(tok, "partially disagree") == 0) {
                freqs[i][3]++;
                
                scoresArray[i][numRespondants-1] = 4;

            } else if (strcmp(tok, "partially agree") == 0) {
                freqs[i][2]++;
                
                scoresArray[i][numRespondants-1] = 3;

            } else if (strcmp(tok, "agree") == 0) {
                freqs[i][1]++;
                
                scoresArray[i][numRespondants-1] = 2;

            } else if (strcmp(tok, "fully agree") == 0) {
                freqs[i][0]++;
                
                scoresArray[i][numRespondants-1] = 1;

            }

            tok = strtok(NULL, ",\n");
            i++;
        }
    }
    return numRespondants;
}


int main() {

    char data[MAX_FILE];                                
    int configBits[MAX_CONFIG_BITS];                   // Array to store config
    char questions[MAX_QUESTIONS][MAX_QUESTION_LEN];  // Array to store parsed questions
    char likert_array[MAX_TYPES][MAX_TYPES_LEN];     // Array to store likert answers
    int reverseArray[MAX_QUESTIONS];                // Array to store reverse flag
    int freqs[MAX_QUESTIONS][MAX_TYPES];           // store answers
    int scoresArray[MAX_QUESTIONS][NUMBER_OF_RESPONDANTS];

    int numQuestions = 0;   //number of questions

    int numLines = 0;      // variable used for fgets read lines
    int numRespondants = 0; //variable used for fgets read lines
    
    //read in the file
    while ( fgets(data, MAX_FILE, stdin) != NULL ) {
        
        if (data[0] == '#') {
            continue;
        } 
        if (numLines == 0) {
            
            parse_configBits(data, configBits);
            numLines++;
            continue;
        }

        if (numLines == 1) {
            //parse_questions(data, questions);
            numQuestions = parse_questions(data, questions);
            numLines++;
            continue;
        }

        if (numLines == 2) {
            
            reverseFlag(data, reverseArray);
            numLines++;
            continue;
        }

        if (numLines == 3) {
            
            numLines++;
            continue;
        }

        if (numLines == 4) { 
            
            numRespondants = parse_freqs(data, freqs, numRespondants, reverseArray, scoresArray);
            // calculate_scores(data);
            numLines++;
            continue;
            
        }

        if (numLines == 5) { 
            
            numRespondants = parse_freqs(data, freqs, numRespondants, reverseArray, scoresArray );
            // calculate_scores();
            numLines++;
            continue;
        }

        if (numLines == 6) { 
            
            numRespondants = parse_freqs(data, freqs, numRespondants, reverseArray, scoresArray);
            // calculate_scores();
            numLines++;
            continue;
        }

        if (numLines == 7) { 
            
            numRespondants = parse_freqs(data, freqs, numRespondants, reverseArray, scoresArray);
            // calculate_scores();
            numLines++;
            continue;
        }

        if (numLines == 8) { 
            
            numRespondants = parse_freqs(data, freqs, numRespondants, reverseArray, scoresArray);
            // calculate_scores();
            numLines++;
            continue;
        }
    }

    printOut(configBits, questions, likert_array, reverseArray, freqs, numRespondants, scoresArray);



    exit(0);
}
