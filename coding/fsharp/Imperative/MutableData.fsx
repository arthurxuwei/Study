let mutable x = 5;;
x <- 10;;
//Notice: val it : unit = ()

//Limitations of Mutable Variables:
//mutables are inaccessible outside of the scope of the function where they are defined. 
//Specifically, this means its not possible to reference a mutable in a subfunction of another function.

let testMutable() = 
    let mutable msg = "hello"
    printfn "%s" msg
    let setMsg() = 
        msg <- "world" (*<---error*)
    setMsg()
    printfn "%s" msg

//Ref cells get around some of the limitations of mutables. 
//In fact, ref cells are very simple datatypes which wrap up a mutable field in a record type.

let y = ref "hello"
!y
y:="world"

let testRef() = 
    let msg = ref "hello"
    printfn "%s" !msg
    let setMsg() = 
        msg := "world" (*<---error*)
    setMsg()
    printfn "%s" !msg

//Aliasing Ref Cells

//Encapsulating Mutable State
//F# discourages the practice of passing mutable data between functions. 
//Functions that rely on mutation should generally hide its implementation details behind a private function

let incr = 
    let counter = ref 0
    fun () ->
        counter := !counter + 1
        !counter
incr()
incr()
incr()