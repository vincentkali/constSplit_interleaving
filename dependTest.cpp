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

#include "llvm/IR/Use.h"
#include "llvm/Analysis/DependenceAnalysis.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

#define DEBUG_TYPE "dependTest"
#define LITTLE_NAME "dependTest"
#define CLASS_NAME "DependTest"


using namespace llvm;

namespace {

struct DependTest : public llvm::FunctionPass {
  static char ID; 
  bool flag;

  DependTest() : FunctionPass(ID) {}

  DependTest(bool flag) : FunctionPass(ID) {
    this->flag = flag;
  }

  bool runOnFunction(llvm::Function &F);
  bool dependTest(llvm::Function *f);
};
}

char DependTest::ID = 0;
static llvm::RegisterPass<DependTest> X("replacetest", "replacetest pass");
//Pass *llvm::createSubstitution(bool flag) { return new Substitution(flag); }

bool DependTest::runOnFunction(llvm::Function &F) {
  llvm::Function *tmp = &F;
  dependTest(tmp);  
  return true;
}

bool DependTest::dependTest(llvm::Function *f) {
  llvm::Function *tmp = f;

  for (Function::iterator bb = tmp->begin(); bb != tmp->end(); ++bb) {
    for (BasicBlock::iterator inst = bb->begin(); inst != bb->end(); ++inst) {
        llvm::Instruction* ii = &*inst; 
        Type *ty = inst->getType();

        if (inst->isBinaryOp()){ // c
          llvm::Value* value0 = inst->getOperand(0); // a
          llvm::Value* value1 = inst->getOperand(1); // a
          if (value1 == value0){
            errs() << "Same\n";
          }
        }


    }                  // End for basickblock
  }                    // End for Function
  return false;
} 