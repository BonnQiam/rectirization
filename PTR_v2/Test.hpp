
typedef std::exception NullPtrException;

inline bool equal(const double a, const double b)
{
	#define EPS 1e-9
	return fabs(a-b)<EPS ? true : false;
}

