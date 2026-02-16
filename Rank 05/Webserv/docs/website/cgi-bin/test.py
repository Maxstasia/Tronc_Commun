import os
import sys

print("Status: 200 OK")
print("Content-Type: text/html")
print("")
print("<html><head><title>CGI Test</title></head><body>")
print("<h1>CGI Test - Success!</h1>")
print("<h2>Environment Variables:</h2>")
print("<table border='1'>")

cgi_vars = [
    "REQUEST_METHOD", "QUERY_STRING", "CONTENT_TYPE", "CONTENT_LENGTH",
    "SCRIPT_NAME", "PATH_INFO", "SERVER_NAME", "SERVER_PORT",
    "SERVER_PROTOCOL", "GATEWAY_INTERFACE", "HTTP_HOST", "HTTP_USER_AGENT"
]

for var in cgi_vars:
    val = os.environ.get(var, "<not set>")
    print("<tr><td><b>{}</b></td><td>{}</td></tr>".format(var, val))

print("</table>")

if os.environ.get("REQUEST_METHOD") == "POST":
    body = sys.stdin.read()
    print("<h2>POST Body:</h2>")
    print("<pre>{}</pre>".format(body))

print("</body></html>")
