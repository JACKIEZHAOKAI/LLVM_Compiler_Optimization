//Basic code required
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"   
#include "llvm/IR/InstIterator.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <string>

using namespace llvm;
using namespace std;

namespace {
struct CountStaticInstructions : public FunctionPass {  
  // This declares a CountStaticInstructions class that is a subclass of FunctionPass. 
  // FunctionPass operates on a function at a time.
  static char ID;
  CountStaticInstructions() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    //This declares pass identifier used by LLVM to identify pass. 
    //This allows LLVM to avoid using expensive C++ runtime information.
    map<string, int> counter; // map OpCodeName to freq

    // step 1: Iterating over the Instruction in a Function and add to counter map
    // F is a pointer to a Function instance
    for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I){
      //errs() << *I << "\n";
      string name((*I).getOpcodeName());  //OR getOpcode()
      counter[name]++;  
    }

    // step 2: iterate the counter map and output
    for(auto it = counter.begin() ; it != counter.end() ; it++){
      // output format: errs() << "Hello: ";  OR  errs().write_escaped(F.getName()) << '\n';
      errs() << (it->first) << "\t" << it->second << "\n";  // OR mapCodeToName()
    }

    return false;    
  }
}; // end of struct TestPass
}  // end of anonymous namespace

char CountStaticInstructions::ID = 0; //initialize pass ID here. LLVM uses ID’s address to identify a pass, so initialization value is not important.
static RegisterPass<CountStaticInstructions> X("cse231-csi", "counts the number of each unique instruction in a function statically",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
// we register our class CountStaticInstructions, giving it a command line argument “cse231-csi”, and a name "xxx”. 