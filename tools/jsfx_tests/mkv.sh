#!/bin/sh
# $1 = source jsfx, $2 = output test copy (2-arg slider_automate -> 1-arg)
sed -E 's/slider_automate\((slider[0-9]+), [01]\)/slider_automate(\1)/g' "$1" > "$2"
