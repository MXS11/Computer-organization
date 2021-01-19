
#include <iostream>
#include <fstream>
#include "pin.H"
using std::cerr;
using std::endl;
using std::ios;
using std::ofstream;
using std::string;

ofstream OutFile;

// Define the variables
static UINT64 memoryInstcount = 0;
static UINT64 total = 0;
static UINT64 branchInstcount = 0;
static UINT64 arithInstcount = 0;

// Count for every instruction that occurs
VOID findbranchcount() { branchInstcount++; }
VOID findmemorycount() { memoryInstcount++; }
VOID findtotalcount() { total++; }

// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{

    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)findtotalcount, IARG_END);
    UINT32 memOperands = INS_MemoryOperandCount(ins);
    // add 1 for each memory operand. 

    if (INS_IsBranch(ins))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)findbranchcount, IARG_END);
    }
    for (UINT32 memOp = 0; memOp < memOperands; memOp++)
    {

        if (INS_MemoryOperandIsWritten(ins, memOp) || INS_MemoryOperandIsRead(ins, memOp))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)findmemorycount, IARG_END);
        }
    }
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
                            "o", "results.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    arithInstcount = total - (branchInstcount + memoryInstcount);
    // Execute and print the tasks 
    OutFile.setf(ios::showbase);
    OutFile << "Task1\nThe total Count of macroinstructions and microinstructions is:  "
            << total << endl;
    OutFile << "\nTask2 " << endl;
    OutFile << "Branch Instructions Count is: " << branchInstcount << endl;
    OutFile << "Memory Instructions is: " << memoryInstcount << endl;
    OutFile << "Arithmetic and Logic Instructions Count is: " << total - (branchInstcount + memoryInstcount) << endl;
    OutFile << "Ratio of branch instructions: " << (double)branchInstcount /(double)total << endl;
    OutFile << "Ratio of memory instructions: " << (double)memoryInstcount /(double)total << endl;
    OutFile << "Ratio of arithmetic instructions: " << (double)arithInstcount /(double)total << endl;



    OutFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool counts the number of dynamic instructions executed" << endl;
    cerr << endl
         << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv))
        return Usage();

    OutFile.open(KnobOutputFile.Value().c_str());

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}
