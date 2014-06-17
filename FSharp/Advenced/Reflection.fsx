//Inspecting Types
"Hello, World".GetType()

typeof<System.IO.File>

type Car(make: string, model: string, year: int) =
    member this.Make = make
    member this.Model = model
    member this.Year = year
    member this.WheelCount = 4

type Cat() =
    let mutable age = 3
    let mutable name = System.String.Empty

    member this.Purr() = printfn "Purr"
    member this.Age
        with get() = age
        and set(v) = age <- v
    member this.Name
        with get() = name
        and set(v) = name <- v

let printProperties x = 
    let t = x.GetType()
    let properties = t.GetProperties()
    printfn "----------"
    printfn "%s" t.FullName
    properties |> Array.iter (fun prop ->
        if prop.CanRead then
            let value = prop.GetValue(x, null)
            printfn "%s: %O" prop.Name value
        else
            printfn "%s: ?" prop.Name)

let carInstance = new Car("Ford", "Focus", 2009)
let catInstance = 
    let temp = new Cat()
    temp.Name <- "Mittens"
    temp

printProperties carInstance
printProperties catInstance

//Working With Attributes
(*
.NET attributes and reflection go hand-in-hand.
 Attributes allow programmers to decorate classes, methods, members, and other source code with metadata used at runtime.
Many .NET classes use attributes to annotate code in a variety of ways; it is only possible to access and interpret attributes through reflection. 
This section will provide a brief overview of attributes. 
*)
    
type MyAttribute(text: string) = 
    inherit System.Attribute()

    do printfn "MyAttribute created. Text: %s" text

    member this.Text = text

[<MyAttribute("Hello World")>]
type MyClass() = 
    member this.SomeProperty = "This is a property"


let z = new MyClass()
z.GetType().GetCustomAttributes(true)


//Encapsulating Singleton Design Pattern
type ConstructionAttribute(singleInstance: bool) =
    inherit System.Attribute()
    member this.IsSingleton = singleInstance

let singletons = new System.Collections.Generic.Dictionary<System.Type, obj>()
let make() : 'a =
    let newInstance() = System.Activator.CreateInstance<'a>()
    let attributes = typeof<'a>.GetCustomAttributes(typeof<ConstructionAttribute>, true)
    let singleInstance = 
        if attributes.Length > 0 then
            let contructionAttribut = attributes.[0] :?> ConstructionAttribute
            contructionAttribut.IsSingleton
        else false

    if singleInstance then
        match singletons.TryGetValue(typeof<'a>) with
        |true, v -> v :?> 'a
        |_ -> 
            let instance = newInstance()
            singletons.Add(typeof<'a>, instance)
            instance
    else newInstance()

[<ConstructionAttribute(true)>]
type SingleOnly() =
    do printfn "SingleOnly contructor"

[<ConstructionAttribute(false)>]
type NewAlways() = 
    do printfn "NewAlways contructor"

let x = make<SingleOnly>()
let x' = make<SingleOnly>()
let y = make<NewAlways>()
let y' = make<NewAlways>()

printfn "x = x': %b" (x=x')
printfn "y = y': %b" (y=y')

