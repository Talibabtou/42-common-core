#! /bin/bash

if [[ "$#" -gt 3 ]]; then
	echo "error: too many argument"
	exit 100
elif [[ "$#" -lt 2 ]]; then
	echo "error: not enough argument"
	exit 100
else
	if [ -z "$3" ]; then
		echo "empty argument"
		exit 4
	elif [[ "$3" == "/" || "$3" == "." || "$3" == ".." ]]; then
		echo "error: invalid or dangerous path"
		exit 3
	fi
	full_path="./$1../assets/uploads/$3"
	if [ -e "$full_path" ]; then
		if rm -f "$full_path"; then
			echo "$3 has been deleted"
			exit 0
		else
			echo "error: $3 can not be deleted"
			exit 3
		fi
	else
		echo "error: $3 does not exist"
			exit 4
	fi
fi
