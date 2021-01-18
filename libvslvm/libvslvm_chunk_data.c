/*
 * Chunk data functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvslvm_chunk_data.h"
#include "libvslvm_definitions.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcnotify.h"

/* Creates a chunk data
 * Make sure the value chunk_data is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_chunk_data_initialize(
     libvslvm_chunk_data_t **chunk_data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_chunk_data_initialize";

	if( chunk_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid chunk data.",
		 function );

		return( -1 );
	}
	if( *chunk_data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid chunk data value already set.",
		 function );

		return( -1 );
	}
	if( ( data_size == 0 )
	 || ( data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	*chunk_data = memory_allocate_structure(
	               libvslvm_chunk_data_t );

	if( *chunk_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create chunk data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *chunk_data,
	     0,
	     sizeof( libvslvm_chunk_data_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear chunk data.",
		 function );

		memory_free(
		 *chunk_data );

		*chunk_data = NULL;

		return( -1 );
	}
	( *chunk_data )->data = (uint8_t *) memory_allocate(
	                                     sizeof( uint8_t ) * data_size );

	if( ( *chunk_data )->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	( *chunk_data )->data_size = data_size;

	return( 1 );

on_error:
	if( *chunk_data != NULL )
	{
		memory_free(
		 *chunk_data );

		*chunk_data = NULL;
	}
	return( -1 );
}

/* Frees a chunk data
 * Returns 1 if successful or -1 on error
 */
int libvslvm_chunk_data_free(
     libvslvm_chunk_data_t **chunk_data,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_chunk_data_free";
	int result            = 1;

	if( chunk_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid chunk data.",
		 function );

		return( -1 );
	}
	if( *chunk_data != NULL )
	{
		if( memory_set(
		     ( *chunk_data )->data,
		     0,
		     ( *chunk_data )->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear data.",
			 function );

			result = -1;
		}
		memory_free(
		 ( *chunk_data )->data );

		memory_free(
		 *chunk_data );

		*chunk_data = NULL;
	}
	return( result );
}

/* Reads chunk data
 * Returns 1 if successful or -1 on error
 */
int libvslvm_chunk_data_read_file_io_pool(
     libvslvm_chunk_data_t *chunk_data,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     off64_t chunk_offset,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_chunk_data_read_file_io_pool";
	ssize_t read_count    = 0;

	if( chunk_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid chunk data.",
		 function );

		return( -1 );
	}
	if( chunk_data->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid chunk data - missing data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading chunk data at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 chunk_offset,
		 chunk_offset );
	}
#endif
	if( libbfio_pool_seek_offset(
	     file_io_pool,
	     file_io_pool_entry,
	     chunk_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek chunk data offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 chunk_offset,
		 chunk_offset );

		return( -1 );
	}
	read_count = libbfio_pool_read_buffer(
		      file_io_pool,
		      file_io_pool_entry,
		      chunk_data->data,
		      chunk_data->data_size,
		      error );

	if( read_count != (ssize_t) chunk_data->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read chunk data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: chunk data:\n",
		 function );
		libcnotify_print_data(
		 chunk_data->data,
		 chunk_data->data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	return( 1 );
}

