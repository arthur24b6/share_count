<?php

/**
 * @file
 * Views integration and data for the Share count module.
 */

/**
 * Implements hook_views_data().
 */
function share_count_views_data() {
  // Basic table information.
  $data['share_count']['table']['group'] = t('Share counts');

  // Advertise this table as a possible base table
  $data['share_count']['table']['base'] = array(
    'field' => 'sid',
    'title' => t('Share counts'),
    'help' => t('Listings of Share counts.'),
    'weight' => 10,
  );

  // Add joins for all other entity types.
  $entity_tables = array();
  foreach (entity_get_info() as $entity_type => $entity_info) {
    if ($entity_type == 'share_count' || empty($entity_info['base table']) || empty($entity_info['entity keys']['id'])) {
      continue;
    }

    $data['share_count']['table']['join'][$entity_info['base table']] = array(
      'type' => 'INNER',
      'left_field' => $entity_info['entity keys']['id'],
      'field' => 'entity_id',
    );

    $entity_tables[$entity_info['base table']] = $entity_type;
  }

  // {share_count}.sid
  $data['share_count']['sid'] = array(
    'title' => t('Share id'),
    'help' => t('The internal ID of the share counter.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // {share_count}.count
  $data['share_count']['count'] = array(
    'title' => t('Count'),
    'help' => t('The actual count of the share counter.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // {share_count}.updated
  $data['share_count']['updated'] = array(
    'title' => t('Last updated'),
    'help' => t('The last date/time the Share count was updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}
