
//
// list.h
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef __LIST_H__
#define __LIST_H__

// Memory management macros

#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
#endif

#ifndef LIST_FREE
#define LIST_FREE free
#endif

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
} List;

// Node prototypes.

ListNode *ListNode_new(void *val);

// List prototypes.

List *List_new();
List *List_push(List *self, ListNode *node);
List *List_unshift(List *self, ListNode *node);
void List_destroy(List *self);

#endif /* __LIST_H__ */