/*
 * Python object wrapper of libvslvm_physical_volume_t
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

#if !defined( _PYVSLVM_PHYSICAL_VOLUME_H )
#define _PYVSLVM_PHYSICAL_VOLUME_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"
#include "pyvslvm_volume_group.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_physical_volume pyvslvm_physical_volume_t;

struct pyvslvm_physical_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvslvm physical volume
	 */
	libvslvm_physical_volume_t *physical_volume;

	/* The pyvslvm volume group object
	 */
	pyvslvm_volume_group_t *volume_group_object;
};

extern PyMethodDef pyvslvm_physical_volume_object_methods[];
extern PyTypeObject pyvslvm_physical_volume_type_object;

PyObject *pyvslvm_physical_volume_new(
           libvslvm_physical_volume_t *physical_volume,
           pyvslvm_volume_group_t *volume_group_object );

int pyvslvm_physical_volume_init(
     pyvslvm_physical_volume_t *pyvslvm_physical_volume );

void pyvslvm_physical_volume_free(
      pyvslvm_physical_volume_t *pyvslvm_physical_volume );

PyObject *pyvslvm_physical_volume_get_name(
           pyvslvm_physical_volume_t *pyvslvm_physical_volume,
           PyObject *arguments );

PyObject *pyvslvm_physical_volume_get_identifier(
           pyvslvm_physical_volume_t *pyvslvm_physical_volume,
           PyObject *arguments );

PyObject *pyvslvm_physical_volume_get_device_path(
           pyvslvm_physical_volume_t *pyvslvm_physical_volume,
           PyObject *arguments );

PyObject *pyvslvm_physical_volume_get_size(
           pyvslvm_physical_volume_t *pyvslvm_physical_volume,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif

