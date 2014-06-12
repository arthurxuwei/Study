(*
Generic Func
*)
let giveMeThree x = 3
//'a -> int
let throwAwayFirstInput x y = y;;
//val throwAwayFirstInput : x:'a -> y:'b -> 'b

throwAwayFirstInput 5 "value 5";;
//val it : string = "value 5"
throwAwayFirstInput "value 5" 10;;
//val it : int = 10


(*
PatternMatch
*)

let rec fib n = 
    match n with
    |0 -> 0
    |1 -> 1
    | _ -> fib (n - 1) + fib (n - 2)
fib 10;;

(*Binding Variables with Pattern Matching*)
let rec factorial = function
    |0|(*this '|' is 'or'*)1->1
    |n -> n * factorial (n - 1)
factorial 5;;

let greeting name = 
    match name with
    |"Steve" | "Kristina" | "Matt" -> "Hello!"
    |"Carlos" | "Maria" -> "Hola!"
    | _ -> "DOES NOT COMPUTE!"

greeting "Maria";;
greeting "Steve";;
greeting "ABC";;

let getPrice = function
    | "banana" -> 0.79
    | "watermelon" -> 3.49
    | "tofu" -> 1.09
    | _ -> nan (*not a number*)

getPrice "tofu";;
getPrice "apple";;

(*Using Guards within Patterns*)
let sign = function
    |0 -> 0
    |x when x < 0 -> -1
    |x when x > 0 -> 1

sign -55;;
sign 108;;
sign 0;;

