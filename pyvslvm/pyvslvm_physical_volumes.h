/*
 * Python object definition of the physical volumes sequence and iterator
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

#if !defined( _PYVSLVM_PHYSICAL_VOLUMES_H )
#define _PYVSLVM_PHYSICAL_VOLUMES_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"
#include "pyvslvm_volume_group.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_physical_volumes pyvslvm_physical_volumes_t;

struct pyvslvm_physical_volumes
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The pyvslvm volume group object
	 */
	pyvslvm_volume_group_t *volume_group_object;

	/* The get physical volume by index callback function
	 */
	PyObject* (*get_physical_volume_by_index)(
	             pyvslvm_volume_group_t *volume_group_object,
	             int physical_volume_index );

	/* The (current) physical volume index
	 */
	int physical_volume_index;

	/* The number of physical volumes
	 */
	int number_of_physical_volumes;
};

extern PyTypeObject pyvslvm_physical_volumes_type_object;

PyObject *pyvslvm_physical_volumes_new(
           pyvslvm_volume_group_t *volume_group_object,
           PyObject* (*get_physical_volume_by_index)(
                        pyvslvm_volume_group_t *volume_group_object,
                        int physical_volume_index ),
           int number_of_physical_volumes );

int pyvslvm_physical_volumes_init(
     pyvslvm_physical_volumes_t *pyvslvm_physical_volumes );

void pyvslvm_physical_volumes_free(
      pyvslvm_physical_volumes_t *pyvslvm_physical_volumes );

Py_ssize_t pyvslvm_physical_volumes_len(
            pyvslvm_physical_volumes_t *pyvslvm_physical_volumes );

PyObject *pyvslvm_physical_volumes_getitem(
           pyvslvm_physical_volumes_t *pyvslvm_physical_volumes,
           Py_ssize_t item_index );

PyObject *pyvslvm_physical_volumes_iter(
           pyvslvm_physical_volumes_t *pyvslvm_physical_volumes );

PyObject *pyvslvm_physical_volumes_iternext(
           pyvslvm_physical_volumes_t *pyvslvm_physical_volumes );

#if defined( __cplusplus )
}
#endif

#endif

