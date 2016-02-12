ngx_hello_module
================

build
-----

```
% cd  /path/to/nginx-src
% bash ../path/to/src/build.sh
```

```
location /test {
    ngx_hello_world;
}
```

running
-------

```
$ /usr/local/nginx/sbin/nginx -c conf/nginx.conf
$ ps aux
$ curl -i http://localhost/test
```


NOTE
----

```
% /usr/local/nginx/sbin/nginx -c conf/nginx.conf
```

confファイルは実は /usr/local/nginx/ディレクトリからの相対パスのようだ。  
ディレクティブを追加したらcopyしてやるか絶対パスでconfigfileを指定する必要がある。
```
% vim conf/nginx.conf
% cp conf/nginx.conf /usr/local/nginx/conf/nginx.conf
```

```
% /usr/local/nginx/sbin/nginx -c `pwd`/conf/nginx.conf
```

```
$ wget http://download.virtualbox.org/virtualbox/5.0.14/VirtualBox-5.0.14-105127-OSX.dmg

$ mv VirtualBox-5.0.14-105127-OSX.dmg  /tmp/

$ sudo mount -t iso9660  /tmp/VirtualBox-5.0.14-105127-OSX.dmg  /mnt
```

docker-running
--------------

こんな感じでコンテナを起動してexecで侵入。

```
$ docker run -v `pwd`:/root/ngx-practice/data -d -it web_dev
269ded7604fd1173de218d8ff7fb90d8c3b4cb277b6972e1756b3e6133d812c9
$ docker exec  -it $(docker ps  -l -q) /bin/bash
$ docker commit $(docker ps  -l -q) web_dev
$ docker images
REPOSITORY                TAG                 IMAGE ID            CREATED              VIRTUAL SIZE
web_dev                   latest              3bf8c4f8eb4c        About a minute ago   519.5 MB
```


Link
-----

- [perusio/nginx-hello-world-module: A hello world module for learning Nginx module development](https://github.com/perusio/nginx-hello-world-module "perusio/nginx-hello-world-module: A hello world module for learning Nginx module development")
- [cubicdaiya/ngx_http_hello_world: Hello, World with nginx](https://github.com/cubicdaiya/ngx_http_hello_world "cubicdaiya/ngx_http_hello_world: Hello, World with nginx")
- [nginx moduleをつくろう その1〜Hello, World〜 - bokko bokkoにしてやんよ](http://cubicdaiya.github.io/blog/ja/blog/2013/01/08/nginx1/ "nginx moduleをつくろう その1〜Hello, World〜 - bokko bokkoにしてやんよ")
- [nginxをdockerで動かす時のTips 3選 - インフラエンジニアway - Powered by HEARTBEATS](http://heartbeats.jp/hbblog/2014/07/3-tips-for-nginx-on-docker.html "nginxをdockerで動かす時のTips 3選 - インフラエンジニアway - Powered by HEARTBEATS")
- [Docker 虎の巻](https://gist.github.com/tcnksm/7700047 "Docker 虎の巻")
