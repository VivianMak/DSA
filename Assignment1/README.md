# Assignment 1

## Translating Your Old Code

Choose a piece of code that you’ve written in a programming language other than C++. Translate the code to run in C++. For simplicity, you may want to choose some code that will not require interacting with a lot of external libraries (although the course how-to discusses how to add dependencies to your project)

The code you produce should be documented and contain at least some unit tests.

> Turning in your work: Include a link to a GitHub repo containing your port of the code. Include a writeup that describes the purpose of the code and how you found the process of translating the code to Kotlin (or the language you wind up choosing). Feel free to touch on the good, the bad, and the ugly.

## Implementing Meeting Scheduler

Implement an algorithm that determines whether a collection of meetings contains a conflict (as we discussed in the [day 1](../in_class/day01) page).

It's up to you how you pass data into your program.  You could read it from a file, hard code a test input into your main function, etc.

* First implement the straightforward algorithm that checks pairs of meetings.
* Develop a second algorithm that sorts the meetings in a useful way so you can check for conflicts more easily.  You should not implement your own search function, but instead use your language's built-in sort function.
* Write unit tests for both implementations, including edge cases such as one meeting ending exactly when another starts. For each algorithm (the straightforward one and the one based sorting), describe how you expect its running time to grow with $n$.  As mentioned on day 1, sorting has runtime $\Theta(n \log n)$.