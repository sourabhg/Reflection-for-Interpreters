#include <iostream>
#include "ParseContext.hpp"
#include "Token.hpp"
#include "Node.hpp"
#include "Reflection.hpp"

using namespace std;
using namespace cs540;



int
main(int argc, char *argv[]) {

    Tokenizer tkz;

    while (true) {

        string line;
        getline(cin, line);
        if (cin.eof()) {
            break;
        }
        // cerr << "line: " << line << endl;
        deque<const Token *> tokens = tkz.tokenize(line);

        ParseContext ctx(tokens);
        yy::Parser parser(&ctx);
        parser.parse();
        const Node *ast = ctx.getAst();
        ast->execute();

        delete ast;

        // Free the tokens.
        for (size_t i = 0; i < tokens.size(); i++) {
            delete tokens.at(i);
        }
    }
}
