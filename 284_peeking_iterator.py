# https://leetcode.com/problems/peeking-iterator/
# We just need to buffer the current object of the iterator. When peek(), return the buffered object. When next(), return the buffered object, update the buffer to the next object.

# Below is the interface for Iterator, which is already defined for you.
#
# class Iterator(object):
#     def __init__(self, nums):
#         """
#         Initializes an iterator object to the beginning of a list.
#         :type nums: List[int]
#         """
#
#     def hasNext(self):
#         """
#         Returns true if the iteration has more elements.
#         :rtype: bool
#         """
#
#     def next(self):
#         """
#         Returns the next element in the iteration.
#         :rtype: int
#         """

class PeekingIterator(object):
    def __nextItem(self):
        if (self.__itr.hasNext()):
            return self.__itr.next()
        else:
            return None
            
    def __init__(self, iterator):
        """
        Initialize your data structure here.
        :type iterator: Iterator
        """
        self.__itr = iterator
        self.__bufferedItem = self.__nextItem()
        

    def peek(self):
        """
        Returns the next element in the iteration without advancing the iterator.
        :rtype: int
        """
        return self.__bufferedItem
        

    def next(self):
        """
        :rtype: int
        """
        tmp = self.__bufferedItem
        self.__bufferedItem = self.__nextItem()
        return tmp
        

    def hasNext(self):
        """
        :rtype: bool
        """
        return self.__bufferedItem is not None

# Your PeekingIterator object will be instantiated and called as such:
# iter = PeekingIterator(Iterator(nums))
# while iter.hasNext():
#     val = iter.peek()   # Get the next element but not advance the iterator.
#     iter.next()         # Should return the same value as [val].