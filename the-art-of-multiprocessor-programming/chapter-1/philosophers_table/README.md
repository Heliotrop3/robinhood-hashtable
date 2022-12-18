# Philosophers Dining Problem

The *dining philosophers problem* was invented by [E.W Dijkstra](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra) to clarify the notions of [deadlock-](https://en.wikipedia.org/wiki/Deadlock) and [starvation-](https://csrc.nist.gov/glossary/term/resource_starvation) freedom.

## Problem Description

Imagine five Philosophers who spend their lives thinking and feasting on rice. They sit around a circular table with 5 chopsticks. <sup>Originally it was forks but who double fists forks?</sup> Each Philosopher thinks and when they get hungry they pick up the two chopsticks nearest their seat. If said chopsticks are available then the Philosopher feasts for a while. Once they have finished eating they place the chopsticks down and resume thinking.

## Solve for the Following

- Write a program to simulate the behaviour of the Philosophers, where each Philosopher is a thread and the chopsticks are shared objects. Note that you must prevent a situation where two Philosophers hold the same chopstick at the same time.

- Amend your solution such that it never reaches a state where the Philosophers are deadlocked - your solution should never reach a state where each Philosopher holds one chopstick and is stuck waiting for another to acquire the second chopstick.

- Amend your solution such that no Philosopher ever starves

- Write a starvation-free solution for *n* Philosophers for any Natural number *n*.
