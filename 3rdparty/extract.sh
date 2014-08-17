#!/bin/bash

function __extract_one()
{
	prog=$1;
	distfile=`ls -t distfiles/${prog}*|sort -rn| head -1`
	if [ "${distfile%\.bz2}" != "${distfile}" ] ; then
		cmd="tar -jxf"
	else
		cmd="tar -zxf"
	fi
		mkdir -p build/$prog
		cmd="$cmd $distfile -C build/$prog"
	$cmd
}

case "$1" in
	all)
		cat packages.list| while read prog
		do
			__extract_one $prog
		done
	;;
	*)
		__extract_one $1;
	;;
esac

