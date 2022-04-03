#!/bin/bash

msgToPrint=""

printMsg()
{
	echo "**----------------------**"
	echo ""
	echo $msgToPrint
	echo ""
	echo "**----------------------**"
}

build()
{
	#Go to build directory
	mkdir -p build
	cd build

	msgToPrint="Generating make files..."
	printMsg

	cmake -DCMAKE_BUILD_TYPE=Debug ..

	msgToPrint="Building..."
	printMsg

	cmake --build . && cp -r ../resources/ ../bin/

	#Go back to previous directory once we finish
	cd ..
}

clean()
{
	if [ -d "./bin/" ]
	then
		rm -rf ./bin
	fi

	if [ -d "./build/" ]
	then
		rm -rf ./build
	fi
}

run()
{
	if [ -d "./bin/" ] && [ -f "./bin/colibriClient" ]
	then
		./bin/colibriClient
	fi
}

# Start script

case $1 in
	"")
		build
		;;
	build)
		build
		;;
	clean)
		clean
		;;
	run)
		run
		;;
esac
	
