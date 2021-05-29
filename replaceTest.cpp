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

#define DEBUG_TYPE "replaceTest"
#define LITTLE_NAME "replaceTest"
#define CLASS_NAME "ReplaceTest"


using namespace llvm;

namespace {

struct ReplaceTest : public llvm::FunctionPass {
  static char ID; 
  bool flag;

  ReplaceTest() : FunctionPass(ID) {}

  ReplaceTest(bool flag) : FunctionPass(ID) {
    this->flag = flag;
  }

  bool runOnFunction(llvm::Function &F);
  bool replaceTest(llvm::Function *f);
};
}

char ReplaceTest::ID = 0;
static llvm::RegisterPass<ReplaceTest> X("replacetest", "replacetest pass");
//Pass *llvm::createSubstitution(bool flag) { return new Substitution(flag); }

bool ReplaceTest::runOnFunction(llvm::Function &F) {
  llvm::Function *tmp = &F;
  replaceTest(tmp);  
  return true;
}

bool ReplaceTest::replaceTest(llvm::Function *f) {
  llvm::Function *tmp = f;

  for (Function::iterator bb = tmp->begin(); bb != tmp->end(); ++bb) {
    for (BasicBlock::iterator inst = bb->begin(); inst != bb->end(); ++inst) {
        llvm::Instruction* ii = &*inst;
        Type *ty = inst->getType();

        if (inst->isBinaryOp()){
          llvm::Value* value0 = inst->getOperand(0);
          llvm::Value* value1 = inst->getOperand(1);


          ConstantInt *co = (ConstantInt *)ConstantInt::get(ty, 100);
          BinaryOperator *op = BinaryOperator::Create(Instruction::Add, value0 , co, "", value0);


        }


    }                  // End for basickblock
  }                    // End for Function
  return false;
} 