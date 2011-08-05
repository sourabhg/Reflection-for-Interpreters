#include "ParseContext.hpp"
#include <assert.h>
#include "Token.hpp"



using namespace std;



namespace cs540 {



ParseContext::ParseContext(const deque<const Token *> &t)
 : m_tokens(t), m_ast(0) {}

int
ParseContext::yylex(yy::Parser::semantic_type *val) {
    if (m_tokens.size() > 0) {
        const Token *t = m_tokens.front();
        m_tokens.pop_front();
        val->token = t;
        return t->code();
    } else {
        val->token = 0;
        return 0;
    }
}

void
ParseContext::setAst(const Node *n) {
    assert(m_ast == 0);
    m_ast = n;
}

const Node *
ParseContext::getAst() const {
    assert(m_ast != 0);
    return m_ast;
}



}
