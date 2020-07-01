//
// Created by liz3 on 29/06/2020.
//

#ifndef SKX_FUNCTION_H
#define SKX_FUNCTION_H

#include "Variable.h"
#include "Step.h"
#include "PreParser.h"
#include "TreeCompiler.h"
#include "Context.h"
#include "utils.h"
#include <vector>
#include <string>

namespace skx {
    struct ReturnOpWithCtx {
        Context* ctx;
        ReturnOperation* descriptor;
    };
    class Function {
    private:
        ReturnOpWithCtx* walk(CompileItem* item);
    public:
        std::string name;
        std::vector<VariableDescriptor*> targetParams;
        Variable* run(std::vector<Variable*> execVars);
        CompileItem* functionItem;
        VarType returnType = UNDEFINED;

    };
}

#endif //SKX_FUNCTION_H