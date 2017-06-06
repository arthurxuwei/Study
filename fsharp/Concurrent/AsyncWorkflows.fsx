//Async Workflows
(*
Async workflows are defined using computation expression notation:

async { comp-exprs }

Here's an example using fsi:

> let asyncAdd x y = async { return x + y };;
 
val asyncAdd : int -> int -> Async<int>
Notice the return type of asyncAdd. It does not actually run a function; instead, it returns an async<int>, which is a special kind of wrapper around our function.

*)

//Async Module

//RunSynchronously
//Parallel
//Start

let extractLinks url = 
    async {
        let webClient = new System.Net.WebClient()

        printfn "Downloading %s" url
        let html = webClient.DownloadString(url:string)
        printfn "Got %i bytes" html.Length
        let matches = System.Text.RegularExpressions.Regex.Matches(html, @"http://\S+")
        printfn "Got %i links" matches.Count

        return url, matches.Count
    }

Async.RunSynchronously(extractLinks "http://www.msn.com/")


//Concurrency with Functional Programming
(*

To put it bluntly, mutable state is enemy of multithreaded code. 
Functional programming often simplifies multithreading tremendously: 
since values are immutable by default, programmers don't need to worry about one thread mutating the value of shared state between two threads, 
so it eliminates a whole class of multithreading bugs related to race conditions. 
Since there are no race conditions, there's no reason to use locks either, so immutability eliminates another whole class of bugs related to deadlocks as well.

*)