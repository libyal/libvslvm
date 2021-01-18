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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_segment.h"
#include "libvslvm_types.h"
#include "libvslvm_stripe.h"

/* Creates a segment
 * Make sure the value segment is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_segment_initialize(
     libvslvm_segment_t **segment,
     libcerror_error_t **error )
{
	libvslvm_internal_segment_t *internal_segment = NULL;
	static char *function                         = "libvslvm_segment_initialize";

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
	internal_segment = memory_allocate_structure(
	                    libvslvm_internal_segment_t );

	if( internal_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create segment.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_segment,
	     0,
	     sizeof( libvslvm_internal_segment_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear segment.",
		 function );

		memory_free(
		 internal_segment );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_segment->stripes_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create stripes array.",
		 function );

		goto on_error;
	}
	*segment = (libvslvm_segment_t *) internal_segment;

	return( 1 );

on_error:
	if( internal_segment != NULL )
	{
		memory_free(
		 internal_segment );
	}
	return( -1 );
}

/* Frees a segment
 * Returns 1 if successful or -1 on error
 */
int libvslvm_segment_free(
     libvslvm_segment_t **segment,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_segment_free";

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
		*segment = NULL;
	}
	return( 1 );
}

/* Frees a segment
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_segment_free(
     libvslvm_internal_segment_t **internal_segment,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_internal_segment_free";
	int result            = 1;

	if( internal_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment.",
		 function );

		return( -1 );
	}
	if( *internal_segment != NULL )
	{
		if( ( *internal_segment )->name != NULL )
		{
			memory_free(
			 ( *internal_segment )->name );
		}
		if( libcdata_array_free(
		     &( ( *internal_segment )->stripes_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_internal_stripe_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free stripes array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_segment );

		*internal_segment = NULL;
	}
	return( result );
}

/* Sets the name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_segment_set_name(
     libvslvm_internal_segment_t *internal_segment,
     const char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_internal_segment_set_name";

	if( internal_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment.",
		 function );

		return( -1 );
	}
	if( internal_segment->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid segment - name value already set.",
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
	internal_segment->name = (char *) memory_allocate(
	                                   sizeof( char ) * name_size );

	if( internal_segment->name == NULL )
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
	     internal_segment->name,
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
	internal_segment->name[ name_size - 1 ] = 0;

	internal_segment->name_size = name_size;

	return( 1 );

on_error:
	if( internal_segment->name != NULL )
	{
		memory_free(
		 internal_segment->name );

		internal_segment->name = NULL;
	}
	internal_segment->name_size = 0;

	return( -1 );
}

/* Retrieves the range
 * Returns 1 if successful or -1 on error
 */
int libvslvm_segment_get_range(
     libvslvm_segment_t *segment,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error )
{
	libvslvm_internal_segment_t *internal_segment = NULL;
	static char *function                         = "libvslvm_segment_get_range";

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
	internal_segment = (libvslvm_internal_segment_t *) segment;

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
	*offset = internal_segment->offset;
	*size   = internal_segment->size;

	return( 1 );
}

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
int libvslvm_segment_get_offset(
     libvslvm_segment_t *segment,
     off64_t *offset,
     libcerror_error_t **error )
{
	libvslvm_internal_segment_t *internal_segment = NULL;
	static char *function                         = "libvslvm_segment_get_offset";

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
	internal_segment = (libvslvm_internal_segment_t *) segment;

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
	*offset = internal_segment->offset;

	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libvslvm_segment_get_size(
     libvslvm_segment_t *segment,
     size64_t *size,
     libcerror_error_t **error )
{
	libvslvm_internal_segment_t *internal_segment = NULL;
	static char *function                         = "libvslvm_segment_get_size";

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
	internal_segment = (libvslvm_internal_segment_t *) segment;

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
	*size = internal_segment->size;

	return( 1 );
}

/* Retrieves the number of stripes
 * Returns 1 if successful or -1 on error
 */
int libvslvm_segment_get_number_of_stripes(
     libvslvm_segment_t *segment,
     int *number_of_stripes,
     libcerror_error_t **error )
{
	libvslvm_internal_segment_t *internal_segment = NULL;
	static char *function                         = "libvslvm_segment_get_number_of_stripes";

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
	internal_segment = (libvslvm_internal_segment_t *) segment;

	if( libcdata_array_get_number_of_entries(
	     internal_segment->stripes_array,
	     number_of_stripes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from stripes array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific stripe
 * Returns 1 if successful or -1 on error
 */
int libvslvm_segment_get_stripe(
     libvslvm_segment_t *segment,
     int stripe_index,
     libvslvm_stripe_t **stripe,
     libcerror_error_t **error )
{
	libvslvm_internal_segment_t *internal_segment = NULL;
	static char *function                         = "libvslvm_segment_get_stripe";

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
	internal_segment = (libvslvm_internal_segment_t *) segment;

	if( stripe == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stripe.",
		 function );

		return( -1 );
	}
	if( *stripe != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stripe value already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_segment->stripes_array,
	     stripe_index,
	     (intptr_t **) stripe,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stripe: %d.",
		 function,
		 stripe_index );

		return( -1 );
	}
	return( 1 );
}

/* Appends a stripe
 * Returns 1 if successful or -1 on error
 */
int libvslvm_segment_append_stripe(
     libvslvm_segment_t *segment,
     libvslvm_stripe_t *stripe,
     libcerror_error_t **error )
{
	libvslvm_internal_segment_t *internal_segment = NULL;
	static char *function                         = "libvslvm_segment_append_stripe";
	int entry_index                               = 0;

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
	internal_segment = (libvslvm_internal_segment_t *) segment;

	if( stripe == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stripe.",
		 function );

		return( -1 );
	}
	if( libcdata_array_append_entry(
	     internal_segment->stripes_array,
	     &entry_index,
	     (intptr_t *) stripe,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append stripe to segment.",
		 function );

		return( -1 );
	}
	return( 1 );
}

