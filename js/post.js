
function StopAllExtraElements()
{
	var youtubeVideos = document.getElementsByClassName( "top-video-youtube" );
	var arrayLength = youtubeVideos.length;
	
	for( var i = 0; i < arrayLength; ++i ) 
	{
		//youtubeVideos[i].stopVideo();
		youtubeVideos[ i ].contentWindow.postMessage( '{"event":"command","func":"' + 'stopVideo' + '","args":""}', '*' );
	}
}

// shows the screenshot
function Show( id ) 
{
	var currentElement = document.getElementsByClassName( "top-preview-show" )[ 0 ];
	var allElements = document.getElementsByClassName( "top-preview" );
	
	currentElement.classList.remove( "top-preview-show" );
	allElements[ parseInt( id ) ].classList.add( "top-preview-show" );
	
	StopAllExtraElements();
}

// called by the preview buttons
// moves the preview bar
function MovePreview( move )
{
	var slideshows = document.getElementsByClassName( "bottom-thumb" );
	var arrayLength = slideshows.length;
	
	var mostLeft = parseFloat( slideshows[ 0 ].style.left );
	var mostRight = parseFloat( slideshows[ arrayLength - 1 ].style.left );
	
	var validMostLeft = Math.max( 0, arrayLength - 4 ) * -25;
	
	// moving right
	if( move > 0 &&  validMostLeft >= mostLeft )
	{
		return;
	}
	
	// moving left
	if( move < 0 && mostLeft >= 0 )
	{
		return;
	}
	
	for( var i = 0; i < arrayLength; ++i ) 
	{
		var left = parseFloat( slideshows[ i ].style.left );
		left = left - ( 25 * move );
		slideshows[ i ].style.left = ( left ).toString() + "%";
	}
}

// called by the main buttons
// switches the images from left to right
function ShowPreview( move )
{
	var currentElement = document.getElementsByClassName( "top-preview-show" )[ 0 ];
	var allElements = document.getElementsByClassName( "top-preview" );
	var arrayLength = allElements.length;
	
	var index = parseInt( currentElement.id );
	
	index += move;
	
	if( index < 0 )
	{
		index = arrayLength - 1;
	}
	
	if( index > arrayLength - 1 )
	{
		index = 0;
	}
	
	Show( parseInt( index ) );
}

function OnLoad(e)
{}

window.addEventListener("load", OnLoad, false);