/*
 * Python object definition of the stripes sequence and iterator
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
#include "pyvslvm_python.h"
#include "pyvslvm_segment.h"
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
	"internal pyvslvm stripes sequence and iterator object",
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
           pyvslvm_segment_t *segment_object,
           PyObject* (*get_stripe_by_index)(
                        pyvslvm_segment_t *segment_object,
                        int stripe_index ),
           int number_of_stripes )
{
	pyvslvm_stripes_t *pyvslvm_stripes = NULL;
	static char *function              = "pyvslvm_stripes_new";

	if( segment_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid segment object.",
		 function );

		return( NULL );
	}
	if( get_stripe_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get stripe by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the stripes values are initialized
	 */
	pyvslvm_stripes = PyObject_New(
	                   struct pyvslvm_stripes,
	                   &pyvslvm_stripes_type_object );

	if( pyvslvm_stripes == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stripes.",
		 function );

		goto on_error;
	}
	if( pyvslvm_stripes_init(
	     pyvslvm_stripes ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stripes.",
		 function );

		goto on_error;
	}
	pyvslvm_stripes->segment_object      = segment_object;
	pyvslvm_stripes->get_stripe_by_index = get_stripe_by_index;
	pyvslvm_stripes->number_of_stripes   = number_of_stripes;

	Py_IncRef(
	 (PyObject *) pyvslvm_stripes->segment_object );

	return( (PyObject *) pyvslvm_stripes );

on_error:
	if( pyvslvm_stripes != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_stripes );
	}
	return( NULL );
}

/* Intializes a stripes object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_stripes_init(
     pyvslvm_stripes_t *pyvslvm_stripes )
{
	static char *function = "pyvslvm_stripes_init";

	if( pyvslvm_stripes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes.",
		 function );

		return( -1 );
	}
	/* Make sure the stripes values are initialized
	 */
	pyvslvm_stripes->segment_object      = NULL;
	pyvslvm_stripes->get_stripe_by_index = NULL;
	pyvslvm_stripes->stripe_index        = 0;
	pyvslvm_stripes->number_of_stripes   = 0;

	return( 0 );
}

/* Frees a stripes object
 */
void pyvslvm_stripes_free(
      pyvslvm_stripes_t *pyvslvm_stripes )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_stripes_free";

	if( pyvslvm_stripes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_stripes );

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
	if( pyvslvm_stripes->segment_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_stripes->segment_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_stripes );
}

/* The stripes len() function
 */
Py_ssize_t pyvslvm_stripes_len(
            pyvslvm_stripes_t *pyvslvm_stripes )
{
	static char *function = "pyvslvm_stripes_len";

	if( pyvslvm_stripes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyvslvm_stripes->number_of_stripes );
}

/* The stripes getitem() function
 */
PyObject *pyvslvm_stripes_getitem(
           pyvslvm_stripes_t *pyvslvm_stripes,
           Py_ssize_t item_index )
{
	PyObject *stripe_object = NULL;
	static char *function   = "pyvslvm_stripes_getitem";

	if( pyvslvm_stripes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes.",
		 function );

		return( NULL );
	}
	if( pyvslvm_stripes->get_stripe_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes - missing get stripe by index function.",
		 function );

		return( NULL );
	}
	if( pyvslvm_stripes->number_of_stripes < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes - invalid number of stripes.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pyvslvm_stripes->number_of_stripes ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	stripe_object = pyvslvm_stripes->get_stripe_by_index(
	                 pyvslvm_stripes->segment_object,
	                 (int) item_index );

	return( stripe_object );
}

/* The stripes iter() function
 */
PyObject *pyvslvm_stripes_iter(
           pyvslvm_stripes_t *pyvslvm_stripes )
{
	static char *function = "pyvslvm_stripes_iter";

	if( pyvslvm_stripes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyvslvm_stripes );

	return( (PyObject *) pyvslvm_stripes );
}

/* The stripes iternext() function
 */
PyObject *pyvslvm_stripes_iternext(
           pyvslvm_stripes_t *pyvslvm_stripes )
{
	PyObject *stripe_object = NULL;
	static char *function   = "pyvslvm_stripes_iternext";

	if( pyvslvm_stripes == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes.",
		 function );

		return( NULL );
	}
	if( pyvslvm_stripes->get_stripe_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes - missing get stripe by index function.",
		 function );

		return( NULL );
	}
	if( pyvslvm_stripes->stripe_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes - invalid stripe index.",
		 function );

		return( NULL );
	}
	if( pyvslvm_stripes->number_of_stripes < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stripes - invalid number of stripes.",
		 function );

		return( NULL );
	}
	if( pyvslvm_stripes->stripe_index >= pyvslvm_stripes->number_of_stripes )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	stripe_object = pyvslvm_stripes->get_stripe_by_index(
	                 pyvslvm_stripes->segment_object,
	                 pyvslvm_stripes->stripe_index );

	if( stripe_object != NULL )
	{
		pyvslvm_stripes->stripe_index++;
	}
	return( stripe_object );
}

