#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"

int compare_terms(const void *a, const void *b) {
    const struct term *term1 = (const struct term *)a;
    const struct term *term2 = (const struct term *)b;
    return strcmp(term1->term, term2->term);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename) {
    /*
    The function allocates memory for all the terms in the file and stores a pointer to the block in
    *terms. The function stores the number of terms in *pnterms. The function reads in all the terms
    from filename, and places them in the block pointed to by *terms.
    */

    // read in all terms from file name, place into terms 
    char line[200]; 
    FILE *fp = fopen(filename, "r"); 

    // store number of terms in *pnterms (first line in the file)
    *pnterms = atoi(fgets(line, sizeof(line), fp));

    // allocate memory for all the terms in the file
    *terms = (term *)malloc(sizeof(term) * (*pnterms));

    for (int i = 0; i < *pnterms; i++) {
        fgets(line, sizeof(line), fp);
        double weight = 0;
        char term[200];
        sscanf(line, "%lf %[^\n]", &weight, term);
        strcpy((*terms)[i].term, term);
        (*terms)[i].weight = weight;
    }

    qsort(*terms, *pnterms, sizeof(term), compare_terms);

    fclose(fp);
}


int lowest_match(struct term *terms, int nterms, char *substr) {
    /*
    The function returns the index in terms of the first term in lexicographic ordering that matches
    the string substr.
    */

    int left = 0;
    int right = nterms - 1;
    int index = -1;

    while (left <= right) {
        int mid = left + (right - left)/2;
        int compare = strncmp(terms[mid].term, substr, strlen(substr));

        if (compare < 0) {
            left = mid + 1;
        }
        else {
            index = mid;
            right = mid - 1;
        }
    }

    return index;
}


int highest_match(struct term *terms, int nterms, char *substr) {
    /*
    The function returns the index in terms of the last term in lexicographic order that matches
    the string substr.
    */

    int left = 0;
    int right = nterms - 1;
    int index = -1;

    while (left <= right) {
        int mid = left + (right - left)/2;
        int compare = strncmp(terms[mid].term, substr, strlen(substr));

        if (compare <= 0) {
            index = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return index;
}


int compare_weights(const void *a, const void *b) {
    const struct term *term1 = (const struct term *)a;
    const struct term *term2 = (const struct term *)b;

    // Compare weights in non-increasing order
    if (term1->weight < term2->weight) {
        return 1;
    } else if (term1->weight > term2->weight) {
        return -1;
    }
    return 0;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr) {
    /*
    The function takes terms (assume it is sorted lexicographically in increasing order), the number
    of terms nterms, and the query string substr, and places the answers in answer, with *n_answer
    being the number of answers. The answers should be sorted by weight in non-increasing order.
    */

    // define range of terms matching substring
    int start = lowest_match(terms, nterms, substr);
    int end = highest_match(terms, nterms, substr);

    // # of matching terms
    *n_answer = end - start + 1;

    // allocate memory to store every possible answer term
    *answer = (term *)malloc(sizeof(term) * (*n_answer));

    // copy matching terms into malloc block
    for (int i = start; i <= end; i++) {
        (*answer)[i - start] = terms[i];
    }

    qsort(*answer, *n_answer, sizeof(term), compare_weights);
}












/* int i = 0;
    int word_found = 0;
    int index_first_word = 0;
    int last_letter = 0;

    for (; i < strlen(str); i++) {
        if (!((str[i] >= '0' && str[i] <= '9') || str[i] == ' ')) {
            word_found = 1;
            index_first_word = i;
        } 
    }

    printf("%dyooo\n", i);

    //printf("%d\n", (strlen(str) - i) * sizeof(char));
    *filtered = (char *)malloc((strlen(str) - i) * sizeof(char) + 1);

    for (int s = i - 1; s <= strlen(str); s++) {
        (*filtered)[s - i] = str[s - 1];
    }

    (*filtered)[strlen(str)] = '\0';

    // printf("hello"); */


/* Strategy for Term Collection 
1. Cut leading and trailing. 
    - Get index where the terms first start and where the terms end
*/


/* void filter_string(const char *str, char **filtered) {
    // Filter out the numbers in the string and get only the word 

    // create memory block to store characters in one line
    *filtered = (char *)malloc(sizeof(char) * (strlen(str) + 1));

    int index = 0;

    // Iterate through the string 
    for (int i = 0; str[i] != '\0'; i++) {
        // If it is a space or number, it is ignored 
        if (!(((str[i] >= '0') && (str[i] <= '9')) || (str[i] == ' '))) {
            (*filtered)[index++] = str[i];
        }
    }

    (*filtered)[index] = '\0';
} */


    /*
    // iterate through every line and filters string
    for (int i = 1; i < *pnterms; i++) {
        fgets(line, sizeof(line), fp);

        // Allocate memory block to store characters in one line
        char *filtered = NULL;

        filter_string(line, &filtered);
        
        // Copy filtered string into term
        strcpy((*terms)[i].term, filtered);
        free(filtered);
    }
    */