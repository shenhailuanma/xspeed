
export PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:${INSTALLDIR}/lib/pkgconfig
echo "${INSTALLDIR}"

./configure --prefix=${INSTALLDIR} --cc=$CC \
  --extra-cflags="-I${INSTALLDIR}/include" --extra-ldflags="-L${INSTALLDIR}/lib -lm" \
  --enable-pthreads --extra-libs=-lpthread --enable-gpl \
  --disable-avdevice \
  --disable-devices \
  --disable-postproc \
  --disable-avfilter \
  --disable-filters \
  --disable-debug \
  --enable-nonfree \
  --enable-static \
  --enable-version3 \
  --disable-ffplay \
  --disable-ffprobe \
  --disable-ffserver \
  --disable-decoders \
  --disable-encoders \
  --disable-parsers \
  --enable-libfaac \
  --enable-encoder=libfaac \
  --enable-libx264 \
  --enable-encoder=libx264 \
  --enable-decoder=aac \
  --enable-decoder=aac_latm \
  --enable-decoder=mp3 \
  --enable-decoder=h264 \
  --enable-decoder=mpeg4 \
  --enable-decoder=flv \
  --enable-parser=aac \
  --enable-parser=aac_latm \
  --enable-parser=h264 \
  --enable-parser=mpeg4video \
  --disable-bsfs \
  --disable-demuxers \
  --enable-demuxer=aac \
  --enable-demuxer=h264 \
  --enable-demuxer=mov \
  --enable-demuxer=mpegps \
  --disable-muxers \
  --enable-muxer=flv \
  --enable-muxer=mp4 \
  --enable-muxer=mpegts \
  --disable-protocols \
  --enable-protocol=file \
  --enable-protocol=rtmp \
  --enable-protocol=rtmpt

#sed -i -e 's/-fomit-frame-pointer//' -e 's/-O3//g' config.mak

# build semi-statically linked ffmpeg, ffplay, ffserver
sed -i -e 's#^LDFLAGS=.*#LDFLAGS=$(SRC_PATH)/libavformat/libavformat.a $(SRC_PATH)/libavcodec/libavcodec.a $(SRC_PATH)/libavutil/libavutil.a $(SRC_PATH)/libswscale/libswscale.a#' -e 's#^EXTRALIBS=.*#EXTRALIBS=${INSTALLDIR}/lib/libx264.a ${INSTALLDIR}/lib/libfaac.a -lm -lasound -lssl -lcrypto -ldl -lbz2 -lz -lpthread #' config.mak
