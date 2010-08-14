
# List

 C doubly linked list implementation.

## API

    ListNode *ListNode_new(void *val);
    
    List *List_new();
    ListNode *List_push(List *self, ListNode *node);
    ListNode *List_unshift(List *self, ListNode *node);
    ListNode *List_find(List *self, void *val);
    void List_destroy(List *self);
    
    ListIterator *ListIterator_new(List *list, ListDirection direction);
    ListNode *ListIterator_next(ListIterator *self);
    void ListIterator_destroy(ListIterator *self);

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
    
	              pushed: 0.5949s
	           unshifted: 0.5977s
	    find (last node): 0.0545s
	             iterate: 0.0558s

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