**Binary Instrumentation with PIN**

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
