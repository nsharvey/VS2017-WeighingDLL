
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif
 {
    VpfInt		intval;
    double		floatval;
    const char*		textval;
    VpfExpression*	exprval;
    VpfComparisonExpression::Operator opval;
    VpfInt		fieldval;
} YYSTYPE;
extern YYSTYPE yylval;
# define STAR 257
# define OPAR 258
# define CPAR 259
# define AND 260
# define OR 261
# define XOR 262
# define NOT 263
# define NAME 264
# define STRING 265
# define INT 266
# define FLOAT 267
# define NULLo 268
# define EQo 269
# define NEo 270
# define LEo 271
# define GEo 272
# define LTo 273
# define GTo 274

