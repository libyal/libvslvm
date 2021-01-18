/*
 * Raw location descriptor functions
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

#if !defined( _LIBVSLVM_RAW_LOCATION_DESCRIPTOR_H )
#define _LIBVSLVM_RAW_LOCATION_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libvslvm_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_raw_location_descriptor libvslvm_raw_location_descriptor_t;

struct libvslvm_raw_location_descriptor
{
	/* The offset
	 */
	uint64_t offset;

	/* The size
	 */
	uint64_t size;

	/* The checksum
	 */
	uint32_t checksum;

	/* The flags
	 */
	uint32_t flags;
};

int libvslvm_raw_location_descriptor_initialize(
     libvslvm_raw_location_descriptor_t **raw_location_descriptor,
     libcerror_error_t **error );

int libvslvm_raw_location_descriptor_free(
     libvslvm_raw_location_descriptor_t **raw_location_descriptor,
     libcerror_error_t **error );

int libvslvm_raw_location_descriptor_get(
     libvslvm_raw_location_descriptor_t *raw_location_descriptor,
     off64_t *offset,
     size64_t *size,
     uint32_t *checksum,
     uint32_t *flags,
     libcerror_error_t **error );

int libvslvm_raw_location_descriptor_set(
     libvslvm_raw_location_descriptor_t *raw_location_descriptor,
     off64_t offset,
     size64_t size,
     uint32_t checksum,
     uint32_t flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_RAW_LOCATION_DESCRIPTOR_H ) */

