extern "C" {
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
}
#include <iostream>
using namespace std;
extern "C" ngx_module_t ngx_http_hello_world_module;

static char *ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_http_output_header_filter_pt  ngx_http_next_header_filter;
static ngx_http_output_body_filter_pt    ngx_http_next_body_filter;

static ngx_int_t
ngx_http_gzip_header_filter(ngx_http_request_t *r)
{
    ngx_table_elt_t       *h;

    // r->headrs_out.x_debug = ngx_list_push(&r->headers_out)
    // r->headers_out.x_debug = ngx_list_push(&r->headers_out.headers);
    h = reinterpret_cast<ngx_table_elt_t *>(ngx_list_push(&r->headers_out.headers));
    if (h == NULL) {
        return NGX_ERROR;
    }
    h->hash = 1;
    h->key.len = sizeof("X-Debug") - 1;
    h->key.data = (u_char *) "X-Debug";
    h->value.len = sizeof("1") - 1;
    h->value.data = (u_char *) "1";
    ngx_http_send_header(r);

    // <-- 中略したけどこんな感じ。
    return ngx_http_next_header_filter(r);
}

static ngx_command_t ngx_http_hello_world_module_commands[] = {
  {
       ngx_string("ngx_hello_world"),
       NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
       ngx_http_hello_world,
       0,
       0,
       NULL,
  },

  ngx_null_command,
};

static ngx_http_module_t ngx_http_hello_world_module_ctx = {
  NULL, /* preconfiguration */
  NULL, /* postconfiguration */
  NULL, /* create main configuration */
  NULL, /* init main configuration */
  NULL, /* create server configuration */
  NULL, /* merge server configuration */
  NULL, /* create location configuration */
  NULL, /* merge location configuration */
};

ngx_module_t  ngx_http_hello_world_module = {
  NGX_MODULE_V1,
  &ngx_http_hello_world_module_ctx, /* module context */
  ngx_http_hello_world_module_commands,   /* module directives */
  NGX_HTTP_MODULE,               /* module type */
  NULL,                          /* init master */
  NULL,                          /* init module */
  NULL,                          /* init process */
  NULL,                          /* init thread */
  NULL,                          /* exit thread */
  NULL,                          /* exit process */
  NULL,                          /* exit master */
  NGX_MODULE_V1_PADDING
};

static ngx_str_t text_plain_type = ngx_string("text/html");
static u_char hello_world[] = "<h1>Hello world !</h1>\n";

static ngx_int_t
ngx_http_hello_world_handler(ngx_http_request_t *r)
{
  ngx_http_complex_value_t cv;

  if (!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD))) {
    return NGX_HTTP_NOT_ALLOWED;
  }

  ngx_memzero(&cv, sizeof(ngx_http_complex_value_t));

  string hw = "Hello World! V2\n";
  cv.value.len = hw.size();
  cv.value.data = reinterpret_cast<u_char*>(const_cast<char*>(hw.c_str()));

  // r->headers_in.headers.get("DEBUG");
  ngx_log_error(NGX_LOG_INFO, r->connection->log, 0, "client debug code");
  // // or
  // ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "hello debug");
  return ngx_http_send_response(r, NGX_HTTP_OK, &text_plain_type, &cv);
}

static ngx_int_t
ngx_http_gzip_filter_init(ngx_conf_t *cf)
{
  // src/http/modules/ngx_http_gzip_filter_module.c
 ngx_http_next_header_filter = ngx_http_top_header_filter;
 ngx_http_top_header_filter = ngx_http_gzip_header_filter;
 // ngx_http_next_body_filter = ngx_http_top_body_filter;
 // ngx_http_top_body_filter = ngx_http_gzip_body_filter;

    return NGX_OK;
}

static char *
ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
  ngx_http_core_loc_conf_t *clcf;

  clcf = reinterpret_cast<ngx_http_core_loc_conf_t *>(ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module));
  clcf->handler = ngx_http_hello_world_handler;

  return NGX_CONF_OK;
}
