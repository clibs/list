
//
// node.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "list.h"

/*
 * Allocates a new tlist_node. NULL on failure.
 */

tlist_node *
list_node_new(void *val) {
  tlist_node *self;
  if (!(self = LIST_MALLOC(sizeof *self)))
    return NULL;
  self->prev = NULL;
  self->next = NULL;
  self->val = val;
  return self;
}
