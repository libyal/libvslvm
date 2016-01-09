/*
 * Python object definition of the logical volumes sequence and iterator
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

#if !defined( _PYVSLVM_LOGICAL_VOLUMES_H )
#define _PYVSLVM_LOGICAL_VOLUMES_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"
#include "pyvslvm_volume_group.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_logical_volumes pyvslvm_logical_volumes_t;

struct pyvslvm_logical_volumes
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The pyvslvm volume group object
	 */
	pyvslvm_volume_group_t *volume_group_object;

	/* The get logical volume by index callback function
	 */
	PyObject* (*get_logical_volume_by_index)(
	             pyvslvm_volume_group_t *volume_group_object,
	             int logical_volume_index );

	/* The (current) logical volume index
	 */
	int logical_volume_index;

	/* The number of logical volumes
	 */
	int number_of_logical_volumes;
};

extern PyTypeObject pyvslvm_logical_volumes_type_object;

PyObject *pyvslvm_logical_volumes_new(
           pyvslvm_volume_group_t *volume_group_object,
           PyObject* (*get_logical_volume_by_index)(
                        pyvslvm_volume_group_t *volume_group_object,
                        int logical_volume_index ),
           int number_of_logical_volumes );

int pyvslvm_logical_volumes_init(
     pyvslvm_logical_volumes_t *pyvslvm_logical_volumes );

void pyvslvm_logical_volumes_free(
      pyvslvm_logical_volumes_t *pyvslvm_logical_volumes );

Py_ssize_t pyvslvm_logical_volumes_len(
            pyvslvm_logical_volumes_t *pyvslvm_logical_volumes );

PyObject *pyvslvm_logical_volumes_getitem(
           pyvslvm_logical_volumes_t *pyvslvm_logical_volumes,
           Py_ssize_t item_index );

PyObject *pyvslvm_logical_volumes_iter(
           pyvslvm_logical_volumes_t *pyvslvm_logical_volumes );

PyObject *pyvslvm_logical_volumes_iternext(
           pyvslvm_logical_volumes_t *pyvslvm_logical_volumes );

#if defined( __cplusplus )
}
#endif

#endif

