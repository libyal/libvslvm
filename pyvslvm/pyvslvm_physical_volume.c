/*
 * Python object wrapper of libvslvm_physical_volume_t
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
#include "pyvslvm_physical_volume.h"
#include "pyvslvm_python.h"
#include "pyvslvm_unused.h"
#include "pyvslvm_volume_group.h"

PyMethodDef pyvslvm_physical_volume_object_methods[] = {

	/* Functions to access the physical volume values */

	{ "get_name",
	  (PyCFunction) pyvslvm_physical_volume_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name." },

	{ "get_identifier",
	  (PyCFunction) pyvslvm_physical_volume_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the identifier." },

	{ "get_device_path",
	  (PyCFunction) pyvslvm_physical_volume_get_device_path,
	  METH_NOARGS,
	  "get_device_path() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the device path." },

	{ "get_size",
	  (PyCFunction) pyvslvm_physical_volume_get_size,
	  METH_NOARGS,
	  "get_size() -> Integer\n"
	  "\n"
	  "Retrieves the size of the volume." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvslvm_physical_volume_object_get_set_definitions[] = {

	{ "name",
	  (getter) pyvslvm_physical_volume_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	{ "identifier",
	  (getter) pyvslvm_physical_volume_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "device_path",
	  (getter) pyvslvm_physical_volume_get_device_path,
	  (setter) 0,
	  "The device path.",
	  NULL },

	{ "size",
	  (getter) pyvslvm_physical_volume_get_size,
	  (setter) 0,
	  "The volume size.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvslvm_physical_volume_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm.physical_volume",
	/* tp_basicsize */
	sizeof( pyvslvm_physical_volume_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_physical_volume_free,
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
	"pyvslvm physical volume object (wraps libvslvm_physical_volume_t)",
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
	pyvslvm_physical_volume_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvslvm_physical_volume_object_get_set_definitions,
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
	(initproc) pyvslvm_physical_volume_init,
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

/* Creates a new physical volume object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_physical_volume_new(
           libvslvm_physical_volume_t *physical_volume,
           pyvslvm_volume_group_t *volume_group_object )
{
	pyvslvm_physical_volume_t *pyvslvm_physical_volume = NULL;
	static char *function                              = "pyvslvm_physical_volume_new";

	if( physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid physical volume.",
		 function );

		return( NULL );
	}
	pyvslvm_physical_volume = PyObject_New(
	                           struct pyvslvm_physical_volume,
	                           &pyvslvm_physical_volume_type_object );

	if( pyvslvm_physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize physical volume.",
		 function );

		goto on_error;
	}
	if( pyvslvm_physical_volume_init(
	     pyvslvm_physical_volume ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize physical volume.",
		 function );

		goto on_error;
	}
	pyvslvm_physical_volume->physical_volume     = physical_volume;
	pyvslvm_physical_volume->volume_group_object = volume_group_object;

	Py_IncRef(
	 (PyObject *) pyvslvm_physical_volume->volume_group_object );

	return( (PyObject *) pyvslvm_physical_volume );

on_error:
	if( pyvslvm_physical_volume != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_physical_volume );
	}
	return( NULL );
}

/* Initializes a physical volume object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_physical_volume_init(
     pyvslvm_physical_volume_t *pyvslvm_physical_volume )
{
	static char *function = "pyvslvm_physical_volume_init";

	if( pyvslvm_physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	/* Make sure libvslvm physical volume is set to NULL
	 */
	pyvslvm_physical_volume->physical_volume = NULL;

	return( 0 );
}

/* Frees a physical volume object
 */
void pyvslvm_physical_volume_free(
      pyvslvm_physical_volume_t *pyvslvm_physical_volume )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_physical_volume_free";

	if( pyvslvm_physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid physical volume.",
		 function );

		return;
	}
	if( pyvslvm_physical_volume->physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid physical volume - missing libvslvm physical volume.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_physical_volume );

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
	if( libvslvm_physical_volume_free(
	     &( pyvslvm_physical_volume->physical_volume ),
	     &error ) != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libvslvm physical volume.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyvslvm_physical_volume->volume_group_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_physical_volume->volume_group_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_physical_volume );
}

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_physical_volume_get_name(
           pyvslvm_physical_volume_t *pyvslvm_physical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	char *name               = NULL;
	const char *errors       = NULL;
	static char *function    = "pyvslvm_physical_volume_get_name";
	size_t name_size         = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid physical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_physical_volume_get_name_size(
	          pyvslvm_physical_volume->physical_volume,
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

	result = libvslvm_physical_volume_get_name(
		  pyvslvm_physical_volume->physical_volume,
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
PyObject *pyvslvm_physical_volume_get_identifier(
           pyvslvm_physical_volume_t *pyvslvm_physical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	char *identifier         = NULL;
	const char *errors       = NULL;
	static char *function    = "pyvslvm_physical_volume_get_identifier";
	size_t identifier_size   = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid physical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_physical_volume_get_identifier_size(
	          pyvslvm_physical_volume->physical_volume,
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

	result = libvslvm_physical_volume_get_identifier(
		  pyvslvm_physical_volume->physical_volume,
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

/* Retrieves the device path
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_physical_volume_get_device_path(
           pyvslvm_physical_volume_t *pyvslvm_physical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	char *device_path        = NULL;
	const char *errors       = NULL;
	static char *function    = "pyvslvm_physical_volume_get_device_path";
	size_t device_path_size  = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid physical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_physical_volume_get_device_path_size(
	          pyvslvm_physical_volume->physical_volume,
	          &device_path_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve device path size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( device_path_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	device_path = (char *) PyMem_Malloc(
	                        sizeof( char ) * device_path_size );

	if( device_path == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create device path.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_physical_volume_get_device_path(
		  pyvslvm_physical_volume->physical_volume,
		  device_path,
		  device_path_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve device path.",
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
			 device_path,
			 (Py_ssize_t) device_path_size - 1,
			 errors );

	PyMem_Free(
	 device_path );

	return( string_object );

on_error:
	if( device_path != NULL )
	{
		PyMem_Free(
		 device_path );
	}
	return( NULL );
}

/* Retrieves the size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_physical_volume_get_size(
           pyvslvm_physical_volume_t *pyvslvm_physical_volume,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyvslvm_physical_volume_get_size";
	size64_t size            = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_physical_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid physical volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_physical_volume_get_size(
	          pyvslvm_physical_volume->physical_volume,
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

