#!/bin/bash

SCRIPT_DIR=$(dirname "$0")
TEMPLATE_PATH="$SCRIPT_DIR/../templates/calculator_result.html"
OUTPUT_PATH="$SCRIPT_DIR/tmp.html"

STYLE_CSS_PATH="/assets/css/style.css"
CALCULATOR_CSS_PATH="/assets/css/calculator.css"

if [[ "$#" -eq 7 ]]; then
	if [ "$2" == "f_num" ] && [ "$4" == "oper" ] && [ "$6" == "s_num" ]; then
		F_NUM=$(echo "$3" | sed 's/^0*\([0-9]\)/\1/')
		OPER="$5"
		S_NUM=$(echo "$7" | sed 's/^0*\([0-9]\)/\1/')
		case "$OPER" in
			"+"|"-"|"*"|"/")
				;;
			*)
				echo "error: bad operator detected $OPER"
				exit 6
				;;
		esac
		if [[ "$F_NUM" =~ ^[-]?[0-9]*\.?[0-9]+$ ]] && [[ "$S_NUM" =~ ^[-]?[0-9]*\.?[0-9]+$ ]]; then
			if [ "$OPER" == "/" ] && [ "$S_NUM" == "0" ]; then
				RESULT="impossible"
			else
				RESULT=$(echo "$F_NUM $OPER $S_NUM" | bc)
			fi
			sed -e "s|{{RESULT}}|$F_NUM $OPER $S_NUM = $RESULT|" \
				-e "s|{{STYLE_CSS_PATH}}|$STYLE_CSS_PATH|" \
				-e "s|{{CALCULATOR_CSS_PATH}}|$CALCULATOR_CSS_PATH|" \
				"$TEMPLATE_PATH" > "$OUTPUT_PATH"
		else
			echo "error: not good numbers"
			exit 6
		fi
	else
		echo "error: bad argument"
		exit 6
	fi
else
	echo "error: bad number of arguments (expect: 7, actual: $#)"
	echo "main usage: ./calc.sh <path> f_num <num> oper <operator> s_num <num>"
	exit 6
fi
exit 0
