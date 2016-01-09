/*
 * Python object definition of the libvslvm physical volume
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvslvm_error.h"
#include "pyvslvm_integer.h"
#include "pyvslvm_libcerror.h"
#include "pyvslvm_libcstring.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_physical_volume.h"
#include "pyvslvm_python.h"
#include "pyvslvm_unused.h"
#include "pyvslvm_volume_group.h"

PyMethodDef pyvslvm_physical_volume_object_methods[] = {

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvslvm_physical_volume_object_get_set_definitions[] = {

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

/* Intializes a physical volume object
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

