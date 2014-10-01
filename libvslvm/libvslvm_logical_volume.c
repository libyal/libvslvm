/*
 * Logical volume functions
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

#include "libvslvm_definitions.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libfcache.h"
#include "libvslvm_libfdata.h"
#include "libvslvm_logical_volume.h"
#include "libvslvm_logical_volume_values.h"
#include "libvslvm_segment.h"
#include "libvslvm_stripe.h"
#include "libvslvm_types.h"

/* Creates a logical volume
 * Make sure the value logical_volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_initialize(
     libvslvm_logical_volume_t **logical_volume,
     libvslvm_logical_volume_values_t *logical_volume_values,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	libvslvm_segment_t *segment                                 = NULL;
	libvslvm_stripe_t *stripe                                   = NULL;
	static char *function                                       = "libvslvm_logical_volume_initialize";
	off64_t segment_offset                                      = 0;
	off64_t stripe_offset                                       = 0;
	size64_t segment_size                                       = 0;
	int element_index                                           = 0;
	int number_of_segments                                      = 0;
	int segment_index                                           = 0;
	int stripe_index                                            = 0;

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
	internal_logical_volume = memory_allocate_structure(
	                           libvslvm_internal_logical_volume_t );

	if( internal_logical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create logical volume.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_logical_volume,
	     0,
	     sizeof( libvslvm_internal_logical_volume_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear logical volume.",
		 function );

		memory_free(
		 internal_logical_volume );

		return( -1 );
	}
/* TODO clone function ? */
/* TODO determine how the LVM raid chunk size is determined, 64k seems to be pretty standard */
	if( libfdata_vector_initialize(
	     &( internal_logical_volume->chunks_vector ),
	     (size64_t) ( 64 * 1024 ),
	     NULL,
/* TODO make sure to set the IO handle
	     (intptr_t *) internal_logical_volume->io_handle,
*/
	     NULL,
	     NULL,
	     NULL,
/* TODO
	     (int (*)(intptr_t *, intptr_t *, libfdata_vector_t *, libfcache_cache_t *, int, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libvslvm_io_handle_read_chunk,
*/
	     NULL,
	     LIBFDATA_FLAG_DATA_HANDLE_NON_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create chunks vector.",
		 function );

		goto on_error;
	}
	if( libvslvm_logical_volume_values_get_number_of_segments(
	     logical_volume_values,
	     &number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of segments.",
		 function );

		goto on_error;
	}
	for( segment_index = 0;
	     segment_index < number_of_segments;
	     segment_index++ )
	{
		if( libvslvm_logical_volume_values_get_segment(
		     logical_volume_values,
		     segment_index,
		     &segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d.",
			 function,
			 segment_index );

			goto on_error;
		}
		if( libvslvm_segment_get_offset(
		     segment,
		     &segment_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d offset.",
			 function,
			 segment_index );

			goto on_error;
		}
		if( libvslvm_segment_get_size(
		     segment,
		     &segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d size.",
			 function,
			 segment_index );

			goto on_error;
		}
/* TODO get stripe */
		if( libvslvm_stripe_free(
		     &stripe,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free stripe: %d.",
			 function,
			 stripe_index );

			goto on_error;
		}
		if( libvslvm_segment_free(
		     &segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free segment: %d.",
			 function,
			 segment_index );

			goto on_error;
		}
		if( libfdata_vector_append_segment(
		     internal_logical_volume->chunks_vector,
		     &element_index,
		     0,
		     stripe_offset,
		     segment_size,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append segment to chunks vector.",
			 function );

			goto on_error;
		}
	}
	if( libfcache_cache_initialize(
	     &( internal_logical_volume->chunks_cache ),
	     LIBVSLVM_MAXIMUM_CACHE_ENTRIES_CHUNKS,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create chunks cache.",
		 function );

		goto on_error;
	}
	internal_logical_volume->logical_volume_values = logical_volume_values;

	*logical_volume= (libvslvm_logical_volume_t *) internal_logical_volume;

	return( 1 );

on_error:
	if( stripe != NULL )
	{
		libvslvm_stripe_free(
		 &stripe,
		 NULL );
	}
	if( segment != NULL )
	{
		libvslvm_segment_free(
		 &segment,
		 NULL );
	}
	if( internal_logical_volume != NULL )
	{
		memory_free(
		 internal_logical_volume );
	}
	return( -1 );
}

/* Frees a logical volume
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_free(
     libvslvm_logical_volume_t **logical_volume,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_free";
	int result                                                  = 1;

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
		internal_logical_volume = (libvslvm_internal_logical_volume_t *) *logical_volume;
		*logical_volume         = NULL;

/* TODO add note about logical_volume_values being referenced */

		if( internal_logical_volume->chunks_vector != NULL )
		{
			if( libfdata_vector_free(
			     &( internal_logical_volume->chunks_vector ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free chunks vector.",
				 function );

				result = -1;
			}
		}
		if( internal_logical_volume->chunks_cache != NULL )
		{
			if( libfcache_cache_free(
			     &( internal_logical_volume->chunks_cache ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free chunks cache.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 internal_logical_volume );
	}
	return( result );
}

/* Retrieves the size of the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_get_name_size(
     libvslvm_logical_volume_t *logical_volume,
     size_t *name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_get_name_size";

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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

	if( libvslvm_logical_volume_values_get_name_size(
	     internal_logical_volume->logical_volume_values,
	     name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the ASCII formatted name
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_get_name(
     libvslvm_logical_volume_t *logical_volume,
     char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_set_name";

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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

	if( libvslvm_logical_volume_values_get_name(
	     internal_logical_volume->logical_volume_values,
	     name,
	     name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_get_identifier_size(
     libvslvm_logical_volume_t *logical_volume,
     size_t *identifier_size,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_get_identifier_size";

	if( logical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logicalogical.",
		 function );

		return( -1 );
	}
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

	if( libvslvm_logical_volume_values_get_identifier_size(
	     internal_logical_volume->logical_volume_values,
	     identifier_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the ASCII formatted identifier
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_get_identifier(
     libvslvm_logical_volume_t *logical_volume,
     char *identifier,
     size_t identifier_size,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_set_identifier";

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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

	if( libvslvm_logical_volume_values_get_identifier(
	     internal_logical_volume->logical_volume_values,
	     identifier,
	     identifier_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of segments
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_get_number_of_segments(
     libvslvm_logical_volume_t *logical_volume,
     int *number_of_segments,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_get_number_of_segments";

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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

	if( libvslvm_logical_volume_values_get_number_of_segments(
	     internal_logical_volume->logical_volume_values,
	     number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of segments.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific segment
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_get_segment(
     libvslvm_logical_volume_t *logical_volume,
     int segment_index,
     libvslvm_segment_t **segment,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_get_segment";

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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

	if( libvslvm_logical_volume_values_get_segment(
	     internal_logical_volume->logical_volume_values,
	     segment_index,
	     segment,
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

#ifdef TODO

/* Reads data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvslvm_volume_read_buffer(
         libvslvm_volume_t *volume,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libvslvm_sector_data_t *sector_data         = NULL;
	libvslvm_internal_volume_t *internal_volume = NULL;
	static char *function                       = "libvslvm_volume_read_buffer";
	off64_t element_data_offset                 = 0;
	size_t buffer_offset                        = 0;
	size_t read_size                            = 0;
	size_t sector_data_offset                   = 0;
	ssize_t total_read_count                    = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvslvm_internal_volume_t *) volume;

	if( internal_volume->is_locked != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - volume is locked.",
		 function );

		return( -1 );
	}
	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_volume->sectors_vector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing sectors vector.",
		 function );

		return( -1 );
	}
	if( internal_volume->sectors_cache == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing sectors cache.",
		 function );

		return( -1 );
	}
	if( internal_volume->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid volume - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( (size64_t) internal_volume->current_offset >= internal_volume->io_handle->volume_size )
	{
		return( 0 );
	}
	if( (size64_t) ( internal_volume->current_offset + buffer_size ) >= internal_volume->io_handle->volume_size )
	{
		buffer_size = (size_t) ( internal_volume->io_handle->volume_size - internal_volume->current_offset );
	}
	sector_data_offset = (size_t) ( internal_volume->current_offset % internal_volume->io_handle->bytes_per_sector );

	while( buffer_size > 0 )
	{
		if( libfdata_vector_get_element_value_at_offset(
		     internal_volume->sectors_vector,
		     (intptr_t *) internal_volume->file_io_handle,
		     internal_volume->sectors_cache,
		     internal_volume->current_offset,
		     &element_data_offset,
		     (intptr_t **) &sector_data,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sector data at offset: %" PRIi64 ".",
			 function,
			 internal_volume->current_offset );

			return( -1 );
		}
		if( sector_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing sector data at offset: %" PRIi64 ".",
			 function,
			 internal_volume->current_offset );

			return( -1 );
		}
		read_size = sector_data->data_size - sector_data_offset;

		if( read_size > buffer_size )
		{
			read_size = buffer_size;
		}
		if( read_size == 0 )
		{
			break;
		}
		if( memory_copy(
		     &( ( (uint8_t *) buffer )[ buffer_offset ] ),
		     &( ( sector_data->data )[ sector_data_offset ] ),
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy sector data to buffer.",
			 function );

			return( -1 );
		}
		buffer_offset     += read_size;
		buffer_size       -= read_size;
		total_read_count  += (ssize_t) read_size;
		sector_data_offset = 0;

		internal_volume->current_offset += (off64_t) read_size;

		if( (size64_t) internal_volume->current_offset >= internal_volume->io_handle->volume_size )
		{
			break;
		}
		if( internal_volume->io_handle->abort != 0 )
		{
			break;
		}
	}
	return( total_read_count );
}

/* Reads (media) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvslvm_volume_read_buffer_at_offset(
         libvslvm_volume_t *volume,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	static char *function = "libvslvm_volume_read_buffer_at_offset";
	ssize_t read_count    = 0;

	if( libvslvm_volume_seek_offset(
	     volume,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	read_count = libvslvm_volume_read_buffer(
	              volume,
	              buffer,
	              buffer_size,
	              error );

	if( read_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libvslvm_volume_seek_offset(
         libvslvm_volume_t *volume,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libvslvm_internal_volume_t *internal_volume = NULL;
	static char *function                     = "libvslvm_volume_seek_offset";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvslvm_internal_volume_t *) volume;

	if( internal_volume->is_locked != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - volume is locked.",
		 function );

		return( -1 );
	}
	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{	
		offset += internal_volume->current_offset;
	}
	else if( whence == SEEK_END )
	{	
		offset += (off64_t) internal_volume->io_handle->volume_size;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: seeking media data offset: %" PRIi64 ".\n",
		 function,
		 offset );
	}
#endif
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	internal_volume->current_offset = offset;

	return( offset );
}

/* Retrieves the current offset of the (volume) data
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_get_offset(
     libvslvm_volume_t *volume,
     off64_t *offset,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_t *internal_volume = NULL;
	static char *function                     = "libvslvm_volume_get_offset";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvslvm_internal_volume_t *) volume;

	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
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
	*offset = internal_volume->current_offset;

	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libvslvm_volume_get_size(
     libvslvm_volume_t *volume,
     size64_t *size,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_t *internal_volume = NULL;
	static char *function                     = "libvslvm_volume_get_size";

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	internal_volume = (libvslvm_internal_volume_t *) volume;

	if( internal_volume->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid volume - missing IO handle.",
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
	*size = internal_volume->io_handle->volume_size;

	return( 1 );
}

#endif /* TODO */


