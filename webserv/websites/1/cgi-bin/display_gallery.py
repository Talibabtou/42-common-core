#!/usr/bin/python3

import os, sys

try:
	upload_path = sys.argv[1] + "../assets/uploads/"

	if not os.path.exists(upload_path):
		exit(4)
	if not os.access(upload_path, os.R_OK):
		exit(3)
	
	gallery_html = '''
		<!DOCTYPE html>
		<html lang="en">
		<head>
			<meta charset="UTF-8">
			<meta name="viewport" content="width=device-width, initial-scale=1.0">
			<meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate">
			<meta http-equiv="Pragma" content="no-cache">
			<meta http-equiv="Expires" content="0">
			<meta http-equiv="Connection" content="close">
			<link href="../assets/css/style.css" rel="stylesheet" type="text/css">
			<link href="../assets/css/upload.css" rel="stylesheet" type="text/css">
		</head>
		<body>
		<div class="image-gallery">
	'''

	for file in os.listdir(upload_path):
		file_ext = os.path.splitext(file)[1].lower()
		if file_ext in ('.png', '.jpg', '.jpeg', '.gif', '.webp'):
			gallery_html += f'''
				<div class="gallery-item">
					<img src="../assets/uploads/{file}" alt="{file}">
					<a href="/cgi-bin/delete.sh?filename={file}" class="trash-icon"></a>
					<div class="file-name">{file}</div>
				</div>'''
		else:
			icon_class = {
				'.txt': 'text-file',
				'.mp3': 'audio-file',
				'.pdf': 'pdf-file'
			}.get(file_ext, 'generic-file')
			
			gallery_html += f'''
				<div class="gallery-item">
					<div class="file-icon {icon_class}"></div>
					<a href="/cgi-bin/delete.sh?filename={file}" class="trash-icon"></a>
					<div class="file-name">{file}</div>
				</div>'''
	gallery_html += '</div></body></html>'

	output_file = sys.argv[1] + "tmp.html"
	with open(output_file, 'w') as html_file:
		html_file.write(gallery_html)
except Exception as e:
	exit(100)
exit(0)
