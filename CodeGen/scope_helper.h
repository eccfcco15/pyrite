#ifndef SCOPE_HELPER_H
#define SCOPE_HELPER_H

#include <map>
#include "llvm/IR/Value.h"

class ScopeNode
{
    public:
        enum class ScopeType
        {
            TOP_SCOPE,
            FUNC_SCOPE,
            SIMPLE_SCOPE,
        };
        ScopeNode(ScopeType scopeType,
                ScopeNode* parent = nullptr, 
                std::map<std::string, 
                        std::tuple<uint64_t, 
                        llvm::Value*>*>* namedVals = nullptr);

        ~ScopeNode();
        ScopeNode* getParent();
        void setParent(ScopeNode* parent);
        void setNamedVal(std::string name, llvm::Value* value, uint64_t index);
        llvm::Value* getNamedVal(std::string name);
        uint64_t getNamedValInd(std::string name);
        void setBlock(llvm::BasicBlock* block);
        bool isVoidReturn();
        void setFuncScopeRetVoid(bool isVoid);
        ScopeType getScopeType();
        uint64_t getNumNamedVarsInScope();
        void incFuncNamedVars();
    private:
        //namedVals: key = var name, 
        //value = tuple(order in which named val was created, val)
        std::map<std::string, std::tuple<uint64_t, llvm::Value*>*>* namedVals;
        ScopeNode* parent;
        llvm::BasicBlock* block;
        ScopeType scopeType;
        bool funcScopeRetVoid;
        uint64_t numNamedVarsInScope;
};

class ScopeHelper
{
    public:
       ScopeHelper(); 
       ~ScopeHelper(); 
       void pushScope(ScopeNode::ScopeType scopeType, bool funcScopeRetVoid=false);
       void popScope();
       void setNamedVal(std::string name, llvm::Value* value, bool isDecl);
       llvm::Value* getNamedVal(std::string name, bool walkScopes);
       uint64_t getNamedValInd(std::string name);
       void setBlockOnCurrScope(llvm::BasicBlock* block);
       //getNearestScopeOfType returns nullptr if no scope of appropriate type is found
       ScopeNode* getNearestScopeOfType(ScopeNode::ScopeType scopeType);
       bool parentFuncReturnsVoid();
       void setParentFuncReturnsVoid(bool isVoid);
       //getNumNamedVarsSince: 
       //returns number of named variables that have been declared starting
       //from the nearest scope of 'scopeType'
       uint64_t getNumNamedVarsSinceFunc();
       void incFuncNamedVars();
    private:
        ScopeNode* parentScope;
        ScopeNode* currScope;
};

#endif
