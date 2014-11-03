/*
 * The internal handle functions
 *
 * Copyright (C) 2014, Joachim Metz <joachim.metz@gmail.com>
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

#include "libvslvm_data_area_descriptor.h"
#include "libvslvm_debug.h"
#include "libvslvm_definitions.h"
#include "libvslvm_handle.h"
#include "libvslvm_io_handle.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcnotify.h"
#include "libvslvm_metadata.h"
#include "libvslvm_metadata_area.h"
#include "libvslvm_raw_location_descriptor.h"
#include "libvslvm_types.h"

/* Creates a handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_initialize(
     libvslvm_handle_t **handle,
     libcerror_error_t **error )
{
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_initialize";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle value already set.",
		 function );

		return( -1 );
	}
	internal_handle = memory_allocate_structure(
	                   libvslvm_internal_handle_t );

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_handle,
	     0,
	     sizeof( libvslvm_internal_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear handle.",
		 function );

		memory_free(
		 internal_handle );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_handle->data_area_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data area descriptors array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_handle->metadata_area_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create metadata area descriptors array.",
		 function );

		goto on_error;
	}
	if( libvslvm_io_handle_initialize(
	     &( internal_handle->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	*handle = (libvslvm_handle_t *) internal_handle;

	return( 1 );

on_error:
	if( internal_handle != NULL )
	{
		memory_free(
		 internal_handle );
	}
	return( -1 );
}

/* Frees a handle
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_free(
     libvslvm_handle_t **handle,
     libcerror_error_t **error )
{
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_free";
	int result                                  = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		internal_handle = (libvslvm_internal_handle_t *) *handle;

		if( internal_handle->file_io_handle != NULL )
		{
			if( libvslvm_handle_close(
			     *handle,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close handle.",
				 function );

				result = -1;
			}
		}
		*handle = NULL;

		if( libvslvm_io_handle_free(
		     &( internal_handle->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_handle->data_area_descriptors_array ),
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
		     &( internal_handle->metadata_area_descriptors_array ),
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
		 internal_handle );
	}
	return( result );
}

/* Signals the handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_signal_abort(
     libvslvm_handle_t *handle,
     libcerror_error_t **error )
{
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_signal_abort";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libvslvm_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_handle->io_handle->abort = 1;

	return( 1 );
}

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open(
     libvslvm_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_open";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libvslvm_internal_handle_t *) handle;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSLVM_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSLVM_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSLVM_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     libcstring_narrow_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libvslvm_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

		goto on_error;
	}
	internal_handle->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_wide(
     libvslvm_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_open_wide";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libvslvm_internal_handle_t *) handle;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSLVM_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSLVM_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSLVM_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     libcstring_wide_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libvslvm_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	internal_handle->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_file_io_handle(
     libvslvm_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_open_file_io_handle";
	int bfio_access_flags                       = 0;
	int file_io_handle_is_open                  = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libvslvm_internal_handle_t *) handle;

	if( internal_handle->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid internal handle - file IO handle already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBVSLVM_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBVSLVM_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSLVM_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBVSLVM_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	internal_handle->file_io_handle = file_io_handle;

	file_io_handle_is_open = libbfio_handle_is_open(
	                          internal_handle->file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		return( -1 );
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     internal_handle->file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			return( -1 );
		}
	}
	if( libvslvm_handle_open_read(
	     internal_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#ifdef TODO

/* Opens the extent data files
 * If the extent data filenames were not set explicitly this function assumes the extent data files
 * are in the same location as the metadata file
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_extent_data_files(
     libvslvm_handle_t *handle,
     libcerror_error_t **error )
{
	libcstring_system_character_t *extent_data_file_location  = NULL;
	libcstring_system_character_t *extent_data_filename_start = NULL;
        libbfio_pool_t *file_io_pool                              = NULL;
	libvslvm_internal_extent_descriptor_t *extent_descriptor  = NULL;
	libvslvm_internal_handle_t *internal_handle               = NULL;
	static char *function                                     = "libvslvm_handle_open_extent_data_files";
	size_t extent_data_file_location_size                     = 0;
	size_t extent_data_filename_size                          = 0;
	int extent_index                                          = 0;
	int number_of_extents                                     = 0;
	int result                                                = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libvslvm_internal_handle_t *) handle;

	if( internal_handle->descriptor_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal handle - missing descriptor file.",
		 function );

		return( -1 );
	}
	if( internal_handle->extent_data_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - extent data file IO pool already exists.",
		 function );

		return( -1 );
	}
	if( libvslvm_descriptor_file_get_number_of_extents(
	     internal_handle->descriptor_file,
	     &number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extents.",
		 function );

		goto on_error;
	}
	if( number_of_extents == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing extents.",
		 function );

		goto on_error;
	}
	if( libbfio_pool_initialize(
	     &file_io_pool,
	     number_of_extents,
	     internal_handle->maximum_number_of_open_handles,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO pool.",
		 function );

		goto on_error;
	}
	for( extent_index = 0;
	     extent_index < number_of_extents;
	     extent_index++ )
	{
		if( libvslvm_descriptor_file_get_extent_by_index(
		     internal_handle->descriptor_file,
		     extent_index,
		     &extent_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve extent: %d from descriptor file.",
			 function,
			 extent_index );

			goto on_error;
		}
		if( extent_descriptor == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing extent descriptor: %d.",
			 function,
			 extent_index );

			goto on_error;
		}
		if( extent_descriptor->type != LIBVSLVM_EXTENT_TYPE_ZERO )
		{
			if( ( extent_descriptor->filename == NULL )
			 || ( extent_descriptor->filename_size == 0 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid extent descriptor: %d - missing filename.",
				 function,
				 extent_index );

				goto on_error;
			}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			extent_data_filename_start = libcstring_wide_string_search_character_reverse(
			                              extent_descriptor->filename,
			                              (wint_t) LIBCPATH_SEPARATOR,
			                              extent_descriptor->filename_size );
#else
			extent_data_filename_start = libcstring_narrow_string_search_character_reverse(
			                              extent_descriptor->filename,
			                              (int) LIBCPATH_SEPARATOR,
			                              extent_descriptor->filename_size );
#endif
			if( extent_data_filename_start != NULL )
			{
				/* Ignore the path separator itself
				 */
				extent_data_filename_start++;

/* TODO does this work for UTF-16 ? */
				extent_data_filename_size = (size_t) ( extent_data_filename_start - extent_descriptor->filename );
			}
			else
			{
				extent_data_filename_start = extent_descriptor->filename;
				extent_data_filename_size  = extent_descriptor->filename_size;
			}
/* TODO refactor to a function in extent table */
			if( internal_handle->extent_table->basename != NULL )
			{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
				if( libcpath_path_join_wide(
				     &extent_data_file_location,
				     &extent_data_file_location_size,
				     internal_handle->extent_table->basename,
				     internal_handle->extent_table->basename_size - 1,
				     extent_data_filename_start,
				     extent_data_filename_size - 1,
				     error ) != 1 )
#else
				if( libcpath_path_join(
				     &extent_data_file_location,
				     &extent_data_file_location_size,
				     internal_handle->extent_table->basename,
				     internal_handle->extent_table->basename_size - 1,
				     extent_data_filename_start,
				     extent_data_filename_size - 1,
				     error ) != 1 )
#endif
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create extent data file location.",
					 function );

					goto on_error;
				}
			}
			else
			{
				extent_data_file_location      = extent_data_filename_start;
				extent_data_file_location_size = extent_data_filename_size;
			}
			/* Note that the open extent data file function will initialize extent_data_file_io_pool
			 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = libvslvm_handle_open_extent_data_file_wide(
				  internal_handle,
				  file_io_pool,
				  extent_index,
				  extent_data_file_location,
				  error );
#else
			result = libvslvm_handle_open_extent_data_file(
				  internal_handle,
				  file_io_pool,
				  extent_index,
				  extent_data_file_location,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_OPEN_FAILED,
				 "%s: unable to open extent data file: %" PRIs_LIBCSTRING_SYSTEM ".",
				 function,
				 extent_data_file_location );

				goto on_error;
			}
			if( ( extent_data_file_location != NULL )
			 && ( extent_data_file_location != extent_data_filename_start ) )
			{
				memory_free(
				 extent_data_file_location );
			}
			extent_data_filename_start = NULL;
			extent_data_file_location  = NULL;
		}
	}
	if( libvslvm_handle_open_extent_data_files_file_io_pool(
	     handle,
	     file_io_pool,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to open extent data files using a file IO pool.",
                 function );

                goto on_error;
	}
	internal_handle->extent_data_file_io_pool                    = file_io_pool;
	internal_handle->extent_data_file_io_pool_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_pool != NULL )
	{
		libbfio_pool_close_all(
		 file_io_pool,
		 NULL );
		libbfio_pool_free(
		 &file_io_pool,
		 NULL );
	}
	if( ( extent_data_file_location != NULL )
	 && ( extent_data_file_location != extent_data_filename_start ) )
	{
		memory_free(
		 extent_data_file_location );
	}
	return( -1 );
}

/* Opens the extent data files using a Basic File IO (bfio) pool
 * This function assumes the extent data files are in same order as defined by the descriptor file
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_extent_data_files_file_io_pool(
     libvslvm_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error )
{
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_open_extent_data_files_file_io_pool";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libvslvm_internal_handle_t *) handle;

	if( internal_handle->descriptor_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal handle - missing descriptor file.",
		 function );

		return( -1 );
	}
	if( internal_handle->extent_data_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - extent data file IO pool already exists.",
		 function );

		return( -1 );
	}
	if( libvslvm_handle_open_read_grain_table(
	     internal_handle,
	     file_io_pool,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to read grain table.",
                 function );

                return( -1 );
	}
	internal_handle->extent_data_file_io_pool = file_io_pool;

	return( 1 );
}

/* Opens a specific extent data file
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_extent_data_file(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int extent_index,
     const char *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libvslvm_handle_open_extent_data_file";

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->descriptor_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal handle - missing descriptor file.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

                goto on_error;
	}
#endif
	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     libcstring_narrow_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( libvslvm_handle_open_extent_data_file_io_handle(
	     internal_handle,
	     file_io_pool,
	     extent_index,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open extent data file: %s.",
		 function,
		 filename );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a specific extent data file
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_extent_data_file_wide(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int extent_index,
     const wchar_t *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libvslvm_handle_open_extent_data_file_wide";

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->descriptor_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal handle - missing descriptor file.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

                goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

                goto on_error;
	}
#endif
	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     libcstring_wide_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( libvslvm_handle_open_extent_data_file_io_handle(
	     internal_handle,
	     file_io_pool,
	     extent_index,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open extent data file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif

/* Opens an extent data file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_extent_data_file_io_handle(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int extent_index,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_handle_open_extent_data_file_io_handle";
	int bfio_access_flags = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->descriptor_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal handle - missing descriptor file.",
		 function );

		return( -1 );
	}
	if( ( ( internal_handle->access_flags & LIBVSLVM_ACCESS_FLAG_READ ) == 0 )
	 && ( ( internal_handle->access_flags & LIBVSLVM_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBVSLVM_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBVSLVM_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	if( libbfio_handle_open(
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_IO,
                 LIBCERROR_IO_ERROR_OPEN_FAILED,
                 "%s: unable to open file IO handle.",
                 function );

		goto on_error;
	}
	if( libbfio_pool_set_handle(
	     file_io_pool,
	     extent_index,
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set file IO handle: %d in pool.",
		 function,
		 extent_index );

		goto on_error;
	}
	return( 1 );

on_error:
	libbfio_handle_close(
	 file_io_handle,
	 NULL );

	return( -1 );
}

#endif /* TODO */

/* Closes a handle
 * Returns 0 if successful or -1 on error
 */
int libvslvm_handle_close(
     libvslvm_handle_t *handle,
     libcerror_error_t **error )
{
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_close";
	int result                                  = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libvslvm_internal_handle_t *) handle;

	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->file_io_handle_created_in_library != 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libvslvm_debug_print_read_offsets(
			     internal_handle->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
#endif
		if( libbfio_handle_close(
		     internal_handle->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		if( libbfio_handle_free(
		     &( internal_handle->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
	}
	internal_handle->file_io_handle                    = NULL;
	internal_handle->file_io_handle_created_in_library = 0;

	if( internal_handle->extent_data_file_io_pool_created_in_library != 0 )
	{
		if( libbfio_pool_close_all(
		     internal_handle->extent_data_file_io_pool,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close all files.",
			 function );

			result = -1;
		}
		if( libbfio_pool_free(
		     &( internal_handle->extent_data_file_io_pool ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to extent data free file IO pool.",
			 function );

			result = -1;
		}
		internal_handle->extent_data_file_io_pool_created_in_library = 0;
	}
	internal_handle->extent_data_file_io_pool = NULL;

	if( libvslvm_io_handle_clear(
	     internal_handle->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_handle->data_area_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_data_area_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty data area descriptors array.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_handle->metadata_area_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_data_area_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty metadata area descriptors array.",
		 function );

		result = -1;
	}
	if( internal_handle->metadata != NULL )
	{
		if( libvslvm_metadata_free(
		     &( internal_handle->metadata ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free metadata.",
			 function );

			result = -1;
		}
	}
	return( result );
}

/* Opens a handle for reading
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_read(
     libvslvm_internal_handle_t *internal_handle,
     libcerror_error_t **error )
{
	libvslvm_data_area_descriptor_t *data_area_descriptor       = NULL;
	libvslvm_metadata_area_t *metadata_area                     = NULL;
	libvslvm_raw_location_descriptor_t *raw_location_descriptor = NULL;
	static char *function                                       = "libvslvm_handle_open_read";
	off64_t file_offset                                         = 0;
	off64_t data_area_offset                                    = 0;
	off64_t metadata_offset                                     = 0;
	size64_t data_area_size                                     = 0;
	size64_t metadata_size                                      = 0;
	uint32_t raw_location_descriptor_checksum                   = 0;
	uint32_t raw_location_descriptor_flags                      = 0;
	int number_of_data_area_descriptors                         = 0;
	int number_of_raw_location_descriptors                      = 0;
	int result                                                  = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->metadata != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - metadata value already set.",
		 function );

		return( -1 );
	}
	/* The physical volume label can be stored in one of the first 4 sectors
	 */
	while( file_offset < 2048 )
	{
		result = libvslvm_io_handle_read_physical_volume_label(
		          internal_handle->io_handle,
		          internal_handle->file_io_handle,
		          file_offset,
		          internal_handle->data_area_descriptors_array,
		          internal_handle->metadata_area_descriptors_array,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read physical volume label at offset: %" PRIi64 ".",
			 function,
			 file_offset );

			goto on_error;
		}
		else if( result != 0 )
		{
			break;
		}
		file_offset += 512;
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->metadata_area_descriptors_array,
	     &number_of_data_area_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of metadata area descriptors from array.",
		 function );

		goto on_error;
	}
/* TODO */
	if( number_of_data_area_descriptors != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported number of metadata area descriptors.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_entry_by_index(
	     internal_handle->metadata_area_descriptors_array,
	     0,
	     (intptr_t **) &data_area_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve metadata area descriptor: 0.",
		 function );

		goto on_error;
	}
	if( libvslvm_data_area_descriptor_get(
	     data_area_descriptor,
	     &data_area_offset,
	     &data_area_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve metadata area descriptor: 0 values.",
		 function );

		goto on_error;
	}
	/* Read the metadata area
	 */
	if( libvslvm_metadata_area_initialize(
	     &metadata_area,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create metadata area.",
		 function );

		goto on_error;
	}
	if( libvslvm_metadata_area_read(
	     metadata_area,
	     internal_handle->file_io_handle,
	     data_area_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read metadata area.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     metadata_area->raw_location_descriptors_array,
	     &number_of_raw_location_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of raw location descriptors from array.",
		 function );

		goto on_error;
	}
/* TODO */
	if( number_of_raw_location_descriptors != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported number of raw location area descriptors.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_entry_by_index(
	     metadata_area->raw_location_descriptors_array,
	     0,
	     (intptr_t **) &raw_location_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve raw location descriptor: 0.",
		 function );

		goto on_error;
	}
	if( libvslvm_raw_location_descriptor_get(
	     raw_location_descriptor,
	     &metadata_offset,
	     &metadata_size,
	     &raw_location_descriptor_checksum,
	     &raw_location_descriptor_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve raw location descriptor: 0 values.",
		 function );

		goto on_error;
	}
	if( libvslvm_metadata_area_free(
	     &metadata_area,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free metadata area.",
		 function );

		goto on_error;
	}
	/* Read the metadata
	 */
	if( libvslvm_metadata_initialize(
	     &( internal_handle->metadata ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create metadata.",
		 function );

		goto on_error;
	}
	if( libvslvm_metadata_read(
	     internal_handle->metadata,
	     internal_handle->io_handle,
	     internal_handle->file_io_handle,
	     metadata_offset,
	     metadata_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read metadata.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( internal_handle->metadata != NULL )
	{
		libvslvm_metadata_free(
		 &( internal_handle->metadata ),
		 NULL );
	}
	if( metadata_area != NULL )
	{
		libvslvm_metadata_area_free(
		 &metadata_area,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the volume group
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvslvm_handle_get_volume_group(
     libvslvm_handle_t *handle,
     libvslvm_volume_group_t **volume_group,
     libcerror_error_t **error )
{
	libvslvm_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libvslvm_handle_get_volume_group";
	int result                                  = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libvslvm_internal_handle_t *) handle;

	result = libvslvm_metadata_get_volume_group(
	          internal_handle->metadata,
	          volume_group,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of metadata area descriptors from array.",
		 function );

		return( -1 );
	}
	return( result );
}

