#include "../include/astnode.hpp"

ASTNode::ASTNode(const std::string &repr)
    : repr_(repr)
    , lhs_{nullptr}
    , rhs_{nullptr} {}

ASTNode::ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs)
    : repr_(repr)
    , lhs_{lhs}
    , rhs_{rhs} {}

ASTNode::~ASTNode() {
    delete lhs_;
    delete rhs_;
}

void ASTNode::print(std::ostream &out) const { inner_print(out, 0); }

void ASTNode::inner_print(std::ostream &out, size_t indent) const {
    
    if (lhs_) {
        lhs_->inner_print(out, indent + 1);
    }
    for (size_t i = 0; i < indent; ++i) {
        out << "    ";
    }
    out << repr_ << '\n';
    if (rhs_) {
        rhs_->inner_print(out, indent + 1);
    }
}

Number::Number(const int& val)
        : ASTNode(std::to_string(val))
        , val_(val) {}

int Number::value() const { return val_; };

Variable::Variable(const std::string &var)
        : ASTNode(std::string(var))
        , var_(var) {}

std::string Variable::variable() const { return var_; };

Operator::Operator(const std::string &oper, ASTNode *lhs, ASTNode *rhs)
        : ASTNode(std::string(oper), lhs, rhs)
        , oper_(oper)
        , lhs_{lhs}
        , rhs_{rhs} {}

std::string Operator::oper() const { return oper_; };
