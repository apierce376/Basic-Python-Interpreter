/*-------------------------------------------------------------------------*
 *---									---*
 *---		Object.h						---*
 *---									---*
 *---	    This file declares a base class and derived classes for a	---*
 *---	subset of the Python's predefined Object hierarchy.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 15		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class		Object
{
  //  I.  Member vars:

  //  II.  Disallowed auto-generated methods:

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new Object instance.  No parameters.  No return
  //	value.
  Object			()
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  Object			(const Object&	source
				)
				{ }

  //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
  //	'source', and to return a reference to '*this'.
  Object&	operator=	(const Object&	source
  				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				    return(*this);

				  //  II.  Release resources of '*this':

				  //  III.  Copy 'source':

				  //  IV.  Finished:
				  return(*this);
				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  virtual
  ~Object			();

  //  PURPOSE:  To return a copy of '*this'.  No parameters.
  virtual
  Object*	copy		()
				const
				= 0;

  //  V.  Accessors:
  //  PURPOSE:  To return the type of '*this'.  No parameters.
  virtual
  pythonType_ty	getType		()
  				const
  				= 0;

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the internal C++ boolean value represented by '*this'.
  //	No parameters.
  virtual
  bool		toBool		()
				const
				= 0;

  //  PURPOSE:  To return the internal C++ integer value represented by '*this'.
  //	No parameters.
  virtual
  int		toInt		()
				const
				= 0;

  //  PURPOSE:  To return the internal C++ float value represented by '*this'.
  //	No parameters.
  virtual
  float		toFloat		()
				const
				= 0;

  //  PURPOSE:  To return the internal C++ string value represented by '*this'.
  //	No parameters.
  virtual
  std::string	toStr		()
				const
				= 0;

};


//  PURPOSE:  To represent a Python bool object.
class		BoolObject : public Object
{
  //  I.  Member vars:
  //  PURPOSE:  To represent the value.
  bool				value_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  BoolObject			();

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new BoolObject instance to hold 'value'.  No return
  //	value.
  BoolObject			(bool	newValue
				) :
				Object(),
				value_(newValue)
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  BoolObject			(const BoolObject&	source
				) :
				Object(source),
				value_(source.getValue())
				{ }

  //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
  //	'source', and to return a reference to '*this'.
  BoolObject&	operator=	(const BoolObject&	source
  				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				    return(*this);

				  //  II.  Release resources of '*this':
				  *(Object*)this	= source;	

				  //  III.  Copy 'source':
				  value_ = source.getValue();

				  //  IV.  Finished:
				  return(*this);
				}

  //  PURPOSE:  To return a copy of '*this'.  No parameters.
  Object*	copy		()
				const
				{ return(new BoolObject(getValue())); }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~BoolObject			()
				{ }


  //  V.  Accessors:
  //  PURPOSE:  To return the type of '*this'.  No parameters.
  pythonType_ty	getType		()
  				const
  				{ return(boolType); }

  //  PURPOSE:  To return the value.  No parameters.
  bool		getValue	()
				const
				{ return(value_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the internal C++ boolean value represented by '*this'.
  //	No parameters.
  bool		toBool		()
				const
				{ return(getValue()); }

  //  PURPOSE:  To return the internal C++ integer value represented by '*this'.
  //	No parameters.
  int		toInt		()
				const
				{ return( getValue() ? 1 : 0 ); }

  //  PURPOSE:  To return the internal C++ float value represented by '*this'.
  //	No parameters.
  float		toFloat		()
				const
				{ return( getValue() ? 1.0 : 0.0 ); }

  //  PURPOSE:  To return the internal C++ string value represented by '*this'.
  //	No parameters.
  std::string	toStr		()
				const
				{
				  return( getValue()
				  	  ? std::string("True")
					  : std::string("False")
					);
				}

};


//  PURPOSE:  To represent a Python int object.
class		IntObject : public Object
{
  //  I.  Member vars:
  //  PURPOSE:  To represent the value.
  int				value_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  IntObject			();

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new IntObject instance to hold 'value'.  No return
  //	value.
  IntObject			(int	newValue
				) :
				Object(),
				value_(newValue)
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  IntObject			(const IntObject&	source
				) :
				Object(source),
				value_(source.getValue())
				{ }

  //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
  //	'source', and to return a reference to '*this'.
  IntObject&	operator=	(const IntObject&	source
  				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				    return(*this);

				  //  II.  Release resources of '*this':
				  *(Object*)this	= source;	

				  //  III.  Copy 'source':
				  value_ = source.getValue();

				  //  IV.  Finished:
				  return(*this);
				}

  //  PURPOSE:  To return a copy of '*this'.  No parameters.
  Object*	copy		()
				const
				{ return(new IntObject(getValue())); }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~IntObject			()
				{ }


  //  V.  Accessors:
  //  PURPOSE:  To return the type of '*this'.  No parameters.
  pythonType_ty	getType		()
  				const
  				{ return(intType); }

  //  PURPOSE:  To return the value.  No parameters.
  int		getValue	()
				const
				{ return(value_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the internal C++ boolean value represented by '*this'.
  //	No parameters.
  bool		toBool		()
				const
				{ return( (getValue() != 0) ? true : false ); }

  //  PURPOSE:  To return the internal C++ integer value represented by '*this'.
  //	No parameters.
  int		toInt		()
				const
				{ return( getValue() ); }

  //  PURPOSE:  To return the internal C++ float value represented by '*this'.
  //	No parameters.
  float		toFloat		()
				const
				{ return( (float)getValue() ); }

  //  PURPOSE:  To return the internal C++ string value represented by '*this'.
  //	No parameters.
  std::string	toStr		()
				const
				{
				  snprintf(line,LINE_LEN,"%d",getValue());
				  return(std::string(line));
				}

};


//  PURPOSE:  To represent a Python float object.
class		FloatObject : public Object
{
  //  I.  Member vars:
  //  PURPOSE:  To represent the value.
  float				value_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  FloatObject			();

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new FloatObject instance to hold 'value'.  No return
  //	value.
  FloatObject			(float	newValue
				) :
				Object(),
				value_(newValue)
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  FloatObject			(const FloatObject&	source
				) :
				Object(source),
				value_(source.getValue())
				{ }

  //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
  //	'source', and to return a reference to '*this'.
  FloatObject&	operator=	(const FloatObject&	source
  				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				    return(*this);

				  //  II.  Release resources of '*this':
				  *(Object*)this	= source;	

				  //  III.  Copy 'source':
				  value_ = source.getValue();

				  //  IV.  Finished:
				  return(*this);
				}

  //  PURPOSE:  To return a copy of '*this'.  No parameters.
  Object*	copy		()
				const
				{ return(new FloatObject(getValue())); }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~FloatObject			()
				{ }


  //  V.  Accessors:
  //  PURPOSE:  To return the type of '*this'.  No parameters.
  pythonType_ty	getType		()
  				const
  				{ return(floatType); }

  //  PURPOSE:  To return the value.  No parameters.
  float		getValue	()
				const
				{ return(value_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the internal C++ boolean value represented by '*this'.
  //	No parameters.
  bool		toBool		()
				const
				{ return( (getValue()!=0.0) ? true : false ); }

  //  PURPOSE:  To return the internal C++ integer value represented by '*this'.
  //	No parameters.
  int		toInt		()
				const
				{ return( (int)getValue() ); }

  //  PURPOSE:  To return the internal C++ float value represented by '*this'.
  //	No parameters.
  float		toFloat		()
				const
				{ return( getValue() ); }

  //  PURPOSE:  To return the internal C++ string value represented by '*this'.
  //	No parameters.
  std::string	toStr		()
				const
				{
				  snprintf(line,LINE_LEN,"%.1f",getValue());
				  return(std::string(line));
				}

};


//  PURPOSE:  To represent a Python str object.
class		StrObject : public Object
{
  //  I.  Member vars:
  //  PURPOSE:  To represent the value.
  std::string			value_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  StrObject			();

protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new StrObject instance to hold 'value'.  No return
  //	value.
  StrObject			(const char*	newValuePtr
				) :
				Object(),
				value_(newValuePtr)
				{ }

  //  PURPOSE:  To create a new StrObject instance to hold 'value'.  No return
  //	value.
  StrObject			(std::string	newValue
				) :
				Object(),
				value_(newValue)
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  StrObject			(const StrObject&	source
				) :
				Object(source),
				value_(source.getValue())
				{ }

  //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
  //	'source', and to return a reference to '*this'.
  StrObject&	operator=	(const StrObject&	source
  				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				    return(*this);

				  //  II.  Release resources of '*this':
				  *(Object*)this	= source;	

				  //  III.  Copy 'source':
				  value_ = source.getValue();

				  //  IV.  Finished:
				  return(*this);
				}

  //  PURPOSE:  To return a copy of '*this'.  No parameters.
  Object*	copy		()
				const
				{ return(new StrObject(getValue())); }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~StrObject			()
				{ }


  //  V.  Accessors:
  //  PURPOSE:  To return the type of '*this'.  No parameters.
  pythonType_ty	getType		()
  				const
  				{ return(strType); }

  //  PURPOSE:  To return the value.  No parameters.
  std::string	getValue	()
				const
				{ return(value_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the internal C++ boolean value represented by '*this'.
  //	No parameters.
  bool		toBool		()
				const
				{ return( !getValue().empty() ); }

  //  PURPOSE:  To return the internal C++ integer value represented by '*this'.
  //	No parameters.
  int		toInt		()
				const
				{
				  int	toReturn;
				  char*	cPtr;

				  toReturn
					= strtol(getValue().c_str(),
						 &cPtr,
						 10
						);

				  while  ( isspace(*cPtr) )
				    cPtr++;

				  if  (*cPtr != '\0')
				    throw
				      Exception
					(std::string
					    ("ValueError: invalid literal"
					     " for int() with base 10'"
					    )
					 + getValue()
					 + std::string("'")
					);

				  return(toReturn);
				}

  //  PURPOSE:  To return the internal C++ float value represented by '*this'.
  //	No parameters.
  float		toFloat		()
				const
				{
				  float	toReturn;
				  char*	cPtr;

				  toReturn
					= strtod(getValue().c_str(),&cPtr);

				  while  ( isspace(*cPtr) )
				    cPtr++;

				  if  (*cPtr != '\0')
				    throw
				      Exception
					(std::string
					    ("ValueError: invalid "
					     "literal for float(): "
					    )
					 + getValue()
					);

				  return(toReturn);
				}

  //  PURPOSE:  To return the internal C++ string value represented by '*this'.
  //	No parameters.
  std::string	toStr		()
				const
				{
				  return(getValue());
				}

};
