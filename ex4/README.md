
We'll take a step back... and to the side:
- what do we know about Linked list? Can we implement one that is cyclic - so that `node->next` never ends?
- what do we know about Queue and can we implement a cyclic one - one that reuses its freed up space?
- let's try implementing both with some testing (we'll make use of [a "framework"](https://github.com/danailbd/sdp_2019/blob/master/lib/testing-framework.h) )


Some simple problems:
### Queue
#### isQueueMonotonous
##### Requirements
- the queue is in its original state in the end

##### Exapmle
A monotonous queue looks like:
[1, 2, 3, 5]
or
[5, 3, 2, 1]
And a non-monotonous queue looks like:
[1, 2, 4, **2**]
[1, 10, **2, 15**]

### Linked List - we can create an extension of the our LList class
#### middleElementOfLList
Given a LLinked list, find its middle element. This can be achieve with one pass through the list ( O(1*n) )
#### reverseLinkedList
Given a LLinked list, reverse its elements
#### hasCycle
Given a Linked list, find if there's a cycle. Here we use the most minimalistic idea for a Linked list that is simply represented as a linked sequence of objects and has nothing to do with a class or interface


For those that doesn't struggle with the above, continue our *Spotify* implementation:
- Add play previous song to our "Player"
