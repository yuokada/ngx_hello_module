#!/bin/bash

./configure --with-pcre --with-http_stub_status_module \
            --add-module=../data/src/

gmake && gmake install
