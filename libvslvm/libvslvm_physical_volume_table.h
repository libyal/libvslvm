/*
 * Physical volume table functions
 *
 * Copyright (C) 2014-2015, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVSLVM_PHYSICAL_VOLUME_TABLE_H )
#define _LIBVSLVM_PHYSICAL_VOLUME_TABLE_H

#include <common.h>
#include <types.h>

#include "libvslvm_io_handle.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcstring.h"
#include "libvslvm_libfcache.h"
#include "libvslvm_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_physical_volume_table libvslvm_physical_volume_table_t;

struct libvslvm_physical_volume_table
{
	/* The physical volumes list
	 */
	libfdata_list_t *physical_volumes_list;

	/* The physical volumes cache
	 */
	libfcache_cache_t *physical_volumes_cache;

	/* The number of physical volumes
	 */
	int number_of_physical_volumes;
};

int libvslvm_physical_volume_table_initialize(
     libvslvm_physical_volume_table_t **physical_volume_table,
     libcerror_error_t **error );

int libvslvm_physical_volume_table_free(
     libvslvm_physical_volume_table_t **physical_volume_table,
     libcerror_error_t **error );

int libvslvm_physical_volume_table_clear(
     libvslvm_physical_volume_table_t *physical_volume_table,
     libcerror_error_t **error );

int libvslvm_physical_volume_table_initialize_physical_volumes(
     libvslvm_physical_volume_table_t *physical_volume_table,
     int number_of_physical_volumes,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

