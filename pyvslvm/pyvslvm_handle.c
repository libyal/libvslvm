/*
 * Python object wrapper of libvslvm_handle_t
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
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pyvslvm_error.h"
#include "pyvslvm_file_object_io_handle.h"
#include "pyvslvm_file_objects_io_pool.h"
#include "pyvslvm_handle.h"
#include "pyvslvm_libbfio.h"
#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"
#include "pyvslvm_unused.h"
#include "pyvslvm_volume_group.h"

#if !defined( LIBVSLVM_HAVE_BFIO )

LIBVSLVM_EXTERN \
int libvslvm_handle_open_file_io_handle(
     libvslvm_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvslvm_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files_file_io_pool(
     libvslvm_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libvslvm_error_t **error );

#endif /* !defined( LIBVSLVM_HAVE_BFIO ) */

PyMethodDef pyvslvm_handle_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyvslvm_handle_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the handle to abort the current activity." },

	/* Functions to access the media data */

	{ "open",
	  (PyCFunction) pyvslvm_handle_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a handle using the descriptor file." },

	{ "open_file_object",
	  (PyCFunction) pyvslvm_handle_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a handle using a file-like object of the descriptor file." },

	{ "open_physical_volume_files",
	  (PyCFunction) pyvslvm_handle_open_physical_volume_files,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_physical_volume_files() -> None\n"
	  "\n"
	  "Opens the physical volume files." },

	{ "open_physical_volume_files_as_file_objects",
	  (PyCFunction) pyvslvm_handle_open_physical_volume_files_as_file_objects,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_physical_volume_files_as_file_objects(file_objects) -> None\n"
	  "\n"
	  "Opens physical volume files using a list of file-like objects." },

	{ "close",
	  (PyCFunction) pyvslvm_handle_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a handle." },

	/* Functions to access the volume group */

	{ "get_volume_group",
	  (PyCFunction) pyvslvm_handle_get_volume_group,
	  METH_NOARGS,
	  "get_volume_group() -> Object\n"
	  "\n"
	  "Retrieves the volume group." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvslvm_handle_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvslvm_handle_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm.handle",
	/* tp_basicsize */
	sizeof( pyvslvm_handle_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_handle_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyvslvm handle object (wraps libvslvm_handle_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyvslvm_handle_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvslvm_handle_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyvslvm_handle_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Initializes a handle object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_handle_init(
     pyvslvm_handle_t *pyvslvm_handle )
{
	static char *function    = "pyvslvm_handle_init";
	libcerror_error_t *error = NULL;

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	pyvslvm_handle->handle         = NULL;
	pyvslvm_handle->file_io_handle = NULL;
	pyvslvm_handle->file_io_pool   = NULL;

	if( libvslvm_handle_initialize(
	     &( pyvslvm_handle->handle ),
	     &error ) != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize handle.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a handle object
 */
void pyvslvm_handle_free(
      pyvslvm_handle_t *pyvslvm_handle )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_handle_free";
	int result                  = 0;

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid handle.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_handle );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( ( pyvslvm_handle->file_io_handle != NULL )
	 || ( pyvslvm_handle->file_io_pool != NULL ) )
	{
		if( pyvslvm_handle_close(
		     pyvslvm_handle,
		     NULL ) == NULL )
		{
			return;
		}
	}
	if( pyvslvm_handle->handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libvslvm_handle_free(
		          &( pyvslvm_handle->handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvslvm_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free handle.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_handle );
}

/* Signals the handle to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_handle_signal_abort(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvslvm_handle_signal_abort";
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvslvm handle.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_handle_signal_abort(
	          pyvslvm_handle->handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a handle
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_handle_open(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	static char *function        = "pyvslvm_handle_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	const char *filename_narrow  = NULL;
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

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

		result = libvslvm_handle_open_wide(
		          pyvslvm_handle->handle,
	                  filename_wide,
		          LIBVSLVM_OPEN_READ,
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

		result = libvslvm_handle_open(
		          pyvslvm_handle->handle,
	                  filename_narrow,
		          LIBVSLVM_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pyvslvm_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
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

		result = libvslvm_handle_open(
		          pyvslvm_handle->handle,
	                  filename_narrow,
		          LIBVSLVM_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvslvm_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a handle using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_handle_open_file_object(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	char *mode                  = NULL;
	static char *keyword_list[] = { "file_object", "mode", NULL };
	static char *function       = "pyvslvm_handle_open_file_object";
	int result                  = 0;

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "read" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing read attribute.",
		 function );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "seek" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing seek attribute.",
		 function );

		return( NULL );
	}
	if( pyvslvm_handle->file_io_handle != NULL )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid file - file IO handle already set.",
		 function );

		goto on_error;
	}
	if( pyvslvm_file_object_initialize(
	     &( pyvslvm_handle->file_io_handle ),
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

	result = libvslvm_handle_open_file_io_handle(
	          pyvslvm_handle->handle,
	          pyvslvm_handle->file_io_handle,
	          LIBVSLVM_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pyvslvm_handle->file_io_handle  != NULL )
	{
		libbfio_handle_free(
		 &( pyvslvm_handle->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Opens the physical volume files
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_handle_open_physical_volume_files(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments,
           PyObject *keywords )
{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wchar_t **filenames              = NULL;
	wchar_t *filename                = NULL;
	const char *errors               = NULL;
	char *narrow_string              = NULL;
	size_t narrow_string_size        = 0;
	int is_unicode_string            = 0;
#else
	char **filenames                 = NULL;
	char *filename                   = NULL;
#endif
	PyObject *filename_string_object = NULL;
	PyObject *sequence_object        = NULL;
	PyObject *string_object          = NULL;
	libcerror_error_t *error         = NULL;
	static char *keyword_list[]      = { "filenames", NULL };
	static char *function            = "pyvslvm_handle_open_physical_volume_files";
	Py_ssize_t sequence_size         = 0;
	size_t filename_length           = 0;
	int filename_index               = 0;
	int number_of_filenames          = 0;
	int result                       = 0;

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvslvm handle.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	      keywords,
	      "O",
	      keyword_list,
	      &sequence_object ) == 0 )
	{
		return( NULL );
	}
	if( PySequence_Check(
	     sequence_object ) == 0 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: argument: files must be a sequence object.",
		 function );

		return( NULL );
	}
	sequence_size = PySequence_Size(
	                 sequence_object );

	if( sequence_size > (Py_ssize_t) INT_MAX )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sequence size value exceeds maximum.",
		 function );

		goto on_error;
	}
	number_of_filenames = (int) sequence_size;

	if( ( number_of_filenames <= 0 )
	 || ( number_of_filenames > (int) UINT16_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid number of files.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	filenames = (wchar_t **) PyMem_Malloc(
	                          sizeof( wchar_t * ) * number_of_filenames );
#else
	filenames = (char **) PyMem_Malloc(
	                       sizeof( char * ) * number_of_filenames );
#endif
	if( filenames == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create filenames.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( memory_set(
	     filenames,
	     0,
	     sizeof( wchar_t * ) * number_of_filenames ) == NULL )
#else
	if( memory_set(
	     filenames,
	     0,
	     sizeof( char * ) * number_of_filenames ) == NULL )
#endif
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to clear filenames.",
		 function );

		PyMem_Free(
		 filenames );

		return( NULL );
	}
	for( filename_index = 0;
	     filename_index < number_of_filenames;
	     filename_index++ )
	{
		string_object = PySequence_GetItem(
		                 sequence_object,
		                 filename_index );

		PyErr_Clear();

		result = PyObject_IsInstance(
			  string_object,
			  (PyObject *) &PyUnicode_Type );

		if( result == -1 )
		{
			pyvslvm_error_fetch_and_raise(
			 PyExc_ValueError,
			 "%s: unable to determine if the sequence object: %d is of type unicode.",
			 function,
			 filename_index );

			goto on_error;
		}
		else if( result == 0 )
		{
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

				goto on_error;
			}
			else if( result == 0 )
			{
				PyErr_Format(
				 PyExc_TypeError,
				 "%s: unsupported string object type",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			else
			{
				is_unicode_string = 0;
			}
#endif
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		else
		{
			is_unicode_string = 1;
		}
#endif
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( is_unicode_string != 0 )
		{
			filename = (wchar_t *) PyUnicode_AsUnicode(
			                        string_object );
		}
		else
		{
#if PY_MAJOR_VERSION >= 3
			narrow_string = PyBytes_AsString(
			                 string_object );

			narrow_string_size = PyBytes_Size(
			                      string_object );
#else
			narrow_string = PyString_AsString(
			                 string_object );

			narrow_string_size = PyString_Size(
			                      string_object );
#endif
			filename_string_object = PyUnicode_Decode(
						  narrow_string,
						  narrow_string_size,
						  PyUnicode_GetDefaultEncoding(),
						  errors );

			if( filename_string_object == NULL )
			{
				PyErr_Format(
				 PyExc_IOError,
				 "%s: unable to convert filename: %d into Unicode.",
				 function,
				 filename_index );

				goto on_error;
			}
			filename = (wchar_t *) PyUnicode_AsUnicode(
			                        filename_string_object );
		}
		filename_length = wide_string_length(
		                   filename );
#else
		/* A Unicode string object can be converted into UFT-8 formatted narrow string
		 */
#if PY_MAJOR_VERSION >= 3
		filename = PyBytes_AsString(
		            string_object );
#else
		filename = PyString_AsString(
		            string_object );
#endif
		filename_length = narrow_string_length(
		                   filename );
#endif

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filenames[ filename_index ] = (wchar_t *) PyMem_Malloc(
		                                           sizeof( wchar_t ) * ( filename_length + 1 ) );
#else
		filenames[ filename_index ] = (char *) PyMem_Malloc(
		                                        sizeof( char ) * ( filename_length + 1 ) );
#endif
		if( filenames[ filename_index ] == NULL )
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to create filename: %d.",
			 function,
			 filename_index );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( wide_string_copy(
		     filenames[ filename_index ],
		     filename,
		     filename_length ) == NULL )
#else
		if( narrow_string_copy(
		     filenames[ filename_index ],
		     filename,
		     filename_length ) == NULL )
#endif
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to set filename: %d.",
			 function,
			 filename_index );

			goto on_error;
		}
		( filenames[ filename_index ] )[ filename_length ] = 0;

		if( filename_string_object != NULL )
		{
			Py_DecRef(
			 filename_string_object );

			filename_string_object = NULL;
		}
		/* The string object was reference by PySequence_GetItem
		 */
		Py_DecRef(
		 string_object );

		string_object = NULL;
	}
	Py_BEGIN_ALLOW_THREADS

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvslvm_handle_open_physical_volume_files_wide(
	          pyvslvm_handle->handle,
	          filenames,
	          number_of_filenames,
	          &error );
#else
	result = libvslvm_handle_open_physical_volume_files(
	          pyvslvm_handle->handle,
	          filenames,
	          number_of_filenames,
	          &error );
#endif
	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	for( filename_index = 0;
	     filename_index < number_of_filenames;
	     filename_index++ )
	{
		PyMem_Free(
		 filenames[ filename_index ] );
	}
	PyMem_Free(
	 filenames );

	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( filename_string_object != NULL )
	{
		Py_DecRef(
		 filename_string_object );
	}
	if( string_object != NULL )
	{
		Py_DecRef(
		 string_object );
	}
	if( filenames != NULL )
	{
		for( ; filename_index > 0; filename_index-- )
		{
			PyMem_Free(
			 filenames[ filename_index - 1 ] );
		}
		PyMem_Free(
		 filenames );
	}
	return( NULL );
}

/* Opens physical volume files using a list of file-like objects
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_handle_open_physical_volume_files_as_file_objects(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_objects      = NULL;
	libcerror_error_t *error    = NULL;
	static char *keyword_list[] = { "file_object", NULL };
	static char *function       = "pyvslvm_handle_open_physical_volume_files_as_file_objects";
	int result                  = 0;

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O",
	     keyword_list,
	     &file_objects ) == 0 )
	{
		return( NULL );
	}
	if( pyvslvm_file_objects_pool_initialize(
	     &( pyvslvm_handle->file_io_pool ),
	     file_objects,
	     LIBBFIO_OPEN_READ,
	     &error ) != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO pool.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_handle_open_physical_volume_files_file_io_pool(
	          pyvslvm_handle->handle,
	          pyvslvm_handle->file_io_pool,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open physical volume files.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pyvslvm_handle->file_io_pool != NULL )
	{
		libbfio_pool_free(
		 &( pyvslvm_handle->file_io_pool ),
		 NULL );
	}
	return( NULL );
}

/* Closes a handle
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_handle_close(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvslvm_handle_close";
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvslvm handle.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_handle_close(
	          pyvslvm_handle->handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close handle.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pyvslvm_handle->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pyvslvm_handle->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvslvm_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	if( pyvslvm_handle->file_io_pool != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_pool_free(
		          &( pyvslvm_handle->file_io_pool ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvslvm_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO pool.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the volume group
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_handle_get_volume_group(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	PyObject *volume_group_object         = NULL;
	static char *function                 = "pyvslvm_handle_get_volume_group";
	int result                            = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_handle == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid handle.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_handle_get_volume_group(
	          pyvslvm_handle->handle,
	          &volume_group,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve volume group.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	volume_group_object = pyvslvm_volume_group_new(
	                       volume_group,
	                       pyvslvm_handle );

	if( volume_group_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create volume group object.",
		 function );

		goto on_error;
	}
	return( volume_group_object );

on_error:
	if( volume_group != NULL )
	{
		libvslvm_volume_group_free(
		 &volume_group,
		 NULL );
	}
	return( NULL );
}

