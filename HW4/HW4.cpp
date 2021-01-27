#include <iostream>
#include <fstream>
#include "pin.H"
using std::cerr;
using std::endl;
using std::ios;
using std::ofstream;
using std::string;

ofstream OutFile;


static UINT64 S = 0;
static UINT64 S2 = 0;
static UINT64 S3 = 0;
static UINT64 S4 = 0;
static UINT64 S5 = 0;
static UINT64 S6 = 0;
static UINT64 S7 = 0;
static UINT64 S8 = 0;
static UINT64 S9 = 0;
static UINT64 S10 = 0;
static UINT64 S11 = 0;
static UINT64 S12 = 0;
static UINT64 S13 = 0;
static UINT64 S14 = 0;
static UINT64 S15 = 0;
static UINT64 S16 = 0;
static UINT32 CountmemOP = 0;
static UINT32 CountReadOp = 0;


VOID Instruction(INS ins, VOID *v)
{

    // Iterate over each memory operand of the instruction.
    if (INS_RegWContain(ins, REG_RAX))
    {
        S++;
    }
    if (INS_RegWContain(ins, REG_RBX))
    {
        S2++;
    }

    if (INS_RegWContain(ins, REG_RCX))
    {
        S3++;
    }
    if (INS_RegWContain(ins, REG_RDX))
    {
        S4++;
    }
    if (INS_RegWContain(ins, REG_RSI))
    {
        S5++;
    }
    if (INS_RegWContain(ins, REG_RDI))
    {
        S6++;
    }
    if (INS_RegWContain(ins, REG_RSP))
    {
        S7++;
    }
    if (INS_RegWContain(ins, REG_RBP))
    {
        S8++;
    }
    if (INS_RegWContain(ins, REG_R8))
    {
        S9++;
    }
    if (INS_RegWContain(ins, REG_R9))
    {
        S10++;
    }
    if (INS_RegWContain(ins, REG_R10))
    {
        S11++;
    }
    if (INS_RegWContain(ins, REG_R11))
    {   
        S12++;
    }
    if (INS_RegWContain(ins, REG_R12))
    {
        S13++;
    }
    if (INS_RegWContain(ins, REG_R13))
    {
        S14++;
    }
    if (INS_RegWContain(ins, REG_R14))
    {
        S15++;
    }
    if (INS_RegWContain(ins, REG_R15))
    {
        S16++;
    }

    
UINT32 memOperands = INS_MemoryOperandCount(ins);
    // Iterate over each memory operand of the instruction.
    for (UINT32 memOp = 0; memOp < memOperands; memOp++)
    {
        CountmemOP++;
        //Checking if MemOp is for read
        if (INS_MemoryOperandIsRead(ins, memOp))
        {
            CountReadOp++;
        }

    }

}
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
                            "o", "results.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    // Write to a file since cout and cerr maybe closed by the application
    OutFile.setf(ios::showbase);

    OutFile << "Task2 " << endl;
    OutFile << "Total size of the memory operations: " << CountmemOP << endl;
    OutFile << "The ratio of the read operations is: " << (double)CountReadOp/(double)CountmemOP << endl;
   


    OutFile << "\nTask3 " << endl;
    OutFile << "Frequency Of RAX " << S << endl;
    OutFile << "Frequency Of RBX " << S2 << endl;
    OutFile << "Frequency Of RCX " << S3 << endl;
    OutFile << "Frequency Of RDX " << S4 << endl;
    OutFile << "Frequency Of RSI " << S5 << endl;
    OutFile << "Frequency Of RDI " << S6 << endl;
    OutFile << "Frequency Of RSP " << S7 << endl;
    OutFile << "Frequency Of RBP " << S8 << endl;
    OutFile << "Frequency Of R8 " << S9 << endl;
    OutFile << "Frequency Of R9 " << S10 << endl;
    OutFile << "Frequency Of R10 " << S11 << endl;
    OutFile << "Frequency Of R11 " << S12 << endl;
    OutFile << "Frequency Of R12 " << S13 << endl;
    OutFile << "Frequency Of R13 " << S14 << endl;
    OutFile << "Frequency Of R14 " << S15 << endl;
    OutFile << "Frequency Of R15 " << S16 << endl;

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