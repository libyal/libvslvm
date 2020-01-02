/*
 * Python object definition of the sequence and iterator object of stripes
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
#include "pyvslvm_python.h"
#include "pyvslvm_stripe.h"
#include "pyvslvm_stripes.h"

PySequenceMethods pyvslvm_stripes_sequence_methods = {
	/* sq_length */
	(lenfunc) pyvslvm_stripes_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyvslvm_stripes_getitem,
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

PyTypeObject pyvslvm_stripes_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm._stripes",
	/* tp_basicsize */
	sizeof( pyvslvm_stripes_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_stripes_free,
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
	&pyvslvm_stripes_sequence_methods,
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
	"pyvslvm internal sequence and iterator object of stripes",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyvslvm_stripes_iter,
	/* tp_iternext */
	(iternextfunc) pyvslvm_stripes_iternext,
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
	(initproc) pyvslvm_stripes_init,
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

/* Creates a new stripes object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_stripes_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items )
{
	pyvslvm_stripes_t *stripes_object = NULL;
	static char *function             = "pyvslvm_stripes_new";

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
	/* Make sure the stripes values are initialized
	 */
	stripes_object = PyObject_New(
	                  struct pyvslvm_stripes,
	                  &pyvslvm_stripes_type_object );

	if( stripes_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create stripes object.",
		 function );

		goto on_error;
	}
	if( pyvslvm_stripes_init(
	     stripes_object ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stripes object.",
		 function );

		goto on_error;
	}
	stripes_object->parent_object     = parent_object;
	stripes_object->get_item_by_index = get_item_by_index;
	stripes_object->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) stripes_object->parent_object );

	return( (PyObject *) stripes_object );

on_error:
	if( stripes_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) stripes_object );
	}
	return( NULL );
}

/* Intializes a stripes object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_stripes_init(
     pyvslvm_stripes_t *stripes_object )
{
	static char *function = "pyvslvm_stripes_init";

	if( stripes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object.",
		 function );

		return( -1 );
	}
	/* Make sure the stripes values are initialized
	 */
	stripes_object->parent_object     = NULL;
	stripes_object->get_item_by_index = NULL;
	stripes_object->current_index     = 0;
	stripes_object->number_of_items   = 0;

	return( 0 );
}

/* Frees a stripes object
 */
void pyvslvm_stripes_free(
      pyvslvm_stripes_t *stripes_object )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_stripes_free";

	if( stripes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           stripes_object );

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
	if( stripes_object->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) stripes_object->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) stripes_object );
}

/* The stripes len() function
 */
Py_ssize_t pyvslvm_stripes_len(
            pyvslvm_stripes_t *stripes_object )
{
	static char *function = "pyvslvm_stripes_len";

	if( stripes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) stripes_object->number_of_items );
}

/* The stripes getitem() function
 */
PyObject *pyvslvm_stripes_getitem(
           pyvslvm_stripes_t *stripes_object,
           Py_ssize_t item_index )
{
	PyObject *stripe_object = NULL;
	static char *function   = "pyvslvm_stripes_getitem";

	if( stripes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object.",
		 function );

		return( NULL );
	}
	if( stripes_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( stripes_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) stripes_object->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	stripe_object = stripes_object->get_item_by_index(
	                 stripes_object->parent_object,
	                 (int) item_index );

	return( stripe_object );
}

/* The stripes iter() function
 */
PyObject *pyvslvm_stripes_iter(
           pyvslvm_stripes_t *stripes_object )
{
	static char *function = "pyvslvm_stripes_iter";

	if( stripes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) stripes_object );

	return( (PyObject *) stripes_object );
}

/* The stripes iternext() function
 */
PyObject *pyvslvm_stripes_iternext(
           pyvslvm_stripes_t *stripes_object )
{
	PyObject *stripe_object = NULL;
	static char *function   = "pyvslvm_stripes_iternext";

	if( stripes_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object.",
		 function );

		return( NULL );
	}
	if( stripes_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( stripes_object->current_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object - invalid current index.",
		 function );

		return( NULL );
	}
	if( stripes_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( stripes_object->current_index >= stripes_object->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	stripe_object = stripes_object->get_item_by_index(
	                 stripes_object->parent_object,
	                 stripes_object->current_index );

	if( stripe_object != NULL )
	{
		stripes_object->current_index++;
	}
	return( stripe_object );
}

