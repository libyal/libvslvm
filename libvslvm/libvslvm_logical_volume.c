/*
 * Logical volume functions
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
#include <narrow_string.h>
#include <types.h>

#include "libvslvm_chunk_data.h"
#include "libvslvm_data_area_descriptor.h"
#include "libvslvm_definitions.h"
#include "libvslvm_io_handle.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcthreads.h"
#include "libvslvm_libfcache.h"
#include "libvslvm_libfdata.h"
#include "libvslvm_logical_volume.h"
#include "libvslvm_logical_volume_values.h"
#include "libvslvm_physical_volume.h"
#include "libvslvm_segment.h"
#include "libvslvm_stripe.h"
#include "libvslvm_types.h"
#include "libvslvm_unused.h"
#include "libvslvm_volume_group.h"

/* Creates a logical volume
 * Make sure the value logical_volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_initialize(
     libvslvm_logical_volume_t **logical_volume,
     libvslvm_io_handle_t *io_handle,
     libvslvm_volume_group_t *volume_group,
     libbfio_pool_t *physical_volume_file_io_pool,
     libvslvm_logical_volume_values_t *logical_volume_values,
     libcerror_error_t **error )
{
	char physical_volume_name[ 64 ];

	libvslvm_data_area_descriptor_t *data_area_descriptor       = NULL;
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	libvslvm_physical_volume_t *physical_volume                 = NULL;
	libvslvm_segment_t *segment                                 = NULL;
	libvslvm_stripe_t *stripe                                   = NULL;
	static char *function                                       = "libvslvm_logical_volume_initialize";
	off64_t segment_offset                                      = 0;
	off64_t stripe_offset                                       = 0;
	size64_t segment_size                                       = 0;
	size_t physical_volume_name_length                          = 0;
	int element_index                                           = 0;
	int number_of_segments                                      = 0;
	int number_of_stripes                                       = 0;
	int result                                                  = 0;
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
/* TODO determine how the LVM raid chunk size is determined, 64k seems to be pretty standard */
	if( libfdata_vector_initialize(
	     &( internal_logical_volume->chunks_vector ),
	     (size64_t) ( 64 * 1024 ),
	     NULL,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_vector_t *, libfdata_cache_t *, int, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libvslvm_logical_volume_read_chunk_data,
	     NULL,
	     LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
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
		if( libvslvm_segment_get_range(
		     segment,
		     &segment_offset,
		     &segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve segment: %d range.",
			 function,
			 segment_index );

			goto on_error;
		}
		if( libvslvm_segment_get_number_of_stripes(
		     segment,
		     &number_of_stripes,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of stripes.",
			 function );

			goto on_error;
		}
/* TODO add support for multi stripe segments */
		if( number_of_stripes != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported number of stripes.",
			 function );

			goto on_error;
		}
		for( stripe_index = 0;
		     stripe_index < number_of_stripes;
		     stripe_index++ )
		{
			if( libvslvm_segment_get_stripe(
			     segment,
			     stripe_index,
			     &stripe,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve stripe: %d.",
				 function,
				 stripe_index );

				goto on_error;
			}
			if( libvslvm_stripe_get_physical_volume_name(
			     stripe,
			     physical_volume_name,
			     64,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve stripe: %d physical volume name.",
				 function,
				 stripe_index );

				goto on_error;
			}
			if( libvslvm_stripe_get_data_area_offset(
			     stripe,
			     &stripe_offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve stripe: %d data area offset.",
				 function,
				 stripe_index );

				goto on_error;
			}
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
			physical_volume_name_length = narrow_string_length(
			                               physical_volume_name );

			if( libvslvm_volume_group_get_physical_volume_by_name(
			     volume_group,
			     physical_volume_name,
			     physical_volume_name_length,
			     &physical_volume,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve physical volume by name.",
				 function );

				goto on_error;
			}
			result = libvslvm_physical_volume_get_data_area_descriptor_by_offset(
			          physical_volume,
			          stripe_offset,
			          &data_area_descriptor,
			          error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve data area descriptor by offset: 0x%08" PRIx64 ".",
				 function,
				 segment_offset );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( data_area_descriptor == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing data area descriptor.",
					 function );

					goto on_error;
				}
				/* The stripe data area offset is relative to the start
				 * of the data area of the volume
				 */
				stripe_offset += data_area_descriptor->offset;
			}
/* TODO check segment size ? */
		}
/* TODO skip the append if the physical volumes are not available? */
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
		segment = NULL;
	}
	if( libfdata_vector_get_size(
	     internal_logical_volume->chunks_vector,
	     &( internal_logical_volume->size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size from chunks vector.",
		 function );

		goto on_error;
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
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_logical_volume->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	internal_logical_volume->io_handle                    = io_handle;
	internal_logical_volume->physical_volume_file_io_pool = physical_volume_file_io_pool;
	internal_logical_volume->logical_volume_values        = logical_volume_values;

	*logical_volume= (libvslvm_logical_volume_t *) internal_logical_volume;

	return( 1 );

on_error:
	if( stripe != NULL )
	{
		libvslvm_stripe_free(
		 &stripe,
		 NULL );
	}
	if( internal_logical_volume != NULL )
	{
		if( internal_logical_volume->chunks_cache != NULL )
		{
			libfcache_cache_free(
			 &( internal_logical_volume->chunks_cache ),
			 NULL );
		}
		if( internal_logical_volume->chunks_vector != NULL )
		{
			libfdata_vector_free(
			 &( internal_logical_volume->chunks_vector ),
			 NULL );
		}
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

		/* The logical_volume_values and physical_volume_file_io_pool references are freed elsewhere
		 */
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
#if defined( HAVE_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_logical_volume->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		memory_free(
		 internal_logical_volume );
	}
	return( result );
}

/* Reads (logical volume) data at the current offset into a buffer using a Basic File IO (bfio) pool
 * This function is not multi-thread safe acquire write lock before call
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvslvm_internal_logical_volume_read_buffer_from_file_io_pool(
         libvslvm_internal_logical_volume_t *internal_logical_volume,
         libbfio_pool_t *physical_volume_file_io_pool,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libvslvm_chunk_data_t *chunk_data = NULL;
	static char *function             = "libvslvm_internal_logical_volume_read_buffer_from_file_io_pool";
	off64_t element_data_offset       = 0;
	size_t buffer_offset              = 0;
	size_t read_size                  = 0;

	if( internal_logical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume.",
		 function );

		return( -1 );
	}
	if( internal_logical_volume->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid logical volume - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( buffer_size == 0 )
	{
		return( 0 );
	}
	if( (size64_t) internal_logical_volume->current_offset >= internal_logical_volume->size )
	{
		return( 0 );
	}
	if( (size64_t) ( internal_logical_volume->current_offset + buffer_size ) > internal_logical_volume->size )
	{
		buffer_size = (size_t) ( internal_logical_volume->size - internal_logical_volume->current_offset );
	}
	while( buffer_size > 0 )
	{
		if( libfdata_vector_get_element_value_at_offset(
		     internal_logical_volume->chunks_vector,
		     (intptr_t *) physical_volume_file_io_pool,
		     (libfdata_cache_t *) internal_logical_volume->chunks_cache,
		     internal_logical_volume->current_offset,
		     &element_data_offset,
		     (intptr_t **) &chunk_data,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve chunk data at offset: 0x%08" PRIx64 ".",
			 function,
			 internal_logical_volume->current_offset );

			return( -1 );
		}
		if( chunk_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing chunk data.",
			 function );

			return( -1 );
		}
		read_size = chunk_data->data_size - (size_t) element_data_offset;

		if( buffer_size < read_size )
		{
			read_size = buffer_size;
		}
		if( memory_copy(
		     &( ( (uint8_t *) buffer )[ buffer_offset ] ),
		     &( chunk_data->data[ element_data_offset ] ),
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy chunk data.",
			 function );

			return( -1 );
		}
		internal_logical_volume->current_offset += read_size;
		buffer_offset                           += read_size;
		buffer_size                             -= read_size;
	}
	return( (ssize_t) buffer_offset );
}

/* Reads (logical volume) data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvslvm_logical_volume_read_buffer(
         libvslvm_logical_volume_t *logical_volume,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_read_buffer";
	ssize_t read_count                                          = 0;

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

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	read_count = libvslvm_internal_logical_volume_read_buffer_from_file_io_pool(
		      internal_logical_volume,
		      internal_logical_volume->physical_volume_file_io_pool,
		      buffer,
		      buffer_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer from logical volume.",
		 function );

		read_count = -1;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Reads (logical volume) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libvslvm_logical_volume_read_buffer_at_offset(
         libvslvm_logical_volume_t *logical_volume,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_read_buffer_at_offset";
	ssize_t read_count                                          = 0;

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

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libvslvm_internal_logical_volume_seek_offset(
	     internal_logical_volume,
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

		goto on_error;
	}
	read_count = libvslvm_internal_logical_volume_read_buffer_from_file_io_pool(
		      internal_logical_volume,
		      internal_logical_volume->physical_volume_file_io_pool,
		      buffer,
		      buffer_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		goto on_error;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );

on_error:
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	libcthreads_read_write_lock_release_for_write(
	 internal_logical_volume->read_write_lock,
	 NULL );
#endif
	return( -1 );
}

/* Seeks a certain offset of the (logical volume) data
 * This function is not multi-thread safe acquire write lock before call
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libvslvm_internal_logical_volume_seek_offset(
         libvslvm_internal_logical_volume_t *internal_logical_volume,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	static char *function = "libvslvm_internal_logical_volume_seek_offset";

	if( internal_logical_volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid logical volume.",
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
		offset += internal_logical_volume->current_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) internal_logical_volume->size;
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	internal_logical_volume->current_offset = offset;

	return( offset );
}

/* Seeks a certain offset of the (logical volume) data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libvslvm_logical_volume_seek_offset(
         libvslvm_logical_volume_t *logical_volume,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_seek_offset";

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

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	offset = libvslvm_internal_logical_volume_seek_offset(
	          internal_logical_volume,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		offset = -1;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( offset );
}

/* Retrieves the current offset of the (logical volume) data
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_get_offset(
     libvslvm_logical_volume_t *logical_volume,
     off64_t *offset,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_get_offset";

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
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*offset = internal_logical_volume->current_offset;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_get_size(
     libvslvm_logical_volume_t *logical_volume,
     size64_t *size,
     libcerror_error_t **error )
{
	libvslvm_internal_logical_volume_t *internal_logical_volume = NULL;
	static char *function                                       = "libvslvm_logical_volume_get_size";

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
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*size = internal_logical_volume->size;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
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

		result = -1;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
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

		result = -1;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
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
	int result                                                  = 1;

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

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
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

		result = -1;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
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

		result = -1;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
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

		result = -1;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
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
	internal_logical_volume = (libvslvm_internal_logical_volume_t *) logical_volume;

#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
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

		result = -1;
	}
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_logical_volume->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Reads chunk data
 * Callback function for the chunk data vector
 * Returns 1 if successful or -1 on error
 */
int libvslvm_logical_volume_read_chunk_data(
     intptr_t *data_handle LIBVSLVM_ATTRIBUTE_UNUSED,
     libbfio_pool_t *file_io_pool,
     libfdata_vector_t *vector,
     libfdata_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags LIBVSLVM_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBVSLVM_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libvslvm_chunk_data_t *chunk_data = NULL;
	static char *function             = "libvslvm_logical_volume_read_chunk_data";

	LIBVSLVM_UNREFERENCED_PARAMETER( data_handle );
	LIBVSLVM_UNREFERENCED_PARAMETER( element_data_flags );
	LIBVSLVM_UNREFERENCED_PARAMETER( read_flags );

	if( element_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		goto on_error;
	}
	if( libvslvm_chunk_data_initialize(
	     &chunk_data,
	     (size_t) element_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create chunk data.",
		 function );

		goto on_error;
	}
	if( libvslvm_chunk_data_read_file_io_pool(
	     chunk_data,
	     file_io_pool,
	     element_data_file_index,
             element_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read chunk data.",
		 function );

		goto on_error;
	}
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_pool,
	     cache,
	     element_index,
	     (intptr_t *) chunk_data,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_chunk_data_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set chunk data as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( chunk_data != NULL )
	{
		libvslvm_chunk_data_free(
		 &chunk_data,
		 NULL );
	}
	return( -1 );
}

