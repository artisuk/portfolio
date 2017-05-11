---
layout: 		post
status:			"shown"
title:  		"Boss Fighter"
date:   		2017-03-30 12:00:00 +0000
category: 		"game uni released"
thumbnail:		"assets/posts/bossfighter/preview.png"
---

<style>
	#slider {
	  position: relative;
	  overflow: hidden;
	  margin: 20px auto 0 auto;
	  border-radius: 4px;
	}

	#slider ul {
	  position: relative;
	  margin: 0;
	  padding: 0;
	  height: 200px;
	  list-style: none;
	}

	#slider ul li {
	  position: relative;
	  display: block;
	  float: left;
	  margin: 0;
	  padding: 0;
	  width: 500px;
	  height: 300px;
	  background: #ccc;
	  text-align: center;
	  line-height: 300px;
	}

	a.control_prev, a.control_next {
	  position: absolute;
	  top: 40%;
	  z-index: 999;
	  display: block;
	  padding: 4% 3%;
	  width: auto;
	  height: auto;
	  background: #2a2a2a;
	  color: #fff;
	  text-decoration: none;
	  font-weight: 600;
	  font-size: 18px;
	  opacity: 0.8;
	  cursor: pointer;
	}

	a.control_prev:hover, a.control_next:hover {
	  opacity: 1;
	  -webkit-transition: all 0.2s ease;
	}

	a.control_prev {
	  border-radius: 0 2px 2px 0;
	}

	a.control_next {
	  right: 0;
	  border-radius: 2px 0 0 2px;
	}

	.slider_option {
	  position: relative;
	  margin: 10px auto;
	  width: 160px;
	  font-size: 18px;
	}
</style>

<script src="/js/jquery.min.js"></script>

<script>
	jQuery(document).ready(function($) {
	  $("#checkbox").change(function() {
		setInterval(function() {
		  moveRight();
		}, 3000);
	  });

	  var slideCount = $("#slider ul li").length;
	  var slideWidth = $("#slider ul li").width();
	  var slideHeight = $("#slider ul li").height();
	  var sliderUlWidth = slideCount * slideWidth;

	  $("#slider").css({ width: slideWidth, height: slideHeight });

	  $("#slider ul").css({ width: sliderUlWidth, marginLeft: -slideWidth });

	  $("#slider ul li:last-child").prependTo("#slider ul");

	  function moveLeft() {
		$("#slider ul").animate(
		  {
			left: +slideWidth
		  },
		  200,
		  function() {
			$("#slider ul li:last-child").prependTo("#slider ul");
			$("#slider ul").css("left", "");
		  }
		);
	  }

	  function moveRight() {
		$("#slider ul").animate(
		  {
			left: -slideWidth
		  },
		  200,
		  function() {
			$("#slider ul li:first-child").appendTo("#slider ul");
			$("#slider ul").css("left", "");
		  }
		);
	  }

	  $("a.control_prev").click(function() {
		moveLeft();
	  });

	  $("a.control_next").click(function() {
		moveRight();
	  });
	});
</script>

<div id="slider">
  <a href="#" class="control_next"></a>
  <a href="#" class="control_prev"></a>
  <ul>
    <li>
		<img src="/assets/posts/bossfighter/screenshots/pic1.png" alt="Screenshot" style="width:100%; height:auto;"/>
	</li>                                                                                        
    <li>                                                                                         
		<img src="/assets/posts/bossfighter/screenshots/pic2.png" alt="Screenshot" style="width:100%; height:auto;"/>
	</li>                                                                                        
    <li>                                                                                         
		<img src="/assets/posts/bossfighter/screenshots/pic3.png" alt="Screenshot" style="width:100%; height:auto;"/>
	</li>                                                                                        
    <li>                                                                                         
		<img src="/assets/posts/bossfighter/screenshots/pic4.png" alt="Screenshot" style="width:100%; height:auto;"/>
	</li>
  </ul>  
</div>


This is the Boss Fighter page.
