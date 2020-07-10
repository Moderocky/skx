//
// Created by liz3 on 29/06/2020.
//

#include "../include/Variable.h"
#include "../include/utils.h"
#include "../include/types/TBoolean.h"
#include "../include/types/TString.h"
#include "../include/types/TNumber.h"
#include "../include/types/TCharacter.h"
#include "../include/types/TArray.h"


void skx::Variable::createVarFromOption(std::string item, skx::Context *targetContext, bool isStatic) {
    auto start = item.find_first_of(':') + 1;
    std::string name = skx::Utils::trim(item.substr(0, start - 1));
    std::string value = skx::Utils::trim(item.substr(start, item.length() - 1));
    skx::Variable *variable = new Variable();
    if (value == "true") {
        variable->type = BOOLEAN;
        variable->value = new TBoolean(true);
        variable->value->varRef = variable;

    } else if (value == "false") {
        variable->type = BOOLEAN;
        variable->value = new TBoolean(false);
        variable->value->varRef = variable;
    } else {
        variable->type = STRING;
        variable->value = new TString(value);
        variable->value->varRef = variable;

    }
    variable->ctx = targetContext;
    variable->name = name;
    variable->accessType = STATIC;
    targetContext->vars[name] = variable;
}

skx::VariableDescriptor *skx::Variable::extractNameSafe(std::string in) {
    auto *descriptor = new VariableDescriptor();
    descriptor->isFromContext = in[0] == '%' && in[in.length()-1] == '%';
    auto trim = in.substr(1, in.length() - 2);
    if (trim.rfind('@', 0) == 0) {
        descriptor->type = STATIC;
        trim = trim.substr(1);
    } else if (trim.rfind('_', 0) == 0) {
        descriptor->type = CONTEXT;
        trim = trim.substr(1);
    } else {
        descriptor->type = descriptor->isFromContext ? CONTEXT : GLOBAL;
    }
    descriptor->name = trim;
    return descriptor;
}

skx::Variable::~Variable() {
    if (value != nullptr && !created) {
        switch (type) {
            case STRING: {
                auto *val = dynamic_cast<TString*>(value);

                delete val;
                break;
            }
            case NUMBER: {
                auto *val = dynamic_cast<TNumber*>(value);
                delete val;
                break;
            }
            case CHARACTER: {
                auto *val = dynamic_cast<TCharacter*>(value);
                delete val;
                break;
            }
            case BOOLEAN: {
                auto *val = dynamic_cast<TBoolean*>(value);
                delete val;
                break;
            }
            default:
                break;
        }
    }
    value = nullptr;
}

void skx::Variable::createVarValue(VarType type, Variable* target, bool isDouble) {
    target->type = type;
    switch (type) {
        case STRING:
            target->value = new TString();
            break;
        case NUMBER: {
            TNumber* v = new TNumber();
            v->isDouble = isDouble;
            target->value = v;
        }
            break;
        case ARRAY:
            target->value = new TArray();
            break;
        case CHARACTER:
            target->value = new TCharacter();
            break;
        case BOOLEAN:
            target->value = new TBoolean();
            break;
        default:
            break;
    }
}

bool skx::VariableValue::isEqual(skx::VariableValue *other) {
    return false;
}

bool skx::VariableValue::isSmaller(skx::VariableValue *other) {
    return false;
}

bool skx::VariableValue::isBigger(skx::VariableValue *other) {
    return false;
}

bool skx::VariableValue::isSmallerOrEquals(skx::VariableValue *other) {
    return false;
}

bool skx::VariableValue::isBiggerOrEquals(skx::VariableValue *other) {
    return false;
}

bool skx::VariableValue::assign(skx::VariableValue *source) {
    return false;
}

bool skx::VariableValue::subtract(skx::VariableValue *source) {
    return false;
}

bool skx::VariableValue::add(skx::VariableValue *source) {
    return false;
}

bool skx::VariableValue::multiply(skx::VariableValue *source) {
    return false;
}

bool skx::VariableValue::divide(skx::VariableValue *source) {
    return false;
}
