/*
 * Python object definition of the sequence and iterator object of logical volumes
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_logical_volume.h"
#include "pyvslvm_logical_volumes.h"
#include "pyvslvm_python.h"

PySequenceMethods pyvslvm_logical_volumes_sequence_methods = {
	/* sq_length */
	(lenfunc) pyvslvm_logical_volumes_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyvslvm_logical_volumes_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pyvslvm_logical_volumes_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm._logical_volumes",
	/* tp_basicsize */
	sizeof( pyvslvm_logical_volumes_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_logical_volumes_free,
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
	&pyvslvm_logical_volumes_sequence_methods,
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
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"pyvslvm internal sequence and iterator object of logical volumes",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyvslvm_logical_volumes_iter,
	/* tp_iternext */
	(iternextfunc) pyvslvm_logical_volumes_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
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
	(initproc) pyvslvm_logical_volumes_init,
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

/* Creates a new logical volumes object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_logical_volumes_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items )
{
	pyvslvm_logical_volumes_t *logical_volumes_object = NULL;
	static char *function                             = "pyvslvm_logical_volumes_new";

	if( parent_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid parent object.",
		 function );

		return( NULL );
	}
	if( get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get item by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the logical volumes values are initialized
	 */
	logical_volumes_object = PyObject_New(
	                          struct pyvslvm_logical_volumes,
	                          &pyvslvm_logical_volumes_type_object );

	if( logical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create logical volumes object.",
		 function );

		goto on_error;
	}
	if( pyvslvm_logical_volumes_init(
	     logical_volumes_object ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize logical volumes object.",
		 function );

		goto on_error;
	}
	logical_volumes_object->parent_object     = parent_object;
	logical_volumes_object->get_item_by_index = get_item_by_index;
	logical_volumes_object->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) logical_volumes_object->parent_object );

	return( (PyObject *) logical_volumes_object );

on_error:
	if( logical_volumes_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) logical_volumes_object );
	}
	return( NULL );
}

/* Intializes a logical volumes object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_logical_volumes_init(
     pyvslvm_logical_volumes_t *logical_volumes_object )
{
	static char *function = "pyvslvm_logical_volumes_init";

	if( logical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object.",
		 function );

		return( -1 );
	}
	/* Make sure the logical volumes values are initialized
	 */
	logical_volumes_object->parent_object     = NULL;
	logical_volumes_object->get_item_by_index = NULL;
	logical_volumes_object->current_index     = 0;
	logical_volumes_object->number_of_items   = 0;

	return( 0 );
}

/* Frees a logical volumes object
 */
void pyvslvm_logical_volumes_free(
      pyvslvm_logical_volumes_t *logical_volumes_object )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_logical_volumes_free";

	if( logical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           logical_volumes_object );

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
	if( logical_volumes_object->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) logical_volumes_object->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) logical_volumes_object );
}

/* The logical volumes len() function
 */
Py_ssize_t pyvslvm_logical_volumes_len(
            pyvslvm_logical_volumes_t *logical_volumes_object )
{
	static char *function = "pyvslvm_logical_volumes_len";

	if( logical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) logical_volumes_object->number_of_items );
}

/* The logical volumes getitem() function
 */
PyObject *pyvslvm_logical_volumes_getitem(
           pyvslvm_logical_volumes_t *logical_volumes_object,
           Py_ssize_t item_index )
{
	PyObject *logical_volume_object = NULL;
	static char *function           = "pyvslvm_logical_volumes_getitem";

	if( logical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object.",
		 function );

		return( NULL );
	}
	if( logical_volumes_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( logical_volumes_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) logical_volumes_object->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	logical_volume_object = logical_volumes_object->get_item_by_index(
	                         logical_volumes_object->parent_object,
	                         (int) item_index );

	return( logical_volume_object );
}

/* The logical volumes iter() function
 */
PyObject *pyvslvm_logical_volumes_iter(
           pyvslvm_logical_volumes_t *logical_volumes_object )
{
	static char *function = "pyvslvm_logical_volumes_iter";

	if( logical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) logical_volumes_object );

	return( (PyObject *) logical_volumes_object );
}

/* The logical volumes iternext() function
 */
PyObject *pyvslvm_logical_volumes_iternext(
           pyvslvm_logical_volumes_t *logical_volumes_object )
{
	PyObject *logical_volume_object = NULL;
	static char *function           = "pyvslvm_logical_volumes_iternext";

	if( logical_volumes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object.",
		 function );

		return( NULL );
	}
	if( logical_volumes_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( logical_volumes_object->current_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object - invalid current index.",
		 function );

		return( NULL );
	}
	if( logical_volumes_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volumes object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( logical_volumes_object->current_index >= logical_volumes_object->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	logical_volume_object = logical_volumes_object->get_item_by_index(
	                         logical_volumes_object->parent_object,
	                         logical_volumes_object->current_index );

	if( logical_volume_object != NULL )
	{
		logical_volumes_object->current_index++;
	}
	return( logical_volume_object );
}

