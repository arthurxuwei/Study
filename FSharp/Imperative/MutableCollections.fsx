//List<T>
//LinkedList<T>
//HashSet<T> Dictionary<T,T>
(*
The major difference between the collections built into the .NET BCL and their F# analogs is, of course, mutability. 
The mutable nature of BCL collections dramatically affects their implementation and time-complexity:

.NET Data Structure	Insert	Remove	Lookup	F# Data Structure	Insert	Remove	Lookup
List	O(1) / O(n)*	O(n)	O(1) (by index) / O(n) (linear)	No built-in equivalent
LinkedList	O(1)	O(1)	O(n)	No built-in equivalent
Stack	O(1)	O(1)	O(n)	List	O(1)	n/a	O(n)
Queue	O(1)	O(1)	O(n)	No built-in equivalent
HashSet	O(1) / O(n)*	O(1)	O(1)	Set	O(log n)	O(log n)	O(log n)
Dictionary	O(1) / O(n)*	O(1)	O(1)	Map	O(log n)	O(log n)	O(log n)
* These classes are built on top of internal arrays. They may take a performance hit as the internal arrays are periodically resized when adding items.
Note: the Big-O notation above refers to the time-complexity of the insert/remove/retrieve operations relative to the number of items in the data structure, not the relative amount of time required to evaluate the operations relative to other data structures. For example, accessing arrays by index vs. accessing dictionaries by key have the same time complexity, O(1), but the operations do not necessarily occur in the same amount of time.
*)