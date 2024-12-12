#!/usr/bin/python3

import cgi, os, sys, hashlib, json
from http import cookies
import time

def set_cookie(username):
	cookie = cookies.SimpleCookie()
	cookie['username'] = username
	print(cookie.output())

def get_cookie():
	if 'HTTP_COOKIE' in os.environ:
		cookie = cookies.SimpleCookie(os.environ['HTTP_COOKIE'])
		if 'username' in cookie:
			return cookie['username'].value
	return None

def load_users():
	users_file = os.path.join(sys.argv[1], "users.json")
	if os.path.exists(users_file):
		with open(users_file, 'r') as f:
			return json.load(f)
	return {}

def save_users(users):
	users_file = os.path.join(sys.argv[1], "users.json")
	with open(users_file, 'w') as f:
		json.dump(users, f, indent=4)

def hash_password(password):
	return hashlib.sha256(password.encode()).hexdigest()

def render_template(template_path, replacements):
	with open(template_path, 'r') as f:
		template = f.read()
		for key, value in replacements.items():
			template = template.replace('{{' + key + '}}', value)
		return template

try:
	form = cgi.FieldStorage()
	users = load_users()
	message = ""
	output_file = sys.argv[1] + "tmp.html"
	
	username = form.getvalue('username')
	password = form.getvalue('password')
	action = form.getvalue('action')
	
	template_path = ""
	replacements = {}

	if action == 'logout':
		cookie = cookies.SimpleCookie()
		cookie['username'] = ''
		cookie['username']['expires'] = 'Thu, 01 Jan 1970 00:00:00 GMT'
		print(cookie.output())
		template_path = sys.argv[1] + "templates/logout_success.html"
	elif username and password:
		hashed_password = hash_password(password)
		if username in users:
			if users[username] == hashed_password:
				set_cookie(username)
				template_path = sys.argv[1] + "../templates/login_success.html"
				replacements = {'username': username}
			else:
				template_path = sys.argv[1] + "../templates/login_fail.html"
				replacements = {'username': username}
		else:
			users[username] = hashed_password
			save_users(users)
			set_cookie(username)
			template_path = sys.argv[1] + "../templates/login_success.html"
			replacements = {'username': username}
	else:
		stored_username = get_cookie()
		if stored_username and stored_username in users:
			template_path = sys.argv[1] + "../templates/login_success.html"
			replacements = {'username': stored_username}
		else:
			template_path = sys.argv[1] + "../templates/login_fail.html"

	if os.path.exists(sys.argv[1]):
		with open(output_file, 'w') as html_file:
			html_content = render_template(template_path, replacements)
			html_file.write(html_content)

except Exception as e:
	exit(6)
exit (0)
