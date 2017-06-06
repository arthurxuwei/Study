// Learn more about F# at http://fsharp.net
// See the 'F# Tutorial' project for more help.
(*The Composition Function*)
//let inline (<<) f g x = f (g x)
//let inline (>>) f g x = g (f x)

let f x = x * x
let g x = -x/2.0 + 5.0
let fog = f << g

fog 0.0
fog 1.0
fog 2.0

//let inline (|>) x f = f x
let square x = x*x
let add x y = x+y
let toString x = x.ToString()

let complexFunc x = 
    toString (add 5 (square x))

let complexFunction x =
    x |> square |> add 5 |> toString

//anonymous functions
let complexFunc_anonymous =
    2
    |> (fun x -> x+5)
    |> (fun x -> x*x)
    |> (fun x -> x.ToString())

//Two Pattern Matching Syntaxes
//Traditional Syntax
let getPrice_t food = 
    match food with
    | "banana" -> 0.79
    | _ -> nan
//shortcut Syntax
let getPrice_s = function
    | "banana" -> 0.79
    | _ -> nan
//F# compiler converts the 'function' keyword into the following construct
let getPrice_s_ = 
    (fun x ->
        match x with
        | "banana" -> 0.79
        | _ -> nan)

//fibo
let res = Seq.unfold (fun (a, b) ->Some(a, (a+b, a))) (0, 1) 

//currying version 1
let adder x y = x+y
let added1 = adder 10
//version 2
let curry f a = f a
let added2 = (curry (fun x -> x + 1))

//whether each item in the query list appears in the source list
let curry2 f a b = f a b

let rec inList l sym = 
    match l with
    | [] -> false
    | h::t -> 
        if h = sym
            then true
            else inList t sym

let inListMany source query = 
    List.map ((curry2 inList) source) query

//filter
let rec filter l f =
    match l with
    | [] -> []
    | h::t ->
        if f h
            then h :: filter t f
        else filter t f

let dividesBy n x =
    (x%n) = 0


[<EntryPoint>]
let main argv = 
    Seq.iter (fun x -> printf "%d " x) (Seq.take 10 res)
    printf "\n" 
    printfn "%d" (added1 1)
    printfn "%d" (curry (fun x -> x+2) 2)
    printfn "%d" (added2 1)
    printfn "%A" (inListMany ["a";"b";"c";"d";"e"] ["a";"x";"e";"d"])
    printfn "%A" (filter [1;2;3;4;5;6;7;8;9] (dividesBy 2))
    printfn "%A" (filter [1;2;3;4;5;6;7;8;9] (dividesBy 3))
    0



