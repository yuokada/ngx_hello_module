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
RUN wget http://nginx.org/download/nginx-1.9.11.tar.gz -O $TGZFILE && tar zxf $TGZFILE && rm -f $TGZFILE
#ADD . /root/ngx-practice
#VOLUME ["."]
CMD ["/bin/bash"]
