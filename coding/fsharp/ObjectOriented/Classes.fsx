(*Object There are actually two different syntaxes for defining a class: an implicit syntax and an explicit syntax.*)
//implicit
(*
type TypeName optional-type-arguments arguments [ as ident ] =
    [ inherit type { as base } ]
    [ let-binding | let-rec bindings ] *
    [ do-statement ] *
    [ abstract-binding | member-binding | interface-implementation ] *
*)

type Account(number : int, holder : string) = class
    let mutable amount = 0m
 
    member x.Number = number
    member x.Holder = holder
    member x.Amount = amount
 
    member x.Deposit(value) = amount <- amount + value
    member x.Withdraw(value) = amount <- amount - value
end

let bob = new Account(123, "Bob's Saving")

let printAccount (x:Account) =
    printfn "x.Number: %i, x.Holder: %s, x.Amount: %M" x.Number x.Holder x.Amount

printAccount bob
bob.Deposit(100M)
printAccount bob

let transfer amount (source : Account) (target : Account) =
    source.Withdraw amount
    target.Deposit  amount

let anni = new Account(222, "Anni's Saving")

transfer 100M bob anni
bob;;
anni;;

//using 'do' keyword
//The do keyword is used for post-constructor initialization. 

type Human (name:string) = class
    let mutable _name = name
    let mutable _firstChar = '#'
    let mutable _secondChar = '#'

    do
        _firstChar <- name.[0]
        _secondChar <- name.[1]

    member x.FirstChar = _firstChar
    member x.SecondChar = _secondChar
end

//explicit 
(*
type TypeName =
    [ inherit type ]
    [ val-definitions ]
    [ new ( optional-type-arguments arguments ) [ as ident ] =
      { field-initialization }
      [ then constructor-statements ]
    ] *
    [ abstract-binding | member-binding | interface-implementation ] *
*)

type Line = class
    val X1 : float
    val Y1 : float
    val X2 : float
    val Y2 : float
 
    new (x1, y1, x2, y2) =
        { X1 = x1; Y1 = y1;
            X2 = x2; Y2 = y2}
 
    member x.Length =
        let sqr x = x * x
        sqrt(sqr(x.X1 - x.X2) + sqr(x.Y1 - x.Y2) )
end

//We can perform some post-constructor processing using a then block
type Line_New = class
    val X1 : float
    val Y1 : float
    val X2 : float
    val Y2 : float
 
    new (x1, y1, x2, y2) as this =
        { X1 = x1; Y1 = y1;
            X2 = x2; Y2 = y2;}
        then
            printfn "Line constructor: {(%F, %F), (%F, %F)}, Line.Length: %F"
                this.X1 this.Y1 this.X2 this.Y2 this.Length
 
    member x.Length =
        let sqr x = x * x
        sqrt(sqr(x.X1 - x.X2) + sqr(x.Y1 - x.Y2) )
end

//Using Two Constructor

type Car = class
    val used: bool
    val owner: string
    val mutable mileage: int

    new (owner) = 
        {used=false;owner=owner;mileage=0}
    new (owner, mileage) = 
        {used=true;owner=owner;mileage=mileage}

end

(*
Differences Between Implicit and Explicit Syntaxes
As you've probably guessed, the major difference between the two syntaxes is related to the constructor: 
the explicit syntax forces a programmer to provide explicit constructor(s), whereas the implicit syntax fuses the primary constructor with the class body. 
However, there are a few other subtle differences:

1) The explicit syntax does not allow programmers to declare let and do bindings.
2) Even though you can use val fields in the implicit syntax, they must have the attribute [<DefaultValue>] and be mutable. 
    It is more convenient to use let bindings in this case. You can add public member accessors when they need to be public.
3) In the implicit syntax, the primary constructor parameters are visible throughout the whole class body. By using this feature, 
    you do not need to write code that copies constructor parameters to instance members.
4) While both syntaxes support multiple constructors, when you declare additional constructors with the implicit syntax, 
    they must call the primary constructor. In the explicit syntax all constructors are declared with new() and 
    there is no primary constructor that needs to be referenced from others.
*)

//Class Inference
(*
F#'s #light syntax allows programmers to omit the class and end keywords in class definitions, 
a feature commonly referred to as class inference or type kind inference
*)

type Product(make : string, model : string) =
    member x.Make = make
    member x.Model = model

type Consumer(make : string, model : string) = class    
    member x.Make = make
    member x.Model = model
end

//Class Member
//Instance and Static Member
type SomeClass(prop : int) = class
    member x.Prop = prop //Instance
    static member SomeStaticMethod = "This is a static method" //Static
end

type SomeClass_New(prop : int) = class
    member x.Prop = prop
    static member SomeStaticMethod = "This is a static method"
    static member Copy (source : SomeClass_New) = new SomeClass_New(source.Prop)
end

let instance = new SomeClass_New(10)
let shallowCopy = instance
let deepCopy = SomeClass_New.Copy instance

System.Object.ReferenceEquals(instance, shallowCopy)
System.Object.ReferenceEquals(instance, deepCopy)

(*
When should you use static methods rather than instance methods?

When the designers of the .NET framework were designing the System.String class, they had to decide where the Length method should go. 
They had the option of making the property an instance method (s.Length) or making it static (String.GetLength(s)). 
The .NET designers chose to make Length an instance method because it is an intrinsic property of strings.

On the other hand, the String class also has several static methods, including String.Concat which takes a list of string and concatenates them all together. 
Concatenating strings is instance-agnostic, its does not depend on the instance members of any particular strings.

The following general principles apply to all OO languages:

Instance members should be used to access properties intrinsic to an object, such as stringInstance.Length.
Instance methods should be used when they depend on state of a particular object instance, such as stringInstance.Contains.
Instance methods should be used when its expected that programmers will want to override the method in a derived class.
Static methods should not depend on a particular instance of an object, such as Int32.TryParse.
Static methods should return the same value as long as the inputs remain the same.
Constants, which are values that don't change for any class instance, should be declared as a static members, such as System.Boolean.TrueString.
*)

//Getter and Setter
type IntWrapper() = class
    let mutable num = 0
 
    member x.Num
        with get() = num
        and set(value) =
            if value > 10 || value < 0 then
                raise (new Exception("Values must be between 0 and 10"))
            else
                num <- value
end

//Adding Members to Records and Unions

type Line =
    { X1 : float; Y1 : float;
        X2 : float; Y2 : float }
    with    
        member x.Length =
            let sqr x = x * x
            sqrt(sqr(x.X1 - x.X2) + sqr(x.Y1 - x.Y2))
 
        member x.ShiftH amount =
            { x with X1 = x.X1 + amount; X2 = x.X2 + amount }
 
        member x.ShiftV amount =
            { x with Y1 = x.Y1 + amount; Y2 = x.Y2 + amount };;

type shape =
    | Circle of float
    | Rectangle of float * float
    | Triangle of float * float
    with
        member x.Area =
            match x with
            | Circle(r) -> Math.PI * r * r
            | Rectangle(b, h) -> b * h
            | Triangle(b, h) -> b * h / 2.0
 
        member x.Scale value =
            match x with
            | Circle(r) -> Circle(r + value)
            | Rectangle(b, h) -> Rectangle(b + value, h + value)
            | Triangle(b, h) -> Triangle(b + value, h + value);;


//Generic classes
type 'a GenericWrapper(initialVal : 'a) = class
    let mutable internalVal = initialVal
 
    member x.Value
        with get() = internalVal
        and set(value) = internalVal <- value
end

//Pattern Matching Objects
type Cat() = class
    member x.Meow() = printfn "Meow"
end
 
type Person(name : string) = class
    member x.Name = name
    member x.SayHello() = printfn "Hi, I'm %s" x.Name
end
 
type Monkey() = class
    member x.SwingFromTrees() = printfn "swinging from trees"
end
 
let handlesAnything (o : obj) =
    match o with
    | null -> printfn "<null>"
    | :? Cat as cat -> cat.Meow()
    | :? Person as person -> person.SayHello()
    | _ -> printfn "I don't recognize type '%s'" (o.GetType().Name)



