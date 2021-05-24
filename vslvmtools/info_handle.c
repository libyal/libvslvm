/*
 * Info handle
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
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "byte_size_string.h"
#include "info_handle.h"
#include "vslvmtools_libbfio.h"
#include "vslvmtools_libcerror.h"
#include "vslvmtools_libclocale.h"
#include "vslvmtools_libvslvm.h"

#if !defined( LIBVSLVM_HAVE_BFIO )

LIBVSLVM_EXTERN \
int libvslvm_handle_open_file_io_handle(
     libvslvm_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvslvm_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_handle_open_physical_volume_files_file_io_pool(
     libvslvm_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );

#endif /* !defined( LIBVSLVM_HAVE_BFIO ) */

#define INFO_HANDLE_NOTIFY_STREAM		stdout

/* Copies a string of a decimal value to a 64-bit value
 * Returns 1 if successful or -1 on error
 */
int vslvmtools_system_string_copy_from_64_bit_in_decimal(
     const system_character_t *string,
     size_t string_size,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	static char *function              = "vslvmtools_system_string_copy_from_64_bit_in_decimal";
	size_t string_index                = 0;
	system_character_t character_value = 0;
	uint8_t maximum_string_index       = 20;
	int8_t sign                        = 1;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	*value_64bit = 0;

	if( string[ string_index ] == (system_character_t) '-' )
	{
		string_index++;
		maximum_string_index++;

		sign = -1;
	}
	else if( string[ string_index ] == (system_character_t) '+' )
	{
		string_index++;
		maximum_string_index++;
	}
	while( string_index < string_size )
	{
		if( string[ string_index ] == 0 )
		{
			break;
		}
		if( string_index > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		*value_64bit *= 10;

		if( ( string[ string_index ] >= (system_character_t) '0' )
		 && ( string[ string_index ] <= (system_character_t) '9' ) )
		{
			character_value = (system_character_t) ( string[ string_index ] - (system_character_t) '0' );
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: %" PRIc_SYSTEM " at index: %d.",
			 function,
			 string[ string_index ],
			 string_index );

			return( -1 );
		}
		*value_64bit += character_value;

		string_index++;
	}
	if( sign == -1 )
	{
		*value_64bit *= (uint64_t) -1;
	}
	return( 1 );
}

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		memory_free(
		 *info_handle );

		*info_handle = NULL;

		return( -1 );
	}
/* TODO control maximum number of handles */
	if( libbfio_pool_initialize(
	     &( ( *info_handle )->physical_volume_file_io_pool ),
	     0,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize physical volume file IO pool.",
		 function );

		goto on_error;
	}
	if( libvslvm_handle_initialize(
	     &( ( *info_handle )->input_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input handle.",
		 function );

		goto on_error;
	}
	( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->physical_volume_file_io_pool != NULL )
		{
			libbfio_pool_free(
			 &( ( *info_handle )->physical_volume_file_io_pool ),
			 NULL );
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( libvslvm_handle_free(
		     &( ( *info_handle )->input_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input handle.",
			 function );

			result = -1;
		}
		if( libbfio_pool_free(
		     &( ( *info_handle )->physical_volume_file_io_pool ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free physical volume file IO pool.",
			 function );

			result = -1;
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	info_handle->abort = 1;

	if( info_handle->input_handle != NULL )
	{
		if( libvslvm_handle_signal_abort(
		     info_handle->input_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input handle to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the volume offset
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_volume_offset(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "info_handle_set_volume_offset";
	size_t string_length  = 0;
	uint64_t value_64bit  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( vslvmtools_system_string_copy_from_64_bit_in_decimal(
	     string,
	     string_length + 1,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy string to 64-bit decimal.",
		 function );

		return( -1 );
	}
	info_handle->volume_offset = (off64_t) value_64bit;

	return( 1 );
}

/* Opens the input
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "info_handle_open_input";
	size_t filename_length           = 0;
	int entry_index                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libbfio_file_range_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file IO handle.",
		 function );

		goto on_error;
	}
	filename_length = system_string_length(
	                   filename );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_file_range_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#else
	if( libbfio_file_range_set_name(
	     file_io_handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open set file name.",
		 function );

		goto on_error;
	}
	if( libbfio_file_range_set(
	     file_io_handle,
	     info_handle->volume_offset,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open set volume offset.",
		 function );

		goto on_error;
	}
	if( libvslvm_handle_open_file_io_handle(
	     info_handle->input_handle,
	     file_io_handle,
	     LIBVSLVM_OPEN_READ,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input handle.",
		 function );

		goto on_error;
	}
	if( libbfio_pool_append_handle(
	     info_handle->physical_volume_file_io_pool,
	     &entry_index,
	     file_io_handle,
	     LIBBFIO_OPEN_READ,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input handle.",
		 function );

		goto on_error;
	}
	/* The takes over management of the file IO handle
	 */
	file_io_handle = NULL;

/* TODO determine if the first file is a metadata only file and change filenames accordingly
 */
	if( libvslvm_handle_open_physical_volume_files_file_io_pool(
	     info_handle->input_handle,
	     info_handle->physical_volume_file_io_pool,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open physical volume files.",
		 function );

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

/* Closes the input
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvslvm_handle_close(
	     info_handle->input_handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input handle.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the volume group information
 * Returns 1 if successful or -1 on error
 */
int info_handle_volume_group_fprint(
     info_handle_t *info_handle,
     libvslvm_volume_group_t *volume_group,
     libcerror_error_t **error )
{
	system_character_t extent_size_string[ 16 ];

	libvslvm_logical_volume_t *logical_volume   = NULL;
	libvslvm_physical_volume_t *physical_volume = NULL;
	static char *function                       = "info_handle_volume_group_fprint";
	char *value_string                          = NULL;
	size64_t extent_size                        = 0;
	size_t value_string_size                    = 0;
	uint32_t value_32bit                        = 0;
	int number_of_logical_volumes               = 0;
	int number_of_physical_volumes              = 0;
	int result                                  = 0;
	int volume_index                            = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Volume Group (VG):\n" );

	if( libvslvm_volume_group_get_name_size(
	     volume_group,
	     &value_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name size.",
		 function );

		goto on_error;
	}
	else if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent value string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = narrow_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create name string.",
			 function );

			goto on_error;
		}
		if( libvslvm_volume_group_get_name(
		     volume_group,
		     value_string,
		     value_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve name.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tName:\t\t\t\t\t%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libvslvm_volume_group_get_identifier_size(
	     volume_group,
	     &value_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier size.",
		 function );

		goto on_error;
	}
	else if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent value string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = narrow_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create identifier string.",
			 function );

			goto on_error;
		}
		if( libvslvm_volume_group_get_identifier(
		     volume_group,
		     value_string,
		     value_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve identifier.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tIdentifier:\t\t\t\t%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libvslvm_volume_group_get_sequence_number(
	     volume_group,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrive sequence number.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tSequence number:\t\t\t%" PRIu32 "\n",
	 value_32bit );

	if( libvslvm_volume_group_get_extent_size(
	     volume_group,
	     &extent_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve extent size.",
		 function );

		goto on_error;
	}
	result = byte_size_string_create(
	          extent_size_string,
	          16,
	          extent_size,
	          BYTE_SIZE_STRING_UNIT_MEBIBYTE,
	          NULL );

	if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tExtent size:\t\t\t\t%" PRIs_SYSTEM " (%" PRIu64 " bytes)\n",
		 extent_size_string,
		 extent_size );
	}
	else
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tExtent size:\t\t\t\t%" PRIu64 " bytes\n",
		 extent_size );
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
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of physical volumes:\t\t%d\n",
	 number_of_physical_volumes );

	if( libvslvm_volume_group_get_number_of_logical_volumes(
	     volume_group,
	     &number_of_logical_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of logical volumes.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of logical volumes:\t\t%d\n",
	 number_of_logical_volumes );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	for( volume_index = 0;
	     volume_index < number_of_physical_volumes;
	     volume_index++ )
	{
		if( libvslvm_volume_group_get_physical_volume(
		     volume_group,
		     volume_index,
		     &physical_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve physical volume: %d.",
			 function,
			 volume_index );

			goto on_error;
		}
		if( info_handle_physical_volume_fprint(
		     info_handle,
		     volume_index,
		     physical_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print physical volume: %d information.",
			 function,
			 volume_index );

			goto on_error;
		}
		if( libvslvm_physical_volume_free(
		     &physical_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free physical volume: %d.",
			 function,
			 volume_index );

			goto on_error;
		}
	}
	for( volume_index = 0;
	     volume_index < number_of_logical_volumes;
	     volume_index++ )
	{
		if( libvslvm_volume_group_get_logical_volume(
		     volume_group,
		     volume_index,
		     &logical_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve logical volume: %d.",
			 function,
			 volume_index );

			goto on_error;
		}
		if( info_handle_logical_volume_fprint(
		     info_handle,
		     volume_index,
		     logical_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print logical volume: %d information.",
			 function,
			 volume_index );

			goto on_error;
		}
		if( libvslvm_logical_volume_free(
		     &logical_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free logical volume: %d.",
			 function,
			 volume_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( logical_volume != NULL )
	{
		libvslvm_logical_volume_free(
		 &logical_volume,
		 NULL );
	}
	if( physical_volume != NULL )
	{
		libvslvm_physical_volume_free(
		 &physical_volume,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the physcial volume information
 * Returns 1 if successful or -1 on error
 */
int info_handle_physical_volume_fprint(
     info_handle_t *info_handle,
     int physical_volume_index,
     libvslvm_physical_volume_t *physical_volume,
     libcerror_error_t **error )
{
	system_character_t volume_size_string[ 16 ];

	static char *function    = "info_handle_physical_volume_fprint";
	char *value_string       = NULL;
	size64_t volume_size     = 0;
	size_t value_string_size = 0;
	int result               = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Physical Volume (PV): %d\n",
	 physical_volume_index + 1 );

	if( libvslvm_physical_volume_get_name_size(
	     physical_volume,
	     &value_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name size.",
		 function );

		goto on_error;
	}
	else if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent value string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = narrow_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create name string.",
			 function );

			goto on_error;
		}
		if( libvslvm_physical_volume_get_name(
		     physical_volume,
		     value_string,
		     value_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve name.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tName:\t\t\t\t\t%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libvslvm_physical_volume_get_identifier_size(
	     physical_volume,
	     &value_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier size.",
		 function );

		goto on_error;
	}
	else if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent value string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = narrow_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create identifier string.",
			 function );

			goto on_error;
		}
		if( libvslvm_physical_volume_get_identifier(
		     physical_volume,
		     value_string,
		     value_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve identifier.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tIdentifier:\t\t\t\t%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libvslvm_physical_volume_get_device_path_size(
	     physical_volume,
	     &value_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve device path size.",
		 function );

		goto on_error;
	}
	else if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent value string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = narrow_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create device path string.",
			 function );

			goto on_error;
		}
		if( libvslvm_physical_volume_get_device_path(
		     physical_volume,
		     value_string,
		     value_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve device path.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tDevice path:\t\t\t\t%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libvslvm_physical_volume_get_size(
	     physical_volume,
	     &volume_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size.",
		 function );

		goto on_error;
	}
	result = byte_size_string_create(
	          volume_size_string,
	          16,
	          volume_size,
	          BYTE_SIZE_STRING_UNIT_MEBIBYTE,
	          NULL );

	if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tVolume size:\t\t\t\t%" PRIs_SYSTEM " (%" PRIu64 " bytes)\n",
		 volume_size_string,
		 volume_size );
	}
	else
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tVolume size:\t\t\t\t%" PRIu64 " bytes\n",
		 volume_size );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the logical volume information
 * Returns 1 if successful or -1 on error
 */
int info_handle_logical_volume_fprint(
     info_handle_t *info_handle,
     int logical_volume_index,
     libvslvm_logical_volume_t *logical_volume,
     libcerror_error_t **error )
{
	libvslvm_segment_t *segment = NULL;
	static char *function       = "info_handle_logical_volume_fprint";
	char *value_string          = NULL;
	size_t value_string_size    = 0;
	int number_of_segments      = 0;
	int segment_index           = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Logical Volume (LV): %d\n",
	 logical_volume_index + 1 );

	if( libvslvm_logical_volume_get_name_size(
	     logical_volume,
	     &value_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name size.",
		 function );

		goto on_error;
	}
	else if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent value string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = narrow_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create name string.",
			 function );

			goto on_error;
		}
		if( libvslvm_logical_volume_get_name(
		     logical_volume,
		     value_string,
		     value_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve name.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tName:\t\t\t\t\t%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libvslvm_logical_volume_get_identifier_size(
	     logical_volume,
	     &value_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier size.",
		 function );

		goto on_error;
	}
	else if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent value string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = narrow_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create identifier string.",
			 function );

			goto on_error;
		}
		if( libvslvm_logical_volume_get_identifier(
		     logical_volume,
		     value_string,
		     value_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve identifier.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tIdentifier:\t\t\t\t%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libvslvm_logical_volume_get_number_of_segments(
	     logical_volume,
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
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of segments:\t\t\t%d\n",
	 number_of_segments );

	for( segment_index = 0;
	     segment_index < number_of_segments;
	     segment_index++ )
	{
		if( libvslvm_logical_volume_get_segment(
		     logical_volume,
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
		if( info_handle_segment_fprint(
		     info_handle,
		     segment_index,
		     segment,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print segment: %d information.",
			 function,
			 segment_index );

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
	}
	return( 1 );

on_error:
	if( segment != NULL )
	{
		libvslvm_segment_free(
		 &segment,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the segment information
 * Returns 1 if successful or -1 on error
 */
int info_handle_segment_fprint(
     info_handle_t *info_handle,
     int segment_index,
     libvslvm_segment_t *segment,
     libcerror_error_t **error )
{
	system_character_t segment_size_string[ 16 ];

	libvslvm_stripe_t *stripe = NULL;
	static char *function     = "info_handle_segment_fprint";
	off64_t segment_offset    = 0;
	size64_t segment_size     = 0;
	int number_of_stripes     = 0;
	int result                = 0;
	int stripe_index          = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tSegment: %d\n",
	 segment_index + 1 );

	if( libvslvm_segment_get_offset(
	     segment,
	     &segment_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\t\tOffset:\t\t\t\t0x%08" PRIx64 " (%" PRIi64 ")\n",
	 segment_offset,
	 segment_offset );

	if( libvslvm_segment_get_size(
	     segment,
	     &segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size.",
		 function );

		goto on_error;
	}
	result = byte_size_string_create(
	          segment_size_string,
	          16,
	          segment_size,
	          BYTE_SIZE_STRING_UNIT_MEBIBYTE,
	          NULL );

	if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\tSize:\t\t\t\t%" PRIs_SYSTEM " (%" PRIu64 " bytes)\n",
		 segment_size_string,
		 segment_size );
	}
	else
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\tSize:\t\t\t\t%" PRIu64 " bytes\n",
		 segment_size );
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
	fprintf(
	 info_handle->notify_stream,
	 "\t\tNumber of stripes:\t\t%d\n",
	 number_of_stripes );

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
		if( info_handle_stripe_fprint(
		     info_handle,
		     stripe_index,
		     stripe,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print stripe: %d information.",
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
	}
	return( 1 );

on_error:
	if( stripe != NULL )
	{
		libvslvm_stripe_free(
		 &stripe,
		 NULL );
	}
	return( -1 );
}

/* Prints the stripe information
 * Returns 1 if successful or -1 on error
 */
int info_handle_stripe_fprint(
     info_handle_t *info_handle,
     int stripe_index,
     libvslvm_stripe_t *stripe,
     libcerror_error_t **error )
{
	static char *function    = "info_handle_stripe_fprint";
	char *value_string       = NULL;
	size_t value_string_size = 0;
	off64_t data_area_offset = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\t\tStripe: %d\n",
	 stripe_index + 1 );

	if( libvslvm_stripe_get_physical_volume_name_size(
	     stripe,
	     &value_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve physical volume name size.",
		 function );

		goto on_error;
	}
	else if( value_string_size > 0 )
	{
		if( value_string_size > (size_t) SSIZE_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid parent value string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = narrow_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create physical volume name string.",
			 function );

			goto on_error;
		}
		if( libvslvm_stripe_get_physical_volume_name(
		     stripe,
		     value_string,
		     value_string_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve physical volume name.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\t\t\tPhysical volume:\t%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libvslvm_stripe_get_data_area_offset(
	     stripe,
	     &data_area_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data area offset.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\t\t\tData area offset:\t0x%08" PRIx64 " (%" PRIi64 ")\n",
	 data_area_offset,
	 data_area_offset );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the information
 * Returns 1 if successful or -1 on error
 */
int info_handle_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libvslvm_volume_group_t *volume_group = NULL;
	static char *function                 = "info_handle_fprint";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Linux Logical Volume Manager (LVM) information:\n" );

	if( libvslvm_handle_get_volume_group(
	     info_handle->input_handle,
	     &volume_group,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve volume group.",
		 function );

		goto on_error;
	}
	if( info_handle_volume_group_fprint(
	     info_handle,
	     volume_group,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print volume group information.",
		 function );

		goto on_error;
	}
	if( libvslvm_volume_group_free(
	     &volume_group,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free volume group.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( volume_group != NULL )
	{
		libvslvm_volume_group_free(
		 &volume_group,
		 NULL );
	}
	return( -1 );
}

