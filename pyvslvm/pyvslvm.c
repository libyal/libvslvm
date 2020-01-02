/*
 * Python bindings module for libvslvm (pyvslvm)
 *
 * Copyright (C) 2014-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pyvslvm.h"
#include "pyvslvm_error.h"
#include "pyvslvm_file_object_io_handle.h"
#include "pyvslvm_handle.h"
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
	  "Checks if a file has a Linux Logical Volume Manager (LVM) volume system signature." },

	{ "check_volume_signature_file_object",
	  (PyCFunction) pyvslvm_check_volume_signature_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_volume_signature_file_object(filename) -> Boolean\n"
	  "\n"
	  "Checks if a file has a Linux Logical Volume Manager (LVM) volume system signature using a file-like object." },

/* TODO: add open functions */

	/* Sentinel */
	{ NULL,
	  NULL,
	  0,
	  NULL}
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

/* Checks if the file has a Linux Logical Volume Manager (LVM) volume system signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_check_volume_signature(
           PyObject *self PYVSLVM_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	static char *function        = "pyvslvm_check_volume_signature";
	static char *keyword_list[]  = { "filename", NULL };
	const char *filename_narrow  = NULL;
	int result                   = 0;

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
	     "|O",
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
		 "%s: unable to determine if string object is of type unicode.",
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
			 "%s: unable to convert unicode string to UTF-8.",
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
#endif
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

/* Checks if the file has a Linux Logical Volume Manager (LVM) volume system signature using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_check_volume_signature_file_object(
           PyObject *self PYVSLVM_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error         = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	PyObject *file_object            = NULL;
	static char *function            = "pyvslvm_check_volume_signature_file_object";
	static char *keyword_list[]      = { "file_object", NULL };
	int result                       = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
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
	PyObject *module                           = NULL;
	PyTypeObject *handle_type_object           = NULL;
	PyTypeObject *logical_volume_type_object   = NULL;
	PyTypeObject *logical_volumes_type_object  = NULL;
	PyTypeObject *physical_volume_type_object  = NULL;
	PyTypeObject *physical_volumes_type_object = NULL;
	PyTypeObject *segment_type_object          = NULL;
	PyTypeObject *segments_type_object         = NULL;
	PyTypeObject *stripe_type_object           = NULL;
	PyTypeObject *stripes_type_object          = NULL;
	PyTypeObject *volume_group_type_object     = NULL;
	PyGILState_STATE gil_state                 = 0;

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
	PyEval_InitThreads();

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

	handle_type_object = &pyvslvm_handle_type_object;

	PyModule_AddObject(
	 module,
	 "handle",
	 (PyObject *) handle_type_object );

	/* Setup the logical volume type object
	 */
	pyvslvm_logical_volume_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_logical_volume_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_logical_volume_type_object );

	logical_volume_type_object = &pyvslvm_logical_volume_type_object;

	PyModule_AddObject(
	 module,
	 "logical_volume",
	 (PyObject *) logical_volume_type_object );

	/* Setup the physical volume type object
	 */
	pyvslvm_physical_volume_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_physical_volume_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_physical_volume_type_object );

	physical_volume_type_object = &pyvslvm_physical_volume_type_object;

	PyModule_AddObject(
	 module,
	 "physical_volume",
	 (PyObject *) physical_volume_type_object );

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

	segment_type_object = &pyvslvm_segment_type_object;

	PyModule_AddObject(
	 module,
	 "segment",
	 (PyObject *) segment_type_object );

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

	stripe_type_object = &pyvslvm_stripe_type_object;

	PyModule_AddObject(
	 module,
	 "stripe",
	 (PyObject *) stripe_type_object );

	/* Setup the volume group type object
	 */
	pyvslvm_volume_group_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_volume_group_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_volume_group_type_object );

	volume_group_type_object = &pyvslvm_volume_group_type_object;

	PyModule_AddObject(
	 module,
	 "volume_group",
	 (PyObject *) volume_group_type_object );

	/* Setup the logical volumes type object
	 */
	pyvslvm_logical_volumes_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_logical_volumes_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_logical_volumes_type_object );

	logical_volumes_type_object = &pyvslvm_logical_volumes_type_object;

	PyModule_AddObject(
	 module,
	 "_logical_volumes",
	 (PyObject *) logical_volumes_type_object );

	/* Setup the physical volumes type object
	 */
	pyvslvm_physical_volumes_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyvslvm_physical_volumes_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyvslvm_physical_volumes_type_object );

	physical_volumes_type_object = &pyvslvm_physical_volumes_type_object;

	PyModule_AddObject(
	 module,
	 "_physical_volumes",
	 (PyObject *) physical_volumes_type_object );

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

	segments_type_object = &pyvslvm_segments_type_object;

	PyModule_AddObject(
	 module,
	 "_segments",
	 (PyObject *) segments_type_object );

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

	stripes_type_object = &pyvslvm_stripes_type_object;

	PyModule_AddObject(
	 module,
	 "_stripes",
	 (PyObject *) stripes_type_object );

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

