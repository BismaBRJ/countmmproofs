# countmmproofs

The first version of this program, as well as this README file, was started and completed on a Saturday, 16 November 2024.

TL;DR:

- `countmmproofs` is a very simple C program to (over)estimate the number of proofs in a given Metamath database file (`.mm`), really by counting occurrences of `$=`

- How to use: after compiling `countmmproofs.c`, the syntax is

    ```
    ./countmmproofs the_metamath_database.mm
    ```

    The program will then estimate the number of proofs in that file and then print out the result.

## What is Metamath?

Metamath is a proof language, which is a computer language with which one can type logical proofs (including mathematical proofs) and let a "proof verifier" check whether the proofs are valid. The relatively simple syntax of Metamath means that proof verifiers are relatively easy to create, compared to [other proof languages](https://en.wikipedia.org/wiki/Proof_assistant).

At the time of writing this README file, files written in the Metamath proof language usually end in the `.mm` file extension, and are called Metamath databases (even though they are really just ASCII text files, not some sort of DBMS format), since they usually contain a (possibly huge) collection of proofs. You can learn more about Metamath

- at the official website: <https://us.metamath.org/>

- by reading the free, public domain Metamath book at <https://us.metamath.org/downloads/metamath.pdf> or accessing it via its GitHub repository <https://github.com/metamath/metamath-book>

- by reading or even joining the Metamath mailing list at Google Groups: <http://groups.google.com/group/metamath>

## What is this `countmmproofs` thing?

The average proof in the Metamath language is written with the following syntax:

```metamath
theorem_name $= step1 step2 ... last_step $.
```

There are other ways, such as the compressed proof format. Regardless, all ways separate the theorem name and the proof data with the `$=` token (as far as I know, from reading the Metamath book).

Thus, the number of proofs in a Metamath database can be (over)estimated by simply counting the number of occurrences of the `$=` token.

I say overestimate, because who knows, some of those `$=` occurrences are actually inside a comment, and therefore technically aren't actually proofs that are checked by any proof verifier (also called proof checker) for the Metamath language.

(Yes, the Metamath language has some support for writing comments.)

## Why C?

I first wrote this program in about two hours for the mere purpose of estimating the number of proofs in `set.mm` (GitHub repository: <https://github.com/metamath/set.mm>), which, at the time of writing this README file,

- is the largest existing Metamath database,

- is almost 50 MB in size (keep in mind that it's really just an ASCII text file!),

- aims to construct (all of?) mathematics from scratch, starting from the very foundations of set theory: the ZFC set theory axioms (so we can expect it to get even larger over time!)

At the time of writing this README file, Python is usually my go-to scripting language for use cases as small as this. However, given the size of `set.mm`, I really need as much speed as I can get. The only low level programming language I know well enough to do this kind of thing is C, and, guessing it would be faster than Python, I decided to go with C. (Why not Rust? I simply haven't learned it. One day I might.)

I especially appreciate C's simple I/O interface that can read one ASCII character (really, one byte) at a time using the `fgetc` function, so the program doesn't have to first load in the entire text file before reading from it.

I quickly wrote up a really simple, linear time algorithm--that is, an algorithm of O(n) time complexity (n being the number of bytes in the given Metamath database)--to count the number of occurrences of the `$=` substring in the entire Metamath database.

The result? In about four seconds (on my machine), it found exactly 43565 occurrences of the `$=` token (in the `set.mm` file in the [2813f8eb3a62e829c4c7afea58513c2d77d4c98f](https://www.github.com/metamath/set.mm/commit/2813f8eb3a62e829c4c7afea58513c2d77d4c98f) commit of the `set.mm` repository), so that's my (over)estimate for the number proofs in `set.mm` at that time. (Honestly, that is quite slow already. I wonder how long a Python program would take!)

And that's how this repo came about. I figured that others could benefit from these lines of code somehow.

## So how do I use this thing?

You need to compile the C code first before using it.

1. Make sure you have a compiler for the C programming language installed on your computer, such as GCC.

2. Download the `countmmproofs.c` file, either by clicking on it on this GitHub page (<https://github.com/BismaBRJ/countmmproofs/>) and then clicking the download button, or by cloning this GitHub repository (if you have git installed) such as by opening a command prompt or terminal and running the following:

    ```
    git clone https://github.com/BismaBRJ/countmmproofs/
    ```

3. Navigate to the folder where you've just downloaded that `countmmproofs.c` file.

4. Make sure to have a command prompt or terminal open **at that same folder.**

5. Using the terminal, compile that `countmmproofs.c` file. For example, if you're using GCC, you can try to run the following:

    ```
    gcc countmmproofs.c -o countmmproofs
    ```

    (You might need to add `.exe` for that second `countmmproofs` if you're on Windows.)

    The `countmmproofs` executable (or `countmmproofs.exe` if you're on Windows) should show up afterwards.

6. Put your Metamath database file there (feel free to copy it in rather than actually moving it there; do it however you see fit) that you want to use this program on.

7. Still on a terminal **on that folder** (open another terminal if you closed it already), run

    ```
    ./countmmproofs the_metamath_database.mm
    ```

    (Again, you might need to add `.exe` for that `countmmproofs` if you're on Windows.)

    Of course, replace `the_metamath_database.mm` with the name of your Metamath database file.

    The program will then estimate the number of proofs in that file and then print out the result.

**Note:**

- If you want to try it on another Metamath database file, you only need to repeat steps 6 and 7 using that other Metamath database.

- If this repository or software gets updated somehow and you'd like to update the one on your machine, you'd have to redo all the steps from the beginning.

I may or may not update this thing from time to time. I have a feeling that the file format for Metamath databases might change quite significantly one day, after stumbling accross this post on the Google Groups maling list, about modularity: <https://groups.google.com/g/metamath/c/ZlRle52FVO0/m/35ZVNUFQBwAJ>

Either way, enjoy!
