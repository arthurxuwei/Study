(*
Active Patterns allow programmers to wrap arbitrary values in a union-like data structure for easy pattern matching.
For example, its possible wrap objects with an active pattern, so that you can use objects in pattern matching as easily as any other union type.
*)

(*
You've probably noticed the immediate difference between active patterns and explicitly defined unions:

Active patterns define an anonymous union, where the explicit union has a name (numKind, seqWrapper, etc.).
Active patterns determine their constructor parameters using a kind of type-inference, whereas we need to explicitly define the constructor parameters for each case of our explicit union.
*)

let (|Even|Odd|) n =
    if n % 2 = 0 then Even
    else Odd

let testNum n =
    match n with
    | Even -> printfn "%i is even" n
    | Odd -> printfn "%i is odd" n;;

//unions
type numKind =
    | Even
    | Odd
 
let get_choice n =
    if n % 2 = 0 then
        Even
    else
        Odd
 
let testNum_union n =
    match get_choice n with
    | Even -> printfn "%i is even" n
    | Odd -> printfn "%i is odd" n

(*The parameter in the match clause is always passed as the last argument to the active pattern expression. Using our seq example from earlier
Traditionally, seq's are resistant to pattern matching, but now we can operate on them just as easily as lists.
*)
let (|SeqNode|SeqEmpty|) s =
    if Seq.isEmpty s then SeqEmpty
    else SeqNode ((Seq.head s), Seq.skip 1 s)
 
let perfectSquares = seq { for a in 1 .. 10 -> a * a }
 
let rec printSeq = function
    | SeqEmpty -> printfn "Done."
    | SeqNode(hd, tl) ->
        printf "%A " hd
        printSeq tl;;

//Parameterizing Active Patterns

let (|Contains|) needle (haystack : string) =
    haystack.Contains(needle)

let testString = function
    | Contains "kitty" true -> printfn "Text contains 'kitty'"
    | Contains "doggy" true -> printfn "Text contains 'doggy'"
    | _ -> printfn "Text neither contains 'kitty' nor 'doggy'";;

testString "I have a pet kitty and she's super adorable!";;

//Partial Active Patterns
let (|RegexContains|_|) pattern input = 
    let matches = System.Text.RegularExpressions.Regex.Matches(input, pattern)
    if matches.Count > 0 then Some [for m in matches -> m.Value]
    else None

let testRegString = function
    | RegexContains "http://\S+" urls -> printfn "Got urls: %A" urls
    | RegexContains "[^@]@[^.]+\.\W+" emails -> printfn "Got email address: %A" emails
    | RegexContains "\d+" numbers -> printfn "Got numbers: %A" numbers
    | _ -> printfn "Didn't find anything.";;

testRegString "867-5309, Jenny are you there?"
    
(*
Equal with:
type choice =
    | RegexContains of string list
 
let get_choice pattern input =
    let matches = System.Text.RegularExpressions.Regex.Matches(input, pattern)
    if matches.Count > 0 then Some (RegexContains [ for m in matches -> m.Value ])
    else None
 
let testString n =
    match get_choice "http://\S+" n with
    | Some(RegexContains(urls)) -> printfn "Got urls: %A" urls
    | None ->
        match get_choice "[^@]@[^.]+\.\W+" n with
        | Some(RegexContains emails) -> printfn "Got email address: %A" emails
        | None ->
            match get_choice "\d+" n with
            | Some(RegexContains numbers) -> printfn "Got numbers: %A" numbers
            | _ -> printfn "Didn't find anything."
*)

let (|StartsWith|_|) needle (haystack : string) = if haystack.StartsWith(needle) then Some() else None
let (|EndsWith|_|) needle (haystack : string) = if haystack.EndsWith(needle) then Some() else None
let (|Equals|_|) x y = if x = y then Some() else None
let (|EqualsMonkey|_|) = function (* "Higher-order" active pattern *)
    | Equals "monkey" () -> Some()
    | _ -> None
let (|RegexContains|_|) pattern input = 
    let matches = System.Text.RegularExpressions.Regex.Matches(input, pattern)
    if matches.Count > 0 then Some [ for m in matches -> m.Value ]
    else None
 
let testString n =
    match n with
    | StartsWith "kitty" () -> printfn "starts with 'kitty'"
    | StartsWith "bunny" () -> printfn "starts with 'bunny'"
    | EndsWith "doggy" () -> printfn "ends with 'doggy'"
    | Equals "monkey" () -> printfn "equals 'monkey'"
    | EqualsMonkey -> printfn "EqualsMonkey!" (* Note: EqualsMonkey and EqualsMonkey() are equivalent *)
    | RegexContains "http://\S+" urls -> printfn "Got urls: %A" urls
    | RegexContains "[^@]@[^.]+\.\W+" emails -> printfn "Got email address: %A" emails
    | RegexContains "\d+" numbers -> printfn "Got numbers: %A" numbers
    | _ -> printfn "Didn't find anything."