/*
 * Physical volume functions
 *
 * Copyright (c) 2014, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libvslvm_libcerror.h"
#include "libvslvm_physical_volume.h"
#include "libvslvm_types.h"

/* Creates a physical volume
 * Make sure the value physical_volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_initialize(
     libvslvm_physical_volume_t **physical_volume,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_initialize";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	if( *physical_volume != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid physical volume value already set.",
		 function );

		return( -1 );
	}
	internal_physical_volume = memory_allocate_structure(
	                            libvslvm_internal_physical_volume_t );

	if( internal_physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create physical volume.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_physical_volume,
	     0,
	     sizeof( libvslvm_internal_physical_volume_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear physical volume.",
		 function );

		goto on_error;
	}
	*physical_volume= (libvslvm_physical_volume_t *) internal_physical_volume;

	return( 1 );

on_error:
	if( internal_physical_volume != NULL )
	{
		memory_free(
		 internal_physical_volume );
	}
	return( -1 );
}

/* Frees a physical volume
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_free(
     libvslvm_physical_volume_t **physical_volume,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_physical_volume_free";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	if( *physical_volume != NULL )
	{
		*physical_volume = NULL;
	}
	return( 1 );
}

/* Frees a physical volume
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_physical_volume_free(
     libvslvm_internal_physical_volume_t **internal_physical_volume,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_internal_physical_volume_free";

	if( internal_physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	if( *internal_physical_volume != NULL )
	{
		if( ( *internal_physical_volume )->name != NULL )
		{
			memory_free(
			 ( *internal_physical_volume )->name );
		}
		if( ( *internal_physical_volume )->device_path != NULL )
		{
			memory_free(
			 ( *internal_physical_volume )->device_path );
		}
		memory_free(
		 *internal_physical_volume );

		*internal_physical_volume = NULL;
	}
	return( 1 );
}

/* Retrieves the size of the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_name_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_name_size";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

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
	*name_size = internal_physical_volume->name_size;

	return( 1 );
}

/* Retrieves the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_name(
     libvslvm_physical_volume_t *physical_volume,
     char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_set_name";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

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
	if( name_size < internal_physical_volume->name_size )
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
	     internal_physical_volume->name,
	     internal_physical_volume->name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		return( -1 );
	}
	name[ internal_physical_volume->name_size - 1 ] = 0;

	return( 1 );
}

/* Sets the name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_set_name(
     libvslvm_physical_volume_t *physical_volume,
     const char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_set_name";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

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
		 "%s: name size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_physical_volume->name != NULL )
	{
		memory_free(
		 internal_physical_volume->name );

		internal_physical_volume->name      = NULL;
		internal_physical_volume->name_size = 0;
	}
	internal_physical_volume->name = (char *) memory_allocate(
	                                           sizeof( char ) * name_size );

	if( internal_physical_volume->name == NULL )
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
	     internal_physical_volume->name,
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
	internal_physical_volume->name[ name_size - 1 ] = 0;

	internal_physical_volume->name_size = name_size;

	return( 1 );

on_error:
	if( internal_physical_volume->name != NULL )
	{
		memory_free(
		 internal_physical_volume->name );

		internal_physical_volume->name = NULL;
	}
	internal_physical_volume->name_size = 0;

	return( -1 );
}

/* Retrieves the size of the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_identifier_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *identifier_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_identifier_size";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

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
	if( internal_physical_volume->identifier[ 0 ] == 0 )
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
int libvslvm_physical_volume_get_identifier(
     libvslvm_physical_volume_t *physical_volume,
     char *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_set_identifier";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

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
	     internal_physical_volume->identifier,
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
int libvslvm_physical_volume_set_identifier(
     libvslvm_physical_volume_t *physical_volume,
     const char *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_set_identifier";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

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
	     internal_physical_volume->identifier,
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
	internal_physical_volume->identifier[ 38 ] = 0;

	return( 1 );
}

/* Retrieves the size of the ASCII formatted device path
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_device_path_size(
     libvslvm_physical_volume_t *physical_volume,
     size_t *device_path_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_device_path_size";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

	if( device_path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid device path size.",
		 function );

		return( -1 );
	}
	*device_path_size = internal_physical_volume->device_path_size;

	return( 1 );
}

/* Retrieves the ASCII formatted device path
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_device_path(
     libvslvm_physical_volume_t *physical_volume,
     char *device_path,
     size_t device_path_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_set_device_path";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

	if( device_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid device_path.",
		 function );

		return( -1 );
	}
	if( device_path_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid device path size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( device_path_size < internal_physical_volume->device_path_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid device path size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     device_path,
	     internal_physical_volume->device_path,
	     internal_physical_volume->device_path_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy device path.",
		 function );

		return( -1 );
	}
	device_path[ internal_physical_volume->device_path_size - 1 ] = 0;

	return( 1 );
}

/* Sets the device path
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_set_device_path(
     libvslvm_physical_volume_t *physical_volume,
     const char *device_path,
     size_t device_path_size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_set_device_path";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

	if( device_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid device path.",
		 function );

		return( -1 );
	}
	if( device_path_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: device path size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_physical_volume->device_path != NULL )
	{
		memory_free(
		 internal_physical_volume->device_path );

		internal_physical_volume->device_path      = NULL;
		internal_physical_volume->device_path_size = 0;
	}
	internal_physical_volume->device_path = (char *) memory_allocate(
	                                                  sizeof( char ) * device_path_size );

	if( internal_physical_volume->device_path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create device path.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     internal_physical_volume->device_path,
	     device_path,
	     device_path_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy device path.",
		 function );

		goto on_error;
	}
	internal_physical_volume->device_path[ device_path_size - 1 ] = 0;

	internal_physical_volume->device_path_size = device_path_size;

	return( 1 );

on_error:
	if( internal_physical_volume->device_path != NULL )
	{
		memory_free(
		 internal_physical_volume->device_path );

		internal_physical_volume->device_path = NULL;
	}
	internal_physical_volume->device_path_size = 0;

	return( -1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_size(
     libvslvm_physical_volume_t *physical_volume,
     size64_t *size,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_size";

	if( physical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume.",
		 function );

		return( -1 );
	}
	internal_physical_volume = (libvslvm_internal_physical_volume_t *) physical_volume;

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
	*size = internal_physical_volume->size;

	return( 1 );
}

