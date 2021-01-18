/*
 * Info handle
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

#if !defined( _INFO_HANDLE_H )
#define _INFO_HANDLE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "vslvmtools_libbfio.h"
#include "vslvmtools_libcerror.h"
#include "vslvmtools_libvslvm.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct info_handle info_handle_t;

struct info_handle
{
	/* The volume offset
	 */
	off64_t volume_offset;

	/* The libbfio physical volume file IO pool
	 */
	libbfio_pool_t *physical_volume_file_io_pool;

	/* The libvslvm input handle
	 */
	libvslvm_handle_t *input_handle;

	/* The notification output stream
	 */
	FILE *notify_stream;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int vslvmtools_system_string_copy_from_64_bit_in_decimal(
     const system_character_t *string,
     size_t string_size,
     uint64_t *value_64bit,
     libcerror_error_t **error );

int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_set_volume_offset(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error );

int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_volume_group_fprint(
     info_handle_t *info_handle,
     libvslvm_volume_group_t *volume_group,
     libcerror_error_t **error );

int info_handle_physical_volume_fprint(
     info_handle_t *info_handle,
     int physical_volume_index,
     libvslvm_physical_volume_t *physical_volume,
     libcerror_error_t **error );

int info_handle_logical_volume_fprint(
     info_handle_t *info_handle,
     int logical_volume_index,
     libvslvm_logical_volume_t *logical_volume,
     libcerror_error_t **error );

int info_handle_segment_fprint(
     info_handle_t *info_handle,
     int segment_index,
     libvslvm_segment_t *segment,
     libcerror_error_t **error );

int info_handle_stripe_fprint(
     info_handle_t *info_handle,
     int stripe_index,
     libvslvm_stripe_t *stripe,
     libcerror_error_t **error );

int info_handle_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _INFO_HANDLE_H ) */

