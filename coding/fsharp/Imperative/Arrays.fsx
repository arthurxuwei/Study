//Arrays
[|1;2;3;4;5|]

[|1..10|]

[|for a in 1..10 do yield a, a*2|]

//System.Array Methods
let (x:int array) = Array.zeroCreate 5

Array.create 5 "0"

Array.init 5 (fun index -> sprintf "index: %i" index)

let names = [| "Juliet"; "Monique"; "Rachelle"; "Tara"; "Sophia" |]

names.[0]
names.Length

names.[0] <- "Arthur"

names;;

//Slicing
names.[1..3]
names.[..3]
names.[1..]

//Differences Between Arrays and Lists
(*
Lists
Symbol thumbs up.svg Immutable, allows new lists to share nodes with other lists.
Symbol thumbs up.svg List literals.
Symbol thumbs up.svg Pattern matching.
Symbol thumbs up.svg Supports mapping and folding.
Symbol thumbs down.svg Linear lookup time.
Symbol thumbs down.svg No random access to elements, just "forward-only" traversal.
Arrays
Symbol thumbs up.svg Array literals.
Symbol thumbs up.svg Constant lookup time.
Symbol thumbs up.svg Good spacial locality of reference ensures efficient lookup time.
Symbol thumbs up.svg Indexes indicate the position of each element relative to others, making arrays ideal for random access.
Symbol thumbs up.svg Supports mapping and folding.
Symbol thumbs down.svg Mutability prevents arrays from sharing nodes with other elements in an array.
Symbol thumbs down.svg Not resizable.
*)