/*
 * Python object wrapper of libvslvm_handle_t
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

#if !defined( _PYVSLVM_HANDLE_H )
#define _PYVSLVM_HANDLE_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libbfio.h"
#include "pyvslvm_libcerror.h"
#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_handle pyvslvm_handle_t;

struct pyvslvm_handle
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvslvm handle
	 */
	libvslvm_handle_t *handle;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The file IO pool
	 */
	libbfio_pool_t *file_io_pool;
};

extern PyMethodDef pyvslvm_handle_object_methods[];
extern PyTypeObject pyvslvm_handle_type_object;

int pyvslvm_handle_init(
     pyvslvm_handle_t *pyvslvm_handle );

void pyvslvm_handle_free(
      pyvslvm_handle_t *pyvslvm_handle );

PyObject *pyvslvm_handle_signal_abort(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments );

PyObject *pyvslvm_handle_open(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_handle_open_file_object(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_handle_open_physical_volume_files(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_handle_open_physical_volume_files_as_file_objects(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvslvm_handle_close(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments );

PyObject *pyvslvm_handle_get_volume_group(
           pyvslvm_handle_t *pyvslvm_handle,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif

