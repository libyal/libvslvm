/*
 * Python object definition of the sequence and iterator object of segments
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

#if !defined( _PYVSLVM_SEGMENTS_H )
#define _PYVSLVM_SEGMENTS_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_segments pyvslvm_segments_t;

struct pyvslvm_segments
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyvslvm_segments_type_object;

PyObject *pyvslvm_segments_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyvslvm_segments_init(
     pyvslvm_segments_t *sequence_object );

void pyvslvm_segments_free(
      pyvslvm_segments_t *sequence_object );

Py_ssize_t pyvslvm_segments_len(
            pyvslvm_segments_t *sequence_object );

PyObject *pyvslvm_segments_getitem(
           pyvslvm_segments_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyvslvm_segments_iter(
           pyvslvm_segments_t *sequence_object );

PyObject *pyvslvm_segments_iternext(
           pyvslvm_segments_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSLVM_SEGMENTS_H ) */

