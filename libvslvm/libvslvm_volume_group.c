/*
 * Volume group functions
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

#include "libvslvm_io_handle.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_logical_volume.h"
#include "libvslvm_logical_volume_values.h"
#include "libvslvm_physical_volume.h"
#include "libvslvm_types.h"
#include "libvslvm_volume_group.h"

/* Creates a volume group
 * Make sure the value volume_group is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_initialize(
     libvslvm_volume_group_t **volume_group,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_initialize";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	if( *volume_group != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume group value already set.",
		 function );

		return( -1 );
	}
	internal_volume_group = memory_allocate_structure(
	                         libvslvm_internal_volume_group_t );

	if( internal_volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create volume group.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_volume_group,
	     0,
	     sizeof( libvslvm_internal_volume_group_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear volume group.",
		 function );

		memory_free(
		 internal_volume_group );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_volume_group->physical_volumes_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create physical volumes array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_volume_group->logical_volumes_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create logical volumes array.",
		 function );

		goto on_error;
	}
	*volume_group = (libvslvm_volume_group_t *) internal_volume_group;

	return( 1 );

on_error:
	if( internal_volume_group != NULL )
	{
		if( internal_volume_group->physical_volumes_array != NULL )
		{
			libcdata_array_free(
			 &( internal_volume_group->physical_volumes_array ),
			 NULL,
			 NULL );
		}
		memory_free(
		 internal_volume_group );
	}
	return( -1 );
}

/* Frees a volume group
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_free(
     libvslvm_volume_group_t **volume_group,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_volume_group_free";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	if( *volume_group != NULL )
	{
		*volume_group = NULL;
	}
	return( 1 );
}

/* Frees a volume group
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_volume_group_free(
     libvslvm_internal_volume_group_t **internal_volume_group,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_internal_volume_group_free";
	int result            = 1;

	if( internal_volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	if( *internal_volume_group != NULL )
	{
		/* The io_handle and physical_volume_file_io_pool references are freed elsewhere
		 */
		if( ( *internal_volume_group )->name != NULL )
		{
			memory_free(
			 ( *internal_volume_group )->name );
		}
		if( libcdata_array_free(
		     &( ( *internal_volume_group )->physical_volumes_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_internal_physical_volume_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free physical volumes array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( ( *internal_volume_group )->logical_volumes_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_logical_volume_values_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free logical volumes array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_volume_group );

		*internal_volume_group = NULL;
	}
	return( result );
}

/* Sets the IO values
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_set_io_values(
     libvslvm_volume_group_t *volume_group,
     libvslvm_io_handle_t *io_handle,
     libbfio_pool_t *physical_volume_file_io_pool,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_set_io_values";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	internal_volume_group->io_handle                    = io_handle;
	internal_volume_group->physical_volume_file_io_pool = physical_volume_file_io_pool;

	return( 1 );
}

/* Retrieves the size of the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_name_size(
     libvslvm_volume_group_t *volume_group,
     size_t *name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_name_size";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	*name_size = internal_volume_group->name_size;

	return( 1 );
}

/* Retrieves the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_name(
     libvslvm_volume_group_t *volume_group,
     char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_name";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	if( name_size < internal_volume_group->name_size )
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
	     internal_volume_group->name,
	     internal_volume_group->name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		return( -1 );
	}
	name[ internal_volume_group->name_size - 1 ] = 0;

	return( 1 );
}

/* Sets the name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_volume_group_set_name(
     libvslvm_internal_volume_group_t *internal_volume_group,
     const char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_internal_volume_group_set_name";

	if( internal_volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	if( internal_volume_group->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume group - name value already set.",
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
	internal_volume_group->name = (char *) memory_allocate(
	                                        sizeof( char ) * name_size );

	if( internal_volume_group->name == NULL )
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
	     internal_volume_group->name,
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
	internal_volume_group->name[ name_size - 1 ] = 0;

	internal_volume_group->name_size = name_size;

	return( 1 );

on_error:
	if( internal_volume_group->name != NULL )
	{
		memory_free(
		 internal_volume_group->name );

		internal_volume_group->name = NULL;
	}
	internal_volume_group->name_size = 0;

	return( -1 );
}

/* Retrieves the size of the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_identifier_size(
     libvslvm_volume_group_t *volume_group,
     size_t *identifier_size,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_identifier_size";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	if( internal_volume_group->identifier[ 0 ] == 0 )
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
int libvslvm_volume_group_get_identifier(
     libvslvm_volume_group_t *volume_group,
     char *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_set_identifier";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	     internal_volume_group->identifier,
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
int libvslvm_volume_group_set_identifier(
     libvslvm_volume_group_t *volume_group,
     const char *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_set_identifier";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	     internal_volume_group->identifier,
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
	internal_volume_group->identifier[ 38 ] = 0;

	return( 1 );
}

/* Retrieves the sequence number
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_sequence_number(
     libvslvm_volume_group_t *volume_group,
     uint32_t *sequence_number,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_sequence_number";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

	if( sequence_number == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sequence number.",
		 function );

		return( -1 );
	}
	*sequence_number = internal_volume_group->sequence_number;

	return( 1 );
}

/* Retrieves the extent size
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_extent_size(
     libvslvm_volume_group_t *volume_group,
     size64_t *extent_size,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_extent_size";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

	if( extent_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent size.",
		 function );

		return( -1 );
	}
	*extent_size = internal_volume_group->extent_size;

	return( 1 );
}

/* Retrieves the number of physical volumes
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_number_of_physical_volumes(
     libvslvm_volume_group_t *volume_group,
     int *number_of_physical_volumes,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_number_of_physical_volumes";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

	if( libcdata_array_get_number_of_entries(
	     internal_volume_group->physical_volumes_array,
	     number_of_physical_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from physical volumes array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific physical volume
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_physical_volume(
     libvslvm_volume_group_t *volume_group,
     int volume_index,
     libvslvm_physical_volume_t **physical_volume,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_physical_volume";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	if( libcdata_array_get_entry_by_index(
	     internal_volume_group->physical_volumes_array,
	     volume_index,
	     (intptr_t **) physical_volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve physical volume: %d.",
		 function,
		 volume_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the physical volume for an ASCII encoded volume name
 * Returns 1 if successful, 0 if no such physical volume or -1 on error
 */
int libvslvm_volume_group_get_physical_volume_by_name(
     libvslvm_volume_group_t *volume_group,
     const char *volume_name,
     size_t volume_name_length,
     libvslvm_physical_volume_t **physical_volume,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_physical_volume_by_name";
	int number_of_volumes                                   = 0;
	int result                                              = 0;
	int volume_index                                        = 0;

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	if( libcdata_array_get_number_of_entries(
	     internal_volume_group->physical_volumes_array,
	     &number_of_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from physical volumes array.",
		 function );

		return( -1 );
	}
	for( volume_index = 0;
	     volume_index < number_of_volumes;
	     volume_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_volume_group->physical_volumes_array,
		     volume_index,
		     (intptr_t **) physical_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve physical volume: %d.",
			 function,
			 volume_index );

			return( -1 );
		}
		result = libvslvm_physical_volume_compare_by_name(
		          *physical_volume,
		          volume_name,
		          volume_name_length,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of physical volume: %d.",
			 function,
			 volume_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			return( 1 );
		}
	}
	*physical_volume = NULL;

	return( 0 );
}

/* Appends a physical volume
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_append_physical_volume(
     libvslvm_volume_group_t *volume_group,
     libvslvm_physical_volume_t *physical_volume,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_append_physical_volume";
	int entry_index                                         = 0;

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	if( libcdata_array_append_entry(
	     internal_volume_group->physical_volumes_array,
	     &entry_index,
	     (intptr_t *) physical_volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append physical volume to array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of logical volumes
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_number_of_logical_volumes(
     libvslvm_volume_group_t *volume_group,
     int *number_of_logical_volumes,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_get_number_of_logical_volumes";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

	if( libcdata_array_get_number_of_entries(
	     internal_volume_group->logical_volumes_array,
	     number_of_logical_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from logical volumes array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific logical volume
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_get_logical_volume(
     libvslvm_volume_group_t *volume_group,
     int volume_index,
     libvslvm_logical_volume_t **logical_volume,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	libvslvm_logical_volume_values_t *logical_volume_values = NULL;
	static char *function                                   = "libvslvm_volume_group_get_logical_volume";

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

	if( logical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume.",
		 function );

		return( -1 );
	}
	if( *logical_volume != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid logical volume value already set.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_volume_group->logical_volumes_array,
	     volume_index,
	     (intptr_t **) &logical_volume_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve logical volume: %d.",
		 function,
		 volume_index );

		return( -1 );
	}
	if( libvslvm_logical_volume_initialize(
	     logical_volume,
	     internal_volume_group->io_handle,
	     volume_group,
	     internal_volume_group->physical_volume_file_io_pool,
	     logical_volume_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create logical volume.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends a logical volume
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_group_append_logical_volume(
     libvslvm_volume_group_t *volume_group,
     libvslvm_logical_volume_values_t *logical_volume_values,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	static char *function                                   = "libvslvm_volume_group_append_logical_volume";
	int entry_index                                         = 0;

	if( volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) volume_group;

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
	if( libcdata_array_append_entry(
	     internal_volume_group->logical_volumes_array,
	     &entry_index,
	     (intptr_t *) logical_volume_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append logical volume to array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

