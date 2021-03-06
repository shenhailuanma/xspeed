
export PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:${INSTALLDIR}/lib/pkgconfig
echo "${INSTALLDIR}"

./configure --prefix=${INSTALLDIR} --cc=$CC \
  --extra-cflags="-I${INSTALLDIR}/include" --extra-ldflags="-L${INSTALLDIR}/lib -lm" \
  --enable-pthreads --extra-libs=-lpthread \
  --disable-avdevice \
  --disable-devices \
  --disable-postproc \
  --disable-avfilter \
  --disable-filters \
  --disable-hwaccels \
  --disable-debug \
  --enable-nonfree \
  --enable-static \
  --enable-version3 \
  --disable-ffplay \
  --disable-ffprobe \
  --disable-ffserver \
  --disable-yasm 

#  --enable-protocol=rtmp \
#  --enable-protocol=rtmpt

  #--disable-decoders \
  #--disable-parsers \
  #--disable-decoders \
  #--enable-small \
#sed -i -e 's/-fomit-frame-pointer//' -e 's/-O3//g' config.mak

# build semi-statically linked ffmpeg, ffplay, ffserver
#sed -i -e 's#^LDFLAGS=.*#LDFLAGS=$(SRC_PATH)/libavformat/libavformat.a $(SRC_PATH)/libavcodec/libavcodec.a $(SRC_PATH)/libavutil/libavutil.a $(SRC_PATH)/libswscale/libswscale.a#' -e 's#^EXTRALIBS=.*#EXTRALIBS= -lm -lasound -lssl -lcrypto -ldl -lbz2 -lz -lpthread #' config.mak
