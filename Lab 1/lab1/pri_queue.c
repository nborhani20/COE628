#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Nousha Borhani
 */
void PQ_insert(int priority, char * data) {
Node_ptr_t new_node = (Node_ptr_t)malloc(sizeof(Node_t));
    if (new_node == NULL) return;

    new_node->priority = priority;
    new_node->data = data;
    new_node->next = NULL;

        /* If the list is empty, or the new node has a higher priority than the current head*/
    if (head == NULL || priority > head->priority) {
        /*point the node to the head*/
        new_node->next = head;
        /*make the new head equal to the new node*/
        head = new_node;
        return;
    }

    /* If the list is not empty and the new node is not the new head
     * start from head of linked list*/
    Node_ptr_t curr = head;
    /*advance through the list while there exists a next node 
     * & priority of the  next node is greater than the node being inserted*/
    while (curr->next != NULL && curr->next->priority >= priority) {
        curr = curr->next;
    }
    /*Once position is found, link the new node to the list*/
    new_node->next = curr->next;
    /*link the current node to the new node*/
    curr->next = new_node;
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    /*If list is empty*/
 if (head == NULL)
        return NULL;
/*save the current head*/
    Node_ptr_t removed = head;
    /*remove the current head and move the head pointer the next node in the list*/
    head = head->next;
    removed->next = NULL;

    return removed;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


