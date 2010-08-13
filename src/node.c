
//
// node.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

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