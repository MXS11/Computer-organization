# Binary Instrumentation with PIN

Definition: In this homework, you are going to do some experiments with X68 ISA, which is the instruction set in your computers.

For this task, you will use [PIN Binary Instrumentation Tool.](https://software.intel.com/en-us/articles/pin-a-dynamic-binary-instrumentation-tool )

PIN allows you to collect runtime information about any application compiled and running on an X86 computer. 

In this homework, you will instrument simple factorial application both for iterative and recursive versions. 
You can get the code from [here.](https://www.javatpoint.com/factorial-program-in-c) 

This homework is to warm up the usage of PIN. In the next homework, you will do more experiments in PIN. 

- Task1: Count the total number of macroinstructions and microinstructions in the application. 

- Task2: In the ISAs, there are three classes of machine instructions: 

       -  Memory Instructions (ie. Loads and Stores)
       
       -  Branch Instructions (ie. Jumps, Branches etc.)
       
       -  Arithmetic and Logic Instructions (ie. Add, Sub, Mul, Div, Shift, And, Or etc.)
       
     Count the number of instructions in each class and find their ratio. 

# **Solutions**

### Setting up the PIN tool
After downloading the PIN tool, we have to apply the following command in order to provide Ubuntu with the path of the PIN tool.
```
set INTEL_JIT_PROFILER /home/user/Downloads/pin-3.17-98314-g0c048d619-gcc-linux/intel64/lib/libpinjitprofiling.so
```
We change our directory to the tools file inside the PIN tool.
```
Cd /Downloads/pin-3.17-98314-g0c048d619-gcc-linux/source/tools/ManualExamples
```
Inside the ManualExample file, we add our c++ code **sy.cpp** then, we create a folder obj-intel64 and put the factorial code inside it. Then, we run the c code using ```gcc RecFact.c``` then we execute the code using ```./a.out```

We put in a number and we get a new file ```a.out```

We move the file from obj-intel64 to the ManualExample file. After that, we will use the following command to execute our C++ code in order to count the instructions.
```
make sy.test
```

Moreover, we will then execute our instruction c++ code on the ```a.out``` file that we got from the factorial using the command

```
../../../pin -t obj-intel64/sy.so -- ./a.out
```

Using this command will perform the count of the instructions and then it will give us a file that has the results of our calculations called ```results.out```
