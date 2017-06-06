(*Discriminated unions, also called tagged unions, represent a finite, well-defined set of choices. 
Discriminated unions are often the tool of choice for building up more complicated data structures including linked lists and a wide range of trees.*)

type switchstate =
    | On
    | Off

let x = On
let y = Off

//Pattern Matching DU
let toggle = function
    | On -> Off
    | Off -> On

//Holding Data In Unions: a dimmer switch

type switchstate_dimmer =
    | On
    | Off
    | Adjustable of float

let toggle_dimmer = function
    | On -> Off
    | Off -> On
    | Adjustable(brightness) ->
    (* Matches any switchstate of type Adjustable. Binds
        the value passed into the constructor to the variable
        'brightness'. Toggles dimness around the halfway point. *)
        let pivot = 0.5
        if brightness <= pivot then
            Adjustable(brightness + pivot)
        else
            Adjustable(brightness - pivot)

let x_dimmer = On
let y_dimmer = Off
let z_dimmer = Adjustable(0.25)

//create tree
type tree = 
    | Leaf of int
    | Node of tree * tree

let simpleTree = 
    Node (
        Leaf 1,
        Node (
            Leaf 2,
            Node (
                Node (
                    Leaf 4,
                    Leaf 5
                ),
                Leaf 3
            )
        )
    )

let countLeaves tree =
    let rec loop sum = function
        | Leaf(_) -> sum + 1
        | Node(tree1, tree2) ->
            sum + (loop 0 tree1) + (loop 0 tree2)
    loop 0 tree

//Propositional Logic
type proposition =
    | True
    | Not of proposition
    | And of proposition * proposition
    | Or of proposition * proposition

let prop1 =
    (* ~t || ~~t *)
    Or(
        Not True,
        Not (Not True)
    )
 
let prop2 =
    (* ~(t && ~t) || ( (t || t) || ~t) *)
    Or(
        Not(
            And(
                True,
                Not True
            )
        ),
        Or(
            Or(
                True,
                True
            ),
            Not True
        )
    )
 
let prop3 = 
    (* ~~~~~~~t *)
    Not(Not(Not(Not(Not(Not(Not True))))))
 
let rec eval = function
    | True -> true
    | Not(prop) -> not (eval(prop))
    | And(prop1, prop2) -> eval(prop1) && eval(prop2)
    | Or(prop1, prop2) -> eval(prop1) || eval(prop2)

let testProp name prop = printfn "%s: %b" name (eval prop)
 
testProp "prop1" prop1
testProp "prop2" prop2
testProp "prop3" prop3