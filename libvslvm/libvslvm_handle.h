/*
 * The internal handle functions
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

#if !defined( _LIBVSLVM_INTERNAL_HANDLE_H )
#define _LIBVSLVM_INTERNAL_HANDLE_H

#include <common.h>
#include <types.h>

#include "libvslvm_extern.h"
#include "libvslvm_io_handle.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_metadata.h"
#include "libvslvm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_internal_handle libvslvm_internal_handle_t;

struct libvslvm_internal_handle
{
	/* The IO handle
	 */
	libvslvm_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The physical volume file IO pool
	 */
	libbfio_pool_t *physical_volume_file_io_pool;

	/* Value to indicate if the file IO pool was created inside the library
	 */
	uint8_t physical_volume_file_io_pool_created_in_library;

	/* The access flags
	 */
	int access_flags;

	/* The maximum number of open handles in the pool
	 */
	int maximum_number_of_open_handles;

	/* The metadata
	 */
	libvslvm_metadata_t *metadata;
};

LIBVSLVM_EXTERN \
int libvslvm_handle_initialize(
     libvslvm_handle_t **handle,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_handle_free(
     libvslvm_handle_t **handle,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_handle_signal_abort(
     libvslvm_handle_t *handle,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_handle_open(
     libvslvm_handle_t *handle,
     char const *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBVSLVM_EXTERN \
int libvslvm_handle_open_wide(
     libvslvm_handle_t *handle,
     wchar_t const *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBVSLVM_EXTERN \
int libvslvm_handle_open_file_io_handle(
     libvslvm_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files(
     libvslvm_handle_t *handle,
     char * const filenames[],
     int number_of_filenames,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files_wide(
     libvslvm_handle_t *handle,
     wchar_t * const filenames[],
     int number_of_filenames,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files_file_io_pool(
     libvslvm_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );

int libvslvm_handle_open_physical_volume_file(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int physical_volume_index,
     const char *filename,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libvslvm_handle_open_physical_volume_file_wide(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int physical_volume_index,
     const wchar_t *filename,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

int libvslvm_handle_open_physical_volume_file_io_handle(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int physical_volume_index,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libvslvm_internal_handle_open_read_data_area_table(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_handle_close(
     libvslvm_handle_t *handle,
     libcerror_error_t **error );

int libvslvm_internal_handle_open_read(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_handle_get_volume_group(
     libvslvm_handle_t *handle,
     libvslvm_volume_group_t **volume_group,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_INTERNAL_HANDLE_H ) */

