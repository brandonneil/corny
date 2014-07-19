<?php
/**
 * @file
 * Ctools content type plugin file for the corny module.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('DrupalCorn Camp Badge'),
  'description' => t('Renders a DrupalCorn Camp Badge based on camp data.'),
  'category' => t('DrupalCorn'),
  'edit form' => 'cornbadge_edit_form',
  'render callback' => 'cornbadge_render',
  'admin info' => 'cornbadge_admin_info',
  'defaults' => array(
    'year' => '2014',
    'type' => 'attendee',
  ),
);

/**
 * The 'admin info' callback for the content type.
 */
function cornbadge_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass();
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    $block->content = t(
      'Showing DrupalCorn Camp @year @type Badge.',
      array('@year' => $conf['year'], '@type' => $conf['type'])
    );
    return $block;
  }
}

/**
 * The 'Edit form' callback for the content type.
 */
function cornbadge_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['year'] = array(
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(t('2014'), t('2013'), t('2012'))),
    '#title' => t('Which DrupalCorn Camp?'),
    '#default_value' => $conf['year'],
  );
  $form['type'] = array(
    '#type' => 'select',
    '#options' => array(
      'attendee' => t('Attendee'),
      'individual_sponsor' => t('Individual Sponsor'),
      'sponsor' => t('Sponsor'),
    ),
    '#title' => t('Which badge would you like to display?'),
    '#default_value' => $conf['type'],
  );
  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function cornbadge_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * Run-time rendering of the body of the block (content type).
 *
 * See ctools_plugin_examples for more advanced info.
 */
function cornbadge_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = t('DrupalCorn Camp');

  // Build path to image.
  $path = drupal_get_path('module', 'corny') . '/assets/' . $conf['year'] . '/' . $conf['type'] . '.png';

  // Create image.
  $image = theme('image', array('path' => $path, 'alt' => 'DrupalCorn Camp Logo',));

  // Create block content.
  $block->content = array(
    // Build link.
    'link' => array(
      '#type' => 'link',
      '#title' => $image,
      '#href' => 'http://' . $conf['year'] . '.drupalcorn.org',
      '#options' => array('html' => TRUE),
    ),
  );
  return $block;
}
