---
layout: 				code
tag:					  code
published:			true
name:					  'Event System'
date:   				2016-12-13 12:00:00 +0000
downloadables:
  - name: EventSystem.zip
    link: /assets/code/eventsystem/EventSystem.zip
---
<p>This is an event system that was given to me as an assignment while I was at Gamer Camp.</p>
<p>The purpose of it was to be an easy to implement a system that would allow to get and send events between different objects. My goal was to make the system as flexible as possible. This entailed implementing a system that would accept any number of arguments, and any type of arguments. Thanks to c++11, the variadic templates was the answer to this conundrum.</p>
<p>The final product was able to register different events to a manager and listen to them while comparing the type of arguments that are being passed in, how many arguments are given, and the id (a string) is given. Based on all of these criteria, the right events will be called through function pointers that can be either static functions or member functions.</p>
<br/>
<h3>Code breakdown</h3>
<h4>Registering the event</h4>
<p>The syntax for registering the events is very simple. Everything being templated, and c++11 being smart, you don't have to directly specify any of the arguments for the templated function. The compiler will automatically extract the types and a number of arguments you want to listen to out of the function given to the register call.</p>

<p id="code_snippet_name">An example of how you would register a member function with multiple arguments.</p>
<pre class="prettyprint linenums:1  lang-cpp" style="white-space: pre-wrap;">CEventManager::GetEventManger()->RegisterEventMemberVariadic( "Callback test", this, MEMBER_VARIADIC_SELECTOR( CTestObject::CB_CallbackVariadicMember2 ) );</pre>
<br/>
<p id="code_snippet_name">An example of how you would register a static function with multiple arguments.</p>
<pre class="prettyprint linenums:1  lang-cpp" style="white-space: pre-wrap;">
CEventManager::GetEventManger()->RegisterEventStaticVariadic( "Callback test", &CB_CallbackVariadicStatic1 );

// Target function
void CTestObject::CB_CallbackVariadicStatic1( int iCount )
{}</pre>
<br/>

<h4>Calling the event</h4>
<p>Calling the events is harder than registering. There is no internal checks to see if the arguments you are giving match the registered events, it will not call them, but making a mistake of registering an of event with arguments of <int> or <char*> will not match if a <unsigned int> or <const char*> is provided. The order and the id of the event really matters here, mismatching any of them will cause the event not to be called.</p>
<p id="code_snippet_name">An example of how you would calling an event with varied types of arguments.</p>
<pre class="prettyprint linenums:1  lang-cpp" style="white-space: pre-wrap;">
CEventManager::GetEventManger()->CallEventVariadic( "Callback test", 100, 103.1231f, 2.1 );

// an example of what the method that would be called, thats if the name of the event matches
void CTestObject::CB_CallbackVariadicMember2( int iCount, float fValue, double dValue )
{}</pre>
<br/>

<h4>Implementation</h4>
<p>The entire implementation is done using variadic templates. This allows me to have templated classes that can have multiple arguments for each call. Obviously, as with every use of templates, each different implementation and combination of different arguments will generate more and more code that will bloat your final size. </p>
<p>Internally, there is a list of id's of each type provided, this will later help me to compare if a given type is the same as the one used for the event. This does mean that type of signed and unsigned are not the same, therefore sometimes causing bugs in relation to events not being called.</p>
<br/>

<p>The storing of the types was tricky, the solution to this was to store unique id to each time, then when calling the event, compare each one to ensure that the event and the call match</p>
<p>Iterating through each type provided was difficult, but the solution was simple. This does mean that the system is limited to POD and pointers, no references of custom objects, but it's not the worst loss.</p>
<p id="code_snippet_name">The store function that recursively will generate and store the id's within the internal array.</p>
<pre class="prettyprint linenums:1 lang-cpp" style="white-space: pre-wrap;">
template< class TType>
void Store( u32 uIndex, TType arg )
{
  m_aIDs[ uIndex ] = GetGCTypeIDOf( TType );
}

template< class TType, class ...AType >
void Store( u32 uIndex, TType arg, AType... args )
{
  m_aIDs[ uIndex ] = GetGCTypeIDOf( TType );
  Store( ++uIndex, args... );
}</pre>
<br/>

<p>In order to pass all the types and store them, I cheated the system. I casted all the given arguemnts to 0's. This should be supported by all the types, POD's and pointers (hence no references are supported). All the types are expanded as a arguement.</p>
<p id="code_snippet_name">Reusively process each argument that has been passed in as a cast to 0(this is why it only supports POD and pointers).</p>
<pre class="prettyprint linenums:1 lang-cpp" style="white-space: pre-wrap;">
Store( 0, ( ( Args )0 )... );</pre>
<br/>
<p id="code_snippet_name">Expanded version of given types int, float and double.</p>
<pre class="prettyprint linenums:1 lang-cpp" style="white-space: pre-wrap;">
Store( 0, ( ( int )0 ), ( ( float )0 ), ( ( double )0 ) );</pre>
