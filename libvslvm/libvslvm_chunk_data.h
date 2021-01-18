/*
 * Chunk data functions
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

#if !defined( _LIBVSLVM_CHUNK_DATA_H )
#define _LIBVSLVM_CHUNK_DATA_H

#include <common.h>
#include <types.h>

#include "libvslvm_libbfio.h"
#include "libvslvm_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_chunk_data libvslvm_chunk_data_t;

struct libvslvm_chunk_data
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int libvslvm_chunk_data_initialize(
     libvslvm_chunk_data_t **chunk_data,
     size_t data_size,
     libcerror_error_t **error );

int libvslvm_chunk_data_free(
     libvslvm_chunk_data_t **chunk_data,
     libcerror_error_t **error );

int libvslvm_chunk_data_read_file_io_pool(
     libvslvm_chunk_data_t *chunk_data,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     off64_t cluster_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_CHUNK_DATA_H ) */

