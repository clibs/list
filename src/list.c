
//
// list.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include <stdlib.h>
#include "list.h"

/*
 * Allocates a new ListNode.
 */

ListNode *
ListNode_new(void *val) {
  ListNode *self;
  if (NULL == (self = LIST_MALLOC(sizeof(ListNode))))
    return NULL;
  self->prev = NULL;
  self->next = NULL;
  self->val = val;
  return self;
}

/*
 * Allocate a new List.
 */

List *
List_new() {
  List *self;
  if (NULL == (self = LIST_MALLOC(sizeof(List))))
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->len = 0;
  return self;
}

List *
List_push(List *self, ListNode *node) {
  if (NULL == node) {
    return NULL;
  } else {
    if (self->len == 0) {
      self->head = self->tail = node;
      node->prev = node->next = NULL;
    } else {
      node->prev = self->tail;
      node->next = NULL;
      self->tail->next = node;
      self->tail = node;
    }
    ++self->len;
  }
  return self;
}