
//
// list.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "list.h"

/*
 * Allocate a new List. NULL on failure.
 */

List *
List_new() {
  List *self;
  if (!(self = LIST_MALLOC(sizeof(List))))
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->free = NULL;
  self->match = NULL;
  self->len = 0;
  return self;
}

/*
 * Free the list.
 */

void
List_destroy(List *self) {
  unsigned int len = self->len;
  ListNode *next;
  ListNode *curr = self->head;
  while (len--) {
    next = curr->next;
    if (self->free) self->free(curr->val);
    LIST_FREE(curr);
    curr = next;
  }
  LIST_FREE(self);
}

/*
 * Append the given node to the list
 * and return the node, NULL on failure.
 */

ListNode *
List_push(List *self, ListNode *node) {
  if (!node) return NULL;
  if (self->len) {
    node->prev = self->tail;
    node->next = NULL;
    self->tail->next = node;
    self->tail = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }
  ++self->len;
  return node;
}

/*
 * Prepend the given node to the list 
 * and return the node, NULL on failure.
 */

ListNode *
List_unshift(List *self, ListNode *node) {
  if (!node) return NULL;
  if (self->len) {
    node->next = self->head;
    node->prev = NULL;
    self->head->prev = node;
    self->head = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }
  ++self->len;
  return node;
}

ListNode *
List_find(List *self, void *val) {
  ListIterator *it = ListIterator_new(self, LIST_HEAD);
  ListNode *node;
  while (node = ListIterator_next(it)) {
    if (self->match) {
      if (self->match(val, node->val)) {
        ListIterator_destroy(it);
        return node;
      }
    } else {
      if (val == node->val) {
        ListIterator_destroy(it);
        return node;
      }
    }
  }
  ListIterator_destroy(it);
  return NULL;
}