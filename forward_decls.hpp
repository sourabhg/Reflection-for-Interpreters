#ifndef CS540_FORWARD_DECLS_HPP
#define CS540_FORWARD_DECLS_HPP



#include <queue>



namespace cs540 {
    //class ArgList;
    class Node;
    typedef std::deque<const Node *> arglist_t;
    class IdentToken;
    class IntegerToken;
    class NewToken;
    class ParseContext;
    class PrintToken;
    class StringToken;
    class Token;
}



#endif
