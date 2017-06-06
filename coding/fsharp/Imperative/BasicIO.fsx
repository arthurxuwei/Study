//working with Console
//printf printfn sprintf

sprintf "hello, %s. I'm %s" "1" "2"

System.String.Format("Hi, my name is {0} and I'm a {1}", "Juliet", "Scorpio")

//Files
(*
The following classes are useful for interrogating the host filesystem:

The System.IO.File class exposes several useful members for creating, appending, and deleting files.
System.IO.Directory exposes methods for creating, moving, and deleting directories.
System.IO.Path performs operations on strings which represent file paths.
System.IO.FileSystemWatcher which allows users to listen to a directory for changes.
*)

//Streams
(*
A stream is a sequence of bytes. .NET provides some classes which allow programmers to work with steams including:

System.IO.StreamReader which is used to read characters from a stream.
System.IO.StreamWriter which is used to write characters to a stream.
System.IO.MemoryStream which creates an in-memory stream of bytes.
*)

//Exception Handling

//try/with
let getNumber msg =
    printf msg;
    try
        int32(System.Console.ReadLine())
    with
        | :? System.FormatException -> System.Int32.MinValue
 
let x = getNumber("x = ")
let y = getNumber("y = ")
printfn "%i + %i = %i" x y (x + y)

//raising exception
type 'a tree =
    | Node of 'a * 'a tree * 'a tree
    | Empty
 
let rec add x = function
    | Empty -> Node(x, Empty, Empty)
    | Node(y, left, right) ->
        if x > y then Node(y, left, add x right)
        else if x < y then Node(y, add x left, right)
        else failwithf "Item '%A' already been added to tree" x

//Try/finally
let tryWithFinallyExample f =
    try
        printfn "tryWithFinallyExample: outer try block"
        try
            printfn "tryWithFinallyExample: inner try block"
            f()
        with
            | exn ->
                printfn "tryWithFinallyExample: inner with block"
                reraise() (* raises the same exception we just caught *)
    finally
        printfn "tryWithFinally: outer finally block"
 
let catchAllExceptions f =
    try
        printfn "-------------"
        printfn "catchAllExceptions: try block"
        tryWithFinallyExample f
    with
        | exn ->
            printfn "catchAllExceptions: with block"
            printfn "Exception message: %s" exn.Message
 
let main() =                
    catchAllExceptions (fun () -> printfn "Function executed successfully")
    catchAllExceptions (fun () -> failwith "Function executed with an error")
 
main()

//use Statement
let writeToFile fileName =
    let sw = new System.IO.StreamWriter(fileName : string)
    try
        sw.Write("Hello ")
        sw.Write("World!")
    finally
        sw.Dispose()

let writeToFile_use fileName =
    use sw = new System.IO.StreamWriter(fileName : string)
    sw.Write("Hello ")
    sw.Write("World!")

//Define New 
exception ReindeerNotFoundException of string