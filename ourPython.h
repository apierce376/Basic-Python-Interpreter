/*-------------------------------------------------------------------------*
 *---									---*
 *---		ourPython.h						---*
 *---									---*
 *---	    This file declares types and classes needed to implement a	---*
 *---	basic Python interpreter.					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 15		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<cstdlib>
#include	<cstdio>
#include	<cstring>
#include	<ctype.h>		// For isspace()
#include	<string>
#include	<vector>
#include	<map>


//  PURPOSE:  To tell the default length of C strings.
const	int	LINE_LEN		= 256;


//  PURPOSE:  To distinguish among the implemented Python types.
typedef		enum
		{
		  noneType,
		  boolType,
		  intType,
		  floatType,
		  strType,
		  typeType
		}
		pythonType_ty;

//  PURPOSE:  To tell the printable names of the values of 'pythonType_ty'.
extern
const char*	typeNameArray[];


//  PURPOSE:  To distinguish among the implemented Python operators.
typedef		enum
		{
		  OR_OP,
		  AND_OP,
		  NOT_OP,
		  LESSER_OP,
		  LESSER_EQUAL_OP,
		  GREATER_OP,
		  GREATER_EQUAL_OP,
		  EQUAL_EQUAL_OP,
		  NOT_EQUAL_OP,
		  PLUS_OP,
		  MINUS_OP,
		  STAR_OP,
		  SLASH_OP,
		  PERCENT_OP,
		  SLASH_SLASH_OP,
		  STAR_STAR_OP
		}
		operator_ty;

//  PURPOSE:  To tell the printable names of the values of 'operator_ty'.
extern
const char*	operatorNameArray[];


//  PURPOSE:  To do 'delete(ptr)', and then set 'ptr' to 'NULL'.
template <typename T>
inline void	   safeDelete	(T& ptr)
{ 
  delete(ptr);
  ptr	= NULL;
}

class		Statement;

//  PURPOSE:  To serve as a global temporary C-string array.
extern
char		line[LINE_LEN];


//  PURPOSE:  To point to the root of the abstract syntax tree.
extern
Statement*	programRootPtr;


//  PURPOSE:  TO serve as the input file.
extern
FILE*		yyin;


//  PURPOSE:  To handle the outputing of parse-time error message 'cPtr'.
//	No return value.
extern
int		yyerror		(const char*	cPtr
				);


//  PURPOSE:  To return the integer encoding of the next token read.  No
//	parameters.  No return value.
extern
int		yylex		();


#include	"Exception.h"
#include	"Object.h"
#include	"Expression.h"
#include	"Statement.h"
#include	"VariableStore.h"


//  PURPOSE:  To hold the variables and their values.
extern
VariableStore	variableStore;