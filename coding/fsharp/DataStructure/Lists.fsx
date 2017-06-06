//lists
let nums = [0;1;2;3;4;5;6;7;8;9];;

let x = 1::2::3::[];;
let y = 12 :: x;;

//List.init
List.init 5 (fun index -> index * 3)
List.init 5 (fun index -> (index, index * 2, index * 3))

//List Comprehensions
[1 .. 10]
//val it : int list = [1; 2; 3; 4; 5; 6; 7; 8; 9; 10]
[1..2..10]
//val it : int list = [1; 3; 5; 7; 9]
['a'..'s']

[for a in 1 .. 10 do yield (a*a)]
[ for a in 1 .. 5 -> a * a];;

[for a in 1 .. 3 do for b in 3 .. 7 do yield (a, b) ]
[for a in 1 .. 100 do if a%3 = 0 && a%5 = 0 then yield a]

let c = ['a'..'f']
[for a in c do yield [a;a;a]]

[for a in 1..10 do yield! [a..a+3]]

[for a in 1..5 do
    match a with
    | 3 -> yield! ["hello";"world"]
    | _ -> yield a.ToString()]

//Alternative List Comprehension Syntax
//-> and ->> are equivalent to the yield and yield! operators respectively.
//'->>' deprecated

//Pattern Matching Lists
let rec sum total = function
    | [] -> total
    | hd :: tl -> sum (hd + total) tl

let testList = [1..5]
let sumOfNumber = sum 0 testList

let reverse l = 
    let rec loop acc = function
        | [] -> acc
        | hd :: tl -> loop (hd :: acc) tl
    loop [] l
reverse [1..5]

let rec filter predicate = function
    | [] -> []
    | hd :: tl -> 
        match predicate hd with
        | true -> hd::filter predicate tl
        | false -> filter predicate tl
let filterNumbers = [1..10] |> filter (fun x -> x%2 = 0) 

//tail-recursive
let filter_tail predicate l =
    let rec loop acc = function
        | [] -> acc
        | hd :: tl ->
            match predicate hd with
            | true -> loop (hd :: acc) tl
            | false -> loop (acc) tl
    List.rev (loop [] l)

let rec map converter = function
    | [] -> []
    | hd::tl -> converter hd::map converter tl
let mapNumbers = [1..10] |> map (fun x-> x*x)

//Using List Module
//List.*
//List.append and the @ Operator

//List.fold and unfold
//fold: f (f (f (f (f (f seed 1) 2) 3) 4) 5
//foldBack: f 1 (f 2 (f 3(f 4(f 5 seed))))

//List.find and tryFind

//pair and unpair
