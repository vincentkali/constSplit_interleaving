//#include "llvm/Transforms/Obfuscation/Substitution.h"
//#include "Substitution.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/ADT/Statistic.h"
//#include "llvm/Transforms/Obfuscation/Utils.h"
//#include "Utils.h"
#include "llvm/IR/Intrinsics.h"

//#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
//#include "llvm/CryptoUtils.h"

#include "llvm/IR/InstrTypes.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>

#define DEBUG_TYPE "testfunction"

using namespace llvm;

namespace {

struct TestFunction : public llvm::FunctionPass {
  static char ID; 
  bool flag;

  TestFunction() : FunctionPass(ID) {}

  TestFunction(bool flag) : FunctionPass(ID) {
    this->flag = flag;
  }

  bool runOnFunction(llvm::Function &F);
  bool testfunction(llvm::Function *f);
};
}

Instruction::BinaryOps convert(unsigned bopCode);

char TestFunction::ID = 0;
static llvm::RegisterPass<TestFunction> X("testfunction", "testfunction pass");
//Pass *llvm::createSubstitution(bool flag) { return new Substitution(flag); }

bool TestFunction::runOnFunction(llvm::Function &F) {
  llvm::Function *tmp = &F;
  testfunction(tmp);  
  return true;
}

bool TestFunction::testfunction(llvm::Function *f) {
  llvm::Function *tmp = f;

  for (Function::iterator bb = tmp->begin(); bb != tmp->end(); ++bb) {
    for (BasicBlock::iterator inst_out = bb->begin(); inst_out != bb->end(); ++inst_out) {
      llvm::Instruction* ii = &*inst_out;
      llvm::Value *vv = &*ii;
      /*
      if(isa<LoadInst>(inst_out)){
        errs() << "Load: \n";
        errs() << (Value*)&*inst_out << "\n";
        errs() << (Value*)(inst_out->getOperand(0)) << "\n";
      }
      
      if(isa<StoreInst>(inst_out)){
        errs() << "Store: \n";
        errs() << (Value*)&*inst_out << "\n";
        errs() << (Value*)(inst_out->getOperand(0)) << "\n";
      }
      */

      /*
      Value* val = cast<Value>(alloca_x);
      Value::use_iterator sUse = val->use_begin();
      Value::use_iterator sEnd = val->use_end();
      for (; sUse != sEnd; ++sUse) {
          if(isa<LoadInst>(sUse)) // load inst
          else if(isa<StoreInst>(sUse)) // store inst
      }
      */
    }                  // End for basickblock inst_out
  }                    // End for Function
  return false;
}