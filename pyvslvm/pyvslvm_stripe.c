/*
 * Python object wrapper of libvslvm_stripe_t
 *
 * Copyright (C) 2014-2024, Joachim Metz <joachim.metz@gmail.com>
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
#include "pyvslvm_python.h"
#include "pyvslvm_segment.h"
#include "pyvslvm_stripe.h"
#include "pyvslvm_unused.h"

PyMethodDef pyvslvm_stripe_object_methods[] = {

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvslvm_stripe_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvslvm_stripe_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm.stripe",
	/* tp_basicsize */
	sizeof( pyvslvm_stripe_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_stripe_free,
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
	"pyvslvm stripe object (wraps libvslvm_stripe_t)",
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
	pyvslvm_stripe_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvslvm_stripe_object_get_set_definitions,
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
	(initproc) pyvslvm_stripe_init,
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

/* Creates a new stripe object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_stripe_new(
           libvslvm_stripe_t *stripe,
           pyvslvm_segment_t *segment_object )
{
	pyvslvm_stripe_t *pyvslvm_stripe = NULL;
	static char *function            = "pyvslvm_stripe_new";

	if( stripe == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stripe.",
		 function );

		return( NULL );
	}
	pyvslvm_stripe = PyObject_New(
	                  struct pyvslvm_stripe,
	                  &pyvslvm_stripe_type_object );

	if( pyvslvm_stripe == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stripe.",
		 function );

		goto on_error;
	}
	if( pyvslvm_stripe_init(
	     pyvslvm_stripe ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stripe.",
		 function );

		goto on_error;
	}
	pyvslvm_stripe->stripe         = stripe;
	pyvslvm_stripe->segment_object = segment_object;

	Py_IncRef(
	 (PyObject *) pyvslvm_stripe->segment_object );

	return( (PyObject *) pyvslvm_stripe );

on_error:
	if( pyvslvm_stripe != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_stripe );
	}
	return( NULL );
}

/* Initializes a stripe object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_stripe_init(
     pyvslvm_stripe_t *pyvslvm_stripe )
{
	static char *function = "pyvslvm_stripe_init";

	if( pyvslvm_stripe == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stripe.",
		 function );

		return( -1 );
	}
	/* Make sure libvslvm stripe is set to NULL
	 */
	pyvslvm_stripe->stripe = NULL;

	return( 0 );
}

/* Frees a stripe object
 */
void pyvslvm_stripe_free(
      pyvslvm_stripe_t *pyvslvm_stripe )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_stripe_free";

	if( pyvslvm_stripe == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stripe.",
		 function );

		return;
	}
	if( pyvslvm_stripe->stripe == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stripe - missing libvslvm stripe.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_stripe );

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
	if( libvslvm_stripe_free(
	     &( pyvslvm_stripe->stripe ),
	     &error ) != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libvslvm stripe.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyvslvm_stripe->segment_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_stripe->segment_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_stripe );
}

