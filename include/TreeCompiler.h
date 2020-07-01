//
// Created by liz3 on 30/06/2020.
//

#ifndef SKX_TREECOMPILER_H
#define SKX_TREECOMPILER_H

#include "Context.h"
#include "Instruction.h"
#include "PreParser.h"
#include <vector>

namespace skx {
    class CompileItem {
    public:
        uint16_t level = 0;
        uint32_t line = 0;
        Context* ctx;
        CompileItem* parent;
        std::vector<CompileItem*> children;
        std::vector<Comparison*> comparisons;
        std::vector<Assigment*> assignments;
        std::vector<Trigger*> triggers;
        std::vector<Execution*> executions;

        //item flags
        bool isElseIf = false;
        bool isElse = false;
        ReturnOperation* returner; // this is specific to functions ofc
    };

    class TreeCompiler {
    public:
        static CompileItem* compileTree(PreParserItem* item, Context* ctx);
        static CompileItem* compileTreeFunction(PreParserItem* item, Context* ctx);

    private:
        void compileExpression(PreParserItem* item, Context* context, CompileItem* target);
        void advance(CompileItem* parent, PreParserItem* parentItem, bool isFuncSuperContext = false);
        void compileCondition(std::string& content, Context* ctx, CompileItem* target, bool isElseIf = false);

        void compileAssigment(std::string basicString, Context *pContext, CompileItem *pItem);
        void compileExecution(std::string& basicString, Context *pContext, CompileItem *pItem);
        void setupFunctionMeta(std::string& content, Function* target);
    };
}


#endif //SKX_TREECOMPILER_H