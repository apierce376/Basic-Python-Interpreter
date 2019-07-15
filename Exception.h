/*-------------------------------------------------------------------------*
 *---									---*
 *---		Exception.h						---*
 *---									---*
 *---	    This file declares a base class and derived classes for	---*
 *---	Python exceptions.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 15		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

class		Exception
{
  //  I.  Member vars:
  //  PURPOSE:  To hold a description of the problem.
  std::string			description_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  Exception			();

  //  No copy assignment op:
protected :
  //  III.  Protected methods:

public :
  //  IV.  Construtor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To create a new Exception instance that describes a problem
  //  	with text 'newDescription'.  No return value.
  Exception			(const std::string&	newDescription
				) :
				description_(newDescription)
				{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
  Exception			(const Exception&	source
				) :
				description_(source.getDescription())
				{ }

  //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
  //	'source', and to return a reference to '*this':
  Exception&	operator=	(const Exception&	source
  				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				    return(*this);

				  //  II.  Release resources:

				  //  III.  Copy '*this':
				  description_	= source.getDescription();

				  //  IV.  Finished:
				  return(*this);
				}

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  virtual
  ~Exception			()
				{ }

  //  V.  Accessors:
  //  PURPOSE:  To hold a description of the problem.
  const std::string&
		getDescription	()
				const
				{ return(description_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:

};