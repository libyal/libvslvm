/*
 * Python bindings module for libvslvm (pyvslvm)
 *
 * Copyright (C) 2014-2021, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvslvm.h"
#include "pyvslvm_error.h"
#include "pyvslvm_file_object_io_handle.h"
#include "pyvslvm_handle.h"
#include "pyvslvm_libbfio.h"
#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_logical_volume.h"
#include "pyvslvm_logical_volumes.h"
#include "pyvslvm_physical_volume.h"
#include "pyvslvm_physical_volumes.h"
#include "pyvslvm_python.h"
#include "pyvslvm_segment.h"
#include "pyvslvm_segments.h"
#include "pyvslvm_stripe.h"
#include "pyvslvm_stripes.h"
#include "pyvslvm_unused.h"
#include "pyvslvm_volume_group.h"

#if !defined( LIBVSLVM_HAVE_BFIO )

LIBVSLVM_EXTERN \
int libvslvm_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libvslvm_error_t **error );

#endif /* !defined( LIBVSLVM_HAVE_BFIO ) */

/* The pyvslvm module methods
 */
PyMethodDef pyvslvm_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pyvslvm_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	{ "check_volume_signature",
	  (PyCFunction) pyvslvm_check_volume_signature,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_volume_signature(filename) -> Boolean\n"
	  "\n"
	  "Checks if a volume has a Linux Logical Volume Manager (LVM) signature." },

	{ "check_volume_signature_file_object",
	  (PyCFunction) pyvslvm_check_volume_signature_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_volume_signature_file_object(file_object) -> Boolean\n"
	  "\n"
	  "Checks if a volume has a Linux Logical Volume Manager (LVM) signature using a file-like object." },

	{ "open",
	  (PyCFunction) pyvslvm_open_new_handle,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a handle." },

	{ "open_file_object",
	  (PyCFunction) pyvslvm_open_new_handle_with_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> Object\n"
	  "\n"
	  "Opens a handle using a file-like object." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pyvslvm/libvslvm version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_get_version(
           PyObject *self PYVSLVM_ATTRIBUTE_UNUSED,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( self )
	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libvslvm_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

/* Checks if a volume has a Linux Logical Volume Manager (LVM) signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_check_volume_signature(
           PyObject *self PYVSLVM_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	const char *filename_narrow = NULL;
	static char *function       = "pyvslvm_check_volume_signature";
	static char *keyword_list[] = { "filename", NULL };
	int result                  = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	PYVSLVM_UNREFERENCED_PARAMETER( self )

	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|",
	     keyword_list,
	     &string_object ) == 0 )
	{
		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pyvslvm_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libvslvm_check_volume_signature_wide(
		          filename_wide,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyvslvm_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvslvm_check_volume_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

		if( result == -1 )
		{
			pyvslvm_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check volume signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyvslvm_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvslvm_check_volume_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		if( result == -1 )
		{
			pyvslvm_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check volume signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Checks if a volume has a Linux Logical Volume Manager (LVM) signature using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_check_volume_signature_file_object(
           PyObject *self PYVSLVM_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object            = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	static char *function            = "pyvslvm_check_volume_signature_file_object";
	static char *keyword_list[]      = { "file_object", NULL };
	int result                       = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|",
	     keyword_list,
	     &file_object ) == 0 )
	{
		return( NULL );
	}
	if( pyvslvm_file_object_initialize(
	     &file_io_handle,
	     file_object,
	     &error ) != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_check_volume_signature_file_io_handle(
	          file_io_handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to check volume signature.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     &error ) != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( result != 0 )
	{
		Py_IncRef(
		 (PyObject *) Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 (PyObject *) Py_False );

	return( Py_False );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

/* Creates a new handle object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_open_new_handle(
           PyObject *self PYVSLVM_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	pyvslvm_handle_t *pyvslvm_handle = NULL;
	static char *function            = "pyvslvm_open_new_handle";

	PYVSLVM_UNREFERENCED_PARAMETER( self )

	/* PyObject_New does not invoke tp_init
	 */
	pyvslvm_handle = PyObject_New(
	                  struct pyvslvm_handle,
	                  &pyvslvm_handle_type_object );

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
	if( pyvslvm_handle_init(
	     pyvslvm_handle ) != 0 )
	{
		goto on_error;
	}
	if( pyvslvm_handle_open(
	     pyvslvm_handle,
	     arguments,
	     keywords ) == NULL )
	{
		goto on_error;
	}
	return( (PyObject *) pyvslvm_handle );

on_error:
	if( pyvslvm_handle != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_handle );
	}
	return( NULL );
}

/* Creates a new handle object and opens it using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_open_new_handle_with_file_object(
           PyObject *self PYVSLVM_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	pyvslvm_handle_t *pyvslvm_handle = NULL;
	static char *function            = "pyvslvm_open_new_handle_with_file_object";

	PYVSLVM_UNREFERENCED_PARAMETER( self )

	/* PyObject_New does not invoke tp_init
	 */
	pyvslvm_handle = PyObject_New(
	                  struct pyvslvm_handle,
	                  &pyvslvm_handle_type_object );

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
	if( pyvslvm_handle_init(
	     pyvslvm_handle ) != 0 )
	{
		goto on_error;
	}
	if( pyvslvm_handle_open_file_object(
	     pyvslvm_handle,
	     arguments,
	     keywords ) == NULL )
	{
		goto on_error;
	}
	return( (PyObject *) pyvslvm_handle );

on_error:
	if( pyvslvm_handle != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_handle );
	}
	return( NULL );
}

#if PY_MAJOR_VERSION >= 3

/* The pyvslvm module definition
 */
PyModuleDef pyvslvm_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pyvslvm",
	/* m_doc */
	"Python libvslvm module (pyvslvm).",
	/* m_size */
	-1,
	/* m_methods */
	pyvslvm_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pyvslvm module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pyvslvm(
                void )
#else
PyMODINIT_FUNC initpyvslvm(
                void )
#endif
{
	PyObject *module           = NULL;
	PyGILState_STATE gil_state = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libvslvm_notify_set_stream(
	 stderr,
	 NULL );
	libvslvm_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pyvslvm_module_definition );
#else
	module = Py_InitModule3(
	          "pyvslvm",
	          pyvslvm_module_methods,
	          "Python libvslvm module (pyvslvm)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
#if PY_VERSION_HEX < 0x03070000
	PyEval_InitThreads();
#endif
	gil_state = PyGILState_Ensure();

	/* Setup the handle type object
	 */
	pyvslvm_handle_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_handle_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_handle_type_object );

	PyModule_AddObject(
	 module,
	 "handle",
	 (PyObject *) &pyvslvm_handle_type_object );

	/* Setup the logical_volume type object
	 */
	pyvslvm_logical_volume_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_logical_volume_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_logical_volume_type_object );

	PyModule_AddObject(
	 module,
	 "logical_volume",
	 (PyObject *) &pyvslvm_logical_volume_type_object );

	/* Setup the logical_volumes type object
	 */
	pyvslvm_logical_volumes_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_logical_volumes_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_logical_volumes_type_object );

	PyModule_AddObject(
	 module,
	 "logical_volumes",
	 (PyObject *) &pyvslvm_logical_volumes_type_object );

	/* Setup the physical_volume type object
	 */
	pyvslvm_physical_volume_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_physical_volume_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_physical_volume_type_object );

	PyModule_AddObject(
	 module,
	 "physical_volume",
	 (PyObject *) &pyvslvm_physical_volume_type_object );

	/* Setup the physical_volumes type object
	 */
	pyvslvm_physical_volumes_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_physical_volumes_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_physical_volumes_type_object );

	PyModule_AddObject(
	 module,
	 "physical_volumes",
	 (PyObject *) &pyvslvm_physical_volumes_type_object );

	/* Setup the segment type object
	 */
	pyvslvm_segment_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_segment_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_segment_type_object );

	PyModule_AddObject(
	 module,
	 "segment",
	 (PyObject *) &pyvslvm_segment_type_object );

	/* Setup the segments type object
	 */
	pyvslvm_segments_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_segments_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_segments_type_object );

	PyModule_AddObject(
	 module,
	 "segments",
	 (PyObject *) &pyvslvm_segments_type_object );

	/* Setup the stripe type object
	 */
	pyvslvm_stripe_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_stripe_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_stripe_type_object );

	PyModule_AddObject(
	 module,
	 "stripe",
	 (PyObject *) &pyvslvm_stripe_type_object );

	/* Setup the stripes type object
	 */
	pyvslvm_stripes_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_stripes_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_stripes_type_object );

	PyModule_AddObject(
	 module,
	 "stripes",
	 (PyObject *) &pyvslvm_stripes_type_object );

	/* Setup the volume_group type object
	 */
	pyvslvm_volume_group_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_volume_group_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_volume_group_type_object );

	PyModule_AddObject(
	 module,
	 "volume_group",
	 (PyObject *) &pyvslvm_volume_group_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}

