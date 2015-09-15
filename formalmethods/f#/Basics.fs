(* The purpose of this note is to show basic functional programming
 * style using F#. In essence, our approach is to minic the 
 * corresponding Coq code: that is, we write the same bunch of
 * code as we discussed in class, but in F#. So the best way to read
 * this is to accompany the Coq code.
 *)
(* We use VS2012 to compile this code. *)

(* Thought not necessary, it's a good practice to encapulate
 * each line of code in a module. *)
module Basics

(* Our first example is the same datatype of "day". *)
type day =
  | Monday
  | Tuesday
  | Wednesday
  | Thursday
  | Friday
  | Saturday
  | Sunday

(* Here are the distinctions:
    1. the keyword is now "type", but not "Inductive";
    2. there is no need to mask each constructor with type name;
    3. each constructor must start with capital character, and
    3. there is no "dot" at the end of this data type.    
*)

(** Having defined [day], we can write functions that operate on
    days. Not surprisingly, these code are the same as the Coq
    code, execept for some trivial syntactic differences. *)
let next_weekday (d:day) : day =
  match d with
  | Monday -> Tuesday
  | Tuesday -> Wednesday
  | Wednesday -> Thursday
  | Thursday -> Friday
  | Friday -> Monday
  | Saturday -> Monday
  | Sunday -> Monday

(* Now, we can perform some "unit test" to make sure this
    function goes well. *)
printfn "%A\n" (next_weekday Friday)

printfn "%A\n" (next_weekday (next_weekday Saturday))

(* In Coq, we can prove some theorems such as: 
Example test_next_weekday:
  (next_weekday (next_weekday saturday)) = tuesday.

Unfortunately, F# does not come with this power :-(, we do not
have such luxury of theorem proving. However, we can minic this
with the assertion feature.
*)
assert ((next_weekday (next_weekday Saturday)) = Tuesday)
(* Assertion is an interesting feature for debugging, read
more about it at:
http://msdn.microsoft.com/en-us/library/dd233187.aspx

Writing assertions is a good programming practice.
*)


(* ###################################################################### *)
(** ** Booleans *)

(** In a similar way, we can define the type [bool] of booleans,
    with members [true] and [false]. *)

type bool =
  | True
  | False


(** Functions over booleans can be defined in the same way as
    above: *)

let negb (b:bool) : bool = 
  match b with
  | True -> False
  | False -> True

let andb (b1:bool) (b2:bool) : bool = 
  match b1 with 
  | True -> b2 
  | False -> False

let orb (b1:bool) (b2:bool) : bool = 
  match b1 with 
  | True -> True
  | False -> b2

(* We can perform some "unit test" again. *)
assert ((orb True  False) = True)
assert ((orb False False) = False)
assert ((orb False True)  = True)
assert ((orb True  True)  = True)

(* F# does not allow theorem proving, so there is no such
feature such as "Admitted", so I put some hacks here---I'll
use exceptions *)
exception Admitted of string
let admit () = raise (Admitted "not implemented")

(* Read more about exception handling at:
http://msdn.microsoft.com/en-us/library/dd233239.aspx
*)

(* Having defined this, we can redo all the practice, such
as: *)
let nandb (b1: bool) (b2: bool) =
  admit ()


(* For the sake of brevity, we don't repeat other functions here, they are
similar. *)


(* ###################################################################### *)
(** ** Numbers *)
(* The simplest module system in F# is like this: *)
module Playground1 =
  type nat =
    | O
    | S of nat

  (* predecessor *)
  let pred (n: nat): nat =
    match n with
      | O -> O
      | S n' -> n'

  let minustwo (n: nat): nat =
    match n with
      | O -> O
      | S O -> O
      | S (S n') -> n'

  let four = S (S (S (S O)))
  let _ = printfn "%A" (minustwo four)

  (* recursion *)
  let rec evenb (n: nat): bool =
    match n with
      | O -> True
      | S O -> False
      | S (S n') -> evenb n'

  let oddb (n: nat): bool = negb (evenb n)

  assert (oddb (S O) = True)
  assert (oddb four = False)

  (* some multi-argument functions: *)
  let rec plus (n: nat) (m: nat): nat =
    match n with
      | O -> m
      | S n' -> S (plus n' m)

      (* unit tests *)
  printfn "%A" (plus (S (S (S O))) (S (S O)))

  let rec mult (n: nat) (m: nat): nat =
    match n with
      | O -> O
      | S n' -> plus m (mult n' m)

  let rec minus (n: nat) (m: nat): nat =
    match (n, m) with
      | (O, _) -> O
      | (_, O) -> n
      | (S n', S m') -> minus n' m'

  let rec exp (basee: nat) (power: nat): nat =
    match power with
      | O -> S O
      | S p -> mult basee (exp basee p)

  (* Fill in this code: *)
  let rec factorial (n: nat): nat =
    admit ()

  let rec beq_nat (n: nat) (m: nat): bool =
    match n with
      | O ->
        match m with
          | O -> True
          | S m' -> False
      | S n' ->
        match m with
          | O -> False
          | S m' -> beq_nat n' m'

  (* and there is another definition for equality function: *)
  let rec beq_nat' (n: nat) (m: nat): bool =
    match (n, m) with
      | (O, O) -> True
      | (S n', S m') -> beq_nat' n' m'
      | _ -> False
        

  (* Less or equal function, that is "<=": *)
  let rec ble_nat (n: nat) (m: nat): bool =
    match n with
      | O -> True
      | S n' ->
        match m with
          | O -> False
          | S m' -> ble_nat n' m'

  (* Fill in this for little function, that is "<": *)
  let rec blt_nat (n: nat) (m: nat): bool =
    admit ()
  (* Don't forget to do some testing. *)



  (* double the input argument *)
  let rec double (n: nat): nat =
    match n with
      | O -> O
      | S n' -> S (S (double n'))

  
  
  
