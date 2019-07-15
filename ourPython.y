%{

/*-------------------------------------------------------------------------*
 *---									---*
 *---		ourPython.y						---*
 *---									---*
 *---	    This file defines the parser and high-level functions that	---*
 *---	implement a basic Python interpreter.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 16		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*

				Compile with:
bison -d --debug ourPython.y
g++ -c ourPython.tab.c -g
flex -o ourPython.cpp ourPython.lex 
g++ -c ourPython.cpp -g
g++ -c Object.cpp -g
g++ -c Expression.cpp -g
g++ -c Statement.cpp -g
g++ -o ourPython ourPython.tab.o ourPython.o Object.o Expression.o Statement.o

 *-------------------------------------------------------------------------*/


#include	"ourPython.h"

%}

%union
{
	int intValue;
	float floatValue;
	char* stringValue;
	bool boolValue;
	Object* value;
	Expression* exprPtr;
	Statement* statePtr;
}

%error-verbose

%start					single_input
%token					NEWLINE
%token					SEMICOLON COLON COMMA
%token					BEGIN_PAREN END_PAREN
%token					IF ELIF ELSE WHILE
%token					PRINT
%token					LESSER LESSER_EQUAL GREATER GREATER_EQUAL EQUALS NOT_EQUAL
%token					TRUE FALSE
%token					PLUS MINUS STAR SLASH EQUAL
%token					AND OR NOT
%token					BEGIN_INDENT END_INDENT
%token	<intValue>		INTEGER
%token	<floatValue>	FLOAT
%token	<stringValue>	STRING
%token	<stringValue>	NAME
%token	<boolValue>		BOOLEAN
%type	<statePtr>		single_input
%type	<statePtr>		if_stmt
%type	<statePtr>		while_stmt
%type	<statePtr>		suite
%type	<statePtr>		stmt
%type	<statePtr>		stmt_list
%type	<statePtr>		simple_stmt
%type	<statePtr>		proto_simple_stmt
%type	<statePtr>		compound_stmt
%type	<statePtr>		proto_if_stmt
%type	<statePtr>		small_stmt
%type	<statePtr>		expr_stmt
%type	<exprPtr>		test
%type	<exprPtr>		and_test
%type	<exprPtr>		or_test
%type	<exprPtr>		not_test
%type	<exprPtr>		comparison
%type	<exprPtr>		expr
%type	<exprPtr>		xor_expr
%type	<exprPtr>		and_expr
%type	<exprPtr>		shift_expr
%type	<exprPtr>		arith_expr
%type	<exprPtr>		term
%type	<exprPtr>		factor
%type	<exprPtr>		power
%type	<exprPtr>		atom_expr
%type	<exprPtr>		atom

%%

single_input : {
		    return(1);
		  }
		| NEWLINE
		  {
		    programRootPtr = $$	= NULL;
		    YYACCEPT;
		  }
		| simple_stmt
		  {
		    programRootPtr = $$	= $1;
		    YYACCEPT;
		  }
		| compound_stmt
		  NEWLINE
		  {
		    programRootPtr = $$	= $1;
		    YYACCEPT;
		  };

stmt : simple_stmt
		  {
		  	$$ = $1;
		  }
		| compound_stmt
		  {
		  	$$ = $1;
		  };

stmt_list : stmt
		  {
		  	$$ = new BlockStatement();
		  	$$->addStatement($1);
		  }
		| stmt_list
		  stmt
		  {
		  	$$ = $1;
		  	$$->addStatement($2);
		  }

simple_stmt	: proto_simple_stmt
			  NEWLINE
		  {
			$$ = $1;
		  }

proto_simple_stmt : small_stmt
		  {
		  	$$ = $1;
		  }
		| small_stmt
		  SEMICOLON
		  {
		  	$$ = new BlockStatement();
		  	$$->addStatement($1);
		  }
		| proto_simple_stmt
		  small_stmt
		  {
		  	$$ = $1;
		  	$$->addStatement($2);
		  }
		| proto_simple_stmt
		  small_stmt
		  SEMICOLON
		  {
		  	$$ = $1;
		  	$$->addStatement($2);
		  }

small_stmt : expr_stmt
		  {
		    $$	= $1;
		  }
		| PRINT
		  {
		    $$	= new PrintStatement;
		  }
		| PRINT
		  test
		  {
		    $$	= new PrintStatement($2);
		  }
		| test
		  EQUAL
		  test
		  {
		    $$	= new ExpressionStatement(new AssignmentExpression($1,$3));
		  };

expr_stmt : test
		  {
		    $$	= new ExpressionStatement($1);
		  };

compound_stmt : if_stmt
		  {
		  	$$ = $1;
		  }
		| while_stmt
		  {
		  	$$ = $1;
		  }

if_stmt	: proto_if_stmt
		  {
		  	$$ = $1;
		  }
		| proto_if_stmt
		  ELSE
		  COLON
		  suite
		  {
		  	$$ = $1;
		  	$1->appendElse($4);
		  };

proto_if_stmt : IF
				test
				COLON
				suite
		  {
		  	$$ = new IfThenElseStatement($2, $4);
		  }
		| proto_if_stmt
		  ELIF
		  test
		  COLON
		  suite
		  {
		  	$$ = $1;
		  	$$->appendElif($3, $5);
		  }

while_stmt : WHILE
			 test
			 COLON
			 suite
		  {
			$$ = new WhileStatement($2, $4);
		  }

suite : simple_stmt
		  {
		  	$$ = $1;
		  }
		| NEWLINE
		  BEGIN_INDENT
		  stmt_list
		  END_INDENT
		  {
		  	$$ = $3;
		  }

test : or_test
		  {
		    $$ = $1;
		  };

or_test	: and_test
		  {
		    $$ = $1;
		  }
		| or_test
		  OR
		  and_test
		  {
		    $$	= new BinaryExpression(OR_OP,$1,$3);
		  };

and_test : not_test
		  {
		  	$$ = $1;
		  }
		| not_test
		  AND
		  not_test
		  {
		  	$$	= new BinaryExpression(AND_OP,$1,$3);
		  };

not_test : NOT
		   not_test
		  {
			$$ = new UnaryExpression(NOT_OP,$2);
		  }
		| comparison
		  {
			$$ = $1;
		  }

comparison : expr
		  {
		  	$$ = $1;
		  }
		| expr
		  LESSER
		  expr
		  {
		  	$$ = new BinaryExpression(LESSER_OP, $1, $3);
		  }
		| expr
		  LESSER_EQUAL
		  expr
		  {
		  	$$ = new BinaryExpression(LESSER_EQUAL_OP, $1, $3);
		  }
		| expr
		  GREATER
		  expr
		  {
		  	$$ = new BinaryExpression(GREATER_OP, $1, $3);
		  }
		| expr
		  GREATER_EQUAL
		  expr
		  {
		  	$$ = new BinaryExpression(GREATER_EQUAL_OP, $1, $3);
		  }
		| expr
		  EQUALS
		  expr
		  {
		  	$$ = new BinaryExpression(EQUAL_EQUAL_OP, $1, $3);
		  }
		| expr
		  NOT_EQUAL
		  expr
		  {
		  	$$ = new BinaryExpression(NOT_EQUAL_OP, $1, $3);
		  }

expr : xor_expr
		  {
		  	$$ = $1;
		  }

xor_expr : and_expr
		  {
			$$ = $1;
		  }

and_expr : shift_expr
		  {
			$$ = $1;
		  }

shift_expr : arith_expr
		  {
			$$ = $1;
		  }

arith_expr : term
		  {
			$$ = $1;
		  }
		| term
		  PLUS
		  term
		  {
			$$ = new BinaryExpression(PLUS_OP, $1, $3);
		  }
		| term
		  MINUS
		  term
		  {
			$$ = new BinaryExpression(MINUS_OP, $1, $3);
		  }

term : factor
		  {
		  	$$ = $1;
		  }
		| factor
		  STAR
		  factor
		  {
		  	$$ = new BinaryExpression(STAR_OP, $1, $3);
		  }
		| factor
		  SLASH
		  factor
		  {
		  	$$ = new BinaryExpression(SLASH_OP, $1, $3);
		  }

factor : PLUS
		  factor
		  {
		  	$$ = new UnaryExpression(PLUS_OP, $2);
		  }
		| MINUS
		  factor
		  {
		  	$$ = new UnaryExpression(MINUS_OP, $2);
		  }
		| power
		  {
		  	$$ = $1;
		  }

power : atom_expr
		  {
		  	$$ = $1;
		  }

atom_expr : atom
		  {
			$$ = $1;
		  }

atom : NAME
		  {
		  	$$ = new VariableExpression($1);
		  }
		| INTEGER
		  {
		  	$$ = new ConstantExpression($1);
		  }
		| FLOAT
		  {
		  	$$ = new ConstantExpression($1);
		  }
		| STRING
		  {
		  	$$ = new ConstantExpression($1);
		  }
		| BOOLEAN
		  {
		  	$$ = new ConstantExpression($1);
		  }
		| BEGIN_PAREN
		  test
		  END_PAREN
		  {
		  	$$ = $2;
		  }

%%


//  PURPOSE:  To tell the printable names of the values of 'pythonType_ty'.
const char*	typeNameArray[]
      		= {
		    "none",
		    "bool",
		    "int",
		    "float",
		    "str",
		    "type"
		  };


//  PURPOSE:  To tell the printable names of the values of 'operator_ty'.
const char*	operatorNameArray[]
      		= {
		    "OR",
		    "AND",
		    "NOT",
		    "+",
		    "-",
		    "*",
		    "/",
		    "%",
		    "//",
		    "**"
		  };


//  PURPOSE:  To hold the names of boolean constants.
const char*	booleanConstName[]
		= { "False",
		    "True"
		  };


//  PURPOSE:  To serve as a global temporary C-string array.
char		line[LINE_LEN];


//  PURPOSE:  To point to the root of the abstract syntax tree.
Statement*	programRootPtr	= NULL;


//  PURPOSE:  To hold the variables and their values.
VariableStore	variableStore;


//  PURPOSE:  To handle the outputing of parse-time error message 'cPtr'.
//	No return value.
int		yyerror		(const char*	cPtr
				)
{
  throw Exception(cPtr);
}


//  PURPOSE:  To interpret and run the Python program given in 'argv[1]'.
//	Returns 'EXIT_SUCCESS' on success or 'EXIT_FAILURE' otherwise.
int		main		(int		argc,
				 char*		argv[]
				)
{
  //  I.  Application validity check:
  if  (argc < 2)
  {
    fprintf(stderr,"Usage:\t%s <pythonProg>\n",argv[0]);
    exit(EXIT_FAILURE);
  }

  //  II.  Parse and execute program:
  //  II.A.  Initialize file:
  const char*	pythonFilepath	= argv[1];

  if  ( (yyin = fopen(pythonFilepath,"r")) == NULL )
  {
    fprintf(stderr,"Error opening %s.\n",pythonFilepath);
    exit(EXIT_FAILURE);
  }

  //  II.B.  Attempt to parse and assemble 'yyin':
  int	status	= EXIT_SUCCESS;

  try
  {
    //  II.B.1.  Attempt to parse:
    while  ( !feof(yyin) && (yyparse() == 0) )
    {
      //  II.B.1.a.  Parse was successful and have tree:
      if  (programRootPtr != NULL)
      {

        //  II.B.1.a.I.  It highest Statement was an Expression,
        //  	       then convert it to a Print so output is generated:
        ExpressionStatement*	exprPtr;

        exprPtr	= dynamic_cast<ExpressionStatement*>(programRootPtr);

        if  (exprPtr != NULL)
        {
	  programRootPtr = new PrintStatement(exprPtr->giveAwayExprPtr());

	  safeDelete(exprPtr);
        }

        //  II.B.1.a.II.  Walk tree to evaluate it:
        programRootPtr->run();

        //  II.B.1.a.III.  Release memory:
        safeDelete(programRootPtr);
      }
    }

  }
  catch  (Exception error)
  {
    fprintf(stderr,"Error: %s\n",error.getDescription().c_str());
    status	= EXIT_FAILURE;
  }

  //  II.C.  Clean up:
  fclose(yyin);

  //  III.  Finished:
  return(status);
}
