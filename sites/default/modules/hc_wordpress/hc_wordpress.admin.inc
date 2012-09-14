<?php



/**
 * Admin Settings Form
 */
function hc_wordpress_admin_form($form, &$form_state) {
  $form = array();
  $form['hc_wordpress_url_xml'] = array(
    '#type' => 'textfield',
    '#title' => 'URL van de XML-feed met de jobs',
    '#default_value' => variable_get('hc_wordpress_url_xml', ''),
  );
  
  $form['hc_wordpress_wordpress_url'] = array(
    '#type' => 'textfield',
    '#title' => 'XML-RPC URL van de Wordpress-blog',
    '#description' => 'Bijv. http://myblog.wordpress.com/xmlrpc.php',
    '#default_value' => variable_get('hc_wordpress_wordpress_url', ''),
  );

  $form['hc_wordpress_wordpress_user'] = array(
    '#type' => 'textfield',
    '#title' => 'Gebruikersnaam van de Wordpress-blog',
    '#default_value' => variable_get('hc_wordpress_wordpress_user', ''),
  );

  $form['hc_wordpress_wordpress_pass'] = array(
    '#type' => 'textfield',
    '#title' => 'Wachtwoord van de Wordpress-blog',
    '#default_value' => variable_get('hc_wordpress_wordpress_pass', ''),
  );
  
  return system_settings_form($form);
}