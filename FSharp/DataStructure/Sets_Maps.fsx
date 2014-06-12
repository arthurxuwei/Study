(*In addition to lists and sequences, F# provides two related immutable data structures called sets and maps. 
Unlike lists, sets and maps are unordered data structures, 
meaning that these collections do not preserve the order of elements as they are inserted, nor do they permit duplicates.*)

//Sets
Set.empty.Add(1).Add(2).Add(7)

Set.ofList ["Mercury"; "Venus"; "Earth"; "Mars"; "Jupiter"; "Saturn"; "Uranus"; "Neptune"]

//Maps
Map.empty.
        Add("Christmas", "Dec. 25").
        Add("Halloween", "Oct. 31").
        Add("Darwin Day", "Feb. 12").
        Add("World Vegan Day", "Nov. 1")

let monkeys = [ "Squirrel Monkey", "Simia sciureus";
        "Marmoset", "Callithrix jacchus";
        "Macaque", "Macaca mulatta";
        "Gibbon", "Hylobates lar";
        "Gorilla", "Gorilla gorilla";
        "Humans", "Homo sapiens";
        "Chimpanzee", "Pan troglodytes" ] |> Map.ofList

monkeys.["Gorilla"]