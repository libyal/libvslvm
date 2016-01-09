/*
 * Python object definition of the libvslvm volume group
 *
 * Copyright (C) 2014-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pyvslvm_error.h"
#include "pyvslvm_libcerror.h"
#include "pyvslvm_libcstring.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_logical_volume.h"
#include "pyvslvm_logical_volumes.h"
#include "pyvslvm_python.h"
#include "pyvslvm_unused.h"
#include "pyvslvm_volume_group.h"

PyMethodDef pyvslvm_volume_group_object_methods[] = {

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

/* Intializes a volume group object
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
           pyvslvm_volume_group_t *pyvslvm_volume_group,
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
	          pyvslvm_volume_group->volume_group,
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
	                         pyvslvm_volume_group );

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
	                         pyvslvm_volume_group,
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
	                          pyvslvm_volume_group,
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

