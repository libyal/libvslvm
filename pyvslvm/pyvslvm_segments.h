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

#if !defined( _PYVSLVM_SEGMENTS_H )
#define _PYVSLVM_SEGMENTS_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"
#include "pyvslvm_logical_volume.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_segments pyvslvm_segments_t;

struct pyvslvm_segments
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The pyvslvm logical volume object
	 */
	pyvslvm_logical_volume_t *logical_volume_object;

	/* The get segment by index callback function
	 */
	PyObject* (*get_segment_by_index)(
	             pyvslvm_logical_volume_t *logical_volume_object,
	             int segment_index );

	/* The (current) segment index
	 */
	int segment_index;

	/* The number of segments
	 */
	int number_of_segments;
};

extern PyTypeObject pyvslvm_segments_type_object;

PyObject *pyvslvm_segments_new(
           pyvslvm_logical_volume_t *logical_volume_object,
           PyObject* (*get_segment_by_index)(
                        pyvslvm_logical_volume_t *logical_volume_object,
                        int segment_index ),
           int number_of_segments );

int pyvslvm_segments_init(
     pyvslvm_segments_t *pyvslvm_segments );

void pyvslvm_segments_free(
      pyvslvm_segments_t *pyvslvm_segments );

Py_ssize_t pyvslvm_segments_len(
            pyvslvm_segments_t *pyvslvm_segments );

PyObject *pyvslvm_segments_getitem(
           pyvslvm_segments_t *pyvslvm_segments,
           Py_ssize_t item_index );

PyObject *pyvslvm_segments_iter(
           pyvslvm_segments_t *pyvslvm_segments );

PyObject *pyvslvm_segments_iternext(
           pyvslvm_segments_t *pyvslvm_segments );

#if defined( __cplusplus )
}
#endif

#endif

