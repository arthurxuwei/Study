//Partial Functions
(*
F# automatically caches the value of any function which takes no parameters. 
When F# comes across a function with no parameters, F# will only evaluate the function once and reuse its value everytime the function is accessed
*)

let isNebraskaCity_bad city =
    let cities =
        printfn "Creating cities Set"
        ["Bellevue"; "Omaha"; "Lincoln"; "Papillion"]
        |> Set.ofList
 
    cities.Contains(city)
 
let isNebraskaCity_good =
    let cities =
        printfn "Creating cities Set"
        ["Bellevue"; "Omaha"; "Lincoln"; "Papillion"]
        |> Set.ofList
 
    fun city -> cities.Contains(city)

(*
The implementation of isNebraskaCity_bad forces F# to re-create the internal set on each call. On the other hand, 
isNebraskaCity_good is a value initialized to the function fun city -> cities.Contains(city), 
so it creates its internal set once and reuses it for all successive calls.

Note: Internally, isNebraskaCity_bad is compiled as a static function which constructs a set on every call. 
                  isNebraskaCity_good is compiled as a static readonly property, where the value is initialized in a static constructor.
This distinction is often subtle, but it can have a huge impact on an application's performance.
*)

//Memoization
(*
"Memoization" is a fancy word meaning that computed values are stored in a lookup table rather than recomputed on every successive call. 
Long-running pure functions (i.e. functions which have no side-effects) are good candidates for memoization. 
*)

let rec fib n =
    if n = 0I then 0I
    elif n = 1I then 1I
    else fib (n-1I) + fib (n-2I)

fib 35I
(*
Real: 00:00:11.328, CPU: 00:00:11.216, GC gen0: 1096, gen1: 2, gen2: 0
val it : System.Numerics.BigInteger = 9227465 {IsEven = false;
                                               IsOne = false;
                                               IsPowerOfTwo = false;
                                               IsZero = false;
                                               Sign = 1;}
*)

let rec fib_memoization = 
    let dict = new System.Collections.Generic.Dictionary<_,_>()
    fun n ->
        match dict.TryGetValue(n) with
        | true, v -> v
        | false, _ ->
            let temp =
                if n = 0I then 0I
                elif n = 1I then 1I
                else fib_memoization (n-1I) + fib_memoization (n-2I)
            dict.Add(n, temp)
            temp

fib_memoization 35I

(*
Real: 00:00:00.003, CPU: 00:00:00.000, GC gen0: 0, gen1: 0, gen2: 0
val it : System.Numerics.BigInteger = 9227465 {IsEven = false;
                                               IsOne = false;
                                               IsPowerOfTwo = false;
                                               IsZero = false;
                                               Sign = 1;}
*)

let memoize f =
    let dict = new System.Collections.Generic.Dictionary<_,_>()
    fun n ->
        match dict.TryGetValue(n) with
        | (true, v) -> v
        | _ ->
            let temp = f(n)
            dict.Add(n, temp)
            temp
 
let rec fib_memoize = memoize(fun n ->
    if n = 0I then 0I
    elif n = 1I then 1I
    else fib_memoize (n - 1I) + fib_memoize (n - 2I) )

(*Note: Its very important to remember that the implementation above is not thread-safe -- 
    the dictionary should be locked before adding/retrieving items if it will be accessed by multiple threads.*)

//Lazy values

(*
The F# lazy data type is an interesting primitive which delays evaluation of a value until the value is actually needed.
 Once computed, lazy values are cached for reuse later:
*)

let x = lazy(printfn "Lazy"; 5+5)

x.Force()//output "Lazy"
x.Force()//no output

let n = seq {for a in 1..10 -> printfn "Got %i" a;a} |> Seq.cache;;
let m = Seq.take 5 n;;
Seq.reduce (+) m;; 
Seq.reduce (+) m;;// not recompute valuse

Seq.reduce (+) n;;//Values 1 through 5 already computed, should only compute 6 through 10
