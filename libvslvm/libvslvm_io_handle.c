/*
 * The IO handle functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libvslvm_data_area_descriptor.h"
#include "libvslvm_io_handle.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcnotify.h"

#include "vslvm_physical_volume_label.h"

const char *vslvm_physical_volume_label_signature = "LABELONE";

const uint8_t vslvm_empty_data_area_descriptor[ 16 ] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_io_handle_initialize(
     libvslvm_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_io_handle_initialize";

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
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libvslvm_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libvslvm_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		goto on_error;
	}
	( *io_handle )->bytes_per_sector = 512;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libvslvm_io_handle_free(
     libvslvm_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_io_handle_free";

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
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libvslvm_io_handle_clear(
     libvslvm_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_io_handle_clear";

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
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libvslvm_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads a physical volume label
 * Returns 1 if successful, 0 if not found or -1 on error
 */
int libvslvm_io_handle_read_physical_volume_label(
     libvslvm_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcdata_array_t *data_area_descriptors_array,
     libcdata_array_t *metadata_area_descriptors_array,
     libcerror_error_t **error )
{
	vslvm_data_area_descriptor_t data_area_descriptor_data;
	vslvm_physical_volume_label_header_t physical_volume_label_header;
	vslvm_physical_volume_header_t physical_volume_header;

	libvslvm_data_area_descriptor_t *data_area_descriptor = NULL;
	static char *function                                 = "libvslvm_io_handle_read_physical_volume_label";
	ssize_t read_count                                    = 0;
	uint64_t offset                                       = 0;
	uint64_t size                                         = 0;
	int entry_index                                       = 0;
	int result                                            = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                                  = 0;
	uint32_t value_32bit                                  = 0;
#endif

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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading physical volume label at offset: %" PRIi64 "\n",
		 function,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
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
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
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
		 "%s: signature\t\t: %c%c%c%c%c%c%c%c\n",
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
		 "%s: sector number\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint32_little_endian(
		 physical_volume_label_header.checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 physical_volume_label_header.data_offset,
		 value_32bit );
		libcnotify_printf(
		 "%s: data offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: type indicator\t\t: %c%c%c%c%c%c%c%c\n",
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

	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
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
		 "%s: identifier\t\t: %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
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
		 "%s: volume size\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	do
	{
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
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
				 "%s: offset\t\t\t: 0x%08" PRIx64 "\n",
				 function,
				 offset );

				libcnotify_printf(
				 "%s: size\t\t\t: %" PRIu64 "\n",
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
			     data_area_descriptors_array,
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
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
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
				 "%s: offset\t\t\t: 0x%08" PRIx64 "\n",
				 function,
				 offset );

				libcnotify_printf(
				 "%s: size\t\t\t: %" PRIu64 "\n",
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
			     metadata_area_descriptors_array,
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
	 metadata_area_descriptors_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_data_area_descriptor_free,
	 NULL );

	libcdata_array_empty(
	 data_area_descriptors_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libvslvm_data_area_descriptor_free,
	 NULL );

	return( -1 );
}

