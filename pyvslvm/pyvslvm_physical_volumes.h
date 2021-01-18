/*
 * Python object definition of the sequence and iterator object of physical volumes
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

#if !defined( _PYVSLVM_PHYSICAL_VOLUMES_H )
#define _PYVSLVM_PHYSICAL_VOLUMES_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_physical_volumes pyvslvm_physical_volumes_t;

struct pyvslvm_physical_volumes
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

extern PyTypeObject pyvslvm_physical_volumes_type_object;

PyObject *pyvslvm_physical_volumes_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyvslvm_physical_volumes_init(
     pyvslvm_physical_volumes_t *sequence_object );

void pyvslvm_physical_volumes_free(
      pyvslvm_physical_volumes_t *sequence_object );

Py_ssize_t pyvslvm_physical_volumes_len(
            pyvslvm_physical_volumes_t *sequence_object );

PyObject *pyvslvm_physical_volumes_getitem(
           pyvslvm_physical_volumes_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyvslvm_physical_volumes_iter(
           pyvslvm_physical_volumes_t *sequence_object );

PyObject *pyvslvm_physical_volumes_iternext(
           pyvslvm_physical_volumes_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSLVM_PHYSICAL_VOLUMES_H ) */

