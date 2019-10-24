
We'll take a step back... and to the side:
- what do we know about Linked list? Can we implement one that is cyclic - so that `node->next` never ends?
- what do we know about Queue and can we implement a cyclic one - one that reuses its freed up space?
- let's try implementing both with some testing (we'll make use of [a "framework"](http://www.url.com) )


Some simple problems:
- Linked List - we can create an extension of the our LList class
    - middleElementOfLList - given a LLinked list, find its middle element. This can be achieve with one pass through the list ( O(1*n) )
    - reverseLinkedList - given a LLinked list, reverse its elements
    - hasCycle - given a LList, find if there's a cycle
- Queue
    - isQueueMonotonous - the queue is in its original state in the end


For those that doesn't have any struggle with the above, continue our *Spotify* implementation:
- Add play previous song to our "Player"
