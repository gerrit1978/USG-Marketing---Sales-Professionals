<?php
require_once('globals.inc');
require_once('functions.inc');

// Stap 0: Connect DB
$db = mysql_connect(DB_SERVER, DB_USER, DB_PASSWORD) or die('Kan niet connecteren');
mysql_select_db(DB_DB, $db) or die('Kan database niet selecteren');


$jobs_from_rss = array();

/*
 * Stap 0: RSS feed COMPLEET ophalen en in array opslaan
 */
$incoming_compleet = file_get_contents(RSS_JOBS_COMPLEET);

$xml = simplexml_load_string($incoming_compleet);

foreach ($xml->channel->item as $item) {
	$jobs_from_rss[(string)$item->guid] = array(
	  'guid' => (string)$item->guid,
	  'link' => utf8_decode((string)$item->link),
	  'author' => utf8_decode((string)$item->author),
	  'category' => utf8_decode((string)$item->functiongroupname),
	  'regio' => utf8_decode((string)$item->regionname),
	  'city' => utf8_decode((string)$item->city),
	  'title' => utf8_decode((string)$item->title),
	  'function' => str_replace('<BR><BR>', '<BR>', utf8_decode((string)$item->orderdescfunction)),
//	  'function' => utf8_decode((string)$item->orderdescfunction),	  
	  'profile' => utf8_decode((string)$item->orderdescprofile),	  
	  'account' => utf8_decode((string)$item->orderdescaccount),	  
	  'offer' => utf8_decode((string)$item->orderdescoffer),	  
	  'pubDate' => (string)$item->pubDate,
	  'applyLink' => 'http://www.usgfinancialforces.be/default.aspx?tabId=566&referenceid=' . (string)$item->guid,
	);
	
}


ksort($jobs_from_rss);

// put guids in separate array for "gemak"
$jobs_from_rss_guids = array();




foreach ($jobs_from_rss as $guid => $job) {
  $jobs_from_rss_guids[] = $guid;
}



/*
 * Stap 2: Database Wordpress posts ophalen en in array opslaan
 */
$query = "SELECT * FROM " . DB_TABLE;
$result = mysql_query($query, $db);

$jobs_from_db = array();
while ($array = mysql_fetch_array($result)) {
  $jobs_from_db[$array['rss_id']] = array(
    'rss_id' => $array['rss_id'],
    'rss_updated' => $array['rss_updated'],
    'wp_id' => $array['wp_id'],
    'wp_updated' => $array['wp_updated'],
  );
}

// put guids in separate array for "gemak"
$jobs_from_db_guids = array();
foreach ($jobs_from_db as $job) {
  $jobs_from_db_guids[] = $job['rss_id'];
}


/*
 * Stap 3: Nieuwe posts toevoegen = Jobs die nog NIET in db zitten maar wel in RSS FEED = ARRAY_JOBS_IN_RSS - ARRAY_JOBS_IN_DB
 */
$new_guids = array_diff($jobs_from_rss_guids, $jobs_from_db_guids);
foreach ($new_guids as $guid) {

  $job = $jobs_from_rss[$guid];
  
	// 1. hier content posten naar wordpress - returns PID
	$title = $job['title'];
	$link = $job['link'];
	
	$description = "";
  $function = $job['function'];
  $profile = $job['profile'];
  $account = $job['account'];
  $offer = $job['offer'];
  $applyLink = $job['applyLink'];

  if ($applyLink) {
		$prefix = "<div style='margin-bottom: 5px;'><a href='" . $applyLink . "' target='_blank' style='background: black; color: white; padding: 4px; text-decoration: none;'>Postulez maintenant!</a></div>";
		$description .= $prefix;
  }

  if (!empty($function)) {
    if (strlen($function) > 275) {
			$description .= trim(substr($function, 0, 200)) . "...<!--more Plus d'info-->" . trim(substr($function, 201, strlen($function)));
    } else {
      $description = trim($function) . "<!--more Plus d'info-->";
    }
  }

  if (!empty($profile)) {
    $description .= "<h2>Profile</h2>" . $profile;
  }

  if (!empty($account)) {
    $description .= "<h2>Account</h2>" .$account;
  }

  if (!empty($offer)) {
    $description .= "<h2>Offre</h2>" . $offer;
  }
	
	$categories = $job['category'];
	
	// Aanpassen: gebruik de juiste regio uit de RSS-feed
	isset($job['regio']) ? $tags = $job['regio'] : $tags = "Undefined";

	$toPublish = TRUE;

/*
  if ($link) {
		$suffix = "<p style='font-size: 20px;'><strong><a href='" . $link . "'>Apply now!</a></strong></p>";
		$description = $description . $suffix;
  }
*/
  $pid = addPost(WP_BLOGID, WP_USERNAME, WP_PASSWORD, $title, $description, $categories, $tags, $toPublish);
  	
	// 2. hier nieuwe posts updaten in database
	$query = "INSERT INTO " . DB_TABLE . " (rss_id, rss_updated, wp_id, wp_updated) VALUES ('" . $guid . "', '" . $job['pubDate'] . "', '" . $pid . "', '" . time() . "');";
	$result = mysql_query($query, $db) or die('Kan query niet uitvoeren');

}


/*
 * Stap 4: Oude posts verwijderen = Jobs die WEL in db zitten maar NIET MEER in RSS FEED = ARRAY_JOBS_IN_DB - ARRAY_JOBS_IN_RSS
 */
$old_guids_to_remove = array_diff($jobs_from_db_guids, $jobs_from_rss_guids);

foreach ($old_guids_to_remove as $guid) {
  
  $job = $jobs_from_db[$guid];
  $wp_id = $job['wp_id'];
 
  // 1. hier content verwijderen uit wordpress
	blogger_deletePost(WP_BLOGID, WP_USERNAME, WP_PASSWORD, $wp_id);

  
  // 2. hier post verwijderen uit database
  $query = "DELETE FROM " . DB_TABLE . " WHERE rss_id = '" . $guid . "';";
  $result = mysql_query($query, $db) or die('Kan query niet uitvoeren');
  
}
