%{
  //  -----------------------------------------------------------------	//
  //									//
  //		ourPython.lex						//
  //									//
  //	    This file defines a flex file that defines a C++ program	//
  //	that outputs the tokens encountered in a Python source file.	//
  //	For the parser's sake, it keeps track of indentation and	//
  //	outputs BEGIN_INDENT when there is more indentation and		//
  //	END_INDENT when there is less.					//
  //									//
  //	----	----	----	----	----	----	----	----	//
  //									//
  //	Version 1a		2018 April 13		Joseph Phillips	//
  //									//
  //  -----------------------------------------------------------------	//

  //  Compile and run with:
  //    $ flex -o ourPythonTokenizer.cpp ourPython.lex
  //    $ g++ ourPythonTokenizer.cpp -o ourPython
  //    $ ./ourPython computeBMI.py

#include	"ourPython.h"
#include	"ourPython.tab.h"

//  PURPOSE:  To tell the size of typical buffers.
const int	BUFFER_LEN		= 4080;


//  PURPOSE:  To tell how many spaces are implied by a tab char.
const int	NUM_SPACES_PER_TAB	= 8;


//  PURPOSE:  To hold the indentation so far on the current line.
extern int	numSpacesSinceNewLine;


//  PURPOSE:  To hold the indentation of the line before the current line.
extern int	lastIndentCount;


//  PURPOSE:  To hold 'true' when should count spaces for indentation
//	comparison purposes, or 'false' otherwise.
extern bool	shouldCount;

#undef 		YY_INPUT

#define		YY_INPUT(buffer,numRetChars,bufferLen)	\
		{ numRetChars = getLexChar(buffer,bufferLen); }

#define		YY_DECL					\
		int		ylex	(void)


//  PURPOSE:  To read the next char from 'yyin' and put it into 'buffer' of
//	length 'bufferLen'.  Returns '1' to signify that only one char was
//	obtained on success, or returns 'YY_NULL' on EOF error otherwise.
extern
int		getLexChar	(char*		buffer,
       				 int		bufferLen
				);

%}

DIGIT [0-9]
ID [A-Za-z_][A-Za-z_0-9]*

%%
"#"			{
			  int	i;

			  while   ( (i = yyinput()) != EOF )
			  {
			    if  (i == '\n')
			    {
			      numSpacesSinceNewLine = 0;
			      break;
			    }
			  }
			  shouldCount		= true;
			  return(NEWLINE);
			}
\n			{
			  numSpacesSinceNewLine = 0;
			  shouldCount		= true;
			  return(NEWLINE);
			}
" "			{
			  if (shouldCount)
			    numSpacesSinceNewLine++;
			}
\t			{
			  if (shouldCount)
			    numSpacesSinceNewLine += NUM_SPACES_PER_TAB;
			}
("+"|­"-")?{DIGIT}+ {
  yylval.intValue = strtol(strdup(yytext), NULL, 10);
  return(INTEGER);
}
("+"|­"-")?[0-9]+"."[0-9]* {
  yylval.floatValue = strtof(strdup(yytext), NULL);
  return(FLOAT);
}
\"(\\.|[^\\"])*\" {
  yytext[strlen(yytext)-1] = '\0';
  yylval.stringValue = strdup(yytext+1);
  return(STRING);
}
\'(\\.|[^\\"])*\' {
  yytext[strlen(yytext)-1] = '\0';
  yylval.stringValue = strdup(yytext+1);
  return(STRING);
}
"True" {
  yylval.boolValue = true;
  return(BOOLEAN);
}
"False" return(FALSE); {
  yylval.boolValue = false;
  return(BOOLEAN);
}
"or"    return(OR);
"and"   return(AND);
"not"   return(NOT);
"<="    return(LESSER_EQUAL);
">="    return(GREATER_EQUAL);
"<"     return(LESSER);
">"     return(GREATER);
"=="    return(EQUALS);
"!="    return(NOT_EQUAL);
"="     return(EQUAL);
"+"     return(PLUS);
"-"     return(MINUS);
"*"     return(STAR);
"/"     return(SLASH);
";"     return(SEMICOLON);
":"     return(COLON);
","     return(COMMA);
"("     return(BEGIN_PAREN);
")"     return(END_PAREN);
"if"    return(IF);
"elif"  return(ELIF);
"else"  return(ELSE);
"while" return(WHILE);
"print" return(PRINT);
{ID} {
  yylval.stringValue = strdup(yytext);
  return(NAME);
}
.			{
			  snprintf(line,LINE_LEN,"What is %c?\n",yytext[0]);
			  throw Exception(line);
			}
%%
//  PURPOSE:  To hold the indentation so far on the current line.
int		numSpacesSinceNewLine
				= 0;


//  PURPOSE:  To hold the indentation of the line before the current line.
int		lastIndentCount	= 0;


//  PURPOSE:  To hold 'true' when should count spaces for indentation
//	comparison purposes, or 'false' otherwise.
bool		shouldCount	= true;


//  PURPOSE:  To read the next char from 'yyin' and put it into 'buffer' of
//	length 'bufferLen'.  Returns '1' to signify that only one char was
//	obtained on success, or returns 'YY_NULL' on EOF error otherwise.
int		getLexChar	(char*	buffer,
				 int	bufferLen
				)
{
  //  PURPOSE:  To hold the chars of the most recently read line:
  static
  char		line[BUFFER_LEN];

  //  PURPOSE:  To hold the position of the next char to read in 'linePtr',
  //	or 'line + BUFFER_LEN' if should read a new line.
  static
  char*		linePtr	= line + BUFFER_LEN;


  //  I.  Application validity check:

  //  II.  Get next char:
  if  ( feof(yyin) )
  {
    //  II.A.  Note when at end-of-file:
    return(YY_NULL);
  }
  else
  {
    //  II.B.  Have not encountered EOF yet, attempt to get next char:
    //  II.B.1.  Read next line if at end of current one:
    if  ( (linePtr >= line + BUFFER_LEN)  ||  (*linePtr == '\0') )
    {
      //  II.B.1.a.  Attempt to read next line, note if find EOF instead:
      if  (fgets(line,BUFFER_LEN,yyin) == NULL)
      {
        return(YY_NULL);
      }

      //  II.B.1.b.  Prepare to read from beginning of new line:
      linePtr = line;
    }

    //  II.B.2.  Store next char in 'buffer':
    buffer[0]	= *linePtr++;
    buffer[1]	= '\0';
  }

  //  III.  Finished:
  return(1);
}


//  PURPOSE:  To serve as a wrapper to the next-token-returning, flex-generated
//  function 'ylex()'.  Keeps track of changes in indentation with global
//  vars 'shouldCount', 'lastIndentCount' and 'numSpacesSinceNewLine'.
//  No parameters.
int   yylex   ()
{
  //  PURPOSE:  To hold the token that was read, and that should be 'return'-ed
  //    on the current call to this function if either 'BEGIN_INDENT' or
  //  'END_INDENT' was returned on the last call.
  static
  int lastResult    = YY_NULL;

  static
  bool  wasLastResultNewline  = false;

  static
  bool  haveReportedLastNewline = false;


  //  I.  Application validity check:

  //  II.  Get integer value of token to return:
  //  II.B.  Get integer value of token to return:
  int   toReturn;

  if  (lastResult != YY_NULL)
  {
    //  II.A.  Return 'lastResult' if it holds a legitimate token:
    toReturn  = lastResult;
    lastResult  = YY_NULL;
    wasLastResultNewline = false;
  }
  else
  {
    //  II.B.  No previously stored token, should get next token:
    //  II.B.1.  Get next token:
    toReturn  = ylex();

    if  (wasLastResultNewline && (numSpacesSinceNewLine != lastIndentCount) )
    {
      //  II.B.3.a.  Remember read token for next call:
      lastResult  = toReturn;

      //  II.B.3.b.  Determine if indented or un-indented:
      if  (numSpacesSinceNewLine > lastIndentCount)
      {
        toReturn  = BEGIN_INDENT;
      }
      else
      {
        toReturn  = END_INDENT;
      }

      //  II.B.3.c.  Remember this level of indentation for next time
      lastIndentCount = numSpacesSinceNewLine;
    }
    else
      wasLastResultNewline = (toReturn == NEWLINE);

  }

    if  ( (toReturn == 0)  &&  !haveReportedLastNewline )
    {
      haveReportedLastNewline = true;
      toReturn      = NEWLINE;
    }

  //  III.  Finished:
  return(toReturn);
}


//  PURPOSE:  To return '0' if tokenizing should continue after reaching feof()
//	on 'yyin', or '1' otherwise.  No parameters.
int		yywrap		()
{
  //  I.  Application validity check:

  //  II.  Return value:
  return(1);
}
