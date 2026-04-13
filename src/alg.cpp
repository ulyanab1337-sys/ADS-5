// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int getPriority(char op) {
    switch (op) {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
        default: return -1;
    }
}

std::string infx2pstfx(const std::string& inf) {
    Tstack<char, 100> stack;
    std::string output;
    
    for (size_t i = 0; i < inf.length(); ++i) {
        char ch = inf[i];
        
        if (isdigit(ch)) {
            // собираем число целиком
            while (i < inf.length() && isdigit(inf[i])) {
                output += inf[i];
                ++i;
            }
            output += ' ';
            --i; // коррекция индекса после цикла
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                output += stack.pop();
                output += ' ';
            }
            if (!stack.isEmpty()) stack.pop(); // убираем '('
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!stack.isEmpty() && getPriority(stack.get()) >= getPriority(ch)) {
                output += stack.pop();
                output += ' ';
            }
            stack.push(ch);
        }
    }
    
    while (!stack.isEmpty()) {
        output += stack.pop();
        output += ' ';
    }
    
    // удаляем последний лишний пробел, если он есть
    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }
    
    return output;
}

int eval(const std::string& post) {
    Tstack<int, 100> stack;
    
    for (size_t i = 0; i < post.length(); ++i) {
        char ch = post[i];
        
        if (isdigit(ch)) {
            int num = 0;
            while (i < post.length() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            stack.push(num);
            --i;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int right = stack.pop();
            int left = stack.pop();
            int result = 0;
            
            switch (ch) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/': result = left / right; break;
            }
            stack.push(result);
        }
    }
    
    return stack.pop();
}
