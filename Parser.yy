%skeleton "lalr1.cc"
%defines
%define "parser_class_name" "Parser"

%lex-param {cs540::ParseContext *context}
%parse-param {cs540::ParseContext *context}

%{
#include <stdio.h>
#include "forward_decls.hpp"
%}

%union {
    const cs540::Node *node;
    const cs540::Token *token;
    cs540::arglist_t *arg_list;
}

%{
#include "ParseContext.hpp"
#include "Node.hpp"
#include "Token.hpp"
namespace cs540 {
    int yylex(yy::Parser::semantic_type *yylval, ParseContext *);
}
%}



%token <token> IDENT
%token <token> INTEGER
%token <token> STRING
%token <token> NEW
%token <token> PRINT
%token <token> ','
%type <node> expr
%type <arg_list> opt_arg
%type <arg_list> arg_list

%%

%start statement;

statement: /* epsilon */ { context->setAst(new cs540::VoidNode); }
    | expr { context->setAst($1); }
    ;

%left PRINT;
%right <token> '=';
%left <token> '+' '-';
%left <token> '*' '/';
%left <token> NEG;
expr:
      PRINT expr { $$ = new cs540::PrintNode($2); }
    | IDENT '=' expr { $$ = new cs540::AssignmentNode($1, $3); }
    | expr '+' expr { $$ = new cs540::AdditionNode($1, $3); }
    | expr '-' expr { $$ = new cs540::AdditionNode($1, $3); }
    | expr '*' expr { $$ = new cs540::MultiplicationNode($1, $3); }
    | expr '/' expr { $$ = new cs540::MultiplicationNode($1, $3); }
    | '-' expr %prec NEG { $$ = new cs540::NegationNode($2); }
    | '(' expr ')' { $$ = $2; }
    | IDENT '.' IDENT '(' opt_arg ')' { $$ = new cs540::InvocationNode($1, $3, $5); }
    | NEW IDENT { $$ = new cs540::NewNode($2); }
    | IDENT { $$ = new cs540::VarNode($1); }
    | INTEGER { $$ = new cs540::IntegerNode($1); }
    | STRING { $$ = new cs540::StringNode($1); }
    ;

opt_arg: /* epsilon */ { $$ = new cs540::arglist_t; }
    | expr arg_list { $2->push_front($1); $$ = $2; }
    ;

arg_list: /* epsilon */ { $$ = new cs540::arglist_t; }
    | ',' expr arg_list { $3->push_front($2); $$ = $3; }
    ;

%%

namespace cs540 {

int
yylex(yy::Parser::semantic_type *yylval, ParseContext *ctx) {
    return ctx->yylex(yylval);
}



}


void
yy::Parser::error (const yy::Parser::location_type& l, const std::string& m) {
    printf("ERROR: Syntax error.\n");
    assert(false);
}
