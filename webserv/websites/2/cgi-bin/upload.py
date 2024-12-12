#!/usr/bin/python3

import cgi, os, html, sys, time

def render_template(template_path, replacements):
	try:
		with open(template_path, 'r') as f:
			template = f.read()
			for key, value in replacements.items():
				template = template.replace('{{' + key + '}}', str(value))
			return template
	except Exception as e:
		return f"""
		<!DOCTYPE html>
		<html lang="en">
		<head>
			<meta charset="UTF-8">
			<meta name="viewport" content="width=device-width, initial-scale=1.0">
			<title>Upload Result</title>
		</head>
		<body>
			<p>{replacements.get('message', '')}</p>
		</body>
		</html>
		"""

try:
	message = ""
	output_file = sys.argv[1] + "tmp.html"
	upload_path = sys.argv[1] + "../assets/uploads/"

	os.environ['REQUEST_METHOD'] = 'POST'
	if 'CONTENT_TYPE' in os.environ:
		os.environ['CONTENT_TYPE'] = os.environ['CONTENT_TYPE']
	if 'CONTENT_LENGTH' in os.environ:
		os.environ['CONTENT_LENGTH'] = os.environ['CONTENT_LENGTH']

	form = cgi.FieldStorage(keep_blank_values=True)
	file_item = form['filename'] if 'filename' in form else None

	if not os.path.exists(upload_path):
		os.makedirs(upload_path)
	stat = os.statvfs(upload_path)
	available_space = stat.f_frsize * stat.f_bavail

	if 'filename' not in form:
		message = "No file was uploaded!"
	else:
		file_item = form['filename']
		if not file_item.filename:
			message = "No file was uploaded!"
		else:
			boundary_prefix = b'------WebKitFormBoundary'
			file_name = os.path.basename(file_item.filename)
			file_path = os.path.join(upload_path, file_name)
			try:
				with open(file_path, 'wb') as f:
					buffer = []
					for line in file_item.file:
						if line.startswith(boundary_prefix):
							break
						buffer.append(line)
					while buffer and buffer[-1].strip() == b'':
						buffer.pop()
					for line in buffer:
						f.write(line)
				if os.path.getsize(file_path) == 0:
					message = f"File {file_name} was corrupted during upload!"
					os.remove(file_path)
				else:
					message = f"File {file_name} has been uploaded!"
			except Exception as e:
				message = f"Error saving file: {str(e)}"

	message = html.escape(message)
	template_path = sys.argv[1] + "../templates/upload_success.html"
	replacements = {'message': message}

	if os.path.exists(sys.argv[1]):
		with open(output_file, 'w') as html_file:
			html_content = render_template(template_path, replacements)
			html_file.write(html_content)

except Exception as e:
	exit(100)
exit(0)
