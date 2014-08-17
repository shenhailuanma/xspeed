sed 's/\r//g' ./bootstrap > ./bootstrap.sh
sed 's/\r//g' ./configure.in > ./configure.in.unix
mv configure.in.unix configure.in
sh ./bootstrap.sh && ./configure --prefix=${INSTALLDIR} --without-mp4v2
