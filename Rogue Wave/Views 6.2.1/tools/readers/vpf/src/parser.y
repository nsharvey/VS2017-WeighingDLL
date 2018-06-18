%{
#include <vpf/basictypes.h>
#include <vpf/query.h>
#include <malloc.h>
#if defined(ILVSTD)
# include <cstdlib>
#else
# include <stdlib.h>
#endif
#ifdef _WIN32
# define alloca _alloca
#endif
%}

%union {
    VpfInt		intval;
    double		floatval;
    const char*		textval;
    VpfExpression*	exprval;
    VpfComparisonExpression::Operator opval;
    VpfInt		fieldval;
}

%{
extern int yylex(YYSTYPE*);
extern void yyerror(const char*);
%}

%token <intval> STAR
%token <intval> OPAR
%token <intval> CPAR
%left <intval> AND OR XOR
%left <intval> NOT
%token <textval> NAME
%token <textval> STRING
%token <intval> INT
%token <floatval> FLOAT
%token <intval> NULLo
%left <opval> EQo NEo LEo GEo LTo GTo

%type <exprval> filter;
%type <exprval> expr;
%type <exprval> fieldtest;
%type <opval> op;
%type <fieldval> field;

%%

filter:
	expr		{ VpfQuery::SetResult($1); $$ = $1; }
|	STAR		{ $$ = new VpfAllExpression(VpfQuery::Table());
			  VpfQuery::SetResult($$); }
;

expr:
	OPAR expr CPAR	{ $$ = $2; }
|	NOT expr	{ $$ = $2 ? new VpfNotExpression($2) : 0;}
|	expr AND expr	{ $$ = ($1 && $3) ? new VpfAndExpression($1, $3) : 0; }
|	expr OR expr	{ $$ = ($1 && $3) ? new VpfOrExpression($1, $3) : 0; }
|	expr XOR expr	{ $$ = ($1 && $3) ? new VpfOrExpression($1, $3) : 0; }
|	fieldtest	{ $$ = $1; }
;

fieldtest:
	field op STRING	{ $$ = ($1 >= 0)
			      ? VpfComparisonExpression::Create($1, $2, $3)
			      : 0; }
|	field op FLOAT	{ $$ = ($1 >= 0)
			      ? VpfComparisonExpression::Create($1, $2, $3)
			      : 0; }
|	field op INT	{ $$ = ($1 >= 0)
			      ? VpfComparisonExpression::Create($1, $2, $3)
			      : 0; }
|	field op field	{ $$ = (($3 >= 0) && ($1 >= 0))
			      ? new VpfMatchExpression(VpfQuery::Table(),
						       $1, $2, $3)
			      : 0; }
|	field EQo NULLo	{ $$ = (VpfMatchExpression*)0; }
|	field NEo NULLo	{ $$ = (VpfMatchExpression*)0; }
;

op:
	EQo		{ $$ = VpfComparisonExpression::EQ; }
|	NEo		{ $$ = VpfComparisonExpression::NE; }
|	LTo		{ $$ = VpfComparisonExpression::LT; }
|	LEo		{ $$ = VpfComparisonExpression::LE; }
|	GTo		{ $$ = VpfComparisonExpression::GT; }
|	GEo		{ $$ = VpfComparisonExpression::GE; }
;

field:
	NAME		{ $$ = VpfQuery::FieldFromName($1); }
;

%%
