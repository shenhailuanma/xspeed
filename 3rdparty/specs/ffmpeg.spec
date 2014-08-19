
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
  --disable-hwaccels \
  --disable-debug \
  --enable-nonfree \
  --enable-static \
  --enable-version3 \
  --disable-ffplay \
  --disable-ffprobe \
  --disable-ffserver \
  --disable-encoders \
  --disable-decoders \
  --enable-decoder=aac \
  --enable-decoder=aac_latm \
  --enable-decoder=ac3 \
  --enable-decoder=flv \
  --enable-decoder=h264 \
  --enable-decoder=mpeg4 \
  --enable-decoder=mpeg2video \
  --enable-decoder=mp3 \
  --enable-decoder=mp2 \
  --disable-muxers \
  --disable-demuxers \
  --enable-muxer=flv \
  --enable-muxer=mp4 \
  --enable-muxer=mpegts \
  --enable-demuxer=aac \
  --enable-demuxer=ac3 \
  --enable-demuxer=h264 \
  --enable-demuxer=flv \
  --enable-demuxer=latm \
  --enable-demuxer=mpegvideo \
  --enable-demuxer=mov \
  --enable-demuxer=pcm_s16le \
  --enable-demuxer=pcm_s16be \
  --disable-protocols \
  --disable-parsers \
  --enable-small \
  --enable-protocol=file 

#  --enable-protocol=rtmp \
#  --enable-protocol=rtmpt

  #--disable-parsers \
  #--disable-decoders \
  #--enable-small \
#sed -i -e 's/-fomit-frame-pointer//' -e 's/-O3//g' config.mak

# build semi-statically linked ffmpeg, ffplay, ffserver
#sed -i -e 's#^LDFLAGS=.*#LDFLAGS=$(SRC_PATH)/libavformat/libavformat.a $(SRC_PATH)/libavcodec/libavcodec.a $(SRC_PATH)/libavutil/libavutil.a $(SRC_PATH)/libswscale/libswscale.a#' -e 's#^EXTRALIBS=.*#EXTRALIBS= -lm -lasound -lssl -lcrypto -ldl -lbz2 -lz -lpthread #' config.mak
