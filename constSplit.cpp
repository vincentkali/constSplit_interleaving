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

#define DEBUG_TYPE "constsplit"

using namespace llvm;

namespace {

struct ConstSplit : public llvm::FunctionPass {
  static char ID; 
  bool flag;

  ConstSplit() : FunctionPass(ID) {}

  ConstSplit(bool flag) : FunctionPass(ID) {
    this->flag = flag;
  }

  bool runOnFunction(llvm::Function &F);
  bool constSplit(llvm::Function *f);
};
}

char ConstSplit::ID = 0;
static llvm::RegisterPass<ConstSplit> X("constsplit", "constant split pass");
//Pass *llvm::createSubstitution(bool flag) { return new Substitution(flag); }

bool ConstSplit::runOnFunction(llvm::Function &F) {
  llvm::Function *tmp = &F;
  constSplit(tmp);  
  return true;
}

bool ConstSplit::constSplit(llvm::Function *f) {
  llvm::Function *tmp = f;

  for (Function::iterator bb = tmp->begin(); bb != tmp->end(); ++bb) {
    for (BasicBlock::iterator inst = bb->begin(); inst != bb->end(); ++inst) {
        llvm::Instruction* ii = &*inst;
        //errs() << *ii << "\n\n";
        if (inst->isBinaryOp()){
          llvm::Value* value0 = inst->getOperand(0);
          llvm::Value* value1 = inst->getOperand(1);

          //llvm::Type* type0 = value0->getType();
          //llvm::Type* type1 = value1->getType();



          if (isa_impl<Constant, Value>::doit(*value0)){ // left side
            /////////////modify//////////////////////
            // a = 2 + b
            //-----------------
            // a = (2+r) + b
            // a = (-r) + a
            llvm::ConstantInt* CI = dyn_cast<llvm::ConstantInt>(value0);

            int constValue = *(CI->getValue().getRawData()); // get constValue
            
            
            BinaryOperator *op = NULL;
            Type *ty = inst->getType();
            
            ConstantInt *co = (ConstantInt *)ConstantInt::get(ty, constValue + 100);
            op = BinaryOperator::Create(Instruction::Add, co,inst->getOperand(1), "", ii);  // a = (2+r) + b

            co = (ConstantInt *)ConstantInt::get(ty, -100);
            ii->setOperand(0,co);
            ii->setOperand(1,op); // a = (-r) + a
            continue;
          }

          if (isa_impl<Constant, Value>::doit(*value1)){ // right side
            /////////////modify//////////////////////
            // a = b + 2
            //-----------------
            // a = b + (2+r)
            // a = a + (-r)
            llvm::ConstantInt* CI = dyn_cast<llvm::ConstantInt>(value1);

            int constValue = *(CI->getValue().getRawData()); // get constValue
            
            
            BinaryOperator *op = NULL;
            Type *ty = inst->getType();
            
            ConstantInt *co = (ConstantInt *)ConstantInt::get(ty, constValue + 100);
            op = BinaryOperator::Create(Instruction::Add, inst->getOperand(0), co, "", ii);  // a = b + (2+r)

            co = (ConstantInt *)ConstantInt::get(ty, -100);
            ii->setOperand(1,co);
            ii->setOperand(0,op); // a = a + (-r)
            continue;
          }

        }


    }                  // End for basickblock
  }                    // End for Function
  return false;
} 