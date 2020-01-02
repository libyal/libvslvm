/*
 * Physical volume functions
 *
 * Copyright (C) 2014-2020, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvslvm_data_area_descriptor.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcnotify.h"
#include "libvslvm_physical_volume.h"
#include "libvslvm_types.h"
#include "libvslvm_unused.h"

#include "vslvm_physical_volume_label.h"

const char *vslvm_physical_volume_label_signature = "LABELONE";

const uint8_t vslvm_empty_data_area_descriptor[ 16 ] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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

		memory_free(
		 internal_physical_volume );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_physical_volume->data_area_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data area descripors array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_physical_volume->metadata_area_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create metadata area descripors array.",
		 function );

		goto on_error;
	}
	*physical_volume= (libvslvm_physical_volume_t *) internal_physical_volume;

	return( 1 );

on_error:
	if( internal_physical_volume != NULL )
	{
		if( internal_physical_volume->data_area_descriptors_array != NULL )
		{
			libcdata_array_free(
			 &( internal_physical_volume->data_area_descriptors_array ),
			 NULL,
			 NULL );
		}
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
	int result            = 1;

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
		if( libcdata_array_free(
		     &( ( *internal_physical_volume )->data_area_descriptors_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_data_area_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data area descriptors array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_physical_volume )->metadata_area_descriptors_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_data_area_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free metadata area descriptors array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_physical_volume );

		*internal_physical_volume = NULL;
	}
	return( result );
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
	static char *function                                         = "libvslvm_physical_volume_get_name";

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

/* Compares the name with that of the physical volume
 * Returns 1 if the name matches, 0 if not or -1 on error
 */
int libvslvm_physical_volume_compare_by_name(
     libvslvm_physical_volume_t *physical_volume,
     const char *name,
     size_t name_length,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_compare_by_name";

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
	if( name_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_physical_volume->name_size == ( name_length + 1 ) )
	 && ( memory_compare(
	       name,
	       internal_physical_volume->name,
	       internal_physical_volume->name_size ) == 0 ) )
	{
		return( 1 );
	}
	return( 0 );
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

/* Retrieves the number of data area descriptors
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_number_of_data_area_descriptors(
     libvslvm_physical_volume_t *physical_volume,
     int *number_of_data_area_descriptors,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_number_of_data_area_descriptors";

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

	if( libcdata_array_get_number_of_entries(
	     internal_physical_volume->data_area_descriptors_array,
	     number_of_data_area_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data area descriptors from array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific data area descriptor
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_data_area_descriptor(
     libvslvm_physical_volume_t *physical_volume,
     int data_area_descriptor_index,
     libvslvm_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_data_area_descriptor";

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

	if( libcdata_array_get_entry_by_index(
	     internal_physical_volume->data_area_descriptors_array,
	     data_area_descriptor_index,
	     (intptr_t **) data_area_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data area descriptor: %d.",
		 function,
		 data_area_descriptor_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data area descriptor for a specific offset
 * Returns 1 if successful, 0 if no such data area descriptor or -1 on error
 */
int libvslvm_physical_volume_get_data_area_descriptor_by_offset(
     libvslvm_physical_volume_t *physical_volume,
     uint64_t offset,
     libvslvm_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_data_area_descriptor_by_offset";
	int data_area_descriptor_index                                = 0;
	int number_of_data_area_descriptors                           = 0;

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
	if( libcdata_array_get_number_of_entries(
	     internal_physical_volume->data_area_descriptors_array,
	     &number_of_data_area_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data area descriptors from array.",
		 function );

		return( -1 );
	}
	for( data_area_descriptor_index = 0;
	     data_area_descriptor_index < number_of_data_area_descriptors;
	     data_area_descriptor_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_physical_volume->data_area_descriptors_array,
		     data_area_descriptor_index,
		     (intptr_t **) data_area_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data area descriptor: %d.",
			 function,
			 data_area_descriptor_index );

			return( -1 );
		}
		if( *data_area_descriptor == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing data area descriptor: %d.",
			 function,
			 data_area_descriptor_index );

			return( -1 );
		}
		if( ( *data_area_descriptor )->size == 0 )
		{
			return( 1 );
		}
		offset -= ( *data_area_descriptor )->size;
	}
	return( 0 );
}

/* Retrieves the number of metadata area descriptors
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_number_of_metadata_area_descriptors(
     libvslvm_physical_volume_t *physical_volume,
     int *number_of_data_area_descriptors,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_number_of_metadata_area_descriptors";

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

	if( libcdata_array_get_number_of_entries(
	     internal_physical_volume->metadata_area_descriptors_array,
	     number_of_data_area_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of metadata area descriptors from array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific metadata area descriptor
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_get_metadata_area_descriptor(
     libvslvm_physical_volume_t *physical_volume,
     int data_area_descriptor_index,
     libvslvm_data_area_descriptor_t **data_area_descriptor,
     libcerror_error_t **error )
{
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_get_metadata_area_descriptor";

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

	if( libcdata_array_get_entry_by_index(
	     internal_physical_volume->metadata_area_descriptors_array,
	     data_area_descriptor_index,
	     (intptr_t **) data_area_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve metadata area descriptor: %d.",
		 function,
		 data_area_descriptor_index );

		return( -1 );
	}
	return( 1 );
}

/* Reads a physical volume label
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libvslvm_physical_volume_read_label(
     libvslvm_physical_volume_t *physical_volume,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     off64_t file_offset,
     libcerror_error_t **error )
{
	vslvm_data_area_descriptor_t data_area_descriptor_data;
	vslvm_physical_volume_label_header_t physical_volume_label_header;
	vslvm_physical_volume_header_t physical_volume_header;

	libvslvm_data_area_descriptor_t *data_area_descriptor         = NULL;
	libvslvm_internal_physical_volume_t *internal_physical_volume = NULL;
	static char *function                                         = "libvslvm_physical_volume_read_label";
	ssize_t read_count                                            = 0;
	uint64_t offset                                               = 0;
	uint64_t size                                                 = 0;
	int entry_index                                               = 0;
	int result                                                    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                                          = 0;
	uint32_t value_32bit                                          = 0;
#endif

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

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading physical volume label at offset: %" PRIi64 "\n",
		 function,
		 file_offset );
	}
#endif
	if( libbfio_pool_seek_offset(
	     file_io_pool,
	     file_io_pool_entry,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	read_count = libbfio_pool_read_buffer(
	              file_io_pool,
	              file_io_pool_entry,
	              (uint8_t *) &physical_volume_label_header,
	              sizeof( vslvm_physical_volume_label_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( vslvm_physical_volume_label_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read physical volume label header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: physical volume label header data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &physical_volume_label_header,
		 sizeof( vslvm_physical_volume_label_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     physical_volume_label_header.signature,
	     vslvm_physical_volume_label_signature,
	     8 ) != 0 )
	{
		return( 0 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c%c%c%c%c\n",
		 function,
		 physical_volume_label_header.signature[ 0 ],
		 physical_volume_label_header.signature[ 1 ],
		 physical_volume_label_header.signature[ 2 ],
		 physical_volume_label_header.signature[ 3 ],
		 physical_volume_label_header.signature[ 4 ],
		 physical_volume_label_header.signature[ 5 ],
		 physical_volume_label_header.signature[ 6 ],
		 physical_volume_label_header.signature[ 7 ] );

		byte_stream_copy_to_uint64_little_endian(
		 physical_volume_label_header.sector_number,
		 value_64bit );
		libcnotify_printf(
		 "%s: sector number\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint32_little_endian(
		 physical_volume_label_header.checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 physical_volume_label_header.data_offset,
		 value_32bit );
		libcnotify_printf(
		 "%s: data offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: type indicator\t\t\t: %c%c%c%c%c%c%c%c\n",
		 function,
		 physical_volume_label_header.type_indicator[ 0 ],
		 physical_volume_label_header.type_indicator[ 1 ],
		 physical_volume_label_header.type_indicator[ 2 ],
		 physical_volume_label_header.type_indicator[ 3 ],
		 physical_volume_label_header.type_indicator[ 4 ],
		 physical_volume_label_header.type_indicator[ 5 ],
		 physical_volume_label_header.type_indicator[ 6 ],
		 physical_volume_label_header.type_indicator[ 7 ] );

		libcnotify_printf(
		 "\n" );
	}
#endif
/* TODO calculate checksum */

	read_count = libbfio_pool_read_buffer(
	              file_io_pool,
	              file_io_pool_entry,
	              (uint8_t *) &physical_volume_header,
	              sizeof( vslvm_physical_volume_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( vslvm_physical_volume_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read physical volume header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: physical volume header data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &physical_volume_header,
		 sizeof( vslvm_physical_volume_header_t ),
		 0 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: identifier\t\t\t\t: %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
		 function,
		 physical_volume_header.identifier[ 0 ],
		 physical_volume_header.identifier[ 1 ],
		 physical_volume_header.identifier[ 2 ],
		 physical_volume_header.identifier[ 3 ],
		 physical_volume_header.identifier[ 4 ],
		 physical_volume_header.identifier[ 5 ],
		 physical_volume_header.identifier[ 6 ],
		 physical_volume_header.identifier[ 7 ],
		 physical_volume_header.identifier[ 8 ],
		 physical_volume_header.identifier[ 9 ],
		 physical_volume_header.identifier[ 10 ],
		 physical_volume_header.identifier[ 11 ],
		 physical_volume_header.identifier[ 12 ],
		 physical_volume_header.identifier[ 13 ],
		 physical_volume_header.identifier[ 14 ],
		 physical_volume_header.identifier[ 15 ],
		 physical_volume_header.identifier[ 16 ],
		 physical_volume_header.identifier[ 17 ],
		 physical_volume_header.identifier[ 18 ],
		 physical_volume_header.identifier[ 19 ],
		 physical_volume_header.identifier[ 20 ],
		 physical_volume_header.identifier[ 21 ],
		 physical_volume_header.identifier[ 22 ],
		 physical_volume_header.identifier[ 23 ],
		 physical_volume_header.identifier[ 24 ],
		 physical_volume_header.identifier[ 25 ],
		 physical_volume_header.identifier[ 26 ],
		 physical_volume_header.identifier[ 27 ],
		 physical_volume_header.identifier[ 28 ],
		 physical_volume_header.identifier[ 29 ],
		 physical_volume_header.identifier[ 30 ],
		 physical_volume_header.identifier[ 31 ] );

		byte_stream_copy_to_uint64_little_endian(
		 physical_volume_header.volume_size,
		 value_64bit );
		libcnotify_printf(
		 "%s: volume size\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	do
	{
		read_count = libbfio_pool_read_buffer(
		              file_io_pool,
		              file_io_pool_entry,
		              (uint8_t *) &data_area_descriptor_data,
		              sizeof( vslvm_data_area_descriptor_t ),
		              error );

		if( read_count != (ssize_t) sizeof( vslvm_data_area_descriptor_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data area descriptor.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data area descriptor data:\n",
			 function );
			libcnotify_print_data(
			 (uint8_t *) &data_area_descriptor_data,
			 sizeof( vslvm_data_area_descriptor_t ),
			 0 );
		}
#endif
		result = memory_compare(
		          (uint8_t *) &data_area_descriptor_data,
		          vslvm_empty_data_area_descriptor,
		          sizeof( vslvm_data_area_descriptor_t ) );

		if( result != 0 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 data_area_descriptor_data.offset,
			 offset );

			byte_stream_copy_to_uint64_little_endian(
			 data_area_descriptor_data.size,
			 size );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: data area offset\t\t\t: 0x%08" PRIx64 "\n",
				 function,
				 offset );

				libcnotify_printf(
				 "%s: data area size\t\t\t: %" PRIu64 "\n",
				 function,
				 size );

				libcnotify_printf(
				 "\n" );
			}
#endif
			if( libvslvm_data_area_descriptor_initialize(
			     &data_area_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create data area descriptor.",
				 function );

				goto on_error;
			}
			if( libvslvm_data_area_descriptor_set(
			     data_area_descriptor,
			     (off64_t) offset,
			     (size64_t) size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set data area descriptor.",
				 function );

				goto on_error;
			}
			if( libcdata_array_append_entry(
			     internal_physical_volume->data_area_descriptors_array,
			     &entry_index,
			     (intptr_t *) data_area_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append entry to data area descriptors array.",
				 function );

				goto on_error;
			}
			data_area_descriptor = NULL;
		}
	}
	while( result != 0 );

	do
	{
		read_count = libbfio_pool_read_buffer(
		              file_io_pool,
		              file_io_pool_entry,
		              (uint8_t *) &data_area_descriptor_data,
		              sizeof( vslvm_data_area_descriptor_t ),
		              error );

		if( read_count != (ssize_t) sizeof( vslvm_data_area_descriptor_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read metadata area descriptor.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: metadata area descriptor data:\n",
			 function );
			libcnotify_print_data(
			 (uint8_t *) &data_area_descriptor_data,
			 sizeof( vslvm_data_area_descriptor_t ),
			 0 );
		}
#endif
		result = memory_compare(
		          (uint8_t *) &data_area_descriptor_data,
		          vslvm_empty_data_area_descriptor,
		          sizeof( vslvm_data_area_descriptor_t ) );

		if( result != 0 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 data_area_descriptor_data.offset,
			 offset );

			byte_stream_copy_to_uint64_little_endian(
			 data_area_descriptor_data.size,
			 size );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: metadata area offset\t\t: 0x%08" PRIx64 "\n",
				 function,
				 offset );

				libcnotify_printf(
				 "%s: metadata area size\t\t\t: %" PRIu64 "\n",
				 function,
				 size );

				libcnotify_printf(
				 "\n" );
			}
#endif
			if( libvslvm_data_area_descriptor_initialize(
			     &data_area_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create data area descriptor.",
				 function );

				goto on_error;
			}
			if( libvslvm_data_area_descriptor_set(
			     data_area_descriptor,
			     (off64_t) offset,
			     (size64_t) size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set data area descriptor.",
				 function );

				goto on_error;
			}
			if( libcdata_array_append_entry(
			     internal_physical_volume->metadata_area_descriptors_array,
			     &entry_index,
			     (intptr_t *) data_area_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append entry to metadata area descriptors array.",
				 function );

				goto on_error;
			}
			data_area_descriptor = NULL;
		}
	}
	while( result != 0 );

	return( 1 );

on_error:
	if( data_area_descriptor != NULL )
	{
		libvslvm_data_area_descriptor_free(
		 &data_area_descriptor,
		 NULL );
	}
	libcdata_array_empty(
	 internal_physical_volume->metadata_area_descriptors_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_data_area_descriptor_free,
	 NULL );

	libcdata_array_empty(
	 internal_physical_volume->data_area_descriptors_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_data_area_descriptor_free,
	 NULL );

	return( -1 );
}

/* Reads the physical volume
 * Callback function for the physical volume files list
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_read_element_data(
     intptr_t *data_handle LIBVSLVM_ATTRIBUTE_UNUSED,
     libbfio_pool_t *file_io_pool,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int file_io_pool_entry,
     off64_t physical_volume_offset,
     size64_t physical_volume_size,
     uint32_t element_flags LIBVSLVM_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBVSLVM_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libvslvm_physical_volume_t *physical_volume = NULL;
	static char *function                       = "libvslvm_physical_volume_read_element_data";
	off64_t label_offset                        = 0;
	int result                                  = 0;

	LIBVSLVM_UNREFERENCED_PARAMETER( data_handle )
	LIBVSLVM_UNREFERENCED_PARAMETER( element_flags )
	LIBVSLVM_UNREFERENCED_PARAMETER( read_flags )

	if( libvslvm_physical_volume_initialize(
	     &physical_volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create physical volume.",
		 function );

		goto on_error;
	}
	/* The physical volume label can be stored in one of the first 4 sectors
	 */
	label_offset = 0;

	while( label_offset < 2048 )
	{
		result = libvslvm_physical_volume_read_label(
			  physical_volume,
			  file_io_pool,
			  file_io_pool_entry,
			  physical_volume_offset + label_offset,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read physical volume label at offset: %" PRIi64 ".",
			 function,
			 physical_volume_offset + label_offset );

			goto on_error;
		}
		else if( result != 0 )
		{
			break;
		}
		label_offset += 512;
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read physical volume label.",
		 function );

		goto on_error;
	}
	if( libfdata_list_element_set_element_value(
	     element,
	     (intptr_t *) file_io_pool,
	     cache,
	     (intptr_t *) physical_volume,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_internal_physical_volume_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set physical volume as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
	}
	return( -1 );
}

