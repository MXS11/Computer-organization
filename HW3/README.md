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

# Setting up the PIN tool

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

# Results

### First task

In first task, we find the number of the total instruction we have. We start by defining total variable that will count each time it counts an instruction.

```VOID findtotalcount() { total++; }```

Our ```findtotalcount``` method will be called by this method.

```INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)findtotalcount, IARG_END);```

### Second task

1. We define if statements in order to find the requested instructions such branch instruction, memory instructions, and arithmetic instructions.

```
if (INS_IsBranch(ins)) {
INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)dobranchcount, IARG_END);
}
for (UINT32 memOp = 0; memOp < memOperands; memOp++){
if (INS_MemoryOperandIsWritten(ins,memOp) || INS_MemoryOperandIsRead(ins,memOp)) {
INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)domemcount, IARG_END);
}
}
```

2. Then, we define the required variables for each type of instructions.
```
static UINT64 memoryInstcount = 0;

static UINT64 total = 0;

static UINT64 branchInstcount = 0;

static UINT64 arithInstcount = 0;
```

3. After getting the branch count and memory count, we just subtract them from the total instruction count to get the value of the arithmetic instruction count.

```
arithInstcount = total - (branchInstcount + memoryInstcount);
```
We call our variables and print the results

```
    OutFile << "\nTask2 " << endl;
    OutFile << "Branch Instructions Count is: " << branchInstcount << endl;
    OutFile << "Memory Instructions is: " << memoryInstcount << endl;
    OutFile << "Arithmetic and Logic Instructions Count is: " << total - (branchInstcount + memoryInstcount) << endl;
    OutFile << "Ratio of branch instructions: " << (double)branchInstcount /(double)total << endl;
    OutFile << "Ratio of memory instructions: " << (double)memoryInstcount /(double)total << endl;
    OutFile << "Ratio of arithmetic instructions: " << (double)arithInstcount /(double)total << endl;
```
