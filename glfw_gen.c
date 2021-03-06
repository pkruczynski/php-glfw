#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_glfw.h"

#include <zend_API.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


#define PHPGLFW_GLFWWINDOW_NAME "glfwwindow"
int phpglfw_glfwwindow_context;
#define PHPGLFW_GLFWCURSOR_NAME "glfwcursor"
int phpglfw_glfwcursor_context;
#define PHPGLFW_STBIMAGEDATA_NAME "stbimagedata"
int phpglfw_stbimagedata_context;

#define PHPGLFW_RESOURCE_TYPE zend_resource
#define PHPGLFW_RETURN_GLFWWINDOW_RESOURCE(glfwwindow, context) \
    RETURN_RES(zend_register_resource(glfwwindow, context))
#define PHPGLFW_RETURN_GLFWCURSOR_RESOURCE(glfwcursor, context) \
    RETURN_RES(zend_register_resource(glfwcursor, context))
#define PHPGLFW_RETURN_STBIMAGEDATA_RESOURCE(stbimagedata, context) \
    RETURN_RES(zend_register_resource(stbimagedata, context))

/**
 * Get GLFWwindow * from resource
 * --------------------------------
 */
static GLFWwindow *phpglfw_fetch_glfwwindow(zval *resource TSRMLS_DC)
{
    GLFWwindow *glfwwindow;

    glfwwindow = (GLFWwindow *)zend_fetch_resource_ex(resource, PHPGLFW_GLFWWINDOW_NAME, phpglfw_glfwwindow_context);

    return glfwwindow;
}

/**
 * dtor GLFWwindow * * --------------------------------
 */
static void phpglfw_glfwwindow_dtor(zend_resource *rsrc TSRMLS_DC)
{
    GLFWwindow *glfwwindow = (void *) rsrc->ptr;

    if (glfwwindow) {
        glfwDestroyWindow(glfwwindow);    }
}

/**
 * Get GLFWcursor * from resource
 * --------------------------------
 */
static GLFWcursor *phpglfw_fetch_glfwcursor(zval *resource TSRMLS_DC)
{
    GLFWcursor *glfwcursor;

    glfwcursor = (GLFWcursor *)zend_fetch_resource_ex(resource, PHPGLFW_GLFWCURSOR_NAME, phpglfw_glfwcursor_context);

    return glfwcursor;
}

/**
 * dtor GLFWcursor * * --------------------------------
 */
static void phpglfw_glfwcursor_dtor(zend_resource *rsrc TSRMLS_DC)
{
    GLFWcursor *glfwcursor = (void *) rsrc->ptr;

    if (glfwcursor) {
        glfwDestroyCursor(glfwcursor);    }
}

/**
 * Get unsigned char * from resource
 * --------------------------------
 */
static unsigned char *phpglfw_fetch_stbimagedata(zval *resource TSRMLS_DC)
{
    unsigned char *stbimagedata;

    stbimagedata = (unsigned char *)zend_fetch_resource_ex(resource, PHPGLFW_STBIMAGEDATA_NAME, phpglfw_stbimagedata_context);

    return stbimagedata;
}

/**
 * dtor unsigned char * * --------------------------------
 */
static void phpglfw_stbimagedata_dtor(zend_resource *rsrc TSRMLS_DC)
{
    unsigned char *stbimagedata = (void *) rsrc->ptr;

    if (stbimagedata) {
        stbi_image_free(stbimagedata);    }
}


/**
 * --------------------------------
 * Generated methods
 * --------------------------------
 */
/**
 * glfwInit
 * --------------------------------
 */
ZEND_NAMED_FUNCTION(zif_glfwInit)
{

    if (glfwInit()) { RETURN_TRUE; } RETURN_FALSE;
}
 
/**
 * glfwTerminate
 * --------------------------------
 */
ZEND_NAMED_FUNCTION(zif_glfwTerminate)
{

    glfwTerminate();
}
 
/**
 * glfwGetVersion
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetVersion, 0, 0, 1)
    ZEND_ARG_INFO(1, major)
    ZEND_ARG_INFO(1, minor)
    ZEND_ARG_INFO(1, rev)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwGetVersion)
{
    zval *z_major;
    zval *z_minor;
    zval *z_rev;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzz", &z_major, &z_minor, &z_rev) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_major); convert_to_long(z_major);
    ZVAL_DEREF(z_minor); convert_to_long(z_minor);
    ZVAL_DEREF(z_rev); convert_to_long(z_rev);
    glfwGetVersion((int *)&z_major->value, (int *)&z_minor->value, (int *)&z_rev->value);
}
 
/**
 * glfwGetVersionString
 * --------------------------------
 */
ZEND_NAMED_FUNCTION(zif_glfwGetVersionString)
{

    RETURN_STRING(glfwGetVersionString());
}
 
/**
 * glfwMakeContextCurrent
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwMakeContextCurrent, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwMakeContextCurrent)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    glfwMakeContextCurrent(glfwwindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    zend_error(E_ERROR, "Could not load glad.");
    }
}
 
/**
 * glfwGetCurrentContext
 * --------------------------------
 */
ZEND_NAMED_FUNCTION(zif_glfwGetCurrentContext)
{

    GLFWwindow* glfwwindow = glfwGetCurrentContext();
    if (!glfwwindow) RETURN_FALSE;
    PHPGLFW_RETURN_GLFWWINDOW_RESOURCE(glfwwindow, phpglfw_glfwwindow_context);
}
 
/**
 * glfwSwapInterval
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSwapInterval, 0, 0, 1)
    ZEND_ARG_INFO(0, interval)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwSwapInterval)
{
    zend_long interval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &interval) == FAILURE) {
       return;
    }
    glfwSwapInterval(interval);
}
 
/**
 * glfwExtensionSupported
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwExtensionSupported, 0, 0, 1)
    ZEND_ARG_INFO(0, extension)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwExtensionSupported)
{
    const char *extension;
    size_t extension_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &extension, &extension_size) == FAILURE) {
       return;
    }
    if (glfwExtensionSupported(extension)) { RETURN_TRUE; } RETURN_FALSE;
}
 
/**
 * glfwGetProcAddress
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetProcAddress, 0, 0, 1)
    ZEND_ARG_INFO(0, procname)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwGetProcAddress)
{
    const char *procname;
    size_t procname_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &procname, &procname_size) == FAILURE) {
       return;
    }
    glfwGetProcAddress(procname);
}
 
/**
 * glfwDefaultWindowHints
 * --------------------------------
 */
ZEND_NAMED_FUNCTION(zif_glfwDefaultWindowHints)
{

    glfwDefaultWindowHints();
}
 
/**
 * glfwWindowHint
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwWindowHint, 0, 0, 1)
    ZEND_ARG_INFO(0, hint)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwWindowHint)
{
    zend_long hint;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &hint, &value) == FAILURE) {
       return;
    }
    glfwWindowHint(hint, value);
}
 
/**
 * glfwDestroyWindow
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwDestroyWindow, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwDestroyWindow)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    zend_list_close(Z_RES_P(glfwwindow_resource));
}
 
/**
 * glfwCreateWindow
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwCreateWindow, 0, 0, 1)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwCreateWindow)
{
    zend_long width;
    zend_long height;
    const char *title;
    size_t title_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls", &width, &height, &title, &title_size) == FAILURE) {
       return;
    }
    GLFWwindow* glfwwindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!glfwwindow) RETURN_FALSE;
    PHPGLFW_RETURN_GLFWWINDOW_RESOURCE(glfwwindow, phpglfw_glfwwindow_context);
}
 
/**
 * glfwWindowShouldClose
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwWindowShouldClose, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwWindowShouldClose)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    if (glfwWindowShouldClose(glfwwindow)) { RETURN_TRUE; } RETURN_FALSE;
}
 
/**
 * glfwSetWindowShouldClose
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSetWindowShouldClose, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwSetWindowShouldClose)
{
    zval *glfwwindow_resource;
    zend_bool value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rb", &glfwwindow_resource, &value) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    glfwSetWindowShouldClose(glfwwindow, value);
}
 
/**
 * glfwSwapBuffers
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSwapBuffers, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwSwapBuffers)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    glfwSwapBuffers(glfwwindow);
}
 
/**
 * glfwPollEvents
 * --------------------------------
 */
ZEND_NAMED_FUNCTION(zif_glfwPollEvents)
{

    glfwPollEvents();
}
 
/**
 * glfwGetTime
 * --------------------------------
 */
ZEND_NAMED_FUNCTION(zif_glfwGetTime)
{

    RETURN_DOUBLE(glfwGetTime());
}
 
/**
 * glfwCreateStandardCursor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwCreateStandardCursor, 0, 0, 1)
    ZEND_ARG_INFO(0, shape)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwCreateStandardCursor)
{
    zend_long shape;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &shape) == FAILURE) {
       return;
    }
    GLFWcursor * glfwcursor = glfwCreateStandardCursor(shape);
    PHPGLFW_RETURN_GLFWCURSOR_RESOURCE(glfwcursor, phpglfw_glfwcursor_context);
}
 
/**
 * glfwDestroyCursor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwDestroyCursor, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwcursor)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwDestroyCursor)
{
    zval *glfwcursor_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &glfwcursor_resource) == FAILURE) {
       return;
    }
    GLFWcursor *glfwcursor = phpglfw_fetch_glfwcursor(glfwcursor_resource TSRMLS_CC);
    zend_list_close(Z_RES_P(glfwcursor_resource));
}
 
/**
 * glfwGetClipboardString
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetClipboardString, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwGetClipboardString)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    RETURN_STRING(glfwGetClipboardString(glfwwindow));
}
 
/**
 * glfwGetCursorPos
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetCursorPos, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(1, xpos)
    ZEND_ARG_INFO(1, ypos)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwGetCursorPos)
{
    zval *glfwwindow_resource;
    zval *z_xpos;
    zval *z_ypos;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rzz", &glfwwindow_resource, &z_xpos, &z_ypos) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_xpos); convert_to_double(z_xpos);
    ZVAL_DEREF(z_ypos); convert_to_double(z_ypos);
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    glfwGetCursorPos(glfwwindow, (double *)&z_xpos->value, (double *)&z_ypos->value);
}
 
/**
 * glfwGetKey
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetKey, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwGetKey)
{
    zval *glfwwindow_resource;
    zend_long key;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &glfwwindow_resource, &key) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    RETURN_LONG(glfwGetKey(glfwwindow, key));
}
 
/**
 * glfwGetMouseButton
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetMouseButton, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwGetMouseButton)
{
    zval *glfwwindow_resource;
    zend_long key;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &glfwwindow_resource, &key) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    RETURN_LONG(glfwGetMouseButton(glfwwindow, key));
}
 
/**
 * glfwSetInputMode
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSetInputMode, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, param)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glfwSetInputMode)
{
    zval *glfwwindow_resource;
    zend_long param;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &glfwwindow_resource, &param, &value) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource TSRMLS_CC);
    glfwSetInputMode(glfwwindow, param, value);
}
 
/**
 * glEnable
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEnable, 0, 0, 1)
    ZEND_ARG_INFO(0, cap)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glEnable)
{
    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &cap) == FAILURE) {
       return;
    }
    glEnable(cap);
}
 
/**
 * glDisable
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDisable, 0, 0, 1)
    ZEND_ARG_INFO(0, cap)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glDisable)
{
    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &cap) == FAILURE) {
       return;
    }
    glDisable(cap);
}
 
/**
 * glPolygonMode
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPolygonMode, 0, 0, 1)
    ZEND_ARG_INFO(0, face)
    ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glPolygonMode)
{
    zend_long face;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &face, &mode) == FAILURE) {
       return;
    }
    glPolygonMode(face, mode);
}
 
/**
 * glBlendFunc
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBlendFunc, 0, 0, 1)
    ZEND_ARG_INFO(0, sfactor)
    ZEND_ARG_INFO(0, dfactor)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glBlendFunc)
{
    zend_long sfactor;
    zend_long dfactor;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &sfactor, &dfactor) == FAILURE) {
       return;
    }
    glBlendFunc(sfactor, dfactor);
}
 
/**
 * glViewport
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glViewport, 0, 0, 1)
    ZEND_ARG_INFO(0, x)
    ZEND_ARG_INFO(0, y)
    ZEND_ARG_INFO(0, w)
    ZEND_ARG_INFO(0, h)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glViewport)
{
    double x;
    double y;
    double w;
    double h;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &x, &y, &w, &h) == FAILURE) {
       return;
    }
    glViewport(x, y, w, h);
}
 
/**
 * glClearColor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearColor, 0, 0, 1)
    ZEND_ARG_INFO(0, r)
    ZEND_ARG_INFO(0, g)
    ZEND_ARG_INFO(0, b)
    ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glClearColor)
{
    double r;
    double g;
    double b;
    double a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &r, &g, &b, &a) == FAILURE) {
       return;
    }
    glClearColor(r, g, b, a);
}
 
/**
 * glClear
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClear, 0, 0, 1)
    ZEND_ARG_INFO(0, mask)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glClear)
{
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &mask) == FAILURE) {
       return;
    }
    glClear(mask);
}
 
/**
 * glGenBuffers
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGenBuffers, 0, 0, 1)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(1, buffers)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glGenBuffers)
{
    zend_long n;
    zval *z_buffers;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &n, &z_buffers) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_buffers); convert_to_long(z_buffers);
    glGenBuffers(n, (GLuint *)&z_buffers->value);
}
 
/**
 * glDeleteBuffers
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteBuffers, 0, 0, 1)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(1, buffers)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glDeleteBuffers)
{
    zend_long n;
    zval *z_buffers;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &n, &z_buffers) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_buffers); convert_to_long(z_buffers);
    glDeleteBuffers(n, (GLuint *)&z_buffers->value);
}
 
/**
 * glGenVertexArrays
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGenVertexArrays, 0, 0, 1)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(1, buffers)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glGenVertexArrays)
{
    zend_long n;
    zval *z_buffers;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &n, &z_buffers) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_buffers); convert_to_long(z_buffers);
    glGenVertexArrays(n, (GLuint *)&z_buffers->value);
}
 
/**
 * glDeleteVertexArrays
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteVertexArrays, 0, 0, 1)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(1, buffers)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glDeleteVertexArrays)
{
    zend_long n;
    zval *z_buffers;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &n, &z_buffers) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_buffers); convert_to_long(z_buffers);
    glDeleteVertexArrays(n, (GLuint *)&z_buffers->value);
}
 
/**
 * glBindBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindBuffer, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, buffer)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glBindBuffer)
{
    zend_long target;
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &target, &buffer) == FAILURE) {
       return;
    }
    glBindBuffer(target, buffer);
}
 
/**
 * glBindVertexArray
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindVertexArray, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glBindVertexArray)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &target) == FAILURE) {
       return;
    }
    glBindVertexArray(target);
}
 
/**
 * glBufferData
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBufferData, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, usage)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glBufferData)
{
    zend_long target;
    zend_long size;
    HashTable *data; zval *data_data;
    zend_long usage;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llhl", &target, &size, &data, &usage) == FAILURE) {
       return;
    }
    zend_error(E_ERROR, "This method is unavailable in PHP-GLFW. Please use `glBufferDataFloat(long target, array data, long usage)`, `glBufferDataDouble(long target, array data, long usage)`, `glBufferDataInt(long target, array data, long usage)` or `glBufferDataLong(long target, array data, long usage)`");
}
 
/**
 * glBufferDataFloat
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBufferDataFloat, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, usage)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glBufferDataFloat)
{
    zend_long target;
    HashTable *data; zval *data_data;
    zend_long usage;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lhl", &target, &data, &usage) == FAILURE) {
       return;
    }
    float cdata[zend_hash_num_elements(data)];
    int i = 0;
    ZEND_HASH_FOREACH_VAL(data, data_data)
      ZVAL_DEREF(data_data);
      convert_to_double(data_data);
      cdata[i] = (float) Z_DVAL_P(data_data);
      i++;
    ZEND_HASH_FOREACH_END();
    glBufferData(target, sizeof(cdata), cdata, usage);
}
 
/**
 * glBufferDataInt
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBufferDataInt, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, data)
    ZEND_ARG_INFO(0, usage)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glBufferDataInt)
{
    zend_long target;
    HashTable *data; zval *data_data;
    zend_long usage;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lhl", &target, &data, &usage) == FAILURE) {
       return;
    }
    int cdata[zend_hash_num_elements(data)];
    int i = 0;
    ZEND_HASH_FOREACH_VAL(data, data_data)
      ZVAL_DEREF(data_data);
      convert_to_long(data_data);
      cdata[i] = (int) Z_LVAL_P(data_data);
      i++;
    ZEND_HASH_FOREACH_END();
    glBufferData(target, sizeof(cdata), cdata, usage);
}
 
/**
 * glVertexAttribPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribPointer, 0, 0, 1)
    ZEND_ARG_INFO(0, index)
    ZEND_ARG_INFO(0, size)
    ZEND_ARG_INFO(0, type)
    ZEND_ARG_INFO(0, normalized)
    ZEND_ARG_INFO(0, stride)
    ZEND_ARG_INFO(0, pointer)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glVertexAttribPointer)
{
    zend_long index;
    zend_long size;
    zend_long type;
    zend_long normalized;
    zend_long stride;
    zend_long pointer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llllll", &index, &size, &type, &normalized, &stride, &pointer) == FAILURE) {
       return;
    }
    glVertexAttribPointer(index, size, type, normalized, stride * sizeof(float), (void*)(pointer * sizeof(float)));
}
 
/**
 * glEnableVertexAttribArray
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEnableVertexAttribArray, 0, 0, 1)
    ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glEnableVertexAttribArray)
{
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
       return;
    }
    glEnableVertexAttribArray(index);
}
 
/**
 * glDrawArrays
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawArrays, 0, 0, 1)
    ZEND_ARG_INFO(0, mode)
    ZEND_ARG_INFO(0, first)
    ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glDrawArrays)
{
    zend_long mode;
    zend_long first;
    zend_long count;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &mode, &first, &count) == FAILURE) {
       return;
    }
    glDrawArrays(mode, first, count);
}
 
/**
 * glDrawElements
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawElements, 0, 0, 1)
    ZEND_ARG_INFO(0, mode)
    ZEND_ARG_INFO(0, count)
    ZEND_ARG_INFO(0, type)
    ZEND_ARG_INFO(0, indices)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glDrawElements)
{
    zend_long mode;
    zend_long count;
    zend_long type;
    zend_long indices;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &mode, &count, &type, &indices) == FAILURE) {
       return;
    }
    glDrawElements(mode, count, type, indices);
}
 
/**
 * glCreateShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCreateShader, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glCreateShader)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &target) == FAILURE) {
       return;
    }
    RETURN_LONG(glCreateShader(target));
}
 
/**
 * glCreateProgram
 * --------------------------------
 */
ZEND_NAMED_FUNCTION(zif_glCreateProgram)
{

    RETURN_LONG(glCreateProgram());
}
 
/**
 * glShaderSource
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glShaderSource, 0, 0, 1)
    ZEND_ARG_INFO(0, shader)
    ZEND_ARG_INFO(0, count)
    ZEND_ARG_INFO(0, source)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glShaderSource)
{
    zend_long shader;
    zend_long count;
    const char *source;
    size_t source_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls", &shader, &count, &source, &source_size) == FAILURE) {
       return;
    }
    glShaderSource(shader, count, &source, NULL);
}
 
/**
 * glCompileShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCompileShader, 0, 0, 1)
    ZEND_ARG_INFO(0, shader)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glCompileShader)
{
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &shader) == FAILURE) {
       return;
    }
    glCompileShader(shader);
}
 
/**
 * glDeleteShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteShader, 0, 0, 1)
    ZEND_ARG_INFO(0, shader)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glDeleteShader)
{
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &shader) == FAILURE) {
       return;
    }
    glDeleteShader(shader);
}
 
/**
 * glAttachShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glAttachShader, 0, 0, 1)
    ZEND_ARG_INFO(0, program)
    ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glAttachShader)
{
    zend_long program;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &program, &index) == FAILURE) {
       return;
    }
    glAttachShader(program, index);
}
 
/**
 * glGetUniformLocation
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetUniformLocation, 0, 0, 1)
    ZEND_ARG_INFO(0, program)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glGetUniformLocation)
{
    zend_long program;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &program, &name, &name_size) == FAILURE) {
       return;
    }
    RETURN_LONG(glGetUniformLocation(program, name));
}
 
/**
 * glUniform1i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform1i, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniform1i)
{
    zend_long location;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &location, &value) == FAILURE) {
       return;
    }
    glUniform1i(location, value);
}
 
/**
 * glUniform2i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform2i, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, value0)
    ZEND_ARG_INFO(0, value1)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniform2i)
{
    zend_long location;
    zend_long value0;
    zend_long value1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &location, &value0, &value1) == FAILURE) {
       return;
    }
    glUniform2i(location, value0, value1);
}
 
/**
 * glUniform3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform3i, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, value0)
    ZEND_ARG_INFO(0, value1)
    ZEND_ARG_INFO(0, value2)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniform3i)
{
    zend_long location;
    zend_long value0;
    zend_long value1;
    zend_long value2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &location, &value0, &value1, &value2) == FAILURE) {
       return;
    }
    glUniform3i(location, value0, value1, value2);
}
 
/**
 * glUniform4i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform4i, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, value0)
    ZEND_ARG_INFO(0, value1)
    ZEND_ARG_INFO(0, value2)
    ZEND_ARG_INFO(0, value3)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniform4i)
{
    zend_long location;
    zend_long value0;
    zend_long value1;
    zend_long value2;
    zend_long value3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lllll", &location, &value0, &value1, &value2, &value3) == FAILURE) {
       return;
    }
    glUniform4i(location, value0, value1, value2, value3);
}
 
/**
 * glUniform1f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform1f, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniform1f)
{
    zend_long location;
    double value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ld", &location, &value) == FAILURE) {
       return;
    }
    glUniform1f(location, value);
}
 
/**
 * glUniform2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform2f, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, value0)
    ZEND_ARG_INFO(0, value1)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniform2f)
{
    zend_long location;
    double value0;
    double value1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ldd", &location, &value0, &value1) == FAILURE) {
       return;
    }
    glUniform2f(location, value0, value1);
}
 
/**
 * glUniform3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform3f, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, value0)
    ZEND_ARG_INFO(0, value1)
    ZEND_ARG_INFO(0, value2)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniform3f)
{
    zend_long location;
    double value0;
    double value1;
    double value2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lddd", &location, &value0, &value1, &value2) == FAILURE) {
       return;
    }
    glUniform3f(location, value0, value1, value2);
}
 
/**
 * glUniform4f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform4f, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, value0)
    ZEND_ARG_INFO(0, value1)
    ZEND_ARG_INFO(0, value2)
    ZEND_ARG_INFO(0, value3)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniform4f)
{
    zend_long location;
    double value0;
    double value1;
    double value2;
    double value3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ldddd", &location, &value0, &value1, &value2, &value3) == FAILURE) {
       return;
    }
    glUniform4f(location, value0, value1, value2, value3);
}
 
/**
 * glUniformMatrix4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix4fv, 0, 0, 1)
    ZEND_ARG_INFO(0, location)
    ZEND_ARG_INFO(0, count)
    ZEND_ARG_INFO(0, transpose)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUniformMatrix4fv)
{
    zend_long location;
    zend_long count;
    zend_bool transpose;
    HashTable *value; zval *value_data;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llbh", &location, &count, &transpose, &value) == FAILURE) {
       return;
    }
    float cdata[zend_hash_num_elements(value)];
    uint32_t i = 0;
    ZEND_HASH_FOREACH_VAL(value, value_data)
      ZVAL_DEREF(value_data);
      convert_to_double(value_data);
      cdata[i] = (float) Z_DVAL_P(value_data);
      i++;
    ZEND_HASH_FOREACH_END();
    glUniformMatrix4fv(location, count, transpose, &cdata[0]);
}
 
/**
 * glLinkProgram
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLinkProgram, 0, 0, 1)
    ZEND_ARG_INFO(0, program)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glLinkProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &program) == FAILURE) {
       return;
    }
    glLinkProgram(program);
}
 
/**
 * glGetShaderiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetShaderiv, 0, 0, 1)
    ZEND_ARG_INFO(0, shader)
    ZEND_ARG_INFO(0, pname)
    ZEND_ARG_INFO(1, params)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glGetShaderiv)
{
    zend_long shader;
    zend_long pname;
    zval *z_params;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llz", &shader, &pname, &z_params) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_params); convert_to_long(z_params);
    glGetShaderiv(shader, pname, (void *)&z_params->value);
}
 
/**
 * glGetProgramiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetProgramiv, 0, 0, 1)
    ZEND_ARG_INFO(0, program)
    ZEND_ARG_INFO(0, pname)
    ZEND_ARG_INFO(1, params)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glGetProgramiv)
{
    zend_long program;
    zend_long pname;
    zval *z_params;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llz", &program, &pname, &z_params) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_params); convert_to_long(z_params);
    glGetProgramiv(program, pname, (void *)&z_params->value);
}
 
/**
 * glUseProgram
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUseProgram, 0, 0, 1)
    ZEND_ARG_INFO(0, program)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glUseProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &program) == FAILURE) {
       return;
    }
    glUseProgram(program);
}
 
/**
 * glGenTextures
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGenTextures, 0, 0, 1)
    ZEND_ARG_INFO(0, n)
    ZEND_ARG_INFO(1, textures)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glGenTextures)
{
    zend_long n;
    zval *z_textures;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &n, &z_textures) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_textures); convert_to_long(z_textures);
    glGenTextures(n, (GLuint *)&z_textures->value);
}
 
/**
 * glBindTexture
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindTexture, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glBindTexture)
{
    zend_long target;
    zend_long texture;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &target, &texture) == FAILURE) {
       return;
    }
    glBindTexture(target, texture);
}
 
/**
 * glTexParameteri
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexParameteri, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, pname)
    ZEND_ARG_INFO(0, param)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glTexParameteri)
{
    zend_long target;
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &target, &pname, &param) == FAILURE) {
       return;
    }
    glTexParameteri(target, pname, param);
}
 
/**
 * glTextureParameteri
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTextureParameteri, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, pname)
    ZEND_ARG_INFO(0, param)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glTextureParameteri)
{
    zend_long target;
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &target, &pname, &param) == FAILURE) {
       return;
    }
    glTextureParameteri(target, pname, param);
}
 
/**
 * glTexParameterf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexParameterf, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, pname)
    ZEND_ARG_INFO(0, param)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glTexParameterf)
{
    zend_long target;
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lld", &target, &pname, &param) == FAILURE) {
       return;
    }
    glTexParameterf(target, pname, param);
}
 
/**
 * glTextureParameterf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTextureParameterf, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, pname)
    ZEND_ARG_INFO(0, param)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glTextureParameterf)
{
    zend_long target;
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lld", &target, &pname, &param) == FAILURE) {
       return;
    }
    glTextureParameterf(target, pname, param);
}
 
/**
 * glTexImage2D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexImage2D, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
    ZEND_ARG_INFO(0, level)
    ZEND_ARG_INFO(0, internal_format)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, border)
    ZEND_ARG_INFO(0, format)
    ZEND_ARG_INFO(0, type)
    ZEND_ARG_INFO(0, stbimagedata)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glTexImage2D)
{
    zend_long target;
    zend_long level;
    zend_long internal_format;
    zend_long width;
    zend_long height;
    zend_long border;
    zend_long format;
    zend_long type;
    zval *stbimagedata_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llllllllr", &target, &level, &internal_format, &width, &height, &border, &format, &type, &stbimagedata_resource) == FAILURE) {
       return;
    }
    unsigned char *stbimagedata = phpglfw_fetch_stbimagedata(stbimagedata_resource TSRMLS_CC);
    glTexImage2D(target, level, internal_format, width, height, border, format, type, stbimagedata);
}
 
/**
 * glGenerateMipmap
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGenerateMipmap, 0, 0, 1)
    ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glGenerateMipmap)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &target) == FAILURE) {
       return;
    }
    glGenerateMipmap(target);
}
 
/**
 * glActiveTexture
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glActiveTexture, 0, 0, 1)
    ZEND_ARG_INFO(0, texture)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_glActiveTexture)
{
    zend_long texture;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &texture) == FAILURE) {
       return;
    }
    glActiveTexture(texture);
}
 
/**
 * stbi_load
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_stbi_load, 0, 0, 1)
    ZEND_ARG_INFO(0, path)
    ZEND_ARG_INFO(1, width)
    ZEND_ARG_INFO(1, height)
    ZEND_ARG_INFO(1, number_or_channels)
    ZEND_ARG_INFO(0, force_n_comp)
ZEND_END_ARG_INFO()

ZEND_NAMED_FUNCTION(zif_stbi_load)
{
    const char *path;
    size_t path_size;
    zval *z_width;
    zval *z_height;
    zval *z_number_or_channels;
    zend_long force_n_comp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "szzzl", &path, &path_size, &z_width, &z_height, &z_number_or_channels, &force_n_comp) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_width); convert_to_long(z_width);
    ZVAL_DEREF(z_height); convert_to_long(z_height);
    ZVAL_DEREF(z_number_or_channels); convert_to_long(z_number_or_channels);
    unsigned char * stbimagedata = stbi_load(path, (int *)&z_width->value, (int *)&z_height->value, (int *)&z_number_or_channels->value, force_n_comp);
    if (!stbimagedata) RETURN_FALSE;
    PHPGLFW_RETURN_STBIMAGEDATA_RESOURCE(stbimagedata, phpglfw_stbimagedata_context);
}
 


/**
 * MINIT
 * --------------------------------
 */
PHP_MINIT_FUNCTION(glfw)
{
    phpglfw_glfwwindow_context = zend_register_list_destructors_ex(phpglfw_glfwwindow_dtor, NULL, PHPGLFW_GLFWWINDOW_NAME, module_number);
    phpglfw_glfwcursor_context = zend_register_list_destructors_ex(phpglfw_glfwcursor_dtor, NULL, PHPGLFW_GLFWCURSOR_NAME, module_number);
    phpglfw_stbimagedata_context = zend_register_list_destructors_ex(phpglfw_stbimagedata_dtor, NULL, PHPGLFW_STBIMAGEDATA_NAME, module_number);
#ifdef GLFW_TRUE 
    REGISTER_LONG_CONSTANT("GLFW_TRUE", GLFW_TRUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_FALSE 
    REGISTER_LONG_CONSTANT("GLFW_FALSE", GLFW_FALSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DONT_CARE 
    REGISTER_LONG_CONSTANT("GLFW_DONT_CARE", GLFW_DONT_CARE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RELEASE 
    REGISTER_LONG_CONSTANT("GLFW_RELEASE", GLFW_RELEASE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_PRESS 
    REGISTER_LONG_CONSTANT("GLFW_PRESS", GLFW_PRESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_REPEAT 
    REGISTER_LONG_CONSTANT("GLFW_REPEAT", GLFW_REPEAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_CENTERED 
    REGISTER_LONG_CONSTANT("GLFW_HAT_CENTERED", GLFW_HAT_CENTERED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_UP 
    REGISTER_LONG_CONSTANT("GLFW_HAT_UP", GLFW_HAT_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_RIGHT 
    REGISTER_LONG_CONSTANT("GLFW_HAT_RIGHT", GLFW_HAT_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_HAT_DOWN", GLFW_HAT_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_LEFT 
    REGISTER_LONG_CONSTANT("GLFW_HAT_LEFT", GLFW_HAT_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_RIGHT_UP 
    REGISTER_LONG_CONSTANT("GLFW_HAT_RIGHT_UP", GLFW_HAT_RIGHT_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_RIGHT_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_HAT_RIGHT_DOWN", GLFW_HAT_RIGHT_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_LEFT_UP 
    REGISTER_LONG_CONSTANT("GLFW_HAT_LEFT_UP", GLFW_HAT_LEFT_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_LEFT_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_HAT_LEFT_DOWN", GLFW_HAT_LEFT_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_UNKNOWN 
    REGISTER_LONG_CONSTANT("GLFW_KEY_UNKNOWN", GLFW_KEY_UNKNOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_SPACE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_SPACE", GLFW_KEY_SPACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_APOSTROPHE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_APOSTROPHE", GLFW_KEY_APOSTROPHE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_COMMA 
    REGISTER_LONG_CONSTANT("GLFW_KEY_COMMA", GLFW_KEY_COMMA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_MINUS 
    REGISTER_LONG_CONSTANT("GLFW_KEY_MINUS", GLFW_KEY_MINUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PERIOD 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PERIOD", GLFW_KEY_PERIOD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_SLASH 
    REGISTER_LONG_CONSTANT("GLFW_KEY_SLASH", GLFW_KEY_SLASH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_0 
    REGISTER_LONG_CONSTANT("GLFW_KEY_0", GLFW_KEY_0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_1 
    REGISTER_LONG_CONSTANT("GLFW_KEY_1", GLFW_KEY_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_2 
    REGISTER_LONG_CONSTANT("GLFW_KEY_2", GLFW_KEY_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_3 
    REGISTER_LONG_CONSTANT("GLFW_KEY_3", GLFW_KEY_3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_4 
    REGISTER_LONG_CONSTANT("GLFW_KEY_4", GLFW_KEY_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_5 
    REGISTER_LONG_CONSTANT("GLFW_KEY_5", GLFW_KEY_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_6 
    REGISTER_LONG_CONSTANT("GLFW_KEY_6", GLFW_KEY_6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_7 
    REGISTER_LONG_CONSTANT("GLFW_KEY_7", GLFW_KEY_7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_8 
    REGISTER_LONG_CONSTANT("GLFW_KEY_8", GLFW_KEY_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_9 
    REGISTER_LONG_CONSTANT("GLFW_KEY_9", GLFW_KEY_9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_SEMICOLON 
    REGISTER_LONG_CONSTANT("GLFW_KEY_SEMICOLON", GLFW_KEY_SEMICOLON, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_EQUAL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_EQUAL", GLFW_KEY_EQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_A 
    REGISTER_LONG_CONSTANT("GLFW_KEY_A", GLFW_KEY_A, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_B 
    REGISTER_LONG_CONSTANT("GLFW_KEY_B", GLFW_KEY_B, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_C 
    REGISTER_LONG_CONSTANT("GLFW_KEY_C", GLFW_KEY_C, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_D 
    REGISTER_LONG_CONSTANT("GLFW_KEY_D", GLFW_KEY_D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_E 
    REGISTER_LONG_CONSTANT("GLFW_KEY_E", GLFW_KEY_E, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F", GLFW_KEY_F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_G 
    REGISTER_LONG_CONSTANT("GLFW_KEY_G", GLFW_KEY_G, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_H 
    REGISTER_LONG_CONSTANT("GLFW_KEY_H", GLFW_KEY_H, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_I 
    REGISTER_LONG_CONSTANT("GLFW_KEY_I", GLFW_KEY_I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_J 
    REGISTER_LONG_CONSTANT("GLFW_KEY_J", GLFW_KEY_J, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_K 
    REGISTER_LONG_CONSTANT("GLFW_KEY_K", GLFW_KEY_K, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_L 
    REGISTER_LONG_CONSTANT("GLFW_KEY_L", GLFW_KEY_L, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_M 
    REGISTER_LONG_CONSTANT("GLFW_KEY_M", GLFW_KEY_M, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_N 
    REGISTER_LONG_CONSTANT("GLFW_KEY_N", GLFW_KEY_N, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_O 
    REGISTER_LONG_CONSTANT("GLFW_KEY_O", GLFW_KEY_O, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_P 
    REGISTER_LONG_CONSTANT("GLFW_KEY_P", GLFW_KEY_P, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_Q 
    REGISTER_LONG_CONSTANT("GLFW_KEY_Q", GLFW_KEY_Q, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_R 
    REGISTER_LONG_CONSTANT("GLFW_KEY_R", GLFW_KEY_R, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_S 
    REGISTER_LONG_CONSTANT("GLFW_KEY_S", GLFW_KEY_S, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_T 
    REGISTER_LONG_CONSTANT("GLFW_KEY_T", GLFW_KEY_T, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_U 
    REGISTER_LONG_CONSTANT("GLFW_KEY_U", GLFW_KEY_U, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_V 
    REGISTER_LONG_CONSTANT("GLFW_KEY_V", GLFW_KEY_V, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_W 
    REGISTER_LONG_CONSTANT("GLFW_KEY_W", GLFW_KEY_W, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_X 
    REGISTER_LONG_CONSTANT("GLFW_KEY_X", GLFW_KEY_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_Y 
    REGISTER_LONG_CONSTANT("GLFW_KEY_Y", GLFW_KEY_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_Z 
    REGISTER_LONG_CONSTANT("GLFW_KEY_Z", GLFW_KEY_Z, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_BRACKET 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_BACKSLASH 
    REGISTER_LONG_CONSTANT("GLFW_KEY_BACKSLASH", GLFW_KEY_BACKSLASH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_BRACKET 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_GRAVE_ACCENT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_WORLD_1 
    REGISTER_LONG_CONSTANT("GLFW_KEY_WORLD_1", GLFW_KEY_WORLD_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_WORLD_2 
    REGISTER_LONG_CONSTANT("GLFW_KEY_WORLD_2", GLFW_KEY_WORLD_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_ESCAPE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_ESCAPE", GLFW_KEY_ESCAPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_ENTER 
    REGISTER_LONG_CONSTANT("GLFW_KEY_ENTER", GLFW_KEY_ENTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_TAB 
    REGISTER_LONG_CONSTANT("GLFW_KEY_TAB", GLFW_KEY_TAB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_BACKSPACE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_BACKSPACE", GLFW_KEY_BACKSPACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_INSERT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_INSERT", GLFW_KEY_INSERT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_DELETE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_DELETE", GLFW_KEY_DELETE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT", GLFW_KEY_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT", GLFW_KEY_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_KEY_DOWN", GLFW_KEY_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_UP 
    REGISTER_LONG_CONSTANT("GLFW_KEY_UP", GLFW_KEY_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PAGE_UP 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PAGE_UP", GLFW_KEY_PAGE_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PAGE_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PAGE_DOWN", GLFW_KEY_PAGE_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_HOME 
    REGISTER_LONG_CONSTANT("GLFW_KEY_HOME", GLFW_KEY_HOME, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_END 
    REGISTER_LONG_CONSTANT("GLFW_KEY_END", GLFW_KEY_END, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_CAPS_LOCK 
    REGISTER_LONG_CONSTANT("GLFW_KEY_CAPS_LOCK", GLFW_KEY_CAPS_LOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_SCROLL_LOCK 
    REGISTER_LONG_CONSTANT("GLFW_KEY_SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_NUM_LOCK 
    REGISTER_LONG_CONSTANT("GLFW_KEY_NUM_LOCK", GLFW_KEY_NUM_LOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PRINT_SCREEN 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PAUSE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PAUSE", GLFW_KEY_PAUSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F1 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F1", GLFW_KEY_F1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F2 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F2", GLFW_KEY_F2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F3 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F3", GLFW_KEY_F3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F4 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F4", GLFW_KEY_F4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F5 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F5", GLFW_KEY_F5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F6 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F6", GLFW_KEY_F6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F7 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F7", GLFW_KEY_F7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F8 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F8", GLFW_KEY_F8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F9 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F9", GLFW_KEY_F9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F10 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F10", GLFW_KEY_F10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F11 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F11", GLFW_KEY_F11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F12 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F12", GLFW_KEY_F12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F13 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F13", GLFW_KEY_F13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F14 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F14", GLFW_KEY_F14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F15 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F15", GLFW_KEY_F15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F16 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F16", GLFW_KEY_F16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F17 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F17", GLFW_KEY_F17, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F18 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F18", GLFW_KEY_F18, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F19 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F19", GLFW_KEY_F19, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F20 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F20", GLFW_KEY_F20, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F21 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F21", GLFW_KEY_F21, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F22 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F22", GLFW_KEY_F22, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F23 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F23", GLFW_KEY_F23, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F24 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F24", GLFW_KEY_F24, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F25 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F25", GLFW_KEY_F25, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_0 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_0", GLFW_KEY_KP_0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_1 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_1", GLFW_KEY_KP_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_2 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_2", GLFW_KEY_KP_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_3 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_3", GLFW_KEY_KP_3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_4 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_4", GLFW_KEY_KP_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_5 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_5", GLFW_KEY_KP_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_6 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_6", GLFW_KEY_KP_6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_7 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_7", GLFW_KEY_KP_7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_8 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_8", GLFW_KEY_KP_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_9 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_9", GLFW_KEY_KP_9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_DECIMAL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_DECIMAL", GLFW_KEY_KP_DECIMAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_DIVIDE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_DIVIDE", GLFW_KEY_KP_DIVIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_MULTIPLY 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_SUBTRACT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_ADD 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_ADD", GLFW_KEY_KP_ADD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_ENTER 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_ENTER", GLFW_KEY_KP_ENTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_EQUAL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_EQUAL", GLFW_KEY_KP_EQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_SHIFT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_CONTROL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_ALT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_ALT", GLFW_KEY_LEFT_ALT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_SUPER 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_SUPER", GLFW_KEY_LEFT_SUPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_SHIFT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_CONTROL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_ALT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_ALT", GLFW_KEY_RIGHT_ALT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_SUPER 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_MENU 
    REGISTER_LONG_CONSTANT("GLFW_KEY_MENU", GLFW_KEY_MENU, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LAST 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LAST", GLFW_KEY_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOD_SHIFT 
    REGISTER_LONG_CONSTANT("GLFW_MOD_SHIFT", GLFW_MOD_SHIFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOD_CONTROL 
    REGISTER_LONG_CONSTANT("GLFW_MOD_CONTROL", GLFW_MOD_CONTROL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOD_ALT 
    REGISTER_LONG_CONSTANT("GLFW_MOD_ALT", GLFW_MOD_ALT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOD_SUPER 
    REGISTER_LONG_CONSTANT("GLFW_MOD_SUPER", GLFW_MOD_SUPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_1 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_1", GLFW_MOUSE_BUTTON_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_2 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_2", GLFW_MOUSE_BUTTON_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_3 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_3", GLFW_MOUSE_BUTTON_3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_4 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_4", GLFW_MOUSE_BUTTON_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_5 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_5", GLFW_MOUSE_BUTTON_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_6 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_6", GLFW_MOUSE_BUTTON_6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_7 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_7", GLFW_MOUSE_BUTTON_7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_8 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_8", GLFW_MOUSE_BUTTON_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_LAST 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_LAST", GLFW_MOUSE_BUTTON_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_LEFT 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_LEFT", GLFW_MOUSE_BUTTON_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_RIGHT 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_RIGHT", GLFW_MOUSE_BUTTON_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_MIDDLE 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_MIDDLE", GLFW_MOUSE_BUTTON_MIDDLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_1 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_1", GLFW_JOYSTICK_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_2 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_2", GLFW_JOYSTICK_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_3 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_3", GLFW_JOYSTICK_3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_4 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_4", GLFW_JOYSTICK_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_5 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_5", GLFW_JOYSTICK_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_6 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_6", GLFW_JOYSTICK_6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_7 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_7", GLFW_JOYSTICK_7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_8 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_8", GLFW_JOYSTICK_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_9 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_9", GLFW_JOYSTICK_9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_10 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_10", GLFW_JOYSTICK_10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_11 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_11", GLFW_JOYSTICK_11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_12 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_12", GLFW_JOYSTICK_12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_13 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_13", GLFW_JOYSTICK_13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_14 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_14", GLFW_JOYSTICK_14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_15 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_15", GLFW_JOYSTICK_15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_16 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_16", GLFW_JOYSTICK_16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_LAST 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_LAST", GLFW_JOYSTICK_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_A 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_A", GLFW_GAMEPAD_BUTTON_A, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_B 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_B", GLFW_GAMEPAD_BUTTON_B, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_X 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_X", GLFW_GAMEPAD_BUTTON_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_Y 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_Y", GLFW_GAMEPAD_BUTTON_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_LEFT_BUMPER 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_LEFT_BUMPER", GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER", GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_BACK 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_BACK", GLFW_GAMEPAD_BUTTON_BACK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_START 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_START", GLFW_GAMEPAD_BUTTON_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_GUIDE 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_GUIDE", GLFW_GAMEPAD_BUTTON_GUIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_LEFT_THUMB 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_LEFT_THUMB", GLFW_GAMEPAD_BUTTON_LEFT_THUMB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_RIGHT_THUMB 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_RIGHT_THUMB", GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_DPAD_UP 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_DPAD_UP", GLFW_GAMEPAD_BUTTON_DPAD_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_DPAD_RIGHT 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_DPAD_RIGHT", GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_DPAD_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_DPAD_DOWN", GLFW_GAMEPAD_BUTTON_DPAD_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_DPAD_LEFT 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_DPAD_LEFT", GLFW_GAMEPAD_BUTTON_DPAD_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_LAST 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_LAST", GLFW_GAMEPAD_BUTTON_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_CROSS 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_CROSS", GLFW_GAMEPAD_BUTTON_CROSS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_CIRCLE 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_CIRCLE", GLFW_GAMEPAD_BUTTON_CIRCLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_SQUARE 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_SQUARE", GLFW_GAMEPAD_BUTTON_SQUARE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_TRIANGLE 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_TRIANGLE", GLFW_GAMEPAD_BUTTON_TRIANGLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_LEFT_X 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_LEFT_X", GLFW_GAMEPAD_AXIS_LEFT_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_LEFT_Y 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_LEFT_Y", GLFW_GAMEPAD_AXIS_LEFT_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_RIGHT_X 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_RIGHT_X", GLFW_GAMEPAD_AXIS_RIGHT_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_RIGHT_Y 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_RIGHT_Y", GLFW_GAMEPAD_AXIS_RIGHT_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_LEFT_TRIGGER 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_LEFT_TRIGGER", GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER", GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_LAST 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_LAST", GLFW_GAMEPAD_AXIS_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_ERROR 
    REGISTER_LONG_CONSTANT("GLFW_NO_ERROR", GLFW_NO_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NOT_INITIALIZED 
    REGISTER_LONG_CONSTANT("GLFW_NOT_INITIALIZED", GLFW_NOT_INITIALIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_CURRENT_CONTEXT 
    REGISTER_LONG_CONSTANT("GLFW_NO_CURRENT_CONTEXT", GLFW_NO_CURRENT_CONTEXT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_INVALID_ENUM 
    REGISTER_LONG_CONSTANT("GLFW_INVALID_ENUM", GLFW_INVALID_ENUM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_INVALID_VALUE 
    REGISTER_LONG_CONSTANT("GLFW_INVALID_VALUE", GLFW_INVALID_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OUT_OF_MEMORY 
    REGISTER_LONG_CONSTANT("GLFW_OUT_OF_MEMORY", GLFW_OUT_OF_MEMORY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_API_UNAVAILABLE 
    REGISTER_LONG_CONSTANT("GLFW_API_UNAVAILABLE", GLFW_API_UNAVAILABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_VERSION_UNAVAILABLE 
    REGISTER_LONG_CONSTANT("GLFW_VERSION_UNAVAILABLE", GLFW_VERSION_UNAVAILABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_PLATFORM_ERROR 
    REGISTER_LONG_CONSTANT("GLFW_PLATFORM_ERROR", GLFW_PLATFORM_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_FORMAT_UNAVAILABLE 
    REGISTER_LONG_CONSTANT("GLFW_FORMAT_UNAVAILABLE", GLFW_FORMAT_UNAVAILABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_WINDOW_CONTEXT 
    REGISTER_LONG_CONSTANT("GLFW_NO_WINDOW_CONTEXT", GLFW_NO_WINDOW_CONTEXT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_FOCUSED 
    REGISTER_LONG_CONSTANT("GLFW_FOCUSED", GLFW_FOCUSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ICONIFIED 
    REGISTER_LONG_CONSTANT("GLFW_ICONIFIED", GLFW_ICONIFIED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RESIZABLE 
    REGISTER_LONG_CONSTANT("GLFW_RESIZABLE", GLFW_RESIZABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_VISIBLE 
    REGISTER_LONG_CONSTANT("GLFW_VISIBLE", GLFW_VISIBLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DECORATED 
    REGISTER_LONG_CONSTANT("GLFW_DECORATED", GLFW_DECORATED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_AUTO_ICONIFY 
    REGISTER_LONG_CONSTANT("GLFW_AUTO_ICONIFY", GLFW_AUTO_ICONIFY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_FLOATING 
    REGISTER_LONG_CONSTANT("GLFW_FLOATING", GLFW_FLOATING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MAXIMIZED 
    REGISTER_LONG_CONSTANT("GLFW_MAXIMIZED", GLFW_MAXIMIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CENTER_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_CENTER_CURSOR", GLFW_CENTER_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RED_BITS 
    REGISTER_LONG_CONSTANT("GLFW_RED_BITS", GLFW_RED_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GREEN_BITS 
    REGISTER_LONG_CONSTANT("GLFW_GREEN_BITS", GLFW_GREEN_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_BLUE_BITS 
    REGISTER_LONG_CONSTANT("GLFW_BLUE_BITS", GLFW_BLUE_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ALPHA_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ALPHA_BITS", GLFW_ALPHA_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DEPTH_BITS 
    REGISTER_LONG_CONSTANT("GLFW_DEPTH_BITS", GLFW_DEPTH_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_STENCIL_BITS 
    REGISTER_LONG_CONSTANT("GLFW_STENCIL_BITS", GLFW_STENCIL_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ACCUM_RED_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ACCUM_RED_BITS", GLFW_ACCUM_RED_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ACCUM_GREEN_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ACCUM_GREEN_BITS", GLFW_ACCUM_GREEN_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ACCUM_BLUE_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ACCUM_BLUE_BITS", GLFW_ACCUM_BLUE_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ACCUM_ALPHA_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ACCUM_ALPHA_BITS", GLFW_ACCUM_ALPHA_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_AUX_BUFFERS 
    REGISTER_LONG_CONSTANT("GLFW_AUX_BUFFERS", GLFW_AUX_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_STEREO 
    REGISTER_LONG_CONSTANT("GLFW_STEREO", GLFW_STEREO, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_SAMPLES 
    REGISTER_LONG_CONSTANT("GLFW_SAMPLES", GLFW_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_SRGB_CAPABLE 
    REGISTER_LONG_CONSTANT("GLFW_SRGB_CAPABLE", GLFW_SRGB_CAPABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_REFRESH_RATE 
    REGISTER_LONG_CONSTANT("GLFW_REFRESH_RATE", GLFW_REFRESH_RATE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DOUBLEBUFFER 
    REGISTER_LONG_CONSTANT("GLFW_DOUBLEBUFFER", GLFW_DOUBLEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CLIENT_API 
    REGISTER_LONG_CONSTANT("GLFW_CLIENT_API", GLFW_CLIENT_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_VERSION_MAJOR 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_VERSION_MAJOR", GLFW_CONTEXT_VERSION_MAJOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_VERSION_MINOR 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_VERSION_MINOR", GLFW_CONTEXT_VERSION_MINOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_REVISION 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_REVISION", GLFW_CONTEXT_REVISION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_ROBUSTNESS 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_ROBUSTNESS", GLFW_CONTEXT_ROBUSTNESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_FORWARD_COMPAT 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_FORWARD_COMPAT", GLFW_OPENGL_FORWARD_COMPAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_DEBUG_CONTEXT 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_DEBUG_CONTEXT", GLFW_OPENGL_DEBUG_CONTEXT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_PROFILE 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_PROFILE", GLFW_OPENGL_PROFILE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_RELEASE_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_RELEASE_BEHAVIOR", GLFW_CONTEXT_RELEASE_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_NO_ERROR 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_NO_ERROR", GLFW_CONTEXT_NO_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_CREATION_API 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_CREATION_API", GLFW_CONTEXT_CREATION_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_RETINA_FRAMEBUFFER 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_RETINA_FRAMEBUFFER", GLFW_COCOA_RETINA_FRAMEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_FRAME_AUTOSAVE 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_FRAME_AUTOSAVE", GLFW_COCOA_FRAME_AUTOSAVE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_GRAPHICS_SWITCHING 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_GRAPHICS_SWITCHING", GLFW_COCOA_GRAPHICS_SWITCHING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_API 
    REGISTER_LONG_CONSTANT("GLFW_NO_API", GLFW_NO_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_API 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_API", GLFW_OPENGL_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_ES_API 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_ES_API", GLFW_OPENGL_ES_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_ROBUSTNESS 
    REGISTER_LONG_CONSTANT("GLFW_NO_ROBUSTNESS", GLFW_NO_ROBUSTNESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_RESET_NOTIFICATION 
    REGISTER_LONG_CONSTANT("GLFW_NO_RESET_NOTIFICATION", GLFW_NO_RESET_NOTIFICATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_LOSE_CONTEXT_ON_RESET 
    REGISTER_LONG_CONSTANT("GLFW_LOSE_CONTEXT_ON_RESET", GLFW_LOSE_CONTEXT_ON_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_ANY_PROFILE 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_ANY_PROFILE", GLFW_OPENGL_ANY_PROFILE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_CORE_PROFILE 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_CORE_PROFILE", GLFW_OPENGL_CORE_PROFILE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_COMPAT_PROFILE 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_COMPAT_PROFILE", GLFW_OPENGL_COMPAT_PROFILE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_CURSOR", GLFW_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_STICKY_KEYS 
    REGISTER_LONG_CONSTANT("GLFW_STICKY_KEYS", GLFW_STICKY_KEYS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_STICKY_MOUSE_BUTTONS 
    REGISTER_LONG_CONSTANT("GLFW_STICKY_MOUSE_BUTTONS", GLFW_STICKY_MOUSE_BUTTONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CURSOR_NORMAL 
    REGISTER_LONG_CONSTANT("GLFW_CURSOR_NORMAL", GLFW_CURSOR_NORMAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CURSOR_HIDDEN 
    REGISTER_LONG_CONSTANT("GLFW_CURSOR_HIDDEN", GLFW_CURSOR_HIDDEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CURSOR_DISABLED 
    REGISTER_LONG_CONSTANT("GLFW_CURSOR_DISABLED", GLFW_CURSOR_DISABLED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ANY_RELEASE_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GLFW_ANY_RELEASE_BEHAVIOR", GLFW_ANY_RELEASE_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RELEASE_BEHAVIOR_FLUSH 
    REGISTER_LONG_CONSTANT("GLFW_RELEASE_BEHAVIOR_FLUSH", GLFW_RELEASE_BEHAVIOR_FLUSH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RELEASE_BEHAVIOR_NONE 
    REGISTER_LONG_CONSTANT("GLFW_RELEASE_BEHAVIOR_NONE", GLFW_RELEASE_BEHAVIOR_NONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NATIVE_CONTEXT_API 
    REGISTER_LONG_CONSTANT("GLFW_NATIVE_CONTEXT_API", GLFW_NATIVE_CONTEXT_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_EGL_CONTEXT_API 
    REGISTER_LONG_CONSTANT("GLFW_EGL_CONTEXT_API", GLFW_EGL_CONTEXT_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OSMESA_CONTEXT_API 
    REGISTER_LONG_CONSTANT("GLFW_OSMESA_CONTEXT_API", GLFW_OSMESA_CONTEXT_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ARROW_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_ARROW_CURSOR", GLFW_ARROW_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_IBEAM_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_IBEAM_CURSOR", GLFW_IBEAM_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CROSSHAIR_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_CROSSHAIR_CURSOR", GLFW_CROSSHAIR_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAND_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_HAND_CURSOR", GLFW_HAND_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HRESIZE_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_HRESIZE_CURSOR", GLFW_HRESIZE_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_VRESIZE_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_VRESIZE_CURSOR", GLFW_VRESIZE_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONNECTED 
    REGISTER_LONG_CONSTANT("GLFW_CONNECTED", GLFW_CONNECTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DISCONNECTED 
    REGISTER_LONG_CONSTANT("GLFW_DISCONNECTED", GLFW_DISCONNECTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_HAT_BUTTONS 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_HAT_BUTTONS", GLFW_JOYSTICK_HAT_BUTTONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_CHDIR_RESOURCES 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_CHDIR_RESOURCES", GLFW_COCOA_CHDIR_RESOURCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_MENUBAR 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_MENUBAR", GLFW_COCOA_MENUBAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_X11_WM_CLASS_NAME 
    REGISTER_LONG_CONSTANT("GLFW_X11_WM_CLASS_NAME", GLFW_X11_WM_CLASS_NAME, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_X11_WM_CLASS_CLASS 
    REGISTER_LONG_CONSTANT("GLFW_X11_WM_CLASS_CLASS", GLFW_X11_WM_CLASS_CLASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_BUFFER_BIT 
    REGISTER_LONG_CONSTANT("GL_DEPTH_BUFFER_BIT", GL_DEPTH_BUFFER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BUFFER_BIT 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BUFFER_BIT", GL_STENCIL_BUFFER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_BUFFER_BIT 
    REGISTER_LONG_CONSTANT("GL_COLOR_BUFFER_BIT", GL_COLOR_BUFFER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FALSE 
    REGISTER_LONG_CONSTANT("GL_FALSE", GL_FALSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRUE 
    REGISTER_LONG_CONSTANT("GL_TRUE", GL_TRUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINTS 
    REGISTER_LONG_CONSTANT("GL_POINTS", GL_POINTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINES 
    REGISTER_LONG_CONSTANT("GL_LINES", GL_LINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_LOOP 
    REGISTER_LONG_CONSTANT("GL_LINE_LOOP", GL_LINE_LOOP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_STRIP 
    REGISTER_LONG_CONSTANT("GL_LINE_STRIP", GL_LINE_STRIP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLES 
    REGISTER_LONG_CONSTANT("GL_TRIANGLES", GL_TRIANGLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLE_STRIP 
    REGISTER_LONG_CONSTANT("GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLE_FAN 
    REGISTER_LONG_CONSTANT("GL_TRIANGLE_FAN", GL_TRIANGLE_FAN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEVER 
    REGISTER_LONG_CONSTANT("GL_NEVER", GL_NEVER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LESS 
    REGISTER_LONG_CONSTANT("GL_LESS", GL_LESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_EQUAL 
    REGISTER_LONG_CONSTANT("GL_EQUAL", GL_EQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LEQUAL 
    REGISTER_LONG_CONSTANT("GL_LEQUAL", GL_LEQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GREATER 
    REGISTER_LONG_CONSTANT("GL_GREATER", GL_GREATER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NOTEQUAL 
    REGISTER_LONG_CONSTANT("GL_NOTEQUAL", GL_NOTEQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEQUAL 
    REGISTER_LONG_CONSTANT("GL_GEQUAL", GL_GEQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALWAYS 
    REGISTER_LONG_CONSTANT("GL_ALWAYS", GL_ALWAYS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ZERO 
    REGISTER_LONG_CONSTANT("GL_ZERO", GL_ZERO, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE 
    REGISTER_LONG_CONSTANT("GL_ONE", GL_ONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC_COLOR 
    REGISTER_LONG_CONSTANT("GL_SRC_COLOR", GL_SRC_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_SRC_COLOR 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_SRC_COLOR", GL_ONE_MINUS_SRC_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC_ALPHA 
    REGISTER_LONG_CONSTANT("GL_SRC_ALPHA", GL_SRC_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_SRC_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DST_ALPHA 
    REGISTER_LONG_CONSTANT("GL_DST_ALPHA", GL_DST_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_DST_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DST_COLOR 
    REGISTER_LONG_CONSTANT("GL_DST_COLOR", GL_DST_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_DST_COLOR 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_DST_COLOR", GL_ONE_MINUS_DST_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC_ALPHA_SATURATE 
    REGISTER_LONG_CONSTANT("GL_SRC_ALPHA_SATURATE", GL_SRC_ALPHA_SATURATE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NONE 
    REGISTER_LONG_CONSTANT("GL_NONE", GL_NONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT_LEFT 
    REGISTER_LONG_CONSTANT("GL_FRONT_LEFT", GL_FRONT_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT_RIGHT 
    REGISTER_LONG_CONSTANT("GL_FRONT_RIGHT", GL_FRONT_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BACK_LEFT 
    REGISTER_LONG_CONSTANT("GL_BACK_LEFT", GL_BACK_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BACK_RIGHT 
    REGISTER_LONG_CONSTANT("GL_BACK_RIGHT", GL_BACK_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT 
    REGISTER_LONG_CONSTANT("GL_FRONT", GL_FRONT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BACK 
    REGISTER_LONG_CONSTANT("GL_BACK", GL_BACK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LEFT 
    REGISTER_LONG_CONSTANT("GL_LEFT", GL_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RIGHT 
    REGISTER_LONG_CONSTANT("GL_RIGHT", GL_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT_AND_BACK 
    REGISTER_LONG_CONSTANT("GL_FRONT_AND_BACK", GL_FRONT_AND_BACK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NO_ERROR 
    REGISTER_LONG_CONSTANT("GL_NO_ERROR", GL_NO_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_ENUM 
    REGISTER_LONG_CONSTANT("GL_INVALID_ENUM", GL_INVALID_ENUM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_VALUE 
    REGISTER_LONG_CONSTANT("GL_INVALID_VALUE", GL_INVALID_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_OPERATION 
    REGISTER_LONG_CONSTANT("GL_INVALID_OPERATION", GL_INVALID_OPERATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OUT_OF_MEMORY 
    REGISTER_LONG_CONSTANT("GL_OUT_OF_MEMORY", GL_OUT_OF_MEMORY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CW 
    REGISTER_LONG_CONSTANT("GL_CW", GL_CW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CCW 
    REGISTER_LONG_CONSTANT("GL_CCW", GL_CCW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_SIZE 
    REGISTER_LONG_CONSTANT("GL_POINT_SIZE", GL_POINT_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_SIZE_RANGE 
    REGISTER_LONG_CONSTANT("GL_POINT_SIZE_RANGE", GL_POINT_SIZE_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_SIZE_GRANULARITY 
    REGISTER_LONG_CONSTANT("GL_POINT_SIZE_GRANULARITY", GL_POINT_SIZE_GRANULARITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_SMOOTH 
    REGISTER_LONG_CONSTANT("GL_LINE_SMOOTH", GL_LINE_SMOOTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_WIDTH 
    REGISTER_LONG_CONSTANT("GL_LINE_WIDTH", GL_LINE_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_WIDTH_RANGE 
    REGISTER_LONG_CONSTANT("GL_LINE_WIDTH_RANGE", GL_LINE_WIDTH_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_WIDTH_GRANULARITY 
    REGISTER_LONG_CONSTANT("GL_LINE_WIDTH_GRANULARITY", GL_LINE_WIDTH_GRANULARITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_MODE 
    REGISTER_LONG_CONSTANT("GL_POLYGON_MODE", GL_POLYGON_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_SMOOTH 
    REGISTER_LONG_CONSTANT("GL_POLYGON_SMOOTH", GL_POLYGON_SMOOTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CULL_FACE 
    REGISTER_LONG_CONSTANT("GL_CULL_FACE", GL_CULL_FACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CULL_FACE_MODE 
    REGISTER_LONG_CONSTANT("GL_CULL_FACE_MODE", GL_CULL_FACE_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT_FACE 
    REGISTER_LONG_CONSTANT("GL_FRONT_FACE", GL_FRONT_FACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_RANGE 
    REGISTER_LONG_CONSTANT("GL_DEPTH_RANGE", GL_DEPTH_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_TEST 
    REGISTER_LONG_CONSTANT("GL_DEPTH_TEST", GL_DEPTH_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_WRITEMASK 
    REGISTER_LONG_CONSTANT("GL_DEPTH_WRITEMASK", GL_DEPTH_WRITEMASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_CLEAR_VALUE 
    REGISTER_LONG_CONSTANT("GL_DEPTH_CLEAR_VALUE", GL_DEPTH_CLEAR_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_FUNC 
    REGISTER_LONG_CONSTANT("GL_DEPTH_FUNC", GL_DEPTH_FUNC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_TEST 
    REGISTER_LONG_CONSTANT("GL_STENCIL_TEST", GL_STENCIL_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_CLEAR_VALUE 
    REGISTER_LONG_CONSTANT("GL_STENCIL_CLEAR_VALUE", GL_STENCIL_CLEAR_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_FUNC 
    REGISTER_LONG_CONSTANT("GL_STENCIL_FUNC", GL_STENCIL_FUNC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_VALUE_MASK 
    REGISTER_LONG_CONSTANT("GL_STENCIL_VALUE_MASK", GL_STENCIL_VALUE_MASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_FAIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL_FAIL", GL_STENCIL_FAIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_PASS_DEPTH_FAIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL_PASS_DEPTH_FAIL", GL_STENCIL_PASS_DEPTH_FAIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_PASS_DEPTH_PASS 
    REGISTER_LONG_CONSTANT("GL_STENCIL_PASS_DEPTH_PASS", GL_STENCIL_PASS_DEPTH_PASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_REF 
    REGISTER_LONG_CONSTANT("GL_STENCIL_REF", GL_STENCIL_REF, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_WRITEMASK 
    REGISTER_LONG_CONSTANT("GL_STENCIL_WRITEMASK", GL_STENCIL_WRITEMASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEWPORT 
    REGISTER_LONG_CONSTANT("GL_VIEWPORT", GL_VIEWPORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DITHER 
    REGISTER_LONG_CONSTANT("GL_DITHER", GL_DITHER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_DST 
    REGISTER_LONG_CONSTANT("GL_BLEND_DST", GL_BLEND_DST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_SRC 
    REGISTER_LONG_CONSTANT("GL_BLEND_SRC", GL_BLEND_SRC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND 
    REGISTER_LONG_CONSTANT("GL_BLEND", GL_BLEND, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOGIC_OP_MODE 
    REGISTER_LONG_CONSTANT("GL_LOGIC_OP_MODE", GL_LOGIC_OP_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER", GL_DRAW_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_BUFFER 
    REGISTER_LONG_CONSTANT("GL_READ_BUFFER", GL_READ_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SCISSOR_BOX 
    REGISTER_LONG_CONSTANT("GL_SCISSOR_BOX", GL_SCISSOR_BOX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SCISSOR_TEST 
    REGISTER_LONG_CONSTANT("GL_SCISSOR_TEST", GL_SCISSOR_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_CLEAR_VALUE 
    REGISTER_LONG_CONSTANT("GL_COLOR_CLEAR_VALUE", GL_COLOR_CLEAR_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_WRITEMASK 
    REGISTER_LONG_CONSTANT("GL_COLOR_WRITEMASK", GL_COLOR_WRITEMASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLEBUFFER 
    REGISTER_LONG_CONSTANT("GL_DOUBLEBUFFER", GL_DOUBLEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STEREO 
    REGISTER_LONG_CONSTANT("GL_STEREO", GL_STEREO, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_SMOOTH_HINT 
    REGISTER_LONG_CONSTANT("GL_LINE_SMOOTH_HINT", GL_LINE_SMOOTH_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_SMOOTH_HINT 
    REGISTER_LONG_CONSTANT("GL_POLYGON_SMOOTH_HINT", GL_POLYGON_SMOOTH_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_SWAP_BYTES 
    REGISTER_LONG_CONSTANT("GL_UNPACK_SWAP_BYTES", GL_UNPACK_SWAP_BYTES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_LSB_FIRST 
    REGISTER_LONG_CONSTANT("GL_UNPACK_LSB_FIRST", GL_UNPACK_LSB_FIRST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_ROW_LENGTH 
    REGISTER_LONG_CONSTANT("GL_UNPACK_ROW_LENGTH", GL_UNPACK_ROW_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_SKIP_ROWS 
    REGISTER_LONG_CONSTANT("GL_UNPACK_SKIP_ROWS", GL_UNPACK_SKIP_ROWS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_SKIP_PIXELS 
    REGISTER_LONG_CONSTANT("GL_UNPACK_SKIP_PIXELS", GL_UNPACK_SKIP_PIXELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_UNPACK_ALIGNMENT", GL_UNPACK_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_SWAP_BYTES 
    REGISTER_LONG_CONSTANT("GL_PACK_SWAP_BYTES", GL_PACK_SWAP_BYTES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_LSB_FIRST 
    REGISTER_LONG_CONSTANT("GL_PACK_LSB_FIRST", GL_PACK_LSB_FIRST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_ROW_LENGTH 
    REGISTER_LONG_CONSTANT("GL_PACK_ROW_LENGTH", GL_PACK_ROW_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_SKIP_ROWS 
    REGISTER_LONG_CONSTANT("GL_PACK_SKIP_ROWS", GL_PACK_SKIP_ROWS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_SKIP_PIXELS 
    REGISTER_LONG_CONSTANT("GL_PACK_SKIP_PIXELS", GL_PACK_SKIP_PIXELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_PACK_ALIGNMENT", GL_PACK_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_SIZE", GL_MAX_TEXTURE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VIEWPORT_DIMS 
    REGISTER_LONG_CONSTANT("GL_MAX_VIEWPORT_DIMS", GL_MAX_VIEWPORT_DIMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SUBPIXEL_BITS 
    REGISTER_LONG_CONSTANT("GL_SUBPIXEL_BITS", GL_SUBPIXEL_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_1D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_1D", GL_TEXTURE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_2D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_2D", GL_TEXTURE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_WIDTH 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_WIDTH", GL_TEXTURE_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_HEIGHT", GL_TEXTURE_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BORDER_COLOR 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BORDER_COLOR", GL_TEXTURE_BORDER_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DONT_CARE 
    REGISTER_LONG_CONSTANT("GL_DONT_CARE", GL_DONT_CARE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FASTEST 
    REGISTER_LONG_CONSTANT("GL_FASTEST", GL_FASTEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NICEST 
    REGISTER_LONG_CONSTANT("GL_NICEST", GL_NICEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BYTE 
    REGISTER_LONG_CONSTANT("GL_BYTE", GL_BYTE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_BYTE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_BYTE", GL_UNSIGNED_BYTE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHORT 
    REGISTER_LONG_CONSTANT("GL_SHORT", GL_SHORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT", GL_UNSIGNED_SHORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT 
    REGISTER_LONG_CONSTANT("GL_INT", GL_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT", GL_UNSIGNED_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT 
    REGISTER_LONG_CONSTANT("GL_FLOAT", GL_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLEAR 
    REGISTER_LONG_CONSTANT("GL_CLEAR", GL_CLEAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_AND 
    REGISTER_LONG_CONSTANT("GL_AND", GL_AND, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_AND_REVERSE 
    REGISTER_LONG_CONSTANT("GL_AND_REVERSE", GL_AND_REVERSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY 
    REGISTER_LONG_CONSTANT("GL_COPY", GL_COPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_AND_INVERTED 
    REGISTER_LONG_CONSTANT("GL_AND_INVERTED", GL_AND_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NOOP 
    REGISTER_LONG_CONSTANT("GL_NOOP", GL_NOOP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_XOR 
    REGISTER_LONG_CONSTANT("GL_XOR", GL_XOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OR 
    REGISTER_LONG_CONSTANT("GL_OR", GL_OR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NOR 
    REGISTER_LONG_CONSTANT("GL_NOR", GL_NOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_EQUIV 
    REGISTER_LONG_CONSTANT("GL_EQUIV", GL_EQUIV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVERT 
    REGISTER_LONG_CONSTANT("GL_INVERT", GL_INVERT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OR_REVERSE 
    REGISTER_LONG_CONSTANT("GL_OR_REVERSE", GL_OR_REVERSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_INVERTED 
    REGISTER_LONG_CONSTANT("GL_COPY_INVERTED", GL_COPY_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OR_INVERTED 
    REGISTER_LONG_CONSTANT("GL_OR_INVERTED", GL_OR_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NAND 
    REGISTER_LONG_CONSTANT("GL_NAND", GL_NAND, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SET 
    REGISTER_LONG_CONSTANT("GL_SET", GL_SET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE", GL_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR 
    REGISTER_LONG_CONSTANT("GL_COLOR", GL_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH 
    REGISTER_LONG_CONSTANT("GL_DEPTH", GL_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL", GL_STENCIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX", GL_STENCIL_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT", GL_DEPTH_COMPONENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RED 
    REGISTER_LONG_CONSTANT("GL_RED", GL_RED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GREEN 
    REGISTER_LONG_CONSTANT("GL_GREEN", GL_GREEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLUE 
    REGISTER_LONG_CONSTANT("GL_BLUE", GL_BLUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ALPHA", GL_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB 
    REGISTER_LONG_CONSTANT("GL_RGB", GL_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA 
    REGISTER_LONG_CONSTANT("GL_RGBA", GL_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT 
    REGISTER_LONG_CONSTANT("GL_POINT", GL_POINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE 
    REGISTER_LONG_CONSTANT("GL_LINE", GL_LINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FILL 
    REGISTER_LONG_CONSTANT("GL_FILL", GL_FILL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_KEEP 
    REGISTER_LONG_CONSTANT("GL_KEEP", GL_KEEP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REPLACE 
    REGISTER_LONG_CONSTANT("GL_REPLACE", GL_REPLACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INCR 
    REGISTER_LONG_CONSTANT("GL_INCR", GL_INCR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DECR 
    REGISTER_LONG_CONSTANT("GL_DECR", GL_DECR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VENDOR 
    REGISTER_LONG_CONSTANT("GL_VENDOR", GL_VENDOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERER 
    REGISTER_LONG_CONSTANT("GL_RENDERER", GL_RENDERER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERSION 
    REGISTER_LONG_CONSTANT("GL_VERSION", GL_VERSION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_EXTENSIONS 
    REGISTER_LONG_CONSTANT("GL_EXTENSIONS", GL_EXTENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEAREST 
    REGISTER_LONG_CONSTANT("GL_NEAREST", GL_NEAREST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINEAR 
    REGISTER_LONG_CONSTANT("GL_LINEAR", GL_LINEAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEAREST_MIPMAP_NEAREST 
    REGISTER_LONG_CONSTANT("GL_NEAREST_MIPMAP_NEAREST", GL_NEAREST_MIPMAP_NEAREST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINEAR_MIPMAP_NEAREST 
    REGISTER_LONG_CONSTANT("GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEAREST_MIPMAP_LINEAR 
    REGISTER_LONG_CONSTANT("GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINEAR_MIPMAP_LINEAR 
    REGISTER_LONG_CONSTANT("GL_LINEAR_MIPMAP_LINEAR", GL_LINEAR_MIPMAP_LINEAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MAG_FILTER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MAG_FILTER", GL_TEXTURE_MAG_FILTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MIN_FILTER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MIN_FILTER", GL_TEXTURE_MIN_FILTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_WRAP_S 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_WRAP_S", GL_TEXTURE_WRAP_S, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_WRAP_T 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_WRAP_T", GL_TEXTURE_WRAP_T, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REPEAT 
    REGISTER_LONG_CONSTANT("GL_REPEAT", GL_REPEAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_LOGIC_OP 
    REGISTER_LONG_CONSTANT("GL_COLOR_LOGIC_OP", GL_COLOR_LOGIC_OP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_UNITS 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_UNITS", GL_POLYGON_OFFSET_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_POINT 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_POINT", GL_POLYGON_OFFSET_POINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_LINE 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_LINE", GL_POLYGON_OFFSET_LINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_FILL 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_FILL", GL_POLYGON_OFFSET_FILL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_FACTOR 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_FACTOR", GL_POLYGON_OFFSET_FACTOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_1D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_1D", GL_TEXTURE_BINDING_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_2D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_2D", GL_TEXTURE_BINDING_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_INTERNAL_FORMAT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_INTERNAL_FORMAT", GL_TEXTURE_INTERNAL_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_RED_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_RED_SIZE", GL_TEXTURE_RED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_GREEN_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_GREEN_SIZE", GL_TEXTURE_GREEN_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BLUE_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BLUE_SIZE", GL_TEXTURE_BLUE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_ALPHA_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_ALPHA_SIZE", GL_TEXTURE_ALPHA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE 
    REGISTER_LONG_CONSTANT("GL_DOUBLE", GL_DOUBLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_1D 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_1D", GL_PROXY_TEXTURE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_2D 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_2D", GL_PROXY_TEXTURE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R3_G3_B2 
    REGISTER_LONG_CONSTANT("GL_R3_G3_B2", GL_R3_G3_B2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB4 
    REGISTER_LONG_CONSTANT("GL_RGB4", GL_RGB4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB5 
    REGISTER_LONG_CONSTANT("GL_RGB5", GL_RGB5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB8 
    REGISTER_LONG_CONSTANT("GL_RGB8", GL_RGB8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB10 
    REGISTER_LONG_CONSTANT("GL_RGB10", GL_RGB10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB12 
    REGISTER_LONG_CONSTANT("GL_RGB12", GL_RGB12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16 
    REGISTER_LONG_CONSTANT("GL_RGB16", GL_RGB16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA2 
    REGISTER_LONG_CONSTANT("GL_RGBA2", GL_RGBA2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA4 
    REGISTER_LONG_CONSTANT("GL_RGBA4", GL_RGBA4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB5_A1 
    REGISTER_LONG_CONSTANT("GL_RGB5_A1", GL_RGB5_A1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA8 
    REGISTER_LONG_CONSTANT("GL_RGBA8", GL_RGBA8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB10_A2 
    REGISTER_LONG_CONSTANT("GL_RGB10_A2", GL_RGB10_A2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA12 
    REGISTER_LONG_CONSTANT("GL_RGBA12", GL_RGBA12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16 
    REGISTER_LONG_CONSTANT("GL_RGBA16", GL_RGBA16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_BYTE_3_3_2 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_BYTE_3_3_2", GL_UNSIGNED_BYTE_3_3_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_4_4_4_4 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_4_4_4_4", GL_UNSIGNED_SHORT_4_4_4_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_5_5_5_1 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_5_5_5_1", GL_UNSIGNED_SHORT_5_5_5_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_8_8_8_8 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_8_8_8_8", GL_UNSIGNED_INT_8_8_8_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_10_10_10_2 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_10_10_10_2", GL_UNSIGNED_INT_10_10_10_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_3D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_3D", GL_TEXTURE_BINDING_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_SKIP_IMAGES 
    REGISTER_LONG_CONSTANT("GL_PACK_SKIP_IMAGES", GL_PACK_SKIP_IMAGES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_IMAGE_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_PACK_IMAGE_HEIGHT", GL_PACK_IMAGE_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_SKIP_IMAGES 
    REGISTER_LONG_CONSTANT("GL_UNPACK_SKIP_IMAGES", GL_UNPACK_SKIP_IMAGES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_IMAGE_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_UNPACK_IMAGE_HEIGHT", GL_UNPACK_IMAGE_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_3D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_3D", GL_TEXTURE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_3D 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_3D", GL_PROXY_TEXTURE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_DEPTH 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_DEPTH", GL_TEXTURE_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_WRAP_R 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_WRAP_R", GL_TEXTURE_WRAP_R, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_3D_TEXTURE_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_3D_TEXTURE_SIZE", GL_MAX_3D_TEXTURE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_BYTE_2_3_3_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_BYTE_2_3_3_REV", GL_UNSIGNED_BYTE_2_3_3_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_5_6_5 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_5_6_5", GL_UNSIGNED_SHORT_5_6_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_5_6_5_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_5_6_5_REV", GL_UNSIGNED_SHORT_5_6_5_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_4_4_4_4_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_4_4_4_4_REV", GL_UNSIGNED_SHORT_4_4_4_4_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_1_5_5_5_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_1_5_5_5_REV", GL_UNSIGNED_SHORT_1_5_5_5_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_8_8_8_8_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_8_8_8_8_REV", GL_UNSIGNED_INT_8_8_8_8_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_2_10_10_10_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_2_10_10_10_REV", GL_UNSIGNED_INT_2_10_10_10_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BGR 
    REGISTER_LONG_CONSTANT("GL_BGR", GL_BGR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BGRA 
    REGISTER_LONG_CONSTANT("GL_BGRA", GL_BGRA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ELEMENTS_VERTICES 
    REGISTER_LONG_CONSTANT("GL_MAX_ELEMENTS_VERTICES", GL_MAX_ELEMENTS_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ELEMENTS_INDICES 
    REGISTER_LONG_CONSTANT("GL_MAX_ELEMENTS_INDICES", GL_MAX_ELEMENTS_INDICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLAMP_TO_EDGE 
    REGISTER_LONG_CONSTANT("GL_CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MIN_LOD 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MIN_LOD", GL_TEXTURE_MIN_LOD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MAX_LOD 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MAX_LOD", GL_TEXTURE_MAX_LOD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BASE_LEVEL 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BASE_LEVEL", GL_TEXTURE_BASE_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MAX_LEVEL 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MAX_LEVEL", GL_TEXTURE_MAX_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SMOOTH_POINT_SIZE_RANGE 
    REGISTER_LONG_CONSTANT("GL_SMOOTH_POINT_SIZE_RANGE", GL_SMOOTH_POINT_SIZE_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SMOOTH_POINT_SIZE_GRANULARITY 
    REGISTER_LONG_CONSTANT("GL_SMOOTH_POINT_SIZE_GRANULARITY", GL_SMOOTH_POINT_SIZE_GRANULARITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SMOOTH_LINE_WIDTH_RANGE 
    REGISTER_LONG_CONSTANT("GL_SMOOTH_LINE_WIDTH_RANGE", GL_SMOOTH_LINE_WIDTH_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SMOOTH_LINE_WIDTH_GRANULARITY 
    REGISTER_LONG_CONSTANT("GL_SMOOTH_LINE_WIDTH_GRANULARITY", GL_SMOOTH_LINE_WIDTH_GRANULARITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALIASED_LINE_WIDTH_RANGE 
    REGISTER_LONG_CONSTANT("GL_ALIASED_LINE_WIDTH_RANGE", GL_ALIASED_LINE_WIDTH_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE0 
    REGISTER_LONG_CONSTANT("GL_TEXTURE0", GL_TEXTURE0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE1 
    REGISTER_LONG_CONSTANT("GL_TEXTURE1", GL_TEXTURE1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE2 
    REGISTER_LONG_CONSTANT("GL_TEXTURE2", GL_TEXTURE2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE3 
    REGISTER_LONG_CONSTANT("GL_TEXTURE3", GL_TEXTURE3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE4 
    REGISTER_LONG_CONSTANT("GL_TEXTURE4", GL_TEXTURE4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE5 
    REGISTER_LONG_CONSTANT("GL_TEXTURE5", GL_TEXTURE5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE6 
    REGISTER_LONG_CONSTANT("GL_TEXTURE6", GL_TEXTURE6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE7 
    REGISTER_LONG_CONSTANT("GL_TEXTURE7", GL_TEXTURE7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE8 
    REGISTER_LONG_CONSTANT("GL_TEXTURE8", GL_TEXTURE8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE9 
    REGISTER_LONG_CONSTANT("GL_TEXTURE9", GL_TEXTURE9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE10 
    REGISTER_LONG_CONSTANT("GL_TEXTURE10", GL_TEXTURE10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE11 
    REGISTER_LONG_CONSTANT("GL_TEXTURE11", GL_TEXTURE11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE12 
    REGISTER_LONG_CONSTANT("GL_TEXTURE12", GL_TEXTURE12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE13 
    REGISTER_LONG_CONSTANT("GL_TEXTURE13", GL_TEXTURE13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE14 
    REGISTER_LONG_CONSTANT("GL_TEXTURE14", GL_TEXTURE14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE15 
    REGISTER_LONG_CONSTANT("GL_TEXTURE15", GL_TEXTURE15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE16 
    REGISTER_LONG_CONSTANT("GL_TEXTURE16", GL_TEXTURE16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE17 
    REGISTER_LONG_CONSTANT("GL_TEXTURE17", GL_TEXTURE17, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE18 
    REGISTER_LONG_CONSTANT("GL_TEXTURE18", GL_TEXTURE18, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE19 
    REGISTER_LONG_CONSTANT("GL_TEXTURE19", GL_TEXTURE19, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE20 
    REGISTER_LONG_CONSTANT("GL_TEXTURE20", GL_TEXTURE20, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE21 
    REGISTER_LONG_CONSTANT("GL_TEXTURE21", GL_TEXTURE21, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE22 
    REGISTER_LONG_CONSTANT("GL_TEXTURE22", GL_TEXTURE22, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE23 
    REGISTER_LONG_CONSTANT("GL_TEXTURE23", GL_TEXTURE23, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE24 
    REGISTER_LONG_CONSTANT("GL_TEXTURE24", GL_TEXTURE24, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE25 
    REGISTER_LONG_CONSTANT("GL_TEXTURE25", GL_TEXTURE25, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE26 
    REGISTER_LONG_CONSTANT("GL_TEXTURE26", GL_TEXTURE26, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE27 
    REGISTER_LONG_CONSTANT("GL_TEXTURE27", GL_TEXTURE27, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE28 
    REGISTER_LONG_CONSTANT("GL_TEXTURE28", GL_TEXTURE28, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE29 
    REGISTER_LONG_CONSTANT("GL_TEXTURE29", GL_TEXTURE29, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE30 
    REGISTER_LONG_CONSTANT("GL_TEXTURE30", GL_TEXTURE30, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE31 
    REGISTER_LONG_CONSTANT("GL_TEXTURE31", GL_TEXTURE31, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_TEXTURE", GL_ACTIVE_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_MULTISAMPLE", GL_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_ALPHA_TO_COVERAGE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_ALPHA_TO_COVERAGE", GL_SAMPLE_ALPHA_TO_COVERAGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_ALPHA_TO_ONE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_ALPHA_TO_ONE", GL_SAMPLE_ALPHA_TO_ONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_COVERAGE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_COVERAGE", GL_SAMPLE_COVERAGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_BUFFERS", GL_SAMPLE_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_SAMPLES", GL_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_COVERAGE_VALUE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_COVERAGE_VALUE", GL_SAMPLE_COVERAGE_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_COVERAGE_INVERT 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_COVERAGE_INVERT", GL_SAMPLE_COVERAGE_INVERT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP", GL_TEXTURE_CUBE_MAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_CUBE_MAP 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_CUBE_MAP", GL_TEXTURE_BINDING_CUBE_MAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_X 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_POSITIVE_X", GL_TEXTURE_CUBE_MAP_POSITIVE_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_X 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_NEGATIVE_X", GL_TEXTURE_CUBE_MAP_NEGATIVE_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_Y 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_POSITIVE_Y", GL_TEXTURE_CUBE_MAP_POSITIVE_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_NEGATIVE_Y", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_Z 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_POSITIVE_Z", GL_TEXTURE_CUBE_MAP_POSITIVE_Z, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_NEGATIVE_Z", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_CUBE_MAP 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_CUBE_MAP", GL_PROXY_TEXTURE_CUBE_MAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_CUBE_MAP_TEXTURE_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_CUBE_MAP_TEXTURE_SIZE", GL_MAX_CUBE_MAP_TEXTURE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB", GL_COMPRESSED_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGBA 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGBA", GL_COMPRESSED_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSION_HINT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSION_HINT", GL_TEXTURE_COMPRESSION_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED_IMAGE_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED_IMAGE_SIZE", GL_TEXTURE_COMPRESSED_IMAGE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED", GL_TEXTURE_COMPRESSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_COMPRESSED_TEXTURE_FORMATS 
    REGISTER_LONG_CONSTANT("GL_NUM_COMPRESSED_TEXTURE_FORMATS", GL_NUM_COMPRESSED_TEXTURE_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_TEXTURE_FORMATS 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_TEXTURE_FORMATS", GL_COMPRESSED_TEXTURE_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLAMP_TO_BORDER 
    REGISTER_LONG_CONSTANT("GL_CLAMP_TO_BORDER", GL_CLAMP_TO_BORDER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_DST_RGB 
    REGISTER_LONG_CONSTANT("GL_BLEND_DST_RGB", GL_BLEND_DST_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_SRC_RGB 
    REGISTER_LONG_CONSTANT("GL_BLEND_SRC_RGB", GL_BLEND_SRC_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_DST_ALPHA 
    REGISTER_LONG_CONSTANT("GL_BLEND_DST_ALPHA", GL_BLEND_DST_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_SRC_ALPHA 
    REGISTER_LONG_CONSTANT("GL_BLEND_SRC_ALPHA", GL_BLEND_SRC_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_FADE_THRESHOLD_SIZE 
    REGISTER_LONG_CONSTANT("GL_POINT_FADE_THRESHOLD_SIZE", GL_POINT_FADE_THRESHOLD_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT16 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT16", GL_DEPTH_COMPONENT16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT24 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT24", GL_DEPTH_COMPONENT24, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT32 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT32", GL_DEPTH_COMPONENT32, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIRRORED_REPEAT 
    REGISTER_LONG_CONSTANT("GL_MIRRORED_REPEAT", GL_MIRRORED_REPEAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_LOD_BIAS 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_LOD_BIAS", GL_MAX_TEXTURE_LOD_BIAS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_LOD_BIAS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_LOD_BIAS", GL_TEXTURE_LOD_BIAS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INCR_WRAP 
    REGISTER_LONG_CONSTANT("GL_INCR_WRAP", GL_INCR_WRAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DECR_WRAP 
    REGISTER_LONG_CONSTANT("GL_DECR_WRAP", GL_DECR_WRAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_DEPTH_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_DEPTH_SIZE", GL_TEXTURE_DEPTH_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPARE_MODE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPARE_MODE", GL_TEXTURE_COMPARE_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPARE_FUNC 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPARE_FUNC", GL_TEXTURE_COMPARE_FUNC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FUNC_ADD 
    REGISTER_LONG_CONSTANT("GL_FUNC_ADD", GL_FUNC_ADD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FUNC_SUBTRACT 
    REGISTER_LONG_CONSTANT("GL_FUNC_SUBTRACT", GL_FUNC_SUBTRACT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FUNC_REVERSE_SUBTRACT 
    REGISTER_LONG_CONSTANT("GL_FUNC_REVERSE_SUBTRACT", GL_FUNC_REVERSE_SUBTRACT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN 
    REGISTER_LONG_CONSTANT("GL_MIN", GL_MIN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX 
    REGISTER_LONG_CONSTANT("GL_MAX", GL_MAX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONSTANT_COLOR 
    REGISTER_LONG_CONSTANT("GL_CONSTANT_COLOR", GL_CONSTANT_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_CONSTANT_COLOR 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_CONSTANT_COLOR", GL_ONE_MINUS_CONSTANT_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONSTANT_ALPHA 
    REGISTER_LONG_CONSTANT("GL_CONSTANT_ALPHA", GL_CONSTANT_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_CONSTANT_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_CONSTANT_ALPHA", GL_ONE_MINUS_CONSTANT_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_SIZE", GL_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_USAGE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_USAGE", GL_BUFFER_USAGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_COUNTER_BITS 
    REGISTER_LONG_CONSTANT("GL_QUERY_COUNTER_BITS", GL_QUERY_COUNTER_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CURRENT_QUERY 
    REGISTER_LONG_CONSTANT("GL_CURRENT_QUERY", GL_CURRENT_QUERY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_RESULT 
    REGISTER_LONG_CONSTANT("GL_QUERY_RESULT", GL_QUERY_RESULT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_RESULT_AVAILABLE 
    REGISTER_LONG_CONSTANT("GL_QUERY_RESULT_AVAILABLE", GL_QUERY_RESULT_AVAILABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ARRAY_BUFFER 
    REGISTER_LONG_CONSTANT("GL_ARRAY_BUFFER", GL_ARRAY_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ELEMENT_ARRAY_BUFFER 
    REGISTER_LONG_CONSTANT("GL_ELEMENT_ARRAY_BUFFER", GL_ELEMENT_ARRAY_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ARRAY_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_ARRAY_BUFFER_BINDING", GL_ARRAY_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ELEMENT_ARRAY_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_ELEMENT_ARRAY_BUFFER_BINDING", GL_ELEMENT_ARRAY_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING", GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_ONLY 
    REGISTER_LONG_CONSTANT("GL_READ_ONLY", GL_READ_ONLY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_WRITE_ONLY 
    REGISTER_LONG_CONSTANT("GL_WRITE_ONLY", GL_WRITE_ONLY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_WRITE 
    REGISTER_LONG_CONSTANT("GL_READ_WRITE", GL_READ_WRITE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_ACCESS 
    REGISTER_LONG_CONSTANT("GL_BUFFER_ACCESS", GL_BUFFER_ACCESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_MAPPED 
    REGISTER_LONG_CONSTANT("GL_BUFFER_MAPPED", GL_BUFFER_MAPPED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_MAP_POINTER 
    REGISTER_LONG_CONSTANT("GL_BUFFER_MAP_POINTER", GL_BUFFER_MAP_POINTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STREAM_DRAW 
    REGISTER_LONG_CONSTANT("GL_STREAM_DRAW", GL_STREAM_DRAW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STREAM_READ 
    REGISTER_LONG_CONSTANT("GL_STREAM_READ", GL_STREAM_READ, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STREAM_COPY 
    REGISTER_LONG_CONSTANT("GL_STREAM_COPY", GL_STREAM_COPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STATIC_DRAW 
    REGISTER_LONG_CONSTANT("GL_STATIC_DRAW", GL_STATIC_DRAW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STATIC_READ 
    REGISTER_LONG_CONSTANT("GL_STATIC_READ", GL_STATIC_READ, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STATIC_COPY 
    REGISTER_LONG_CONSTANT("GL_STATIC_COPY", GL_STATIC_COPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DYNAMIC_DRAW 
    REGISTER_LONG_CONSTANT("GL_DYNAMIC_DRAW", GL_DYNAMIC_DRAW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DYNAMIC_READ 
    REGISTER_LONG_CONSTANT("GL_DYNAMIC_READ", GL_DYNAMIC_READ, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DYNAMIC_COPY 
    REGISTER_LONG_CONSTANT("GL_DYNAMIC_COPY", GL_DYNAMIC_COPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLES_PASSED 
    REGISTER_LONG_CONSTANT("GL_SAMPLES_PASSED", GL_SAMPLES_PASSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC1_ALPHA 
    REGISTER_LONG_CONSTANT("GL_SRC1_ALPHA", GL_SRC1_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_EQUATION_RGB 
    REGISTER_LONG_CONSTANT("GL_BLEND_EQUATION_RGB", GL_BLEND_EQUATION_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_ENABLED 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_ENABLED", GL_VERTEX_ATTRIB_ARRAY_ENABLED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_SIZE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_SIZE", GL_VERTEX_ATTRIB_ARRAY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_STRIDE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_STRIDE", GL_VERTEX_ATTRIB_ARRAY_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_TYPE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_TYPE", GL_VERTEX_ATTRIB_ARRAY_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CURRENT_VERTEX_ATTRIB 
    REGISTER_LONG_CONSTANT("GL_CURRENT_VERTEX_ATTRIB", GL_CURRENT_VERTEX_ATTRIB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_PROGRAM_POINT_SIZE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_PROGRAM_POINT_SIZE", GL_VERTEX_PROGRAM_POINT_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_POINTER 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_POINTER", GL_VERTEX_ATTRIB_ARRAY_POINTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_FUNC 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_FUNC", GL_STENCIL_BACK_FUNC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_FAIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_FAIL", GL_STENCIL_BACK_FAIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_PASS_DEPTH_FAIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_PASS_DEPTH_FAIL", GL_STENCIL_BACK_PASS_DEPTH_FAIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_PASS_DEPTH_PASS 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_PASS_DEPTH_PASS", GL_STENCIL_BACK_PASS_DEPTH_PASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DRAW_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_DRAW_BUFFERS", GL_MAX_DRAW_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER0 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER0", GL_DRAW_BUFFER0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER1 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER1", GL_DRAW_BUFFER1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER2 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER2", GL_DRAW_BUFFER2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER3 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER3", GL_DRAW_BUFFER3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER4 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER4", GL_DRAW_BUFFER4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER5 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER5", GL_DRAW_BUFFER5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER6 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER6", GL_DRAW_BUFFER6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER7 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER7", GL_DRAW_BUFFER7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER8 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER8", GL_DRAW_BUFFER8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER9 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER9", GL_DRAW_BUFFER9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER10 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER10", GL_DRAW_BUFFER10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER11 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER11", GL_DRAW_BUFFER11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER12 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER12", GL_DRAW_BUFFER12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER13 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER13", GL_DRAW_BUFFER13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER14 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER14", GL_DRAW_BUFFER14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER15 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER15", GL_DRAW_BUFFER15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_EQUATION_ALPHA 
    REGISTER_LONG_CONSTANT("GL_BLEND_EQUATION_ALPHA", GL_BLEND_EQUATION_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATTRIBS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATTRIBS", GL_MAX_VERTEX_ATTRIBS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_NORMALIZED", GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_IMAGE_UNITS", GL_MAX_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SHADER 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SHADER", GL_FRAGMENT_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SHADER 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SHADER", GL_VERTEX_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_UNIFORM_COMPONENTS", GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_UNIFORM_COMPONENTS", GL_MAX_VERTEX_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VARYING_FLOATS 
    REGISTER_LONG_CONSTANT("GL_MAX_VARYING_FLOATS", GL_MAX_VARYING_FLOATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS", GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_TYPE 
    REGISTER_LONG_CONSTANT("GL_SHADER_TYPE", GL_SHADER_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_VEC2 
    REGISTER_LONG_CONSTANT("GL_FLOAT_VEC2", GL_FLOAT_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_VEC3 
    REGISTER_LONG_CONSTANT("GL_FLOAT_VEC3", GL_FLOAT_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_VEC4 
    REGISTER_LONG_CONSTANT("GL_FLOAT_VEC4", GL_FLOAT_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_VEC2 
    REGISTER_LONG_CONSTANT("GL_INT_VEC2", GL_INT_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_VEC3 
    REGISTER_LONG_CONSTANT("GL_INT_VEC3", GL_INT_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_VEC4 
    REGISTER_LONG_CONSTANT("GL_INT_VEC4", GL_INT_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BOOL 
    REGISTER_LONG_CONSTANT("GL_BOOL", GL_BOOL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BOOL_VEC2 
    REGISTER_LONG_CONSTANT("GL_BOOL_VEC2", GL_BOOL_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BOOL_VEC3 
    REGISTER_LONG_CONSTANT("GL_BOOL_VEC3", GL_BOOL_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BOOL_VEC4 
    REGISTER_LONG_CONSTANT("GL_BOOL_VEC4", GL_BOOL_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT2 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT2", GL_FLOAT_MAT2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT3 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT3", GL_FLOAT_MAT3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT4 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT4", GL_FLOAT_MAT4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_1D 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_1D", GL_SAMPLER_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D", GL_SAMPLER_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_3D 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_3D", GL_SAMPLER_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_CUBE 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_CUBE", GL_SAMPLER_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_1D_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_1D_SHADOW", GL_SAMPLER_1D_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_SHADOW", GL_SAMPLER_2D_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DELETE_STATUS 
    REGISTER_LONG_CONSTANT("GL_DELETE_STATUS", GL_DELETE_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPILE_STATUS 
    REGISTER_LONG_CONSTANT("GL_COMPILE_STATUS", GL_COMPILE_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINK_STATUS 
    REGISTER_LONG_CONSTANT("GL_LINK_STATUS", GL_LINK_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VALIDATE_STATUS 
    REGISTER_LONG_CONSTANT("GL_VALIDATE_STATUS", GL_VALIDATE_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INFO_LOG_LENGTH 
    REGISTER_LONG_CONSTANT("GL_INFO_LOG_LENGTH", GL_INFO_LOG_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATTACHED_SHADERS 
    REGISTER_LONG_CONSTANT("GL_ATTACHED_SHADERS", GL_ATTACHED_SHADERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_UNIFORMS", GL_ACTIVE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_UNIFORM_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_UNIFORM_MAX_LENGTH", GL_ACTIVE_UNIFORM_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_SOURCE_LENGTH 
    REGISTER_LONG_CONSTANT("GL_SHADER_SOURCE_LENGTH", GL_SHADER_SOURCE_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_ATTRIBUTES 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_ATTRIBUTES", GL_ACTIVE_ATTRIBUTES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_ATTRIBUTE_MAX_LENGTH", GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SHADER_DERIVATIVE_HINT 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SHADER_DERIVATIVE_HINT", GL_FRAGMENT_SHADER_DERIVATIVE_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADING_LANGUAGE_VERSION 
    REGISTER_LONG_CONSTANT("GL_SHADING_LANGUAGE_VERSION", GL_SHADING_LANGUAGE_VERSION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CURRENT_PROGRAM 
    REGISTER_LONG_CONSTANT("GL_CURRENT_PROGRAM", GL_CURRENT_PROGRAM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_SPRITE_COORD_ORIGIN 
    REGISTER_LONG_CONSTANT("GL_POINT_SPRITE_COORD_ORIGIN", GL_POINT_SPRITE_COORD_ORIGIN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOWER_LEFT 
    REGISTER_LONG_CONSTANT("GL_LOWER_LEFT", GL_LOWER_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UPPER_LEFT 
    REGISTER_LONG_CONSTANT("GL_UPPER_LEFT", GL_UPPER_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_REF 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_REF", GL_STENCIL_BACK_REF, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_VALUE_MASK 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_VALUE_MASK", GL_STENCIL_BACK_VALUE_MASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_WRITEMASK 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_WRITEMASK", GL_STENCIL_BACK_WRITEMASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_PACK_BUFFER 
    REGISTER_LONG_CONSTANT("GL_PIXEL_PACK_BUFFER", GL_PIXEL_PACK_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_UNPACK_BUFFER 
    REGISTER_LONG_CONSTANT("GL_PIXEL_UNPACK_BUFFER", GL_PIXEL_UNPACK_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_PACK_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_PIXEL_PACK_BUFFER_BINDING", GL_PIXEL_PACK_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_UNPACK_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_PIXEL_UNPACK_BUFFER_BINDING", GL_PIXEL_UNPACK_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT2x3 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT2x3", GL_FLOAT_MAT2x3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT2x4 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT2x4", GL_FLOAT_MAT2x4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT3x2 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT3x2", GL_FLOAT_MAT3x2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT3x4 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT3x4", GL_FLOAT_MAT3x4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT4x2 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT4x2", GL_FLOAT_MAT4x2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT4x3 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT4x3", GL_FLOAT_MAT4x3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB 
    REGISTER_LONG_CONSTANT("GL_SRGB", GL_SRGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB8 
    REGISTER_LONG_CONSTANT("GL_SRGB8", GL_SRGB8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB_ALPHA 
    REGISTER_LONG_CONSTANT("GL_SRGB_ALPHA", GL_SRGB_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB8_ALPHA8 
    REGISTER_LONG_CONSTANT("GL_SRGB8_ALPHA8", GL_SRGB8_ALPHA8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB", GL_COMPRESSED_SRGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB_ALPHA 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB_ALPHA", GL_COMPRESSED_SRGB_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPARE_REF_TO_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_COMPARE_REF_TO_TEXTURE", GL_COMPARE_REF_TO_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE0 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE0", GL_CLIP_DISTANCE0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE1 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE1", GL_CLIP_DISTANCE1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE2 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE2", GL_CLIP_DISTANCE2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE3 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE3", GL_CLIP_DISTANCE3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE4 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE4", GL_CLIP_DISTANCE4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE5 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE5", GL_CLIP_DISTANCE5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE6 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE6", GL_CLIP_DISTANCE6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE7 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE7", GL_CLIP_DISTANCE7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_CLIP_DISTANCES 
    REGISTER_LONG_CONSTANT("GL_MAX_CLIP_DISTANCES", GL_MAX_CLIP_DISTANCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAJOR_VERSION 
    REGISTER_LONG_CONSTANT("GL_MAJOR_VERSION", GL_MAJOR_VERSION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MINOR_VERSION 
    REGISTER_LONG_CONSTANT("GL_MINOR_VERSION", GL_MINOR_VERSION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_EXTENSIONS 
    REGISTER_LONG_CONSTANT("GL_NUM_EXTENSIONS", GL_NUM_EXTENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAGS 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAGS", GL_CONTEXT_FLAGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RED 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RED", GL_COMPRESSED_RED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RG 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RG", GL_COMPRESSED_RG, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT", GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA32F 
    REGISTER_LONG_CONSTANT("GL_RGBA32F", GL_RGBA32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB32F 
    REGISTER_LONG_CONSTANT("GL_RGB32F", GL_RGB32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16F 
    REGISTER_LONG_CONSTANT("GL_RGBA16F", GL_RGBA16F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16F 
    REGISTER_LONG_CONSTANT("GL_RGB16F", GL_RGB16F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_INTEGER 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_INTEGER", GL_VERTEX_ATTRIB_ARRAY_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ARRAY_TEXTURE_LAYERS 
    REGISTER_LONG_CONSTANT("GL_MAX_ARRAY_TEXTURE_LAYERS", GL_MAX_ARRAY_TEXTURE_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_PROGRAM_TEXEL_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MIN_PROGRAM_TEXEL_OFFSET", GL_MIN_PROGRAM_TEXEL_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_PROGRAM_TEXEL_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MAX_PROGRAM_TEXEL_OFFSET", GL_MAX_PROGRAM_TEXEL_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLAMP_READ_COLOR 
    REGISTER_LONG_CONSTANT("GL_CLAMP_READ_COLOR", GL_CLAMP_READ_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FIXED_ONLY 
    REGISTER_LONG_CONSTANT("GL_FIXED_ONLY", GL_FIXED_ONLY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VARYING_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_VARYING_COMPONENTS", GL_MAX_VARYING_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_1D_ARRAY", GL_TEXTURE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_1D_ARRAY", GL_PROXY_TEXTURE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_2D_ARRAY", GL_TEXTURE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_2D_ARRAY", GL_PROXY_TEXTURE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_1D_ARRAY", GL_TEXTURE_BINDING_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_2D_ARRAY", GL_TEXTURE_BINDING_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R11F_G11F_B10F 
    REGISTER_LONG_CONSTANT("GL_R11F_G11F_B10F", GL_R11F_G11F_B10F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_10F_11F_11F_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_10F_11F_11F_REV", GL_UNSIGNED_INT_10F_11F_11F_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB9_E5 
    REGISTER_LONG_CONSTANT("GL_RGB9_E5", GL_RGB9_E5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_5_9_9_9_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_5_9_9_9_REV", GL_UNSIGNED_INT_5_9_9_9_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SHARED_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SHARED_SIZE", GL_TEXTURE_SHARED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH", GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_MODE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_MODE", GL_TRANSFORM_FEEDBACK_BUFFER_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS", GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_VARYINGS 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_VARYINGS", GL_TRANSFORM_FEEDBACK_VARYINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_START 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_START", GL_TRANSFORM_FEEDBACK_BUFFER_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_SIZE", GL_TRANSFORM_FEEDBACK_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVES_GENERATED 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVES_GENERATED", GL_PRIMITIVES_GENERATED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN", GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RASTERIZER_DISCARD 
    REGISTER_LONG_CONSTANT("GL_RASTERIZER_DISCARD", GL_RASTERIZER_DISCARD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS", GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 
    REGISTER_LONG_CONSTANT("GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS", GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERLEAVED_ATTRIBS 
    REGISTER_LONG_CONSTANT("GL_INTERLEAVED_ATTRIBS", GL_INTERLEAVED_ATTRIBS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SEPARATE_ATTRIBS 
    REGISTER_LONG_CONSTANT("GL_SEPARATE_ATTRIBS", GL_SEPARATE_ATTRIBS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER", GL_TRANSFORM_FEEDBACK_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_BINDING", GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA32UI 
    REGISTER_LONG_CONSTANT("GL_RGBA32UI", GL_RGBA32UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB32UI 
    REGISTER_LONG_CONSTANT("GL_RGB32UI", GL_RGB32UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16UI 
    REGISTER_LONG_CONSTANT("GL_RGBA16UI", GL_RGBA16UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16UI 
    REGISTER_LONG_CONSTANT("GL_RGB16UI", GL_RGB16UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA8UI 
    REGISTER_LONG_CONSTANT("GL_RGBA8UI", GL_RGBA8UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB8UI 
    REGISTER_LONG_CONSTANT("GL_RGB8UI", GL_RGB8UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA32I 
    REGISTER_LONG_CONSTANT("GL_RGBA32I", GL_RGBA32I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB32I 
    REGISTER_LONG_CONSTANT("GL_RGB32I", GL_RGB32I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16I 
    REGISTER_LONG_CONSTANT("GL_RGBA16I", GL_RGBA16I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16I 
    REGISTER_LONG_CONSTANT("GL_RGB16I", GL_RGB16I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA8I 
    REGISTER_LONG_CONSTANT("GL_RGBA8I", GL_RGBA8I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB8I 
    REGISTER_LONG_CONSTANT("GL_RGB8I", GL_RGB8I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RED_INTEGER 
    REGISTER_LONG_CONSTANT("GL_RED_INTEGER", GL_RED_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GREEN_INTEGER 
    REGISTER_LONG_CONSTANT("GL_GREEN_INTEGER", GL_GREEN_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLUE_INTEGER 
    REGISTER_LONG_CONSTANT("GL_BLUE_INTEGER", GL_BLUE_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB_INTEGER 
    REGISTER_LONG_CONSTANT("GL_RGB_INTEGER", GL_RGB_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA_INTEGER 
    REGISTER_LONG_CONSTANT("GL_RGBA_INTEGER", GL_RGBA_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BGR_INTEGER 
    REGISTER_LONG_CONSTANT("GL_BGR_INTEGER", GL_BGR_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BGRA_INTEGER 
    REGISTER_LONG_CONSTANT("GL_BGRA_INTEGER", GL_BGRA_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_1D_ARRAY", GL_SAMPLER_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_ARRAY", GL_SAMPLER_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_1D_ARRAY_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_1D_ARRAY_SHADOW", GL_SAMPLER_1D_ARRAY_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_ARRAY_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_ARRAY_SHADOW", GL_SAMPLER_2D_ARRAY_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_CUBE_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_CUBE_SHADOW", GL_SAMPLER_CUBE_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_VEC2 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_VEC2", GL_UNSIGNED_INT_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_VEC3 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_VEC3", GL_UNSIGNED_INT_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_VEC4 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_VEC4", GL_UNSIGNED_INT_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_1D 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_1D", GL_INT_SAMPLER_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D", GL_INT_SAMPLER_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_3D 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_3D", GL_INT_SAMPLER_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_CUBE 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_CUBE", GL_INT_SAMPLER_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_1D_ARRAY", GL_INT_SAMPLER_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D_ARRAY", GL_INT_SAMPLER_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_1D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_1D", GL_UNSIGNED_INT_SAMPLER_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D", GL_UNSIGNED_INT_SAMPLER_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_3D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_3D", GL_UNSIGNED_INT_SAMPLER_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_CUBE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_CUBE", GL_UNSIGNED_INT_SAMPLER_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_1D_ARRAY", GL_UNSIGNED_INT_SAMPLER_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D_ARRAY", GL_UNSIGNED_INT_SAMPLER_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_WAIT", GL_QUERY_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_NO_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_NO_WAIT", GL_QUERY_NO_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BY_REGION_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_BY_REGION_WAIT", GL_QUERY_BY_REGION_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BY_REGION_NO_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_BY_REGION_NO_WAIT", GL_QUERY_BY_REGION_NO_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_ACCESS_FLAGS 
    REGISTER_LONG_CONSTANT("GL_BUFFER_ACCESS_FLAGS", GL_BUFFER_ACCESS_FLAGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_MAP_LENGTH 
    REGISTER_LONG_CONSTANT("GL_BUFFER_MAP_LENGTH", GL_BUFFER_MAP_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_MAP_OFFSET 
    REGISTER_LONG_CONSTANT("GL_BUFFER_MAP_OFFSET", GL_BUFFER_MAP_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT32F 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT32F", GL_DEPTH_COMPONENT32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH32F_STENCIL8 
    REGISTER_LONG_CONSTANT("GL_DEPTH32F_STENCIL8", GL_DEPTH32F_STENCIL8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_32_UNSIGNED_INT_24_8_REV 
    REGISTER_LONG_CONSTANT("GL_FLOAT_32_UNSIGNED_INT_24_8_REV", GL_FLOAT_32_UNSIGNED_INT_24_8_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION 
    REGISTER_LONG_CONSTANT("GL_INVALID_FRAMEBUFFER_OPERATION", GL_INVALID_FRAMEBUFFER_OPERATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING", GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE", GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE", GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE", GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE", GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE", GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE", GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE", GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT", GL_FRAMEBUFFER_DEFAULT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_UNDEFINED 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_UNDEFINED", GL_FRAMEBUFFER_UNDEFINED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_STENCIL_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_DEPTH_STENCIL_ATTACHMENT", GL_DEPTH_STENCIL_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_RENDERBUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_RENDERBUFFER_SIZE", GL_MAX_RENDERBUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_STENCIL 
    REGISTER_LONG_CONSTANT("GL_DEPTH_STENCIL", GL_DEPTH_STENCIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_24_8 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_24_8", GL_UNSIGNED_INT_24_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH24_STENCIL8 
    REGISTER_LONG_CONSTANT("GL_DEPTH24_STENCIL8", GL_DEPTH24_STENCIL8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_STENCIL_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_STENCIL_SIZE", GL_TEXTURE_STENCIL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_RED_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_RED_TYPE", GL_TEXTURE_RED_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_GREEN_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_GREEN_TYPE", GL_TEXTURE_GREEN_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BLUE_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BLUE_TYPE", GL_TEXTURE_BLUE_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_ALPHA_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_ALPHA_TYPE", GL_TEXTURE_ALPHA_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_DEPTH_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_DEPTH_TYPE", GL_TEXTURE_DEPTH_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_NORMALIZED 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_NORMALIZED", GL_UNSIGNED_NORMALIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_BINDING", GL_FRAMEBUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_FRAMEBUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_DRAW_FRAMEBUFFER_BINDING", GL_DRAW_FRAMEBUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_BINDING", GL_RENDERBUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_FRAMEBUFFER 
    REGISTER_LONG_CONSTANT("GL_READ_FRAMEBUFFER", GL_READ_FRAMEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_FRAMEBUFFER 
    REGISTER_LONG_CONSTANT("GL_DRAW_FRAMEBUFFER", GL_DRAW_FRAMEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_FRAMEBUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_READ_FRAMEBUFFER_BINDING", GL_READ_FRAMEBUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_SAMPLES", GL_RENDERBUFFER_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE", GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME", GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL", GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE", GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER", GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_COMPLETE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_COMPLETE", GL_FRAMEBUFFER_COMPLETE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT", GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT", GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER", GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER", GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_UNSUPPORTED 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_UNSUPPORTED", GL_FRAMEBUFFER_UNSUPPORTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COLOR_ATTACHMENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COLOR_ATTACHMENTS", GL_MAX_COLOR_ATTACHMENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT0 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT0", GL_COLOR_ATTACHMENT0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT1 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT1", GL_COLOR_ATTACHMENT1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT2 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT2", GL_COLOR_ATTACHMENT2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT3 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT3", GL_COLOR_ATTACHMENT3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT4 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT4", GL_COLOR_ATTACHMENT4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT5 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT5", GL_COLOR_ATTACHMENT5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT6 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT6", GL_COLOR_ATTACHMENT6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT7 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT7", GL_COLOR_ATTACHMENT7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT8 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT8", GL_COLOR_ATTACHMENT8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT9 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT9", GL_COLOR_ATTACHMENT9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT10 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT10", GL_COLOR_ATTACHMENT10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT11 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT11", GL_COLOR_ATTACHMENT11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT12 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT12", GL_COLOR_ATTACHMENT12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT13 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT13", GL_COLOR_ATTACHMENT13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT14 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT14", GL_COLOR_ATTACHMENT14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT15 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT15", GL_COLOR_ATTACHMENT15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT16 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT16", GL_COLOR_ATTACHMENT16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT17 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT17", GL_COLOR_ATTACHMENT17, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT18 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT18", GL_COLOR_ATTACHMENT18, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT19 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT19", GL_COLOR_ATTACHMENT19, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT20 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT20", GL_COLOR_ATTACHMENT20, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT21 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT21", GL_COLOR_ATTACHMENT21, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT22 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT22", GL_COLOR_ATTACHMENT22, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT23 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT23", GL_COLOR_ATTACHMENT23, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT24 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT24", GL_COLOR_ATTACHMENT24, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT25 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT25", GL_COLOR_ATTACHMENT25, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT26 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT26", GL_COLOR_ATTACHMENT26, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT27 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT27", GL_COLOR_ATTACHMENT27, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT28 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT28", GL_COLOR_ATTACHMENT28, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT29 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT29", GL_COLOR_ATTACHMENT29, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT30 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT30", GL_COLOR_ATTACHMENT30, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT31 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT31", GL_COLOR_ATTACHMENT31, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_DEPTH_ATTACHMENT", GL_DEPTH_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_STENCIL_ATTACHMENT", GL_STENCIL_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER", GL_FRAMEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER", GL_RENDERBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_WIDTH 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_WIDTH", GL_RENDERBUFFER_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_HEIGHT", GL_RENDERBUFFER_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_INTERNAL_FORMAT 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_INTERNAL_FORMAT", GL_RENDERBUFFER_INTERNAL_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX1 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX1", GL_STENCIL_INDEX1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX4 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX4", GL_STENCIL_INDEX4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX8 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX8", GL_STENCIL_INDEX8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX16 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX16", GL_STENCIL_INDEX16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_RED_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_RED_SIZE", GL_RENDERBUFFER_RED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_GREEN_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_GREEN_SIZE", GL_RENDERBUFFER_GREEN_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_BLUE_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_BLUE_SIZE", GL_RENDERBUFFER_BLUE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_ALPHA_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_ALPHA_SIZE", GL_RENDERBUFFER_ALPHA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_DEPTH_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_DEPTH_SIZE", GL_RENDERBUFFER_DEPTH_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_STENCIL_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_STENCIL_SIZE", GL_RENDERBUFFER_STENCIL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE", GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_SAMPLES", GL_MAX_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INDEX 
    REGISTER_LONG_CONSTANT("GL_INDEX", GL_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_SRGB 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_SRGB", GL_FRAMEBUFFER_SRGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_HALF_FLOAT 
    REGISTER_LONG_CONSTANT("GL_HALF_FLOAT", GL_HALF_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_READ_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_READ_BIT", GL_MAP_READ_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_WRITE_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_WRITE_BIT", GL_MAP_WRITE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_INVALIDATE_RANGE_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_INVALIDATE_RANGE_BIT", GL_MAP_INVALIDATE_RANGE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_INVALIDATE_BUFFER_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_INVALIDATE_BUFFER_BIT", GL_MAP_INVALIDATE_BUFFER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_FLUSH_EXPLICIT_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_FLUSH_EXPLICIT_BIT", GL_MAP_FLUSH_EXPLICIT_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_UNSYNCHRONIZED_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_UNSYNCHRONIZED_BIT", GL_MAP_UNSYNCHRONIZED_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RED_RGTC1 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RED_RGTC1", GL_COMPRESSED_RED_RGTC1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SIGNED_RED_RGTC1 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SIGNED_RED_RGTC1", GL_COMPRESSED_SIGNED_RED_RGTC1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RG_RGTC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RG_RGTC2", GL_COMPRESSED_RG_RGTC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SIGNED_RG_RGTC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SIGNED_RG_RGTC2", GL_COMPRESSED_SIGNED_RG_RGTC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG 
    REGISTER_LONG_CONSTANT("GL_RG", GL_RG, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG_INTEGER 
    REGISTER_LONG_CONSTANT("GL_RG_INTEGER", GL_RG_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R8 
    REGISTER_LONG_CONSTANT("GL_R8", GL_R8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16 
    REGISTER_LONG_CONSTANT("GL_R16", GL_R16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG8 
    REGISTER_LONG_CONSTANT("GL_RG8", GL_RG8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16 
    REGISTER_LONG_CONSTANT("GL_RG16", GL_RG16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16F 
    REGISTER_LONG_CONSTANT("GL_R16F", GL_R16F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R32F 
    REGISTER_LONG_CONSTANT("GL_R32F", GL_R32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16F 
    REGISTER_LONG_CONSTANT("GL_RG16F", GL_RG16F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG32F 
    REGISTER_LONG_CONSTANT("GL_RG32F", GL_RG32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R8I 
    REGISTER_LONG_CONSTANT("GL_R8I", GL_R8I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R8UI 
    REGISTER_LONG_CONSTANT("GL_R8UI", GL_R8UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16I 
    REGISTER_LONG_CONSTANT("GL_R16I", GL_R16I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16UI 
    REGISTER_LONG_CONSTANT("GL_R16UI", GL_R16UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R32I 
    REGISTER_LONG_CONSTANT("GL_R32I", GL_R32I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R32UI 
    REGISTER_LONG_CONSTANT("GL_R32UI", GL_R32UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG8I 
    REGISTER_LONG_CONSTANT("GL_RG8I", GL_RG8I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG8UI 
    REGISTER_LONG_CONSTANT("GL_RG8UI", GL_RG8UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16I 
    REGISTER_LONG_CONSTANT("GL_RG16I", GL_RG16I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16UI 
    REGISTER_LONG_CONSTANT("GL_RG16UI", GL_RG16UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG32I 
    REGISTER_LONG_CONSTANT("GL_RG32I", GL_RG32I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG32UI 
    REGISTER_LONG_CONSTANT("GL_RG32UI", GL_RG32UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ARRAY_BINDING 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ARRAY_BINDING", GL_VERTEX_ARRAY_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_RECT", GL_SAMPLER_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_RECT_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_RECT_SHADOW", GL_SAMPLER_2D_RECT_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_BUFFER", GL_SAMPLER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D_RECT", GL_INT_SAMPLER_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_BUFFER", GL_INT_SAMPLER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D_RECT", GL_UNSIGNED_INT_SAMPLER_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_BUFFER", GL_UNSIGNED_INT_SAMPLER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER", GL_TEXTURE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_BUFFER_SIZE", GL_MAX_TEXTURE_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_BUFFER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_BUFFER", GL_TEXTURE_BINDING_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_DATA_STORE_BINDING 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_DATA_STORE_BINDING", GL_TEXTURE_BUFFER_DATA_STORE_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_RECTANGLE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_RECTANGLE", GL_TEXTURE_RECTANGLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_RECTANGLE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_RECTANGLE", GL_TEXTURE_BINDING_RECTANGLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_RECTANGLE 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_RECTANGLE", GL_PROXY_TEXTURE_RECTANGLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_RECTANGLE_TEXTURE_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_RECTANGLE_TEXTURE_SIZE", GL_MAX_RECTANGLE_TEXTURE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R8_SNORM 
    REGISTER_LONG_CONSTANT("GL_R8_SNORM", GL_R8_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG8_SNORM 
    REGISTER_LONG_CONSTANT("GL_RG8_SNORM", GL_RG8_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB8_SNORM 
    REGISTER_LONG_CONSTANT("GL_RGB8_SNORM", GL_RGB8_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA8_SNORM 
    REGISTER_LONG_CONSTANT("GL_RGBA8_SNORM", GL_RGBA8_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16_SNORM 
    REGISTER_LONG_CONSTANT("GL_R16_SNORM", GL_R16_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16_SNORM 
    REGISTER_LONG_CONSTANT("GL_RG16_SNORM", GL_RG16_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16_SNORM 
    REGISTER_LONG_CONSTANT("GL_RGB16_SNORM", GL_RGB16_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16_SNORM 
    REGISTER_LONG_CONSTANT("GL_RGBA16_SNORM", GL_RGBA16_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIGNED_NORMALIZED 
    REGISTER_LONG_CONSTANT("GL_SIGNED_NORMALIZED", GL_SIGNED_NORMALIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVE_RESTART 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVE_RESTART", GL_PRIMITIVE_RESTART, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVE_RESTART_INDEX 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVE_RESTART_INDEX", GL_PRIMITIVE_RESTART_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_READ_BUFFER 
    REGISTER_LONG_CONSTANT("GL_COPY_READ_BUFFER", GL_COPY_READ_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_WRITE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_COPY_WRITE_BUFFER", GL_COPY_WRITE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER", GL_UNIFORM_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER_BINDING", GL_UNIFORM_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER_START 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER_START", GL_UNIFORM_BUFFER_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER_SIZE", GL_UNIFORM_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_UNIFORM_BLOCKS", GL_MAX_VERTEX_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_UNIFORM_BLOCKS", GL_MAX_GEOMETRY_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_UNIFORM_BLOCKS", GL_MAX_FRAGMENT_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_UNIFORM_BLOCKS", GL_MAX_COMBINED_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_UNIFORM_BUFFER_BINDINGS 
    REGISTER_LONG_CONSTANT("GL_MAX_UNIFORM_BUFFER_BINDINGS", GL_MAX_UNIFORM_BUFFER_BINDINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_UNIFORM_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_UNIFORM_BLOCK_SIZE", GL_MAX_UNIFORM_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS", GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS", GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS", GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT", GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH", GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_UNIFORM_BLOCKS", GL_ACTIVE_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_TYPE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_TYPE", GL_UNIFORM_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_SIZE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_SIZE", GL_UNIFORM_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_NAME_LENGTH", GL_UNIFORM_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_INDEX 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_INDEX", GL_UNIFORM_BLOCK_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_OFFSET 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_OFFSET", GL_UNIFORM_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_ARRAY_STRIDE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_ARRAY_STRIDE", GL_UNIFORM_ARRAY_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_MATRIX_STRIDE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_MATRIX_STRIDE", GL_UNIFORM_MATRIX_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_IS_ROW_MAJOR 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_IS_ROW_MAJOR", GL_UNIFORM_IS_ROW_MAJOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_BINDING 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_BINDING", GL_UNIFORM_BLOCK_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_DATA_SIZE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_DATA_SIZE", GL_UNIFORM_BLOCK_DATA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_NAME_LENGTH", GL_UNIFORM_BLOCK_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS", GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES", GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_INDEX 
    REGISTER_LONG_CONSTANT("GL_INVALID_INDEX", GL_INVALID_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_CORE_PROFILE_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_CORE_PROFILE_BIT", GL_CONTEXT_CORE_PROFILE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_COMPATIBILITY_PROFILE_BIT", GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINES_ADJACENCY 
    REGISTER_LONG_CONSTANT("GL_LINES_ADJACENCY", GL_LINES_ADJACENCY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_STRIP_ADJACENCY 
    REGISTER_LONG_CONSTANT("GL_LINE_STRIP_ADJACENCY", GL_LINE_STRIP_ADJACENCY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLES_ADJACENCY 
    REGISTER_LONG_CONSTANT("GL_TRIANGLES_ADJACENCY", GL_TRIANGLES_ADJACENCY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLE_STRIP_ADJACENCY 
    REGISTER_LONG_CONSTANT("GL_TRIANGLE_STRIP_ADJACENCY", GL_TRIANGLE_STRIP_ADJACENCY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_POINT_SIZE 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_POINT_SIZE", GL_PROGRAM_POINT_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS", GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_LAYERED 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_LAYERED", GL_FRAMEBUFFER_ATTACHMENT_LAYERED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS", GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SHADER 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SHADER", GL_GEOMETRY_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_VERTICES_OUT 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_VERTICES_OUT", GL_GEOMETRY_VERTICES_OUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_INPUT_TYPE 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_INPUT_TYPE", GL_GEOMETRY_INPUT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_OUTPUT_TYPE 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_OUTPUT_TYPE", GL_GEOMETRY_OUTPUT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_UNIFORM_COMPONENTS", GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_OUTPUT_VERTICES 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_OUTPUT_VERTICES", GL_MAX_GEOMETRY_OUTPUT_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS", GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_OUTPUT_COMPONENTS", GL_MAX_VERTEX_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_INPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_INPUT_COMPONENTS", GL_MAX_GEOMETRY_INPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_OUTPUT_COMPONENTS", GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_INPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_INPUT_COMPONENTS", GL_MAX_FRAGMENT_INPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_PROFILE_MASK 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_PROFILE_MASK", GL_CONTEXT_PROFILE_MASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_CLAMP 
    REGISTER_LONG_CONSTANT("GL_DEPTH_CLAMP", GL_DEPTH_CLAMP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 
    REGISTER_LONG_CONSTANT("GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION", GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FIRST_VERTEX_CONVENTION 
    REGISTER_LONG_CONSTANT("GL_FIRST_VERTEX_CONVENTION", GL_FIRST_VERTEX_CONVENTION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LAST_VERTEX_CONVENTION 
    REGISTER_LONG_CONSTANT("GL_LAST_VERTEX_CONVENTION", GL_LAST_VERTEX_CONVENTION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROVOKING_VERTEX 
    REGISTER_LONG_CONSTANT("GL_PROVOKING_VERTEX", GL_PROVOKING_VERTEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_SEAMLESS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_SEAMLESS", GL_TEXTURE_CUBE_MAP_SEAMLESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SERVER_WAIT_TIMEOUT 
    REGISTER_LONG_CONSTANT("GL_MAX_SERVER_WAIT_TIMEOUT", GL_MAX_SERVER_WAIT_TIMEOUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OBJECT_TYPE 
    REGISTER_LONG_CONSTANT("GL_OBJECT_TYPE", GL_OBJECT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_CONDITION 
    REGISTER_LONG_CONSTANT("GL_SYNC_CONDITION", GL_SYNC_CONDITION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_STATUS 
    REGISTER_LONG_CONSTANT("GL_SYNC_STATUS", GL_SYNC_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_FLAGS 
    REGISTER_LONG_CONSTANT("GL_SYNC_FLAGS", GL_SYNC_FLAGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_FENCE 
    REGISTER_LONG_CONSTANT("GL_SYNC_FENCE", GL_SYNC_FENCE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_GPU_COMMANDS_COMPLETE 
    REGISTER_LONG_CONSTANT("GL_SYNC_GPU_COMMANDS_COMPLETE", GL_SYNC_GPU_COMMANDS_COMPLETE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNALED 
    REGISTER_LONG_CONSTANT("GL_UNSIGNALED", GL_UNSIGNALED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIGNALED 
    REGISTER_LONG_CONSTANT("GL_SIGNALED", GL_SIGNALED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALREADY_SIGNALED 
    REGISTER_LONG_CONSTANT("GL_ALREADY_SIGNALED", GL_ALREADY_SIGNALED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TIMEOUT_EXPIRED 
    REGISTER_LONG_CONSTANT("GL_TIMEOUT_EXPIRED", GL_TIMEOUT_EXPIRED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONDITION_SATISFIED 
    REGISTER_LONG_CONSTANT("GL_CONDITION_SATISFIED", GL_CONDITION_SATISFIED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_WAIT_FAILED 
    REGISTER_LONG_CONSTANT("GL_WAIT_FAILED", GL_WAIT_FAILED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TIMEOUT_IGNORED 
    REGISTER_LONG_CONSTANT("GL_TIMEOUT_IGNORED", GL_TIMEOUT_IGNORED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_FLUSH_COMMANDS_BIT 
    REGISTER_LONG_CONSTANT("GL_SYNC_FLUSH_COMMANDS_BIT", GL_SYNC_FLUSH_COMMANDS_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_POSITION 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_POSITION", GL_SAMPLE_POSITION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_MASK 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_MASK", GL_SAMPLE_MASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_MASK_VALUE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_MASK_VALUE", GL_SAMPLE_MASK_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SAMPLE_MASK_WORDS 
    REGISTER_LONG_CONSTANT("GL_MAX_SAMPLE_MASK_WORDS", GL_MAX_SAMPLE_MASK_WORDS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_2D_MULTISAMPLE", GL_TEXTURE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_2D_MULTISAMPLE", GL_PROXY_TEXTURE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_2D_MULTISAMPLE_ARRAY", GL_TEXTURE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY", GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_2D_MULTISAMPLE", GL_TEXTURE_BINDING_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY", GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SAMPLES", GL_TEXTURE_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_FIXED_SAMPLE_LOCATIONS", GL_TEXTURE_FIXED_SAMPLE_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_MULTISAMPLE", GL_SAMPLER_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D_MULTISAMPLE", GL_INT_SAMPLER_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE", GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_MULTISAMPLE_ARRAY", GL_SAMPLER_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY", GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY", GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COLOR_TEXTURE_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_COLOR_TEXTURE_SAMPLES", GL_MAX_COLOR_TEXTURE_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEPTH_TEXTURE_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_DEPTH_TEXTURE_SAMPLES", GL_MAX_DEPTH_TEXTURE_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_INTEGER_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_INTEGER_SAMPLES", GL_MAX_INTEGER_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_DIVISOR 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_DIVISOR", GL_VERTEX_ATTRIB_ARRAY_DIVISOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC1_COLOR 
    REGISTER_LONG_CONSTANT("GL_SRC1_COLOR", GL_SRC1_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_SRC1_COLOR 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_SRC1_COLOR", GL_ONE_MINUS_SRC1_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_SRC1_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_SRC1_ALPHA", GL_ONE_MINUS_SRC1_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_DUAL_SOURCE_DRAW_BUFFERS", GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ANY_SAMPLES_PASSED 
    REGISTER_LONG_CONSTANT("GL_ANY_SAMPLES_PASSED", GL_ANY_SAMPLES_PASSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_BINDING 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_BINDING", GL_SAMPLER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB10_A2UI 
    REGISTER_LONG_CONSTANT("GL_RGB10_A2UI", GL_RGB10_A2UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_R 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_R", GL_TEXTURE_SWIZZLE_R, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_G 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_G", GL_TEXTURE_SWIZZLE_G, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_B 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_B", GL_TEXTURE_SWIZZLE_B, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_A 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_A", GL_TEXTURE_SWIZZLE_A, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_RGBA 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_RGBA", GL_TEXTURE_SWIZZLE_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TIME_ELAPSED 
    REGISTER_LONG_CONSTANT("GL_TIME_ELAPSED", GL_TIME_ELAPSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TIMESTAMP 
    REGISTER_LONG_CONSTANT("GL_TIMESTAMP", GL_TIMESTAMP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_2_10_10_10_REV 
    REGISTER_LONG_CONSTANT("GL_INT_2_10_10_10_REV", GL_INT_2_10_10_10_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_SHADING 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_SHADING", GL_SAMPLE_SHADING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_SAMPLE_SHADING_VALUE 
    REGISTER_LONG_CONSTANT("GL_MIN_SAMPLE_SHADING_VALUE", GL_MIN_SAMPLE_SHADING_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET", GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET", GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_ARRAY", GL_TEXTURE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_CUBE_MAP_ARRAY", GL_TEXTURE_BINDING_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_CUBE_MAP_ARRAY", GL_PROXY_TEXTURE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_CUBE_MAP_ARRAY", GL_SAMPLER_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW", GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_CUBE_MAP_ARRAY", GL_INT_SAMPLER_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY", GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_INDIRECT_BUFFER 
    REGISTER_LONG_CONSTANT("GL_DRAW_INDIRECT_BUFFER", GL_DRAW_INDIRECT_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_INDIRECT_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_DRAW_INDIRECT_BUFFER_BINDING", GL_DRAW_INDIRECT_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SHADER_INVOCATIONS", GL_GEOMETRY_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_SHADER_INVOCATIONS", GL_MAX_GEOMETRY_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MIN_FRAGMENT_INTERPOLATION_OFFSET", GL_MIN_FRAGMENT_INTERPOLATION_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_INTERPOLATION_OFFSET", GL_MAX_FRAGMENT_INTERPOLATION_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_INTERPOLATION_OFFSET_BITS", GL_FRAGMENT_INTERPOLATION_OFFSET_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_STREAMS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_STREAMS", GL_MAX_VERTEX_STREAMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_VEC2 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_VEC2", GL_DOUBLE_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_VEC3 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_VEC3", GL_DOUBLE_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_VEC4 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_VEC4", GL_DOUBLE_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT2 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT2", GL_DOUBLE_MAT2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT3 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT3", GL_DOUBLE_MAT3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT4 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT4", GL_DOUBLE_MAT4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT2x3 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT2x3", GL_DOUBLE_MAT2x3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT2x4 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT2x4", GL_DOUBLE_MAT2x4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT3x2 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT3x2", GL_DOUBLE_MAT3x2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT3x4 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT3x4", GL_DOUBLE_MAT3x4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT4x2 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT4x2", GL_DOUBLE_MAT4x2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT4x3 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT4x3", GL_DOUBLE_MAT4x3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINES", GL_ACTIVE_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINE_UNIFORMS", GL_ACTIVE_SUBROUTINE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS", GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINE_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINE_MAX_LENGTH", GL_ACTIVE_SUBROUTINE_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH", GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_MAX_SUBROUTINES", GL_MAX_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS", GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_COMPATIBLE_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_NUM_COMPATIBLE_SUBROUTINES", GL_NUM_COMPATIBLE_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPATIBLE_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_COMPATIBLE_SUBROUTINES", GL_COMPATIBLE_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PATCHES 
    REGISTER_LONG_CONSTANT("GL_PATCHES", GL_PATCHES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PATCH_VERTICES 
    REGISTER_LONG_CONSTANT("GL_PATCH_VERTICES", GL_PATCH_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PATCH_DEFAULT_INNER_LEVEL 
    REGISTER_LONG_CONSTANT("GL_PATCH_DEFAULT_INNER_LEVEL", GL_PATCH_DEFAULT_INNER_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PATCH_DEFAULT_OUTER_LEVEL 
    REGISTER_LONG_CONSTANT("GL_PATCH_DEFAULT_OUTER_LEVEL", GL_PATCH_DEFAULT_OUTER_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_OUTPUT_VERTICES 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_OUTPUT_VERTICES", GL_TESS_CONTROL_OUTPUT_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_GEN_MODE 
    REGISTER_LONG_CONSTANT("GL_TESS_GEN_MODE", GL_TESS_GEN_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_GEN_SPACING 
    REGISTER_LONG_CONSTANT("GL_TESS_GEN_SPACING", GL_TESS_GEN_SPACING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_GEN_VERTEX_ORDER 
    REGISTER_LONG_CONSTANT("GL_TESS_GEN_VERTEX_ORDER", GL_TESS_GEN_VERTEX_ORDER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_GEN_POINT_MODE 
    REGISTER_LONG_CONSTANT("GL_TESS_GEN_POINT_MODE", GL_TESS_GEN_POINT_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ISOLINES 
    REGISTER_LONG_CONSTANT("GL_ISOLINES", GL_ISOLINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRACTIONAL_ODD 
    REGISTER_LONG_CONSTANT("GL_FRACTIONAL_ODD", GL_FRACTIONAL_ODD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRACTIONAL_EVEN 
    REGISTER_LONG_CONSTANT("GL_FRACTIONAL_EVEN", GL_FRACTIONAL_EVEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_PATCH_VERTICES 
    REGISTER_LONG_CONSTANT("GL_MAX_PATCH_VERTICES", GL_MAX_PATCH_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_GEN_LEVEL 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_GEN_LEVEL", GL_MAX_TESS_GEN_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS", GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS", GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS", GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS", GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS", GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_PATCH_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_PATCH_COMPONENTS", GL_MAX_TESS_PATCH_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS", GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS", GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS", GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS", GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_INPUT_COMPONENTS", GL_MAX_TESS_CONTROL_INPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS", GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS", GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS", GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SHADER 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SHADER", GL_TESS_EVALUATION_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SHADER 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SHADER", GL_TESS_CONTROL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK", GL_TRANSFORM_FEEDBACK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED", GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE", GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BINDING 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BINDING", GL_TRANSFORM_FEEDBACK_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TRANSFORM_FEEDBACK_BUFFERS", GL_MAX_TRANSFORM_FEEDBACK_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FIXED 
    REGISTER_LONG_CONSTANT("GL_FIXED", GL_FIXED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMPLEMENTATION_COLOR_READ_TYPE 
    REGISTER_LONG_CONSTANT("GL_IMPLEMENTATION_COLOR_READ_TYPE", GL_IMPLEMENTATION_COLOR_READ_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMPLEMENTATION_COLOR_READ_FORMAT 
    REGISTER_LONG_CONSTANT("GL_IMPLEMENTATION_COLOR_READ_FORMAT", GL_IMPLEMENTATION_COLOR_READ_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOW_FLOAT 
    REGISTER_LONG_CONSTANT("GL_LOW_FLOAT", GL_LOW_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MEDIUM_FLOAT 
    REGISTER_LONG_CONSTANT("GL_MEDIUM_FLOAT", GL_MEDIUM_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_HIGH_FLOAT 
    REGISTER_LONG_CONSTANT("GL_HIGH_FLOAT", GL_HIGH_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOW_INT 
    REGISTER_LONG_CONSTANT("GL_LOW_INT", GL_LOW_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MEDIUM_INT 
    REGISTER_LONG_CONSTANT("GL_MEDIUM_INT", GL_MEDIUM_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_HIGH_INT 
    REGISTER_LONG_CONSTANT("GL_HIGH_INT", GL_HIGH_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_COMPILER 
    REGISTER_LONG_CONSTANT("GL_SHADER_COMPILER", GL_SHADER_COMPILER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_BINARY_FORMATS 
    REGISTER_LONG_CONSTANT("GL_SHADER_BINARY_FORMATS", GL_SHADER_BINARY_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_SHADER_BINARY_FORMATS 
    REGISTER_LONG_CONSTANT("GL_NUM_SHADER_BINARY_FORMATS", GL_NUM_SHADER_BINARY_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_UNIFORM_VECTORS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_UNIFORM_VECTORS", GL_MAX_VERTEX_UNIFORM_VECTORS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VARYING_VECTORS 
    REGISTER_LONG_CONSTANT("GL_MAX_VARYING_VECTORS", GL_MAX_VARYING_VECTORS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_UNIFORM_VECTORS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_UNIFORM_VECTORS", GL_MAX_FRAGMENT_UNIFORM_VECTORS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB565 
    REGISTER_LONG_CONSTANT("GL_RGB565", GL_RGB565, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_BINARY_RETRIEVABLE_HINT 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_BINARY_RETRIEVABLE_HINT", GL_PROGRAM_BINARY_RETRIEVABLE_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_BINARY_LENGTH 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_BINARY_LENGTH", GL_PROGRAM_BINARY_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_PROGRAM_BINARY_FORMATS 
    REGISTER_LONG_CONSTANT("GL_NUM_PROGRAM_BINARY_FORMATS", GL_NUM_PROGRAM_BINARY_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_BINARY_FORMATS 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_BINARY_FORMATS", GL_PROGRAM_BINARY_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SHADER_BIT", GL_VERTEX_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SHADER_BIT", GL_FRAGMENT_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SHADER_BIT", GL_GEOMETRY_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SHADER_BIT", GL_TESS_CONTROL_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SHADER_BIT", GL_TESS_EVALUATION_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALL_SHADER_BITS 
    REGISTER_LONG_CONSTANT("GL_ALL_SHADER_BITS", GL_ALL_SHADER_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_SEPARABLE 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_SEPARABLE", GL_PROGRAM_SEPARABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_PROGRAM 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_PROGRAM", GL_ACTIVE_PROGRAM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_PIPELINE_BINDING 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_PIPELINE_BINDING", GL_PROGRAM_PIPELINE_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VIEWPORTS 
    REGISTER_LONG_CONSTANT("GL_MAX_VIEWPORTS", GL_MAX_VIEWPORTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEWPORT_SUBPIXEL_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEWPORT_SUBPIXEL_BITS", GL_VIEWPORT_SUBPIXEL_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEWPORT_BOUNDS_RANGE 
    REGISTER_LONG_CONSTANT("GL_VIEWPORT_BOUNDS_RANGE", GL_VIEWPORT_BOUNDS_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LAYER_PROVOKING_VERTEX 
    REGISTER_LONG_CONSTANT("GL_LAYER_PROVOKING_VERTEX", GL_LAYER_PROVOKING_VERTEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEWPORT_INDEX_PROVOKING_VERTEX 
    REGISTER_LONG_CONSTANT("GL_VIEWPORT_INDEX_PROVOKING_VERTEX", GL_VIEWPORT_INDEX_PROVOKING_VERTEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNDEFINED_VERTEX 
    REGISTER_LONG_CONSTANT("GL_UNDEFINED_VERTEX", GL_UNDEFINED_VERTEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_READ_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_COPY_READ_BUFFER_BINDING", GL_COPY_READ_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_WRITE_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_COPY_WRITE_BUFFER_BINDING", GL_COPY_WRITE_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_ACTIVE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_ACTIVE", GL_TRANSFORM_FEEDBACK_ACTIVE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_PAUSED 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_PAUSED", GL_TRANSFORM_FEEDBACK_PAUSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_COMPRESSED_BLOCK_WIDTH 
    REGISTER_LONG_CONSTANT("GL_UNPACK_COMPRESSED_BLOCK_WIDTH", GL_UNPACK_COMPRESSED_BLOCK_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_UNPACK_COMPRESSED_BLOCK_HEIGHT", GL_UNPACK_COMPRESSED_BLOCK_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_COMPRESSED_BLOCK_DEPTH 
    REGISTER_LONG_CONSTANT("GL_UNPACK_COMPRESSED_BLOCK_DEPTH", GL_UNPACK_COMPRESSED_BLOCK_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_COMPRESSED_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_UNPACK_COMPRESSED_BLOCK_SIZE", GL_UNPACK_COMPRESSED_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_COMPRESSED_BLOCK_WIDTH 
    REGISTER_LONG_CONSTANT("GL_PACK_COMPRESSED_BLOCK_WIDTH", GL_PACK_COMPRESSED_BLOCK_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_COMPRESSED_BLOCK_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_PACK_COMPRESSED_BLOCK_HEIGHT", GL_PACK_COMPRESSED_BLOCK_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_COMPRESSED_BLOCK_DEPTH 
    REGISTER_LONG_CONSTANT("GL_PACK_COMPRESSED_BLOCK_DEPTH", GL_PACK_COMPRESSED_BLOCK_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_COMPRESSED_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_PACK_COMPRESSED_BLOCK_SIZE", GL_PACK_COMPRESSED_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_SAMPLE_COUNTS 
    REGISTER_LONG_CONSTANT("GL_NUM_SAMPLE_COUNTS", GL_NUM_SAMPLE_COUNTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_MAP_BUFFER_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_MIN_MAP_BUFFER_ALIGNMENT", GL_MIN_MAP_BUFFER_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER", GL_ATOMIC_COUNTER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_BINDING", GL_ATOMIC_COUNTER_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_START 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_START", GL_ATOMIC_COUNTER_BUFFER_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_SIZE", GL_ATOMIC_COUNTER_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE", GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS", GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES", GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS", GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS", GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS", GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS", GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS", GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS", GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATOMIC_COUNTERS", GL_MAX_VERTEX_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS", GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS", GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_ATOMIC_COUNTERS", GL_MAX_GEOMETRY_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_ATOMIC_COUNTERS", GL_MAX_FRAGMENT_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_ATOMIC_COUNTERS", GL_MAX_COMBINED_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE", GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 
    REGISTER_LONG_CONSTANT("GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS", GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_ATOMIC_COUNTER_BUFFERS", GL_ACTIVE_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX", GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_ATOMIC_COUNTER 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_ATOMIC_COUNTER", GL_UNSIGNED_INT_ATOMIC_COUNTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT", GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ELEMENT_ARRAY_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_ELEMENT_ARRAY_BARRIER_BIT", GL_ELEMENT_ARRAY_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BARRIER_BIT", GL_UNIFORM_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_FETCH_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_FETCH_BARRIER_BIT", GL_TEXTURE_FETCH_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_SHADER_IMAGE_ACCESS_BARRIER_BIT", GL_SHADER_IMAGE_ACCESS_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMMAND_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_COMMAND_BARRIER_BIT", GL_COMMAND_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_BUFFER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_PIXEL_BUFFER_BARRIER_BIT", GL_PIXEL_BUFFER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_UPDATE_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_UPDATE_BARRIER_BIT", GL_TEXTURE_UPDATE_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_UPDATE_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_BUFFER_UPDATE_BARRIER_BIT", GL_BUFFER_UPDATE_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_BARRIER_BIT", GL_FRAMEBUFFER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BARRIER_BIT", GL_TRANSFORM_FEEDBACK_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BARRIER_BIT", GL_ATOMIC_COUNTER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALL_BARRIER_BITS 
    REGISTER_LONG_CONSTANT("GL_ALL_BARRIER_BITS", GL_ALL_BARRIER_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_IMAGE_UNITS", GL_MAX_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS", GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_NAME 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_NAME", GL_IMAGE_BINDING_NAME, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_LEVEL 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_LEVEL", GL_IMAGE_BINDING_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_LAYERED 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_LAYERED", GL_IMAGE_BINDING_LAYERED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_LAYER 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_LAYER", GL_IMAGE_BINDING_LAYER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_ACCESS 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_ACCESS", GL_IMAGE_BINDING_ACCESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_1D 
    REGISTER_LONG_CONSTANT("GL_IMAGE_1D", GL_IMAGE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D", GL_IMAGE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_3D 
    REGISTER_LONG_CONSTANT("GL_IMAGE_3D", GL_IMAGE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D_RECT", GL_IMAGE_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CUBE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CUBE", GL_IMAGE_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BUFFER", GL_IMAGE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_IMAGE_1D_ARRAY", GL_IMAGE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D_ARRAY", GL_IMAGE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CUBE_MAP_ARRAY", GL_IMAGE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D_MULTISAMPLE", GL_IMAGE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D_MULTISAMPLE_ARRAY", GL_IMAGE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_1D 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_1D", GL_INT_IMAGE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D", GL_INT_IMAGE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_3D 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_3D", GL_INT_IMAGE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D_RECT", GL_INT_IMAGE_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_CUBE 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_CUBE", GL_INT_IMAGE_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_BUFFER", GL_INT_IMAGE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_1D_ARRAY", GL_INT_IMAGE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D_ARRAY", GL_INT_IMAGE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_CUBE_MAP_ARRAY", GL_INT_IMAGE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D_MULTISAMPLE", GL_INT_IMAGE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY", GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_1D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_1D", GL_UNSIGNED_INT_IMAGE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D", GL_UNSIGNED_INT_IMAGE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_3D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_3D", GL_UNSIGNED_INT_IMAGE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D_RECT", GL_UNSIGNED_INT_IMAGE_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_CUBE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_CUBE", GL_UNSIGNED_INT_IMAGE_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_BUFFER", GL_UNSIGNED_INT_IMAGE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_1D_ARRAY", GL_UNSIGNED_INT_IMAGE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D_ARRAY", GL_UNSIGNED_INT_IMAGE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY", GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE", GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY", GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_IMAGE_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_IMAGE_SAMPLES", GL_MAX_IMAGE_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_FORMAT 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_FORMAT", GL_IMAGE_BINDING_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_FORMAT_COMPATIBILITY_TYPE", GL_IMAGE_FORMAT_COMPATIBILITY_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE", GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 
    REGISTER_LONG_CONSTANT("GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS", GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_IMAGE_UNIFORMS", GL_MAX_VERTEX_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS", GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS", GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_IMAGE_UNIFORMS", GL_MAX_GEOMETRY_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_IMAGE_UNIFORMS", GL_MAX_FRAGMENT_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_IMAGE_UNIFORMS", GL_MAX_COMBINED_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGBA_BPTC_UNORM 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGBA_BPTC_UNORM", GL_COMPRESSED_RGBA_BPTC_UNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM", GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT", GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT", GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_IMMUTABLE_FORMAT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_IMMUTABLE_FORMAT", GL_TEXTURE_IMMUTABLE_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_SHADING_LANGUAGE_VERSIONS 
    REGISTER_LONG_CONSTANT("GL_NUM_SHADING_LANGUAGE_VERSIONS", GL_NUM_SHADING_LANGUAGE_VERSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_LONG 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_LONG", GL_VERTEX_ATTRIB_ARRAY_LONG, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB8_ETC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB8_ETC2", GL_COMPRESSED_RGB8_ETC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB8_ETC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB8_ETC2", GL_COMPRESSED_SRGB8_ETC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2", GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2", GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGBA8_ETC2_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGBA8_ETC2_EAC", GL_COMPRESSED_RGBA8_ETC2_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC", GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_R11_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_R11_EAC", GL_COMPRESSED_R11_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SIGNED_R11_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SIGNED_R11_EAC", GL_COMPRESSED_SIGNED_R11_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RG11_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RG11_EAC", GL_COMPRESSED_RG11_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SIGNED_RG11_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SIGNED_RG11_EAC", GL_COMPRESSED_SIGNED_RG11_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVE_RESTART_FIXED_INDEX 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVE_RESTART_FIXED_INDEX", GL_PRIMITIVE_RESTART_FIXED_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ANY_SAMPLES_PASSED_CONSERVATIVE 
    REGISTER_LONG_CONSTANT("GL_ANY_SAMPLES_PASSED_CONSERVATIVE", GL_ANY_SAMPLES_PASSED_CONSERVATIVE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ELEMENT_INDEX 
    REGISTER_LONG_CONSTANT("GL_MAX_ELEMENT_INDEX", GL_MAX_ELEMENT_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SHADER 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SHADER", GL_COMPUTE_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_UNIFORM_BLOCKS", GL_MAX_COMPUTE_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS", GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_IMAGE_UNIFORMS", GL_MAX_COMPUTE_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_SHARED_MEMORY_SIZE", GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_UNIFORM_COMPONENTS", GL_MAX_COMPUTE_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS", GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_ATOMIC_COUNTERS", GL_MAX_COMPUTE_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS", GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS", GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_WORK_GROUP_COUNT 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_WORK_GROUP_COUNT", GL_MAX_COMPUTE_WORK_GROUP_COUNT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_WORK_GROUP_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_WORK_GROUP_SIZE", GL_MAX_COMPUTE_WORK_GROUP_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_WORK_GROUP_SIZE 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_WORK_GROUP_SIZE", GL_COMPUTE_WORK_GROUP_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DISPATCH_INDIRECT_BUFFER 
    REGISTER_LONG_CONSTANT("GL_DISPATCH_INDIRECT_BUFFER", GL_DISPATCH_INDIRECT_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DISPATCH_INDIRECT_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_DISPATCH_INDIRECT_BUFFER_BINDING", GL_DISPATCH_INDIRECT_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SHADER_BIT", GL_COMPUTE_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_OUTPUT_SYNCHRONOUS 
    REGISTER_LONG_CONSTANT("GL_DEBUG_OUTPUT_SYNCHRONOUS", GL_DEBUG_OUTPUT_SYNCHRONOUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 
    REGISTER_LONG_CONSTANT("GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH", GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_CALLBACK_FUNCTION 
    REGISTER_LONG_CONSTANT("GL_DEBUG_CALLBACK_FUNCTION", GL_DEBUG_CALLBACK_FUNCTION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_CALLBACK_USER_PARAM 
    REGISTER_LONG_CONSTANT("GL_DEBUG_CALLBACK_USER_PARAM", GL_DEBUG_CALLBACK_USER_PARAM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_API 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_API", GL_DEBUG_SOURCE_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_WINDOW_SYSTEM 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_WINDOW_SYSTEM", GL_DEBUG_SOURCE_WINDOW_SYSTEM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_SHADER_COMPILER 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_SHADER_COMPILER", GL_DEBUG_SOURCE_SHADER_COMPILER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_THIRD_PARTY 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_THIRD_PARTY", GL_DEBUG_SOURCE_THIRD_PARTY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_APPLICATION 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_APPLICATION", GL_DEBUG_SOURCE_APPLICATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_OTHER 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_OTHER", GL_DEBUG_SOURCE_OTHER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_ERROR 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_ERROR", GL_DEBUG_TYPE_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR", GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR", GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_PORTABILITY 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_PORTABILITY", GL_DEBUG_TYPE_PORTABILITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_PERFORMANCE 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_PERFORMANCE", GL_DEBUG_TYPE_PERFORMANCE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_OTHER 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_OTHER", GL_DEBUG_TYPE_OTHER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEBUG_MESSAGE_LENGTH 
    REGISTER_LONG_CONSTANT("GL_MAX_DEBUG_MESSAGE_LENGTH", GL_MAX_DEBUG_MESSAGE_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEBUG_LOGGED_MESSAGES 
    REGISTER_LONG_CONSTANT("GL_MAX_DEBUG_LOGGED_MESSAGES", GL_MAX_DEBUG_LOGGED_MESSAGES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_LOGGED_MESSAGES 
    REGISTER_LONG_CONSTANT("GL_DEBUG_LOGGED_MESSAGES", GL_DEBUG_LOGGED_MESSAGES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SEVERITY_HIGH 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SEVERITY_HIGH", GL_DEBUG_SEVERITY_HIGH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SEVERITY_MEDIUM 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SEVERITY_MEDIUM", GL_DEBUG_SEVERITY_MEDIUM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SEVERITY_LOW 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SEVERITY_LOW", GL_DEBUG_SEVERITY_LOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_MARKER 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_MARKER", GL_DEBUG_TYPE_MARKER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_PUSH_GROUP 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_PUSH_GROUP", GL_DEBUG_TYPE_PUSH_GROUP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_POP_GROUP 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_POP_GROUP", GL_DEBUG_TYPE_POP_GROUP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SEVERITY_NOTIFICATION 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SEVERITY_NOTIFICATION", GL_DEBUG_SEVERITY_NOTIFICATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEBUG_GROUP_STACK_DEPTH 
    REGISTER_LONG_CONSTANT("GL_MAX_DEBUG_GROUP_STACK_DEPTH", GL_MAX_DEBUG_GROUP_STACK_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_GROUP_STACK_DEPTH 
    REGISTER_LONG_CONSTANT("GL_DEBUG_GROUP_STACK_DEPTH", GL_DEBUG_GROUP_STACK_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER 
    REGISTER_LONG_CONSTANT("GL_BUFFER", GL_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER 
    REGISTER_LONG_CONSTANT("GL_SHADER", GL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM 
    REGISTER_LONG_CONSTANT("GL_PROGRAM", GL_PROGRAM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY 
    REGISTER_LONG_CONSTANT("GL_QUERY", GL_QUERY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_PIPELINE 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_PIPELINE", GL_PROGRAM_PIPELINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER 
    REGISTER_LONG_CONSTANT("GL_SAMPLER", GL_SAMPLER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_LABEL_LENGTH 
    REGISTER_LONG_CONSTANT("GL_MAX_LABEL_LENGTH", GL_MAX_LABEL_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_OUTPUT 
    REGISTER_LONG_CONSTANT("GL_DEBUG_OUTPUT", GL_DEBUG_OUTPUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAG_DEBUG_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAG_DEBUG_BIT", GL_CONTEXT_FLAG_DEBUG_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_UNIFORM_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_UNIFORM_LOCATIONS", GL_MAX_UNIFORM_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_WIDTH 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_WIDTH", GL_FRAMEBUFFER_DEFAULT_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_HEIGHT", GL_FRAMEBUFFER_DEFAULT_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_LAYERS 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_LAYERS", GL_FRAMEBUFFER_DEFAULT_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_SAMPLES", GL_FRAMEBUFFER_DEFAULT_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS", GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAMEBUFFER_WIDTH 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAMEBUFFER_WIDTH", GL_MAX_FRAMEBUFFER_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAMEBUFFER_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAMEBUFFER_HEIGHT", GL_MAX_FRAMEBUFFER_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAMEBUFFER_LAYERS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAMEBUFFER_LAYERS", GL_MAX_FRAMEBUFFER_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAMEBUFFER_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAMEBUFFER_SAMPLES", GL_MAX_FRAMEBUFFER_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_SUPPORTED 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_SUPPORTED", GL_INTERNALFORMAT_SUPPORTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_PREFERRED 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_PREFERRED", GL_INTERNALFORMAT_PREFERRED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_RED_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_RED_SIZE", GL_INTERNALFORMAT_RED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_GREEN_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_GREEN_SIZE", GL_INTERNALFORMAT_GREEN_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_BLUE_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_BLUE_SIZE", GL_INTERNALFORMAT_BLUE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_ALPHA_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_ALPHA_SIZE", GL_INTERNALFORMAT_ALPHA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_DEPTH_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_DEPTH_SIZE", GL_INTERNALFORMAT_DEPTH_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_STENCIL_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_STENCIL_SIZE", GL_INTERNALFORMAT_STENCIL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_SHARED_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_SHARED_SIZE", GL_INTERNALFORMAT_SHARED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_RED_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_RED_TYPE", GL_INTERNALFORMAT_RED_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_GREEN_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_GREEN_TYPE", GL_INTERNALFORMAT_GREEN_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_BLUE_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_BLUE_TYPE", GL_INTERNALFORMAT_BLUE_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_ALPHA_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_ALPHA_TYPE", GL_INTERNALFORMAT_ALPHA_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_DEPTH_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_DEPTH_TYPE", GL_INTERNALFORMAT_DEPTH_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_STENCIL_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_STENCIL_TYPE", GL_INTERNALFORMAT_STENCIL_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_WIDTH 
    REGISTER_LONG_CONSTANT("GL_MAX_WIDTH", GL_MAX_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_MAX_HEIGHT", GL_MAX_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEPTH 
    REGISTER_LONG_CONSTANT("GL_MAX_DEPTH", GL_MAX_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_LAYERS 
    REGISTER_LONG_CONSTANT("GL_MAX_LAYERS", GL_MAX_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_DIMENSIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_DIMENSIONS", GL_MAX_COMBINED_DIMENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_COLOR_COMPONENTS", GL_COLOR_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENTS", GL_DEPTH_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_STENCIL_COMPONENTS", GL_STENCIL_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_RENDERABLE 
    REGISTER_LONG_CONSTANT("GL_COLOR_RENDERABLE", GL_COLOR_RENDERABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_RENDERABLE 
    REGISTER_LONG_CONSTANT("GL_DEPTH_RENDERABLE", GL_DEPTH_RENDERABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_RENDERABLE 
    REGISTER_LONG_CONSTANT("GL_STENCIL_RENDERABLE", GL_STENCIL_RENDERABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_RENDERABLE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_RENDERABLE", GL_FRAMEBUFFER_RENDERABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_RENDERABLE_LAYERED 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_RENDERABLE_LAYERED", GL_FRAMEBUFFER_RENDERABLE_LAYERED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_BLEND 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_BLEND", GL_FRAMEBUFFER_BLEND, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_PIXELS 
    REGISTER_LONG_CONSTANT("GL_READ_PIXELS", GL_READ_PIXELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_PIXELS_FORMAT 
    REGISTER_LONG_CONSTANT("GL_READ_PIXELS_FORMAT", GL_READ_PIXELS_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_PIXELS_TYPE 
    REGISTER_LONG_CONSTANT("GL_READ_PIXELS_TYPE", GL_READ_PIXELS_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_IMAGE_FORMAT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_IMAGE_FORMAT", GL_TEXTURE_IMAGE_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_IMAGE_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_IMAGE_TYPE", GL_TEXTURE_IMAGE_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GET_TEXTURE_IMAGE_FORMAT 
    REGISTER_LONG_CONSTANT("GL_GET_TEXTURE_IMAGE_FORMAT", GL_GET_TEXTURE_IMAGE_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GET_TEXTURE_IMAGE_TYPE 
    REGISTER_LONG_CONSTANT("GL_GET_TEXTURE_IMAGE_TYPE", GL_GET_TEXTURE_IMAGE_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIPMAP 
    REGISTER_LONG_CONSTANT("GL_MIPMAP", GL_MIPMAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MANUAL_GENERATE_MIPMAP 
    REGISTER_LONG_CONSTANT("GL_MANUAL_GENERATE_MIPMAP", GL_MANUAL_GENERATE_MIPMAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_AUTO_GENERATE_MIPMAP 
    REGISTER_LONG_CONSTANT("GL_AUTO_GENERATE_MIPMAP", GL_AUTO_GENERATE_MIPMAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ENCODING 
    REGISTER_LONG_CONSTANT("GL_COLOR_ENCODING", GL_COLOR_ENCODING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB_READ 
    REGISTER_LONG_CONSTANT("GL_SRGB_READ", GL_SRGB_READ, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB_WRITE 
    REGISTER_LONG_CONSTANT("GL_SRGB_WRITE", GL_SRGB_WRITE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FILTER 
    REGISTER_LONG_CONSTANT("GL_FILTER", GL_FILTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_TEXTURE", GL_VERTEX_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_TEXTURE", GL_TESS_CONTROL_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_TEXTURE", GL_TESS_EVALUATION_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_TEXTURE", GL_GEOMETRY_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_TEXTURE", GL_FRAGMENT_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_TEXTURE", GL_COMPUTE_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SHADOW 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SHADOW", GL_TEXTURE_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_GATHER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_GATHER", GL_TEXTURE_GATHER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_GATHER_SHADOW 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_GATHER_SHADOW", GL_TEXTURE_GATHER_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_IMAGE_LOAD 
    REGISTER_LONG_CONSTANT("GL_SHADER_IMAGE_LOAD", GL_SHADER_IMAGE_LOAD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_IMAGE_STORE 
    REGISTER_LONG_CONSTANT("GL_SHADER_IMAGE_STORE", GL_SHADER_IMAGE_STORE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_IMAGE_ATOMIC 
    REGISTER_LONG_CONSTANT("GL_SHADER_IMAGE_ATOMIC", GL_SHADER_IMAGE_ATOMIC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_TEXEL_SIZE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_TEXEL_SIZE", GL_IMAGE_TEXEL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_COMPATIBILITY_CLASS 
    REGISTER_LONG_CONSTANT("GL_IMAGE_COMPATIBILITY_CLASS", GL_IMAGE_COMPATIBILITY_CLASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_PIXEL_FORMAT 
    REGISTER_LONG_CONSTANT("GL_IMAGE_PIXEL_FORMAT", GL_IMAGE_PIXEL_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_PIXEL_TYPE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_PIXEL_TYPE", GL_IMAGE_PIXEL_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 
    REGISTER_LONG_CONSTANT("GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST", GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 
    REGISTER_LONG_CONSTANT("GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST", GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 
    REGISTER_LONG_CONSTANT("GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE", GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 
    REGISTER_LONG_CONSTANT("GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE", GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED_BLOCK_WIDTH", GL_TEXTURE_COMPRESSED_BLOCK_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT", GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED_BLOCK_SIZE", GL_TEXTURE_COMPRESSED_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLEAR_BUFFER 
    REGISTER_LONG_CONSTANT("GL_CLEAR_BUFFER", GL_CLEAR_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW", GL_TEXTURE_VIEW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_COMPATIBILITY_CLASS 
    REGISTER_LONG_CONSTANT("GL_VIEW_COMPATIBILITY_CLASS", GL_VIEW_COMPATIBILITY_CLASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FULL_SUPPORT 
    REGISTER_LONG_CONSTANT("GL_FULL_SUPPORT", GL_FULL_SUPPORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CAVEAT_SUPPORT 
    REGISTER_LONG_CONSTANT("GL_CAVEAT_SUPPORT", GL_CAVEAT_SUPPORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_4_X_32 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_4_X_32", GL_IMAGE_CLASS_4_X_32, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_2_X_32 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_2_X_32", GL_IMAGE_CLASS_2_X_32, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_1_X_32 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_1_X_32", GL_IMAGE_CLASS_1_X_32, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_4_X_16 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_4_X_16", GL_IMAGE_CLASS_4_X_16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_2_X_16 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_2_X_16", GL_IMAGE_CLASS_2_X_16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_1_X_16 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_1_X_16", GL_IMAGE_CLASS_1_X_16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_4_X_8 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_4_X_8", GL_IMAGE_CLASS_4_X_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_2_X_8 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_2_X_8", GL_IMAGE_CLASS_2_X_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_1_X_8 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_1_X_8", GL_IMAGE_CLASS_1_X_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_11_11_10 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_11_11_10", GL_IMAGE_CLASS_11_11_10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_10_10_10_2 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_10_10_10_2", GL_IMAGE_CLASS_10_10_10_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_128_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_128_BITS", GL_VIEW_CLASS_128_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_96_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_96_BITS", GL_VIEW_CLASS_96_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_64_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_64_BITS", GL_VIEW_CLASS_64_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_48_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_48_BITS", GL_VIEW_CLASS_48_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_32_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_32_BITS", GL_VIEW_CLASS_32_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_24_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_24_BITS", GL_VIEW_CLASS_24_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_16_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_16_BITS", GL_VIEW_CLASS_16_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_8_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_8_BITS", GL_VIEW_CLASS_8_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_S3TC_DXT1_RGB 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_S3TC_DXT1_RGB", GL_VIEW_CLASS_S3TC_DXT1_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_S3TC_DXT1_RGBA 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_S3TC_DXT1_RGBA", GL_VIEW_CLASS_S3TC_DXT1_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_S3TC_DXT3_RGBA 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_S3TC_DXT3_RGBA", GL_VIEW_CLASS_S3TC_DXT3_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_S3TC_DXT5_RGBA 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_S3TC_DXT5_RGBA", GL_VIEW_CLASS_S3TC_DXT5_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_RGTC1_RED 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_RGTC1_RED", GL_VIEW_CLASS_RGTC1_RED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_RGTC2_RG 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_RGTC2_RG", GL_VIEW_CLASS_RGTC2_RG, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_BPTC_UNORM 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_BPTC_UNORM", GL_VIEW_CLASS_BPTC_UNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_BPTC_FLOAT 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_BPTC_FLOAT", GL_VIEW_CLASS_BPTC_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_UNIFORM", GL_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK", GL_UNIFORM_BLOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_INPUT 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_INPUT", GL_PROGRAM_INPUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_OUTPUT 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_OUTPUT", GL_PROGRAM_OUTPUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_VARIABLE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_VARIABLE", GL_BUFFER_VARIABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BLOCK 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BLOCK", GL_SHADER_STORAGE_BLOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SUBROUTINE", GL_VERTEX_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SUBROUTINE", GL_TESS_CONTROL_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SUBROUTINE", GL_TESS_EVALUATION_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SUBROUTINE", GL_GEOMETRY_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SUBROUTINE", GL_FRAGMENT_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SUBROUTINE", GL_COMPUTE_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SUBROUTINE_UNIFORM", GL_VERTEX_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SUBROUTINE_UNIFORM", GL_TESS_CONTROL_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SUBROUTINE_UNIFORM", GL_TESS_EVALUATION_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SUBROUTINE_UNIFORM", GL_GEOMETRY_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SUBROUTINE_UNIFORM", GL_FRAGMENT_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SUBROUTINE_UNIFORM", GL_COMPUTE_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_VARYING 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_VARYING", GL_TRANSFORM_FEEDBACK_VARYING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_RESOURCES 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_RESOURCES", GL_ACTIVE_RESOURCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_MAX_NAME_LENGTH", GL_MAX_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_NUM_ACTIVE_VARIABLES 
    REGISTER_LONG_CONSTANT("GL_MAX_NUM_ACTIVE_VARIABLES", GL_MAX_NUM_ACTIVE_VARIABLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_NUM_COMPATIBLE_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_MAX_NUM_COMPATIBLE_SUBROUTINES", GL_MAX_NUM_COMPATIBLE_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_NAME_LENGTH", GL_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TYPE 
    REGISTER_LONG_CONSTANT("GL_TYPE", GL_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ARRAY_SIZE 
    REGISTER_LONG_CONSTANT("GL_ARRAY_SIZE", GL_ARRAY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OFFSET 
    REGISTER_LONG_CONSTANT("GL_OFFSET", GL_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLOCK_INDEX 
    REGISTER_LONG_CONSTANT("GL_BLOCK_INDEX", GL_BLOCK_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ARRAY_STRIDE 
    REGISTER_LONG_CONSTANT("GL_ARRAY_STRIDE", GL_ARRAY_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MATRIX_STRIDE 
    REGISTER_LONG_CONSTANT("GL_MATRIX_STRIDE", GL_MATRIX_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IS_ROW_MAJOR 
    REGISTER_LONG_CONSTANT("GL_IS_ROW_MAJOR", GL_IS_ROW_MAJOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_INDEX 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_INDEX", GL_ATOMIC_COUNTER_BUFFER_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_BUFFER_BINDING", GL_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_DATA_SIZE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_DATA_SIZE", GL_BUFFER_DATA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_ACTIVE_VARIABLES 
    REGISTER_LONG_CONSTANT("GL_NUM_ACTIVE_VARIABLES", GL_NUM_ACTIVE_VARIABLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_VARIABLES 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_VARIABLES", GL_ACTIVE_VARIABLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_VERTEX_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_VERTEX_SHADER", GL_REFERENCED_BY_VERTEX_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_TESS_CONTROL_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_TESS_CONTROL_SHADER", GL_REFERENCED_BY_TESS_CONTROL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_TESS_EVALUATION_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_TESS_EVALUATION_SHADER", GL_REFERENCED_BY_TESS_EVALUATION_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_GEOMETRY_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_GEOMETRY_SHADER", GL_REFERENCED_BY_GEOMETRY_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_FRAGMENT_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_FRAGMENT_SHADER", GL_REFERENCED_BY_FRAGMENT_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_COMPUTE_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_COMPUTE_SHADER", GL_REFERENCED_BY_COMPUTE_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TOP_LEVEL_ARRAY_SIZE 
    REGISTER_LONG_CONSTANT("GL_TOP_LEVEL_ARRAY_SIZE", GL_TOP_LEVEL_ARRAY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TOP_LEVEL_ARRAY_STRIDE 
    REGISTER_LONG_CONSTANT("GL_TOP_LEVEL_ARRAY_STRIDE", GL_TOP_LEVEL_ARRAY_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOCATION 
    REGISTER_LONG_CONSTANT("GL_LOCATION", GL_LOCATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOCATION_INDEX 
    REGISTER_LONG_CONSTANT("GL_LOCATION_INDEX", GL_LOCATION_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IS_PER_PATCH 
    REGISTER_LONG_CONSTANT("GL_IS_PER_PATCH", GL_IS_PER_PATCH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER", GL_SHADER_STORAGE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER_BINDING", GL_SHADER_STORAGE_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER_START 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER_START", GL_SHADER_STORAGE_BUFFER_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER_SIZE", GL_SHADER_STORAGE_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS", GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS", GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS", GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS", GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS", GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS", GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS", GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 
    REGISTER_LONG_CONSTANT("GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS", GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SHADER_STORAGE_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_SHADER_STORAGE_BLOCK_SIZE", GL_MAX_SHADER_STORAGE_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT", GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BARRIER_BIT", GL_SHADER_STORAGE_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES", GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_STENCIL_TEXTURE_MODE 
    REGISTER_LONG_CONSTANT("GL_DEPTH_STENCIL_TEXTURE_MODE", GL_DEPTH_STENCIL_TEXTURE_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_OFFSET 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_OFFSET", GL_TEXTURE_BUFFER_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_SIZE", GL_TEXTURE_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT", GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW_MIN_LEVEL 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW_MIN_LEVEL", GL_TEXTURE_VIEW_MIN_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW_NUM_LEVELS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW_NUM_LEVELS", GL_TEXTURE_VIEW_NUM_LEVELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW_MIN_LAYER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW_MIN_LAYER", GL_TEXTURE_VIEW_MIN_LAYER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW_NUM_LAYERS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW_NUM_LAYERS", GL_TEXTURE_VIEW_NUM_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_IMMUTABLE_LEVELS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_IMMUTABLE_LEVELS", GL_TEXTURE_IMMUTABLE_LEVELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_BINDING 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_BINDING", GL_VERTEX_ATTRIB_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_RELATIVE_OFFSET 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_RELATIVE_OFFSET", GL_VERTEX_ATTRIB_RELATIVE_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_BINDING_DIVISOR 
    REGISTER_LONG_CONSTANT("GL_VERTEX_BINDING_DIVISOR", GL_VERTEX_BINDING_DIVISOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_BINDING_OFFSET 
    REGISTER_LONG_CONSTANT("GL_VERTEX_BINDING_OFFSET", GL_VERTEX_BINDING_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_BINDING_STRIDE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_BINDING_STRIDE", GL_VERTEX_BINDING_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET", GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATTRIB_BINDINGS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATTRIB_BINDINGS", GL_MAX_VERTEX_ATTRIB_BINDINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_BINDING_BUFFER 
    REGISTER_LONG_CONSTANT("GL_VERTEX_BINDING_BUFFER", GL_VERTEX_BINDING_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DISPLAY_LIST 
    REGISTER_LONG_CONSTANT("GL_DISPLAY_LIST", GL_DISPLAY_LIST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATTRIB_STRIDE 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATTRIB_STRIDE", GL_MAX_VERTEX_ATTRIB_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED", GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_BINDING", GL_TEXTURE_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_PERSISTENT_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_PERSISTENT_BIT", GL_MAP_PERSISTENT_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_COHERENT_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_COHERENT_BIT", GL_MAP_COHERENT_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DYNAMIC_STORAGE_BIT 
    REGISTER_LONG_CONSTANT("GL_DYNAMIC_STORAGE_BIT", GL_DYNAMIC_STORAGE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIENT_STORAGE_BIT 
    REGISTER_LONG_CONSTANT("GL_CLIENT_STORAGE_BIT", GL_CLIENT_STORAGE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT", GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_IMMUTABLE_STORAGE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_IMMUTABLE_STORAGE", GL_BUFFER_IMMUTABLE_STORAGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_STORAGE_FLAGS 
    REGISTER_LONG_CONSTANT("GL_BUFFER_STORAGE_FLAGS", GL_BUFFER_STORAGE_FLAGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLEAR_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_CLEAR_TEXTURE", GL_CLEAR_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOCATION_COMPONENT 
    REGISTER_LONG_CONSTANT("GL_LOCATION_COMPONENT", GL_LOCATION_COMPONENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_INDEX", GL_TRANSFORM_FEEDBACK_BUFFER_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE", GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BUFFER 
    REGISTER_LONG_CONSTANT("GL_QUERY_BUFFER", GL_QUERY_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BUFFER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_BUFFER_BARRIER_BIT", GL_QUERY_BUFFER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_QUERY_BUFFER_BINDING", GL_QUERY_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_RESULT_NO_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_RESULT_NO_WAIT", GL_QUERY_RESULT_NO_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIRROR_CLAMP_TO_EDGE 
    REGISTER_LONG_CONSTANT("GL_MIRROR_CLAMP_TO_EDGE", GL_MIRROR_CLAMP_TO_EDGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_LOST 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_LOST", GL_CONTEXT_LOST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEGATIVE_ONE_TO_ONE 
    REGISTER_LONG_CONSTANT("GL_NEGATIVE_ONE_TO_ONE", GL_NEGATIVE_ONE_TO_ONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ZERO_TO_ONE 
    REGISTER_LONG_CONSTANT("GL_ZERO_TO_ONE", GL_ZERO_TO_ONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_ORIGIN 
    REGISTER_LONG_CONSTANT("GL_CLIP_ORIGIN", GL_CLIP_ORIGIN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DEPTH_MODE 
    REGISTER_LONG_CONSTANT("GL_CLIP_DEPTH_MODE", GL_CLIP_DEPTH_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_WAIT_INVERTED 
    REGISTER_LONG_CONSTANT("GL_QUERY_WAIT_INVERTED", GL_QUERY_WAIT_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_NO_WAIT_INVERTED 
    REGISTER_LONG_CONSTANT("GL_QUERY_NO_WAIT_INVERTED", GL_QUERY_NO_WAIT_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BY_REGION_WAIT_INVERTED 
    REGISTER_LONG_CONSTANT("GL_QUERY_BY_REGION_WAIT_INVERTED", GL_QUERY_BY_REGION_WAIT_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BY_REGION_NO_WAIT_INVERTED 
    REGISTER_LONG_CONSTANT("GL_QUERY_BY_REGION_NO_WAIT_INVERTED", GL_QUERY_BY_REGION_NO_WAIT_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_CULL_DISTANCES 
    REGISTER_LONG_CONSTANT("GL_MAX_CULL_DISTANCES", GL_MAX_CULL_DISTANCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES", GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_TARGET 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_TARGET", GL_TEXTURE_TARGET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_TARGET 
    REGISTER_LONG_CONSTANT("GL_QUERY_TARGET", GL_QUERY_TARGET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GUILTY_CONTEXT_RESET 
    REGISTER_LONG_CONSTANT("GL_GUILTY_CONTEXT_RESET", GL_GUILTY_CONTEXT_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INNOCENT_CONTEXT_RESET 
    REGISTER_LONG_CONSTANT("GL_INNOCENT_CONTEXT_RESET", GL_INNOCENT_CONTEXT_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNKNOWN_CONTEXT_RESET 
    REGISTER_LONG_CONSTANT("GL_UNKNOWN_CONTEXT_RESET", GL_UNKNOWN_CONTEXT_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RESET_NOTIFICATION_STRATEGY 
    REGISTER_LONG_CONSTANT("GL_RESET_NOTIFICATION_STRATEGY", GL_RESET_NOTIFICATION_STRATEGY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOSE_CONTEXT_ON_RESET 
    REGISTER_LONG_CONSTANT("GL_LOSE_CONTEXT_ON_RESET", GL_LOSE_CONTEXT_ON_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NO_RESET_NOTIFICATION 
    REGISTER_LONG_CONSTANT("GL_NO_RESET_NOTIFICATION", GL_NO_RESET_NOTIFICATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT", GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_RELEASE_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_RELEASE_BEHAVIOR", GL_CONTEXT_RELEASE_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH", GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_BINARY_FORMAT_SPIR_V 
    REGISTER_LONG_CONSTANT("GL_SHADER_BINARY_FORMAT_SPIR_V", GL_SHADER_BINARY_FORMAT_SPIR_V, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SPIR_V_BINARY 
    REGISTER_LONG_CONSTANT("GL_SPIR_V_BINARY", GL_SPIR_V_BINARY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PARAMETER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_PARAMETER_BUFFER", GL_PARAMETER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PARAMETER_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_PARAMETER_BUFFER_BINDING", GL_PARAMETER_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAG_NO_ERROR_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAG_NO_ERROR_BIT", GL_CONTEXT_FLAG_NO_ERROR_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTICES_SUBMITTED 
    REGISTER_LONG_CONSTANT("GL_VERTICES_SUBMITTED", GL_VERTICES_SUBMITTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVES_SUBMITTED 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVES_SUBMITTED", GL_PRIMITIVES_SUBMITTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SHADER_INVOCATIONS", GL_VERTEX_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SHADER_PATCHES 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SHADER_PATCHES", GL_TESS_CONTROL_SHADER_PATCHES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SHADER_INVOCATIONS", GL_TESS_EVALUATION_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED", GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SHADER_INVOCATIONS", GL_FRAGMENT_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SHADER_INVOCATIONS", GL_COMPUTE_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIPPING_INPUT_PRIMITIVES 
    REGISTER_LONG_CONSTANT("GL_CLIPPING_INPUT_PRIMITIVES", GL_CLIPPING_INPUT_PRIMITIVES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIPPING_OUTPUT_PRIMITIVES 
    REGISTER_LONG_CONSTANT("GL_CLIPPING_OUTPUT_PRIMITIVES", GL_CLIPPING_OUTPUT_PRIMITIVES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_CLAMP 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_CLAMP", GL_POLYGON_OFFSET_CLAMP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SPIR_V_EXTENSIONS 
    REGISTER_LONG_CONSTANT("GL_SPIR_V_EXTENSIONS", GL_SPIR_V_EXTENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_SPIR_V_EXTENSIONS 
    REGISTER_LONG_CONSTANT("GL_NUM_SPIR_V_EXTENSIONS", GL_NUM_SPIR_V_EXTENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MAX_ANISOTROPY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MAX_ANISOTROPY", GL_TEXTURE_MAX_ANISOTROPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_MAX_ANISOTROPY 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_MAX_ANISOTROPY", GL_MAX_TEXTURE_MAX_ANISOTROPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_OVERFLOW 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_OVERFLOW", GL_TRANSFORM_FEEDBACK_OVERFLOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW", GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW, CONST_CS|CONST_PERSISTENT);
#endif
    return SUCCESS;
}

/**
 * Register
 * --------------------------------
 */
static zend_function_entry glfw_functions[] = {
    ZEND_RAW_NAMED_FE(glfwInit, zif_glfwInit, NULL) 
    ZEND_RAW_NAMED_FE(glfwTerminate, zif_glfwTerminate, NULL) 
    ZEND_RAW_NAMED_FE(glfwGetVersion, zif_glfwGetVersion, arginfo_glfwGetVersion) 
    ZEND_RAW_NAMED_FE(glfwGetVersionString, zif_glfwGetVersionString, NULL) 
    ZEND_RAW_NAMED_FE(glfwMakeContextCurrent, zif_glfwMakeContextCurrent, arginfo_glfwMakeContextCurrent) 
    ZEND_RAW_NAMED_FE(glfwGetCurrentContext, zif_glfwGetCurrentContext, NULL) 
    ZEND_RAW_NAMED_FE(glfwSwapInterval, zif_glfwSwapInterval, arginfo_glfwSwapInterval) 
    ZEND_RAW_NAMED_FE(glfwExtensionSupported, zif_glfwExtensionSupported, arginfo_glfwExtensionSupported) 
    ZEND_RAW_NAMED_FE(glfwGetProcAddress, zif_glfwGetProcAddress, arginfo_glfwGetProcAddress) 
    ZEND_RAW_NAMED_FE(glfwDefaultWindowHints, zif_glfwDefaultWindowHints, NULL) 
    ZEND_RAW_NAMED_FE(glfwWindowHint, zif_glfwWindowHint, arginfo_glfwWindowHint) 
    ZEND_RAW_NAMED_FE(glfwDestroyWindow, zif_glfwDestroyWindow, arginfo_glfwDestroyWindow) 
    ZEND_RAW_NAMED_FE(glfwCreateWindow, zif_glfwCreateWindow, arginfo_glfwCreateWindow) 
    ZEND_RAW_NAMED_FE(glfwWindowShouldClose, zif_glfwWindowShouldClose, arginfo_glfwWindowShouldClose) 
    ZEND_RAW_NAMED_FE(glfwSetWindowShouldClose, zif_glfwSetWindowShouldClose, arginfo_glfwSetWindowShouldClose) 
    ZEND_RAW_NAMED_FE(glfwSwapBuffers, zif_glfwSwapBuffers, arginfo_glfwSwapBuffers) 
    ZEND_RAW_NAMED_FE(glfwPollEvents, zif_glfwPollEvents, NULL) 
    ZEND_RAW_NAMED_FE(glfwGetTime, zif_glfwGetTime, NULL) 
    ZEND_RAW_NAMED_FE(glfwCreateStandardCursor, zif_glfwCreateStandardCursor, arginfo_glfwCreateStandardCursor) 
    ZEND_RAW_NAMED_FE(glfwDestroyCursor, zif_glfwDestroyCursor, arginfo_glfwDestroyCursor) 
    ZEND_RAW_NAMED_FE(glfwGetClipboardString, zif_glfwGetClipboardString, arginfo_glfwGetClipboardString) 
    ZEND_RAW_NAMED_FE(glfwGetCursorPos, zif_glfwGetCursorPos, arginfo_glfwGetCursorPos) 
    ZEND_RAW_NAMED_FE(glfwGetKey, zif_glfwGetKey, arginfo_glfwGetKey) 
    ZEND_RAW_NAMED_FE(glfwGetMouseButton, zif_glfwGetMouseButton, arginfo_glfwGetMouseButton) 
    ZEND_RAW_NAMED_FE(glfwSetInputMode, zif_glfwSetInputMode, arginfo_glfwSetInputMode) 
    ZEND_RAW_NAMED_FE(glEnable, zif_glEnable, arginfo_glEnable) 
    ZEND_RAW_NAMED_FE(glDisable, zif_glDisable, arginfo_glDisable) 
    ZEND_RAW_NAMED_FE(glPolygonMode, zif_glPolygonMode, arginfo_glPolygonMode) 
    ZEND_RAW_NAMED_FE(glBlendFunc, zif_glBlendFunc, arginfo_glBlendFunc) 
    ZEND_RAW_NAMED_FE(glViewport, zif_glViewport, arginfo_glViewport) 
    ZEND_RAW_NAMED_FE(glClearColor, zif_glClearColor, arginfo_glClearColor) 
    ZEND_RAW_NAMED_FE(glClear, zif_glClear, arginfo_glClear) 
    ZEND_RAW_NAMED_FE(glGenBuffers, zif_glGenBuffers, arginfo_glGenBuffers) 
    ZEND_RAW_NAMED_FE(glDeleteBuffers, zif_glDeleteBuffers, arginfo_glDeleteBuffers) 
    ZEND_RAW_NAMED_FE(glGenVertexArrays, zif_glGenVertexArrays, arginfo_glGenVertexArrays) 
    ZEND_RAW_NAMED_FE(glDeleteVertexArrays, zif_glDeleteVertexArrays, arginfo_glDeleteVertexArrays) 
    ZEND_RAW_NAMED_FE(glBindBuffer, zif_glBindBuffer, arginfo_glBindBuffer) 
    ZEND_RAW_NAMED_FE(glBindVertexArray, zif_glBindVertexArray, arginfo_glBindVertexArray) 
    ZEND_RAW_NAMED_FE(glBufferData, zif_glBufferData, arginfo_glBufferData) 
    ZEND_RAW_NAMED_FE(glBufferDataFloat, zif_glBufferDataFloat, arginfo_glBufferDataFloat) 
    ZEND_RAW_NAMED_FE(glBufferDataInt, zif_glBufferDataInt, arginfo_glBufferDataInt) 
    ZEND_RAW_NAMED_FE(glVertexAttribPointer, zif_glVertexAttribPointer, arginfo_glVertexAttribPointer) 
    ZEND_RAW_NAMED_FE(glEnableVertexAttribArray, zif_glEnableVertexAttribArray, arginfo_glEnableVertexAttribArray) 
    ZEND_RAW_NAMED_FE(glDrawArrays, zif_glDrawArrays, arginfo_glDrawArrays) 
    ZEND_RAW_NAMED_FE(glDrawElements, zif_glDrawElements, arginfo_glDrawElements) 
    ZEND_RAW_NAMED_FE(glCreateShader, zif_glCreateShader, arginfo_glCreateShader) 
    ZEND_RAW_NAMED_FE(glCreateProgram, zif_glCreateProgram, NULL) 
    ZEND_RAW_NAMED_FE(glShaderSource, zif_glShaderSource, arginfo_glShaderSource) 
    ZEND_RAW_NAMED_FE(glCompileShader, zif_glCompileShader, arginfo_glCompileShader) 
    ZEND_RAW_NAMED_FE(glDeleteShader, zif_glDeleteShader, arginfo_glDeleteShader) 
    ZEND_RAW_NAMED_FE(glAttachShader, zif_glAttachShader, arginfo_glAttachShader) 
    ZEND_RAW_NAMED_FE(glGetUniformLocation, zif_glGetUniformLocation, arginfo_glGetUniformLocation) 
    ZEND_RAW_NAMED_FE(glUniform1i, zif_glUniform1i, arginfo_glUniform1i) 
    ZEND_RAW_NAMED_FE(glUniform2i, zif_glUniform2i, arginfo_glUniform2i) 
    ZEND_RAW_NAMED_FE(glUniform3i, zif_glUniform3i, arginfo_glUniform3i) 
    ZEND_RAW_NAMED_FE(glUniform4i, zif_glUniform4i, arginfo_glUniform4i) 
    ZEND_RAW_NAMED_FE(glUniform1f, zif_glUniform1f, arginfo_glUniform1f) 
    ZEND_RAW_NAMED_FE(glUniform2f, zif_glUniform2f, arginfo_glUniform2f) 
    ZEND_RAW_NAMED_FE(glUniform3f, zif_glUniform3f, arginfo_glUniform3f) 
    ZEND_RAW_NAMED_FE(glUniform4f, zif_glUniform4f, arginfo_glUniform4f) 
    ZEND_RAW_NAMED_FE(glUniformMatrix4fv, zif_glUniformMatrix4fv, arginfo_glUniformMatrix4fv) 
    ZEND_RAW_NAMED_FE(glLinkProgram, zif_glLinkProgram, arginfo_glLinkProgram) 
    ZEND_RAW_NAMED_FE(glGetShaderiv, zif_glGetShaderiv, arginfo_glGetShaderiv) 
    ZEND_RAW_NAMED_FE(glGetProgramiv, zif_glGetProgramiv, arginfo_glGetProgramiv) 
    ZEND_RAW_NAMED_FE(glUseProgram, zif_glUseProgram, arginfo_glUseProgram) 
    ZEND_RAW_NAMED_FE(glGenTextures, zif_glGenTextures, arginfo_glGenTextures) 
    ZEND_RAW_NAMED_FE(glBindTexture, zif_glBindTexture, arginfo_glBindTexture) 
    ZEND_RAW_NAMED_FE(glTexParameteri, zif_glTexParameteri, arginfo_glTexParameteri) 
    ZEND_RAW_NAMED_FE(glTextureParameteri, zif_glTextureParameteri, arginfo_glTextureParameteri) 
    ZEND_RAW_NAMED_FE(glTexParameterf, zif_glTexParameterf, arginfo_glTexParameterf) 
    ZEND_RAW_NAMED_FE(glTextureParameterf, zif_glTextureParameterf, arginfo_glTextureParameterf) 
    ZEND_RAW_NAMED_FE(glTexImage2D, zif_glTexImage2D, arginfo_glTexImage2D) 
    ZEND_RAW_NAMED_FE(glGenerateMipmap, zif_glGenerateMipmap, arginfo_glGenerateMipmap) 
    ZEND_RAW_NAMED_FE(glActiveTexture, zif_glActiveTexture, arginfo_glActiveTexture) 
    ZEND_RAW_NAMED_FE(stbi_load, zif_stbi_load, arginfo_stbi_load) 
#ifdef PHP_FE_END
    PHP_FE_END
#else
    {NULL, NULL, NULL}
#endif
};

zend_module_entry glfw_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_GLFW_EXTNAME,
    glfw_functions,
    PHP_MINIT(glfw),
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_GLFW_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GLFW
ZEND_GET_MODULE(glfw)
#endif