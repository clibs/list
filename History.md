
0.0.8 / 2015-01-30
==================

  * fix `list_at` unsigned compare error (bolasblack, #13)
  * travis: Fail the build if any memory is leaked
  * travis: Update before installing deps
  * test: Fix memory leaks

0.0.7 / 2014-06-02
==================

 * ci: Remove benchmarks
 * add travis
 * test: Fix 'unused parameter' warning
 * readme: Update benchmarks
 * benchmark: Fix 'unused parameter' warning
 * benchmark: Use clibs/bench for CPU time
 * readme: Correct types
 * readme: Add syntax highlighting
 * iterator: set to `NULL` after freeing

0.0.6 / 2014-05-06
==================

 * list.h: Fix header guards
 * Add “list” prefix to sources

0.0.5 / 2013-10-20 
==================

 * add package.json
 * fix free in link_remove(). Closes #3

0.0.4 / 2011-04-15 
==================

  * pop -> rpop
  * shift -> lpop
  * push -> rpush
  * unshift -> lpush

0.0.3 / 2010-11-27 
==================

  * Added `make install`
  * Added `list_shift()`
  * Added `list_pop()`
  * Lowercased function names and typedefs
  * Wrap with extern "C" when \_\_cplusplus
  * Installing `list.h`

0.0.2 / 2010-08-21 
==================

  * Added `ListNode *List_at(List *self, int index)`
  * Added `void List_remove(List *self, ListNode *node)`
  * Added `make liblist.a`

0.0.1 / 2010-08-13 
==================

  * Initial release
