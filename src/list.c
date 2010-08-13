
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
  if ((self = LIST_MALLOC(sizeof(ListNode))) == NULL)
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
  if ((self = LIST_MALLOC(sizeof(List))) == NULL)
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->len = 0;
  return self;
}