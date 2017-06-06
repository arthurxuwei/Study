(*
Operator overloading allows programmers to provide new behavior for the default operators in F#. 
In practice, programmers overload operators to provide a simplified syntax for objects which can be combined mathematically.
*)

type Complex = 
    {
        Re:double
        Im:double
    }
    static member (+) (left: Complex, right: Complex) = 
        {
            Re = left.Re + right.Re;
            Im = left.Im + right.Im
        }

let first = {Re = 1.0; Im = 7.0}
let second = {Re = 2.0; Im= -2.0}

first + second

(*
In addition to overloading existing operators, its possible to define new operators. 
The names of custom operators can only be one or more of the following characters:
!%&*+-./<=>?@^|~
F# supports two types of operators: infix operators and prefix operators.
*)

