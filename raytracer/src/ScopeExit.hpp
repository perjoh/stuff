#pragma once
#include <boost/function.hpp>

class ScopeExit {
public :
	ScopeExit( boost::function0<void> funType )
		: funType_(funType)
	{ }

	~ScopeExit() {
		funType_();
	}

private :
	boost::function0<void> funType_;

	ScopeExit( const ScopeExit& );
	ScopeExit& operator=( const ScopeExit& );
};
