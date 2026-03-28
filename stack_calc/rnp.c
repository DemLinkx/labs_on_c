#include "rpn.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


static void set_error(RPNResult* res, RPNErrorCode code, const char* msg) {
    res->code = code;
    res->value = 0.0;
    if (msg != NULL) {
        strncpy(res->message, msg, sizeof(res->message) - 1);
        res->message[sizeof(res->message) - 1] = '\0';
    } else {
        res->message[0] = '\0';
    }
}


static int is_number(const char* token) {
    char* endptr;
    if (token == NULL || *token == '\0') {
        return 0;
    }
    strtod(token, &endptr);
    return (*endptr == '\0');
}


static int is_binary_operator(const char* token) {
    return (strcmp(token, "+") == 0 || 
            strcmp(token, "-") == 0 || 
            strcmp(token, "*") == 0 || 
            strcmp(token, "/") == 0 ||
            strcmp(token, "^") == 0 || 
            strcmp(token, "pow") == 0);
}


static int is_unary_operator(const char* token) {
    return (strcmp(token, "inv") == 0 || 
            strcmp(token, "~") == 0 ||
            strcmp(token, "neg") == 0 || 
            strcmp(token, "±") == 0);
}



static int is_function(const char* token) {
    const char* functions[] = {
        "sin", "cos", "tan", "cot", "sec", "csc",
        "sinh", "cosh", "tanh", "coth", "sech", "csch", "asin", "acos", "atan", "acot", "asec", "acsc",
        "arcsin", "arccos", "arctan","asinh", "acosh", "atanh", "acoth", "asech", "acsch",
        "arsinh", "arcosh", "artanh", "sqrt", "cbrt", "exp", "ln", "log", "log10", "log2"
    };
    
    size_t count = sizeof(functions) / sizeof(functions[0]);
    for (size_t i = 0; i < count; i++) {
        if (strcmp(token, functions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}



static int is_binary_function(const char* token) {
    return (strcmp(token, "logb") == 0);
}


static RPNErrorCode execute_binary_op(Stack* stack, const char* op) {
    double b, a;
    
    if (stack_pop(stack, &b) != 0 || stack_pop(stack, &a) != 0) {
        return RPN_ERR_STACK_UNDERFLOW;
    }
    
    double result = 0.0;
    
    if (strcmp(op, "+") == 0) {
        result = a + b;
    } else if (strcmp(op, "-") == 0) {
        result = a - b;
    } else if (strcmp(op, "*") == 0) {
        result = a * b;
    } else if (strcmp(op, "/") == 0) {
        if (b == 0.0) {
            return RPN_ERR_DIVISION_BY_ZERO;
        }
        result = a / b;
    } else if (strcmp(op, "^") == 0 || strcmp(op, "pow") == 0) {
        result = pow(a, b);
    }
    
    return (stack_push(stack, result) == 0) ? RPN_OK : RPN_ERR_MEMORY;
}



static RPNErrorCode execute_unary_op(Stack* stack, const char* op) {
    double a;
    
    if (stack_pop(stack, &a) != 0) {
        return RPN_ERR_STACK_UNDERFLOW;
    }
    
    double result = 0.0;
    
    if (strcmp(op, "inv") == 0 || strcmp(op, "~") == 0) {
        if (a == 0.0) {
            return RPN_ERR_DIVISION_BY_ZERO;
        }
        result = 1.0 / a;
    } else if (strcmp(op, "neg") == 0 || strcmp(op, "±") == 0) {
        result = -a;
    }
    
    return (stack_push(stack, result) == 0) ? RPN_OK : RPN_ERR_MEMORY;
}


static RPNErrorCode execute_function(Stack* stack, const char* func) {
    double a;
    
    if (stack_pop(stack, &a) != 0) {
        return RPN_ERR_STACK_UNDERFLOW;
    }
    
    double result = 0.0;
    
    if (strcmp(func, "sin") == 0) {
        result = sin(a);
    } else if (strcmp(func, "cos") == 0) {
        result = cos(a);
    } else if (strcmp(func, "tan") == 0) {
        result = tan(a);
    } else if (strcmp(func, "cot") == 0) {
        if (sin(a) == 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = 1.0 / tan(a);
    } else if (strcmp(func, "sec") == 0) {
        if (cos(a) == 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = 1.0 / cos(a);
    } else if (strcmp(func, "csc") == 0) {
        if (sin(a) == 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = 1.0 / sin(a);
    }
    else if (strcmp(func, "sinh") == 0) {
        result = sinh(a);
    } else if (strcmp(func, "cosh") == 0) {
        result = cosh(a);
    } else if (strcmp(func, "tanh") == 0) {
        result = tanh(a);
    } else if (strcmp(func, "coth") == 0) {
        if (sinh(a) == 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = 1.0 / tanh(a);
    } else if (strcmp(func, "sech") == 0) {
        result = 1.0 / cosh(a);
    } else if (strcmp(func, "csch") == 0) {
        if (sinh(a) == 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = 1.0 / sinh(a);
    }
    else if (strcmp(func, "asin") == 0 || strcmp(func, "arcsin") == 0) {
        if (a < -1.0 || a > 1.0) return RPN_ERR_INVALID_ARGUMENT;
        result = asin(a);
    } else if (strcmp(func, "acos") == 0 || strcmp(func, "arccos") == 0) {
        if (a < -1.0 || a > 1.0) return RPN_ERR_INVALID_ARGUMENT;
        result = acos(a);
    } else if (strcmp(func, "atan") == 0 || strcmp(func, "arctan") == 0) {
        result = atan(a);
    } else if (strcmp(func, "acot") == 0) {
        result = M_PI_2 - atan(a);
    } else if (strcmp(func, "asec") == 0) {
        if (a < -1.0 || a > 1.0) return RPN_ERR_INVALID_ARGUMENT;
        result = acos(1.0 / a);
    } else if (strcmp(func, "acsc") == 0) {
        if (a < -1.0 || a > 1.0) return RPN_ERR_INVALID_ARGUMENT;
        result = asin(1.0 / a);
    }
    else if (strcmp(func, "asinh") == 0 || strcmp(func, "arsinh") == 0) {
        result = asinh(a);
    } else if (strcmp(func, "acosh") == 0 || strcmp(func, "arcosh") == 0) {
        if (a < 1.0) return RPN_ERR_INVALID_ARGUMENT;
        result = acosh(a);
    } else if (strcmp(func, "atanh") == 0 || strcmp(func, "artanh") == 0) {
        if (a <= -1.0 || a >= 1.0) return RPN_ERR_INVALID_ARGUMENT;
        result = atanh(a);
    } else if (strcmp(func, "acoth") == 0) {
        if (a <= -1.0 || a >= 1.0) return RPN_ERR_INVALID_ARGUMENT;
        result = atanh(1.0 / a);
    } else if (strcmp(func, "asech") == 0) {
        if (a <= 0.0 || a > 1.0) return RPN_ERR_INVALID_ARGUMENT;
        result = acosh(1.0 / a);
    } else if (strcmp(func, "acsch") == 0) {
        if (a == 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = asinh(1.0 / a);
    }
    else if (strcmp(func, "sqrt") == 0) {
        if (a < 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = sqrt(a);
    } else if (strcmp(func, "cbrt") == 0) {
        result = cbrt(a);
    } else if (strcmp(func, "exp") == 0) {
        result = exp(a);
    }
    else if (strcmp(func, "ln") == 0) {
        if (a <= 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = log(a);
    } else if (strcmp(func, "log") == 0 || strcmp(func, "log10") == 0) {
        if (a <= 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = log10(a);
    } else if (strcmp(func, "log2") == 0) {
        if (a <= 0.0) return RPN_ERR_INVALID_ARGUMENT;
        result = log2(a);
    }
    else {
        return RPN_ERR_INVALID_OPERATOR;
    }
    
    return (stack_push(stack, result) == 0) ? RPN_OK : RPN_ERR_MEMORY;
}


static RPNErrorCode execute_binary_function(Stack* stack, const char* func) {
    double base, value;
    
    if (stack_pop(stack, &base) != 0) {
        return RPN_ERR_STACK_UNDERFLOW;
    }
    
    if (stack_pop(stack, &value) != 0) {
        return RPN_ERR_STACK_UNDERFLOW;
    }
    
    if (strcmp(func, "logb") == 0) {
        if (value <= 0.0) return RPN_ERR_INVALID_ARGUMENT;
        if (base <= 0.0 || base == 1.0) return RPN_ERR_INVALID_ARGUMENT;
        
        double result = log(value) / log(base);
        return (stack_push(stack, result) == 0) ? RPN_OK : RPN_ERR_MEMORY;
    }
    
    return RPN_ERR_INVALID_OPERATOR;
}

const char* rpn_get_error_string(RPNErrorCode code) {
    switch (code) {
        case RPN_OK:
            return "Успешно";
        case RPN_ERR_STACK_UNDERFLOW:
            return "Недостаток операндов";
        case RPN_ERR_STACK_OVERFLOW:
            return "Недостаток операций (лишние операнды в стеке)";
        case RPN_ERR_INVALID_NUMBER:
            return "Неверный формат числа";
        case RPN_ERR_INVALID_OPERATOR:
            return "Неизвестная операция или функция";
        case RPN_ERR_DIVISION_BY_ZERO:
            return "Деление на ноль";
        case RPN_ERR_INVALID_ARGUMENT:
            return "Недопустимый аргумент функции";
        case RPN_ERR_MEMORY:
            return "Ошибка выделения памяти";
        default:
            return "Неизвестная ошибка";
    }
}

RPNResult rpn_calculate(const char* expression) {
    RPNResult result;
    result.code = RPN_OK;
    result.value = 0.0;
    result.message[0] = '\0';
    
    if (expression == NULL) {
        set_error(&result, RPN_ERR_INVALID_OPERATOR, "Пустое выражение (NULL)");
        return result;
    }
    
    Stack* stack = stack_create();
    if (stack == NULL) {
        set_error(&result, RPN_ERR_MEMORY, "Не удалось создать стек");
        return result;
    }
    
    char* expr_copy = strdup(expression);
    if (expr_copy == NULL) {
        stack_free(stack);
        set_error(&result, RPN_ERR_MEMORY, "Не удалось выделить память");
        return result;
    }
    
    char* token = strtok(expr_copy, " \t\n\r");
    
    while (token != NULL) {
        RPNErrorCode error = RPN_OK;
        
        if (is_number(token)) {
            if (stack_push(stack, strtod(token, NULL)) != 0) {
                error = RPN_ERR_MEMORY;
            }
        }
        else if (is_binary_operator(token)) {
            error = execute_binary_op(stack, token);
        }
        else if (is_unary_operator(token)) {
            error = execute_unary_op(stack, token);
        }
        else if (is_function(token)) {
            error = execute_function(stack, token);
        }
        else if (is_binary_function(token)) {
            error = execute_binary_function(stack, token);
        }
        else {
            set_error(&result, RPN_ERR_INVALID_OPERATOR, token);
            break;
        }
        
        if (error != RPN_OK) {
            set_error(&result, error, NULL);
            break;
        }
        
        token = strtok(NULL, " \t\n\r");
    }
    
    if (result.code == RPN_OK) {
        if (stack_size(stack) == 1) {
            stack_pop(stack, &result.value);
        } else if (stack_size(stack) > 1) {
            set_error(&result, RPN_ERR_STACK_OVERFLOW, NULL);
        } else {
            set_error(&result, RPN_ERR_STACK_UNDERFLOW, "Пустое выражение");
        }
    }
    
    free(expr_copy);
    stack_free(stack);
    
    if (result.code != RPN_OK && result.message[0] == '\0') {
        const char* msg = rpn_get_error_string(result.code);
        strncpy(result.message, msg, sizeof(result.message) - 1);
    }
    
    return result;
}