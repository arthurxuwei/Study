//subclass
type Person(name) =
    member x.Name = name
    member x.Greet() = printfn "Hi, I'm %s" x.Name

type Student(name, studentID: int) =
    inherit Person(name)

    let mutable _GPA = 0.0

    member x.StudentID = studentID
    member x.GPA
        with get() = _GPA
        and set value = _GPA <- value

type Worker(name, employer: string) = 
    inherit Person(name)

    let mutable _salary = 0.0

    member x.Employer = employer
    member x.Salary
        with get() = _salary
        and set value = _salary <- value

let somePerson, someStudent, someWorker =
    new Person("Juliet"), new Student("Monique", 123456), new Worker("Carla", "Awesome Hair Salon");;

somePerson.Name , someStudent.Name, someWorker.Name
someStudent.StudentID
someWorker.Employer

//Overriding Methods
type Person_New(name) = 
    member x.Name = name
    member x.Greet() = printfn "Hi, I'm %s" x.Name

    override x.ToString() = x.Name

type Person_New_New(name) =
    member x.Name = name   

    abstract Greet: unit -> unit
    default x.Greet() = printfn "Hi, I'm %s" x.Name

type Quebecois(name) =
    inherit Person_New_New(name)

    override x.Greet() = printfn "Bonjour, je m'appelle %s, eh." x.Name

let terrance, phillip = new Person("Terrance"), new Quebecois("Phillip")

terrance.Greet();
phillip.Greet();

//abstract class
open System

type Point = { X : int; Y : int }

[<AbstractClass>]
type Shape(position: Point) = 
    member x.Position = position
    override x.ToString() =
        sprintf "position = {%i, %i}, area = %f" position.X position.Y (x.Area())

        abstract member Draw: unit -> unit
        abstract member Area: unit -> float

type Circle(position: Point, radius: float) =
    inherit Shape(position)

    member x.Radius = radius
    override x.Draw() = printfn "(Circle)"
    override x.Area() = Math.PI * radius * radius

type Rectangle(position: Point, width: float, height: float) =
    inherit Shape(position)

    member x.Width = width
    member x.Height = height
    override x.Draw() = printfn "(Rectangle)"
    override x.Area() = width * height

type Square(position : Point, width : float) =
    inherit Shape(position)
 
    member x.Width = width
    member x.ToRectangle() = new Rectangle(position, width, width)
    override x.Draw() = printfn "(Square)"
    override x.Area() = width * width

type Triangle(position : Point, sideA : float, sideB : float, sideC : float) =
    inherit Shape(position)
 
    member x.SideA = sideA
    member x.SideB = sideB
    member x.SideC = sideC
 
    override x.Draw() = printfn "(Triangle)"
    override x.Area() =
        (* Heron's formula *)
        let a, b, c = sideA, sideB, sideC
        let s = (a + b + c) / 2.0
        Math.Sqrt(s * (s - a) * (s - b) * (s - c) )

let position = {X=0;Y=0}

let circle, rectangle, square, triangle = 
    new Circle(position, 5.0),
    new Rectangle(position, 2.0, 7.0),
    new Square(position, 10.0),
    new Triangle(position, 3.0, 4.0, 5.0)

circle.ToString()
triangle.ToString()
square.ToRectangle().ToString()
rectangle.ToString()

//Up-casting and Down-casting
let regularString = "Hello world"
let upcastString = "Hello world" :> obj
regularString.ToString()
regularString.Length

upcastString.ToString()
//upcastString.Length

let intAsObj = 20 :> obj
intAsObj, intAsObj.ToString()

let intDownCast = intAsObj :?> int
intDownCast, intDownCast.ToString()

let stringDownCast = intAsObj :?> string

