/*
 * Segment functions
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

#if !defined( _LIBVSLVM_SEGMENT_H )
#define _LIBVSLVM_SEGMENT_H

#include <common.h>
#include <types.h>

#include "libvslvm_extern.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_internal_segment libvslvm_internal_segment_t;

struct libvslvm_internal_segment
{
	/* The name
	 */
	char *name;

	/* The name size
	 */
	size_t name_size;

	/* The stripes array
	 */
	libcdata_array_t *stripes_array;

	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;
};

int libvslvm_segment_initialize(
     libvslvm_segment_t **segment,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_free(
     libvslvm_segment_t **segment,
     libcerror_error_t **error );

int libvslvm_internal_segment_free(
     libvslvm_internal_segment_t **internal_segment,
     libcerror_error_t **error );

int libvslvm_internal_segment_set_name(
     libvslvm_internal_segment_t *internal_segment,
     const char *name,
     size_t name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_range(
     libvslvm_segment_t *segment,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_offset(
     libvslvm_segment_t *segment,
     off64_t *offset,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_size(
     libvslvm_segment_t *segment,
     size64_t *size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_number_of_stripes(
     libvslvm_segment_t *segment,
     int *number_of_stripes,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_stripe(
     libvslvm_segment_t *segment,
     int stripe_index,
     libvslvm_stripe_t **stripe,
     libcerror_error_t **error );

int libvslvm_segment_append_stripe(
     libvslvm_segment_t *segment,
     libvslvm_stripe_t *stripe,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_SEGMENT_H ) */

