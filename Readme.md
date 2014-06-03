
# list

 C doubly linked list implementation.

## API

 Below is the public api currently provided by "list".

## list_t *list_new();

 Allocate and initialize a `list`.
 
    list_t *mylist = list_new();

## list_node_t \*list_node_new(void *val)

 Allocate and initialize a `list_node_t` with the given _val_.

```c
list_node_t *node = list_node_new("my value");
node->val; // "my value"
```

## list_node_t \* list_rpush(list_t \*self, list_node_t *node)

 Append _node_ to _self_, returning _node_.
 
```c
list_rpush(list, list_node_new("value"));
list->tail->val; // "value"
```

## list_node_t \* list_rpop(list_t \*self)

  Return / detach node from the end of the list, or __NULL__.

```c
list_node_t *last = list_pop(names);
```

##  list_node_t \*list_lpush(list_t \*self, list_node_t *node)

 Prepend _node_ to _self_, returning _node_.

```c
list_lpush(list, list_node_new("value"));
list->head->val; // "value"
```

## list_node_t \*list_find(list_t \*self, void *val)

 Return the `list_node_t` containing _val_ or __NULL__.

```c
list_node_t *node = list_find(list, "some value");
```

## list_node_t \*list_at(list_t *self, int index)

 Return the `list_node_t` at the given _index_, where _index_
 may also be a negative integer indicating an index from the
 list _tail_.

```c
list_at(list, 0);  // first
list_at(list, 1);  // second
list_at(list, -1); // last
list_at(list, -3); // third last
```

## void list_remove(list_t \*self, list_node_t *node)

  Remove _node_ from the list, freeing it and it's value.

```c
list_remove(list, node);
```

## void list_destroy(list_t *self)

  Free the list and all nodes.

```c
list_destroy(list);
```

## list_iterator_t \*list_iterator_new(list_t *list, list_direction_t direction)

  Allocate and initialize a `list_iterator_t` with the given _direction_,
  where _direction_ may be __LIST_HEAD__ or __LIST_TAIL__.

```c
list_node_t *node;
list_iterator_t *it = list_iterator_new(list, LIST_HEAD);
while ((node = list_iterator_next(it))) {
  puts(node->val);
}
```  

## list_node_t \*list_iterator_next(list_iterator_t *self)

  Return the next `list_node_t` or __NULL__.

## void list_iterator_destroy(list_iterator_t *self);

  Free the iterator only.

```c
list_iterator_destroy(it);
```

## Examples

list iteration:

```c
list_t *langs = list_new();

list_node_t *c = list_rpush(langs, list_node_new("c"));
list_node_t *js = list_rpush(langs, list_node_new("js"));
list_node_t *ruby = list_rpush(langs, list_node_new("ruby"));

list_node_t *node;
list_iterator_t *it = list_iterator_new(langs, LIST_HEAD);
while ((node = list_iterator_next(it))) {
  puts(node->val);
}

list_iterator_destroy(it);
list_destroy(langs);
```

stdout:

    c
    js
    ruby

## Benchmarks

    $ make benchmark
    
     10,000,000 nodes
    
                  lpush: 0.5000s
                  rpush: 0.5000s
                   lpop: 0.0312s
                   rpop: 0.0312s
       find (last node): 0.0312s
                iterate: 0.0625s
            at(100,000): 0.0000s
          at(1,000,000): 0.0000s
           at(-100,000): 0.0000s



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
