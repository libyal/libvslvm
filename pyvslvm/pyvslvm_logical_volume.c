/*
 * Python object wrapper of libvslvm_logical_volume_t
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvslvm_error.h"
#include "pyvslvm_integer.h"
#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_logical_volume.h"
#include "pyvslvm_python.h"
#include "pyvslvm_segment.h"
#include "pyvslvm_segments.h"
#include "pyvslvm_unused.h"
#include "pyvslvm_volume_group.h"

PyMethodDef pyvslvm_logical_volume_object_methods[] = {

	/* Functions to access the logical volume data */

	{ "read_buffer",
	  (PyCFunction) pyvslvm_logical_volume_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer(size) -> String\n"
	  "\n"
	  "Reads a buffer of data." },

	{ "read_buffer_at_offset",
	  (PyCFunction) pyvslvm_logical_volume_read_buffer_at_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer_at_offset(size, offset) -> String\n"
	  "\n"
	  "Reads a buffer of data at a specific offset." },

	{ "seek_offset",
	  (PyCFunction) pyvslvm_logical_volume_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek_offset(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the data." },

	{ "get_offset",
	  (PyCFunction) pyvslvm_logical_volume_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Integer\n"
	  "\n"
	  "Retrieves the current offset within the data." },

	/* Some Pythonesque aliases */

	{ "read",
	  (PyCFunction) pyvslvm_logical_volume_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read(size) -> String\n"
	  "\n"
	  "Reads a buffer of data." },

	{ "seek",
	  (PyCFunction) pyvslvm_logical_volume_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the data." },

	{ "tell",
	  (PyCFunction) pyvslvm_logical_volume_get_offset,
	  METH_NOARGS,
	  "tell() -> Integer\n"
	  "\n"
	  "Retrieves the current offset within the data." },

	/* Functions to access the logical volume values */

	{ "get_size",
	  (PyCFunction) pyvslvm_logical_volume_get_size,
	  METH_NOARGS,
	  "get_size() -> Integer\n"
	  "\n"
	  "Retrieves the size of the volume." },

	{ "get_name",
	  (PyCFunction) pyvslvm_logical_volume_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name." },

	{ "get_identifier",
	  (PyCFunction) pyvslvm_logical_volume_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the identifier." },

	/* Functions to access the segments */

	{ "get_number_of_segments",
	  (PyCFunction) pyvslvm_logical_volume_get_number_of_segments,
	  METH_NOARGS,
	  "get_number_of_segments() -> Integer\n"
	  "\n"
	  "Retrieves the number of segments." },

	{ "get_segment",
	  (PyCFunction) pyvslvm_logical_volume_get_segment,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_segment(segment_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific segment." },

	{ "get_segments",
	  (PyCFunction) pyvslvm_logical_volume_get_segments,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_segments() -> Object\n"
	  "\n"
	  "Retrieves a sequence object of the segments." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvslvm_logical_volume_object_get_set_definitions[] = {

	{ "size",
	  (getter) pyvslvm_logical_volume_get_size,
	  (setter) 0,
	  "The volume size.",
	  NULL },

	{ "name",
	  (getter) pyvslvm_logical_volume_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	{ "identifier",
	  (getter) pyvslvm_logical_volume_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "number_of_segments",
	  (getter) pyvslvm_logical_volume_get_number_of_segments,
	  (setter) 0,
	  "The number of segments.",
	  NULL },

	{ "segments",
	  (getter) pyvslvm_logical_volume_get_segments,
	  (setter) 0,
	  "The segments.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvslvm_logical_volume_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm.logical_volume",
	/* tp_basicsize */
	sizeof( pyvslvm_logical_volume_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_logical_volume_free,
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
	"pyvslvm logical volume object (wraps libvslvm_logical_volume_t)",
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
	pyvslvm_logical_volume_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvslvm_logical_volume_object_get_set_definitions,
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
	(initproc) pyvslvm_logical_volume_init,
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

/* Creates a new logical volume object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_new(
           libvslvm_logical_volume_t *logical_volume,
           pyvslvm_volume_group_t *volume_group_object )
{
	pyvslvm_logical_volume_t *pyvslvm_logical_volume = NULL;
	static char *function                            = "pyvslvm_logical_volume_new";

	if( logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( NULL );
	}
	pyvslvm_logical_volume = PyObject_New(
	                          struct pyvslvm_logical_volume,
	                          &pyvslvm_logical_volume_type_object );

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize logical volume.",
		 function );

		goto on_error;
	}
	if( pyvslvm_logical_volume_init(
	     pyvslvm_logical_volume ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize logical volume.",
		 function );

		goto on_error;
	}
	pyvslvm_logical_volume->logical_volume      = logical_volume;
	pyvslvm_logical_volume->volume_group_object = volume_group_object;

	Py_IncRef(
	 (PyObject *) pyvslvm_logical_volume->volume_group_object );

	return( (PyObject *) pyvslvm_logical_volume );

on_error:
	if( pyvslvm_logical_volume != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_logical_volume );
	}
	return( NULL );
}

/* Initializes a logical volume object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_logical_volume_init(
     pyvslvm_logical_volume_t *pyvslvm_logical_volume )
{
	static char *function = "pyvslvm_logical_volume_init";

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( -1 );
	}
	/* Make sure libvslvm logical volume is set to NULL
	 */
	pyvslvm_logical_volume->logical_volume = NULL;

	return( 0 );
}

/* Frees a logical volume object
 */
void pyvslvm_logical_volume_free(
      pyvslvm_logical_volume_t *pyvslvm_logical_volume )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_logical_volume_free";

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return;
	}
	if( pyvslvm_logical_volume->logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume - missing libvslvm logical volume.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_logical_volume );

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
	if( libvslvm_logical_volume_free(
	     &( pyvslvm_logical_volume->logical_volume ),
	     &error ) != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libvslvm logical volume.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyvslvm_logical_volume->volume_group_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_logical_volume->volume_group_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_logical_volume );
}

/* Reads data at the current offset into a buffer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_read_buffer(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	PyObject *string_object     = NULL;
	static char *function       = "pyvslvm_logical_volume_read_buffer";
	static char *keyword_list[] = { "size", NULL };
	char *buffer                = NULL;
	ssize_t read_count          = 0;
	int read_size               = -1;

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvslvm logical volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|i",
	     keyword_list,
	     &read_size ) == 0 )
	{
		return( NULL );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
	if( read_size > INT_MAX )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libvslvm_logical_volume_read_buffer(
	              pyvslvm_logical_volume->logical_volume,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count <= -1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Reads data at a specific offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_read_buffer_at_offset(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	PyObject *string_object     = NULL;
	static char *function       = "pyvslvm_logical_volume_read_buffer_at_offset";
	static char *keyword_list[] = { "size", "offset", NULL };
	char *buffer                = NULL;
	off64_t read_offset         = 0;
	ssize_t read_count          = 0;
	int read_size               = 0;

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvslvm logical volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i|L",
	     keyword_list,
	     &read_size,
	     &read_offset ) == 0 )
	{
		return( NULL );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
	if( read_size > INT_MAX )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
	if( read_offset < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read offset value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libvslvm_logical_volume_read_buffer_at_offset(
	              pyvslvm_logical_volume->logical_volume,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              (off64_t) read_offset,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count <= -1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Seeks a certain offset in the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_seek_offset(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvslvm_logical_volume_seek_offset";
	static char *keyword_list[] = { "offset", "whence", NULL };
	off64_t offset              = 0;
	int whence                  = 0;

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyvslvm logical volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "L|i",
	     keyword_list,
	     &offset,
	     &whence ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	offset = libvslvm_logical_volume_seek_offset(
	          pyvslvm_logical_volume->logical_volume,
	          offset,
	          whence,
	          &error );

	Py_END_ALLOW_THREADS

 	if( offset == -1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to seek offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the current offset in the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_get_offset(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvslvm_logical_volume_get_offset";
	off64_t current_offset   = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_offset(
	          pyvslvm_logical_volume->logical_volume,
	          &current_offset,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvslvm_integer_signed_new_from_64bit(
	                  (int64_t) current_offset );

	return( integer_object );
}

/* Retrieves the size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_get_size(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvslvm_logical_volume_get_size";
	size64_t size            = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_size(
	          pyvslvm_logical_volume->logical_volume,
	          &size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvslvm_integer_unsigned_new_from_64bit(
	                  (uint64_t) size );

	return( integer_object );
}

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_get_name(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	char *name               = NULL;
	const char *errors       = NULL;
	static char *function    = "pyvslvm_logical_volume_get_name";
	size_t name_size         = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_name_size(
	          pyvslvm_logical_volume->logical_volume,
	          &name_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve name size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( name_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	name = (char *) PyMem_Malloc(
	                 sizeof( char ) * name_size );

	if( name == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create name.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_name(
		  pyvslvm_logical_volume->logical_volume,
		  name,
		  name_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve name.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 name,
			 (Py_ssize_t) name_size - 1,
			 errors );

	PyMem_Free(
	 name );

	return( string_object );

on_error:
	if( name != NULL )
	{
		PyMem_Free(
		 name );
	}
	return( NULL );
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_get_identifier(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	char *identifier         = NULL;
	const char *errors       = NULL;
	static char *function    = "pyvslvm_logical_volume_get_identifier";
	size_t identifier_size   = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_identifier_size(
	          pyvslvm_logical_volume->logical_volume,
	          &identifier_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve identifier size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( identifier_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	identifier = (char *) PyMem_Malloc(
	                       sizeof( char ) * identifier_size );

	if( identifier == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create identifier.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_identifier(
		  pyvslvm_logical_volume->logical_volume,
		  identifier,
		  identifier_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve identifier.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 identifier,
			 (Py_ssize_t) identifier_size - 1,
			 errors );

	PyMem_Free(
	 identifier );

	return( string_object );

on_error:
	if( identifier != NULL )
	{
		PyMem_Free(
		 identifier );
	}
	return( NULL );
}

/* Retrieves the number of segments
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_get_number_of_segments(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvslvm_logical_volume_get_number_of_segments";
	int number_of_segments   = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_number_of_segments(
	          pyvslvm_logical_volume->logical_volume,
	          &number_of_segments,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of segments.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_segments );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_segments );
#endif
	return( integer_object );
}

/* Retrieves a specific segment by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_get_segment_by_index(
           PyObject *pyvslvm_logical_volume,
           int segment_index )
{
	libcerror_error_t *error    = NULL;
	libvslvm_segment_t *segment = NULL;
	PyObject *segment_object    = NULL;
	static char *function       = "pyvslvm_logical_volume_get_segment_by_index";
	int result                  = 0;

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_segment(
	          ( (pyvslvm_logical_volume_t *) pyvslvm_logical_volume )->logical_volume,
	          segment_index,
	          &segment,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve segment: %d.",
		 function,
		 segment_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	segment_object = pyvslvm_segment_new(
	                  segment,
	                  (pyvslvm_logical_volume_t *) pyvslvm_logical_volume );

	if( segment_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create segment object.",
		 function );

		goto on_error;
	}
	return( segment_object );

on_error:
	if( segment != NULL )
	{
		libvslvm_segment_free(
		 &segment,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific segment
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_get_segment(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *segment_object    = NULL;
	static char *keyword_list[] = { "segment_index", NULL };
	int segment_index           = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &segment_index ) == 0 )
	{
		return( NULL );
	}
	segment_object = pyvslvm_logical_volume_get_segment_by_index(
	                  (PyObject *) pyvslvm_logical_volume,
	                  segment_index );

	return( segment_object );
}

/* Retrieves a segments sequence and iterator object for the segments
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volume_get_segments(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error  = NULL;
	PyObject *segments_object = NULL;
	static char *function     = "pyvslvm_logical_volume_get_segments";
	int number_of_segments    = 0;
	int result                = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_logical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid logical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_logical_volume_get_number_of_segments(
	          pyvslvm_logical_volume->logical_volume,
	          &number_of_segments,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of segments.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	segments_object = pyvslvm_segments_new(
	                   (PyObject *) pyvslvm_logical_volume,
	                   &pyvslvm_logical_volume_get_segment_by_index,
	                   number_of_segments );

	if( segments_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create segments object.",
		 function );

		return( NULL );
	}
	return( segments_object );
}

