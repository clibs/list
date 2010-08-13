
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#define test(fn) \
  puts("... " # fn); \
  fn();

void
testListNodeInitialization() {
  char *val = "some value";
  ListNode *node = ListNode_new(val);
  assert(node->val == val);
}

int
main(int argc, const char **argv){
  test(testListNodeInitialization);
  puts("... done");
  return 0;
}