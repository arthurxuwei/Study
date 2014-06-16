//Interfaces
type ILifeForm = 
    abstract Name: string
    abstract Speak: unit -> unit
    abstract Eat: unit -> unit

type Dog(name: string, age: int) =
    member this.Age = age

    interface ILifeForm with
        member this.Name = name
        member this.Speak() = printfn "Woof!"
        member this.Eat() = printfn "Yum, doggy biscuits!"

type Monkey(weight: float) = 
    let mutable _weight = weight

    member this.Weight
        with get() = _weight
        and set(value) = _weight <- value

    interface ILifeForm with
        member this.Name = "Monkey!!!"
        member this.Speak() = printfn "Ook Ook"
        member this.Eat() = printfn "Bananas!"

type Ninja() =
    interface ILifeForm with
        member this.Name = "Ninjas hav no name"
        member this.Speak() = printfn "Ninjas are silent, deadly killers"
        member this.Eat() = printfn "Ninjas don't eat, they wail on guitars because they're totally sweet"

//Implementing Interfaces with Object Expressions
open System
open System.Collections.Generic
type person = {name: string; age: int}
let people = [|
            {name= "Larry"; age= 20}
            {name= "Moe"; age= 30}
            {name= "Curly"; age= 25}
            |]

let sortAndPrint msg items (comparer: System.Collections.Generic.IComparer<person>) = 
    Array.Sort(items, comparer)
    printf "%s: " msg
    Seq.iter(fun x -> printf "(%s, %i) " x.name x.age) items
    printfn ""

//sort by age
sortAndPrint "age" people { new IComparer<person> with member this.Compare(x, y) = x.age.CompareTo(y.age) }

//sort by name
sortAndPrint "name" people { new IComparer<person> with member this.Compare(x, y) = x.name.CompareTo(y.name) }

//sort by name descending
sortAndPrint "name desc" people { new IComparer<person> with member this.Compare(x, y) = y.name.CompareTo(x.name) }

//implementing multiple interfaces
type Person(name: string, age: int) =
    member this.Name = name
    member this.Age = age
    (*IComparable is used for ordering instances*)
    interface IComparable<Person> with
        member this.CompareTo(other) = 
            (*Sort by name, then age*)
            match this.Name.CompareTo(other.Name) with
            | 0 -> this.Age.CompareTo(other.Age)
            | n -> n

    (*Used for comparing this type against other types *)
    interface IEquatable<string> with
        member this.Equals(othername) = this.Name.Equals(othername)

//Interface Hierarchies
type ILifeForm_ =
    abstract member location: System.Drawing.Point

type 'a IAnimal =
    inherit ILifeForm_
    inherit System.IComparable<'a>
    abstract member speak: unit -> unit

type IFeline = 
    inherit IAnimal<IFeline>
    abstract member purr: unit -> unit

//Using interface in generic type definitions
type tree<'a> when 'a :> IComparable<'a> =
    | Nil
    | Node of 'a * 'a tree * 'a tree

let rec insert (x: #IComparable<'a>) = function
    | Nil -> Node(x, Nil, Nil)
    | Node(y, l, r) as node -> 
        if x.CompareTo(y) = 0 then node
        elif x.CompareTo(y) = -1 then Node(y, insert x l, r)
        else Node(y, l, insert x r);;

let rec contains (x: #IComparable<'a>) = function
    | Nil -> false
    | Node(y, l , r) as node ->
        if x.CompareTo(y) = 0 then true
        elif x.CompareTo(y) = -1 then contains x l
        else contains x r;;

let x = 
    let rnd = new Random()
    [ for a in 1..10 -> rnd.Next(1, 100) ]
    |> Seq.fold (fun acc x -> insert x acc) Nil;;

//Simple dependency injection
type IAddStrategy = 
    abstract add: int -> int -> int

type DefaultAdder() =
    interface IAddStrategy with
        member this.add x y = x + y

type SlowAdder() = 
    interface IAddStrategy with
        member this.add x y =
            let rec loop acc = function
                |0 -> acc
                |n -> loop (acc+1) (n-1)
            loop x y

type OffByOneAdder() =
    interface IAddStrategy with
        member this.add x y = x + y - 1

type SwappableAdder(adder : IAddStrategy) = 
    let mutable _adder = adder
    member this.Adder
        with get() = _adder
        and set(value) = _adder <- value

    member this.Add x y = this.Adder.add x y;;

let myAdder = new SwappableAdder(new DefaultAdder())

myAdder.Add 10 1000000000

myAdder.Adder <- new SlowAdder()

myAdder.Add 10 100000000

myAdder.Adder <- new OffByOneAdder()

myAdder.Add 10 100000000