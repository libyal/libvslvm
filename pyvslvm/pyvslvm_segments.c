/*
 * Python object definition of the sequence and iterator object of segments
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
#include "pyvslvm_segment.h"
#include "pyvslvm_segments.h"

PySequenceMethods pyvslvm_segments_sequence_methods = {
	/* sq_length */
	(lenfunc) pyvslvm_segments_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyvslvm_segments_getitem,
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

PyTypeObject pyvslvm_segments_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm._segments",
	/* tp_basicsize */
	sizeof( pyvslvm_segments_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_segments_free,
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
	&pyvslvm_segments_sequence_methods,
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
	"pyvslvm internal sequence and iterator object of segments",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyvslvm_segments_iter,
	/* tp_iternext */
	(iternextfunc) pyvslvm_segments_iternext,
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
	(initproc) pyvslvm_segments_init,
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

/* Creates a new segments object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_segments_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items )
{
	pyvslvm_segments_t *segments_object = NULL;
	static char *function               = "pyvslvm_segments_new";

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
	/* Make sure the segments values are initialized
	 */
	segments_object = PyObject_New(
	                   struct pyvslvm_segments,
	                   &pyvslvm_segments_type_object );

	if( segments_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create segments object.",
		 function );

		goto on_error;
	}
	if( pyvslvm_segments_init(
	     segments_object ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize segments object.",
		 function );

		goto on_error;
	}
	segments_object->parent_object     = parent_object;
	segments_object->get_item_by_index = get_item_by_index;
	segments_object->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) segments_object->parent_object );

	return( (PyObject *) segments_object );

on_error:
	if( segments_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) segments_object );
	}
	return( NULL );
}

/* Intializes a segments object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_segments_init(
     pyvslvm_segments_t *segments_object )
{
	static char *function = "pyvslvm_segments_init";

	if( segments_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object.",
		 function );

		return( -1 );
	}
	/* Make sure the segments values are initialized
	 */
	segments_object->parent_object     = NULL;
	segments_object->get_item_by_index = NULL;
	segments_object->current_index     = 0;
	segments_object->number_of_items   = 0;

	return( 0 );
}

/* Frees a segments object
 */
void pyvslvm_segments_free(
      pyvslvm_segments_t *segments_object )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_segments_free";

	if( segments_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           segments_object );

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
	if( segments_object->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) segments_object->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) segments_object );
}

/* The segments len() function
 */
Py_ssize_t pyvslvm_segments_len(
            pyvslvm_segments_t *segments_object )
{
	static char *function = "pyvslvm_segments_len";

	if( segments_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) segments_object->number_of_items );
}

/* The segments getitem() function
 */
PyObject *pyvslvm_segments_getitem(
           pyvslvm_segments_t *segments_object,
           Py_ssize_t item_index )
{
	PyObject *segment_object = NULL;
	static char *function    = "pyvslvm_segments_getitem";

	if( segments_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object.",
		 function );

		return( NULL );
	}
	if( segments_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( segments_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) segments_object->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	segment_object = segments_object->get_item_by_index(
	                  segments_object->parent_object,
	                  (int) item_index );

	return( segment_object );
}

/* The segments iter() function
 */
PyObject *pyvslvm_segments_iter(
           pyvslvm_segments_t *segments_object )
{
	static char *function = "pyvslvm_segments_iter";

	if( segments_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) segments_object );

	return( (PyObject *) segments_object );
}

/* The segments iternext() function
 */
PyObject *pyvslvm_segments_iternext(
           pyvslvm_segments_t *segments_object )
{
	PyObject *segment_object = NULL;
	static char *function    = "pyvslvm_segments_iternext";

	if( segments_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object.",
		 function );

		return( NULL );
	}
	if( segments_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( segments_object->current_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object - invalid current index.",
		 function );

		return( NULL );
	}
	if( segments_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( segments_object->current_index >= segments_object->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	segment_object = segments_object->get_item_by_index(
	                  segments_object->parent_object,
	                  segments_object->current_index );

	if( segment_object != NULL )
	{
		segments_object->current_index++;
	}
	return( segment_object );
}

