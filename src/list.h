
//
// list.h
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef __LIST_H__
#define __LIST_H__

#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
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
} List;

/*
 * Node prototypes.
 */

ListNode *ListNode_new(void *val);
ListNode *ListNode_destroy(ListNode *self);

/*
 * List prototypes.
 */

List *List_new();
List *List_push(List *self, ListNode *node);
List *List_unshift(List *self, ListNode *node);
List *List_destroy(List *self);

#endif /* __LIST_H__ */