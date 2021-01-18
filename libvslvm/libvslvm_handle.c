/*
 * The internal handle functions
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
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

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
		if( internal_handle->io_handle != NULL )
		{
			libvslvm_io_handle_free(
			 &( internal_handle->io_handle ),
			 NULL );
		}
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

		if( ( internal_handle->physical_volume_file_io_pool != NULL )
		 || ( internal_handle->metadata != NULL ) )
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
	size_t filename_length                      = 0;

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
		 "%s: unsupported accesss flags.",
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
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
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
		 "%s: unable to open handle: %s.",
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
	size_t filename_length                      = 0;

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
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

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
	int file_io_handle_opened_in_library        = 0;

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
		 "%s: invalid handle - file IO handle already set.",
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
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
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
		file_io_handle_opened_in_library = 1;
	}
	if( libvslvm_internal_handle_open_read(
	     internal_handle,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
	internal_handle->file_io_handle                   = file_io_handle;
	internal_handle->file_io_handle_opened_in_library = file_io_handle_opened_in_library;

	return( 1 );

on_error:
	if( ( file_io_handle_is_open == 0 )
	 && ( file_io_handle_opened_in_library != 0 ) )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Opens the physical volume files
 * This function assumes the physical volume files are in same order as defined by the metadata
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_physical_volume_files(
     libvslvm_handle_t *handle,
     char * const filenames[],
     int number_of_filenames,
     libcerror_error_t **error )
{
        libbfio_pool_t *file_io_pool                = NULL;
	libvslvm_internal_handle_t *internal_handle = NULL;
	libvslvm_volume_group_t *volume_group       = NULL;
	static char *function                       = "libvslvm_handle_open_physical_volume_files";
	int number_of_physical_volumes              = 0;
	int physical_volume_index                   = 0;
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

	if( internal_handle->metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal handle - missing metadata.",
		 function );

		return( -1 );
	}
	if( internal_handle->physical_volume_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - physical volume file IO pool already exists.",
		 function );

		return( -1 );
	}
	result = libvslvm_metadata_get_volume_group(
	          internal_handle->metadata,
	          &volume_group,
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
	else if( result == 0 )
	{
		return( 1 );
	}
	if( libvslvm_volume_group_get_number_of_physical_volumes(
	     volume_group,
	     &number_of_physical_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of physical volumes.",
		 function );

		goto on_error;
	}
	if( number_of_physical_volumes == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing physical volumes.",
		 function );

		goto on_error;
	}
	if( number_of_filenames != number_of_physical_volumes )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: mismatch between number of filenames and physical volumes in metadata.",
		 function );

		goto on_error;
	}
	if( libbfio_pool_initialize(
	     &file_io_pool,
	     number_of_physical_volumes,
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
	for( physical_volume_index = 0;
	     physical_volume_index < number_of_physical_volumes;
	     physical_volume_index++ )
	{
		if( filenames[ physical_volume_index ] == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing filename for physical volume: %d.",
			 function,
			 physical_volume_index );

			goto on_error;
		}
		if( libvslvm_handle_open_physical_volume_file(
		     internal_handle,
		     file_io_pool,
		     physical_volume_index,
		     filenames[ physical_volume_index ],
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open physical volume file: %" PRIs_SYSTEM ".",
			 function,
			 filenames[ physical_volume_index ] );

			goto on_error;
		}
	}
	if( libvslvm_internal_handle_open_read_data_area_table(
	     internal_handle,
	     file_io_pool,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to read data area table.",
                 function );

                goto on_error;
	}
	internal_handle->physical_volume_file_io_pool                    = file_io_pool;
	internal_handle->physical_volume_file_io_pool_created_in_library = 1;

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
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens the physical volume files
 * This function assumes the physical volume files are in same order as defined by the metadata
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_physical_volume_files_wide(
     libvslvm_handle_t *handle,
     wchar_t * const filenames[],
     int number_of_filenames,
     libcerror_error_t **error )
{
        libbfio_pool_t *file_io_pool                = NULL;
	libvslvm_internal_handle_t *internal_handle = NULL;
	libvslvm_volume_group_t *volume_group       = NULL;
	static char *function                       = "libvslvm_handle_open_physical_volume_files_wide";
	int number_of_physical_volumes              = 0;
	int physical_volume_index                   = 0;
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

	if( internal_handle->metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal handle - missing metadata.",
		 function );

		return( -1 );
	}
	if( internal_handle->physical_volume_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - physical volume file IO pool already exists.",
		 function );

		return( -1 );
	}
	result = libvslvm_metadata_get_volume_group(
	          internal_handle->metadata,
	          &volume_group,
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
	else if( result == 0 )
	{
		return( 1 );
	}
	if( libvslvm_volume_group_get_number_of_physical_volumes(
	     volume_group,
	     &number_of_physical_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of physical volumes.",
		 function );

		goto on_error;
	}
	if( number_of_physical_volumes == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing physical volumes.",
		 function );

		goto on_error;
	}
	if( number_of_filenames != number_of_physical_volumes )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: mismatch between number of filenames and physical volumes in metadata.",
		 function );

		goto on_error;
	}
	if( libbfio_pool_initialize(
	     &file_io_pool,
	     number_of_physical_volumes,
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
	for( physical_volume_index = 0;
	     physical_volume_index < number_of_physical_volumes;
	     physical_volume_index++ )
	{
		if( filenames[ physical_volume_index ] == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing filename for physical volume: %d.",
			 function,
			 physical_volume_index );

			goto on_error;
		}
		if( libvslvm_handle_open_physical_volume_file_wide(
		     internal_handle,
		     file_io_pool,
		     physical_volume_index,
		     filenames[ physical_volume_index ],
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open physical volume file: %" PRIs_SYSTEM ".",
			 function,
			 filenames[ physical_volume_index ] );

			goto on_error;
		}
	}
	if( libvslvm_internal_handle_open_read_data_area_table(
	     internal_handle,
	     file_io_pool,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to read data area table.",
                 function );

                goto on_error;
	}
	internal_handle->physical_volume_file_io_pool                    = file_io_pool;
	internal_handle->physical_volume_file_io_pool_created_in_library = 1;

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
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens the physical volume files using a Basic File IO (bfio) pool
 * This function assumes the physical volume files are in same order as defined by the metadata
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_physical_volume_files_file_io_pool(
     libvslvm_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error )
{
	libvslvm_internal_handle_t *internal_handle = NULL;
	libvslvm_volume_group_t *volume_group       = NULL;
	static char *function                       = "libvslvm_handle_open_physical_volume_files_file_io_pool";
	int number_of_file_io_handles               = 0;
	int number_of_physical_volumes              = 0;
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

	if( internal_handle->metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal handle - missing metadata.",
		 function );

		return( -1 );
	}
	if( internal_handle->physical_volume_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - physical volume file IO pool already exists.",
		 function );

		return( -1 );
	}
	result = libvslvm_metadata_get_volume_group(
	          internal_handle->metadata,
	          &volume_group,
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
	else if( result == 0 )
	{
		return( 1 );
	}
	if( libvslvm_volume_group_get_number_of_physical_volumes(
	     volume_group,
	     &number_of_physical_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of physical volumes.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_get_number_of_handles(
	     file_io_pool,
	     &number_of_file_io_handles,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of handles in file IO pool.",
		 function );

		return( -1 );
	}
	if( number_of_physical_volumes == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing physical volumes.",
		 function );

		return( -1 );
	}
	if( number_of_file_io_handles != number_of_physical_volumes )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: mismatch between number of filenames and physical volumes in metadata.",
		 function );

		return( -1 );
	}
	if( libvslvm_internal_handle_open_read_data_area_table(
	     internal_handle,
	     file_io_pool,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to read data area table.",
                 function );

                return( -1 );
	}
	internal_handle->physical_volume_file_io_pool = file_io_pool;

	return( 1 );
}

/* Opens a specific physical volume file
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_physical_volume_file(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int physical_volume_index,
     const char *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libvslvm_handle_open_physical_volume_file";
	size_t filename_length           = 0;

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
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
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
	if( libvslvm_handle_open_physical_volume_file_io_handle(
	     internal_handle,
	     file_io_pool,
	     physical_volume_index,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open physical volume file: %s.",
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

/* Opens a specific physical volume file
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_physical_volume_file_wide(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int physical_volume_index,
     const wchar_t *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libvslvm_handle_open_physical_volume_file_wide";
	size_t filename_length           = 0;

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
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
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
	if( libvslvm_handle_open_physical_volume_file_io_handle(
	     internal_handle,
	     file_io_pool,
	     physical_volume_index,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open physical volume file: %ls.",
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens an physical volume file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libvslvm_handle_open_physical_volume_file_io_handle(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int physical_volume_index,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function                = "libvslvm_handle_open_physical_volume_file_io_handle";
	int bfio_access_flags                = 0;
	int file_io_handle_is_open           = 0;
	int file_io_handle_opened_in_library = 0;

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
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to determine if file IO handle is open.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
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
		file_io_handle_opened_in_library = 1;
	}
	if( libbfio_pool_set_handle(
	     file_io_pool,
	     physical_volume_index,
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
		 physical_volume_index );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Reads the data area table
 * Returns 1 if successful or -1 on error
 */
int libvslvm_internal_handle_open_read_data_area_table(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error )
{
	libvslvm_physical_volume_t *physical_volume = NULL;
	libvslvm_volume_group_t *volume_group       = NULL;
	static char *function                       = "libvslvm_internal_handle_open_read_data_area_table";
	off64_t file_offset                         = 0;
	int number_of_file_io_handles               = 0;
	int number_of_data_area_descriptors         = 0;
	int number_of_physical_volumes              = 0;
	int physical_volume_index                   = 0;
	int result                                  = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	result = libvslvm_metadata_get_volume_group(
	          internal_handle->metadata,
	          &volume_group,
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
	else if( result == 0 )
	{
		return( 1 );
	}
	if( libvslvm_volume_group_get_number_of_physical_volumes(
	     volume_group,
	     &number_of_physical_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of physical volumes.",
		 function );

		return( -1 );
	}
	if( number_of_physical_volumes == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing physical volumes.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_get_number_of_handles(
	     file_io_pool,
	     &number_of_file_io_handles,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve the number of file IO handles.",
		 function );

		return( -1 );
	}
	if( number_of_file_io_handles != number_of_physical_volumes )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: mismatch between number of file IO handles in pool and physical volumes in metadata.",
		 function );

		return( -1 );
	}
	for( physical_volume_index = 0;
	     physical_volume_index < number_of_physical_volumes;
	     physical_volume_index++ )
	{
		if( libvslvm_volume_group_get_physical_volume(
		     volume_group,
		     physical_volume_index,
		     &physical_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve physical volume: %d from volume group.",
			 function,
			 physical_volume_index );

			return( -1 );
		}
		/* The physical volume label can be stored in one of the first 4 sectors
		 */
		file_offset = 0;

		while( file_offset < 2048 )
		{
			result = libvslvm_physical_volume_read_label_file_io_pool(
				  physical_volume,
				  file_io_pool,
				  physical_volume_index,
				  file_offset,
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

				return( -1 );
			}
			else if( result != 0 )
			{
				break;
			}
			file_offset += 512;
		}
		if( libvslvm_physical_volume_get_number_of_data_area_descriptors(
		     physical_volume,
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
		if( number_of_data_area_descriptors <= 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported number of data area descriptors.",
			 function );

			return( -1 );
		}
	}
/* TODO build data area table */
	return( 1 );
}

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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_handle->file_io_handle_created_in_library != 0 )
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
	}
#endif
	if( internal_handle->file_io_handle_opened_in_library != 0 )
	{
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
		internal_handle->file_io_handle_opened_in_library = 0;
	}
	if( internal_handle->file_io_handle_created_in_library != 0 )
	{
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
		internal_handle->file_io_handle_created_in_library = 0;
	}
	internal_handle->file_io_handle = NULL;

	if( internal_handle->physical_volume_file_io_pool_created_in_library != 0 )
	{
		if( libbfio_pool_close_all(
		     internal_handle->physical_volume_file_io_pool,
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
		     &( internal_handle->physical_volume_file_io_pool ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free physical volume data file IO pool.",
			 function );

			result = -1;
		}
		internal_handle->physical_volume_file_io_pool_created_in_library = 0;
	}
	internal_handle->physical_volume_file_io_pool = NULL;

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
int libvslvm_internal_handle_open_read(
     libvslvm_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libbfio_pool_t *file_io_pool                                = NULL;
	libvslvm_data_area_descriptor_t *data_area_descriptor       = NULL;
	libvslvm_metadata_area_t *metadata_area                     = NULL;
	libvslvm_physical_volume_t *physical_volume                 = NULL;
	libvslvm_raw_location_descriptor_t *raw_location_descriptor = NULL;
	static char *function                                       = "libvslvm_internal_handle_open_read";
	size64_t data_area_size                                     = 0;
	size64_t metadata_size                                      = 0;
	off64_t data_area_offset                                    = 0;
	off64_t file_offset                                         = 0;
	off64_t metadata_offset                                     = 0;
	uint32_t raw_location_descriptor_flags                      = 0;
	uint32_t stored_checksum                                    = 0;
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
	if( libbfio_pool_initialize(
	     &file_io_pool,
	     1,
	     0,
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
	if( libbfio_pool_set_handle(
	     file_io_pool,
	     0,
	     file_io_handle,
	     LIBBFIO_OPEN_READ,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set file IO handle: 0 in pool.",
		 function );

		goto on_error;
	}
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
	while( file_offset < 2048 )
	{
		result = libvslvm_physical_volume_read_label_file_io_pool(
		          physical_volume,
		          file_io_pool,
		          0,
		          file_offset,
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
	if( libbfio_pool_remove_handle(
	     file_io_pool,
	     0,
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_REMOVE_FAILED,
		 "%s: unable to remove file IO handle: 0 from pool.",
		 function );

		goto on_error;
	}
	if( libbfio_pool_free(
	     &file_io_pool,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file IO pool.",
		 function );

		goto on_error;
	}
	if( libvslvm_physical_volume_get_number_of_metadata_area_descriptors(
	     physical_volume,
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
/* TODO add support for more than one metadata area descriptors */
	if( number_of_data_area_descriptors != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported number of metadata area descriptors: %d.",
		 function,
		 number_of_data_area_descriptors );

		goto on_error;
	}
	if( libvslvm_physical_volume_get_metadata_area_descriptor(
	     physical_volume,
	     0,
	     &data_area_descriptor,
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
	if( libvslvm_metadata_area_read_file_io_handle(
	     metadata_area,
	     file_io_handle,
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
/* TODO add support for more than one raw location descriptors */
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
	     &stored_checksum,
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
	if( libvslvm_metadata_read_file_io_handle(
	     internal_handle->metadata,
	     file_io_handle,
	     metadata_offset,
	     metadata_size,
	     stored_checksum,
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
	if( libvslvm_internal_physical_volume_free(
	     (libvslvm_internal_physical_volume_t **) &physical_volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free physical volume.",
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
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
	}
	if( file_io_pool != NULL )
	{
		libbfio_pool_remove_handle(
		 file_io_pool,
		 0,
		 &file_io_handle,
		 NULL );
		libbfio_pool_free(
		 &file_io_pool,
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
	else if( result != 0 )
	{
		if( libvslvm_volume_group_set_io_values(
		     *volume_group,
		     internal_handle->io_handle,
		     internal_handle->physical_volume_file_io_pool,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set IO values in volume group.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

