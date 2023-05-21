#include "../include/parser.hpp"

using Token = Lexer::Token;

ASTNode *Parser::parse() { return expr(); }

void Parser::next_token() { tok_ = lexer_.next_token(); }

ASTNode *Parser::expr() {
    // parse addition and subsctruction
    ASTNode *root = term();
    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            std::string op = lexer_.get_operator();
            if (op.front()== '+' || op.front()== '-') {
                root = new Operator(op, root, term());
                break;
            }
            return root;
            break;
        }
        default:
            return root;
        }
    }
}

ASTNode *Parser::term() {
    // parse multiplication and division
    ASTNode *root = prim();
    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            std::string op = lexer_.get_operator();
            if (op.front()== '*' || op.front()== '/') {
                root = new Operator(op, root, prim());
                break;
            }
            return root;
            break;
        }
        default:
            return root;
        }
    }
}

ASTNode *Parser::prim() {
    // parse numbers and names
    ASTNode *node = nullptr;
    next_token();
    switch (tok_) {
    case Token::Number:
        node = new Number(lexer_.get_number());
        break;
    case Token::Name:
        node = new Variable(lexer_.get_name());
        break;
    default:
        break;
    }
    next_token();
    return node;
}