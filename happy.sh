rm -f happy.cpp
for file in "$@"; do
	lines=$(grep -n -m 2 '/\* -/- *.* -/- \*/' $file | sed 's/\([0-9]*\).*/\1/' | tr '\n' ',' | sed 's/.$/p/')
	if [ ! -z "$lines" ]; then
		sed -n $lines $file >> happy.cpp
	fi
done