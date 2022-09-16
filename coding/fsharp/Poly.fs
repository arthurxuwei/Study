module Poly

(* Polymorphic lists *)
type list<'a> =
  | Nil
  | Cons of 'a * list<'a>

(* Type variables are prefixed by a prime ' symbol, and
should be called "alpha". *)
(* In fact, there is an equivalent and traditional way to
write polymorphic types, which uses a prefix version, rather
than postfix: *)
type 'a mylist =
  | MyNil
  | MyCons of 'a * 'a mylist
(* However, in order to be consistent with the Coq, I prefer
to write in the first style. *)

(* One nice aspect about F# polymorphism is that you don't
need to specify the type variable instance when constructing
data, in other words, the type variable application is dumb.
Here is an example, instead of writing: *)
// let mylist = Cons int (4, Cons int (3, Nil int))code shows this: *)
(* we can simply write: *)
let mylist = Cons (4, Cons (3, Nil))

(* this is a very powerful feature of F# called type inference,
read more about type inference here:
http://zh.wikipedia.org/wiki/%E7%B1%BB%E5%9E%8B%E6%8E%A8%E8%AE%BA
*)

(* unit test to make sure our list looks fine: *)
printfn "%A" mylist

(* length function: *)
let rec length (l: list<'a>): int =
  match l with
    | Nil -> 0
    | Cons (_, xs) -> 1 + length xs

printfn "length = %d" (length mylist)

(* append function: *)
let rec app (l1: list<'a>) (l2: list<'a>): list<'a> =
  match l1 with
    | Nil -> l2
    | Cons (x, xs) -> Cons (x, app xs l2)

let rec snoc (l: list<'a>) (v: 'a): list<'a> =
  match l with
    | Nil -> Cons (v, Nil)
    | Cons (x, xs) -> Cons (x, snoc xs v)

let rec rev (l: list<'a>): list<'a> =
  match l with
    | Nil -> Nil
    | Cons (x, xs) -> snoc (rev xs) x

(*==================================================*)
(** Type annotation inference revisited *)
(* In fact, the F#'s Hindley-Milner type inference
engine is so powerful that most type annotations can be
omitted from the code. Here is another version of the
"length" function: *)
let rec length' l =
  match l with
    | Nil -> 0
    | Cons (_, xs) -> 1 + length' xs

(* As the code shows, there is no type annotations at all, however,
it's still type-safe. *)

(*==================================================*)
(** Polymorphic pairs *)
type prod<'a, 'b> =
  | Pair of 'a * 'b

let fst (p: prod<'a, 'b>): 'a =
  match p with
    | Pair (x, y) -> x

(* Question: what's the type of this function? *)
let rec combine l1 l2 =
  match (l1, l2) with
    | ([], _) -> []
    | (_, []) -> []
    | (x::xs, y::ys) -> (x, y)::(combine xs ys)

(*==================================================*)
(** Polymorphic options *)
type option<'a> =
  | Some of 'a
  | None

let rec index n l =
  match l with
    | [] -> None
    | x::xs ->
      match n with
        | 0 -> Some x
        | _ -> index (n-1) xs


(*==================================================*)
(** Higher-order functions *)

(* Here, the function "f" is an argument to the higher-order
function "doit3times": *)
let doit3times f n = f (f (f n))

(* Recall our "minus2" function from "Basics.fs": *)
let minus2 n = n-2

(* unit test *)
printfn "%d" (doit3times minus2 9)

(* Filter function: *)
let rec filter test l =
  match l with
    | [] -> []
    | x::xs ->
      if test x
      then x::(filter test xs)
      else filter test xs

(* I rewrite the evenb function from "Basics.fs" as follows: *)
let rec evenb n =
  match n with
    | 0 -> true
    | 1 -> false
    | _ -> evenb (n-2)

printfn "%A" (filter evenb [1; 2; 3; 4; 5; 6; 7; 8])

(*==================================================*)
(** Anonymous Functions *)
(* The anonymous functions in F# are very similar with those
in Coq, even the key word are the same---"fun": *)
printfn "ano = %d" (doit3times (fun n -> (n-2)) 9)

let tmplist = [ [1;2]; [3]; [4]; [5;6;7]; []; [8] ]
printfn "%A" (filter (fun l -> (match l with
                                | [] -> false
                                | [x] -> true
                                | _ -> false)) tmplist)
(* Note that at the beginning, I'd like to writing some code
like this: *)
// filter (fun l -> length l = 1) tmplist
(* But there seems to be a bug in VS2012 preventing me from
doing so. :-( *)

(** map *)
let rec map f l =
  match l with
    | [] -> []
    | x::xs -> (f x)::(map f xs)

printfn "%A" (map evenb [2; 1; 2; 5])

printfn "%A" (map (fun x -> (x*x, x*x*x)) [1;2;3;4])

let option_map f xo =
  match xo with
    | None -> None
    | Some x -> Some (f x)

(** Fold *)
let rec fold f l b =
  match l with
    | [] -> b
    | x::xs -> f x (fold f xs b)

printfn "%d" (fold (fun x y -> x+y) [1;2;3;4;5;6;7;8;9;10] 0)

(* Gauss formulea *)
let rec genList n =
  match n with
    | 0 -> []
    | _ -> n::(genList (n-1))
    
printfn "%d" (fold (fun x y -> x+y) (genList 100) 0)

(** Functions for Constructing Functions *)
let constfun x = fun k -> x

let ftrue = constfun true

printfn "%A" (ftrue 0)

let overridef f k v =
  fun k' -> if k'=k then v else f k'
