#ifndef ObjexxFCL_Array2_hh_INCLUDED
#define ObjexxFCL_Array2_hh_INCLUDED

// Array2: Row-Major 2D Array Abstract Base Class
//
// Project: Objexx Fortran Compatibility Library (ObjexxFCL)
//
// Version: 4.0.0
//
// Language: C++
//
// Copyright (c) 2000-2015 Objexx Engineering, Inc. All Rights Reserved.
// Use of this source code or any derivative of it is restricted by license.
// Licensing is available from Objexx Engineering, Inc.:  http://objexx.com

// ObjexxFCL Headers
#include <ObjexxFCL/Array2.fwd.hh>
#include <ObjexxFCL/Array.hh>
#include <ObjexxFCL/Array2S.hh>
#include <ObjexxFCL/MArray2.hh>

namespace ObjexxFCL {

// Forward
template< typename > class Array1D; // For project-specific member array methods
template< typename > class Array2D;
template< typename > class Array2A;

// Array2: Row-Major 2D Array Abstract Base Class
template< typename T >
class Array2 : public Array< T >
{

private: // Types

	typedef  Array< T >  Super;

private: // Friend

	template< typename > friend class Array2;
	template< typename > friend class Array2D;
	template< typename > friend class Array2A;

protected: // Types

	typedef  internal::InitializerSentinel  InitializerSentinel;
	typedef  internal::ProxySentinel  ProxySentinel;

public: // Types

	typedef  typename Super::Base  Base;
	typedef  typename Super::Tail  Tail;
	typedef  typename Super::IR  IR;
	typedef  typename Super::IS  IS;
	typedef  typename Super::DS  DS;

	// STL Style
	typedef  typename Super::value_type  value_type;
	typedef  typename Super::reference  reference;
	typedef  typename Super::const_reference  const_reference;
	typedef  typename Super::pointer  pointer;
	typedef  typename Super::const_pointer  const_pointer;
	typedef  typename Super::size_type  size_type;
	typedef  typename Super::difference_type  difference_type;

	// C++ Style
	typedef  typename Super::Value  Value;
	typedef  typename Super::Reference  Reference;
	typedef  typename Super::ConstReference  ConstReference;
	typedef  typename Super::Pointer  Pointer;
	typedef  typename Super::ConstPointer  ConstPointer;
	typedef  typename Super::Size  Size;
	typedef  typename Super::Difference  Difference;

	using Super::isize;
	using Super::npos;
	using Super::overlap;
	using Super::size;
	using Super::size_of;
	using Super::slice_k;
	using Super::swapB;
	using Super::data_;
	using Super::data_size_;
	using Super::sdata_;
	using Super::shift_;
	using Super::size_;

protected: // Creation

	// Default Constructor
	inline
	Array2() :
	 z1_( 0u ),
	 z2_( 0u )
	{}

	// Copy Constructor
	inline
	Array2( Array2 const & a ) :
	 Super( a ),
	 I1_( a.I1_ ),
	 I2_( a.I2_ ),
	 z1_( a.z1_ ),
	 z2_( a.z2_ )
	{}

	// Move Constructor
	inline
	Array2( Array2 && a ) NOEXCEPT :
	 Super( std::move( a ) ),
	 I1_( a.I1_ ),
	 I2_( a.I2_ ),
	 z1_( a.z1_ ),
	 z2_( a.z2_ )
	{
		a.clear_move();
	}

	// Copy Constructor Template
	template< typename U, class = typename std::enable_if< std::is_constructible< T, U >::value >::type >
	inline
	explicit
	Array2( Array2< U > const & a ) :
	 Super( a ),
	 I1_( a.I1_ ),
	 I2_( a.I2_ ),
	 z1_( a.z1_ ),
	 z2_( a.z2_ )
	{}

	// Slice Constructor Template
	template< typename U, class = typename std::enable_if< std::is_constructible< T, U >::value >::type >
	inline
	explicit
	Array2( Array2S< U > const & a ) :
	 Super( a ),
	 I1_( a.u1() ),
	 I2_( a.u2() ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// MArray Constructor Template
	template< class A, typename M >
	inline
	explicit
	Array2( MArray2< A, M > const & a ) :
	 Super( a ),
	 I1_( a.u1() ),
	 I2_( a.u2() ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// IndexRange Constructor
	inline
	Array2( IR const & I1, IR const & I2 ) :
	 Super( size_of( I1, I2 ) ),
	 I1_( I1 ),
	 I2_( I2 ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// IndexRange + InitializerSentinel Constructor
	inline
	Array2( IR const & I1, IR const & I2, InitializerSentinel const & initialized ) :
	 Super( size_of( I1, I2 ), initialized ),
	 I1_( I1 ),
	 I2_( I2 ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// IndexRange + Initializer List Constructor Template
	template< typename U, class = typename std::enable_if< std::is_constructible< T, U >::value >::type >
	inline
	Array2( IR const & I1, IR const & I2, std::initializer_list< U > const l ) :
	 Super( l ),
	 I1_( I1 ),
	 I2_( I2 ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{
		assert( size_of( I1, I2 ) == l.size() );
	}

	// Default Proxy Constructor
	inline
	Array2( ProxySentinel const & proxy ) :
	 Super( proxy ),
	 z1_( 0u ),
	 z2_( 0u )
	{}

	// Copy Proxy Constructor
	inline
	Array2( Array2 const & a, ProxySentinel const & proxy ) :
	 Super( a, proxy ),
	 I1_( a.I1_ ),
	 I2_( a.I2_ ),
	 z1_( a.z1_ ),
	 z2_( a.z2_ )
	{}

	// Slice Proxy Constructor
	inline
	Array2( Array2S< T > const & a, ProxySentinel const & proxy ) :
	 Super( a, proxy ),
	 I1_( a.u1() ),
	 I2_( a.u2() ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// Base Proxy Constructor
	inline
	Array2( Base const & a, ProxySentinel const & proxy ) :
	 Super( a, proxy ),
	 I1_( a.isize() ),
	 I2_( 1 ),
	 z1_( I1_.size() ),
	 z2_( 1u )
	{}

	// Tail Proxy Constructor
	inline
	Array2( Tail const & s, ProxySentinel const & proxy ) :
	 Super( s, proxy ),
	 I1_( s.isize() ),
	 I2_( 1 ),
	 z1_( I1_.size() ),
	 z2_( 1u )
	{}

	// Value Proxy Constructor
	inline
	Array2( T const & t, ProxySentinel const & proxy ) :
	 Super( t, proxy ),
	 I1_( _ ),
	 I2_( 1 ),
	 z1_( I1_.size() ),
	 z2_( 1u )
	{}

	// Copy + IndexRange Proxy Constructor
	inline
	Array2( Array2 const & a, IR const & I1, IR const & I2, ProxySentinel const & proxy ) :
	 Super( a, proxy ),
	 I1_( I1 ),
	 I2_( I2 ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// Slice + IndexRange Proxy Constructor
	inline
	Array2( Array2S< T > const & a, IR const & I1, IR const & I2, ProxySentinel const & proxy ) :
	 Super( a, proxy ),
	 I1_( I1 ),
	 I2_( I2 ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// Base + IndexRange Proxy Constructor
	inline
	Array2( Base const & a, IR const & I1, IR const & I2, ProxySentinel const & proxy ) :
	 Super( a, proxy ),
	 I1_( I1 ),
	 I2_( I2 ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// Tail + IndexRange Proxy Constructor
	inline
	Array2( Tail const & s, IR const & I1, IR const & I2, ProxySentinel const & proxy ) :
	 Super( s, proxy ),
	 I1_( I1 ),
	 I2_( I2 ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

	// Value + IndexRange Proxy Constructor
	inline
	Array2( T const & t, IR const & I1, IR const & I2, ProxySentinel const & proxy ) :
	 Super( t, proxy ),
	 I1_( I1 ),
	 I2_( I2 ),
	 z1_( I1_.size() ),
	 z2_( I2_.size() )
	{}

public: // Creation

	// Destructor
	inline
	virtual
	~Array2()
	{}

public: // Assignment: Array

	// Copy Assignment
	inline
	Array2 &
	operator =( Array2 const & a )
	{
		if ( this != &a ) {
			if ( ! conformable( a ) ) dimension_assign( a.I1_, a.I2_ );
			Super::operator =( a );
		}
		return *this;
	}

	// Copy Assignment Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator =( Array2< U > const & a )
	{
		if ( ! conformable( a ) ) dimension_assign( a.I1_, a.I2_ );
		Super::operator =( a );
		return *this;
	}

	// Slice Assignment
	inline
	Array2 &
	operator =( Array2S< T > const & a )
	{
		if ( ! conformable( a ) ) dimension_assign( a.I1(), a.I2() );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					c[ l ] = a( i1, i2 );
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] = c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					data_[ l ] = a( i1, i2 );
				}
			}
		}
		return *this;
	}

	// Slice Assignment Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator =( Array2S< U > const & a )
	{
		if ( ! conformable( a ) ) dimension_assign( a.I1(), a.I2() );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] = a( i1, i2 );
			}
		}
		return *this;
	}

	// MArray Assignment Template
	template< class A, typename M >
	inline
	Array2 &
	operator =( MArray2< A, M > const & a )
	{
		if ( ! conformable( a ) ) dimension_assign( a.I1(), a.I2() );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] = a( i1, i2 );
			}
		}
		return *this;
	}

	// Initializer List Assignment Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator =( std::initializer_list< U > const l )
	{
		Super::operator =( l );
		return *this;
	}

	// += Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator +=( Array2< U > const & a )
	{
		assert( conformable( a ) );
		Super::operator +=( a );
		return *this;
	}

	// -= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator -=( Array2< U > const & a )
	{
		assert( conformable( a ) );
		Super::operator -=( a );
		return *this;
	}

	// *= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator *=( Array2< U > const & a )
	{
		assert( conformable( a ) );
		Super::operator *=( a );
		return *this;
	}

	// /= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator /=( Array2< U > const & a )
	{
		assert( conformable( a ) );
		Super::operator /=( a );
		return *this;
	}

	// += Slice
	inline
	Array2 &
	operator +=( Array2S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					c[ l ] = a( i1, i2 );
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] += c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					data_[ l ] += a( i1, i2 );
				}
			}
		}
		return *this;
	}

	// -= Slice
	inline
	Array2 &
	operator -=( Array2S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					c[ l ] = a( i1, i2 );
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] -= c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					data_[ l ] -= a( i1, i2 );
				}
			}
		}
		return *this;
	}

	// *= Slice
	inline
	Array2 &
	operator *=( Array2S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					c[ l ] = a( i1, i2 );
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] *= c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					data_[ l ] *= a( i1, i2 );
				}
			}
		}
		return *this;
	}

	// /= Slice
	inline
	Array2 &
	operator /=( Array2S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					assert( a( i1, i2 ) != T( 0 ) );
					c[ l ] = a( i1, i2 );
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] /= c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					assert( a( i1, i2 ) != T( 0 ) );
					data_[ l ] /= a( i1, i2 );
				}
			}
		}
		return *this;
	}

	// += Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator +=( Array2S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] += a( i1, i2 );
			}
		}
		return *this;
	}

	// -= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator -=( Array2S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] -= a( i1, i2 );
			}
		}
		return *this;
	}

	// *= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator *=( Array2S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] *= a( i1, i2 );
			}
		}
		return *this;
	}

	// /= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	operator /=( Array2S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				assert( a( i1, i2 ) != T( 0 ) );
				data_[ l ] /= a( i1, i2 );
			}
		}
		return *this;
	}

	// += MArray Template
	template< class A, typename M >
	inline
	Array2 &
	operator +=( MArray2< A, M > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] += a( i1, i2 );
			}
		}
		return *this;
	}

	// -= MArray Template
	template< class A, typename M >
	inline
	Array2 &
	operator -=( MArray2< A, M > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] -= a( i1, i2 );
			}
		}
		return *this;
	}

	// *= MArray Template
	template< class A, typename M >
	inline
	Array2 &
	operator *=( MArray2< A, M > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] *= a( i1, i2 );
			}
		}
		return *this;
	}

	// /= MArray Template
	template< class A, typename M >
	inline
	Array2 &
	operator /=( MArray2< A, M > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				assert( a( i1, i2 ) != T( 0 ) );
				data_[ l ] /= a( i1, i2 );
			}
		}
		return *this;
	}

public: // Assignment: Array: Logical

	// &&= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	and_equals( Array2< U > const & a )
	{
		assert( conformable( a ) );
		Super::and_equals( a );
		return *this;
	}

	// ||= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	or_equals( Array2< U > const & a )
	{
		assert( conformable( a ) );
		Super::or_equals( a );
		return *this;
	}

	// &&= Slice
	inline
	Array2 &
	and_equals( Array2S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					c[ l ] = a( i1, i2 );
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] = data_[ i ] && c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					data_[ l ] = data_[ l ] && a( i1, i2 );
				}
			}
		}
		return *this;
	}

	// ||= Slice
	inline
	Array2 &
	or_equals( Array2S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					c[ l ] = a( i1, i2 );
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] = data_[ i ] || c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
				for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
					data_[ l ] = data_[ l ] || a( i1, i2 );
				}
			}
		}
		return *this;
	}

	// &&= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	and_equals( Array2S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] = data_[ l ] && a( i1, i2 );
			}
		}
		return *this;
	}

	// ||= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	or_equals( Array2S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] = data_[ l ] || a( i1, i2 );
			}
		}
		return *this;
	}

	// &&= MArray Template
	template< class A, typename M >
	inline
	Array2 &
	and_equals( MArray2< A, M > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] = data_[ l ] && a( i1, i2 );
			}
		}
		return *this;
	}

	// ||= MArray Template
	template< class A, typename M >
	inline
	Array2 &
	or_equals( MArray2< A, M > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2, ++l ) {
				data_[ l ] = data_[ l ] || a( i1, i2 );
			}
		}
		return *this;
	}

public: // Assignment: Value

	// = Value
	inline
	Array2 &
	operator =( T const & t )
	{
		Super::operator =( t );
		return *this;
	}

	// += Value
	inline
	Array2 &
	operator +=( T const & t )
	{
		Super::operator +=( t );
		return *this;
	}

	// -= Value
	inline
	Array2 &
	operator -=( T const & t )
	{
		Super::operator -=( t );
		return *this;
	}

	// *= Value
	inline
	Array2 &
	operator *=( T const & t )
	{
		Super::operator *=( t );
		return *this;
	}

	// /= Value
	inline
	Array2 &
	operator /=( T const & t )
	{
		Super::operator /=( t );
		return *this;
	}

public: // Subscript

	// array( i1, i2 ) const
	inline
	T const &
	operator ()( int const i1, int const i2 ) const
	{
		assert( contains( i1, i2 ) );
		return sdata_[ ( i1 * z2_ ) + i2 ];
	}

	// array( i1, i2 )
	inline
	T &
	operator ()( int const i1, int const i2 )
	{
		assert( contains( i1, i2 ) );
		return sdata_[ ( i1 * z2_ ) + i2 ];
	}

	// Linear Index
	inline
	size_type
	index( int const i1, int const i2 ) const
	{
		return ( ( i1 * z2_ ) + i2 ) - shift_;
	}

	// Const Tail Starting at array( i1, i2 )
	inline
	Tail const
	a( int const i1, int const i2 ) const
	{
		assert( contains( i1, i2 ) );
		size_type const offset( ( ( i1 * z2_ ) + i2 ) - shift_ );
		return Tail( static_cast< T const * >( data_ + offset ), ( data_size_ != npos ? data_size_ - offset : npos ) );
	}

	// Tail Starting at array( i1, i2 )
	inline
	Tail
	a( int const i1, int const i2 )
	{
		assert( contains( i1, i2 ) );
		size_type const offset( ( ( i1 * z2_ ) + i2 ) - shift_ );
		return Tail( data_ + offset, ( data_size_ != npos ? data_size_ - offset : npos ) );
	}

public: // Slice Proxy Generators

	// array( s1, s2 ) const
	inline
	Array2S< T >
	operator ()( IS const & s1, IS const & s2 ) const
	{
		DS const d1( I1_, s1, z2_ );
		DS const d2( I2_, s2 );
		return Array2S< T >( data_, -shift_, d1, d2 );
	}

	// array( i1, s2 ) const
	inline
	Array1S< T >
	operator ()( int const i1, IS const & s2 ) const
	{
		int k( -shift_ );
		k += slice_k( I1_, i1, z2_ );
		DS const d2( I2_, s2 );
		return Array1S< T >( data_, k, d2 );
	}

	// array( s1, i2 ) const
	inline
	Array1S< T >
	operator ()( IS const & s1, int const i2 ) const
	{
		int k( -shift_ );
		DS const d1( I1_, s1, z2_ );
		k += slice_k( I2_, i2 );
		return Array1S< T >( data_, k, d1 );
	}

	// array( s1, s2 )
	inline
	Array2S< T >
	operator ()( IS const & s1, IS const & s2 )
	{
		DS const d1( I1_, s1, z2_ );
		DS const d2( I2_, s2 );
		return Array2S< T >( data_, -shift_, d1, d2 );
	}

	// array( i1, s2 )
	inline
	Array1S< T >
	operator ()( int const i1, IS const & s2 )
	{
		int k( -shift_ );
		k += slice_k( I1_, i1, z2_ );
		DS const d2( I2_, s2 );
		return Array1S< T >( data_, k, d2 );
	}

	// array( s1, i2 )
	inline
	Array1S< T >
	operator ()( IS const & s1, int const i2 )
	{
		int k( -shift_ );
		DS const d1( I1_, s1, z2_ );
		k += slice_k( I2_, i2 );
		return Array1S< T >( data_, k, d1 );
	}

public: // Predicate

	// Contains Indexed Element?
	inline
	bool
	contains( int const i1, int const i2 ) const
	{
		return ( I1_.contains( i1 ) && I2_.contains( i2 ) );
	}

	// Conformable?
	template< typename U >
	inline
	bool
	conformable( Array2< U > const & a ) const
	{
		return ( ( z1_ == a.z1_ ) && ( z2_ == a.z2_ ) );
	}

	// Conformable?
	template< typename U >
	inline
	bool
	conformable( Array2S< U > const & a ) const
	{
		return ( ( z1_ == a.size1() ) && ( z2_ == a.size2() ) );
	}

	// Conformable?
	template< class A, typename M >
	inline
	bool
	conformable( MArray2< A, M > const & a ) const
	{
		return ( ( z1_ == a.size1() ) && ( z2_ == a.size2() ) );
	}

	// Equal Dimensions?
	template< typename U >
	inline
	bool
	equal_dimensions( Array2< U > const & a ) const
	{
		return ( ( I1_ == a.I1_ ) && ( I2_ == a.I2_ ) );
	}

	// Equal Dimensions?
	template< typename U >
	inline
	bool
	equal_dimensions( Array2S< U > const & a ) const
	{
		return ( ( l1() == 1 ) && ( u1() == a.u1() ) && ( l2() == 1 ) && ( u2() == a.u2() ) );
	}

	// Equal Dimensions?
	template< class A, typename M >
	inline
	bool
	equal_dimensions( MArray2< A, M > const & a ) const
	{
		return ( ( l1() == 1 ) && ( u1() == a.u1() ) && ( l2() == 1 ) && ( u2() == a.u2() ) );
	}

	// Is Identity?
	inline
	bool
	is_identity() const
	{
		static T const ZERO( 0 );
		static T const ONE( 1 );
		Array2 const & A( *this ); // Shorthand name
		if ( ! square() ) { // Non-square
			return false;
		} else { // Square
			for ( int i = l1(), ie = u1(); i <= ie; ++i ) {
				int const jd( l2() + ( i - l1() ) ); // Col index of diagonal
				for ( int j = l2(), je = u2(); j <= je; ++j ) {
					if ( A( i, j ) != ( j == jd ? ONE : ZERO ) ) return false;
				}
			}
			return true;
		}
	}

	// Square?
	inline
	bool
	square() const
	{
		return ( z1_ == z2_ );
	}

	// Square and Equal Dimensions?
	inline
	bool
	equal_square_dimensions() const
	{
		return ( I1_ == I2_ );
	}

	// Symmetric?
	inline
	bool
	symmetric() const
	{
		Array2 const & A( *this ); // Shorthand name
		if ( I1_ != I2_ ) { // Unequal index ranges
			return false;
		} else { // Equal index ranges
			for ( int i = l1(), ie = u1(); i <= ie; ++i ) {
				for ( int j = l2(), je = i - 1; j <= je; ++j ) {
					if ( A( i, j ) != A( j, i ) ) return false;
				}
			}
			return true;
		}
	}

public: // Inspector

	// Rank
	inline
	int
	rank() const
	{
		return 2;
	}

	// IndexRange of a Dimension
	inline
	IR const &
	I( int const d ) const
	{
		switch ( d ) {
		case 1:
			return I1_;
		case 2:
			return I2_;
		default:
			assert( false );
			return I1_;
		}
	}

	// Lower Index of a Dimension
	inline
	int
	l( int const d ) const
	{
		switch ( d ) {
		case 1:
			return l1();
		case 2:
			return l2();
		default:
			assert( false );
			return l1();
		}
	}

	// Upper Index of a Dimension
	inline
	int
	u( int const d ) const
	{
		switch ( d ) {
		case 1:
			return u1();
		case 2:
			return u2();
		default:
			assert( false );
			return u1();
		}
	}

	// Size of a Dimension
	inline
	size_type
	size( int const d ) const
	{
		switch ( d ) {
		case 1:
			return z1_;
		case 2:
			return z2_;
		default:
			assert( false );
			return z1_;
		}
	}

	// Size of a Dimension
	inline
	int
	isize( int const d ) const
	{
		switch ( d ) {
		case 1:
			return isize1();
		case 2:
			return isize2();
		default:
			assert( false );
			return isize1();
		}
	}

	// IndexRange of Dimension 1
	inline
	IR const &
	I1() const
	{
		return I1_;
	}

	// Lower Index of Dimension 1
	inline
	int
	l1() const
	{
		return I1_.l();
	}

	// Upper Index of Dimension 1
	inline
	int
	u1() const
	{
		return I1_.u();
	}

	// Size of Dimension 1
	inline
	size_type
	size1() const
	{
		return z1_;
	}

	// Size of Dimension 1
	inline
	int
	isize1() const
	{
		return static_cast< int >( z1_ );
	}

	// IndexRange of Dimension 2
	inline
	IR const &
	I2() const
	{
		return I2_;
	}

	// Lower Index of Dimension 2
	inline
	int
	l2() const
	{
		return I2_.l();
	}

	// Upper Index of Dimension 2
	inline
	int
	u2() const
	{
		return I2_.u();
	}

	// Size of Dimension 2
	inline
	size_type
	size2() const
	{
		return z2_;
	}

	// Size of Dimension 2
	inline
	int
	isize2() const
	{
		return static_cast< int >( z2_ );
	}

public: // Modifier

	// Clear
	inline
	Array2 &
	clear()
	{
		Super::clear();
		I1_.clear();
		I2_.clear();
		z1_ = z2_ = 0u;
		return *this;
	}

	// Assign Default Value to all Elements
	inline
	Array2 &
	to_default()
	{
		Super::to_default();
		return *this;
	}

	// Set to the Identity Matrix
	inline
	Array2 &
	to_identity()
	{
		assert( square() );
		Array2 & A( *this ); // Shorthand name
		A = T( 0 ); // Zero the array
		T const One( T( 1 ) );
		for ( size_type l = 0, l_inc = z1_ + 1; l < size_; l += l_inc ) {
			A[ l ] = One;
		}
		return *this;
	}

	// Set to Diagonal Matrix with Uniform Value
	inline
	Array2 &
	to_diag( T const & d )
	{
		assert( square() );
		Array2 & A( *this ); // Shorthand name
		A = T( 0 ); // Zero the array
		for ( size_type l = 0, l_inc = z1_ + 1; l < size_; l += l_inc ) {
			A[ l ] = d;
		}
		return *this;
	}

	// Set Diagonal of Matrix to a Uniform Value
	inline
	Array2 &
	set_diagonal( T const & d )
	{
		assert( square() );
		Array2 & A( *this ); // Shorthand name
		for ( size_type l = 0, l_inc = z1_ + 1; l < size_; l += l_inc ) {
			A[ l ] = d;
		}
		return *this;
	}

	// Transpose
	inline
	Array2 &
	transpose()
	{
		using std::swap; // Allows std::swap to be used if no T version
		assert( square() ); // So dimensions aren't changed
		Array2 & A( *this ); // Shorthand name
		for ( size_type i = 0; i < z2_; ++i ) {
			for ( size_type j = 0, l = i * z2_, lT = i; j < i; ++j, ++l, lT += z2_ ) {
				swap( A[ lT ], A[ l ] );
			}
		}
		return *this;
	}

	// Right Multiply By Array
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	right_multiply_by( Array2< U > const & a )
	{
		size_type const as1( a.z1_ );
		size_type const as2( a.z2_ );
		assert( z2_ == as1 );
		assert( as1 == as2 ); // Square so that this array's dimensions aren't changed
		Array2 & t( *this ); // Shorthand name for this array
		T * const r( new T[ z2_ ] ); // Temporary row
		for ( size_type i = 0; i < z1_; ++i ) {
			for ( size_type j = 0, lt_beg = i * z2_, lt_end = lt_beg + z2_; j < as2; ++j ) {
				T d( 0 );
				for ( size_type lt = lt_beg, la = j; lt < lt_end; ++lt, la += as2 ) {
					d += t[ lt ] * a[ la ];
				}
				r[ j ] = d;
			}
			for ( size_type l = 0, lt = i * z2_; l < z2_; ++l, ++lt ) { // Copy in the new row
				t[ lt ] = r[ l ];
			}
		}
		delete[] r;
		return *this;
	}

	// Right Multiply By Transpose of Array
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	Array2 &
	right_multiply_by_transpose( Array2< U > const & a )
	{
		size_type const as1( a.z1_ );
		size_type const as2( a.z2_ );
		assert( z2_ == as2 );
		assert( as1 == as2 ); // Square so that this array's dimensions aren't changed
		Array2 & t( *this ); // Shorthand name for this array
		T * const r( new T[ z2_ ] ); // Temporary row
		for ( size_type i = 0; i < z1_; ++i ) {
			for ( size_type j = 0, lt_beg = i * z2_, lt_end = lt_beg + z2_, la = 0; j < as1; ++j ) {
				T d( 0 );
				for ( size_type lt = lt_beg; lt < lt_end; ++lt, ++la ) {
					d += t[ lt ] * a[ la ];
				}
				r[ j ] = d;
			}
			for ( size_type l = 0, lt = i * z2_; l < z2_; ++l, ++lt ) { // Copy in the new row
				t[ lt ] = r[ l ];
			}
		}
		delete[] r;
		return *this;
	}

public: // MArray Generators

	// Template Helpers
	template< typename U > class Wrapper {};
	typedef  typename std::conditional< std::is_class< T >::value, T, Wrapper< T > >::type  ClassT;

	// MArray Generator
	template< typename M >
	inline
	MArray2< Array2 const, M >
	ma( M ClassT::* pmem ) const
	{
		return MArray2< Array2 const, M >( *this, pmem );
	}

	// MArray Generator
	template< typename M >
	inline
	MArray2< Array2, M >
	ma( M ClassT::* pmem )
	{
		return MArray2< Array2, M >( *this, pmem );
	}

#include <ObjexxFCL/Array2.Project.MArray.hh> // Inject project-specific MArray generators

public: // Comparison: Predicate

	// Array2 == Array2
	inline
	friend
	bool
	eq( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return eq( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 != Array2
	inline
	friend
	bool
	ne( Array2 const & a, Array2 const & b )
	{
		return ! eq( a, b );
	}

	// Array2 < Array2
	inline
	friend
	bool
	lt( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return lt( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 <= Array2
	inline
	friend
	bool
	le( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return le( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 > Array2
	inline
	friend
	bool
	gt( Array2 const & a, Array2 const & b )
	{
		return lt( b, a );
	}

	// Array2 >= Array2
	inline
	friend
	bool
	ge( Array2 const & a, Array2 const & b )
	{
		return le( b, a );
	}

public: // Comparison: Predicate: Any

	// Array2 == Array2
	inline
	friend
	bool
	any_eq( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return any_eq( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 != Array2
	inline
	friend
	bool
	any_ne( Array2 const & a, Array2 const & b )
	{
		return ! eq( a, b );
	}

	// Array2 < Array2
	inline
	friend
	bool
	any_lt( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return any_lt( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 <= Array2
	inline
	friend
	bool
	any_le( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return any_le( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 > Array2
	inline
	friend
	bool
	any_gt( Array2 const & a, Array2 const & b )
	{
		return any_lt( b, a );
	}

	// Array2 >= Array2
	inline
	friend
	bool
	any_ge( Array2 const & a, Array2 const & b )
	{
		return any_le( b, a );
	}

public: // Comparison: Predicate: All

	// Array2 == Array2
	inline
	friend
	bool
	all_eq( Array2 const & a, Array2 const & b )
	{
		return eq( a, b );
	}

	// Array2 != Array2
	inline
	friend
	bool
	all_ne( Array2 const & a, Array2 const & b )
	{
		return ! any_eq( a, b );
	}

	// Array2 < Array2
	inline
	friend
	bool
	all_lt( Array2 const & a, Array2 const & b )
	{
		return lt( a, b );
	}

	// Array2 <= Array2
	inline
	friend
	bool
	all_le( Array2 const & a, Array2 const & b )
	{
		return le( a, b );
	}

	// Array2 > Array2
	inline
	friend
	bool
	all_gt( Array2 const & a, Array2 const & b )
	{
		return gt( a, b );
	}

	// Array2 >= Array2
	inline
	friend
	bool
	all_ge( Array2 const & a, Array2 const & b )
	{
		return ge( a, b );
	}

public: // Comparison: Count

	// Array2 == Array2
	inline
	friend
	bool
	count_eq( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_eq( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 != Array2
	inline
	friend
	bool
	count_ne( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_ne( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 < Array2
	inline
	friend
	bool
	count_lt( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_lt( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 <= Array2
	inline
	friend
	bool
	count_le( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_le( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 > Array2
	inline
	friend
	bool
	count_gt( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_gt( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// Array2 >= Array2
	inline
	friend
	bool
	count_ge( Array2 const & a, Array2 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_ge( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

public: // Comparison: Predicate: Slice

	// Array2 == Array2S
	inline
	friend
	bool
	eq( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] == b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2 != Array2S
	inline
	friend
	bool
	ne( Array2 const & a, Array2S< T > const & b )
	{
		return ! eq( a, b );
	}

	// Array2 < Array2S
	inline
	friend
	bool
	lt( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] < b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2 <= Array2S
	inline
	friend
	bool
	le( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] <= b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2 > Array2S
	inline
	friend
	bool
	gt( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] > b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2 >= Array2S
	inline
	friend
	bool
	ge( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] >= b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2S == Array2
	inline
	friend
	bool
	eq( Array2S< T > const & a, Array2 const & b )
	{
		return eq( b, a );
	}

	// Array2S != Array2
	inline
	friend
	bool
	ne( Array2S< T > const & a, Array2 const & b )
	{
		return ne( b, a );
	}

	// Array2S < Array2
	inline
	friend
	bool
	lt( Array2S< T > const & a, Array2 const & b )
	{
		return gt( b, a );
	}

	// Array2S <= Array2
	inline
	friend
	bool
	le( Array2S< T > const & a, Array2 const & b )
	{
		return ge( b, a );
	}

	// Array2S > Array2
	inline
	friend
	bool
	gt( Array2S< T > const & a, Array2 const & b )
	{
		return lt( b, a );
	}

	// Array2S >= Array2
	inline
	friend
	bool
	ge( Array2S< T > const & a, Array2 const & b )
	{
		return le( b, a );
	}

public: // Comparison: Predicate: Any: Slice

	// Any Array2 == Array2S
	inline
	friend
	bool
	any_eq( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] == b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2 != Array2S
	inline
	friend
	bool
	any_ne( Array2 const & a, Array2S< T > const & b )
	{
		return ! eq( a, b );
	}

	// Any Array2 < Array2S
	inline
	friend
	bool
	any_lt( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] < b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2 <= Array2S
	inline
	friend
	bool
	any_le( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] <= b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2 > Array2S
	inline
	friend
	bool
	any_gt( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] > b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2 >= Array2S
	inline
	friend
	bool
	any_ge( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] >= b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2S == Array2
	inline
	friend
	bool
	any_eq( Array2S< T > const & a, Array2 const & b )
	{
		return any_eq( b, a );
	}

	// Any Array2S != Array2
	inline
	friend
	bool
	any_ne( Array2S< T > const & a, Array2 const & b )
	{
		return any_ne( b, a );
	}

	// Any Array2S < Array2
	inline
	friend
	bool
	any_lt( Array2S< T > const & a, Array2 const & b )
	{
		return any_gt( b, a );
	}

	// Any Array2S <= Array2
	inline
	friend
	bool
	any_le( Array2S< T > const & a, Array2 const & b )
	{
		return any_ge( b, a );
	}

	// Any Array2S > Array2
	inline
	friend
	bool
	any_gt( Array2S< T > const & a, Array2 const & b )
	{
		return any_lt( b, a );
	}

	// Any Array2S >= Array2
	inline
	friend
	bool
	any_ge( Array2S< T > const & a, Array2 const & b )
	{
		return any_le( b, a );
	}

public: // Comparison: Predicate: All: Slice

	// All Array2 == Array2S
	inline
	friend
	bool
	all_eq( Array2 const & a, Array2S< T > const & b )
	{
		return eq( a, b );
	}

	// All Array2 != Array2S
	inline
	friend
	bool
	all_ne( Array2 const & a, Array2S< T > const & b )
	{
		return ! any_eq( a, b );
	}

	// All Array2 < Array2S
	inline
	friend
	bool
	all_lt( Array2 const & a, Array2S< T > const & b )
	{
		return lt( a, b );
	}

	// All Array2 <= Array2S
	inline
	friend
	bool
	all_le( Array2 const & a, Array2S< T > const & b )
	{
		return le( a, b );
	}

	// All Array2 > Array2S
	inline
	friend
	bool
	all_gt( Array2 const & a, Array2S< T > const & b )
	{
		return gt( a, b );
	}

	// All Array2 >= Array2S
	inline
	friend
	bool
	all_ge( Array2 const & a, Array2S< T > const & b )
	{
		return ge( a, b );
	}

	// All Array2S == Array2
	inline
	friend
	bool
	all_eq( Array2S< T > const & a, Array2 const & b )
	{
		return all_eq( b, a );
	}

	// All Array2S != Array2
	inline
	friend
	bool
	all_ne( Array2S< T > const & a, Array2 const & b )
	{
		return all_ne( b, a );
	}

	// All Array2S < Array2
	inline
	friend
	bool
	all_lt( Array2S< T > const & a, Array2 const & b )
	{
		return all_gt( b, a );
	}

	// All Array2S <= Array2
	inline
	friend
	bool
	all_le( Array2S< T > const & a, Array2 const & b )
	{
		return all_ge( b, a );
	}

	// All Array2S > Array2
	inline
	friend
	bool
	all_gt( Array2S< T > const & a, Array2 const & b )
	{
		return all_lt( b, a );
	}

	// All Array2S >= Array2
	inline
	friend
	bool
	all_ge( Array2S< T > const & a, Array2 const & b )
	{
		return all_le( b, a );
	}

public: // Comparison: Count: Slice

	// Count Array2 == Array2S
	inline
	friend
	size_type
	count_eq( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] == b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 != Array2S
	inline
	friend
	size_type
	count_ne( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] != b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 < Array2S
	inline
	friend
	size_type
	count_lt( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] < b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 <= Array2S
	inline
	friend
	size_type
	count_le( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] <= b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 > Array2S
	inline
	friend
	size_type
	count_gt( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] > b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 >= Array2S
	inline
	friend
	size_type
	count_ge( Array2 const & a, Array2S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] >= b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2S == Array2
	inline
	friend
	size_type
	count_eq( Array2S< T > const & a, Array2 const & b )
	{
		return count_eq( b, a );
	}

	// Count Array2S != Array2
	inline
	friend
	size_type
	count_ne( Array2S< T > const & a, Array2 const & b )
	{
		return count_ne( b, a );
	}

	// Count Array2S < Array2
	inline
	friend
	size_type
	count_lt( Array2S< T > const & a, Array2 const & b )
	{
		return count_gt( b, a );
	}

	// Count Array2S <= Array2
	inline
	friend
	size_type
	count_le( Array2S< T > const & a, Array2 const & b )
	{
		return count_ge( b, a );
	}

	// Count Array2S > Array2
	inline
	friend
	size_type
	count_gt( Array2S< T > const & a, Array2 const & b )
	{
		return count_lt( b, a );
	}

	// Count Array2S >= Array2
	inline
	friend
	size_type
	count_ge( Array2S< T > const & a, Array2 const & b )
	{
		return count_le( b, a );
	}

public: // Comparison: Predicate: MArray

	// Array2 == MArray2
	template< class A >
	inline
	friend
	bool
	eq( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] == b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2 != MArray2
	template< class A >
	inline
	friend
	bool
	ne( Array2 const & a, MArray2< A, T > const & b )
	{
		return ! eq( a, b );
	}

	// Array2 < MArray2
	template< class A >
	inline
	friend
	bool
	lt( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] < b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2 <= MArray2
	template< class A >
	inline
	friend
	bool
	le( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] <= b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2 > MArray2
	template< class A >
	inline
	friend
	bool
	gt( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] > b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// Array2 >= MArray2
	template< class A >
	inline
	friend
	bool
	ge( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( ! ( a[ l ] >= b( i1, i2 ) ) ) return false;
			}
		}
		return true;
	}

	// MArray2 == Array2
	template< class A >
	inline
	friend
	bool
	eq( MArray2< A, T > const & a, Array2 const & b )
	{
		return eq( b, a );
	}

	// MArray2 != Array2
	template< class A >
	inline
	friend
	bool
	ne( MArray2< A, T > const & a, Array2 const & b )
	{
		return ne( b, a );
	}

	// MArray2 < Array2
	template< class A >
	inline
	friend
	bool
	lt( MArray2< A, T > const & a, Array2 const & b )
	{
		return gt( b, a );
	}

	// MArray2 <= Array2
	template< class A >
	inline
	friend
	bool
	le( MArray2< A, T > const & a, Array2 const & b )
	{
		return ge( b, a );
	}

	// MArray2 > Array2
	template< class A >
	inline
	friend
	bool
	gt( MArray2< A, T > const & a, Array2 const & b )
	{
		return lt( b, a );
	}

	// MArray2 >= Array2
	template< class A >
	inline
	friend
	bool
	ge( MArray2< A, T > const & a, Array2 const & b )
	{
		return le( b, a );
	}

public: // Comparison: Predicate: Any: MArray

	// Any Array2 == MArray2
	template< class A >
	inline
	friend
	bool
	any_eq( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] == b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2 != MArray2
	template< class A >
	inline
	friend
	bool
	any_ne( Array2 const & a, MArray2< A, T > const & b )
	{
		return ! eq( a, b );
	}

	// Any Array2 < MArray2
	template< class A >
	inline
	friend
	bool
	any_lt( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		if ( &a == &b ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] < b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2 <= MArray2
	template< class A >
	inline
	friend
	bool
	any_le( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] <= b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2 > MArray2
	template< class A >
	inline
	friend
	bool
	any_gt( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		if ( &a == &b ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] > b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any Array2 >= MArray2
	template< class A >
	inline
	friend
	bool
	any_ge( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] >= b( i1, i2 ) ) return true;
			}
		}
		return false;
	}

	// Any MArray2 == Array2
	template< class A >
	inline
	friend
	bool
	any_eq( MArray2< A, T > const & a, Array2 const & b )
	{
		return any_eq( b, a );
	}

	// Any MArray2 != Array2
	template< class A >
	inline
	friend
	bool
	any_ne( MArray2< A, T > const & a, Array2 const & b )
	{
		return any_ne( b, a );
	}

	// Any MArray2 < Array2
	template< class A >
	inline
	friend
	bool
	any_lt( MArray2< A, T > const & a, Array2 const & b )
	{
		return any_gt( b, a );
	}

	// Any MArray2 <= Array2
	template< class A >
	inline
	friend
	bool
	any_le( MArray2< A, T > const & a, Array2 const & b )
	{
		return any_ge( b, a );
	}

	// Any MArray2 > Array2
	template< class A >
	inline
	friend
	bool
	any_gt( MArray2< A, T > const & a, Array2 const & b )
	{
		return any_lt( b, a );
	}

	// Any MArray2 >= Array2
	template< class A >
	inline
	friend
	bool
	any_ge( MArray2< A, T > const & a, Array2 const & b )
	{
		return any_le( b, a );
	}

public: // Comparison: Predicate: All: MArray

	// All Array2 == MArray2
	template< class A >
	inline
	friend
	bool
	all_eq( Array2 const & a, MArray2< A, T > const & b )
	{
		return eq( a, b );
	}

	// All Array2 != MArray2
	template< class A >
	inline
	friend
	bool
	all_ne( Array2 const & a, MArray2< A, T > const & b )
	{
		return ! any_eq( a, b );
	}

	// All Array2 < MArray2
	template< class A >
	inline
	friend
	bool
	all_lt( Array2 const & a, MArray2< A, T > const & b )
	{
		return lt( a, b );
	}

	// All Array2 <= MArray2
	template< class A >
	inline
	friend
	bool
	all_le( Array2 const & a, MArray2< A, T > const & b )
	{
		return le( a, b );
	}

	// All Array2 > MArray2
	template< class A >
	inline
	friend
	bool
	all_gt( Array2 const & a, MArray2< A, T > const & b )
	{
		return gt( a, b );
	}

	// All Array2 >= MArray2
	template< class A >
	inline
	friend
	bool
	all_ge( Array2 const & a, MArray2< A, T > const & b )
	{
		return ge( a, b );
	}

	// All MArray2 == Array2
	template< class A >
	inline
	friend
	bool
	all_eq( MArray2< A, T > const & a, Array2 const & b )
	{
		return all_eq( b, a );
	}

	// All MArray2 != Array2
	template< class A >
	inline
	friend
	bool
	all_ne( MArray2< A, T > const & a, Array2 const & b )
	{
		return all_ne( b, a );
	}

	// All MArray2 < Array2
	template< class A >
	inline
	friend
	bool
	all_lt( MArray2< A, T > const & a, Array2 const & b )
	{
		return all_gt( b, a );
	}

	// All MArray2 <= Array2
	template< class A >
	inline
	friend
	bool
	all_le( MArray2< A, T > const & a, Array2 const & b )
	{
		return all_ge( b, a );
	}

	// All MArray2 > Array2
	template< class A >
	inline
	friend
	bool
	all_gt( MArray2< A, T > const & a, Array2 const & b )
	{
		return all_lt( b, a );
	}

	// All MArray2 >= Array2
	template< class A >
	inline
	friend
	bool
	all_ge( MArray2< A, T > const & a, Array2 const & b )
	{
		return all_le( b, a );
	}

public: // Comparison: Count: MArray

	// Count Array2 == MArray2
	template< class A >
	inline
	friend
	size_type
	count_eq( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] == b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 != MArray2
	template< class A >
	inline
	friend
	size_type
	count_ne( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] != b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 < MArray2
	template< class A >
	inline
	friend
	size_type
	count_lt( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] < b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 <= MArray2
	template< class A >
	inline
	friend
	size_type
	count_le( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] <= b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 > MArray2
	template< class A >
	inline
	friend
	size_type
	count_gt( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] > b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count Array2 >= MArray2
	template< class A >
	inline
	friend
	size_type
	count_ge( Array2 const & a, MArray2< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1 ) {
			for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2, ++l ) {
				if ( a[ l ] >= b( i1, i2 ) ) ++n;
			}
		}
		return n;
	}

	// Count MArray2 == Array2
	template< class A >
	inline
	friend
	size_type
	count_eq( MArray2< A, T > const & a, Array2 const & b )
	{
		return count_eq( b, a );
	}

	// Count MArray2 != Array2
	template< class A >
	inline
	friend
	size_type
	count_ne( MArray2< A, T > const & a, Array2 const & b )
	{
		return count_ne( b, a );
	}

	// Count MArray2 < Array2
	template< class A >
	inline
	friend
	size_type
	count_lt( MArray2< A, T > const & a, Array2 const & b )
	{
		return count_gt( b, a );
	}

	// Count MArray2 <= Array2
	template< class A >
	inline
	friend
	size_type
	count_le( MArray2< A, T > const & a, Array2 const & b )
	{
		return count_ge( b, a );
	}

	// Count MArray2 > Array2
	template< class A >
	inline
	friend
	size_type
	count_gt( MArray2< A, T > const & a, Array2 const & b )
	{
		return count_lt( b, a );
	}

	// Count MArray2 >= Array2
	template< class A >
	inline
	friend
	size_type
	count_ge( MArray2< A, T > const & a, Array2 const & b )
	{
		return count_le( b, a );
	}

protected: // Functions

	// Dimension by IndexRange
	virtual
	void
	dimension_assign( IR const & I1, IR const & I2 ) = 0;

	// Clear on Move
	inline
	void
	clear_move()
	{
		I1_.clear();
		I2_.clear();
		z1_ = z2_ = 0u;
	}

	// Swap
	inline
	void
	swap2( Array2 & v )
	{
		swapB( v );
		I1_.swap( v.I1_ );
		I2_.swap( v.I2_ );
		std::swap( z1_, v.z1_ );
		std::swap( z2_, v.z2_ );
	}

protected: // Data

	IR I1_; // Index range of dim 1
	IR I2_; // Index range of dim 2

	size_type z1_; // Size of dim 1
	size_type z2_; // Size of dim 2

}; // Array2

// Conformable?
template< typename U, typename V >
inline
bool
conformable( Array2< U > const & a, Array2< V > const & b )
{
	return a.conformable( b );
}

// Conformable?
template< typename U, typename V >
inline
bool
conformable( Array2< U > const & a, Array2S< V > const & b )
{
	return a.conformable( b );
}

// Conformable?
template< typename U, typename V >
inline
bool
conformable( Array2S< U > const & a, Array2< V > const & b )
{
	return b.conformable( a );
}

// Conformable?
template< typename U, class A, typename M >
inline
bool
conformable( Array2< U > const & a, MArray2< A, M > const & b )
{
	return a.conformable( b );
}

// Conformable?
template< class A, typename M, typename V >
inline
bool
conformable( MArray2< A, M > const & a, Array2< V > const & b )
{
	return b.conformable( a );
}

// Equal Dimensions?
template< typename U, typename V >
inline
bool
equal_dimensions( Array2< U > const & a, Array2< V > const & b )
{
	return a.equal_dimensions( b );
}

} // ObjexxFCL

#endif // ObjexxFCL_Array2_hh_INCLUDED
