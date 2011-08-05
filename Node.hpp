#ifndef CS540_NODE_HPP
#define CS540_NODE_HPP


#include <string>
#include <deque>
#include "Value.hpp"
#include "Reflection.hpp"


namespace cs540 {

class IntegerToken;
class IdentToken;
class StringToken;
class Token;


class Node {
    public:
        virtual ~Node() {}
        virtual const Value *execute() const = 0;
};

class VoidNode : public Node {
    public:
        virtual const Value *execute() const { return 0; }
};

class AssignmentNode : public Node {
    public:
        AssignmentNode(const Token *, const Node *);
        virtual const Value *execute() const;
    private:
          const IdentToken *Assg_t;
          const Node *Assg_n;
          const Token *myt;
          
          
};
 
class VarNode : public Node {
    public:
        VarNode(const Token *);
        virtual const Value *execute() const;
    private:
        const IdentToken *var_t;
};

class IntegerNode : public Node {
    public:
        IntegerNode(const Token *);
        virtual const Value *execute() const;
    private: 
       const IntegerToken *int_tok;   
       const IntegerValue *x;
       int real_val;
};

class StringNode : public Node {
    public:
        StringNode(const Token *);
        virtual const Value *execute() const;
    private:
        const StringToken *t;
        const StringValue *st;
        std :: string real_st;
};

class AdditionNode : public Node {
    public:
        AdditionNode(const Node *l, const Node *r);
        virtual const Value *execute() const;
    private:
        const Token *tt;
        const Node *ll;
        const Node *rr;       
};

class MultiplicationNode : public Node {
    public:
        MultiplicationNode(const Node *l, const Node *r);
        virtual const Value *execute() const;
    private:
        const Token *tt;
        const Node *ll;
        const Node *rr;
};

class NegationNode : public Node {
    public:
        NegationNode(const Node *e) ;
        virtual const Value *execute() const;
    private:
        const Token *tt;
        const Node *ee;
};

class NewNode : public Node {
    public:
        NewNode(const Token *);
        virtual const Value *execute() const;
    private:
        Reflection *new_clss;
        std :: string cname;
        const IdentToken *class_name;
        const ObjPtrValue *obj;
};

class PrintNode : public Node {
    public:
        PrintNode(const Node *n);
        virtual const Value *execute() const;
    private:
        const Node *s;
};

class ArgList;

class InvocationNode : public Node {
    public:
        InvocationNode(const Token *, const Token *, const std::deque<const Node *> *);
        virtual const Value *execute() const;
    private:
        Reflection *go;
        const IdentToken *ret_t;
        const IdentToken *method;
        const std::deque<const Node *> *deq;        
};



}



#endif
