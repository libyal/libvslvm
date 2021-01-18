/*
 * Logical volume values functions
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

#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_logical_volume_values.h"
#include "libvslvm_segment.h"

/* Creates logical volume values
 * Make sure the value logical_volume_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_initialize(
     libvslvm_logical_volume_values_t **logical_volume_values,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_initialize";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( *logical_volume_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid logical volume values value already set.",
		 function );

		return( -1 );
	}
	*logical_volume_values = memory_allocate_structure(
	                          libvslvm_logical_volume_values_t );

	if( *logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create logical volume values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *logical_volume_values,
	     0,
	     sizeof( libvslvm_logical_volume_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear logical volume values.",
		 function );

		memory_free(
		 *logical_volume_values );

		*logical_volume_values = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *logical_volume_values )->segments_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create segments array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *logical_volume_values != NULL )
	{
		memory_free(
		 *logical_volume_values );

		*logical_volume_values = NULL;
	}
	return( -1 );
}

/* Frees logical volume values
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_free(
     libvslvm_logical_volume_values_t **logical_volume_values,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_free";
	int result            = 1;

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( *logical_volume_values != NULL )
	{
		if( ( *logical_volume_values )->name != NULL )
		{
			memory_free(
			 ( *logical_volume_values )->name );
		}
		if( libcdata_array_free(
		     &( ( *logical_volume_values )->segments_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_internal_segment_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free segments array.",
			 function );

			result = -1;
		}
		memory_free(
		 *logical_volume_values );

		*logical_volume_values = NULL;
	}
	return( result );
}

/* Retrieves the size of the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_get_name_size(
     libvslvm_logical_volume_values_t *logical_volume_values,
     size_t *name_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_get_name_size";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( name_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name size.",
		 function );

		return( -1 );
	}
	*name_size = logical_volume_values->name_size;

	return( 1 );
}

/* Retrieves the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_get_name(
     libvslvm_logical_volume_values_t *logical_volume_values,
     char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_set_name";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( name_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( name_size < logical_volume_values->name_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid name size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     name,
	     logical_volume_values->name,
	     logical_volume_values->name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		return( -1 );
	}
	name[ logical_volume_values->name_size - 1 ] = 0;

	return( 1 );
}

/* Sets the name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_set_name(
     libvslvm_logical_volume_values_t *logical_volume_values,
     const char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_set_name";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( logical_volume_values->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid logical volume values - name value already set.",
		 function );

		return( -1 );
	}
	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( ( name_size == 0 )
	 || ( name_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid name size value out of bounds.",
		 function );

		return( -1 );
	}
	logical_volume_values->name = (char *) memory_allocate(
	                                        sizeof( char ) * name_size );

	if( logical_volume_values->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     logical_volume_values->name,
	     name,
	     name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		goto on_error;
	}
	logical_volume_values->name[ name_size - 1 ] = 0;

	logical_volume_values->name_size = name_size;

	return( 1 );

on_error:
	if( logical_volume_values->name != NULL )
	{
		memory_free(
		 logical_volume_values->name );

		logical_volume_values->name = NULL;
	}
	logical_volume_values->name_size = 0;

	return( -1 );
}

/* Retrieves the size of the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_get_identifier_size(
     libvslvm_logical_volume_values_t *logical_volume_values,
     size_t *identifier_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_get_identifier_size";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( identifier_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier size.",
		 function );

		return( -1 );
	}
	if( logical_volume_values->identifier[ 0 ] == 0 )
	{
		*identifier_size = 0;
	}
	else
	{
		*identifier_size = 39;
	}
	return( 1 );
}

/* Retrieves the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_get_identifier(
     libvslvm_logical_volume_values_t *logical_volume_values,
     char *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_set_identifier";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	if( identifier_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid identifier size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( identifier_size < 39 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid identifier size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     identifier,
	     logical_volume_values->identifier,
	     39 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	identifier[ 38 ] = 0;

	return( 1 );
}

/* Sets the identifier
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_set_identifier(
     libvslvm_logical_volume_values_t *logical_volume_values,
     const char *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_set_identifier";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	if( identifier_size != 39 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: identifier size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     logical_volume_values->identifier,
	     identifier,
	     39 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	logical_volume_values->identifier[ 38 ] = 0;

	return( 1 );
}

/* Retrieves the number of segments
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_get_number_of_segments(
     libvslvm_logical_volume_values_t *logical_volume_values,
     int *number_of_segments,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_get_number_of_segments";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     logical_volume_values->segments_array,
	     number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from segments array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific segment
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_get_segment(
     libvslvm_logical_volume_values_t *logical_volume_values,
     int segment_index,
     libvslvm_segment_t **segment,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_get_segment";

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment.",
		 function );

		return( -1 );
	}
	if( *segment != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid segment value already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     logical_volume_values->segments_array,
	     segment_index,
	     (intptr_t **) segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve segment: %d.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( 1 );
}

/* Appends a segment
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_values_append_segment(
     libvslvm_logical_volume_values_t *logical_volume_values,
     libvslvm_segment_t *segment,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_logical_volume_values_append_segment";
	int entry_index       = 0;

	if( logical_volume_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume values.",
		 function );

		return( -1 );
	}
	if( segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment.",
		 function );

		return( -1 );
	}
	if( libcdata_array_append_entry(
	     logical_volume_values->segments_array,
	     &entry_index,
	     (intptr_t *) segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append segment to logical volume values.",
		 function );

		return( -1 );
	}
	return( 1 );
}
