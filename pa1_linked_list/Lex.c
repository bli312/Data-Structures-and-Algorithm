/***
 * Leo Li
 * 2024 Fall UCSC CSE101 PA1
 * Lex.c
 * Using functions to sort a List in alphabetical order and return the index.
 ***/


#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>
#include "List.h"
#include <stdint.h>


void free_vocabulary(char **vocabulary, int num_words){
    for (int k = 0; k < num_words; k++){
        free(vocabulary[k]);
    }
    free(vocabulary);
}

char** load_vocabulary(char *filename, int* num_words){
    char** out = NULL;

    FILE *infile;
    infile = fopen(filename, "r");
    if (infile == NULL){
        printf("Unable to open file %s for reading\n", filename);
        exit(1);
    }

    char buffer[1024];
    int count = 0;
    out = (char **) malloc(sizeof(char *));

    
    while (fgets(buffer, 1024, infile) != NULL){
        char* word = (char *)malloc(strlen(buffer)+1); // for "\0"
        if (word == NULL){
            printf("Unable to allocate memory to word\n");
            exit(1);
        }
        strcpy(word, buffer);
        
        if (word[strlen(word)-1] == '\n'){
            word[strlen(word)-1] = '\0';
        }

        count ++;
        out = (char **)realloc(out, count* sizeof(char*));
        out[count-1] = word;
    }



    *num_words = count;
    printf("%d", count);
    fclose(infile);
    return out;
}



int main(int argc, char* argv[]){
    int index_word;
    List a = newList();
    char **vocabulary;
    int n;


// check command line for correct number of arguments
    if (argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // load the vocabulary list and update the number of words.
    vocabulary = load_vocabulary(argv[1], &n);

    // char** sub = calloc(n, sizeof(char*)); // create the empty sub array
    index_word = 0;
    prepend(a, index_word);
    char* s1;
    char* s2;
    bool inserted;
    

    for (index_word = 1; index_word < n; index_word++){   // for loop to go over the vocabulary
        moveFront(a);
        s1 = (vocabulary[index_word]);  // the word to insert
        
        inserted = false;

        for (int move = 0; move < index_word; move++ ){  // another for loop to move the cursor and insertBefore()

            s2 = vocabulary[ (get(a)) ]; // the cursor word
            int result = strcmp(s1, s2);

            if (result <= 0){
                insertBefore(a, index_word);
                inserted = true;
                break;
            }
            moveNext(a);
        }

        if (!inserted){
            append(a, index_word);
        }

    }

    // open the file for writing
    FILE *out;
    out = fopen(argv[2], "w");
    if (out == NULL){
        printf("Unable to open file %s for writing\n", argv[2]);
        free_vocabulary(vocabulary, n);
        freeList(&a);
        exit(1);
    }

    if (n==0){
        free_vocabulary(vocabulary, n);
        freeList(&a); 
        fclose(out);
        return 0;
    }
    
    for(moveFront(a); index(a) >= 0; moveNext(a)){
        fprintf(out, "%s\n", vocabulary[get(a)]);
    }


    // close the out file
    fclose(out);

    free_vocabulary(vocabulary, n);
    freeList(&a);  
    return 0;
}