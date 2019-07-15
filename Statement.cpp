/*-------------------------------------------------------------------------*
 *---									---*
 *---		Statement.cpp						---*
 *---									---*
 *---	    This file defines members for a base class and derived	---*
 *---	classes for a subset of the Python's statements.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 16		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"ourPython.h"

//  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
//	value.
Statement::~Statement		()
{
}


//  PURPOSE:  To add another IfThenElseStatement with condition '*condPtr'
//	and then statement '*thenPtr' at the end of the else chain.  No
//	return value.
void		IfThenElseStatement::appendElif
				(Expression*	condPtr,
				 Statement*	thenPtr
				)
{
  //  I.  Application validity check:
  if  ( (condPtr == NULL)  ||  (thenPtr == NULL) )
    throw Exception("BUG: Attempt to append NULL as elif clause");

  //  II.  Append ifel:
  if  (elsePtr_ == NULL)
    elsePtr_	= new IfThenElseStatement(condPtr,thenPtr);
  else
    elsePtr_->appendElif(condPtr,thenPtr);

  //  III.  Finished:

}


//  PURPOSE:  To add final else statement '*elsePtr' at the end of the else
//	chain.  No return value.
void		IfThenElseStatement::appendElse
				(Statement*	elsePtr
				)
{
  //  I.  Application validity check:
  if  (elsePtr == NULL)
    throw Exception("BUG: Attempt to append NULL as else clause");

  //  II.  Append else:
  if  (elsePtr_ == NULL)
    elsePtr_	= elsePtr;
  else
    elsePtr_->appendElse(elsePtr);

  //  III.  Finished:
}
