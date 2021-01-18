/*
 * Python object wrapper of libvslvm_segment_t
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
#include "pyvslvm_unused.h"

PyMethodDef pyvslvm_segment_object_methods[] = {

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvslvm_segment_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvslvm_segment_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvslvm.segment",
	/* tp_basicsize */
	sizeof( pyvslvm_segment_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvslvm_segment_free,
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
	"pyvslvm segment object (wraps libvslvm_segment_t)",
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
	pyvslvm_segment_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvslvm_segment_object_get_set_definitions,
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
	(initproc) pyvslvm_segment_init,
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

/* Creates a new segment object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvslvm_segment_new(
           libvslvm_segment_t *segment,
           pyvslvm_logical_volume_t *logical_volume_object )
{
	pyvslvm_segment_t *pyvslvm_segment = NULL;
	static char *function              = "pyvslvm_segment_new";

	if( segment == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid segment.",
		 function );

		return( NULL );
	}
	pyvslvm_segment = PyObject_New(
	                   struct pyvslvm_segment,
	                   &pyvslvm_segment_type_object );

	if( pyvslvm_segment == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize segment.",
		 function );

		goto on_error;
	}
	if( pyvslvm_segment_init(
	     pyvslvm_segment ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize segment.",
		 function );

		goto on_error;
	}
	pyvslvm_segment->segment               = segment;
	pyvslvm_segment->logical_volume_object = logical_volume_object;

	Py_IncRef(
	 (PyObject *) pyvslvm_segment->logical_volume_object );

	return( (PyObject *) pyvslvm_segment );

on_error:
	if( pyvslvm_segment != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_segment );
	}
	return( NULL );
}

/* Initializes a segment object
 * Returns 0 if successful or -1 on error
 */
int pyvslvm_segment_init(
     pyvslvm_segment_t *pyvslvm_segment )
{
	static char *function = "pyvslvm_segment_init";

	if( pyvslvm_segment == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid segment.",
		 function );

		return( -1 );
	}
	/* Make sure libvslvm segment is set to NULL
	 */
	pyvslvm_segment->segment = NULL;

	return( 0 );
}

/* Frees a segment object
 */
void pyvslvm_segment_free(
      pyvslvm_segment_t *pyvslvm_segment )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyvslvm_segment_free";

	if( pyvslvm_segment == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid segment.",
		 function );

		return;
	}
	if( pyvslvm_segment->segment == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid segment - missing libvslvm segment.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvslvm_segment );

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
	if( libvslvm_segment_free(
	     &( pyvslvm_segment->segment ),
	     &error ) != 1 )
	{
		pyvslvm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libvslvm segment.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyvslvm_segment->logical_volume_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvslvm_segment->logical_volume_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvslvm_segment );
}

