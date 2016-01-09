/*
 * Python object definition of the segments sequence and iterator
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_logical_volume.h"
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
	"internal pyvslvm segments sequence and iterator object",
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
           pyvslvm_logical_volume_t *logical_volume_object,
           PyObject* (*get_segment_by_index)(
                        pyvslvm_logical_volume_t *logical_volume_object,
                        int segment_index ),
           int number_of_segments )
{
	pyvslvm_segments_t *pyvslvm_segments = NULL;
	static char *function                = "pyvslvm_segments_new";

	if( logical_volume_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid logical volume object.",
		 function );

		return( NULL );
	}
	if( get_segment_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get segment by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the segments values are initialized
	 */
	pyvslvm_segments = PyObject_New(
	                    struct pyvslvm_segments,
	                    &pyvslvm_segments_type_object );

	if( pyvslvm_segments == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize segments.",
		 function );

		goto on_error;
	}
	if( pyvslvm_segments_init(
	     pyvslvm_segments ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize segments.",
		 function );

		goto on_error;
	}
	pyvslvm_segments->logical_volume_object = logical_volume_object;
	pyvslvm_segments->get_segment_by_index  = get_segment_by_index;
	pyvslvm_segments->number_of_segments    = number_of_segments;

	Py_IncRef(
	 (PyObject *) pyvslvm_segments->logical_volume_object );

	return( (PyObject *) pyvslvm_segments );

on_error:
	if( pyvslvm_segments != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_segments );
	}
	return( NULL );
}

/* Intializes a segments object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_segments_init(
     pyvslvm_segments_t *pyvslvm_segments )
{
	static char *function = "pyvslvm_segments_init";

	if( pyvslvm_segments == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments.",
		 function );

		return( -1 );
	}
	/* Make sure the segments values are initialized
	 */
	pyvslvm_segments->logical_volume_object = NULL;
	pyvslvm_segments->get_segment_by_index  = NULL;
	pyvslvm_segments->segment_index         = 0;
	pyvslvm_segments->number_of_segments    = 0;

	return( 0 );
}

/* Frees a segments object
 */
void pyvslvm_segments_free(
      pyvslvm_segments_t *pyvslvm_segments )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_segments_free";

	if( pyvslvm_segments == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_segments );

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
	if( pyvslvm_segments->logical_volume_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_segments->logical_volume_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_segments );
}

/* The segments len() function
 */
Py_ssize_t pyvslvm_segments_len(
            pyvslvm_segments_t *pyvslvm_segments )
{
	static char *function = "pyvslvm_segments_len";

	if( pyvslvm_segments == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyvslvm_segments->number_of_segments );
}

/* The segments getitem() function
 */
PyObject *pyvslvm_segments_getitem(
           pyvslvm_segments_t *pyvslvm_segments,
           Py_ssize_t item_index )
{
	PyObject *segment_object = NULL;
	static char *function    = "pyvslvm_segments_getitem";

	if( pyvslvm_segments == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments.",
		 function );

		return( NULL );
	}
	if( pyvslvm_segments->get_segment_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments - missing get segment by index function.",
		 function );

		return( NULL );
	}
	if( pyvslvm_segments->number_of_segments < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments - invalid number of segments.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pyvslvm_segments->number_of_segments ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	segment_object = pyvslvm_segments->get_segment_by_index(
	                  pyvslvm_segments->logical_volume_object,
	                  (int) item_index );

	return( segment_object );
}

/* The segments iter() function
 */
PyObject *pyvslvm_segments_iter(
           pyvslvm_segments_t *pyvslvm_segments )
{
	static char *function = "pyvslvm_segments_iter";

	if( pyvslvm_segments == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyvslvm_segments );

	return( (PyObject *) pyvslvm_segments );
}

/* The segments iternext() function
 */
PyObject *pyvslvm_segments_iternext(
           pyvslvm_segments_t *pyvslvm_segments )
{
	PyObject *segment_object = NULL;
	static char *function    = "pyvslvm_segments_iternext";

	if( pyvslvm_segments == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments.",
		 function );

		return( NULL );
	}
	if( pyvslvm_segments->get_segment_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments - missing get segment by index function.",
		 function );

		return( NULL );
	}
	if( pyvslvm_segments->segment_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments - invalid segment index.",
		 function );

		return( NULL );
	}
	if( pyvslvm_segments->number_of_segments < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segments - invalid number of segments.",
		 function );

		return( NULL );
	}
	if( pyvslvm_segments->segment_index >= pyvslvm_segments->number_of_segments )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	segment_object = pyvslvm_segments->get_segment_by_index(
	                  pyvslvm_segments->logical_volume_object,
	                  pyvslvm_segments->segment_index );

	if( segment_object != NULL )
	{
		pyvslvm_segments->segment_index++;
	}
	return( segment_object );
}

