/*
 * Python object wrapper of libvslvm_logical_volume_t
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

#if !defined( _PYVSLVM_LOGICAL_VOLUME_H )
#define _PYVSLVM_LOGICAL_VOLUME_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"
#include "pyvslvm_volume_group.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_logical_volume pyvslvm_logical_volume_t;

struct pyvslvm_logical_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvslvm logical volume
	 */
	libvslvm_logical_volume_t *logical_volume;

	/* The pyvslvm volume group object
	 */
	pyvslvm_volume_group_t *volume_group_object;
};

extern PyMethodDef pyvslvm_logical_volume_object_methods[];
extern PyTypeObject pyvslvm_logical_volume_type_object;

PyObject *pyvslvm_logical_volume_new(
           libvslvm_logical_volume_t *logical_volume,
           pyvslvm_volume_group_t *volume_group_object );

int pyvslvm_logical_volume_init(
     pyvslvm_logical_volume_t *pyvslvm_logical_volume );

void pyvslvm_logical_volume_free(
      pyvslvm_logical_volume_t *pyvslvm_logical_volume );

PyObject *pyvslvm_logical_volume_read_buffer(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_logical_volume_read_buffer_at_offset(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_logical_volume_seek_offset(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_logical_volume_get_offset(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments );

PyObject *pyvslvm_logical_volume_get_size(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments );

PyObject *pyvslvm_logical_volume_get_name(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments );

PyObject *pyvslvm_logical_volume_get_identifier(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments );

PyObject *pyvslvm_logical_volume_get_number_of_segments(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments );

PyObject *pyvslvm_logical_volume_get_segment_by_index(
           PyObject *pyvslvm_logical_volume,
           int segment_index );

PyObject *pyvslvm_logical_volume_get_segment(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_logical_volume_get_segments(
           pyvslvm_logical_volume_t *pyvslvm_logical_volume,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSLVM_LOGICAL_VOLUME_H ) */

