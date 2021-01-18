/*
 * Data area descriptor functions
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

#include "libvslvm_data_area_descriptor.h"
#include "libvslvm_libcerror.h"

/* Creates a data area descriptor
 * Make sure the value data_area_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_data_area_descriptor_initialize(
     libvslvm_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_data_area_descriptor_initialize";

	if( data_area_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data area descriptor.",
		 function );

		return( -1 );
	}
	if( *data_area_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data area descriptor value already set.",
		 function );

		return( -1 );
	}
	*data_area_descriptor = memory_allocate_structure(
	                         libvslvm_data_area_descriptor_t );

	if( *data_area_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data area descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_area_descriptor,
	     0,
	     sizeof( libvslvm_data_area_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data area descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *data_area_descriptor != NULL )
	{
		memory_free(
		 *data_area_descriptor );

		*data_area_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a data area descriptor
 * Returns 1 if successful or -1 on error
 */
int libvslvm_data_area_descriptor_free(
     libvslvm_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_data_area_descriptor_free";

	if( data_area_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data area descriptor.",
		 function );

		return( -1 );
	}
	if( *data_area_descriptor != NULL )
	{
		memory_free(
		 *data_area_descriptor );

		*data_area_descriptor = NULL;
	}
	return( 1 );
}

/* Retrieves a data area descriptor
 * Returns 1 if successful or -1 on error
 */
int libvslvm_data_area_descriptor_get(
     libvslvm_data_area_descriptor_t *data_area_descriptor,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_data_area_descriptor_get";

	if( data_area_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data area descriptor.",
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
	*offset = data_area_descriptor->offset;
	*size   = data_area_descriptor->size;

	return( 1 );
}

/* Sets a data area descriptor
 * Returns 1 if successful or -1 on error
 */
int libvslvm_data_area_descriptor_set(
     libvslvm_data_area_descriptor_t *data_area_descriptor,
     off64_t offset,
     size64_t size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_data_area_descriptor_set";

	if( data_area_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data area descriptor.",
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
	data_area_descriptor->offset = offset;
	data_area_descriptor->size   = size;

	return( 1 );
}

