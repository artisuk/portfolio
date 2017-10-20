---
layout: 				code
tag:					  code
published:			true
name:					  'Multidimensional variadic array'
date:   				2017-10-20 12:00:00 +0000
downloadables:
  - name: Multidimensional-Array.zip
    link: /assets/code/array/Multidimensional-Array.zip
---
<p>This is a multidimensional array that is fully templated. The array can handle any amount of dimensions while still being as efficient as possible.</p>
<p>The purpose of this is to have a convenient way to have n amount of dimensions for a constant sized array. Values can easily be copied to another array and a default value can be set conveniently to all the values of the array with a single method. Furthermore, it's easy to add asserts to ensure that the requested array item is not out of bounds, ensuring that the code is not trying to access an element that is beyond it's scope.</p>
<br/>
<h3>Code breakdown</h3>
<h4>Using the array</h4>
<p>The usage of the array is pretty straightforward, you use it in a similar manner you would use a C# array, but the declaration is slightly different.</p>

<p id="code_snippet_name">An example of how to declare an array and assigning all of values to 1.</p>
<pre class="prettyprint linenums:1  lang-cpp" style="white-space: pre-wrap;">TStaticArrayNested< int, 4, 4, 4 > cNestedArray( 1 );</pre>
<br/>

<h4>Implementation</h4>
<p>The arrays are hidden inside a class. Each dimension is placed within a nested class, this allows for multiple dimensions to be made from the same class. The superclass has multiple helpful features that allow the array to work the way it does.</p>
<p>The ArraySize is the total amount of elements within the array, this value is calculated during the compile time. Using constexpr functions and self-recursion, I was able to calculate the total size based on each dimension size. constexpr does not allow to have loops within it, so recursion was the answer. This consisted of having two methods, one took n amount of arguments, and another only took 1. The arguments had to be actual arguments, and could not be just templated values. This is a normal way to recursively go through a list of arguments from a variadic source.</p>
<br/>

<p id="code_snippet_name">Helpful functions that calculate the total amount of elements within the array.</p>
<pre class="prettyprint linenums:77 lang-cpp" style="white-space: pre-wrap;">
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
}</pre>
<br/>

<p>Another useful feature of this array is that it maintains and knows the size of each dimension. This can be retrieved using a GetDimension function by providing the dimension you want to know the size of. There is no asserts or error checking, but implementing one would not be too difficult. There is no direct way of returning the exact value of a particular template value, at least the ones that have been defined with ... thing. The workaround to this is to make a static array that contains all the values of the dimensions and return the asked dimension size.</p>

<p id="code_snippet_name">A function that returns the size of each dimension, no error checking.</p>
<pre class="prettyprint linenums:102 lang-cpp" style="white-space: pre-wrap;">
// return the size of the iDimension'th dimension
static StaticArraySizeType GetDimension( const StaticArraySizeType iDimension )
{
  static const StaticArraySizeType DimensionSize[ ArraySize ] = { TDimensions... };
  return DimensionSize[ iDimension ];
}</pre>
<br/>

<p>I needed a way to have the nested arrays, so it would act as one expects a nested array to work, using multiple []. For every dimension of an array, it would either select the type of object that the user wanted, or would take one of the dimensions out, and create a nested object of itself and repeat the process until no extra dimensions are provided.</p>
<p id="code_snippet_name">A method to change the type of an object based on the number of dimensions. If the number of dimensions equals 0(no more nested objects), the type then changed to the one used for the array, else use a nested array with one less dimension.</p>
<pre class="prettyprint linenums:18 lang-cpp" style="white-space: pre-wrap;">
static const int DimensionCount = sizeof...( TOtherDimensions );

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

typedef typename select< DimensionCount >::type InnerArrayType;</pre>
