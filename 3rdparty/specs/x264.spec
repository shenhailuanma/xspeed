
if [ "$OS" = "ios" ]
then
    echo "OS is ios"
elif [ "$OS" = "android" ]
then
    echo "OS is android"
else
    echo "OS is default"
fi

echo $OS
echo $CC
./configure --prefix=${INSTALLDIR} --enable-static
