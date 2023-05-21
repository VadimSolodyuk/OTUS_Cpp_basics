// OTUS C++ basic course homework.
// ASTNode

#pragma once

#include <cctype>
#include <iostream>
#include <string>

class ASTNode {
  public:
    explicit ASTNode(const std::string &repr);

    ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs);

    ASTNode(const ASTNode &other) = delete;

    ASTNode &operator=(const ASTNode &other) = delete;

    virtual ~ASTNode();

    std::string repr() const { return repr_; }

    void print(std::ostream &out) const;

  private:
    void inner_print(std::ostream &out, size_t indent) const;

    std::string repr_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};

class Number : public ASTNode {
  public:
    Number(const int& val);
    int value() const;     

  private:
    int val_;
};

class Variable : public ASTNode {  
  public:
    Variable(const std::string &var);
    std::string variable() const;

  private:
    std::string var_;
};

class Operator : public ASTNode {  
  public:
    Operator(const std::string &oper, ASTNode *lhs, ASTNode *rhs);
    std::string oper() const;

  private:
    std::string oper_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};

/*
class Div : public ASTNode {  
  public:
    Div(std::string op, ASTNode *lhs, ASTNode *rhs)
        : ASTNode(std::string(op), lhs, rhs)
        , op_(op)
        , lhs_{lhs}
        , rhs_{rhs}
         {}

    std::string op() const { return op_; } //

  private:
    std::string op_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};

class Add : public ASTNode {  
  public:
    Add(std::string op, ASTNode *lhs, ASTNode *rhs)
        : ASTNode(std::string(op), lhs, rhs)
        , op_(op)
        , lhs_{lhs}
        , rhs_{rhs}
         {}

    std::string op() const { return op_; } //

  private:
    std::string op_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};

class Sub : public ASTNode {  
  public:
    Sub(std::string op, ASTNode *lhs, ASTNode *rhs)
        : ASTNode(std::string(op), lhs, rhs)
        , op_(op)
        , lhs_{lhs}
        , rhs_{rhs}
         {}

    std::string op() const { return op_; } //

  private:
    std::string op_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};

*/