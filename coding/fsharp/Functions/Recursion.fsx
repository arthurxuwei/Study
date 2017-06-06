let rec fact x =
    if x < 1 then 1
    else x * fact (x - 1)

(* // can also be written using pattern matching syntax:
let rec fact = function
    | n when n < 1 -> 1
    | n -> n * fact (n - 1) *)

//Greatest Common Divisor

let rec gcd x y =
    if y = 0 then x
    else gcd y (x % y)

gcd 259 111
//val it : int = 37


(*Tail Recursion*)
//non-tail recursive function
let rec count_nontail n = 
    if n = 1000000 then
        printfn "Done"
    else 
        if n % 1000 = 0 then
            printfn "n: %i" n

        count_nontail (n + 1) (*recursive call*)
        () (* <-- This function is not tail recursive 
                because  it performs extra work (by returning unit) 
                after this recursive call is invoked.*);;
//count_nontail 0;;
//Process is terminated due to StackOverflowException.

let rec count n = 
    if n = 1000000 then
        printfn "Done"
    else
        if n % 1000 = 0 then
            printfn "n: %i" n

        count (n + 1)

count 0;;
//Done

(*How to Write Tail-recursive Functions*)
//define multiplication recursively as M(a, b) = a + M(a, b - 1), b > 1.
let rec slowMultiply_non a b =
    if b > 1 then
        a + (slowMultiply_non a b-1) (*<-- it is not tail-recursive ::Remember tail recursion needs the last operation to be the recursion.*)
    else
        a

let slowMultiply a b =
    let rec loop acc counter =
        if counter > 1 then
            loop (acc + a) (counter - 1) (* tail-recursive*)
        else    acc
    loop a b;;