
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 3 "mcc.y"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mc.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
int yylex();
void yyerror(const char* fmt, ...);


/* Line 189 of yacc.c  */
#line 86 "mcc.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     FLOAT = 259,
     STRING = 260,
     ELE = 261,
     ID = 262,
     TYPE = 263,
     RELOP = 264,
     INT = 265,
     IF = 266,
     ELSE = 267,
     WHILE = 268,
     FOR = 269,
     AND = 270,
     OR = 271,
     RETURN = 272,
     SWITCH = 273,
     CASE = 274,
     BREAK = 275,
     CONTINUE = 276,
     DEFAULT = 277,
     UMINUS = 278,
     LOWER_THEN_ELSE = 279
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 15 "mcc.y"

    char   type_char;
	int    type_int;
	float  type_float;
	char   type_id[32];
    void * node;



/* Line 214 of yacc.c  */
#line 156 "mcc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 181 "mcc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   325

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  132

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,     2,     2,     2,     2,     2,
       7,     8,    31,    29,     6,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,     5,
       2,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    34,    35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     9,    11,    16,    19,    21,    25,
      30,    37,    41,    47,    54,    63,    70,    77,    78,    81,
      86,    91,    92,    97,    98,   101,   104,   106,   110,   113,
     116,   122,   130,   139,   145,   155,   160,   166,   167,   171,
     173,   175,   179,   183,   187,   191,   195,   199,   203,   207,
     211,   214,   217,   222,   227,   229,   231,   233,   235,   237,
     238,   240
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    14,    43,     5,    -1,    44,
      -1,    14,    43,     5,    42,    -1,    44,    42,    -1,    13,
      -1,    13,     3,    53,    -1,    13,    36,    16,    37,    -1,
      13,    36,    16,    37,     3,    11,    -1,    13,     6,    43,
      -1,    13,     3,    53,     6,    43,    -1,    13,    36,    16,
      37,     6,    43,    -1,    13,    36,    16,    37,     3,    11,
       6,    43,    -1,    14,    13,     7,    45,     8,     5,    -1,
      14,    13,     7,    45,     8,    46,    -1,    -1,    14,    13,
      -1,    14,    13,     6,    45,    -1,    38,    47,    48,    39,
      -1,    -1,    14,    43,     5,    47,    -1,    -1,    49,    48,
      -1,    53,     5,    -1,    46,    -1,    23,    53,     5,    -1,
      26,     5,    -1,    27,     5,    -1,    17,     7,    53,     8,
      49,    -1,    17,     7,    53,     8,    49,    18,    49,    -1,
      24,     7,    53,     8,    38,    50,    51,    39,    -1,    19,
       7,    53,     8,    49,    -1,    20,     7,    53,     5,    53,
       5,    53,     8,    52,    -1,    25,    53,     4,    48,    -1,
      25,    53,     4,    48,    50,    -1,    -1,    28,     4,    48,
      -1,     5,    -1,    49,    -1,    53,     3,    53,    -1,    53,
      21,    53,    -1,    53,    22,    53,    -1,    53,    15,    53,
      -1,    53,    29,    53,    -1,    53,    30,    53,    -1,    53,
      31,    53,    -1,    53,    32,    53,    -1,     7,    53,     8,
      -1,    30,    53,    -1,    33,    53,    -1,    13,     7,    54,
       8,    -1,    13,    36,    16,    37,    -1,    13,    -1,     9,
      -1,    11,    -1,    16,    -1,    10,    -1,    -1,    53,    -1,
      53,     6,    54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    47,    47,    51,    52,    53,    54,    59,    60,    61,
      62,    63,    64,    65,    66,    70,    71,    74,    75,    76,
      80,    83,    84,    87,    88,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   104,   105,   107,   108,   111,
     112,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   135,
     136,   137
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "':'", "';'", "','", "'('", "')'",
  "CHAR", "FLOAT", "STRING", "ELE", "ID", "TYPE", "RELOP", "INT", "IF",
  "ELSE", "WHILE", "FOR", "AND", "OR", "RETURN", "SWITCH", "CASE", "BREAK",
  "CONTINUE", "DEFAULT", "'+'", "'-'", "'*'", "'/'", "'!'", "UMINUS",
  "LOWER_THEN_ELSE", "'['", "']'", "'{'", "'}'", "$accept", "program",
  "declarations", "var_init_list", "func_declaration", "param_list",
  "compound_stmt", "var_declaration", "stmt_list", "stmt", "case_list",
  "default", "for_body", "exp", "args_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    61,    58,    59,    44,    40,    41,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,    43,
      45,    42,    47,    33,   278,   279,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    43,    43,    43,
      43,    43,    43,    43,    43,    44,    44,    45,    45,    45,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     1,     4,     2,     1,     3,     4,
       6,     3,     5,     6,     8,     6,     6,     0,     2,     4,
       4,     0,     4,     0,     2,     2,     1,     3,     2,     2,
       5,     7,     8,     5,     9,     4,     5,     0,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     4,     1,     1,     1,     1,     1,     0,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,     7,     0,     1,     6,     0,
       0,    17,     0,     3,     0,    55,    58,    56,    54,    57,
       0,     0,     8,     7,    11,     0,     0,     0,     5,     0,
      59,     0,    50,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     9,    49,    60,     0,     0,
      41,    12,    44,    42,    43,    45,    46,    47,    48,    17,
      15,    21,    16,     0,     0,    59,    52,    53,    19,     0,
      23,    10,    13,    61,     0,     0,     0,     0,     0,     0,
       0,     0,    26,     0,    23,     0,     0,    21,     0,     0,
       0,     0,     0,    28,    29,    20,    24,    25,    14,    22,
       0,     0,     0,    27,     0,     0,     0,     0,     0,    30,
      33,     0,     0,     0,     0,     0,    37,    31,     0,     0,
       0,     0,     0,    23,    23,    32,    39,    40,    34,    35,
      38,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     4,    26,    82,    70,    83,    84,
     116,   121,   128,    85,    48
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -84
static const yytype_int16 yypact[] =
{
     -10,    11,    20,   -84,   -10,     0,    21,   -84,   -84,   272,
      26,    28,    31,   -10,   272,   -84,   -84,   -84,     1,   -84,
     272,   272,    43,     7,   -84,    35,    49,    24,   -84,   133,
     272,    46,   -84,   -84,   272,    26,   272,   272,   272,   272,
     272,   272,   272,    60,    -3,    16,   -84,   129,    62,    34,
      23,   -84,   -14,   210,   293,    19,    19,   -84,   -84,    28,
     -84,    63,   -84,    67,    26,   272,   -84,   -84,   -84,    26,
     107,    83,   -84,   -84,    86,    85,    88,    92,   272,    95,
     103,   104,   -84,    72,   107,   163,    26,    63,   272,   272,
     272,   167,   272,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     197,   201,   231,   -84,   235,   107,   107,   272,    74,   101,
     -84,   265,    96,   107,   272,   272,    94,   -84,   269,   289,
     109,    89,    77,   107,   107,   -84,   -84,   -84,   -84,    96,
     -84,   -84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,    10,    -1,   -84,    66,    98,    42,   -83,   -46,
       9,   -84,   -84,    -9,    78
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      22,    96,    60,     9,     1,    29,    10,    11,    30,    24,
       9,    32,    33,    10,     8,    39,    40,    41,    42,    63,
       7,    47,    64,    28,     5,    50,    13,    52,    53,    54,
      55,    56,    57,    58,    51,    61,    12,    31,    36,    23,
     129,   130,    25,    12,    37,    38,    34,    27,    43,    35,
      41,    42,    39,    40,    41,    42,    47,    44,    36,   109,
     110,    45,    49,    72,    37,    38,    59,   117,    74,    91,
      66,    67,    39,    40,    41,    42,   127,    69,    71,   100,
     101,   102,   126,   104,    14,    98,    15,    16,    17,    86,
      18,    87,    88,    19,    75,    89,    76,    77,   111,    90,
      78,    79,    92,    80,    81,   118,   119,    20,    93,    94,
      21,    95,   112,   124,    14,    61,    15,    16,    17,   113,
      18,   115,   120,    19,    75,    68,    76,    77,   125,    99,
      78,    79,    34,    80,    81,    65,    34,    20,   131,     0,
      21,    46,    62,    73,    36,    61,     0,     0,    36,     0,
      37,    38,     0,     0,    37,    38,     0,     0,    39,    40,
      41,    42,    39,    40,    41,    42,    34,     0,    97,     0,
      34,     0,   103,     0,     0,     0,     0,     0,    36,     0,
       0,     0,    36,     0,    37,    38,     0,     0,    37,    38,
       0,     0,    39,    40,    41,    42,    39,    40,    41,    42,
      34,     0,     0,     0,    34,   105,     0,     0,     0,   106,
       0,     0,    36,     0,     0,     0,    36,     0,    37,    38,
       0,     0,    37,    38,     0,    36,    39,    40,    41,    42,
      39,    40,    41,    42,    34,     0,   107,     0,    34,    39,
      40,    41,    42,   108,     0,     0,    36,     0,     0,     0,
      36,     0,    37,    38,     0,     0,    37,    38,     0,     0,
      39,    40,    41,    42,    39,    40,    41,    42,    34,     0,
     114,     0,    34,     0,     0,     0,     0,   122,     0,    14,
      36,    15,    16,    17,    36,    18,    37,    38,    19,     0,
      37,    38,    34,   123,    39,    40,    41,    42,    39,    40,
      41,    42,    20,     0,    36,    21,     0,     0,    36,     0,
      37,    38,     0,     0,    37,     0,     0,     0,    39,    40,
      41,    42,    39,    40,    41,    42
};

static const yytype_int16 yycheck[] =
{
       9,    84,     5,     3,    14,    14,     6,     7,     7,    10,
       3,    20,    21,     6,     4,    29,    30,    31,    32,     3,
       0,    30,     6,    13,    13,    34,     5,    36,    37,    38,
      39,    40,    41,    42,    35,    38,    36,    36,    15,    13,
     123,   124,    14,    36,    21,    22,     3,    16,    13,     6,
      31,    32,    29,    30,    31,    32,    65,     8,    15,   105,
     106,    37,    16,    64,    21,    22,     6,   113,    69,    78,
       8,    37,    29,    30,    31,    32,   122,    14,    11,    88,
      89,    90,     5,    92,     7,    86,     9,    10,    11,     6,
      13,     5,     7,    16,    17,     7,    19,    20,   107,     7,
      23,    24,     7,    26,    27,   114,   115,    30,     5,     5,
      33,    39,    38,     4,     7,    38,     9,    10,    11,    18,
      13,    25,    28,    16,    17,    59,    19,    20,    39,    87,
      23,    24,     3,    26,    27,     6,     3,    30,   129,    -1,
      33,     8,    44,    65,    15,    38,    -1,    -1,    15,    -1,
      21,    22,    -1,    -1,    21,    22,    -1,    -1,    29,    30,
      31,    32,    29,    30,    31,    32,     3,    -1,     5,    -1,
       3,    -1,     5,    -1,    -1,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    15,    -1,    21,    22,    -1,    -1,    21,    22,
      -1,    -1,    29,    30,    31,    32,    29,    30,    31,    32,
       3,    -1,    -1,    -1,     3,     8,    -1,    -1,    -1,     8,
      -1,    -1,    15,    -1,    -1,    -1,    15,    -1,    21,    22,
      -1,    -1,    21,    22,    -1,    15,    29,    30,    31,    32,
      29,    30,    31,    32,     3,    -1,     5,    -1,     3,    29,
      30,    31,    32,     8,    -1,    -1,    15,    -1,    -1,    -1,
      15,    -1,    21,    22,    -1,    -1,    21,    22,    -1,    -1,
      29,    30,    31,    32,    29,    30,    31,    32,     3,    -1,
       5,    -1,     3,    -1,    -1,    -1,    -1,     8,    -1,     7,
      15,     9,    10,    11,    15,    13,    21,    22,    16,    -1,
      21,    22,     3,     4,    29,    30,    31,    32,    29,    30,
      31,    32,    30,    -1,    15,    33,    -1,    -1,    15,    -1,
      21,    22,    -1,    -1,    21,    -1,    -1,    -1,    29,    30,
      31,    32,    29,    30,    31,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    41,    42,    44,    13,    43,     0,    42,     3,
       6,     7,    36,     5,     7,     9,    10,    11,    13,    16,
      30,    33,    53,    13,    43,    14,    45,    16,    42,    53,
       7,    36,    53,    53,     3,     6,    15,    21,    22,    29,
      30,    31,    32,    13,     8,    37,     8,    53,    54,    16,
      53,    43,    53,    53,    53,    53,    53,    53,    53,     6,
       5,    38,    46,     3,     6,     6,     8,    37,    45,    14,
      47,    11,    43,    54,    43,    17,    19,    20,    23,    24,
      26,    27,    46,    48,    49,    53,     6,     5,     7,     7,
       7,    53,     7,     5,     5,    39,    48,     5,    43,    47,
      53,    53,    53,     5,    53,     8,     8,     5,     8,    49,
      49,    53,    38,    18,     5,    25,    50,    49,    53,    53,
      28,    51,     8,     4,     4,    39,     5,    49,    52,    48,
      48,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 47 "mcc.y"
    {puts("1");(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 51 "mcc.y"
    {puts("2");(yyval.node)=newdec(EXTERN_VAR,(yyvsp[(1) - (3)].type_id),(yyvsp[(2) - (3)].node),NULL);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 52 "mcc.y"
    {puts("3");(yyval.node)=newdec(EXTERN_FUN,NULL,(yyvsp[(1) - (1)].node),NULL);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 53 "mcc.y"
    {puts("4");(yyval.node)=newdec(EXTERN_VAR_LIST,NULL,(yyvsp[(2) - (4)].node),(yyvsp[(4) - (4)].node));;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 54 "mcc.y"
    {puts("5");(yyval.node)=newdec(EXTERN_FUN_LIST,NULL,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node));;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 59 "mcc.y"
    {puts("6");(yyval.node)=newvarinitlist(VAR_NO,(yyvsp[(1) - (1)].type_id),-1,NULL,NULL,NULL);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 60 "mcc.y"
    {puts("7");(yyval.node)=newvarinitlist(VAR_INIT,(yyvsp[(1) - (3)].type_id),-1,NULL,(yyvsp[(3) - (3)].node),NULL);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 61 "mcc.y"
    {puts("8");(yyval.node)=newvarinitlist(ARRAY_NO,(yyvsp[(1) - (4)].type_id),(yyvsp[(3) - (4)].type_int),NULL,NULL,NULL);;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 62 "mcc.y"
    {puts("9");(yyval.node)=newvarinitlist(ARRAY_INIT,(yyvsp[(1) - (6)].type_id),(yyvsp[(3) - (6)].type_int),(yyvsp[(6) - (6)].type_id),NULL,NULL);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 63 "mcc.y"
    {puts("10");(yyval.node)=newvarinitlist(VAR_LIST,(yyvsp[(1) - (3)].type_id),-1,NULL,(yyvsp[(3) - (3)].node),NULL);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 64 "mcc.y"
    {puts("11");(yyval.node)=newvarinitlist(VAR_INIT_LIST,(yyvsp[(1) - (5)].type_id),-1,NULL,(yyvsp[(3) - (5)].node),(yyvsp[(5) - (5)].node));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 65 "mcc.y"
    {puts("12");(yyval.node)=newvarinitlist(ARRAY_LIST,(yyvsp[(1) - (6)].type_id),(yyvsp[(3) - (6)].type_int),NULL,(yyvsp[(6) - (6)].node),NULL);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 66 "mcc.y"
    {puts("13");(yyval.node)=newvarinitlist(ARRAY_INIT_LIST,(yyvsp[(1) - (8)].type_id),(yyvsp[(3) - (8)].type_int),(yyvsp[(6) - (8)].type_id),(yyvsp[(8) - (8)].node),NULL);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 70 "mcc.y"
    {puts("14");(yyval.node)=newfundec(FUN_DEC,(yyvsp[(1) - (6)].type_id),(yyvsp[(2) - (6)].type_id),(yyvsp[(4) - (6)].node),NULL);;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 71 "mcc.y"
    {puts("15");(yyval.node)=newfundec(FUN_DEC,(yyvsp[(1) - (6)].type_id),(yyvsp[(2) - (6)].type_id),(yyvsp[(4) - (6)].node),(yyvsp[(6) - (6)].node));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 74 "mcc.y"
    {puts("16");(yyval.node)=NULL;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 75 "mcc.y"
    {puts("17");(yyval.node)=newparam(PARAM,(yyvsp[(1) - (2)].type_id),(yyvsp[(2) - (2)].type_id),NULL);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 76 "mcc.y"
    {puts("18");(yyval.node)=newparam(PARAM,(yyvsp[(1) - (4)].type_id),(yyvsp[(2) - (4)].type_id),(yyvsp[(4) - (4)].node));;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 80 "mcc.y"
    {puts("19");(yyval.node)=newast(COMPSTMT,(yyvsp[(2) - (4)].node),(yyvsp[(3) - (4)].node));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 83 "mcc.y"
    {puts("20");(yyval.node)=NULL;;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 84 "mcc.y"
    {puts("21");(yyval.node)=newdec(INNER_VAR,(yyvsp[(1) - (4)].type_id),(yyvsp[(2) - (4)].node),(yyvsp[(4) - (4)].node));;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 87 "mcc.y"
    {puts("22");(yyval.node)=NULL;;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 88 "mcc.y"
    {puts("23");(yyval.node)=newast(STMTLIST,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 91 "mcc.y"
    {puts("24");(yyval.node)=(yyvsp[(1) - (2)].node);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 92 "mcc.y"
    {puts("25");(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 93 "mcc.y"
    {puts("26");(yyval.node)=newast(RETURN_NO,(yyvsp[(2) - (3)].node),NULL);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 94 "mcc.y"
    {puts("27");(yyval.node)=newast(BREAK_NO,NULL,NULL);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 95 "mcc.y"
    {puts("28");(yyval.node)=newast(CONTINUE_NO,NULL,NULL);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 96 "mcc.y"
    {puts("29");(yyval.node)=newcondition(IF_NO,(yyvsp[(3) - (5)].node),(yyvsp[(5) - (5)].node),NULL,NULL);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 97 "mcc.y"
    {puts("30");(yyval.node)=newcondition(IF_NO,(yyvsp[(3) - (7)].node),(yyvsp[(5) - (7)].node),(yyvsp[(7) - (7)].node),NULL);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 98 "mcc.y"
    {puts("31");(yyval.node)=newcondition(SWITCH_NO,(yyvsp[(3) - (8)].node),(yyvsp[(6) - (8)].node),(yyvsp[(7) - (8)].node),NULL);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 99 "mcc.y"
    {puts("32");(yyval.node)=newast(WHILE_NO,(yyvsp[(3) - (5)].node),(yyvsp[(5) - (5)].node));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 100 "mcc.y"
    {puts("33");(yyval.node)=newcondition(FOR_NO,(yyvsp[(3) - (9)].node),(yyvsp[(5) - (9)].node),(yyvsp[(7) - (9)].node),(yyvsp[(9) - (9)].node));;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 104 "mcc.y"
    {puts("34");(yyval.node)=newcondition(CASE_NO,(yyvsp[(2) - (4)].node),(yyvsp[(4) - (4)].node),NULL,NULL);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 105 "mcc.y"
    {puts("35");(yyval.node)=newcondition(CASE_NO,(yyvsp[(2) - (5)].node),(yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node),NULL);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 107 "mcc.y"
    {puts("36");(yyval.node)=NULL;;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 108 "mcc.y"
    {puts("37");(yyval.node)=newast(DEFAULT_NO,(yyvsp[(3) - (3)].node),NULL);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 111 "mcc.y"
    {puts("38");(yyval.node)=NULL;;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 112 "mcc.y"
    {puts("39");(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 115 "mcc.y"
    {puts("40");(yyval.node)=newast(ASSIGN,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 116 "mcc.y"
    {puts("41");(yyval.node)=newast(AND_NO,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 117 "mcc.y"
    {puts("42");(yyval.node)=newast(OR_NO,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 118 "mcc.y"
    {puts("43");(yyval.node)=newast(RELOP_NO,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 119 "mcc.y"
    {puts("44");(yyval.node)=newast(ADD,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 120 "mcc.y"
    {puts("45");(yyval.node)=newast(MINUS,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 121 "mcc.y"
    {puts("46");(yyval.node)=newast(MUL,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 122 "mcc.y"
    {puts("47");(yyval.node)=newast(DIV,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 123 "mcc.y"
    {puts("48");(yyval.node)=(yyvsp[(2) - (3)].node);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 124 "mcc.y"
    {puts("49");(yyval.node)=newast(UMINUS_NO,(yyvsp[(2) - (2)].node),NULL);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 125 "mcc.y"
    {puts("50");(yyval.node)=newast(NOT,(yyvsp[(2) - (2)].node),NULL);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 126 "mcc.y"
    {puts("51");(yyval.node)=newfun(FUN_CALL,(yyvsp[(1) - (4)].type_id),(yyvsp[(3) - (4)].node));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 127 "mcc.y"
    {puts("52");(yyval.node)=newele(ELE_NO,(yyvsp[(1) - (4)].type_id),(yyvsp[(3) - (4)].type_int));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 128 "mcc.y"
    {puts("53");(yyval.node)=newnum(ID_NO);strcpy(((struct num*)(yyval.node))->numval.string,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 129 "mcc.y"
    {puts("54");(yyval.node)=newnum(CHAR_NO);((struct num*)(yyval.node))->numval.ch=(yyvsp[(1) - (1)].type_char);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 130 "mcc.y"
    {puts("55");(yyval.node)=newnum(STRING_NO);strcpy(((struct num*)(yyval.node))->numval.string,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 131 "mcc.y"
    {puts("56");(yyval.node)=newnum(INT_NO);((struct num*)(yyval.node))->numval.intval=(yyvsp[(1) - (1)].type_int);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 132 "mcc.y"
    {puts("57");(yyval.node)=newnum(FLOAT_NO);((struct num*)(yyval.node))->numval.floatval=(yyvsp[(1) - (1)].type_float);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 135 "mcc.y"
    {(yyval.node)=NULL;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 136 "mcc.y"
    {puts("58");(yyval.node)=newast(ARGS,(yyvsp[(1) - (1)].node),NULL);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 137 "mcc.y"
    {puts("59");(yyval.node)=newast(ARGS,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;



/* Line 1455 of yacc.c  */
#line 1979 "mcc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 139 "mcc.y"


int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
	yylineno=1;
	yyparse();
	return 0;
	}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}	

