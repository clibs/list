
#include <stdio.h>
#include <time.h>
#include "src/list.h"

static void
bm(char *label, void (*fn)()) {
  printf(" %25s", label);
  fflush(stdout);
  fn();
}

static clock_t startTime;

static void
start() {
  startTime = clock();
}

static void
stop() {
  float duration = (float) (clock() - startTime) / CLOCKS_PER_SEC;
  printf(": \x1b[32m%.4f\x1b[0ms\n", duration);
}

static void
bm_push() {
  start();
  int n = 5000000;
  List *list = List_new();
  while (n--) {
    List_push(list, ListNode_new("foo"));
  }
  stop();
}

static void
bm_unshift() {
  start();
  int n = 5000000;
  List *list = List_new();
  while (n--) {
    List_unshift(list, ListNode_new("foo"));
  }
  stop();
}

int
main(int argc, const char **argv){
  puts("");
  bm("5,000,000 nodes pushed", bm_push);
  bm("5,000,000 nodes unshifted", bm_unshift);  
  puts("");
  return 0;
}