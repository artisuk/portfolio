#pragma once

// a typedef that defines what type will be accepted for the size and stuff
typedef int StaticArraySizeType;


// a internal array that is nested
// should be very quick
template< class TType, StaticArraySizeType ICurrentDimensionCount, StaticArraySizeType... TOtherDimensions >
class TStaticArrayInternal
{
public:
	static const int DimensionCount = sizeof...( TOtherDimensions );

private:
	typedef TStaticArrayInternal< TType, ICurrentDimensionCount, TOtherDimensions... > ThisType;

	template< int b >
	struct select
	{
		typedef TStaticArrayInternal< TType, TOtherDimensions... > type;
	};
	template<>
	struct select< 0 >
	{
		typedef TType type;
	};

public:
	// https://stackoverflow.com/questions/8243134/c-templates-select-different-type-based-on-value-of-template-parameter
	typedef typename select< DimensionCount >::type InnerArrayType;

public:
	// empty constructor
	TStaticArrayInternal()
		: m_aArray()
	{}

	// constructor with default value
	TStaticArrayInternal( const TType& rDefValue )
	{
		for( int iIndex = 0; iIndex < ICurrentDimensionCount; ++iIndex )
		{
			m_aArray[ iIndex ] = rDefValue;
		}
	}

	// initialiser list

	// copy constructor
	TStaticArrayInternal( const ThisType& rOther )
	{
		for( int iIndex = 0; iIndex < ICurrentDimensionCount; ++iIndex )
		{
			m_aArray[ iIndex ] = rOther.m_aArray[ iIndex ];
		}
	}

	// assign operator
	void operator=( const ThisType& rOther )
	{
		for( int iIndex = 0; iIndex < ICurrentDimensionCount; ++iIndex )
		{
			m_aArray[ iIndex ] = rOther.m_aArray[ iIndex ];
		}
	}


	static inline StaticArraySizeType GetArraySize()								{ return ICurrentDimensionCount; }
	inline InnerArrayType& operator[]( const StaticArraySizeType iIndex )			{ return m_aArray[ iIndex ]; }
	inline InnerArrayType& operator[]( const StaticArraySizeType iIndex ) const		{ return m_aArray[ iIndex ]; }

private:
	InnerArrayType m_aArray[ ICurrentDimensionCount ];
};

namespace StaticArrayNestedHelper
{
	template< class TType >
	constexpr int GetTotalSize( TType tType )
	{
		return tType;
	}

	template< class TType, class ...TDimensions >
	constexpr int GetTotalSize( TType tType, TDimensions... tDimensions )
	{
		return tType * GetTotalSize( tDimensions... );
	}
}

template< class TType, StaticArraySizeType... TDimensions >
class TStaticArrayNested
{
private:
	template< StaticArraySizeType >
	struct DimensionHelper { typedef StaticArraySizeType type; };
	
public:
	// extra 0 as it creates a nested array up to the last number
	typedef TStaticArrayInternal< TType, TDimensions... > InnerArrayType;
	
	static const StaticArraySizeType ArraySize = StaticArrayNestedHelper::GetTotalSize( ( TDimensions )... );
	static const StaticArraySizeType DimensionCount = sizeof...( TDimensions );

	// return the size of the iDimension'th dimension
	static StaticArraySizeType GetDimension( const StaticArraySizeType iDimension )
	{
		static const StaticArraySizeType DimensionSize[ ArraySize ] = { TDimensions... };
		return DimensionSize[ iDimension ];
	}

public:
	// empty constructor
	TStaticArrayNested()
		: m_cArray()
	{}

	// constructor with default value
	TStaticArrayNested( const TType& rDefValue )
		: m_cArray( rDefValue )
	{}

	// initialiser list

	// copy constructor
	TStaticArrayNested( const TStaticArrayNested<TType, TDimensions...>& rOther )
		: m_cArray( rOther.m_cArray )
	{}

	// assign operator
	inline void operator=( const TStaticArrayNested<TType, TDimensions...>& rOther )
	{
		m_cArray = rOther.m_cArray;
	}


	auto& operator[]( const StaticArraySizeType iIndex )				{ return m_cArray[ iIndex ]; }
	const auto& operator[]( const StaticArraySizeType iIndex ) const	{ return m_cArray[ iIndex ]; }
	TType* GetArrayPointer()											{ return &m_cArray; }
	TType* GetArrayPointer() const										{ return &m_cArray; }

	
private:
	InnerArrayType m_cArray;
};