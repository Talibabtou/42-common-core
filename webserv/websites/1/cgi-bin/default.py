#!/usr/bin/env python
import os, sys

message = ""
output_file = sys.argv[1] + "tmp.html"
content_length = int(os.environ.get('CONTENT_LENGTH', 0))
post_data = sys.stdin.read(content_length)

message = "<p>{}</p>".format(post_data)
try:
	if os.path.exists(sys.argv[1]):
		with open(output_file, 'w') as html_file:
					html_file.write(f"""
			<!DOCTYPE html>
			<html lang="en">
			<head>
				<meta charset="UTF-8">
				<meta name="viewport" content="width=device-width, initial-scale=1.0">
				<title>Default CGI</title>
			</head>
			<body>
				<p>{message}</p>
			</body>
			</html>
			""")
except Exception as e:
	exit(6)
exit(0)
