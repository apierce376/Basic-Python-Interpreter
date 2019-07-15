/*-------------------------------------------------------------------------*
 *---									---*
 *---		Statement.h						---*
 *---									---*
 *---	    This file declares a base class and derived classes for a	---*
 *---	subset of the Python's statements.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 16		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class		Statement
{
  //  I.  Member vars:

  //  II.  Disallowed auto-generated methods:
  //  No copy assignment op:
  Statement&	operator=	(const Statement&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new Statement instance.  No parameters.  No return
  //	value.
  Statement			()
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  Statement			(const Statement&	source
				)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  virtual
  ~Statement			();

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To run '*this' Statement.  No parameters.
  virtual
  void		run		()
				const
				= 0;

  //  PURPOSE:  To add another IfThenElseStatement with condition '*condPtr'
  //	and then statement '*thenPtr' at the end of the else chain.  No
  //	return value.
  virtual
  void		appendElif	(Expression*	condPtr,
				 Statement*	thenPtr
				)
				{
				  throw Exception
					    ("Attempt to add elif"
					     " to non-If statement"
					    );
				}

  //  PURPOSE:  To add final else statement '*elsePtr' at the end of the else
  //	chain.  No return value.
  virtual
  void		appendElse	(Statement*	elsePtr
				)
				{
				  throw Exception
					    ("Attempt to add else"
					     " to non-If statement"
					    );
				}

  //  PURPOSE:  To add the Statement whose address is given in 'statePtr' as
  //	the next Statement to run in '*this' sequence.
  virtual
  void		addStatement 	(Statement*	statePtr
  				)
				{
				  throw Exception
					    ("Attempt to add statements"
					     " to non-BlockStatement"
					    );
				}

};


//  PURPOSE:  To represent the a statement that evaluates an Expression
class		ExpressionStatement : public Statement
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the expression to evaluate.
  Expression*			argPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  ExpressionStatement		(const ExpressionStatement&
				);

  //  No copy assignment op:
  ExpressionStatement&
	operator=		(const ExpressionStatement&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new ExpressionStatement instance to evaluate
  //  	'*newArgPtr'.  No return value.
  ExpressionStatement		(Expression*	newArgPtr
				) :
				Statement(),
				argPtr_(newArgPtr)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~ExpressionStatement		()
  				{
				  safeDelete(argPtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To run '*this' Statement.  No parameters.
  void		run		()
				const
				{
				  Object*	valPtr	= argPtr_->evaluate();

				  safeDelete(valPtr);
				}

  //  PURPOSE:  To return the current value of 'argPtr_' and to set it to
  //	'NULL'.  No parameters.
  Expression*	giveAwayExprPtr	()
				{
				  Expression*	toReturn	= argPtr_;

				  argPtr_			= NULL;
				  return(toReturn);
				}

};


//  PURPOSE:  To represent the 'print' statement.
class		PrintStatement : public Statement
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the optional argument whose value should
  //	be printed.
  Expression*			argPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  PrintStatement		(const PrintStatement&
				);

  //  No copy assignment op:
  PrintStatement&
	operator=		(const PrintStatement&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new PrintStatement instance to print the expression
  //  	computed by 'newArgPtr' (if it is not 'NULL').  No return value.
  PrintStatement		(Expression*	newArgPtr	= NULL
				) :
				Statement(),
				argPtr_(newArgPtr)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~PrintStatement		()
  				{
				  safeDelete(argPtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To run '*this' Statement.  No parameters.
  void		run		()
				const
				{
				  if  (argPtr_ != NULL)
				  {
				    Object*	valPtr	= argPtr_->evaluate();

				    printf("%s",valPtr->toStr().c_str());
				    safeDelete(valPtr);
				  }

				  putchar('\n');
				}

};


//  PURPOSE:  To represent a conventional 'if-then-else' statement.
class		IfThenElseStatement : public Statement
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the argument whose value is used as the
  //	conditional.
  Expression*			condPtr_;

  //  PURPOSE:  To hold the address of the argument to do if the conditional
  //	evaluates to 'true'.
  Statement*			thenPtr_;

  //  PURPOSE:  To hold the address of the optional argument to do if the
  //	conditional evaluates to 'false'.
  Statement*			elsePtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  IfThenElseStatement		(const IfThenElseStatement&
				);

  //  No copy assignment op:
  IfThenElseStatement&
	operator=		(const IfThenElseStatement&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new IfThenElseStatement instance to evaluate
  //	'*newCondPtr', and then do '*newThenPtr' if the condition evaluates
  //	to 'True', or to do '*newElsePtr' if the condition evaluates to 'False'
  //	and there is else code to do.  No return value.
  IfThenElseStatement		(Expression*	newCondPtr,
				 Statement*	newThenPtr,
				 Statement*	newElsePtr	= NULL
				) :
				Statement(),
				condPtr_(newCondPtr),
				thenPtr_(newThenPtr),
				elsePtr_(newElsePtr)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~IfThenElseStatement		()
  				{
				  safeDelete(elsePtr_);
				  safeDelete(thenPtr_);
				  safeDelete(condPtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To run '*this' Statement.  No parameters.
  void		run		()
				const
				{
				  Object* condValPtr = condPtr_->evaluate();

				  if  ( condValPtr->toBool() )
				    thenPtr_->run();
				  else
				  if  (elsePtr_ != NULL)
				    elsePtr_->run();

				  safeDelete(condValPtr);
				}

  //  PURPOSE:  To add another IfThenElseStatement with condition '*condPtr'
  //	and then statement '*thenPtr' at the end of the else chain.  No
  //	return value.
  void		appendElif	(Expression*	condPtr,
				 Statement*	thenPtr
				);

  //  PURPOSE:  To add final else statement '*elsePtr' at the end of the else
  //	chain.  No return value.
  void		appendElse	(Statement*	elsePtr
				);

};


//  PURPOSE:  To represent the 'while' statement.
class		WhileStatement : public Statement
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the address of the argument whose value is used as the
  //	conditional.
  Expression*			condPtr_;

  //  PURPOSE:  To hold the address of the argument to do while the conditional
  //	evaluates to 'true'.
  Statement*			bodyPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  WhileStatement		(const WhileStatement&
				);

  //  No copy assignment op:
  WhileStatement&
	operator=		(const WhileStatement&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new WhileStatement instance to evaluate
  //	'*newCondPtr', and then do '*newWhilePtr' until the condition evaluates
  //	to 'False'.  No return value.
  WhileStatement		(Expression*	newCondPtr,
				 Statement*	newBodyPtr
				) :
				Statement(),
				condPtr_(newCondPtr),
				bodyPtr_(newBodyPtr)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~WhileStatement		()
  				{
				  safeDelete(condPtr_);
				  safeDelete(bodyPtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To run '*this' Statement.  No parameters.
  void		run		()
				const
				{
				  Object* condValPtr;

				  while  ( condValPtr = condPtr_->evaluate(),
				  	   condValPtr->toBool()
					 )
				  {
				    safeDelete(condValPtr);
				    bodyPtr_->run();
				  }

				  safeDelete(condValPtr);
				}

};


//  PURPOSE:  To represent the 'while' statement.
class		BlockStatement : public Statement
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the addresses of the Statement instances to execute in
  //	order.
  std::vector<Statement*>	bodyDS_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  BlockStatement		(const BlockStatement&
				);

  //  No copy assignment op:
  BlockStatement&
	operator=		(const BlockStatement&
				);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new BlockStatement instance to evaluate Statement
  //	instances in order.  No parameters.  No return value.
  BlockStatement		() :
				Statement(),
				bodyDS_()
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~BlockStatement		()
  				{
				  int	i;

				  for  (i = bodyDS_.size() - 1;  i >= 0;  i--)
				    safeDelete(bodyDS_[i]);

				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To run '*this' Statement.  No parameters.
  void		run		()
				const
				{
				  size_t	i;

				  for  (i = 0;  i < bodyDS_.size();  i++)
				    bodyDS_[i]->run();
				}

  //  PURPOSE:  To add the Statement whose address is given in 'statePtr' as
  //	the next Statement to run in '*this' sequence.
  void		addStatement 	(Statement*	statePtr
  				)
				{
				  if  (statePtr == NULL)
				    throw Exception
						("BUG: Attempt to add NULL"
						 " statement to a block"
						);

				  bodyDS_.push_back(statePtr);
				}

};
