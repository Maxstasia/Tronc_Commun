<?php

echo "<html><head><title>PHP CGI Test</title>";
echo "<style>body{font-family:Arial,sans-serif;background:#0f0f1a;color:#e0e0e0;padding:40px;}";
echo "h1{color:#e94560;}h2{color:#00b894;margin-top:20px;}";
echo "table{border-collapse:collapse;margin:10px 0;}";
echo "td,th{border:1px solid #2a2a4a;padding:8px 12px;text-align:left;}";
echo "th{background:#1a1a2e;color:#e94560;}td{background:#1a1a2e;}";
echo "pre{background:#1a1a2e;padding:15px;border-radius:8px;overflow-x:auto;}";
echo ".badge{display:inline-block;padding:4px 12px;border-radius:12px;font-weight:bold;}";
echo ".badge-get{background:#0984e333;color:#0984e3;}";
echo ".badge-post{background:#00b89433;color:#00b894;}</style></head><body>";

echo "<h1>PHP CGI Test - Success!</h1>";
$method = getenv('REQUEST_METHOD');
$badge = ($method === 'POST') ? 'badge-post' : 'badge-get';
echo "<p>Method: <span class='badge $badge'>$method</span></p>";

if ($method === 'POST' && !empty($_POST)) {
	echo "<h2>\$_POST Data:</h2><table><tr><th>Key</th><th>Value</th></tr>";
	foreach ($_POST as $key => $val) {
		echo "<tr><td><b>" . htmlspecialchars($key) . "</b></td>";
		echo "<td>" . htmlspecialchars($val) . "</td></tr>";
	}
	echo "</table>";
}

if ($method === 'POST') {
	$raw = file_get_contents("php://input");
	if (!empty($raw)) {
		echo "<h2>Raw POST Body:</h2>";
		echo "<pre>" . htmlspecialchars($raw) . "</pre>";
	}
}


$qs = getenv('QUERY_STRING');
if (!empty($qs)) {
	echo "<h2>Query String:</h2><pre>" . htmlspecialchars($qs) . "</pre>";
	parse_str($qs, $params);
	echo "<table><tr><th>Key</th><th>Value</th></tr>";
	foreach ($params as $k => $v) {
		echo "<tr><td><b>" . htmlspecialchars($k) . "</b></td>";
		echo "<td>" . htmlspecialchars($v) . "</td></tr>";
	}
	echo "</table>";
}

echo "<h2>CGI Environment:</h2><table><tr><th>Variable</th><th>Value</th></tr>";
$vars = array("REQUEST_METHOD", "QUERY_STRING", "CONTENT_TYPE", "CONTENT_LENGTH",
	"SCRIPT_NAME", "PATH_INFO", "SERVER_NAME", "SERVER_PORT",
	"SERVER_PROTOCOL", "GATEWAY_INTERFACE", "HTTP_HOST", "HTTP_USER_AGENT");
foreach ($vars as $v) {
	$val = getenv($v);
	echo "<tr><td><b>$v</b></td><td>" . htmlspecialchars($val ? $val : "(not set)") . "</td></tr>";
}
sleep(4);
echo "</table></body></html>";
?>
