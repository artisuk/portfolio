function ShowHide( show )
{
	var container = document.getElementsByName( "img-container" )[ 0 ];
	var gameobj = container.querySelectorAll( "div.div-game" );
	var validobj = [];
	
	for( var i = 0, max = gameobj.length; i < max; ++i ) 
	{
		if( show == '' || gameobj[ i ].classList.contains( show ) )
		{
			gameobj[ i ].classList.add( "show" );
			validobj.push( gameobj[ i ] );
		}
		else
		{
			gameobj[ i ].classList.remove( "show" );
		}
	}
	
	var perLine = Math.floor( container.offsetWidth / 300 );
	
	var topPoint = 0;
	for( var i = 0, max = validobj.length; i < max; i += perLine ) 
	{
		for( var u = i; u < Math.min( max, i + perLine ); ++u )
		{
			var obj = validobj[ u ];
			
			obj.style.left = ( 300 * ( u % perLine ) ).toString() + "px";
			obj.style.top = ( topPoint ).toString() + "px";
		}
		
		topPoint += 300;
	}
	
	container.style.height = ( topPoint ) + "px";
}

function OnLoad(e)
{
	ShowHide('');
}

window.addEventListener("load", OnLoad, false);