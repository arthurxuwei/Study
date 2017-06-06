(*
Most programmers coming from a C#, Java, or C++ background are familiar with an imperative style of programming 
which uses loops, mutable data, and functions with side-effects in applications. 
    While F# primarily encourages the use of a functional programming style, 
it has constructs which allow programmers to write code in a more imperative 
style as well. Imperative programming can be useful in the following situations:

    Interacting with many objects in the .NET Framework, most of which are inherently imperative.
    Interacting with components that depend heavily on side-effects, such as GUIs, I/O, and sockets.
    Scripting and prototyping snippets of code.
    Initializing complex data structures.
    Optimizing blocks of code where an imperative version of an algorithm is more efficient than the functional version.
*)

//if/then/elif/else
(* simple if *)
if expr then
    expr
 
(* binary if *)
if expr then
    expr
else
    expr
 
(* multiple else branches *)
if expr then
    expr
elif expr then
    expr
elif expr then
    expr
...
else
    expr
//for
for var = start-expr to end-expr do
    ... // loop body

for pattern in expr do
    ... // loop body

//while
while expr do
    ... // loop body

