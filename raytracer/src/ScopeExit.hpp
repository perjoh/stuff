#pragma once

template <typename Fun>
class ScopeExit_ {
public :
	ScopeExit_( Fun f )
		: f_(f)
	{ }

	ScopeExit_(ScopeExit_&& other)
		: f_(std::move(other.f_))
	{ 
	}

	~ScopeExit_() {
		f_();
	}

private :
	Fun f_;

	ScopeExit_(const ScopeExit_&) = delete;
	ScopeExit_& operator=(const ScopeExit_&) = delete;
};

template <typename Fun>
ScopeExit_<Fun> ScopeExit(Fun f)
{
	return ScopeExit_<Fun>(f); 
}
