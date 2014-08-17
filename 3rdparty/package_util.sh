function __extract()
{
	prog=$1
	distfile=`ls -t distfiles/${prog}*|sort -rn| head -1`
	if [ "${distfile%\.bz2}" != "${distfile}" ] ; then
		cmd="tar -jxf"
	else
		cmd="tar -zxf"
	fi

	mkdir -p _build/${prog}
	rm -fr _build/${prog}/*
	${cmd} ${distfile} -C _build/${prog}
}

function __prepare()
{
	prog=$1
	echo "building: " ${prog}
	dir=`ls -dt _build/${prog}/* | tail -1`
	BUILDDIR=`pwd`

	echo cd ${dir}
	cd ${dir}

	cat ${BUILDDIR}/specs/${prog}.spec | while read i
	do
		echo -n "+"
		echo ${i}
	done
	source ${BUILDDIR}/specs/${prog}.spec
}
