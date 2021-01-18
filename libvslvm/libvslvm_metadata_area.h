/*
 * The metadata area functions
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

#if !defined( _LIBVSLVM_METADATA_AREA_H )
#define _LIBVSLVM_METADATA_AREA_H

#include <common.h>
#include <types.h>

#include "libvslvm_libbfio.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_metadata_area libvslvm_metadata_area_t;

struct libvslvm_metadata_area
{
	/* The raw location descriptors array
	 */
	libcdata_array_t *raw_location_descriptors_array;
};

int libvslvm_metadata_area_initialize(
     libvslvm_metadata_area_t **metadata_area,
     libcerror_error_t **error );

int libvslvm_metadata_area_free(
     libvslvm_metadata_area_t **metadata_area,
     libcerror_error_t **error );

int libvslvm_metadata_area_read_data(
     libvslvm_metadata_area_t *metadata_area,
     const uint8_t *data,
     size_t data_size,
     off64_t file_offset,
     libcerror_error_t **error );

int libvslvm_metadata_area_read_file_io_handle(
     libvslvm_metadata_area_t *metadata_area,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_METADATA_AREA_H ) */

