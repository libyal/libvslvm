/*
 * Python object wrapper of libvslvm_volume_group_t
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
#include <types.h>

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pyvslvm_error.h"
#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_logical_volume.h"
#include "pyvslvm_logical_volumes.h"
#include "pyvslvm_physical_volume.h"
#include "pyvslvm_physical_volumes.h"
#include "pyvslvm_python.h"
#include "pyvslvm_unused.h"
#include "pyvslvm_volume_group.h"

PyMethodDef pyvslvm_volume_group_object_methods[] = {

	/* Functions to access the volume group values */

	{ "get_name",
	  (PyCFunction) pyvslvm_volume_group_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name." },

	{ "get_identifier",
	  (PyCFunction) pyvslvm_volume_group_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the identifier." },

	/* Functions to access the physical volumes */

	{ "get_number_of_physical_volumes",
	  (PyCFunction) pyvslvm_volume_group_get_number_of_physical_volumes,
	  METH_NOARGS,
	  "get_number_of_physical_volumes() -> Integer\n"
	  "\n"
	  "Retrieves the number of physical volumes." },

	{ "get_physical_volume",
	  (PyCFunction) pyvslvm_volume_group_get_physical_volume,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_physical_volume(volume_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific physical volume." },

	{ "get_physical_volumes",
	  (PyCFunction) pyvslvm_volume_group_get_physical_volumes,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_physical_volumes() -> Object\n"
	  "\n"
	  "Retrieves a sequence object of the physical volumes." },

	/* Functions to access the logical volumes */

	{ "get_number_of_logical_volumes",
	  (PyCFunction) pyvslvm_volume_group_get_number_of_logical_volumes,
	  METH_NOARGS,
	  "get_number_of_logical_volumes() -> Integer\n"
	  "\n"
	  "Retrieves the number of logical volumes." },

	{ "get_logical_volume",
	  (PyCFunction) pyvslvm_volume_group_get_logical_volume,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_logical_volume(volume_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific logical volume." },

	{ "get_logical_volumes",
	  (PyCFunction) pyvslvm_volume_group_get_logical_volumes,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_logical_volumes() -> Object\n"
	  "\n"
	  "Retrieves a sequence object of the logical volumes." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvslvm_volume_group_object_get_set_definitions[] = {

	{ "name",
	  (getter) pyvslvm_volume_group_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	{ "identifier",
	  (getter) pyvslvm_volume_group_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "number_of_physical_volumes",
	  (getter) pyvslvm_volume_group_get_number_of_physical_volumes,
	  (setter) 0,
	  "The number of physical volumes.",
	  NULL },

	{ "physical_volumes",
	  (getter) pyvslvm_volume_group_get_physical_volumes,
	  (setter) 0,
	  "The physical volumes.",
	  NULL },

	{ "number_of_logical_volumes",
	  (getter) pyvslvm_volume_group_get_number_of_logical_volumes,
	  (setter) 0,
	  "The number of logical volumes.",
	  NULL },

	{ "logical_volumes",
	  (getter) pyvslvm_volume_group_get_logical_volumes,
	  (setter) 0,
	  "The logical volumes.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvslvm_volume_group_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm.volume_group",
	/* tp_basicsize */
	sizeof( pyvslvm_volume_group_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_volume_group_free,
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
	"pyvslvm volume group object (wraps libvslvm_volume_group_t)",
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
	pyvslvm_volume_group_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvslvm_volume_group_object_get_set_definitions,
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
	(initproc) pyvslvm_volume_group_init,
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

/* Creates a new pyvslvm volume group object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_new(
           libvslvm_volume_group_t *volume_group,
           pyvslvm_handle_t *handle_object )
{
	static char *function                        = "pyvslvm_volume_group_new";
	pyvslvm_volume_group_t *pyvslvm_volume_group = NULL;

	pyvslvm_volume_group = PyObject_New(
	                        struct pyvslvm_volume_group,
	                        &pyvslvm_volume_group_type_object );

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volume group.",
		 function );

		goto on_error;
	}
	if( pyvslvm_volume_group_init(
	     pyvslvm_volume_group ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volume group.",
		 function );

		goto on_error;
	}
	pyvslvm_volume_group->volume_group  = volume_group;
	pyvslvm_volume_group->handle_object = handle_object;

	Py_IncRef(
	 (PyObject *) pyvslvm_volume_group->handle_object );

	return( (PyObject *) pyvslvm_volume_group );

on_error:
	if( pyvslvm_volume_group != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_volume_group );
	}
	return( NULL );
}

/* Initializes a volume group object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_volume_group_init(
     pyvslvm_volume_group_t *pyvslvm_volume_group )
{
	static char *function = "pyvslvm_volume_group_init";

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	/* Make sure libvslvm volume group is set to NULL
	 */
	pyvslvm_volume_group->volume_group = NULL;

	return( 0 );
}

/* Frees a volume group object
 */
void pyvslvm_volume_group_free(
      pyvslvm_volume_group_t *pyvslvm_volume_group )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_volume_group_free";
	int result                  = 0;

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return;
	}
	if( pyvslvm_volume_group->volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group - missing libvslvm volume group.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_volume_group );

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
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_free(
	          &( pyvslvm_volume_group->volume_group ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free volume group.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyvslvm_volume_group->handle_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_volume_group->handle_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_volume_group );
}

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_name(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	char *name               = NULL;
	const char *errors       = NULL;
	static char *function    = "pyvslvm_volume_group_get_name";
	size_t name_size         = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_get_name_size(
	          pyvslvm_volume_group->volume_group,
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

	result = libvslvm_volume_group_get_name(
		  pyvslvm_volume_group->volume_group,
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
PyObject *pyvslvm_volume_group_get_identifier(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	char *identifier         = NULL;
	const char *errors       = NULL;
	static char *function    = "pyvslvm_volume_group_get_identifier";
	size_t identifier_size   = 0;
	int result               = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_get_identifier_size(
	          pyvslvm_volume_group->volume_group,
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

	result = libvslvm_volume_group_get_identifier(
		  pyvslvm_volume_group->volume_group,
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

/* Retrieves the number of physical volumes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_number_of_physical_volumes(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error       = NULL;
	PyObject *integer_object       = NULL;
	static char *function          = "pyvslvm_volume_group_get_number_of_physical_volumes";
	int number_of_physical_volumes = 0;
	int result                     = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_get_number_of_physical_volumes(
	          pyvslvm_volume_group->volume_group,
	          &number_of_physical_volumes,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of physical volumes.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_physical_volumes );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_physical_volumes );
#endif
	return( integer_object );
}

/* Retrieves a specific physical volume by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_physical_volume_by_index(
           PyObject *pyvslvm_volume_group,
           int volume_index )
{
	libcerror_error_t *error                    = NULL;
	libvslvm_physical_volume_t *physical_volume = NULL;
	PyObject *physical_volume_object            = NULL;
	static char *function                       = "pyvslvm_volume_group_get_physical_volume_by_index";
	int result                                  = 0;

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_get_physical_volume(
	          ( (pyvslvm_volume_group_t *) pyvslvm_volume_group )->volume_group,
	          volume_index,
	          &physical_volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve physical volume: %d.",
		 function,
		 volume_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	physical_volume_object = pyvslvm_physical_volume_new(
	                          physical_volume,
	                          (pyvslvm_volume_group_t *) pyvslvm_volume_group );

	if( physical_volume_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create physical volume object.",
		 function );

		goto on_error;
	}
	return( physical_volume_object );

on_error:
	if( physical_volume != NULL )
	{
		libvslvm_physical_volume_free(
		 &physical_volume,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific physical volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_physical_volume(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *physical_volume_object = NULL;
	static char *keyword_list[]      = { "volume_index", NULL };
	int volume_index                 = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &volume_index ) == 0 )
	{
		return( NULL );
	}
	physical_volume_object = pyvslvm_volume_group_get_physical_volume_by_index(
	                          (PyObject *) pyvslvm_volume_group,
	                          volume_index );

	return( physical_volume_object );
}

/* Retrieves a physical volumes sequence and iterator object for the physical volumes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_physical_volumes(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error          = NULL;
	PyObject *physical_volumes_object = NULL;
	static char *function             = "pyvslvm_volume_group_get_physical_volumes";
	int number_of_physical_volumes    = 0;
	int result                        = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_get_number_of_physical_volumes(
	          pyvslvm_volume_group->volume_group,
	          &number_of_physical_volumes,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of physical volumes.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	physical_volumes_object = pyvslvm_physical_volumes_new(
	                           (PyObject *) pyvslvm_volume_group,
	                           &pyvslvm_volume_group_get_physical_volume_by_index,
	                           number_of_physical_volumes );

	if( physical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create physical volumes object.",
		 function );

		return( NULL );
	}
	return( physical_volumes_object );
}

/* Retrieves the number of logical volumes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_number_of_logical_volumes(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error      = NULL;
	PyObject *integer_object      = NULL;
	static char *function         = "pyvslvm_volume_group_get_number_of_logical_volumes";
	int number_of_logical_volumes = 0;
	int result                    = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_get_number_of_logical_volumes(
	          pyvslvm_volume_group->volume_group,
	          &number_of_logical_volumes,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of logical volumes.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_logical_volumes );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_logical_volumes );
#endif
	return( integer_object );
}

/* Retrieves a specific logical volume by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_logical_volume_by_index(
           PyObject *pyvslvm_volume_group,
           int volume_index )
{
	libcerror_error_t *error                  = NULL;
	libvslvm_logical_volume_t *logical_volume = NULL;
	PyObject *logical_volume_object           = NULL;
	static char *function                     = "pyvslvm_volume_group_get_logical_volume_by_index";
	int result                                = 0;

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_get_logical_volume(
	          ( (pyvslvm_volume_group_t *) pyvslvm_volume_group )->volume_group,
	          volume_index,
	          &logical_volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve logical volume: %d.",
		 function,
		 volume_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	logical_volume_object = pyvslvm_logical_volume_new(
	                         logical_volume,
	                         (pyvslvm_volume_group_t *) pyvslvm_volume_group );

	if( logical_volume_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create logical volume object.",
		 function );

		goto on_error;
	}
	return( logical_volume_object );

on_error:
	if( logical_volume != NULL )
	{
		libvslvm_logical_volume_free(
		 &logical_volume,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific logical volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_logical_volume(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *logical_volume_object = NULL;
	static char *keyword_list[]     = { "volume_index", NULL };
	int volume_index                = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &volume_index ) == 0 )
	{
		return( NULL );
	}
	logical_volume_object = pyvslvm_volume_group_get_logical_volume_by_index(
	                         (PyObject *) pyvslvm_volume_group,
	                         volume_index );

	return( logical_volume_object );
}

/* Retrieves a logical volumes sequence and iterator object for the logical volumes
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_volume_group_get_logical_volumes(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments PYVSLVM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error         = NULL;
	PyObject *logical_volumes_object = NULL;
	static char *function            = "pyvslvm_volume_group_get_logical_volumes";
	int number_of_logical_volumes    = 0;
	int result                       = 0;

	PYVSLVM_UNREFERENCED_PARAMETER( arguments )

	if( pyvslvm_volume_group == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume group.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvslvm_volume_group_get_number_of_logical_volumes(
	          pyvslvm_volume_group->volume_group,
	          &number_of_logical_volumes,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of logical volumes.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	logical_volumes_object = pyvslvm_logical_volumes_new(
	                          (PyObject *) pyvslvm_volume_group,
	                          &pyvslvm_volume_group_get_logical_volume_by_index,
	                          number_of_logical_volumes );

	if( logical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create logical volumes object.",
		 function );

		return( NULL );
	}
	return( logical_volumes_object );
}

