#!/bin/bash

# ./configure --with-ld-opt="-lstdc++" \
#             --with-pcre --with-http_stub_status_module \
#             --add-dynamic-module=../data/ngx_http_hello_world/ \
./configure --with-ld-opt="-lstdc++"  --with-cc-opt="-Wno-unused-local-typedefs -Wno-error" \
            --with-pcre --with-http_stub_status_module \
            --add-dynamic-module=../data/src/
gmake && gmake install
