jQuery(document).ready(function($) {

	// placeholder search form
	$('#search-block-form .form-text').attr('placeholder', 'Site doorzoeken');

	// default link animations
	$('#columns a').not('.large-btn').hover(function() { 
		$(this).animate({borderBottomColor: '#344e56'}, 100)
	}, function() {
		$(this).animate({borderBottomColor: '#ccd3d5'}, 100)
	});
	
	// animate buttons bg color
	$('#columns a.large-btn, #columns a.small-btn, .node-type-job .block-webform .form-submit').hover(function() {
	  $(this).animate({
	    backgroundColor: '#344e56'
	  }, 100)
	}, function() {
	  $(this).animate({
	    backgroundColor: '#677a80'
	  }, 100)
	});
	
	// animate links color
	$('.brown a').hover(function() {
	  $(this).animate({
	    borderBottomColor: '#cdb886',
	    color: '#cdb886'
	  }, 200)
	}, function() {
	  $(this).animate({
	    borderBottomColor: '#e7dcc3',
	    color: '#e7dcc3'
	  }, 200)
	});
	
  // animate prefooter links color
  $('#tertiary-content-wrapper  a').hover(function() {
		$(this).animate({borderBottomColor: '#e7dcc3'}, 150);
  }, function() {
		$(this).animate({borderBottomColor: '#a07511'}, 150);  
  });
 
  // carrousel
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
	
	// scroll to top
	$('a#scrollTop').click(function(e) {
	  e.preventDefault();
    $('html, body').animate({scrollTop:0}, 'slow', 'easeInOutExpo');		
	});

});