//Event class
type Person(name: string) =
    let mutable _name = name;
    let nameChanged = new Event<unit>() (*create event*)

    member this.NameChanged = nameChanged.Publish (*exposed event handler*)

    member this.Name
        with get() = _name
        and set(value) = 
            _name <- value
            nameChanged.Trigger() (*invokes event handler*)                       

//adding callbacks to event handlers
let p = new Person("Bob")
p.NameChanged.Add(fun () -> printfn "--Name changed! New name: %s" p.Name)

printfn "Event Handing is easy"
p.Name <- "Joe"

printfn "It handily decouples objects from one another"
p.Name <- "Moe"

p.NameChanged.Add(fun () -> printfn "-- Another handler attached to NameChanged!")


let person_NameChanged =
    new Handler<unit>(fun sender eventargs -> printfn "-- Name changed! New name: %s" p.Name)
 
p.NameChanged.AddHandler(person_NameChanged)

p.NameChanged.RemoveHandler(person_NameChanged)


//Pass and retrive State
open System
 
type SuperFileReader() =
    let progressChanged = new Event<int>()
 
    member this.ProgressChanged = progressChanged.Publish
 
    member this.OpenFile (filename : string, charsPerBlock) =
        use sr = new System.IO.StreamReader(filename)
        let streamLength = int64 sr.BaseStream.Length
        let sb = new System.Text.StringBuilder(int streamLength)
        let charBuffer = Array.zeroCreate<char> charsPerBlock
 
        let mutable oldProgress = 0
        let mutable totalCharsRead = 0
        progressChanged.Trigger(0)
        while not sr.EndOfStream do
            (* sr.ReadBlock returns number of characters read from stream *)
            let charsRead = sr.ReadBlock(charBuffer, 0, charBuffer.Length)
            totalCharsRead <- totalCharsRead + charsRead
 
            (* appending chars read from buffer *)
            sb.Append(charBuffer, 0, charsRead) |> ignore
 
            let newProgress = int(decimal totalCharsRead / decimal streamLength * 100m)
            if newProgress > oldProgress then
                progressChanged.Trigger(newProgress) // passes newProgress as state to callbacks
                oldProgress <- newProgress
 
        sb.ToString()
 
let fileReader = new SuperFileReader()
fileReader.ProgressChanged.Add(fun percent ->
    printfn "%i percent done..." percent)
 
let x = fileReader.OpenFile(@"C:\Test.txt", 50)
printfn "%s[...]" x.[0 .. if x.Length <= 100 then x.Length - 1 else 100]

printfn "It's also causes programs behave non-deterministically."
p.Name <- "Bo"

printfn "The function NameChanged is invoked effortlessly."
