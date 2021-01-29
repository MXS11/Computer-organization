# Binary Instrumentation with PIN

Definition: In this homework, you are going to do some experiments with X68 ISA, which is the instruction set in your computers.

For this task, you will use [PIN Binary Instrumentation Tool.](https://software.intel.com/en-us/articles/pin-a-dynamic-binary-instrumentation-tool )

PIN allows you to collect runtime information about any application compiled and running on an X86 computer. 

In this homework, you will instrument simple factorial application both for iterative and recursive versions. 
You can get the code from [here.](https://www.javatpoint.com/factorial-program-in-c) 

- Task1: Measure the accuracy of branch prediction. How many of the branches are predicted correctly?

- Task2: Measure the total size of memory operations. Also, among memory operations, measure the ratio of read operations. 

- Task 3: Here is the list of registers and their purposes in X86. 

    - RAX: Accumulator

    - RBX: Base index (for use with arrays)

    - RCX: Counter (for use with loops and strings)

    - RDX: Extend the precision of the accumulator

    - RSI: Source index for string operations.

    - RDI: Destination index for string operations.

    - RSP: Stack pointer for top address of the stack.

    - RBP: Stack base pointer for holding the address of the current stack frame.

    - R8-R15: general purposed registers

Calculate the frequency of usage of each register as a destination register. 

# Solutions

### Setting up the PIN tool
After downloading the PIN tool, we have to apply the following command in order to provide Ubuntu with the path of the PIN tool.
```
set INTEL_JIT_PROFILER /home/user/Downloads/pin-3.17-98314-g0c048d619-gcc-linux/intel64/lib/libpinjitprofiling.so
```
We change our directory to the tools file inside the PIN tool.
```
Cd /Downloads/pin-3.17-98314-g0c048d619-gcc-linux/source/tools/ManualExamples$
```
Inside the ManualExample file, we add our c++ code **hw4.cpp** then, we create a folder obj-intel64 and put the factorial code inside it. Then, we run the c code using ```gcc RecFact.c``` then we execute the code using ```./a.out```

We put in a number and we get a new file ```a.out```

We move the file from obj-intel64 to the ManualExample file. After that, we will use the following command to execute our C++ code in order to count the instructions.
```
make hw4.test
```

Moreover, we will then execute our instruction c++ code on the ```a.out``` file that we got from the factorial using the command

```
../../../pin -t obj-intel64/hw4.so -- ./a.out
```

Using this command will perform the count of the instructions and then it will give us a file that has the results of our calculations called ```results.out.```
