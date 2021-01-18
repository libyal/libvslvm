/*
 * Logical volume functions
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

#if !defined( _LIBVSLVM_INTERNAL_LOGICAL_VOLUME_H )
#define _LIBVSLVM_INTERNAL_LOGICAL_VOLUME_H

#include <common.h>
#include <types.h>

#include "libvslvm_extern.h"
#include "libvslvm_io_handle.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcthreads.h"
#include "libvslvm_libfcache.h"
#include "libvslvm_libfdata.h"
#include "libvslvm_logical_volume_values.h"
#include "libvslvm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_internal_logical_volume libvslvm_internal_logical_volume_t;

struct libvslvm_internal_logical_volume
{
	/* The logical volume values
	 */
	libvslvm_logical_volume_values_t *logical_volume_values;

	/* The IO handle
	 */
	libvslvm_io_handle_t *io_handle;

	/* The physical volume file IO pool
	 */
	libbfio_pool_t *physical_volume_file_io_pool;

	/* The chunks vector
	 */
	libfdata_vector_t *chunks_vector;

	/* The chunks cache
	 */
	libfcache_cache_t *chunks_cache;

	/* The current offset
	 */
	off64_t current_offset;

	/* The size
	 */
	size64_t size;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libvslvm_logical_volume_initialize(
     libvslvm_logical_volume_t **logical_volume,
     libvslvm_io_handle_t *io_handle,
     libvslvm_volume_group_t *volume_group,
     libbfio_pool_t *physical_volume_file_io_pool,
     libvslvm_logical_volume_values_t *logical_volume_values,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_free(
     libvslvm_logical_volume_t **logical_volume,
     libcerror_error_t **error );

ssize_t libvslvm_internal_logical_volume_read_buffer_from_file_io_pool(
         libvslvm_internal_logical_volume_t *internal_logical_volume,
         libbfio_pool_t *physical_volume_file_io_pool,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSLVM_EXTERN \
ssize_t libvslvm_logical_volume_read_buffer(
         libvslvm_logical_volume_t *logical_volume,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBVSLVM_EXTERN \
ssize_t libvslvm_logical_volume_read_buffer_at_offset(
         libvslvm_logical_volume_t *logical_volume,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

off64_t libvslvm_internal_logical_volume_seek_offset(
         libvslvm_internal_logical_volume_t *internal_logical_volume,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVSLVM_EXTERN \
off64_t libvslvm_logical_volume_seek_offset(
         libvslvm_logical_volume_t *logical_volume,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_offset(
     libvslvm_logical_volume_t *logical_volume,
     off64_t *offset,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_size(
     libvslvm_logical_volume_t *logical_volume,
     size64_t *size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_name_size(
     libvslvm_logical_volume_t *logical_volume,
     size_t *name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_name(
     libvslvm_logical_volume_t *logical_volume,
     char *name,
     size_t name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_identifier_size(
     libvslvm_logical_volume_t *logical_volume,
     size_t *identifier_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_identifier(
     libvslvm_logical_volume_t *logical_volume,
     char *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_number_of_segments(
     libvslvm_logical_volume_t *logical_volume,
     int *number_of_segments,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_logical_volume_get_segment(
     libvslvm_logical_volume_t *logical_volume,
     int segment_index,
     libvslvm_segment_t **segment,
     libcerror_error_t **error );

int libvslvm_logical_volume_read_chunk_data(
     intptr_t *data_handle,
     libbfio_pool_t *file_io_pool,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_INTERNAL_LOGICAL_VOLUME_H ) */

