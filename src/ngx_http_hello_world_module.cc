extern "C" {
    #include <ngx_config.h>
    #include <ngx_core.h>
    #include <ngx_http.h>
}
using namespace std;
extern "C" ngx_module_t  ngx_http_hello_world_module;

static char *ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

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

static ngx_http_module_t  ngx_http_hello_world_module_ctx = {
    NULL,  /* preconfiguration */
    NULL,  /* postconfiguration */

    NULL,  /* create main configuration */
    NULL,  /* init main configuration */

    NULL,  /* create server configuration */
    NULL,  /* merge server configuration */

    NULL,  /* create location configuration */
    NULL,  /* merge location configuration */
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

static ngx_str_t  text_plain_type = ngx_string("text/html");
static u_char hello_world[] =  "<h1>Hello world !</h1>";

static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r)
{
    ngx_http_complex_value_t  cv;

    if (! (r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))) {
        return NGX_HTTP_NOT_ALLOWED;
    }

    ngx_memzero(&cv, sizeof(ngx_http_complex_value_t));

    cv.value.len = sizeof(hello_world) - 1;
    cv.value.data = hello_world;

    return ngx_http_send_response(r, NGX_HTTP_OK, &text_plain_type, &cv);
}


static char *ngx_http_hello_world
(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t  *clcf;

    clcf = reinterpret_cast<ngx_http_core_loc_conf_t*>(
		ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module));
    clcf->handler = ngx_http_hello_world_handler;

    return NGX_CONF_OK;
}
