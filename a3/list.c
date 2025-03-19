#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "emalloc.h"
#include "list.h"

/**
 * Function:  new_node
 * -------------------
 * @brief  Dynamically allocates memory for a new node.
 */
node_t *new_node(char *val) {
    assert(val != NULL);
    node_t *temp = (node_t *)emalloc(sizeof(node_t));
    temp->word = strdup(val);
    if (temp->word == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    temp->next = NULL;
    return temp;
}

/**
 * Function:  add_front
 * --------------------
 * @brief  Adds a node at the front of the list.
 */
node_t *add_front(node_t *list, node_t *new) {
    new->next = list;
    return new;
}

/**
 * Function:  add_end
 * ------------------
 * @brief  Adds a node at the end of the list.
 */
node_t *add_end(node_t *list, node_t *new) {
    if (list == NULL) {
        return new;
    }
    
    node_t *curr = list;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new;
    
    return list;
}

/**
 * Function:  add_inorder
 * ----------------------
 * @brief  Adds a new node in sorted order.
 */
node_t *add_inorder(node_t *list, node_t *new) {
    node_t *prev = NULL, *curr = list;

    while (curr != NULL && strcmp(new->word, curr->word) > 0) {
        prev = curr;
        curr = curr->next;
    }

    new->next = curr;

    if (prev == NULL) {
        return new;
    } else {
        prev->next = new;
        return list;
    }
}

/**
 * Function: free_list
 * -------------------
 * @brief Frees all nodes in the linked list.
 */
void free_list(node_t *list) {
    node_t *temp;
    while (list != NULL) {
        temp = list->next;
        free(list->word);
        free(list);
        list = temp;
    }
}
