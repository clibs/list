
//
// list.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include <stdlib.h>
#include "list.h"

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