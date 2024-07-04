# Robin Hood Hash Table

The scope of this project was to become familiar with C, learn how a hash table works, and finally implement one. 

## Description

This is a key-value open addressing hash table utilizing Robin Hood hashing.

Robin Hood hashing involves assigning a real number in the range \[0,∞) to each hashed Item. This number is called the Probe Sequence Length (PSL) and represents an Item's shift from its optimal position in the array. For example, an Item with a PSL of 0 is optimally hashed - it's location in the array will be the first item found on lookup. In contrast, an Item with a PSL of 3 is stored 3 indices away from its optimal hash - a lookup method will need to examine 3 indices before finding the desired value.

The idea of optimal location is important when talking about removing an Item. The algorithm for removing an item involves iterating backwards and moving entries forward by one index until an optimally hashed item is encountered. Improving the position of poorly indexed entries is central to the namesake "Robin Hood Hashing" 

### Dependencies

- The code was written on a Fedora Linux 35 (Workstation Edition) on Linux kernel version 6.0.11-100.fc35.x86_64
- #DEFINE _GNU_SOURCE is included in hashtable.h - <b><i><ins>this won't run on Windows</ins></i></b>
- The [Unity testing framework](https://github.com/ThrowTheSwitch/Unity) is used - and included in this repo - for the unit tests 

### Installing
USE AT YOUR OWN RISK - The Author, Maintainer, and/or Owner are not responsible for the consequences of using this code.

The CMake is... rough. I wanted to learn CMake to simplify building the unit test(s). To this end, it's functional, but if you seriously want to use this as a library please reconsider. The goal of this project was to create a personal string key hashtable in C to familiarize myself with C, CMake, and unit-testing in C. Should that not discourage you, then you should treat this for what it is - code that passes Valgrind but that hasn't been hardened or battle-tested


## Help

The good Lord helps those who help themselves - you're on your own. This is a personal project and not something meant for widespread consumption.

## Resources/Acknowledgements

[Here](https://cs.uwaterloo.ca/research/tr/1986/CS-86-14.pdf) is a great research paper delving into the CS aspects of Robin Hood hashing.

[This](https://programming.guide/robin-hood-hashing.html) gives a cliff-notes overview.
