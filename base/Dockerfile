FROM centos:centos7
MAINTAINER The CentOS Project <cloud-ops@centos.org>
RUN yum update  -y; yum clean all
RUN yum install -y epel-release; \
    yum install -y autoconf automake libtool wget; \
    yum install -y git make vim less; \
    yum install -y gcc gcc-c++ pkgconfig pcre-devel tcl-devel expat-devel openssl-devel; \
    yum install -y rpm-build ;\
    yum clean all
# https://cwiki.apache.org/confluence/display/TS/CentOS

RUN mkdir /root/ngx-practice
WORKDIR /root/ngx-practice
ENV TGZFILE nginx.tar.gz
RUN wget http://nginx.org/download/nginx-1.9.15.tar.gz -O $TGZFILE && tar zxf $TGZFILE && rm -f $TGZFILE
#ADD . /root/ngx-practice
#VOLUME ["."]

# http2 client
RUN yum -y groupinstall "Development Tools" && \
    yum -y install libev libev-devel zlib zlib-devel openssl openssl-devel
ENV NGHTTP2_VER af24f8394e43f4
RUN cd /root && git clone https://github.com/tatsuhiro-t/nghttp2.git && \
    cd /root/nghttp2 && \
    echo "git reset --hard $NGHTTP2_VER" && \
    autoreconf -i && \
    automake && \
    autoconf && \
    ./configure && \
    make && \
    make install

WORKDIR /root
RUN wget --quiet http://curl.haxx.se/download/curl-7.40.0.tar.gz && \
    tar -zxf curl-7.40.0.tar.gz
RUN cd /root/curl-7.40.0 && \
    ./buildconf  && \
    echo "DEBUG: ./configure --with-ssl --with-nghttp2=/usr/local" && \
    which nghttp && \
    ls  -lh /usr/local && \
    ./configure --with-nghttp2=/usr/local && \
    make && \
    make install && \
    ldconfig

CMD ["/bin/bash"]
