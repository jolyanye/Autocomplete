#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");

    lowest_match(terms, nterms, "Tor");
    highest_match(terms, nterms, "Tor");
    
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");

    printf("Autocomplete results:\n");
    for (int i = 0; i < n_answer; i++) {
        printf("%s\n", answer[i].term);
    }

    // Free memory allocated for terms
    free(terms);
    free(answer);

    return 0;
}
