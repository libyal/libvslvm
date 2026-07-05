/*
 * OSS-Fuzz target for libvslvm volume group type
 *
 * Copyright (C) 2014-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libvslvm.h"

#if !defined( LIBVSLVM_HAVE_BFIO )

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_open_file_io_handle(
     libvslvm_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvslvm_error_t **error );

/* Opens the physical volume files
 * This function assumes the physical volume files are in same order as defined by the metadata
 * Returns 1 if successful or -1 on error
 */
LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files_file_io_pool(
     libvslvm_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libvslvm_error_t **error );

#endif /* !defined( LIBVSLVM_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	char string[ 64 ];

	libbfio_handle_t *file_io_handle      = NULL;
	libbfio_pool_t *file_io_pool          = NULL;
	libvslvm_handle_t *handle             = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	size64_t extent_size                  = 0;
	size_t string_size                    = 0;
	uint32_t value_32bit                  = 0;
	int entry_index                       = 0;
	int number_of_volumes                 = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libbfio_pool_initialize(
	     &file_io_pool,
	     0,
	     0,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libvslvm_handle_initialize(
	     &handle,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libvslvm_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     LIBVSLVM_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libvslvm_handle;
	}
	if( libbfio_pool_append_handle(
	     file_io_pool,
	     &entry_index,
	     file_io_handle,
	     LIBBFIO_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libvslvm_handle;
	}
	/* The file IO pool takes over management of the file IO handle
	 */
	file_io_handle = NULL;

	if( libvslvm_handle_open_physical_volume_files_file_io_pool(
	     handle,
	     file_io_pool,
	     NULL ) != 1 )
	{
		goto on_error_libvslvm_handle;
	}
	if( libvslvm_handle_get_volume_group(
	     handle,
	     &volume_group,
	     NULL ) == 1 )
	{
		if( libvslvm_volume_group_get_name_size(
		     volume_group,
		     &string_size,
		     NULL ) != 1 )
		{
			goto on_error_libvslvm_volume_group;
		}
		if( libvslvm_volume_group_get_name(
		     volume_group,
		     string,
		     64,
		     NULL ) != 1 )
		{
			goto on_error_libvslvm_volume_group;
		}
		if( libvslvm_volume_group_get_identifier_size(
		     volume_group,
		     &string_size,
		     NULL ) != 1 )
		{
			goto on_error_libvslvm_volume_group;
		}
		if( libvslvm_volume_group_get_identifier(
		     volume_group,
		     string,
		     64,
		     NULL ) != 1 )
		{
			goto on_error_libvslvm_volume_group;
		}
		if( libvslvm_volume_group_get_sequence_number(
		     volume_group,
		     &value_32bit,
		     NULL ) != 1 )
		{
			goto on_error_libvslvm_volume_group;
		}
		if( libvslvm_volume_group_get_extent_size(
		     volume_group,
		     &extent_size,
		     NULL ) != 1 )
		{
			goto on_error_libvslvm_volume_group;
		}
		if( libvslvm_volume_group_get_number_of_physical_volumes(
		     volume_group,
		     &number_of_volumes,
		     NULL ) != 1 )
		{
			goto on_error_libvslvm_volume_group;
		}
		if( libvslvm_volume_group_get_number_of_logical_volumes(
		     volume_group,
		     &number_of_volumes,
		     NULL ) != 1 )
		{
			goto on_error_libvslvm_volume_group;
		}
on_error_libvslvm_volume_group:
		libvslvm_volume_group_free(
		 &volume_group,
		 NULL );
	}
	libvslvm_handle_close(
	 handle,
	 NULL );

on_error_libvslvm_handle:
	libvslvm_handle_free(
	 &handle,
	 NULL );

on_error_libbfio:
	/* Note that on error the handle still has a reference to file_io_pool
	 * that will be closed. Therefore the file IO pool and handle need to
	 * be freed after closing or freeing the handle.
	 */
	if( file_io_pool != NULL )
	{
		libbfio_pool_free(
		 &file_io_pool,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

} /* extern "C" */

