<?php

/**
 * @file
 * Provides API information about share_count functionality.
 */

/**
 * Implements hook_share_count_provider().
 *
 * Define your provider, provider name, and callback function. This provider
 * will be shown as an option at: admin/config/services/share-services
 *
 * @return array()
 */
function hook_share_count_provider() {
  $items = array();
  $items['provider_machine_name'] = array(
    'title' => t('Human readable name'),
    'callback' => 'my_module_share_count_callback'
  );
  return $items;
}

/**
 * Call back to get a count of number of times this was shared.
 *
 * @param string $path
 *   This is a drupal page path- this will will be the alias rather than node/1
 *   if an alias exists for this entity.
 *
 * @return int
 *   Total count.
 */
function my_module_share_count_callback($path) {
  global $base_url;
  $count = 0;
  $url = 'http://PROVIDER.COM/?url=' . rawurlencode($base_url . '/' . $path);
  $json = _share_count_get_remote_counts($url);
  // Do something with the returned data
  foreach ($json->data as $share) {
    $count++;
  }
  return $count;
}