#ifndef math3d_vector_hpp
#define math3d_vector_hpp

#include <cmath>
#include <algorithm>

namespace math3d
{

	// Traits

	// TODO Move this to helpers.hpp?

	template <typename T>
	struct value_traits
	{
		static bool almost_equal( T a, T b )
		{
			return a == b;
		}

		static T sqrt( T a )
		{
			return static_cast<T>(std::sqrt(static_cast<double>(a)));
		}
	};

	template <>
	struct value_traits<float>
	{
		static bool almost_equal( float a, float b )
		{
			using namespace std;
			const float eps = max( abs( a ), abs( b ) ) * 0.00001f;
			return abs( a - b ) <= eps;
		}

		static float sqrt( float a )
		{
			return std::sqrt( a );
		}
	};

	template <>
	struct value_traits<double>
	{
		static bool almost_equal( double a, double b )
		{
			using namespace std;
			const double eps = max( abs( a ), abs( b ) ) * 0.00001;
			return abs( a - b ) <= eps;
		}

		static double sqrt( double a )
		{
			return std::sqrt( a );
		}
	};

	template <typename T1, typename T2>
	T1 lerp( const T1& from, const T1& to, T2 t ) {
		return from * ( T2( 1 ) - t ) + to * t;
	}


	// Meta programs


	template <typename T>
	struct op_mul {
		static T op(T lhs, T rhs) {
			return lhs*rhs;
		}
	};

	template <typename T>
	struct op_div {
		static T op(T lhs, T rhs) {
			return lhs/rhs;
		}
	};

	template <typename T>
	struct op_add {
		static T op(T lhs, T rhs) {
			return lhs+rhs;
		}
	};

	template <typename T>
	struct op_sub {
		static T op(T lhs, T rhs) {
			return lhs-rhs;
		}
	};

	template <int COUNT, typename T, template <typename> class OP>
	struct do_binary_op {
		static void exec(const T* lhs, const T* rhs, T* dest) {
			*dest = OP<T>::op(*lhs, *rhs);
			do_binary_op<COUNT-1, T, OP>::exec(lhs+1, rhs+1, dest+1);
		}
	};

	template <typename T, template <typename> class OP>
	struct do_binary_op<1, T, OP> {
		static void exec(const T* lhs, const T* rhs, T* dest) {
			*dest = OP<T>::op(*lhs, *rhs);
		}
	};

	template <int COUNT, typename T, template <typename> class OP>
	struct do_binary_op_scalar {
		static void exec(const T* lhs, T s, T* dest) {
			*dest = OP<T>::op(*lhs, s);
			do_binary_op_scalar<COUNT-1, T, OP>::exec(lhs+1, s, dest+1);
		}
	};

	template <typename T, template <typename> class OP>
	struct do_binary_op_scalar<1, T, OP> {
		static void exec(const T* lhs, T s, T* dest) {
			*dest = OP<T>::op(*lhs, s);
		}
	};


    // Fill array with value.
    template <int COUNT, typename T>
    struct fill {
        static void exec(T* bufToFill, const T& fillValue) {
            *bufToFill = fillValue;
            fill<COUNT-1, T>::exec(bufToFill+1, fillValue);
        }
    };

    // Fill array with value. (Ends recursion)
    template <typename T>
    struct fill<1, T> {
        static void exec(T* bufToFill, const T& fillValue) {
            *bufToFill = fillValue;
        }
    };


	//! Executes: arg[0] OP arg[1] OP ... arg[n]
	template < int COUNT, typename T, template < typename > class OP >
	struct do_binary_op_cumulative {
		static T exec( const T* arg ) {
			return OP<T>::op( *arg, do_binary_op_cumulative<COUNT-1, T, OP>::exec( arg+1 ) );
		}
	};

	template <typename T, template <typename> class OP>
	struct do_binary_op_cumulative<1, T, OP> {
		static T exec( const T* arg ) {
			return *arg;
		}
	};


	template <int COUNT, typename T>
	struct dot_product {
		static T exec(const T* lhs, const T* rhs) {
			return *lhs * *rhs + dot_product<COUNT-1, T>::exec(lhs+1, rhs+1);
		}
	};

	template <typename T>
	struct dot_product<1, T> {
		static T exec(const T* lhs, const T* rhs) {
			return *lhs * *rhs;
		}
	};


	template < int COUNT, typename T1, typename T2 >
	struct vec_copy {
		static void exec( T1* lhs, const T2* rhs ) {
			*lhs = static_cast<T1>(*rhs);
			vec_copy< COUNT-1, T1, T2 >::exec( lhs + 1, rhs + 1 );
		}
	};

	template < typename T1, typename T2 >
	struct vec_copy< 1, T1, T2 > {
		static void exec( T1* lhs, const T2* rhs ) {
			*lhs = static_cast<T1>(*rhs);
		}
	};

	// clamp program
	template <int COUNT, typename T>
	struct clamp_prg {
		static void exec( T* t, const T& clampTo ) {
			if ( *t > clampTo )
				*t = clampTo;
			clamp_prg<COUNT-1, T>::exec(t+1, clampTo);
		}
	};

	template <typename T>
	struct clamp_prg<0, T> {
		static void exec( T*, const T& ) {
			// empty, stops recursion
		}
	};

	// Class vector

	template <typename T, int SIZE = 3>
	class vector
	{
	public :
		typedef T value_type;
		enum { size = SIZE };

	public :
		//!
		vector() {}

		//! Construct vector with all elements set to \c t.
		explicit vector(T t)
		{
            fill<size, T>::exec(&d_[0], t);
		}

		//! Copy construct from other type.
		template < typename T2 >
		vector( const vector<T2, SIZE>& v )
		{
			vec_copy<SIZE, T, T2>::exec( &d_[0], &v[0] );
		}

	public :
		//! Subscript operator
		T& operator[](int i)
		{
			return d_[i];
		}

		//! Subscript operator (const)
		const T& operator[](int i) const
		{
			return d_[i];
		}

	public :
		//! Compare
		bool operator==(const vector& rhs) const
		{
			for (int i = 0; i < size; ++i)
			{
				if (!value_traits<T>::almost_equal(d_[i], rhs.d_[i]))
					return false;
			}

			return true;
		}

		bool operator!=( const vector& rhs ) const
		{
			return !( *this == rhs );
		}


	public :
		//! Multiplication
		vector operator*(const vector& rhs) const
		{
			vector r;
			do_binary_op<size, T, op_mul>::exec(&d_[0], &rhs.d_[0], &r.d_[0]);
			return r;
		}

		//! Assignment multiplication
		const vector& operator*=(const vector& rhs)
		{
			do_binary_op<size, T, op_mul>::exec(&d_[0], &rhs.d_[0], &d_[0]);
			return *this;
		}

		//! Multiplication with scalar
		vector operator*(T s) const
		{
			vector r;
			do_binary_op_scalar<size, T, op_mul>::exec(&d_[0], s, &r.d_[0]);
			return r;
		}

		//! Assignment multiplication with scalar
		const vector& operator*=(T s)
		{
			do_binary_op_scalar<size, T, op_mul>::exec(&d_[0], s, &d_[0]);
			return *this;
		}


	public :
		//! Division
		vector operator/(const vector& rhs) const
		{
			vector r;
			do_binary_op<size, T, op_div>::exec(&d_[0], &rhs.d_[0], &r.d_[0]);
			return r;
		}

		//! Assignment division
		const vector& operator/=(const vector& rhs)
		{
			do_binary_op<size, T, op_div>::exec(&d_[0], &rhs.d_[0], &d_[0]);
			return *this;
		}

		//! Division with scalar
		vector operator/(T s) const
		{
			vector r;
			do_binary_op_scalar<size, T, op_div>::exec(&d_[0], s, &r.d_[0]);
			return r;
		}

		//! Assignment division with scalar
		const vector& operator/=(T s)
		{
			do_binary_op_scalar<size, T, op_div>::exec(&d_[0], s, &d_[0]);
			return *this;
		}


	public :
		//! Addition
		vector operator+(const vector& rhs) const
		{
			vector r;
			do_binary_op<size, T, op_add>::exec(&d_[0], &rhs.d_[0], &r.d_[0]);
			return r;
		}

		//! Assignment addition
		const vector& operator+=(const vector& rhs)
		{
			do_binary_op<size, T, op_add>::exec(&d_[0], &rhs.d_[0], &d_[0]);
			return *this;
		}

		//! Addition with scalar
		vector operator+(T s) const
		{
			vector r;
			do_binary_op_scalar<size, T, op_add>::exec(&d_[0], s, &r.d_[0]);
			return r;
		}

		//! Assignment addtion with scalar
		const vector& operator+=(T s)
		{
			do_binary_op_scalar<size, T, op_add>::exec(&d_[0], s, &d_[0]);
			return *this;
		}


	public :
		//! Subtraction
		vector operator-(const vector& rhs) const
		{
			vector r;
			do_binary_op<size, T, op_sub>::exec(&d_[0], &rhs.d_[0], &r.d_[0]);
			return r;
		}

		//! Assignment subtraction
		const vector& operator-=(const vector& rhs)
		{
			do_binary_op<size, T, op_sub>::exec(&d_[0], &rhs.d_[0], &d_[0]);
			return *this;
		}

		//! Subtraction with scalar
		vector operator-(T s) const
		{
			vector r;
			do_binary_op_scalar<size, T, op_sub>::exec(&d_[0], s, &r.d_[0]);
			return r;
		}

		//! Assignment subtraction with scalar
		const vector& operator-=(T s)
		{
			do_binary_op_scalar<size, T, op_sub>::exec(&d_[0], s, &d_[0]);
			return *this;
		}

	public :

		// Invert sign.
		const vector operator-() const
		{
			return vector( *this*T(-1) );
		}


	public :
		//! Calculate length of vector.
		T length() const
		{
			return vec_length( *this );
		}

		//! Normalizes the vector. (Sets length to 1)
		void norm()
		{
			*this /= length();
		}

	public :
		static const vector<T, 2> make( T x, T y )
		{
			vector<T, 2> v;
			v[0] = x;
			v[1] = y;
			return v;
		}

		static const vector<T, 3> make( T x, T y, T z )
		{
			vector<T, 3> v;
			v[0] = x;
			v[1] = y;
			v[2] = z;
			return v;
		}

		static const vector<T, 4> make( T x, T y, T z, T w )
		{
			vector<T, 4> v;
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
			return v;
		}

	private :
		T d_[size];
	};


	// Free functions

	//!
	template <typename V>
	const V operator*( typename V::value_type s, const V& v )
	{
		return v*s;
	}

	//! Dot product
	template <typename V>
	typename V::value_type dot(const V& lhs, const V& rhs)
	{
		return dot_product<V::size, typename V::value_type>::exec(&lhs[0], &rhs[0]);
	}

	//!
	template <typename V>
	typename V::value_type dot_square(const V& v)
	{
		return dot( v, v );
	}

	//! Cross product
	template <typename T>
	const vector<T, 3> cross(const vector<T, 3>& lhs, const vector<T, 3>& rhs)
	{
		vector<T, 3> r;
		r[0] = lhs[1]*rhs[2] - lhs[2]*rhs[1];
		r[1] = -(lhs[0]*rhs[2] - lhs[2]*rhs[0]);
		r[2] = lhs[0]*rhs[1] - lhs[1]*rhs[0];
		return r;
	}

	//! Normalize
	template <typename V>
	const V norm( const V& v )
	{
		V v_( v );
		v_.norm();
		return v_;
	}

	template <typename V>
	V& norm(V& v)
	{
		v.norm();
		return v;
	}

	//! Length
	template <typename V>
	typename V::value_type vec_length( const V& v )
	{
		return value_traits<typename V::value_type>::sqrt( dot_square( v ) );
	}

	// Helper functions

	template <typename T>
	const vector<T, 3> make_vec(T x, T y, T z)
	{
		vector<T, 3> v;
		v[0] = x;
		v[1] = y;
		v[2] = z;
		return v;
	}

	template <typename T>
	const vector<T, 4> make_vec(T x, T y, T z, T w)
	{
		vector<T, 4> v;
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
		return v;
	}

	template <typename VEC>
	const VEC reflect( const VEC& inc, const VEC& norm )
	{
		return inc - ( dot( norm, inc ) * norm * typename VEC::value_type(2) );
	}

	template <typename VEC>
	void clamp( VEC& v, const typename VEC::value_type& clampTo )
	{
		clamp_prg<VEC::size, typename VEC::value_type>::exec(&v[0], clampTo);
	}


    template <int X, int Y, int Z>
    struct Xyz {
        enum { x = X, y = Y, z = Z };
    };

    template <int LhsX, int LhsY, int LhsZ, int RhsX, int RhsY, int RhsZ>
    struct OptimizingDot {
        template <typename T>
        static T calc(T lhsX, T lhsY, T lhsZ, T rhsX, T rhsY, T rhsZ) {
            return ((LhsX != 0 && RhsX != 0) ? lhsX*rhsX : T()) +
                ((LhsY != 0 && RhsY != 0) ? lhsY*rhsY : T()) +
                ((LhsZ != 0 && RhsZ != 0) ? lhsZ*rhsZ : T());
        }
    };
}

#endif
