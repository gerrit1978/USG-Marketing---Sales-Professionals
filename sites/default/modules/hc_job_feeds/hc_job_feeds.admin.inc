<?php


function hc_jobs_feeds_admin_form($form, &$form_state) {

  $form['settings_nl']= array(
    '#type' => 'fieldset',
    '#title' => 'Nederlandstalig',
  );
  
  $form['settings_nl']['hc_feed_nl']= array(
    '#type' => 'textfield',
    '#title' => 'XML feed',
    '#default_value' => variable_get('hc_feed_nl', ''),
  );
  
  $form['settings_nl']['hc_user_nl'] = array(
    '#type' => 'textfield',
    '#title' => 'Gebruikersnaam',
    '#default_value' => variable_get('hc_user_nl', ''),
  );

  $form['settings_nl']['hc_pass_nl'] = array(
    '#type' => 'textfield',
    '#title' => 'Wachtwoord',
    '#default_value' => variable_get('hc_pass_nl', ''),
  );

  $form['settings_fr']= array(
    '#type' => 'fieldset',
    '#title' => 'Franstalig',
  );
  
  $form['settings_fr']['hc_feed_fr']= array(
    '#type' => 'textfield',
    '#title' => 'XML feed',
    '#default_value' => variable_get('hc_feed_fr', ''),
  );
  
  $form['settings_fr']['hc_user_fr'] = array(
    '#type' => 'textfield',
    '#title' => 'Gebruikersnaam',
    '#default_value' => variable_get('hc_user_fr', ''),
  );

  $form['settings_fr']['hc_pass_fr'] = array(
    '#type' => 'textfield',
    '#title' => 'Wachtwoord',
    '#default_value' => variable_get('hc_pass_fr', ''),
  );



  return system_settings_form($form);
}