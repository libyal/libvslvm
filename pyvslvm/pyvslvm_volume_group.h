/*
 * Python object wrapper of libvslvm_volume_group_t
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

#if !defined( _PYVSLVM_VOLUME_GROUP_H )
#define _PYVSLVM_VOLUME_GROUP_H

#include <common.h>
#include <types.h>

#include "pyvslvm_handle.h"
#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_volume_group pyvslvm_volume_group_t;

struct pyvslvm_volume_group
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvslvm volume group
	 */
	libvslvm_volume_group_t *volume_group;

	/* The handle object
	 */
	pyvslvm_handle_t *handle_object;
};

extern PyMethodDef pyvslvm_volume_group_object_methods[];
extern PyTypeObject pyvslvm_volume_group_type_object;

PyObject *pyvslvm_volume_group_new(
           libvslvm_volume_group_t *volume_group,
           pyvslvm_handle_t *handle_object );

int pyvslvm_volume_group_init(
     pyvslvm_volume_group_t *pyvslvm_volume_group );

void pyvslvm_volume_group_free(
      pyvslvm_volume_group_t *pyvslvm_volume_group );

PyObject *pyvslvm_volume_group_get_name(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments );

PyObject *pyvslvm_volume_group_get_identifier(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments );

/* TODO add get sequence number */

/* TODO add get extent_size */

PyObject *pyvslvm_volume_group_get_number_of_physical_volumes(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments );

PyObject *pyvslvm_volume_group_get_physical_volume_by_index(
           PyObject *pyvslvm_volume_group,
           int volume_index );

PyObject *pyvslvm_volume_group_get_physical_volume(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_volume_group_get_physical_volumes(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments );

PyObject *pyvslvm_volume_group_get_number_of_logical_volumes(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments );

PyObject *pyvslvm_volume_group_get_logical_volume_by_index(
           PyObject *pyvslvm_volume_group,
           int volume_index );

PyObject *pyvslvm_volume_group_get_logical_volume(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_volume_group_get_logical_volumes(
           pyvslvm_volume_group_t *pyvslvm_volume_group,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif

