//OptionType

let div x y = x / y

let safediv x y = 
    match y with
    | 0 -> None
    | _ -> Some(x/y)

//Pattern Matching Option Types
let isFortyTwo = function
    | Some(42) -> true
    | Some(_) | None -> false

isFortyTwo(Some(43));;
isFortyTwo(Some(42));;
isFortyTwo(None);;