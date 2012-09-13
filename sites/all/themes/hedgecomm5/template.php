<?php

/**
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function and instance of "hedgecomm5" to match
 *    your subthemes name, e.g. if you name your theme "footheme" then the function
 *    name will be "footheme_preprocess_hook". Tip - you can search/replace
 *    on "hedgecomm5".
 * 2. Uncomment the required function to use.
 */

/**
 * Override or insert variables into the html templates.
 */
function hedgecomm5_preprocess_html(&$vars) {
  // Load the media queries styles
  // Remember to rename these files to match the names used here - they are
  // in the CSS directory of your subtheme.
  $media_queries_css = array(
    'hedgecomm5.responsive.style.css',
    'hedgecomm5.responsive.gpanels.css'
  );
  load_subtheme_media_queries($media_queries_css, 'hedgecomm5');

 /**
  * Load IE specific stylesheets
  * AT automates adding IE stylesheets, simply add to the array using
  * the conditional comment as the key and the stylesheet name as the value.
  *
  * See our online help: http://adaptivethemes.com/documentation/working-with-internet-explorer
  *
  * For example to add a stylesheet for IE8 only use:
  *
  *  'IE 8' => 'ie-8.css',
  *
  * Your IE CSS file must be in the /css/ directory in your subtheme.
  */
  /* -- Delete this line to add a conditional stylesheet for IE 7 or less.
  $ie_files = array(
    'lte IE 7' => 'ie-lte-7.css',
  );
  load_subtheme_ie_styles($ie_files, 'hedgecomm5');
  // */
}

/* -- Delete this line if you want to use this function
function hedgecomm5_process_html(&$vars) {
}
// */

/**
 * Override or insert variables into the page templates.
 */
function hedgecomm5_preprocess_page(&$vars) {
}

function hedgecomm5_process_page(&$vars) {
	
	// prepare main menu for footer (tertiary content region) - we split menu in two (two columns)
	$menu_name = variable_get('menu_main_links_source', 'main-menu');
  $tree = menu_tree($menu_name);
  $tree_new = array();
  $tree_left = array();
  $tree_right = array();
  $number_of_links = 0;
	foreach ($tree as $id => $leaf) {
		if (is_numeric($id) && isset($leaf['#title'])) {
		  $tree_new[] = array('id' => $id, 'leaf' => $leaf);
		  $number_of_links++;
		}
	}

	$number_of_links_left = ceil($number_of_links / 2);
	
	for ($i = 0; $i < $number_of_links_left; $i++) {
	  $id = $tree_new[$i]['id'];
	  $leaf = $tree_new[$i]['leaf'];
	  $tree_left[$id] = $leaf;
	}
	
	for ($i = $number_of_links_left; $i < $number_of_links; $i++) {
	  $id = $tree_new[$i]['id'];
	  $leaf = $tree_new[$i]['leaf'];
	  $tree_right[$id] = $leaf;
	}

	
  $vars['main_menu_tree_footer_left'] = $tree_left;
  $vars['main_menu_tree_footer_right'] = $tree_right;
}
// */

/**
 * Override or insert variables into the node templates.
 */

function hedgecomm5_preprocess_node(&$vars) {
  
  // preprocess arbeidsduur - dienstverband - uur_per_week
  if ($vars['type'] == 'job') {

		// arbeidsduur
    $output = array();
    if (isset($vars['field_dienstverband'][0]['value'])) {
      $output[] = $vars['field_dienstverband'][0]['value'];
    }
    if (isset($vars['field_job_arbeidsduur'][0]['value'])) {
      $output[] = $vars['field_job_arbeidsduur'][0]['value'];
    }
    if (isset($vars['field_uur_per_week'][0]['value'])) {
      $output[] = $vars['field_uur_per_week'][0]['value'] . t('u per week');
    }
    
    $arbeid = implode(' <span>/</span> ', $output);
    $vars['content']['job_arbeid'] = "<div class='arbeid'>$arbeid</div>";
    
    // functie - branche
    $output = array();
    if (isset($vars['field_functie'][0]['value'])) {
      $output[] = $vars['field_functie'][0]['value'];
    }
    if (isset($vars['field_branche'][0]['value'])) {
      $output[] = $vars['field_branche'][0]['value'];
    }
    
    $functie_branche = implode(' <span>/</span> ', $output);
    $vars['content']['job_functie_branche'] = "<div class='functie-branche'>$functie_branche</div>";
  }

}

function hedgecomm5_process_node(&$vars) {
}
// */

/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function hedgecomm5_preprocess_comment(&$vars) {
}

function hedgecomm5_process_comment(&$vars) {
}
// */

/**
 * Override or insert variables into the block templates.
 */
/* -- Delete this line if you want to use these functions
function hedgecomm5_preprocess_block(&$vars) {
}

function hedgecomm5_process_block(&$vars) {
}
// */

/**
 * Add the Style Schemes if enabled.
 * NOTE: You MUST make changes in your subthemes theme-settings.php file
 * also to enable Style Schemes.
 */
/* -- Delete this line if you want to enable style schemes.
// DONT TOUCH THIS STUFF...
function get_at_styles() {
  $scheme = theme_get_setting('style_schemes');
  if (!$scheme) {
    $scheme = 'style-default.css';
  }
  if (isset($_COOKIE["atstyles"])) {
    $scheme = $_COOKIE["atstyles"];
  }
  return $scheme;
}
if (theme_get_setting('style_enable_schemes') == 'on') {
  $style = get_at_styles();
  if ($style != 'none') {
    drupal_add_css(path_to_theme() . '/css/schemes/' . $style, array(
      'group' => CSS_THEME,
      'preprocess' => TRUE,
      )
    );
  }
}
// */


function hedgecomm5_site_map_box($variables) {

	$content = $variables['content'];
  $attributes = $variables['attributes'];

  $output = '';
  if (!empty($title) || !empty($content)) {
    $output .= '<div' . drupal_attributes($attributes) . '>';
    if (!empty($content)) {
      $output .= '<div class="content">' . $content . '</div>';
    }
    $output .= '</div>';
  }

  return $output;
}
