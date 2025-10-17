/**
 * file name: concordance.c
 * Concordance generator using BST
 * @author: Munkh-Orgil Jargalsaikhan
 */

 #define _DEFAULT_SOURCE
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #include "bst.h"

 int main(int argc, char *argv[]) {
    (void)argv;
    if (argc != 1){
        fprintf(stderr, "usage: concordance\n");
        return EXIT_FAILURE;
    }

    bstnode_t *root = NULL;
    char *line = NULL;
    size_t len = 0;
    int lineno = 0;

    while (getline(&line, &len, stdin) >= 0){
        lineno++;
        char *p = line;
        while (*p) {
            while (*p && !isalnum(*p) && *p != '\'' && *p != '-' && *p != '_') p++; 
            if (!*p) break;
            char *start = p;
            while (*p && (isalnum(*p) || *p == '\'' || *p == '-' || *p == '_')) p++;
            char saved = *p;
            *p = '\0';
            bst_insert(&root, start, lineno);
            *p = saved;
        }
    }

    free(line);
    if(root == NULL){
        fprintf(stderr, "concordance: no words in the input\n");
        return EXIT_FAILURE;
    }  

    bst_traverse(root);
    bst_cleanup(root);

    return EXIT_SUCCESS;
 }