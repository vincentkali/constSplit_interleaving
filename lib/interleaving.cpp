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

#define DEBUG_TYPE "interleaving"

using namespace llvm;

namespace {

struct Interleaving : public llvm::FunctionPass {
  static char ID; 
  bool flag;

  Interleaving() : FunctionPass(ID) {}

  Interleaving(bool flag) : FunctionPass(ID) {
    this->flag = flag;
  }

  bool runOnFunction(llvm::Function &F);
  bool interleaving(llvm::Function *f);
};
}

Instruction::BinaryOps convert(unsigned bopCode);

char Interleaving::ID = 0;
static llvm::RegisterPass<Interleaving> X("interleaving", "interleaving pass");
//Pass *llvm::createSubstitution(bool flag) { return new Substitution(flag); }

bool Interleaving::runOnFunction(llvm::Function &F) {
  llvm::Function *tmp = &F;
  interleaving(tmp);  
  return true;
}

bool Interleaving::interleaving(llvm::Function *f) {
  llvm::Function *tmp = f;

  for (Function::iterator bb = tmp->begin(); bb != tmp->end(); ++bb) {
    for (BasicBlock::iterator inst_out = bb->begin(); inst_out != bb->end(); ++inst_out) {
      llvm::Instruction* ii = &*inst_out;

      if (inst_out->isBinaryOp() && inst_out != bb->end()){
        llvm::Value* value0 = inst_out->getOperand(0);
        llvm::Value* value1 = inst_out->getOperand(1);
        for (BasicBlock::iterator inst_in = ++inst_out; inst_in != bb->end(); ++inst_in){
          if (inst_in->isBinaryOp()){
            if (inst_in->getOperand(0) == &*inst_out || inst_in->getOperand(1) == &*inst_out\
                      || inst_in == bb->end()){

              BinaryOperator *op = BinaryOperator::Create(convert(inst_out->getOpcode()), \
                inst_out->getOperand(0),inst_out->getOperand(1), "", &*inst_in); 
                      // put right before the cloest instruction with dependency
              inst_out->replaceAllUsesWith(op);
              errs() << "create and replace\n";
            }
          }
        }              // End for inst_in
      }                // End if  inst
    }                  // End for basickblock inst_out
  }                    // End for Function
  return false;
} 

Instruction::BinaryOps convert(unsigned bopCode){
  switch (bopCode){
    case BinaryOperator::Add:
      return Instruction::Add;

    case BinaryOperator::Sub:
      return Instruction::Sub;

    case BinaryOperator::Mul:
      return Instruction::Mul;

    case BinaryOperator::And:
      return Instruction::And;

    case BinaryOperator::Or:
      return Instruction::Or;

    case BinaryOperator::Xor:
      return Instruction::Xor;
    default:
      return Instruction::Add;
  } 
}