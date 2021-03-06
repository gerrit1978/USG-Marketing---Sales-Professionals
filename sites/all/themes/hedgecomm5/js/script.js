jQuery(document).ready(function($) {

  // zijbalk op z'n plaats houden: http://www.profilepicture.co.uk/sticky-sidebar-jquery-plugin/
	$("body.node-type-job .region-sidebar-second").stickySidebar({speed: 800});


	// placeholder search form
	$('#search-block-form .form-text').attr('placeholder', 'Site doorzoeken');

	// default link animations
	$('#columns a').not('.large-btn').hover(function() { 
		$(this).animate({borderBottomColor: '#59802c'}, 100)
	}, function() {
		$(this).animate({borderBottomColor: '#59802c'}, 100)
	});
	
	// animate buttons bg color
	$('#columns a.large-btn, #columns a.small-btn, .node-type-job .block-webform .form-submit').hover(function() {
	  $(this).animate({
	    backgroundColor: '#59802c'
	  }, 100)
	}, function() {
	  $(this).animate({
	    backgroundColor: '#819c59'
	  }, 100)
	});
	
	// animate links color
	$('.green a').hover(function() {
	  $(this).animate({
	    borderBottomColor: '#819c59',
	    color: '#819c59'
	  }, 200)
	}, function() {
	  $(this).animate({
	    borderBottomColor: '#d1dbc4',
	    color: '#d1dbc4'
	  }, 200)
	});
	
  // animate prefooter links color
  $('#tertiary-content-wrapper  a').hover(function() {
		$(this).animate({
		  borderBottomColor: '#d2dbc3',
		  color: '#ffffff'
		}, 150);
  }, function() {
		$(this).animate({
		  borderBottomColor: '#59802c',
		  color: '#59802c'
		}, 150);  
  });
 
  // carrousel
  /* DEPRECATED 
	$('#block-views-carrousel-block .view-content ul').carouFredSel({
	  width: "auto",
	  items: 1,
	  scroll : {
	  	fx : 'crossfade'
	  },
	  auto : {
	    pauseDuration : 4500
	  },
	  pagination : '#carrousel-pagination',
	});
	
	*/
	
	// scroll to top
	$('a#scrollTop').click(function(e) {
	  e.preventDefault();
    $('html, body').animate({scrollTop:0}, 'slow', 'easeInOutExpo');		
	});

});