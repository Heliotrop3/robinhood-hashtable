# Robin Hood Hash Table

The scope of this project was to become familiar with C, learn how a hash table works, and finally implement one. 

## Description

This is a key-value open addressing hash table utilizing Robin Hood hashing.

Robin Hood hashing involves assigning a real number in the range \[0,∞) to each hashed Item. This number is called the Probe Sequence Length (PSL) and represents the Item's shift from its optimal position in the array. An Item's optimal position is determined by where the hash function wants to place the item vs where the array can store the item. For example, an Item with a PSL of 0 is optimally hashed - it's location in the array means when its key is looked up it'll be the first Item the lookup method encounters. In contrast, an Item with a PSL of 3 is stored 3 indices away from its optimal hash - a lookup method will need to examine 3 indices before finding what it's looking for.

TODO: Finish explanation


### Dependencies

- The code was written on a Fedora Linux 35 (Workstation Edition) on Linux kernel version 6.0.11-100.fc35.x86_64
- #DEFINE _GNU_SOURCE is included in hashtable.h - <b><i><ins>this won't run on Windows</ins></i></b>
- The [Unity testing framework](https://github.com/ThrowTheSwitch/Unity) is used - and included in this repo - for the unit tests 

### Installing
USE AT YOUR OWN RISK - The Author, Maintainer, and/or Owner are not responsible for the consequences of using this code.

The CMake is... well, it's rough. My primary motivation for using CMake was to simplify building the unit test(s). To this end, it's functional, but if you want to use this as a library it'll need some extra love. I specifically avoided trying to [install](https://cmake.org/cmake/help/latest/command/install.html) via CMake as I didn't want to mess up the VM and need to reset it (I hadn't pushed anything to GitHub when writing the code - a fear I have overcome). As I'm typing this, I'm realizing that's a terrible reason and will look into creating a check point on the VM.

Regardless, until I have a reason to revisit the installation process, it'll stay in its current questionable state.

## Help

The good Lord helps those who help themselves... or something like that. Look, don't come to me for help on installing. This is a personal project and not something meant to be used in a production environment. If choosing to use this in any capacity, you do so at your own risk and with the understanding the Author, Maintainer, and/or Repo Owner are not responsible for the consequences of your decision to use this code. Should that not discourage you, then you should treat this for what it is - code that hasn't been hardened or battle-tested and probably has bugs I haven't caught.

## Resources/Acknowledgements

[Here](https://cs.uwaterloo.ca/research/tr/1986/CS-86-14.pdf) is a great research paper delving into the CS aspects of Robin Hood hashing.

[This](https://programming.guide/robin-hood-hashing.html) gives a cliff-notes overview.
