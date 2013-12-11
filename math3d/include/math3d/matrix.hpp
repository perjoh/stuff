#pragma once

#include "vector.hpp"
#include <cassert>

namespace math3d
{
	namespace internals {

		template <typename T, int DIM>
		struct Mult {
			static void mult( const T& lhs, const T& rhs, T& dest );
		};

		template <typename T>
		struct Mult<T, 3> {
			static void mult( const T& lhs, const T& rhs, T& dest ) {
				dest(0,0) = lhs(0, 0)*rhs(0, 0) + lhs(1, 0)*rhs(0, 1) + lhs(2, 0)*rhs(0, 2);
				dest(1,0) = lhs(0, 0)*rhs(1, 0) + lhs(1, 0)*rhs(1, 1) + lhs(2, 0)*rhs(1, 2);
				dest(2,0) = lhs(0, 0)*rhs(2, 0) + lhs(1, 0)*rhs(2, 1) + lhs(2, 0)*rhs(2, 2);

				dest(0,1) = lhs(0, 1)*rhs(0, 0) + lhs(1, 1)*rhs(0, 1) + lhs(2, 1)*rhs(0, 2);
				dest(1,1) = lhs(0, 1)*rhs(1, 0) + lhs(1, 1)*rhs(1, 1) + lhs(2, 1)*rhs(1, 2);
				dest(2,1) = lhs(0, 1)*rhs(2, 0) + lhs(1, 1)*rhs(2, 1) + lhs(2, 1)*rhs(2, 2);

				dest(0,2) = lhs(0, 2)*rhs(0, 0) + lhs(1, 2)*rhs(0, 1) + lhs(2, 2)*rhs(0, 2);
				dest(1,2) = lhs(0, 2)*rhs(1, 0) + lhs(1, 2)*rhs(1, 1) + lhs(2, 2)*rhs(1, 2);
				dest(2,2) = lhs(0, 2)*rhs(2, 0) + lhs(1, 2)*rhs(2, 1) + lhs(2, 2)*rhs(2, 2);
			}
		};

		template <typename T>
		struct Mult<T, 4> {
			static void mult( const T& lhs, const T& rhs, T& dest ) {
				dest(0,0)	= 	lhs(0, 0)*rhs(0, 0) + lhs(1, 0)*rhs(0, 1) + lhs(2, 0)*rhs(0, 2) + lhs(3, 0)*rhs(0, 3);
				dest(1,0)	= 	lhs(0, 0)*rhs(1, 0) + lhs(1, 0)*rhs(1, 1) + lhs(2, 0)*rhs(1, 2) + lhs(3, 0)*rhs(1, 3);
				dest(2,0)	= 	lhs(0, 0)*rhs(2, 0) + lhs(1, 0)*rhs(2, 1) + lhs(2, 0)*rhs(2, 2) + lhs(3, 0)*rhs(2, 3);
				dest(3,0)	= 	lhs(0, 0)*rhs(3, 0) + lhs(1, 0)*rhs(3, 1) + lhs(2, 0)*rhs(3, 2) + lhs(3, 0)*rhs(3, 3);

				dest(0,1)	= 	lhs(0, 1)*rhs(0, 0) + lhs(1, 1)*rhs(0, 1) + lhs(2, 1)*rhs(0, 2) + lhs(3, 1)*rhs(0, 3);
				dest(1,1)	= 	lhs(0, 1)*rhs(1, 0) + lhs(1, 1)*rhs(1, 1) + lhs(2, 1)*rhs(1, 2) + lhs(3, 1)*rhs(1, 3);
				dest(2,1)	= 	lhs(0, 1)*rhs(2, 0) + lhs(1, 1)*rhs(2, 1) + lhs(2, 1)*rhs(2, 2) + lhs(3, 1)*rhs(2, 3);
				dest(3,1)	= 	lhs(0, 1)*rhs(3, 0) + lhs(1, 1)*rhs(3, 1) + lhs(2, 1)*rhs(3, 2) + lhs(3, 1)*rhs(3, 3);

				dest(0,2)	= 	lhs(0, 2)*rhs(0, 0) + lhs(1, 2)*rhs(0, 1) + lhs(2, 2)*rhs(0, 2) + lhs(3, 2)*rhs(0, 3);
				dest(1,2)	= 	lhs(0, 2)*rhs(1, 0) + lhs(1, 2)*rhs(1, 1) + lhs(2, 2)*rhs(1, 2) + lhs(3, 2)*rhs(1, 3);
				dest(2,2)	= 	lhs(0, 2)*rhs(2, 0) + lhs(1, 2)*rhs(2, 1) + lhs(2, 2)*rhs(2, 2) + lhs(3, 2)*rhs(2, 3);
				dest(3,2)	= 	lhs(0, 2)*rhs(3, 0) + lhs(1, 2)*rhs(3, 1) + lhs(2, 2)*rhs(3, 2) + lhs(3, 2)*rhs(3, 3);

				dest(0,3)	= 	lhs(0, 3)*rhs(0, 0) + lhs(1, 3)*rhs(0, 1) + lhs(2, 3)*rhs(0, 2) + lhs(3, 3)*rhs(0, 3);
				dest(1,3)	= 	lhs(0, 3)*rhs(1, 0) + lhs(1, 3)*rhs(1, 1) + lhs(2, 3)*rhs(1, 2) + lhs(3, 3)*rhs(1, 3);
				dest(2,3)	= 	lhs(0, 3)*rhs(2, 0) + lhs(1, 3)*rhs(2, 1) + lhs(2, 3)*rhs(2, 2) + lhs(3, 3)*rhs(2, 3);
				dest(3,3)	= 	lhs(0, 3)*rhs(3, 0) + lhs(1, 3)*rhs(3, 1) + lhs(2, 3)*rhs(3, 2) + lhs(3, 3)*rhs(3, 3);
			}
		};
	}

	namespace internals {

		template <typename T, int DIM>
		struct VecMatMult {
			typedef typename T::vector_type vec;
			static const vec mult( const vec& lhs, const T& rhs );
		};

		template <typename T>
		struct VecMatMult<T, 3> {
			typedef typename T::vector_type vec;
			static const vec mult( const vec& lhs, const T& rhs ) {
				const vec v_ret( make_vec(
									lhs[0]*rhs(0,0) + lhs[1]*rhs(1,0) + lhs[2]*rhs(2,0),
									lhs[0]*rhs(0,1) + lhs[1]*rhs(1,1) + lhs[2]*rhs(2,1),
									lhs[0]*rhs(0,2) + lhs[1]*rhs(1,2) + lhs[2]*rhs(2,2)
								) ) ;
				return v_ret;
			}
		};

		template <typename T>
		struct VecMatMult<T, 4> {
			typedef typename T::vector_type vec;
			static const vec mult( const vec& lhs, const T& rhs ) {
				const vec v_ret( make_vec(
									lhs[0]*rhs(0,0) + lhs[1]*rhs(1,0) + lhs[2]*rhs(2,0) + lhs[3]*rhs(3,0),
									lhs[0]*rhs(0,1) + lhs[1]*rhs(1,1) + lhs[2]*rhs(2,1) + lhs[3]*rhs(3,1),
									lhs[0]*rhs(0,2) + lhs[1]*rhs(1,2) + lhs[2]*rhs(2,2) + lhs[3]*rhs(3,2),
									lhs[0]*rhs(0,3) + lhs[1]*rhs(1,3) + lhs[2]*rhs(2,3) + lhs[3]*rhs(3,3)
								) ) ;
				return v_ret;
			}
		};
	}

	namespace internals {

		template <typename T, int DIM>
		struct Identity {
			static void set( T& t ) {
				typedef typename T::value_type V;

				for ( int y = 0; y < DIM; ++y ) {
					for ( int x = 0; x < DIM; ++x ) {
						if ( x == y ) {
							t( x, y ) = V(1);
						} else {
							t( x, y ) = V();
						}
					}
				}
			}
		};

		template <typename T>
		struct Identity<T, 3> {
			static void set( T& t ) {
				typedef typename T::value_type V;

				t(0, 0) = V(1L);
				t(1, 0) = V();
				t(2, 0) = V();

				t(0, 1) = V();
				t(1, 1) = V(1L);
				t(2, 1) = V();

				t(0, 2) = V();
				t(1, 2) = V();
				t(2, 2) = V(1L);
			}
		};

		template <typename T>
		struct Identity<T, 4> {
			static void set( T& t ) {
				typedef typename T::value_type V;

				t(0, 0) = V(1L);
				t(1, 0) = V();
				t(2, 0) = V();
				t(3, 0) = V();

				t(0, 1) = V();
				t(1, 1) = V(1L);
				t(2, 1) = V();
				t(3, 1) = V();

				t(0, 2) = V();
				t(1, 2) = V();
				t(2, 2) = V(1L);
				t(3, 2) = V();

				t(0, 3) = V();
				t(1, 3) = V();
				t(2, 3) = V();
				t(3, 3) = V(1L);
			}
		};
	}

	namespace internals {
		template <typename T1, typename T2, int DIM>
		struct Copy {
			static void copy( const T1& src, T2& dest ) {
			}
		};

		template <typename T1, typename T2>
		struct Copy<T1, T2, 3> {
			static void copy( const T1& src, T2& dest ) {
				dest( 0, 0 ) = src( 0, 0 );
				dest( 1, 0 ) = src( 1, 0 );
				dest( 2, 0 ) = src( 2, 0 );
				dest( 0, 1 ) = src( 0, 1 );
				dest( 1, 1 ) = src( 1, 1 );
				dest( 2, 1 ) = src( 2, 1 );
				dest( 0, 2 ) = src( 0, 2 );
				dest( 1, 2 ) = src( 1, 2 );
				dest( 2, 2 ) = src( 2, 2 );
			}
		};

		template <typename T1, typename T2>
		struct Copy<T1, T2, 4> {
			static void copy( const T1& src, T2& dest ) {
				dest( 0, 0 ) = src( 0, 0 );
				dest( 1, 0 ) = src( 1, 0 );
				dest( 2, 0 ) = src( 2, 0 );
				dest( 3, 0 ) = src( 3, 0 );
				dest( 0, 1 ) = src( 0, 1 );
				dest( 1, 1 ) = src( 1, 1 );
				dest( 2, 1 ) = src( 2, 1 );
				dest( 3, 1 ) = src( 3, 1 );
				dest( 0, 2 ) = src( 0, 2 );
				dest( 1, 2 ) = src( 1, 2 );
				dest( 2, 2 ) = src( 2, 2 );
				dest( 3, 2 ) = src( 3, 2 );
				dest( 0, 3 ) = src( 0, 3 );
				dest( 1, 3 ) = src( 1, 3 );
				dest( 2, 3 ) = src( 2, 3 );
				dest( 3, 3 ) = src( 3, 3 );
			}
		};

		// <loop unrolled copy>
		template <typename T, int COUNT>
		struct CopyArray {
			static void copy( const T* src, T* dest ) {
				*dest = *src;
				CopyArray<T, COUNT-1>::copy( src+1, dest+1 );
			}
		};

		template <typename T>
		struct CopyArray<T, 0> {
			static void copy( const T* src, T* dest ) {
				// empty!
			}
		};
		// </loop unrolled copy>
	}

	//! A matrix class suitable for 3d graphics.
	template <typename T, int DIM, bool ROW_MAJOR=true>
	class matrix
	{
	public :
		enum { dim = DIM };
		enum { size = dim*dim };
		enum { row_major = ROW_MAJOR };
		typedef T value_type;
		typedef vector<T,dim> vector_type;

		//! Default constructor.
		matrix()
		{
		}

		//! construction
		explicit matrix(const T d[size])
		{
			internals::CopyArray<T, size>::copy( &d[0], &d1_[0] );
		}

		//! construction
		explicit matrix(const T d[dim][dim])
		{
			// TODO improve
			for ( int y = 0; y < dim; ++y )
			for ( int x = 0; x < dim; ++x ) {
				this->access( x, y ) = d[y][x];
			}
		}

		template <typename T2>
		matrix( const T2& m ) {
			internals::Copy<T2, matrix, dim>::copy( m, *this );
		}

	private :
		// TODO Put these functions in their own struct?

		/*template <bool DUMMY>
		inline T& access_internal( const int column, const int row ) const;

		template <>
		inline T& access_internal<true>( const int column, const int row ) const {
			return d2_[row][column];
		}

		template <>
		inline T& access_internal<false>( const int column, const int row ) const {
			return d2_[column][row];
		}*/

		inline T& access( const int column, const int row ) const {
			return d2_[ROW_MAJOR?row:column][ROW_MAJOR?column:row];
			//return access_internal<ROW_MAJOR==true>( column, row );
		}

	public :

		//! referencing
		T&	operator()(const int col, const int row)
		{
			//return d2_[col][row];
			return access( col, row );
		}

		//! referencing
		const T& operator()(const int col, const int row) const
		{
			//return d2_[col][row];
			return access( col, row );
		}

		//! referencing
		T&	operator[](const int i)
		{
			return d1_[i];
		}

		//! referencing
		const T& operator[](const int i) const
		{
			return d1_[i];
		}

		//! comparison
		bool operator==(const matrix& rhs) const
		{
			for ( int i = 0; i < size; ++i ) {
				if ( d1_[i] != rhs.d1_[i] ) {
					return false;
				}
			}
			return true;
		}

		//! set identity matrix
		void identity()
		{
			internals::Identity<matrix, dim>::set( *this );
		}

		//! Helper
		static const matrix makeIdentity()
		{
			matrix m;
			m.identity();
			return m;
		}

	public :
		void transpose() {
			for ( int y = 0; y < dim; ++y ) {
				for ( int x = y; x < dim; ++x ) {
					T t = access( x, y );
					access( x, y ) = access( y, x );
					access( y, x ) = t;
				}
			}
		}

	public :

		//! matrix multiplication (row major)
		matrix operator*(const matrix& rhs) const
		{
			matrix r;
			internals::Mult<matrix, dim>::mult( *this, rhs, r );
			return r;
		}

	public :
		static const matrix make_identity() {
			matrix mat;
			mat.identity();
			return mat;
		}

	private :
		union
		{
			mutable T d1_[size];
			mutable T d2_[dim][dim];
		};
	};


	template < typename MAT >
	typename MAT::vector_type operator*( const typename MAT::vector_type& v, const MAT& m )
	{
		return internals::VecMatMult<MAT, MAT::dim>::mult( v, m );
	}

	template < typename MAT >
	void set_rot_x( MAT& m, typename MAT::value_type a ) {
		m.identity();
		m( 1, 1 ) = std::cos( a );
		m( 2, 1 ) = -std::sin( a );
		m( 1, 2 ) = std::sin( a );
		m( 2, 2 ) = std::cos( a );
	}

	template <typename MAT>
	void set_rot_y( MAT& m, typename MAT::value_type a ) {
		m.identity();
		m( 0, 0 ) = std::cos(a);
		m( 2, 0 ) = std::sin(a);
		m( 0, 2 ) = -std::sin(a);
		m( 2, 2 ) = std::cos(a);
	}

	template <typename MAT>
	void set_rot_z( MAT& m, typename MAT::value_type a ) {
		m.identity();
		m( 0, 0 ) = std::cos(a);
		m( 1, 0 ) = -std::sin(a);
		m( 0,1 ) = std::sin(a);
		m( 1,1 ) = std::cos(a);
	}

	template <typename MAT, typename VEC>
	void setLookAtLh( MAT&m, const VEC& position, const VEC& target, const VEC& up = VEC::make(0, 1, 0) ) {
		typedef typename MAT::vector_type vec;
		const VEC zaxis = norm(target - position);
		const VEC xaxis = norm(crossp(zaxis, up));
		const VEC yaxis = crossp(xaxis, zaxis);

		m(0,0) = xaxis[0];
		m(1,0) = xaxis[1];
		m(2,0) = xaxis[2];
		m(3,0) = -dot(xaxis, position);

		m(0,1) = yaxis[0];
		m(1,1) = yaxis[1];
		m(2,1) = yaxis[2];
		m(3,1) = -dot(yaxis, position);

		m(0,2) = zaxis[0];
		m(1,2) = zaxis[1];
		m(2,2) = zaxis[2];
		m(3,2) = -dot(zaxis, position);

		typedef typename MAT::value_type value;

		m(0,3) = value();
		m(1,3) = value();
		m(2,3) = value();
		m(3,3) = value(1);
	}

	template <typename MAT, typename VEC>
	void setLookAtRh( MAT&m, const VEC& position, const VEC& target, const VEC& up = VEC::make(0, 1, 0) ) 
    {
		setLookAtLh( m, position, target, up );
		typedef typename MAT::value_type value;
		m(0, 2) *= -value(1);
		m(1, 2) *= -value(1);
		m(2, 2) *= -value(1);
		m(3, 2) *= -value(1);
	}

	template <typename MAT, typename VEC>
	void scale( MAT& m, const VEC& scale )
	{
		m(0, 0) *= scale[0];
		m(1, 0) *= scale[1];
		m(2, 0) *= scale[2];

		m(0, 1) *= scale[0];
		m(1, 1) *= scale[1];
		m(2, 1) *= scale[2];

		m(0, 2) *= scale[0];
		m(1, 2) *= scale[1];
		m(2, 2) *= scale[2];
	}

    template <typename MAT, typename VEC>
    void translate( MAT&m, const VEC& delta )
    {
        m(3, 0) += delta[0];
        m(3, 1) += delta[1];
        m(3, 2) += delta[2];
    }

}
