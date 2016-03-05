[Installation and Compile-Time Options | NGINX](https://www.nginx.com/resources/wiki/start/topics/tutorials/installoptions/#compilation-controls "Installation and Compile-Time Options | NGINX")

1.9.11対応ってわけでもないけどビルドオプションが変わってたので`configure`で
`--with-cc-opt="-Wno-unused-local-typedefs -Wno-error"` を渡してエラーを警告に変えて対応。


```
cc -c -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g   -I src/core -I src/event -I src/event/modules -I src/os/unix -I objs -I src/http -I src/http/modules \
        -o objs/addon/src/ngx_http_hello_world_module.o \
        ../data/src//ngx_http_hello_world_module.cc
../data/src//ngx_http_hello_world_module.cc:51:1: error: deprecated conversion from string constant to 'char*' [-Werror=write-strings]
 };
```


----------

```
cc -c -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g   -I src/core -I src/event -I src/event/modules -I src/os/unix -I objs -I src/http -I src/http/modules \
        -o objs/addon/src/ngx_http_hello_world_module.o \
        ../data/src//ngx_http_hello_world_module.cc
../data/src//ngx_http_hello_world_module.cc:38:21: error: conflicting declaration 'const ngx_module_t ngx_http_hello_world_module'
 const ngx_module_t  ngx_http_hello_world_module = {
                     ^
../data/src//ngx_http_hello_world_module.cc:7:25: error: 'ngx_http_hello_world_module' has a previous declaration as 'ngx_module_t ngx_http_hello_world_module'
 extern "C" ngx_module_t ngx_http_hello_world_module;
                         ^
```


cc -c -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g   -I src/core -I src/event -I src/event/modules -I src/os/unix -I objs -I src/http -I src/http/modules -o objs/addon/src/ngx_http_hello_world_module.o ../data/src//ngx_http_hello_world_module.cc


cc -c -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror=write-strings -g   -I src/core -I src/event -I src/event/modules -I src/os/unix -I objs -I src/http -I src/http/modules -o objs/addon/src/ngx_http_hello_world_module.o ../data/src//ngx_http_hello_world_module.cc


## 2016-02-16

とりあえず、これで通った。
```
# gcc  -std=c++0x -c -pipe  -O -W  -Wpointer-arith -Wno-unused-parameter  -g   -I src/core -I src/event -I src/event/modules -I src/os/unix -I objs -I src/http -I src/http/modules -o objs/addon/src/ngx_http_hello_world_module.o ../data/src//ngx_http_hello_world_module.cc
../data/src//ngx_http_hello_world_module.cc:49:1: warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
 };
```

## 2016-03-05
-fpermissive オプションのありなしでビルドが成功/失敗する。

-fpermissive ありのとき。
```
# cc -c -fPIC -pipe -fpermissive -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g -Wno-unused-local-typedefs -Wno-error -I src/core -I src/event -I src/event/modules -I src/os/unix -I objs -I src/http -I src/http/modules         -o objs/addon/src/ngx_http_hello_world_module.o         ../data/src//ngx_http_hello_world_module.cc
../data/src//ngx_http_hello_world_module.cc: In function 'ngx_int_t ngx_http_gzip_header_filter(ngx_http_request_t*)':
../data/src//ngx_http_hello_world_module.cc:23:76: warning: invalid conversion from 'void*' to 'ngx_table_elt_t*' [-fpermissive]
     r->headers_out.content_encoding = ngx_list_push(&r->headers_out.headers);
                                                                            ^
../data/src//ngx_http_hello_world_module.cc: At global scope:
../data/src//ngx_http_hello_world_module.cc:75:1: warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
 };
 ^
../data/src//ngx_http_hello_world_module.cc:13:42: warning: 'ngx_http_next_body_filter' defined but not used [-Wunused-variable]
 static ngx_http_output_body_filter_pt    ngx_http_next_body_filter;
                                          ^
../data/src//ngx_http_hello_world_module.cc:78:15: warning: 'hello_world' defined but not used [-Wunused-variable]
 static u_char hello_world[] = "<h1>Hello world !</h1>\n";
               ^
../data/src//ngx_http_hello_world_module.cc:103:1: warning: 'ngx_int_t ngx_http_gzip_filter_init(ngx_conf_t*)' defined but not used [-Wunused-function]
 ngx_http_gzip_filter_init(ngx_conf_t *cf)
 ^
 ```

-fpermissive なしの時。 <= デフォルト。
```
# cc -c -fPIC -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g -Wno-unused-local-typedefs -Wno-error -I src/core -I src/event -I src/event/modules -I src/os/unix -I objs -I src/http -I src/http/modules         -o objs/addon/src/ngx_http_hello_world_module.o         ../data/src//ngx_http_hello_world_module.cc
../data/src//ngx_http_hello_world_module.cc: In function 'ngx_int_t ngx_http_gzip_header_filter(ngx_http_request_t*)':
../data/src//ngx_http_hello_world_module.cc:23:76: error: invalid conversion from 'void*' to 'ngx_table_elt_t*' [-fpermissive]
     r->headers_out.content_encoding = ngx_list_push(&r->headers_out.headers);
                                                                            ^
../data/src//ngx_http_hello_world_module.cc: At global scope:
../data/src//ngx_http_hello_world_module.cc:75:1: warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
 };
 ^
../data/src//ngx_http_hello_world_module.cc:13:42: warning: 'ngx_http_next_body_filter' defined but not used [-Wunused-variable]
 static ngx_http_output_body_filter_pt    ngx_http_next_body_filter;
                                          ^
../data/src//ngx_http_hello_world_module.cc:78:15: warning: 'hello_world' defined but not used [-Wunused-variable]
 static u_char hello_world[] = "<h1>Hello world !</h1>\n";
               ^
../data/src//ngx_http_hello_world_module.cc:103:1: warning: 'ngx_int_t ngx_http_gzip_filter_init(ngx_conf_t*)' defined but not used [-Wunused-function]
 ngx_http_gzip_filter_init(ngx_conf_t *cf)
 ^
 ```

> ngx_pagespeed/のコードみて判断するしか無さそう。

と思ったけど、reinterpret_castでいけた。

> r->headers_out.content_encoding = reinterpret_cast<ngx_table_elt_t *>(ngx_list_push(&r->headers_out.headers));
foobar

hoge

```
[root@bb43529e9d58 nginx-1.9.11]# cc -c -fPIC -pipe  -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g -Wno-unused-local-typedefs -Wno-error -I src/core -I src/event -I src/event/modules -I src/os/unix -I objs -I src/http -I src/http/modules         -o objs/addon/src/ngx_http_hello_world_module.o         ../data/src//ngx_http_hello_world_module.cc
../data/src//ngx_http_hello_world_module.cc:74:1: warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
 };
 ^
../data/src//ngx_http_hello_world_module.cc:13:42: warning: 'ngx_http_next_body_filter' defined but not used [-Wunused-variable]
 static ngx_http_output_body_filter_pt    ngx_http_next_body_filter;
                                          ^
../data/src//ngx_http_hello_world_module.cc:77:15: warning: 'hello_world' defined but not used [-Wunused-variable]
 static u_char hello_world[] = "<h1>Hello world !</h1>\n";
               ^
../data/src//ngx_http_hello_world_module.cc:102:1: warning: 'ngx_int_t ngx_http_gzip_filter_init(ngx_conf_t*)' defined but not used [-Wunused-function]
 ngx_http_gzip_filter_init(ngx_conf_t *cf)
 ^

```
