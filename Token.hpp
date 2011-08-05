#ifndef CS540_TOKEN_HPP
#define CS540_TOKEN_HPP



#include <regex.h>
#include <deque>
#include <vector>
#include <string>
#include <assert.h>
#include <string.h>
#include "Value.hpp"
//#include <stdlib.h>
//#include <unistd.h>



namespace cs540 {



class Token {
    public:
        Token(int code) : m_code(code) {}
        virtual ~Token() {}
        int code() const { return m_code; }
    private:
        const int m_code;
};

class StringToken : public Token {
    public:
        StringToken(const std::string &);
        const StringValue &value() const { return m_value; }
        static const char pattern_string[];
    private:
        const StringValue m_value;
};

class IntegerToken : public Token {
    public:
        IntegerToken(const std::string &);
        const IntegerValue &value() const { return m_value; }
        static const char pattern_string[];
    private:
        const IntegerValue m_value;
};

class IdentToken : public Token {
    public:
        IdentToken(const std::string &);
        static const char pattern_string[];
        const std::string &ident() const { return m_ident; }
    private:
        const std::string m_ident;
};

class TerminalToken : public Token {
    public:
        TerminalToken(const std::string &);
        static const char pattern_string[];
    private:
        const std::string m_char;
};

class NewToken : public Token {
    public:
        NewToken(const std::string &);
        static const char pattern_string[];
};

class PrintToken : public Token {
    public:
        PrintToken(const std::string &);
        static const char pattern_string[];
};

class Factory {
    public:
        virtual ~Factory() {}
        virtual int match(const char *) const = 0;
        virtual Token *make(const char *p, int n) const = 0;
};

template <typename T>
class TokenFactory : public Factory {
    public:
        TokenFactory();
        virtual ~TokenFactory();
        virtual int match(const char *) const;
        virtual Token *make(const char *p, int n) const;
    private:
        regex_t m_pattern;
};

// Specialization so that strings have their beginning
// and ending " removed.
template <>
Token *
TokenFactory<StringToken>::make(const char *p, int n) const;

template <typename T>
TokenFactory<T>::TokenFactory() {
    int ec;
    // Put a ^ at the very front of the pattern so that we
    // don't skip any characters.
    std::string pat(std::string("^") + T::pattern_string);
    ec = regcomp(&m_pattern, pat.c_str(), REG_EXTENDED);
    assert(ec == 0);
}

template <typename T>
TokenFactory<T>::~TokenFactory() {
    regfree(&m_pattern);
}

template <typename T>
int
TokenFactory<T>::match(const char *p) const {
    regmatch_t matches[1];
    int ec;
    ec = regexec(&m_pattern, p, 1, matches, 0);
    if (ec == 0) {
        assert(matches[0].rm_so != -1);
        assert(matches[0].rm_so == 0);
        //printf("token: %d-%d\n", int(matches[0].rm_so),
        // int(matches[0].rm_eo));
        return matches[0].rm_eo - matches[0].rm_so;
    } else {
        return 0;
    }
}

template <typename T>
Token *
TokenFactory<T>::make(const char *p, int n) const {
    std::string s(p, n);
    //printf("make called with: %s\n", s.c_str());
    return new T(s);
}

class Tokenizer {
    public:
        Tokenizer();
        ~Tokenizer();
        std::deque<const Token *> tokenize(const std::string &) const;
    private:
        regex_t m_ws_pattern;
        std::vector<const Factory *> m_factories;
};



}



#endif
