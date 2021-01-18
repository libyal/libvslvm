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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvslvm_libcerror.h"
#include "libvslvm_raw_location_descriptor.h"

/* Creates a raw location descriptor
 * Make sure the value raw_location_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raw_location_descriptor_initialize(
     libvslvm_raw_location_descriptor_t **raw_location_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_raw_location_descriptor_initialize";

	if( raw_location_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid raw location descriptor.",
		 function );

		return( -1 );
	}
	if( *raw_location_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid raw location descriptor value already set.",
		 function );

		return( -1 );
	}
	*raw_location_descriptor = memory_allocate_structure(
	                            libvslvm_raw_location_descriptor_t );

	if( *raw_location_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create raw location descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *raw_location_descriptor,
	     0,
	     sizeof( libvslvm_raw_location_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear raw location descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *raw_location_descriptor != NULL )
	{
		memory_free(
		 *raw_location_descriptor );

		*raw_location_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a raw location descriptor
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raw_location_descriptor_free(
     libvslvm_raw_location_descriptor_t **raw_location_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_raw_location_descriptor_free";

	if( raw_location_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid raw location descriptor.",
		 function );

		return( -1 );
	}
	if( *raw_location_descriptor != NULL )
	{
		memory_free(
		 *raw_location_descriptor );

		*raw_location_descriptor = NULL;
	}
	return( 1 );
}

/* Retrieves a raw location descriptor
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raw_location_descriptor_get(
     libvslvm_raw_location_descriptor_t *raw_location_descriptor,
     off64_t *offset,
     size64_t *size,
     uint32_t *checksum,
     uint32_t *flags,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_raw_location_descriptor_get";

	if( raw_location_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid raw location descriptor.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	if( checksum == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid checksum.",
		 function );

		return( -1 );
	}
	if( flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid flags.",
		 function );

		return( -1 );
	}
	*offset   = raw_location_descriptor->offset;
	*size     = raw_location_descriptor->size;
	*checksum = raw_location_descriptor->checksum;
	*flags    = raw_location_descriptor->flags;

	return( 1 );
}

/* Sets a raw location descriptor
 * Returns 1 if successful or -1 on error
 */
int libvslvm_raw_location_descriptor_set(
     libvslvm_raw_location_descriptor_t *raw_location_descriptor,
     off64_t offset,
     size64_t size,
     uint32_t checksum,
     uint32_t flags,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_raw_location_descriptor_set";

	if( raw_location_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid raw location descriptor.",
		 function );

		return( -1 );
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid offset value less than zero.",
		 function );

		return( -1 );
	}
	if( size > (uint64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	raw_location_descriptor->offset   = offset;
	raw_location_descriptor->size     = size;
	raw_location_descriptor->checksum = checksum;
	raw_location_descriptor->flags    = flags;

	return( 1 );
}

