(*Computation expressions are easily the most difficult*)

//Monad Primer
(*
 The designers of F# use term "computation expression" and "workflow" because it's less obscure and daunting than the word "monad." 
 The author of this book prefers "monad" to emphasize the parallel between the F# and Haskell (and, strictly as an aside, it's just a neat sounding five-dollar word).
*)

//Visualizing Monads with F#
(*
let read_line() = System.Console.ReadLine()
let print_string(s) = printf "%s" s

print_string "What's your name?"
let name = read_line()
print_string("Hello, " + name)
*)
(*
re-write the read_line and print_string functions to take an extra parameter, 
namely a function to execute once our computation completes
*)

let read_line(f) = f("Arthur")
let print_string(s, f) = f(printf "%s" s)

print_string("What's your name?", fun() ->
    read_line(fun name ->
        print_string("Hello, " + name, fun () -> () ) ) )

//The MayBe Monad
(*
A well-known monad, the Maybe monad, represents a short-circuited computation which should "bail out" if any part of the computation fails. 
*)
(*
let addThreeNumbers() =
    let getNum msg =
        printf "%s" msg
        match System.Int32.TryParse(System.Console.ReadLine()) with
        | (true, n) when n >= 0 && n <= 100 -> Some(n)
        | _ -> None
 
    match getNum "#1: " with
    | Some(x) ->
        match getNum "#2: " with
        | Some(y) ->
            match getNum "#3: " with
            | Some(z) -> Some(x + y + z)
            | None -> None
        | None -> None
    | None -> None
*)
//monadic style
let addThreeNumbers() =
    let bind(input, rest) =
        match System.Int32.TryParse(input()) with
        | (true, n) when n >= 0 && n <= 100 -> rest(n)
        | _ -> None
 
    let createMsg msg = fun () -> printf "%s" msg; System.Console.ReadLine()
 
    bind(createMsg "#1: ", fun x ->
        bind(createMsg "#2: ", fun y ->
            bind(createMsg "#3: ", fun z -> Some(x + y + z) ) ) )

//why use monads
(*
The code above is still quite extravagant and verbose for practical use, 
however monads are especially useful for modeling calculations which are difficult to capture sequentially.
Multithreaded code, for example, is notoriously resistant to efforts to write in an imperative style; 
however it becomes remarkably concise and easy to write in monadic style. 
*)

open System.Threading
open System.Text.RegularExpressions

let bind(input, rest) = 
    ThreadPool.QueueUserWorkItem(new WaitCallback( fun _ -> rest(input()) )) |> ignore

let downloadAsync(url: string) = 
    let printMsg msg = printfn "ThreadID = %i, Url = %s, %s" (Thread.CurrentThread.ManagedThreadId) url msg
    bind( (fun() -> printMsg "Creating webclient..."; new System.Net.WebClient() ),fun webclient -> 
        bind( (fun() -> printMsg "Downloading url..."; webclient.DownloadString(url)), fun html ->
            bind( (fun() -> printMsg "Extracting urls..."; Regex.Matches(html, @"http://\S+") ), fun matches ->
                    printMsg ("Found " + matches.Count.ToString() + " links")
                )
            )
        )

["http://www.google.com/"; "http://microsoft.com/"; "http://www.wordpress.com/"; "http://www.peta.org"] |> Seq.iter downloadAsync

//Computation Expressions
(*
Computation expressions are fundamentally the same concept as seen above, 
although they hide the complexity of monadic syntax behind a thick layer of syntactic sugar. 
A monad is a special kind of class which must have the following methods: Bind, Delay, and Return.
*)

type MaybeBuilder() =
    member this.Bind(x, f) =
        match x with
        | Some(x) when x >= 0 && x <= 100 -> f(x)
        |_ -> None
    member this.Delay(f) = f()
    member this.Return(x) = Some x

let maybe = MaybeBuilder()

maybe.Delay( fun () ->
    let x = 12
    maybe.Bind(Some 11, fun y ->
        maybe.Bind(Some 30, fun z ->
            maybe.Return(x + y + z)
            )
        )
    )

//Sugared syntax
let sugared =
    maybe {
        let x = 12
        let! y = Some 11
        let! z = Some 30
        return x + y + z
    }
(*
Note: You probably noticed that the sugared syntax is strikingly similar to the syntax used to declare sequence expressions, seq { expr }. 
This is not a coincidence. In the F# library, sequences are defined as computation expressions and used as such. 
The async workflow is another computation expression you'll encounter while learning F#.
*)

//What are Computation Expressions Used For?
(*
F# encourages of a programming style called language oriented programming to solve problems. 
In contrast to general purpose programming style, language oriented programming centers around the programmers identifying problems they want to solve, 
then writing domain specific mini-languages to tackle the problem, and finally solve problem in the new mini-language.

Computation expressions are one of several tools F# programmers have at their disposal for designing mini-languages.
 Its surprising how often computation expressions and monad-like constructs occur in practice.
  For example, the Haskell User Group has a collection of common and uncommon monads, including those which compute distributions of integers and parse text. 
  Another significant example, an F# implementation of software transactional memory, is introduced on hubFS.
*)
