(** Lists *)
(* Read this along with the "Lists.v". *)

module Lists

(* A "natprod" consists a pair of "nat", as in the following code: *)
// type natprod =
//   | Pair of Basics.Playground1.nat * Basics.Playground1.nat

(* However, there are some inconvience with this code:
   1. this code is dependent on the "Basics.fs" file, that
      is, the code now should compile with:
        $ fsc Basics.fs Lists.fs
   2. writing "nat" must be in its fully qualified form
      (though you can open the "Basics" module, however, opening
      a module is not a great software engineering idea).
   So, instead of using "nat", I use "int", which is F#'s
   default type. *)

type intprod =
  | Pair of int * int

printfn "%A" (Pair (3, 5))

(* The standard projection function: *)
let fst (p: intprod): int =
  match p with
    | Pair (x, y) -> x

let snd (p: intprod): int =
  match p with
    | Pair (x, y) -> y

printfn "%d" (fst (Pair (3, 5)))

(* However, there is another more popular programming idom in F#, which
is called pattern matching in arguments, just as these: *)
let fst' (Pair (x, _)) = x
let snd' (Pair (_, y)) = y

printfn "fst' = %d" (fst' (Pair (3, 5)))

let swap (Pair (x, y)) = Pair (y, x)

(*=================================================*)
(** List of numbers *)
type intlist =
  | Nil
  | Cons of int * intlist

(* Cook a list with 1, 2, and 3, in this order: *)
let mylist = Cons (1, Cons (2, Cons (3, Nil)))

printfn "%A" mylist

(* List data structures are very important in functional
programming community, so the F# programming system has
built-in support for this:
  1. the "Nil" constructor is "[]", and
  2. the "Cons" constructor is "::".
Rewriting "mylist" as follows: *)
let mylist' = 1::2::3::[]

(* Read this to find out more ways to deal with lists:
http://msdn.microsoft.com/zh-cn/library/vstudio/dd233224.aspx
*)

(* In the following, let's forget F#'s built-in lists, but
to use our version of "intlist". *)

(* The repeat function takes a number "n" and a "count" and
returns a list of length "count" where every element is "n". *)
let rec repeat (n: int) (count: int): intlist =
  match count with
    | 0 -> Nil
    | _ -> Cons (n, repeat n (count-1))

(* Advanced materials (you may skip the following
function). For some reason
we don't have time to explain in detail here, this "repeat"
function above is rather slow (why?). If you are interested in
the reason, read this article about tail recursion:

http://baike.baidu.com/view/1439396.htm

So a better way to write repeat is:*)
let rec repeat' (n: int) (count: int) (defaultlist: intlist): intlist =
  match count with
    | 0 -> defaultlist
    | _ -> repeat' n (count-1) (Cons (n, defaultlist))

(* The length function calculates the length of a list.*)
let rec length (l: intlist): int = 
  match l with
    | Nil -> 0
    | Cons (head, tail) -> 1+ (length tail)

(* The app ("append") function concatenates two lists.*)
let rec app (l1: intlist) (l2: intlist): intlist = 
  match l1 with
    | Nil -> l2
    | Cons (x, xs) -> Cons (x, (app xs l2))

printfn "%A" (app (Cons (4, Cons (3, Nil))) (Cons (1, Cons (0, Nil))))

(* The hd function returns the first element (the "head")
of the list, while tail returns everything but the first
element. Of course, the empty list has no first element,
so we must pass a default value to be returned in that case.*)
let hd (defaultt: int) (l: intlist): int =
  match l with
    | Nil -> defaultt
    | Cons (h, t) -> h

let tail (l: intlist): intlist =
  match l with
    | Nil -> Nil 
    | Cons (h, t) -> t

(*=========================================================*)
(** Options *)
type intoption =
  | Some of int
  | None

let rec index (n: int) (l: intlist): intoption =
  match l with
    | Nil -> None
    | Cons (x, xs) ->
      match n with
        | 0 -> Some x
        | _ -> index (n-1) xs

let option_elim (n: int) (o: intoption): int =
  match o with
    | Some n' -> n'
    | None -> n

(*=========================================================*)
(** dictionaries *)
module Dict =
  type dictionary =
    | Empty
    | Record of int * int * dictionary

  let insert (d: dictionary) (k: int) (v: int) =
    Record (k, v, d)

  let rec find (d: dictionary) (k: int): intoption =
    match d with
      | Empty -> None
      | Record (k', v', d') ->
        if k=k'
        then Some v'
        else find d' k
