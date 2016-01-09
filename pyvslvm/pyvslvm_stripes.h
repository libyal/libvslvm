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

#if !defined( _PYVSLVM_STRIPES_H )
#define _PYVSLVM_STRIPES_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"
#include "pyvslvm_segment.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_stripes pyvslvm_stripes_t;

struct pyvslvm_stripes
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The pyvslvm segment object
	 */
	pyvslvm_segment_t *segment_object;

	/* The get stripe by index callback function
	 */
	PyObject* (*get_stripe_by_index)(
	             pyvslvm_segment_t *segment_object,
	             int stripe_index );

	/* The (current) stripe index
	 */
	int stripe_index;

	/* The number of stripes
	 */
	int number_of_stripes;
};

extern PyTypeObject pyvslvm_stripes_type_object;

PyObject *pyvslvm_stripes_new(
           pyvslvm_segment_t *segment_object,
           PyObject* (*get_stripe_by_index)(
                        pyvslvm_segment_t *segment_object,
                        int stripe_index ),
           int number_of_stripes );

int pyvslvm_stripes_init(
     pyvslvm_stripes_t *pyvslvm_stripes );

void pyvslvm_stripes_free(
      pyvslvm_stripes_t *pyvslvm_stripes );

Py_ssize_t pyvslvm_stripes_len(
            pyvslvm_stripes_t *pyvslvm_stripes );

PyObject *pyvslvm_stripes_getitem(
           pyvslvm_stripes_t *pyvslvm_stripes,
           Py_ssize_t item_index );

PyObject *pyvslvm_stripes_iter(
           pyvslvm_stripes_t *pyvslvm_stripes );

PyObject *pyvslvm_stripes_iternext(
           pyvslvm_stripes_t *pyvslvm_stripes );

#if defined( __cplusplus )
}
#endif

#endif

