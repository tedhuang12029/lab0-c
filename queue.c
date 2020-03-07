#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q) {
        list_ele_t *curr = q->head;
        while (curr) {
            list_ele_t *tmp = curr;
            curr = curr->next;
            free(tmp->value);
            free(tmp);
        }
    }
    free(q);
}
/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    int sSize = strlen(s) + 1;
    newh->value = malloc(sSize);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strlcpy(newh->value, s, sSize);
    newh->next = q->head;
    if (!q->head)
        q->tail = newh;
    q->head = newh;
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return NULL;
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    int sSize = strlen(s) + 1;
    newt->value = malloc(sSize);
    if (!newt->value) {
        free(newt);
        return NULL;
    }
    strlcpy(newt->value, s, sSize);
    newt->next = NULL;
    q->tail->next = newt;
    q->tail = newt;
    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if ((q != NULL) && (q->size != 0)) {
        list_ele_t *tmp = q->head;
        if (sp) {
            strlcpy(sp, tmp->value, bufsize);
        }
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
        q->size -= 1;
    } else {
        return false;
    }
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return false;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if ((q != 0) && (q->size != 0)) {
        list_ele_t *prev = NULL;
        list_ele_t *tmp;
        q->tail = q->head;
        while (q->head->next) {
            tmp = q->head->next;
            q->head->next = prev;
            prev = q->head;
            q->head = tmp;
        }
        q->head->next = prev;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

// void q_sort(queue_t *q)
// {
//     /* TODO: You need to write the code for this function */
//     /* TODO: Remove the above comment when you are about to implement. */
//     // bubble sort
//     if ((q != 0) && (q->size != 0)) {
//         list_ele_t *tmp, *curr, *prev;

//         // get Linked list size first
//         for (int i = q->size; i > 0; i--) {
//             curr = q->head;
//             prev = q->head;
//             for (int j = 0; j < i - 1 && curr->next; j++) {
//                 // Compares two elements, and swaps if current is bigger than
//                 // next
//                 if (strcasecmp(curr->value,curr->next->value)>0) {
//                     if (curr->next == q->tail)
//                         q->tail = curr;
//                     tmp = curr->next;
//                     curr->next = tmp->next;
//                     tmp->next = curr;
//                     // In linked list, swap has two case. In head or not.

//                     if (curr == q->head) {
//                         q->head = tmp;
//                         prev = tmp;
//                     } else {
//                         prev->next = tmp;
//                         prev = prev->next;
//                     }
//                 } else {
//                     curr = curr->next;
//                     if (j != 0)
//                         prev = prev->next;
//                 }
//             }
//         }
//     }
// }

void q_sort(queue_t *q)
{
    if ((q != 0) && (q->size != 0))
        q->head = sort(q->head);
}
list_ele_t *sort(list_ele_t *start)
{
    if (!start || !start->next)
        return start;
    list_ele_t *left = start;
    list_ele_t *right = left->next;
    left->next = NULL;
    left = sort(left);
    right = sort(right);

    for (list_ele_t *merge = NULL; left || right;) {
        if (!right || (left && (strcasecmp(right->value, left->value) > 0))) {
            if (!merge) {
                start = merge = left;
            } else {
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
    }
    return start;
}
