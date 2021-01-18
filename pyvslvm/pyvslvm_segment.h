/*
 * Python object wrapper of libvslvm_segment_t
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

#if !defined( _PYVSLVM_SEGMENT_H )
#define _PYVSLVM_SEGMENT_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_logical_volume.h"
#include "pyvslvm_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_segment pyvslvm_segment_t;

struct pyvslvm_segment
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvslvm segment
	 */
	libvslvm_segment_t *segment;

	/* The pyvslvm logical volume object
	 */
	pyvslvm_logical_volume_t *logical_volume_object;
};

extern PyMethodDef pyvslvm_segment_object_methods[];
extern PyTypeObject pyvslvm_segment_type_object;

PyObject *pyvslvm_segment_new(
           libvslvm_segment_t *segment,
           pyvslvm_logical_volume_t *logical_volume_object );

int pyvslvm_segment_init(
     pyvslvm_segment_t *pyvslvm_segment );

void pyvslvm_segment_free(
      pyvslvm_segment_t *pyvslvm_segment );

#if defined( __cplusplus )
}
#endif

#endif

