#!/bin/bash

__rebuild_one()
{
	prog=$1;
	confirm_param=$2;

	echo "building: " $prog
	dir=`ls -dt build/${prog}/*|tail -1`
	echo cd $MEDIA_BUILD/$dir
	cd $MEDIA_BUILD/$dir
	cat $MEDIA_BUILD/specs/$prog.spec | while read i
	do
		echo -n "+"
		echo $i
	done
	source $MEDIA_BUILD/specs/$prog.spec && make -j 4
	echo "comfirm install? (y/n)"
	
	if [ "$confirm_param" == "yes" ]; then
		yes="y"
	else
		read yes
	fi

	if [ "$yes" == "y" ]; then
		sudo make install
	fi

	if [ -f $MEDIA_BUILD/specs/$prog.postinstall ]; then
		source $MEDIA_BUILD/specs/$prog.postinstall
	fi
	
	cd -
}

if [ "$1" == "" ];then
	exit 1;
fi

source ./env.sh

if [ "$2" == "-y" ]; then
	confirm_param="yes"
fi

case "$1" in
	all)
		for prog in `cat packages.list`
		do
			__rebuild_one $prog $confirm_param;
		done
		;;
	*)
		__rebuild_one $1 $confirm_param;
		;;
esac
