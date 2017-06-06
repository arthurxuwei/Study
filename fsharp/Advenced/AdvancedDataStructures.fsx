//Stack

(*
type 'a stack =
    | EmptyStack
    | StackNode of 'a * 'a stack
*)

//Queue

(*
type Queue<'a>(item : stack<'a>) =
    member this.hd
        with get() = Stack.hd (Stack.rev item)
 
    member this.tl
        with get() = Queue(item |> Stack.rev |> Stack.tl |> Stack.rev)
 
    member this.enqueue(x) = Queue(StackNode(x, item))
 
    override this.ToString() = sprintf "%A" item
 
    static member empty = Queue<'a>(Stack.empty)
*)

//Binary Search Trees
(*
type 'a tree =
    | EmptyTree
    | TreeNode of 'a * 'a tree * 'a tree
*)
//Red Black Trees

//AVL Trees

//Heaps

//Lazy Data Structures
type 'a lazyStack =
    | Node of Lazy<'a * 'a lazyStack>
    | EmptyStack


