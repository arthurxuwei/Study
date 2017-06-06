//Tuples
let average (a, b) =
    (a + b) / 2.0

let scalarMultiply (s : float) (a, b, c) = 
    (a * s, b * s, c * s);;
scalarMultiply 5.0 (6.0, 11.0, 0.5);;

let swap(a, b) =
    (b, a);;
swap ("web", 2.0);;

let divrem x y =
    match y with
    | 0 -> None
    | _ -> Some(x / y, x % y);;
divrem 100 20;;

//Pattern Match Tuples
let greeting (name, language) = 
    match (name, language) with 
    | ("Steve", _) -> "Howdy, Steve"
    | (name, "English") -> "Hello, " + name
    | (name, _) when language.StartsWith("Span") -> "Hola, " + name
    | (_, "French") -> "Bonjour!"
    | _ -> "DOES NOT COMPUTE"

greeting ("Steve", "English");;
greeting ("Pierre", "French");;
greeting ("Maria", "Spanish");;
greeting ("Rocko", "Esperanto");;

fst (0, 1);;
snd (1, 10);;

let x, y = (1, 2);;

//Records
type website = {
    Title: string;
    Url: string
}

let homepage = { Title = "Google"; Url = "http://www.google.com"};;
//var homepage : website
homepage.Title;;
homepage.Url;;

//cloning record
type coord = {X:float; Y:float}
let setX item newX =
    { item with X = newX }
let start = {X=10.0; Y=2.0}
let finish = setX start 5.0


//Pattern Matching Records
type coords = {X:float; Y:float}
let getQuadrant = function
    | {X = 0.0; Y = 0.0} -> "Origin"
    | item when item.X >=0.0 && item.Y >=0.0 -> "I"
    | item when item.X <= 0.0 && item.Y >= 0.0 -> "II"
    | item when item.X <= 0.0 && item.Y <= 0.0 -> "III"
    | item when item.X >= 0.0 && item.Y <= 0.0 -> "IV"

let testCoords (x, y) = 
    let item = {X = x; Y = y}
    printfn "(%f, %f) is in quadrant %s" x y (getQuadrant item)

testCoords(0.0, 0.0)
testCoords(1.0, 1.0)
testCoords(-1.0, 1.0)
testCoords(-1.0, -1.0)
testCoords(1.0, -1.0)

