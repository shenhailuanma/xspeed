ARCH_FLAGS="-march=nocona -msse2"
GCC_PATH="/usr/bin"

if [ -f /etc/redhat-release ]; then
	GCC_PATH="/usr/local/gcc/bin"
fi

cat /proc/cpuinfo |grep "Opteron" > /dev/null
if [ "$?" == "0" ]; then
ARCH_FLAGS="-march=opteron -m3dnow -msse2"
fi
 
cat /proc/cpuinfo |grep "Core(TM)2" > /dev/null
if [ "$?" == "0" ]; then
	gcc -v 2>&1|grep "version"|grep "4.3" > /dev/null
	if [ "$?" == "0" ]; then
	ARCH_FLAGS="-march=core2 -mtune=core2"
	else
	ARCH_FLAGS="-march=nocona"
	fi
fi

if [ `uname -m` == "x86_64" ]; then
	ARCH_FLAGS="$ARCH_FLAGS -m64"
fi

hostname=`hostname -s`
ENV_NAME=MEDIA_BUILD
echo $TVIE_APP_ENVS |grep $ENV_NAME &> /dev/null

if [ $? -eq 1 ] ; then
  export MEDIA_BASE=`cd ../release; pwd`
  export MB=$MEDIA_BASE
  MEDIA_BUILD_PATH=$(cd $(dirname $BASH_SOURCE); pwd -P)
  export MEDIA_BUILD="$MEDIA_BUILD_PATH"
  export CC="${GCC_PATH}/gcc"
  export CXX="${GCC_PATH}/g++"
  CFLAGS="-O3 ${ARCH_FLAGS} -pipe -fomit-frame-pointer -mpreferred-stack-boundary=4" 
  CXXFLAGS="-O3 ${ARCH_FLAGS} -pipe -fomit-frame-pointer -mpreferred-stack-boundary=4" 
  
  if [ "$hostname" == "flux" ] ; then
	CFLAGS="-g ${CFLAGS}"
	CXXFLAGS="-g ${CXXFLAGS}"
  fi

  export CFLAGS
  export CXXFLAGS
  export PATH=$PATH:${MEDIA_BASE}/bin
 
  if [ -z "$LD_LIBRARY_PATH" ] ; then
    export LD_LIBRARY_PATH=${MEDIA_BASE}/lib
  else
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${MEDIA_BASE}/lib
  fi
 
  if [ -z "$PKG_CONFIG_PATH" ] ; then
    export PKG_CONFIG_PATH=${MEDIA_BASE}/lib/pkgconfig
  else
    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${MEDIA_BASE}/lib/pkgconfig
  fi
  export TVIE_APP_ENVS="$ENV_NAME,$TVIE_APP_ENVS"
  echo "$ENV_NAME registered!"

fi
