/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_OURPYTHON_TAB_H_INCLUDED
# define YY_YY_OURPYTHON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NEWLINE = 258,
    SEMICOLON = 259,
    COLON = 260,
    COMMA = 261,
    BEGIN_PAREN = 262,
    END_PAREN = 263,
    IF = 264,
    ELIF = 265,
    ELSE = 266,
    WHILE = 267,
    PRINT = 268,
    LESSER = 269,
    LESSER_EQUAL = 270,
    GREATER = 271,
    GREATER_EQUAL = 272,
    EQUALS = 273,
    NOT_EQUAL = 274,
    TRUE = 275,
    FALSE = 276,
    PLUS = 277,
    MINUS = 278,
    STAR = 279,
    SLASH = 280,
    EQUAL = 281,
    AND = 282,
    OR = 283,
    NOT = 284,
    BEGIN_INDENT = 285,
    END_INDENT = 286,
    INTEGER = 287,
    FLOAT = 288,
    STRING = 289,
    NAME = 290,
    BOOLEAN = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 36 "ourPython.y" /* yacc.c:1909  */

	int intValue;
	float floatValue;
	char* stringValue;
	bool boolValue;
	Object* value;
	Expression* exprPtr;
	Statement* statePtr;

#line 101 "ourPython.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_OURPYTHON_TAB_H_INCLUDED  */
