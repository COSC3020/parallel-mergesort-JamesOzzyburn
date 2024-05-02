[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/Dt3ukIt2)
# Parallel Mergesort

Implement a parallel version of mergesort (both the original recursive and the
iterative in-place version from a previous exercise are fine). You may use any
parallelization framework or method.

I have not provided any test code, but you can base yours on test code from
other exercises. Your tests must check the correctness of the result of running
the function and run automatically when you commit through a GitHub action.

## Runtime Analysis

What is the span of the parallel program, in terms of worst-case $\Theta$? Hint:
It may help to consider the DAG of the parallel program.


## Answer
I believe that the span of this program is $\Theta(n*log(n))$. I believe this because for $log(n)$ that is the depth of recursion, and we can only half it $log(n)$ times until we get to just one element. For $n$ that is the merging part as it takes $n$ to merge all the smaller arrays up. This also makes sense intuitively as we are still doing the same amount of work as "regular" merge sort but just giving it extra threads. We aren't somehow doing less work or more (I mean we do have more overhead when using threads but asymptotically speaking we are not).
