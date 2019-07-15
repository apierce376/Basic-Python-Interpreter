/*-------------------------------------------------------------------------*
 *---									---*
 *---		VariableStore.h						---*
 *---									---*
 *---	    This file declares a class that stores variables.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 May 17		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/


class		VariableStore
{
  //  I.  Member vars:
  //  PURPOSE:  To map from variable names to their values.
  std::map<std::string,Object*>	varNameToValueMap_;

  //  II.  Disallowed member vars:
  //  No copy constructor:
  VariableStore			(const VariableStore&
				);

  //  No copy assignment op:
  VariableStore&
		operator=	(const VariableStore&
				);

protected :
  //  III.  Protected:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to an empty VariableStore object.  No
  //	parameters.  No return value.
  VariableStore			() :
				varNameToValueMap_()
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~VariableStore		()
				{
				  std::map<std::string,Object*>::iterator
					iter	= varNameToValueMap_.begin();
				  std::map<std::string,Object*>::iterator
					end	= varNameToValueMap_.end();

				  for  ( ; iter != end;  iter++)
				  {
				    safeDelete(iter->second);
				  }

				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return a pointer to the current value of the variable
  //	named 'varName', or to return 'NULL' if it does not have a value.
  const Object*	get		(const std::string&	varName
				)
				{
				  std::map<std::string,Object*>::iterator
					iter	= varNameToValueMap_.
							find(varName);
				  std::map<std::string,Object*>::iterator
					end	= varNameToValueMap_.end();

				  return( (iter == end) ? NULL : iter->second );
				}

  //  PURPOSE:  To 
  void		store		(const std::string&	varName,
				 Object*		objPtr
				)
				{
				  std::map<std::string,Object*>::iterator
					iter	= varNameToValueMap_.
							find(varName);
				  std::map<std::string,Object*>::iterator
					end	= varNameToValueMap_.end();

				  if  (iter == end)
				    varNameToValueMap_[varName]	= objPtr;
				  else
				  {
				    safeDelete(iter->second);
				    iter->second	= objPtr;
				  }

				}

};