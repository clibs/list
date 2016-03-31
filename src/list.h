
//
// list.h
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

// Library version

#define LIST_VERSION "0.0.5"

// Memory management macros

#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
#endif

#ifndef LIST_FREE
#define LIST_FREE free
#endif

/*
 * tlist iterator direction.
 */

typedef enum {
    LIST_HEAD
  , LIST_TAIL
} tlist_direction;

/*
 * tlist node struct.
 */

typedef struct list_node {
  struct list_node *prev;
  struct list_node *next;
  void *val;
} tlist_node;

/*
 * tlist struct.
 */

typedef struct {
  tlist_node *head;
  tlist_node *tail;
  unsigned int len;
  void (*free)(void *val);
  int (*match)(void *a, void *b);
} tlist;

/*
 * tlist iterator struct.
 */

typedef struct {
  tlist_node *next;
  tlist_direction direction;
} tlist_iterator;

// Node prototypes.

tlist_node *
list_node_new(void *val);

// list_t prototypes.

tlist *
list_new();

tlist_node *
list_rpush(tlist *self, tlist_node *node);

tlist_node *
list_lpush(tlist *self, tlist_node *node);

tlist_node *
list_find(tlist *self, void *val);

tlist_node *
list_at(tlist *self, int index);

tlist_node *
list_rpop(tlist *self);

tlist_node *
list_lpop(tlist *self);

void
list_remove(tlist *self, tlist_node *node);

void
list_destroy(tlist *self);

// tlist iterator prototypes.

tlist_iterator *
list_iterator_new(tlist *list, tlist_direction direction);

tlist_iterator *
list_iterator_new_from_node(tlist_node *node, tlist_direction direction);

tlist_node *
list_iterator_next(tlist_iterator *self);

void
list_iterator_destroy(tlist_iterator *self);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
