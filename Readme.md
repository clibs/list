
# List

 C doubly linked list implementation.

## API

### List *List_new();

 Allocate and initialize a `List`.

### ListNode \*ListNode_new(void *val)

 Allocate and initialize a `ListNode` with the given _val_.

### List_push(List \*self, ListNode *node)

 Append _node_ to _self_, returning _node_.

###  ListNode \*List_unshift(List \*self, ListNode *node)

 Prepend _node_ to _self_, returning _node_.

### ListNode \*List_find(List \*self, void *val)

 Return the `ListNode` containing _val_ or __NULL__.

### ListNode \*List_at(List *self, int index)

 Return the `ListNode` at the given _index_, where _index_
 may also be a negative integer indicating an index from the
 list _tail_.

    List_at(list, 0);  // first
    List_at(list, 1);  // second
    List_at(list, -1); // last
    List_at(list, -3); // third last

### void List_remove(List \*self, ListNode *node)

  Remove _node_ from the list.

### void List_destroy(List *self)

  Free the list and all nodes.

### ListIterator \*ListIterator_new(List *list, ListDirection direction)

  Allocate and initialize a `ListIterator` with the given _direction_,
  where _direction_ may be __LIST_HEAD__ or __LIST_TAIL__.

### ListNode \*ListIterator_next(ListIterator *self)

  Return the next `ListNode` or __NULL__.

### void ListIterator_destroy(ListIterator *self);

  Free the iterator only.

## Examples

List iteration:

    List *langs = List_new();
    
    ListNode *c = List_push(langs, ListNode_new("c"));
    ListNode *js = List_push(langs, ListNode_new("js"));
    ListNode *ruby = List_push(langs, ListNode_new("ruby"));
    
    ListIterator *it = ListIterator_new(langs, LIST_HEAD);
    ListNode *node;
    while ((node = ListIterator_next(it))) {
    	puts(node->val);
    }
    
    ListIterator_destroy(it);
    List_destroy(langs);

stdout:

    c
    js
    ruby

## Benchmarks

    $ make benchmark

    10,000,000 nodes

                pushed: 0.5934s
             unshifted: 0.6018s
      find (last node): 0.0546s
               iterate: 0.0717s
           at(100,000): 0.0006s
         at(1,000,000): 0.0056s
          at(-100,000): 0.0006s



## Testing

    $ make test

## License 

(The MIT License)

Copyright (c) 2009-2010 TJ Holowaychuk &lt;tj@vision-media.ca&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.