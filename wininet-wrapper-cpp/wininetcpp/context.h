#ifndef _CONTEXT_H_
#define _CONTEXT_H_

namespace wininetcpp
{
	typedef struct _MainContext
	{
		DWORD dwStructType;
		HINTERNET session;
		HINTERNET connect;
	} MainContext;
}

#endif
