As part of this question, we want to implement a simple plagiarism checker that checks code files. We want to design a checker to compare two codes at a time (hence accuracy matters).
In order to avoid complicating things for this project, we have already written a parsing code that generates
a stream of integer tokens from a C++ file which is given to your functions.

You will be provided two submissions, both of which are vectors of integers. Each integer is a token. Conse-
quently, both submissions are collections of tokens in order that form the respective code after being parsed.

# How to run your code

We will be relying heavily on the famous clang compiler, as well as on the LLVM toolchain, for the parsing of
code files into streams of tokens. We (and the LLVM devs) have done the tokenizing, but you should be able
to run your code (which relies on that) on your machine.

Since the behaviour of the tokenizing library could depend on the execution environment, we chose to switch
from running the it natively on the machine, to running it on a docker container that is provided alongwith
the other files. Ensure that docker is installed on your machine and that it works.

## Steps to run:
1. Install docker on your machine
2. Inside the plag-checker folder run: docker buildx build ./ -t plag_checker
3. After build is complete, run: docker run -rm -it -v .:.plag_checker plag_checker
4. Now inside the container, go to the /plag_checker/phase1 folder and run make


# What kind of matching patterns should you detect?
Firstly, a pattern is a series of numbers in a particular order. The order matters as code without
order (unless you’re talking pure functional programming – even then, the order of tokens matters) is not of
any use. You need to look for matching subsequences between the two sequences of tokens.

There is no point looking for sequences of length 1 since there are only a few individual tokens, and
there are bound to be a lot of matches. 

The same holds for matches of very short length. For short patterns
(10-20 tokens each), you need to look for accurate matches – all tokens are to be identical in the same order.

For larger patterns (above 30 tokens each), look for approximate matches: you are to consider two patterns as
matches if there exists a subsequence of at least 80% the length of the longer of the two. This automatically
implies that the patterns that are matched should roughly be of the same length.
# Output Format
You are to report five values in order, which gives the caller an idea of the degree of match between the two
code files and the most significant match.

1. The zeroth return value is a flag that is 1 if the two submissions are flagged as plagiarised, and 0 otherwise
2. The first value should be the total length (number of tokens) of all pattern matches detected, of lengths 10-20. Longer pattern matches will count as multiple pattern matches, but that doesn’t matter
since you report the total length.

3. The second value should be the length of the longest approximate pattern match that you were able to
detect. Look only at long pattern matches (30 or higher tokens); return zero otherwise.
4. The third and fourth values are the start indices of the pattern you found above in the first and second
files, respectively (start index of the pattern in either vector of tokens).

## NOTE

Ensure that in the first value, you do not double-count patterns, i.e., all patterns caught should be present as
accurate matches in both files, and no two of them should overlap in either file. This not only takes care of
direct/global plagiarism but also of patchwork plagiarism – when the offender copies lots of sections from the
other work and intertwines them with original content.

Looking for approximate matches as well (for the longest match) ensures that additions/modifications of a few
statements are still caught (variants of paraphrasing plagiarism), and the very fact that you look at tokens and
not code files directly ensures that merely changing of variable names does not evade your detector.

For the flag (zeroth value), try to be as accurate as possible. Ensure that your code correctly identifies pairs of
files that are plagiarized and those that are not. You are free to decide the threshold for the number of short
and approximate pattern matches that should be caught for a pair of files to be flagged as plagiarised, but
ensure that it is reasonable and avoids too many false positives and negatives.

# Your task
You are supposed to modify and submit only the file `match submissions.hpp`, implementing the provided
method match submissions provided, and return an `std::array<int, 5>`, containing whatever is mentioned
above. 

Do not write print, read/write file or log statements.

Write code as efficiently as you can since some submissions (a few thousand tokens) will take a long time. 

It is okay if you miss some small pattern matches or if values slightly differ from expected. 
# Make Commands

```
make             # Build and Run Tests
make build       # Build
make runtests    # Run Tests
make clean       # Clean Temporary Files
```
Please read Makefile to understand the above commands!

# VS Code interface

You can open this folder in VS Code. The problem folder is configured 
to enable debugging.

After opening the folder, click on Run > Start Debugging or press F5.
This will run your program on input ./test/test1/input.txt.
You may place breakpoints to pause the program at any desired location.

You can modify "./.vscode/launch.json" to run any test of your choice.

In some labs, there may be multiple binaries, and you may need to modify 
the binary name in the ./.vscode/settings.json file.

```
    "problem": "<binary>",
```

# General Instructions

- Read all .h and .cpp files before starting.
- Do not include any additional header files.
- Do not modify files other than the specified files. Any other changes 
  will not be considered during evaluation.
- You are expected to submit an efficient implementation. Inefficient 
  solutions will lose marks.

