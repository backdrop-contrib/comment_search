<?php
/**
 * @file
 * Theme functions for the Comment Search module.
 */

/**
 * Returns HTML for the comment search rankings form.
 *
 * Renders the Comment rankings table matching core's Content rankings style,
 * with Factor and Influence columns and a select element per row.
 *
 * @param array $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_comment_search_admin($variables) {
  $form = $variables['form'];
  $output = '';

  if (isset($form['#help'])) {
    $output .= '<p><em>' . $form['#help'] . '</em></p>';
  }

  $header = array(
    t('Factor'),
    t('Influence'),
  );
  $rows = array();

  foreach (element_children($form['factors']) as $key) {
    $title = $form['factors'][$key]['#title'];
    // Unset title before rendering to prevent it appearing above the select.
    unset($form['factors'][$key]['#title']);
    $rows[] = array(
      $title,
      backdrop_render($form['factors'][$key]),
    );
  }

  $output .= theme('table', array(
    'header' => $header,
    'rows'   => $rows,
    'attributes' => array('class' => array('sticky-enabled')),
  ));

  $output .= backdrop_render_children($form);

  return $output;
}
