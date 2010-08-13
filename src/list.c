
//
// list.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include <stdlib.h>
#include "list.h"

/*
 * Allocates a new ListNode. NULL on failure.
 */

ListNode *
ListNode_new(void *val) {
  ListNode *self;
  if (!(self = LIST_MALLOC(sizeof(ListNode))))
    return NULL;
  self->prev = NULL;
  self->next = NULL;
  self->val = val;
  return self;
}

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
    LIST_FREE(curr);
    curr = next;
  }
  LIST_FREE(self);
}

/*
 * Append the given node to the list. NULL on failure.
 */

List *
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
  return self;
}

/*
 * Prepend the given node to the list. NULL on failure.
 */

List *
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
  return self;
}