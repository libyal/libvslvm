/*
 * Stripe functions
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
#include "libvslvm_stripe.h"
#include "libvslvm_types.h"

/* Creates a stripe
 * Make sure the value stripe is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_stripe_initialize(
     libvslvm_stripe_t **stripe,
     libcerror_error_t **error )
{
	libvslvm_internal_stripe_t *internal_stripe = NULL;
	static char *function                       = "libvslvm_stripe_initialize";

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
	internal_stripe = memory_allocate_structure(
	                   libvslvm_internal_stripe_t );

	if( internal_stripe == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create stripe.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_stripe,
	     0,
	     sizeof( libvslvm_internal_stripe_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear stripe.",
		 function );

		goto on_error;
	}
	*stripe = (libvslvm_stripe_t *) internal_stripe;

	return( 1 );

on_error:
	if( internal_stripe != NULL )
	{
		memory_free(
		 internal_stripe );
	}
	return( -1 );
}

/* Frees a stripe
 * Returns 1 if successful or -1 on error
 */
int libvslvm_stripe_free(
     libvslvm_stripe_t **stripe,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_stripe_free";

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
		*stripe = NULL;
	}
	return( 1 );
}

/* Frees a stripe
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_stripe_free(
     libvslvm_internal_stripe_t **internal_stripe,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_internal_stripe_free";

	if( internal_stripe == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stripe.",
		 function );

		return( -1 );
	}
	if( *internal_stripe != NULL )
	{
		if( ( *internal_stripe )->physical_volume_name != NULL )
		{
			memory_free(
			 ( *internal_stripe )->physical_volume_name );
		}
		memory_free(
		 *internal_stripe );

		*internal_stripe = NULL;
	}
	return( 1 );
}

/* Retrieves the size of the ASCII formatted physical volume name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_stripe_get_physical_volume_name_size(
     libvslvm_stripe_t *stripe,
     size_t *physical_volume_name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_stripe_t *internal_stripe = NULL;
	static char *function                       = "libvslvm_stripe_get_physical_volume_name_size";

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
	internal_stripe = (libvslvm_internal_stripe_t *) stripe;

	if( physical_volume_name_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume name size.",
		 function );

		return( -1 );
	}
	*physical_volume_name_size = internal_stripe->physical_volume_name_size;

	return( 1 );
}

/* Retrieves the ASCII formatted physical volume name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_stripe_get_physical_volume_name(
     libvslvm_stripe_t *stripe,
     char *physical_volume_name,
     size_t physical_volume_name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_stripe_t *internal_stripe = NULL;
	static char *function                       = "libvslvm_stripe_get_physical_volume_name";

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
	internal_stripe = (libvslvm_internal_stripe_t *) stripe;

	if( physical_volume_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume name.",
		 function );

		return( -1 );
	}
	if( physical_volume_name_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid physical volume name size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( physical_volume_name_size < internal_stripe->physical_volume_name_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid physical volume name size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     physical_volume_name,
	     internal_stripe->physical_volume_name,
	     internal_stripe->physical_volume_name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy physical volume name.",
		 function );

		return( -1 );
	}
	physical_volume_name[ internal_stripe->physical_volume_name_size - 1 ] = 0;

	return( 1 );
}

/* Sets the physical volume name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_stripe_set_physical_volume_name(
     libvslvm_internal_stripe_t *internal_stripe,
     const char *physical_volume_name,
     size_t physical_volume_name_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_internal_stripe_set_physical_volume_name";

	if( internal_stripe == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stripe.",
		 function );

		return( -1 );
	}
	if( internal_stripe->physical_volume_name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stripe - physical volume name value already set.",
		 function );

		return( -1 );
	}
	if( physical_volume_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume name.",
		 function );

		return( -1 );
	}
	if( ( physical_volume_name_size == 0 )
	 || ( physical_volume_name_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid physical volume name size value out of bounds.",
		 function );

		return( -1 );
	}
	internal_stripe->physical_volume_name = (char *) memory_allocate(
	                                                  sizeof( char ) * physical_volume_name_size );

	if( internal_stripe->physical_volume_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create physical volume name.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     internal_stripe->physical_volume_name,
	     physical_volume_name,
	     physical_volume_name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy physical volume name.",
		 function );

		goto on_error;
	}
	internal_stripe->physical_volume_name[ physical_volume_name_size - 1 ] = 0;

	internal_stripe->physical_volume_name_size = physical_volume_name_size;

	return( 1 );

on_error:
	if( internal_stripe->physical_volume_name != NULL )
	{
		memory_free(
		 internal_stripe->physical_volume_name );

		internal_stripe->physical_volume_name = NULL;
	}
	internal_stripe->physical_volume_name_size = 0;

	return( -1 );
}

/* Retrieves the data area offset
 * Returns 1 if successful or -1 on error
 */
int libvslvm_stripe_get_data_area_offset(
     libvslvm_stripe_t *stripe,
     off64_t *data_area_offset,
     libcerror_error_t **error )
{
	libvslvm_internal_stripe_t *internal_stripe = NULL;
	static char *function                       = "libvslvm_stripe_get_data_area_offset";

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
	internal_stripe = (libvslvm_internal_stripe_t *) stripe;

	if( data_area_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data area offset.",
		 function );

		return( -1 );
	}
	*data_area_offset = internal_stripe->data_area_offset;

	return( 1 );
}

/* Sets the data area offset
 * Returns 1 if successful or -1 on error
 */
int libvslvm_stripe_set_data_area_offset(
     libvslvm_stripe_t *stripe,
     off64_t data_area_offset,
     libcerror_error_t **error )
{
	libvslvm_internal_stripe_t *internal_stripe = NULL;
	static char *function                       = "libvslvm_stripe_set_data_area_offset";

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
	internal_stripe = (libvslvm_internal_stripe_t *) stripe;

	internal_stripe->data_area_offset = data_area_offset;

	return( 1 );
}

