<?php

error_reporting(0);
//error_reporting(E_ALL);
//ini_set('display_errors', 1);
//ini_set('display_startup_errors', 1);

require("login.php");

ob_start("ob_gzhandler");

header('Content-Type: text/json; charset=utf-8');
header("Cache-Control: no-cache"); //http://support.microsoft.com/kb/234067
header("Expires: -1");

if (isset($_POST['rese']))
{
    $conn = connect($re);
	$s = array();
	$data = json_decode($_POST['rese']);
	for ($i = 0; $i < count($data->r); $i++)
	{
		$s[] = $conn->real_escape_string($data->r[$i]);
	}
	$str = '"' . implode('","', $s ) . '"';


	$query = sprintf("INSERT INTO synopsisresults VALUES (NULL,'name',%s,NULL,'%s','%s');", $str, $_SERVER['REMOTE_ADDR'], $_SERVER['HTTP_USER_AGENT']);
	echo $query;
    if ( $conn->query($query) === TRUE)
    {
    	echo "{'success':true,'affectedrows':" . $conn->affected_rows . "}";
    }
    else
    {
    	echo "{'success':false,'affectedrows':0,'query1':" . $query . "}";
    }
}
else
{
	echo "{'success':false,'affectedrows':0,'query2':" . $query . "}";
}

/*
CREATE TABLE `synopsisresults` (
 `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
 `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `pp` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f1` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f2` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f3` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f4` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f5` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f6` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f7` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f8` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f9` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f10` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f11` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f12` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f13` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f14` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f15` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f16` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f17` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f18` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f19` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f20` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f21` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f22` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f23` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f24` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f25` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f26` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f27` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f28` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f29` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f30` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f31` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f32` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f33` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f34` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f35` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f36` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f37` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f38` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f39` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f40` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f41` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f42` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f43` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f44` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f45` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f46` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f47` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f48` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f49` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f50` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f51` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f52` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f53` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f54` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f55` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f56` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f57` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f58` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f59` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `f60` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `updated` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
 `ip` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 `ua` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
 PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci
*/
?>
