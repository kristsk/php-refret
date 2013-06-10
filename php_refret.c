#include <php.h>

#include "php_refret.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_refret_call_user_func, 0, 1, 1)
	ZEND_ARG_INFO(0, function_name)
	ZEND_ARG_INFO(0, parmeter)
	ZEND_ARG_INFO(0, ...)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_refret_call_user_func_array, 0, 1, 2)
	ZEND_ARG_INFO(0, function_name)
	ZEND_ARG_INFO(0, parameters) /* ARRAY_INFO(0, parameters, 1) */
ZEND_END_ARG_INFO()

zend_function_entry refret_functions[] = {
  PHP_FE(refret_call_user_func, 		arginfo_refret_call_user_func)
  PHP_FE(refret_call_user_func_array, 	arginfo_refret_call_user_func_array)
  { NULL, NULL, NULL }
};

zend_module_entry refret_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_REFRET_EXTNAME,
  refret_functions,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  PHP_REFRET_VERSION,
  STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(refret)

PHP_FUNCTION(refret_call_user_func) 
{
	zval *retval_ptr = NULL;
	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f*", &fci, &fci_cache, &fci.params, &fci.param_count) == FAILURE) {
		return;
	}

	fci.retval_ptr_ptr = &retval_ptr;

	if (zend_call_function(&fci, &fci_cache TSRMLS_CC) == SUCCESS && fci.retval_ptr_ptr && *fci.retval_ptr_ptr) {
     	if (Z_ISREF_P(retval_ptr) && return_value_ptr) {
			if (return_value) {
				zval_ptr_dtor(&return_value);
			}
		    *return_value_ptr = retval_ptr;
        }
    	else {
    		COPY_PZVAL_TO_ZVAL(*return_value, *fci.retval_ptr_ptr);
    	}
	}

	if (fci.params) {
		efree(fci.params);
	}
}


PHP_FUNCTION(refret_call_user_func_array) 
{
	zval *params, *retval_ptr = NULL;
	zend_fcall_info fci;
	zend_fcall_info_cache fci_cache;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "fa/", &fci, &fci_cache, &params) == FAILURE) {
		return;
	}

	zend_fcall_info_args(&fci, params TSRMLS_CC);
	fci.retval_ptr_ptr = &retval_ptr;

	if (zend_call_function(&fci, &fci_cache TSRMLS_CC) == SUCCESS && fci.retval_ptr_ptr && *fci.retval_ptr_ptr) {
     	if (Z_ISREF_P(retval_ptr) && return_value_ptr) {
			if (return_value) {
				zval_ptr_dtor(&return_value);
			}
		    *return_value_ptr = retval_ptr;
        }
    	else {
    		COPY_PZVAL_TO_ZVAL(*return_value, *fci.retval_ptr_ptr);
    	}
	}

	zend_fcall_info_args_clear(&fci, 1);
}
