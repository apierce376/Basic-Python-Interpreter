/*-------------------------------------------------------------------------*
 *---									---*
 *---		Expression.h						---*
 *---									---*
 *---	    This file declares a base class and derived classes for a	---*
 *---	subset of the Python's Expressions.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 15		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class		Expression
{
  //  I.  Member vars:

  //  II.  Disallowed auto-generated methods:
  //  No copy assignment op:
  Expression&	operator=	(const Expression&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new Expression instance.  No parameters.  No return
  //	value.
  Expression			()
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  Expression			(const Expression&	source
				)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  virtual
  ~Expression			();


  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the address of an object that result from evaluating
  //	'*this'.  No parameters.
  virtual
  Object*	evaluate	()
				const
				= 0;

};


class		ConstantExpression : public Expression
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the Object of which to return a copy.
  Object*			objectPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy assignment op:
  ConstantExpression&
		operator=	(const ConstantExpression&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new ConstantExpression instance to represent bool
  //	value 'value'.  No return value.
  explicit
  ConstantExpression		(bool	value
				) :
				Expression(),
				objectPtr_(new BoolObject(value))
				{ }

  //  PURPOSE:  To create a new ConstantExpression instance to represent int
  //	value 'value'.  No return value.
  explicit
  ConstantExpression		(int	value
				) :
				Expression(),
				objectPtr_(new IntObject(value))
				{ }

  //  PURPOSE:  To create a new ConstantExpression instance to represent float
  //	value 'value'.  No return value.
  explicit
  ConstantExpression		(float	value
				) :
				Expression(),
				objectPtr_(new FloatObject(value))
				{ }

  //  PURPOSE:  To create a new ConstantExpression instance to represent string
  //	'cPtr'.  No return value.
  explicit
  ConstantExpression		(const char*	cPtr
				) :
				Expression(),
				objectPtr_(new StrObject(cPtr))
				{ }

  //  PURPOSE:  To create a new ConstantExpression instance to represent string
  //	value 'value'.  No return value.
  explicit
  ConstantExpression		(const std::string&	value
				) :
				Expression(),
				objectPtr_(new StrObject(value))
				{ }

  //  PURPOSE:  To make '*this' hold the object with address 'newObjPtr'.  No
  //	return value.
  explicit
  ConstantExpression		(Object*	newObjPtr
				) :
				Expression(),
				objectPtr_(newObjPtr)
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  explicit
  ConstantExpression		(const ConstantExpression&	source
				) :
				Expression(),
				objectPtr_(source.objectPtr_->copy())
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~ConstantExpression		()
				{
				  safeDelete(objectPtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the address of an object that result from evaluating
  //	'*this'.  No parameters.
  Object*	evaluate	()
				const
				{ return(objectPtr_->copy()); }

};


class		VariableExpression : public Expression
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the Object of which to return a copy.
  std::string			varName_;

  //  II.  Disallowed auto-generated methods:
  //  No copy assignment op:
  VariableExpression&
		operator=	(const VariableExpression&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new VariableExpression instance to represent
  //	variable 'newVarName'.  No return value.
  explicit
  VariableExpression		(const std::string&	newVarName
				) :
				Expression(),
				varName_(newVarName)
				{ }

  //  PURPOSE:  To create a new VariableExpression instance to represent
  //	variable 'newVarNameCPtr'.  No return value.
  explicit
  VariableExpression		(const char*	newVarNameCPtr
				) :
				Expression(),
				varName_(newVarNameCPtr)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~VariableExpression		()
				{
				}

  //  V.  Accessors:
  //  PURPOSE:  To hold the address of the Object of which to return a copy.
  const std::string&
		getVarName	()
				const
				{ return(varName_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the address of an object that result from evaluating
  //	'*this'.  No parameters.
  Object*	evaluate	()
				const;

};


class		UnaryExpression : public Expression
{
  //  I.  Member vars:
  //  PURPOSE:  To tell which operation to compute.
  operator_ty			operator_;

  //  PURPOSE:  To hold the address of the sole operand.
  Expression*			operandPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  UnaryExpression		(const UnaryExpression&
				);

  //  No copy assignment op:
  UnaryExpression&
		operator=	(const UnaryExpression&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new UnaryExpression instance to operator
  //	'newOperator' operating on the operand evaluated by 'newOperandPtr'.
  //	No return value.
  UnaryExpression		(operator_ty	newOperator,
				 Expression*	newOperandPtr
				) :
				Expression(),
				operator_(newOperator),
				operandPtr_(newOperandPtr)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~UnaryExpression		()
				{
				  safeDelete(operandPtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the address of an object that result from evaluating
  //	'*this'.  No parameters.
  Object*	evaluate	()
				const
				{
				  Object* opValPtr	=
				  	  	operandPtr_->evaluate();
				  Object* toReturnPtr	= NULL;

				  switch  (operator_)
				  {
				  case NOT_OP :
				    toReturnPtr	=
				    	new BoolObject(!opValPtr->toBool());
				    break;

				  case PLUS_OP :
				  case MINUS_OP :
				    switch  (opValPtr->getType())
				    {
				    case boolType :
				    case intType :
				      toReturnPtr	=
				      	(operator_ == PLUS_OP)
					? new IntObject( opValPtr->toInt())
					: new IntObject(-opValPtr->toInt());
				      break;

				    case floatType :
				      toReturnPtr	=
				    	(operator_ == PLUS_OP)
					? new IntObject( opValPtr->toFloat())
					: new IntObject(-opValPtr->toFloat());
				      break;

				    default :
				      throw Exception("TypeError: bad operand type for unary +: 'str'");
				    }
				    break;

				  default :
				    throw Exception("BUG: Attempt to compute operand %s as unary");
				  }

				  safeDelete(opValPtr);
				  return(toReturnPtr);
				}

};


class		BinaryExpression : public Expression
{
  //  I.  Member vars:
  //  PURPOSE:  To tell which operation to compute.
  operator_ty			operator_;

  //  PURPOSE:  To hold the address of the left-hand side operand.
  Expression*			lhsOperandPtr_;

  //  PURPOSE:  To hold the address of the right-hand side operand.
  Expression*			rhsOperandPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  BinaryExpression		(const BinaryExpression&
				);

  //  No copy assignment op:
  BinaryExpression&
		operator=	(const BinaryExpression&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new BinaryExpression instance to operator
  //	'newOperator' operating on the operands evaluated by 'newLhsOperandPtr'
  //	and 'newRhsOperandPtr'.  No return value.
  BinaryExpression		(operator_ty	newOperator,
				 Expression*	newLhsOperandPtr,
				 Expression*	newRhsOperandPtr
				) :
				Expression(),
				operator_(newOperator),
				lhsOperandPtr_(newLhsOperandPtr),
				rhsOperandPtr_(newRhsOperandPtr)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~BinaryExpression		()
				{
				  safeDelete(rhsOperandPtr_);
				  safeDelete(lhsOperandPtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the address of an object that result from evaluating
  //	'*this'.  No parameters.
  Object*	evaluate	()
				const;

};


class		AssignmentExpression : public Expression
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the left-hand side operand.
  Expression*			variablePtr_;

  //  PURPOSE:  To hold the address of the right-hand side operand.
  Expression*			rhsOperandPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  AssignmentExpression		(const AssignmentExpression&
				);

  //  No copy assignment op:
  AssignmentExpression&
		operator=	(const AssignmentExpression&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new AssignmentExpression instance to operator
  //	'newOperator' operating on the operands evaluated by 'newVariablePtr'
  //	and 'newRhsOperandPtr'.  No return value.
  AssignmentExpression		(Expression*	newVariablePtr,
				 Expression*	newRhsOperandPtr
				);

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~AssignmentExpression		()
				{
				  safeDelete(rhsOperandPtr_);
				  safeDelete(variablePtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the address of an object that result from evaluating
  //	'*this'.  No parameters.
  Object*	evaluate	()
				const;

};
