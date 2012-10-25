<?php
/**
 * @file modal_forms.pages.inc
 * Page callbacks for the modal_forms module.
 */

/*
 * A modal user login callback.
 */
function modal_forms_login($js = NULL) {
  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('user_login');
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'title' => t('Log in'),
    'ajax' => TRUE,
  );

  $output = ctools_modal_form_wrapper('user_login', $form_state);
  if (!empty($form_state['executed'])) {
    // We'll just overwrite the form output if it was successful.
    $output = array();
    ctools_add_js('ajax-responder');
    $output[] = ctools_modal_command_dismiss(t('Login Success'));
    if (isset($_GET['destination'])) {
      $output[] = ctools_ajax_command_redirect($_GET['destination']);
    }
    else {
      $output[] = ctools_ajax_command_reload();
    }
  }
  print ajax_render($output);
  exit;
}

/**
 * A modal user register callback.
 */
function modal_forms_register($js = NULL) {
  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('user_register_form');
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'title' => t('Create new account'),
    'ajax' => TRUE,
  );
  $output = ctools_modal_form_wrapper('user_register_form', $form_state);
  if (!empty($form_state['executed'])) {
    // We'll just overwrite the form output if it was successful.
    $output = array();
    ctools_add_js('ajax-responder');
    if (isset($_GET['destination'])) {
      $output[] = ctools_ajax_command_redirect($_GET['destination']);
    }
    else {
      $output[] = ctools_ajax_command_reload();
    }
  }
  print ajax_render($output);
  exit;
}

/**
 * A modal user password callback.
 */
function modal_forms_password($js = NULL) {
  module_load_include('inc', 'user', 'user.pages');

  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('user_pass');
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'title' => t('Request new password'),
    'ajax' => TRUE,
  );
  $output = ctools_modal_form_wrapper('user_pass', $form_state);
  if (!empty($form_state['executed'])) {
    // We'll just overwrite the form output if it was successful.
    $output = array();
    ctools_add_js('ajax-responder');
    if (isset($_GET['destination'])) {
      $output[] = ctools_ajax_command_redirect($_GET['destination']);
    }
    else {
      $output[] = ctools_ajax_command_reload();
    }
  }
  print ajax_render($output);
  exit;
}

/**
 * A modal contact callback.
 */
function modal_forms_contact($js = NULL) {
  module_load_include('inc', 'contact', 'contact.pages');

  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('contact_site_form');
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'title' => t('Contact'),
    'ajax' => TRUE,
  );
  $output = ctools_modal_form_wrapper('contact_site_form', $form_state);
  if (!empty($form_state['executed'])) {
    // We'll just overwrite the form output if it was successful.
    $output = array();
    ctools_add_js('ajax-responder');
    if (isset($_GET['destination'])) {
      $output[] = ctools_ajax_command_redirect($_GET['destination']);
    }
    else {
      $output[] = ctools_ajax_command_reload();
    }
  }
  print ajax_render($output);
  exit;
}

/**
 * Modal display of the node's webform.
 *
 * @param $node
 *   A node object.
 */
function modal_forms_view_webform($js = NULL, $node) {
  $output = array();

  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('webform_client_form_' . $node->nid, $node, FALSE);
  }
  ctools_include('modal');
  ctools_include('ajax');
  if (empty($node->webform['components'])) {
    // No webform or no components.
    $output[] = ctools_modal_command_display(t('Webform'), t('No webform found.'));
    print ajax_render($output);
    exit;
  }
  // Get webform defaults.
  $title = check_plain($node->title);
  $text = check_markup($node->webform['confirmation'], $node->webform['confirmation_format'], '', TRUE);
  $form_state = array(
    'title' => $title,
    'ajax' => TRUE,
  );
  // Prevent webform redirect.
  $GLOBALS['conf']['webform_blocks']['client-block-' . $node->nid]['pages_block'] = 1;
  $node->webform_block = TRUE;
  // Pass required parameters.
  $form_state['build_info']['args'] = array($node, FALSE);
  $output = ctools_modal_form_wrapper('webform_client_form_' . $node->nid, $form_state);

  if (!empty($form_state['executed'])) {
    if (!isset($form_state['storage'])) {
      ctools_add_js('ajax-responder');
      $output[] = ctools_modal_command_display($title, $text . ctools_ajax_text_button(t('Close'), 'modal_forms/nojs/dismiss', t('Close')));
      // @todo Add support for redirect. Require some magic.
      // Copied from webform_client_form_submit().
      // $redirect_url = trim($node->webform['redirect_url']);
      // $redirect_url = _webform_filter_values($redirect_url, $node, NULL, NULL, FALSE, TRUE);
      // $output[] = ctools_ajax_command_redirect($redirect_url);
    }
    else {
      // We are on a multistep form step.
      $form_state['executed'] = array();
      $output = ctools_modal_form_wrapper('webform_client_form_' . $node->nid, $form_state);
    }
  }
  print ajax_render($output);
  exit;
}

/**
 * Closes modal windows.
 */
function modal_forms_dismiss($js) {
  if (!$js) {
    return ;
  }
  ctools_include('modal');
  ctools_include('ajax');

  $commands = array(ctools_modal_command_dismiss());
  print ajax_render($commands);
}
