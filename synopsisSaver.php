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

?>
