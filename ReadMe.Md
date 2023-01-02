# ScopeTimer

This is a scope timer in c++, which measures the time it takes for a scope to finish in Nano-seconds & CPU cycles. 
Very straightforward and easy code, which uses the chrono library.

## How it works ?

It has only one class (Timer).
You need to instantiate it in the scope and it will print the time when the program goes out of that certain scope.

Syntax:
{
Timer TimeIt;
Function();
}
