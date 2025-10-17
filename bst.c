/**
*file name: bst.c
*Implementation of the binary search tree functions for the concordance
*@author: Munkh-Orgil Jargalsaikhan
*/

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "bst.h"

#define INITIAL_REFLEN 4u

static int add_ref(bstnode_t *node, unsigned int line) {
    if (node == NULL) return -1;

    if (node->freq >= node->reflen) {
        unsigned int newlen = node->reflen * 2u;
        if (newlen == 0) newlen = INITIAL_REFLEN;
        unsigned int *tmp = realloc(node->refs, newlen * sizeof(unsigned int));
        if (tmp == NULL) return -1;
        node->refs = tmp;
        node->reflen = newlen;
    }
    node->refs[node->freq] = line;
    node->freq += 1;
    return 0;
}

void bst_insert(bstnode_t **bp, const char *word, int line){
    if(*bp == NULL){
        bstnode_t *node = malloc(sizeof(bstnode_t));
        if (node == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        node->word = strdup(word);
        node->freq = 1;
        node->reflen = 5;
        node->refs = malloc(node->reflen * sizeof(unsigned int));
        node->refs[0] = line;
        node->left = node->right = NULL;
        *bp = node;
        return;
    } 
    int cmp = strcasecmp(word, (*bp)->word);

    if (cmp == 0){
        add_ref(*bp, line);
    } else if (cmp < 0) {
        bst_insert(&((*bp)->left),word, line);
    } else {
        bst_insert(&((*bp)->right), word, line);
    }
}

void bst_traverse(const bstnode_t *root) {
    if (root == NULL) return;

    bst_traverse(root->left);

    printf("%s (%u): ", root->word, root->freq);
    for (unsigned int i = 0; i < root->freq; i++) {
        printf("%u", root->refs[i]);
        if (i + 1 < root->freq) {
            printf(", ");
        }
    }
    printf("\n");

    bst_traverse(root->right);
}


void bst_cleanup(bstnode_t *root){
    if(root == NULL) return;
    
    bst_cleanup(root->left);
    bst_cleanup(root->right);
    
    free(root->word);
    free(root->refs);
    free(root);
}


