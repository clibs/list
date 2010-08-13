
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#define test(fn) \
  puts("... " # fn); \
  fn();

void
testListInitialization() {
  List *list = List_new();
}

int
main(int argc, const char **argv){
  test(testListInitialization);
  puts("... done");
  return 0;
}