
//
// list.h
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

// Library version

#define LIST_VERSION "0.0.1"

// Memory management macros

#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
#endif

#ifndef LIST_FREE
#define LIST_FREE free
#endif

/*
 * List iterator direction.
 */

typedef enum {
    LIST_HEAD
  , LIST_TAIL
} ListDirection;

/*
 * List node struct.
 */

typedef struct ListNode {
  struct ListNode *prev;
  struct ListNode *next;
  void *val;
} ListNode;

/*
 * List struct.
 */

typedef struct {
  ListNode *head;
  ListNode *tail;
  unsigned int len;
  void (*free)(void *val);
  int (*match)(void *a, void *b);
} List;

/*
 * List iterator struct.
 */

typedef struct {
  ListNode *next;
  ListDirection direction;
} ListIterator;

// Node prototypes.

ListNode *ListNode_new(void *val);

// List prototypes.

List *List_new();
ListNode *List_push(List *self, ListNode *node);
ListNode *List_unshift(List *self, ListNode *node);
ListNode *List_find(List *self, void *val);
ListNode *List_at(List *self, int index);
void List_remove(List *self, ListNode *node);
void List_destroy(List *self);

// List iterator prototypes.

ListIterator *ListIterator_new(List *list, ListDirection direction);
ListNode *ListIterator_next(ListIterator *self);
void ListIterator_destroy(ListIterator *self);

#endif /* __LIST_H__ */