/*-------------------------------------------------------------------------*
 *---									---*
 *---		Expression.cpp						---*
 *---									---*
 *---	    This file defines members of a base class and derived	---*
 *---	classes for a subset of the Python's Expressions.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 15		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"ourPython.h"


//  PURPOSE:  To return the string 'str' replicated 'times' times.
std::string	stringReplicate	(int			times,
				 const std::string&	str
				)
{
  //  I.  Application validity check:
  if  (times <= 0)
    return(std::string(""));

  //  II.  Replicate string:
  std::string	toReturn	= str;

  while  (--times > 0)
    toReturn += str;

  //  III.  Finished:
  return(toReturn);
}


//  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
//	value.
Expression::~Expression		()
{
}



//  PURPOSE:  To return the address of an object that result from evaluating
//	'*this'.  No parameters.
Object*		VariableExpression::evaluate
				()
				const
{
  //  I.  Application validity check:

  //  II.  Look up value:
  const Object*	objPtr	= variableStore.get(varName_);

  if  (objPtr == NULL)
  {
    snprintf(line,LINE_LEN,"NameError: name '%s' is not defined",
	     varName_.c_str()
	    );
    throw Exception(line);
  }

  //  III.  Return value:
  return(objPtr->copy());
}


//  PURPOSE:  To return the address of an object that result from evaluating
//	'*this'.  No parameters.
Object*		BinaryExpression::evaluate
				()
				const
{
  //  I.  Application validity check:

  //  II.  Compute result:
  Object* lhsValPtr	= lhsOperandPtr_->evaluate();
  Object* rhsValPtr	= NULL;
  Object* toReturnPtr	= NULL;

  if  (operator_ == OR_OP)
  {
    if  ( lhsValPtr->toBool() )
      return(lhsValPtr);

    safeDelete(lhsValPtr);
    toReturnPtr	= rhsOperandPtr_->evaluate();
  }
  else
  if  (operator_ == AND_OP)
  {
    if  ( !lhsValPtr->toBool() )
      return(lhsValPtr);

    safeDelete(lhsValPtr);
    toReturnPtr	= rhsOperandPtr_->evaluate();
  }
  else
  {
    rhsValPtr		= rhsOperandPtr_->evaluate();

    switch  (operator_)
    {
    case PLUS_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  (  rhsValPtr->getType() )
        {
        case boolType :
        case intType :
	  toReturnPtr = new IntObject(lhsValPtr->toInt() + rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr = new FloatObject
				(lhsValPtr->toFloat() + rhsValPtr->toFloat()
				);
	  break;

	default :
	  snprintf(line,LINE_LEN,
		   "TypeError: cannot concatenate '%s' and '%s' objects",
		   typeNameArray[lhsValPtr->getType()],
		   typeNameArray[rhsValPtr->getType()]
		  );
	  throw Exception(line);
        }

	break;

      case floatType :
        switch  (  rhsValPtr->getType() )
        {
        case boolType :
        case intType :
	case floatType :
	  toReturnPtr = new FloatObject
				(lhsValPtr->toFloat() + rhsValPtr->toFloat()
				);
	  break;

	default :
	  snprintf(line,LINE_LEN,
		   "TypeError: cannot multiply '%s' and '%s' objects",
		   typeNameArray[lhsValPtr->getType()],
		   typeNameArray[rhsValPtr->getType()]
		  );
	  throw Exception(line);
        }

      	break;

      default :
	break;
      }

      break;

    case MINUS_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  (  rhsValPtr->getType() )
        {
        case boolType :
        case intType :
	  toReturnPtr = new IntObject(lhsValPtr->toInt() - rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr = new FloatObject
				(lhsValPtr->toFloat() - rhsValPtr->toFloat()
				);
	  break;

	default :
	  snprintf(line,LINE_LEN,
		   "TypeError: unsupported operand"
		   " type(s) for -: '%s' and '%s'",
		   typeNameArray[lhsValPtr->getType()],
		   typeNameArray[rhsValPtr->getType()]
		  );
	  throw Exception(line);
        }
	break;

      case floatType :
	toReturnPtr = new FloatObject
				(lhsValPtr->toFloat() - rhsValPtr->toFloat()
				);
	break;

      default :
	snprintf(line,LINE_LEN,
		 "TypeError: unsupported operand type(s) for -: '%s' and '%s'",
		 typeNameArray[lhsValPtr->getType()],
		 typeNameArray[rhsValPtr->getType()]
		);
	throw Exception(line);
      }
      break;

    case STAR_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  (  rhsValPtr->getType() )
        {
        case boolType :
        case intType :
	  toReturnPtr = new IntObject(lhsValPtr->toInt() * rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr = new FloatObject
				(lhsValPtr->toFloat() * rhsValPtr->toFloat()
				);
	  break;

	case strType :
	  toReturnPtr = new StrObject
				(stringReplicate
				    (lhsValPtr->toInt(),
				     rhsValPtr->toStr()
				    )
				);
	  break;

	default :
	  snprintf(line,LINE_LEN,
		   "TypeError: unsupported operand"
		   " type(s) for *: '%s' and '%s'",
		   typeNameArray[lhsValPtr->getType()],
		   typeNameArray[rhsValPtr->getType()]
		  );
	  throw Exception(line);
        }

	break;

      case floatType :
	toReturnPtr = new FloatObject
				(lhsValPtr->toFloat() * rhsValPtr->toFloat()
				);
	break;

      case strType :
      	switch  (  rhsValPtr->getType() )
        {
        case boolType :
        case intType :
	  toReturnPtr = new StrObject
				(stringReplicate
				    (rhsValPtr->toInt(),
				     lhsValPtr->toStr()
				    )
				);
	  break;

	default :
	  snprintf(line,LINE_LEN,
		   "TypeError: unsupported operand"
		   " type(s) for *: '%s' and '%s'",
		   typeNameArray[lhsValPtr->getType()],
		   typeNameArray[rhsValPtr->getType()]
		  );
	  throw Exception(line);
	}

      default :
	snprintf(line,LINE_LEN,
		   "TypeError: unsupported operand"
		   " type(s) for *: '%s' and '%s'",
		   typeNameArray[lhsValPtr->getType()],
		   typeNameArray[rhsValPtr->getType()]
		  );
	throw Exception(line);
      }

      break;

    case SLASH_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  (  rhsValPtr->getType() )
        {
        case boolType :
        case intType :
	  toReturnPtr = new IntObject(lhsValPtr->toInt() / rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr = new FloatObject
				(lhsValPtr->toFloat() / rhsValPtr->toFloat()
				);
	  break;

	default :
	  snprintf(line,LINE_LEN,
		   "TypeError: unsupported operand"
		   " type(s) for /: '%s' and '%s'",
		   typeNameArray[lhsValPtr->getType()],
		   typeNameArray[rhsValPtr->getType()]
		  );
	  throw Exception(line);
        }

	break;

      case floatType :
	  toReturnPtr = new FloatObject
				(lhsValPtr->toFloat() / rhsValPtr->toFloat()
				);
	break;

      default :
	snprintf(line,LINE_LEN,
		 "TypeError: unsupported operand type(s) for /: '%s' and '%s'",
		 typeNameArray[lhsValPtr->getType()],
		 typeNameArray[rhsValPtr->getType()]
		);
	throw Exception(line);
      }

      break;

    case LESSER_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toInt() < rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() < rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(true);
	  break;
	}

      	break;

      case floatType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() < rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(true);
	  break;
	}

      	break;

      case strType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =	new BoolObject(false);
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(lhsValPtr->toStr() < rhsValPtr->toStr());
	  break;
	}
      	break;

      }
      break;

    case LESSER_EQUAL_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toInt() <= rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() <= rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(true);
	  break;
	}

      	break;

      case floatType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() <= rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(true);
	  break;
	}

      	break;

      case strType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =	new BoolObject(false);
	  break;

	case strType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toStr() <= rhsValPtr->toStr());
	  break;
	}
      	break;

      }
      break;

    case GREATER_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toInt() > rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() > rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(false);
	  break;
	}

      	break;

      case floatType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() > rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(false);
	  break;
	}

      	break;

      case strType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =	new BoolObject(true);
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(lhsValPtr->toStr() > rhsValPtr->toStr());
	  break;
	}
      	break;

      }
      break;

    case GREATER_EQUAL_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toInt() >= rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() >= rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(false);
	  break;
	}

      	break;

      case floatType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() >= rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(false);
	  break;
	}

      	break;

      case strType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =	new BoolObject(true);
	  break;

	case strType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toStr() >= rhsValPtr->toStr());
	  break;
	}
      	break;

      }
      break;

    case EQUAL_EQUAL_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toInt() == rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() == rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(false);
	  break;
	}

      	break;

      case floatType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() == rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(false);
	  break;
	}

      	break;

      case strType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =	new BoolObject(false);
	  break;

	case strType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toStr() == rhsValPtr->toStr());
	  break;
	}
      	break;

      }
      break;

    case NOT_EQUAL_OP :
      switch  ( lhsValPtr->getType() )
      {
      case boolType :
      case intType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toInt() != rhsValPtr->toInt());
	  break;

	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() != rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(true);
	  break;
	}

      	break;

      case floatType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toFloat() != rhsValPtr->toFloat());
	  break;

	case strType :
	  toReturnPtr =	new BoolObject(true);
	  break;
	}

      	break;

      case strType :
        switch  ( rhsValPtr->getType() )
	{
	case boolType :
	case intType :
	case floatType :
	  toReturnPtr =	new BoolObject(true);
	  break;

	case strType :
	  toReturnPtr =
		new BoolObject(lhsValPtr->toStr() != rhsValPtr->toStr());
	  break;
	}
      	break;

      }
      break;

    case SLASH_SLASH_OP :
      throw Exception("// not yet supported");

    case STAR_STAR_OP :
      throw Exception("** not yet supported");

    case PERCENT_OP :
      throw Exception("% not yet supported");

    default :
      snprintf(line,LINE_LEN,
	       "Unhandled operator ordinal %d in BinaryExpression()",operator_
	      );
      throw Exception(line);
    }

    safeDelete(rhsValPtr);
    safeDelete(lhsValPtr);
  }

  //  III.  Finished:
  return(toReturnPtr);
}


//  PURPOSE:  To create a new AssignmentExpression instance to operator
//	'newOperator' operating on the operands evaluated by 'newVariablePtr'
//	and 'newRhsOperandPtr'.  No return value.
AssignmentExpression::AssignmentExpression
				(Expression*	newVariablePtr,
				 Expression*	newRhsOperandPtr
				) :
				Expression(),
				variablePtr_(newVariablePtr),
				rhsOperandPtr_(newRhsOperandPtr)
{
  //  I.  Application validity check:
  if  (dynamic_cast<VariableExpression*>(newVariablePtr) == NULL)
  {
    throw Exception("BUG: Assignment to other than vars not yet supported");
  }

  //  II.  Assign member vars:

  //  III.  Finished:
}


//  PURPOSE:  To return the address of an object that result from evaluating
//	'*this'.  No parameters.
Object*		AssignmentExpression::evaluate
				()
				const
{
  //  I.  Application validity check:
  //  II.  Do assignment:
  Object*	valuePtr	= rhsOperandPtr_->evaluate();
  std::string	varName		= dynamic_cast<VariableExpression*>
					(variablePtr_)->getVarName();

  variableStore.store(varName,valuePtr);

  //  III.  Finished:
  return(valuePtr->copy());
}