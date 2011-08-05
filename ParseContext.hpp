#ifndef CS540_PARSE_CONTEXT_HPP
#define CS540_PARSE_CONTEXT_HPP



#include <deque>
// The .hh file needs some forward declarations.
#include "forward_decls.hpp"
#include "Parser.tab.hh"



namespace cs540 {



class ParseContext {
    public:
        ParseContext(const std::deque<const Token *> &);
        int yylex(yy::Parser::semantic_type *);
        void setAst(const Node *);
        const Node *getAst() const;
    private:
        std::deque<const Token *> m_tokens;
        const Node *m_ast;
};



}



#endif
