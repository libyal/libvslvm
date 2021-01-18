/*
 * Logical volume functions values
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

#if !defined( _LIBVSLVM_LOGICAL_VOLUME_VALUES_H )
#define _LIBVSLVM_LOGICAL_VOLUME_VALUES_H

#include <common.h>
#include <types.h>

#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_logical_volume_values libvslvm_logical_volume_values_t;

struct libvslvm_logical_volume_values
{
	/* The name
	 */
	char *name;

	/* The name size
	 */
	size_t name_size;

	/* The identfier
	 */
	char identifier[ 39 ];

	/* The segment values array
	 */
	libcdata_array_t *segments_array;

	/* The segments (file data) stream
	 */
	libfdata_stream_t *segments_stream;
};

int libvslvm_logical_volume_values_initialize(
     libvslvm_logical_volume_values_t **logical_volume_values,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_free(
     libvslvm_logical_volume_values_t **logical_volume_values,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_get_name_size(
     libvslvm_logical_volume_values_t *logical_volume_values,
     size_t *name_size,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_get_name(
     libvslvm_logical_volume_values_t *logical_volume_values,
     char *name,
     size_t name_size,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_set_name(
     libvslvm_logical_volume_values_t *logical_volume_values,
     const char *name,
     size_t name_size,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_get_identifier_size(
     libvslvm_logical_volume_values_t *logical_volume_values,
     size_t *identifier_size,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_get_identifier(
     libvslvm_logical_volume_values_t *logical_volume_values,
     char *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_set_identifier(
     libvslvm_logical_volume_values_t *logical_volume_values,
     const char *identifier,
     size_t identifier_size,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_get_number_of_segments(
     libvslvm_logical_volume_values_t *logical_volume_values,
     int *number_of_segments,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_get_segment(
     libvslvm_logical_volume_values_t *logical_volume_values,
     int segment_index,
     libvslvm_segment_t **segment,
     libcerror_error_t **error );

int libvslvm_logical_volume_values_append_segment(
     libvslvm_logical_volume_values_t *logical_volume_values,
     libvslvm_segment_t *segment,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_LOGICAL_VOLUME_VALUES_H ) */

