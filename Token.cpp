#include "Token.hpp"
#include <regex.h>
#include <vector>
#include <deque>
#include <string>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "forward_decls.hpp"
#include "Parser.tab.hh"

using namespace std;

namespace cs540 {




IdentToken::IdentToken(const std::string &s)
 : Token(yy::Parser::token::IDENT), m_ident(s) {}
const char IdentToken::pattern_string[] = "[[:alpha:]][[:alnum:]]*";
TokenFactory<IdentToken> identFactory;

IntegerToken::IntegerToken(const std::string &s)
 : Token(yy::Parser::token::INTEGER), m_value(atoi(s.c_str())) {
  //  printf("IntegerToken created: %s, %d\n", s.c_str(), m_value.value());
}
const char IntegerToken::pattern_string[] = "[[:digit:]]+";
TokenFactory<IntegerToken> integerFactory;

StringToken::StringToken(const std::string &s)
 : Token(yy::Parser::token::STRING), m_value(s) {}
const char StringToken::pattern_string[] = "\"[^\"]*\"";
TokenFactory<StringToken> stringFactory;

template <>
Token *
TokenFactory<StringToken>::make(const char *p, int n) const {
    return new StringToken(std::string(p + 1, n - 2));
}

TerminalToken::TerminalToken(const string &s)
 : Token(s.at(0)) {}
// Hyphen must come first in pattern below.
const char TerminalToken::pattern_string[] = "[-+/*()=.,]";
TokenFactory<TerminalToken> terminalFactory;

NewToken::NewToken(const string &) : Token(yy::Parser::token::NEW) {}
const char NewToken::pattern_string[] = "new";
TokenFactory<NewToken> newFactory;

PrintToken::PrintToken(const string &) : Token(yy::Parser::token::PRINT) {}
const char PrintToken::pattern_string[] = "print";
TokenFactory<PrintToken> printFactory;

Tokenizer::Tokenizer() {

    int ec;

    ec = regcomp(&m_ws_pattern, "^[[:space:]]+", REG_EXTENDED);
    //ec = regcomp(&ws_pattern, "a", REG_EXTENDED);
    assert(ec == 0);

    m_factories.push_back(&stringFactory);
    m_factories.push_back(&newFactory);
    m_factories.push_back(&printFactory); m_factories.push_back(&identFactory);
    m_factories.push_back(&integerFactory);
    m_factories.push_back(&terminalFactory);
}

Tokenizer::~Tokenizer() {

    regfree(&m_ws_pattern);
}

deque<const Token *>
Tokenizer::tokenize(const std::string &line) const {

    int ec;

    deque<const Token *> tokens;

    const char *p = line.c_str(), *end = p + strlen(p);
    loop:
    while (p < end) {
        regmatch_t matches[1];
        int ec;
        ec = regexec(&m_ws_pattern, p, 1, matches, 0);
        if (ec == 0) {
            assert(matches[0].rm_so != -1);
            // Eat white space.
            {
                string s(p + matches[0].rm_so,
                 matches[0].rm_eo - matches[0].rm_so);
                // printf("ws: %d-%d\n", int(matches[0].rm_so),
                //  int(matches[0].rm_eo));
                //s.c_str());
            }
            p += matches[0].rm_eo - matches[0].rm_so;
        } else {
            assert(ec == REG_NOMATCH);
            for (size_t i = 0; i < m_factories.size(); i++) {
                int n;
                if ((n = m_factories[i]->match(p)) > 0) {
                    // printf("%d\n", i);
                    Token *t = m_factories[i]->make(p, n);
                    tokens.push_back(t);
                    p = p + n;
                    goto loop;
                }
            }
            assert(false);
        }
    }

    return tokens;
}



}
