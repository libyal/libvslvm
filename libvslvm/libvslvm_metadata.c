/*
 * The metadata functions
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
#include <narrow_string.h>
#include <types.h>

#include "libvslvm_checksum.h"
#include "libvslvm_definitions.h"
#include "libvslvm_libbfio.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libcnotify.h"
#include "libvslvm_libcsplit.h"
#include "libvslvm_libfvalue.h"
#include "libvslvm_logical_volume_values.h"
#include "libvslvm_metadata.h"
#include "libvslvm_physical_volume.h"
#include "libvslvm_raw_location_descriptor.h"
#include "libvslvm_segment.h"
#include "libvslvm_stripe.h"
#include "libvslvm_volume_group.h"

/* Creates a metadata
 * Make sure the value metadata is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_metadata_initialize(
     libvslvm_metadata_t **metadata,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_metadata_initialize";

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( *metadata != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid metadata value already set.",
		 function );

		return( -1 );
	}
	*metadata = memory_allocate_structure(
	             libvslvm_metadata_t );

	if( *metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create metadata.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *metadata,
	     0,
	     sizeof( libvslvm_metadata_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear metadata.",
		 function );

		memory_free(
		 *metadata );

		*metadata = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *metadata != NULL )
	{
		memory_free(
		 *metadata );

		*metadata = NULL;
	}
	return( -1 );
}

/* Frees a metadata
 * Returns 1 if successful or -1 on error
 */
int libvslvm_metadata_free(
     libvslvm_metadata_t **metadata,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_metadata_free";
	int result            = 1;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( *metadata != NULL )
	{
		if( ( *metadata )->volume_group != NULL )
		{
			if( libvslvm_internal_volume_group_free(
			     (libvslvm_internal_volume_group_t **) &( ( *metadata )->volume_group ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free volume group.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *metadata );

		*metadata = NULL;
	}
	return( result );
}

/* Reads the metadata
 * Returns 1 if successful or -1 on error
 */
int libvslvm_metadata_read_data(
     libvslvm_metadata_t *metadata,
     const uint8_t *data,
     size_t data_size,
     uint32_t stored_checksum,
     libcerror_error_t **error )
{
	libcsplit_narrow_split_string_t *lines = NULL;
	static char *function                  = "libvslvm_metadata_read_data";
	uint32_t calculated_checksum           = 0;
	int line_index                         = 0;
	int number_of_lines                    = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size == 0 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( libvslvm_checksum_calculate_weak_crc32(
	     &calculated_checksum,
	     data,
	     data_size,
	     0xf597a6cfUL,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to calculate CRC-32.",
		 function );

		goto on_error;
	}
	if( ( stored_checksum != 0 )
	 && ( stored_checksum != calculated_checksum ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_INPUT,
		 LIBCERROR_INPUT_ERROR_CHECKSUM_MISMATCH,
		 "%s: mismatch in checksum ( 0x%08" PRIx32 " != 0x%08" PRIx32 " ).",
		 function,
		 stored_checksum,
		 calculated_checksum );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: metadata:\n%s",
		 function,
		 data );
	}
#endif
	if( libcsplit_narrow_string_split(
	     (char *) data,
	     data_size,
	     '\n',
	     &lines,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to split data into lines.",
		 function );

		goto on_error;
	}
	if( libcsplit_narrow_split_string_get_number_of_segments(
	     lines,
	     &number_of_lines,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to retrieve number of lines.",
		 function );

		goto on_error;
	}
	if( libvslvm_metadata_read_volume_group(
	     metadata,
	     lines,
	     number_of_lines,
	     &line_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read volume group.",
		 function );

		goto on_error;
	}
	if( libcsplit_narrow_split_string_free(
	     &lines,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free lines.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( lines != NULL )
	{
		libcsplit_narrow_split_string_free(
		 &lines,
		 NULL );
	}
	return( -1 );
}

/* Reads the metadata
 * Returns 1 if successful or -1 on error
 */
int libvslvm_metadata_read_file_io_handle(
     libvslvm_metadata_t *metadata,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     size64_t metadata_size,
     uint32_t stored_checksum,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libvslvm_metadata_read_file_io_handle";
	ssize_t read_count    = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( ( metadata_size == 0 )
	 || ( metadata_size > (size64_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid metadata size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading metadata at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	data = (uint8_t *) memory_allocate(
	                    (size_t) metadata_size );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              (size_t) metadata_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) metadata_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read metadata at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libvslvm_metadata_read_data(
	     metadata,
	     data,
	     (size_t) metadata_size,
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
	memory_free(
	 data );

	return( 1 );

on_error:
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

/* Reads the volume group
 * Returns the 1 if succesful or -1 on error
 */
int libvslvm_metadata_read_volume_group(
     libvslvm_metadata_t *metadata,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	char *line_string_segment                               = NULL;
	char *value                                             = NULL;
	char *value_identifier                                  = NULL;
	static char *function                                   = "libvslvm_metadata_read_volume_group";
	size_t line_string_segment_index                        = 0;
	size_t line_string_segment_size                         = 0;
	size_t value_identifier_length                          = 0;
	size_t value_length                                     = 0;
	uint64_t value_64bit                                    = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( metadata->volume_group != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid metadata - volume group value already set.",
		 function );

		return( -1 );
	}
	if( line_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid line index.",
		 function );

		return( -1 );
	}
	if( number_of_lines <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of lines value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( *line_index < 0 )
	 || ( *line_index >= number_of_lines ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcsplit_narrow_split_string_get_segment_by_index(
	     lines,
	     *line_index,
	     &line_string_segment,
	     &line_string_segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve line: %d.",
		 function,
		 *line_index );

		goto on_error;
	}
	if( line_string_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing line string segment: %d.",
		 function,
		 *line_index );

		goto on_error;
	}
	/* Ignore trailing white space
	 */
	if( line_string_segment_size >= 2 )
	{
		line_string_segment_index = line_string_segment_size - 2;

		while( line_string_segment_index > 0 )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index--;
			line_string_segment_size--;
		}
	}
	/* Ignore leading white space
	 */
	line_string_segment_index = 0;

	while( line_string_segment_index < line_string_segment_size )
	{
		if( ( line_string_segment[ line_string_segment_index ] != '\t' )
		 && ( line_string_segment[ line_string_segment_index ] != '\n' )
		 && ( line_string_segment[ line_string_segment_index ] != '\f' )
		 && ( line_string_segment[ line_string_segment_index ] != '\v' )
		 && ( line_string_segment[ line_string_segment_index ] != '\r' )
		 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
		{
			break;
		}
		line_string_segment_index++;
	}
	if( ( line_string_segment_size < 3 )
	 || ( line_string_segment[ line_string_segment_size - 3 ] != ' ' )
	 || ( line_string_segment[ line_string_segment_size - 2 ] != '{' ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported volume group signature.",
		 function );

		goto on_error;
	}
	if( libvslvm_volume_group_initialize(
	     &( metadata->volume_group ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create volume group.",
		 function );

		goto on_error;
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) metadata->volume_group;

	if( ( line_string_segment_size < 2 )
	 || ( line_string_segment_index >= ( line_string_segment_size - 2 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line string segment size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libvslvm_internal_volume_group_set_name(
	     (libvslvm_internal_volume_group_t *) metadata->volume_group,
	     &( line_string_segment[ line_string_segment_index ] ),
	     line_string_segment_size - ( line_string_segment_index + 2 ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set volume group name.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: name\t\t\t\t: %s\n",
		 function,
		 internal_volume_group->name );
	}
#endif
	*line_index += 1;

	while( *line_index < number_of_lines )
	{
		if( libcsplit_narrow_split_string_get_segment_by_index(
		     lines,
		     *line_index,
		     &line_string_segment,
		     &line_string_segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve line: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		if( line_string_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing line string segment: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		/* Ignore trailing white space
		 */
		if( line_string_segment_size >= 2 )
		{
			line_string_segment_index = line_string_segment_size - 2;

			while( line_string_segment_index > 0 )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index--;
				line_string_segment_size--;
			}
		}
		/* Ignore leading white space
		 */
		line_string_segment_index = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		/* Skip an empty line
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Check for the end of section
		 */
		if( ( ( line_string_segment_size - line_string_segment_index ) == 2 )
		 && ( line_string_segment[ line_string_segment_index ] == '}' ) )
		{
			*line_index += 1;

			break;
		}
		/* Check for the start of a sub section
		 */
		if( ( line_string_segment_size - line_string_segment_index ) == 18 )
		{
			if( narrow_string_compare(
			     &( line_string_segment[ line_string_segment_index ] ),
			     "logical_volumes {",
			     17 ) == 0 )
			{
				if( libvslvm_metadata_read_logical_volumes(
				     metadata,
				     metadata->volume_group,
				     lines,
				     number_of_lines,
				     line_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read logical volumes.",
					 function );

					goto on_error;
				}
				continue;
			}
		}
		else if( ( line_string_segment_size - line_string_segment_index ) == 19 )
		{
			if( narrow_string_compare(
			     &( line_string_segment[ line_string_segment_index ] ),
			     "physical_volumes {",
			     18 ) == 0 )
			{
				if( libvslvm_metadata_read_physical_volumes(
				     metadata,
				     metadata->volume_group,
				     lines,
				     number_of_lines,
				     line_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read physical volumes.",
					 function );

					goto on_error;
				}
				continue;
			}
		}
		/* Determine the value identifier
		 */
		value_identifier        = &( line_string_segment[ line_string_segment_index ] );
		value_identifier_length = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] == '\t' )
			 || ( line_string_segment[ line_string_segment_index ] == '\n' )
			 || ( line_string_segment[ line_string_segment_index ] == '\f' )
			 || ( line_string_segment[ line_string_segment_index ] == '\v' )
			 || ( line_string_segment[ line_string_segment_index ] == '\r' )
			 || ( line_string_segment[ line_string_segment_index ] == ' ' )
			 || ( line_string_segment[ line_string_segment_index ] == '=' ) )
			{
				break;
			}
			value_identifier_length++;

			line_string_segment_index++;
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Make sure the value identifier is terminated by an end of string
		 */
		line_string_segment[ line_string_segment_index ] = 0;

		line_string_segment_index++;

		/* Ignore whitespace
		 */
		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		if( line_string_segment[ line_string_segment_index ] == '=' )
		{
			line_string_segment_index++;

			while( line_string_segment_index < line_string_segment_size )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index++;
			}
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Determine the value
		 */
		value        = &( line_string_segment[ line_string_segment_index ] );
		value_length = line_string_segment_size - 1;

		/* Ingore quotes at the beginning of the value data
		 */
		if( ( line_string_segment[ line_string_segment_index ] == '"' )
		 || ( line_string_segment[ line_string_segment_index ] == '\'' ) )
		{
			line_string_segment_index++;
			value++;
			value_length--;
		}
		/* Ingore quotes at the end of the value data
		 */
		if( ( line_string_segment[ value_length - 1 ] == '"' )
		 || ( line_string_segment[ value_length - 1 ] == '\'' ) )
		{
			value_length--;
		}
		/* Make sure the value is terminated by an end of string
		 */
		line_string_segment[ value_length ] = 0;

		value_length -= line_string_segment_index;

		if( value_identifier_length == 2 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "id",
			     2 ) == 0 )
			{
				if( libvslvm_volume_group_set_identifier(
				     metadata->volume_group,
				     value,
				     value_length + 1,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set volume group identifier.",
					 function );

					goto on_error;
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: identifier\t\t\t\t: %s\n",
					 function,
					 internal_volume_group->identifier );
				}
#endif
			}
		}
		else if( value_identifier_length == 5 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "flags",
			     5 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: flags\t\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
			else if( narrow_string_compare(
			          value_identifier,
			          "seqno",
			          5 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: sequence number\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
				if( libfvalue_utf8_string_copy_to_integer(
				     (uint8_t *) value,
				     value_length + 1,
				     &value_64bit,
				     32,
				     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set sequence number.",
					 function );

					goto on_error;
				}
				if( value_64bit > (uint64_t) UINT32_MAX )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid sequence number value exceeds maximum.",
					 function );

					goto on_error;
				}
				internal_volume_group->sequence_number = (uint32_t) value_64bit;
			}
		}
		else if( value_identifier_length == 6 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "max_lv",
			     6 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: max_lv\t\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
			else if( narrow_string_compare(
			          value_identifier,
			          "max_pv",
			          6 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: max_pv\t\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
			else if( narrow_string_compare(
			          value_identifier,
			          "status",
			          6 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: status flags\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
		}
		else if( value_identifier_length == 11 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "extent_size",
			     11 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: extent size\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
				if( libfvalue_utf8_string_copy_to_integer(
				     (uint8_t *) value,
				     value_length + 1,
				     &value_64bit,
				     64,
				     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set extent size.",
					 function );

					goto on_error;
				}
				if( value_64bit > (uint64_t) ( UINT64_MAX / 512 ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid extent size value exceeds maximum.",
					 function );

					goto on_error;
				}
				value_64bit *= 512;

				internal_volume_group->extent_size = value_64bit;
			}
		}
		else if( value_identifier_length == 15 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "metadata_copies",
			     15 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: metadata copies\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		else if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %d\t\t\t: %s = %s\n",
			 function,
			 *line_index,
			 value_identifier,
			 value );
		}
#endif
		*line_index += 1;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( metadata->volume_group != NULL )
	{
		libvslvm_internal_volume_group_free(
		 (libvslvm_internal_volume_group_t **) &( metadata->volume_group ),
		 NULL );
	}
	return( -1 );
}

/* Reads the physical volumes
 * Returns the 1 if succesful or -1 on error
 */
int libvslvm_metadata_read_physical_volumes(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t *volume_group,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error )
{
	char *line_string_segment        = NULL;
	static char *function            = "libvslvm_metadata_read_physical_volumes";
	size_t line_string_segment_index = 0;
	size_t line_string_segment_size  = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( line_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid line index.",
		 function );

		return( -1 );
	}
	if( number_of_lines <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of lines value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( *line_index < 0 )
	 || ( *line_index >= number_of_lines ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcsplit_narrow_split_string_get_segment_by_index(
	     lines,
	     *line_index,
	     &line_string_segment,
	     &line_string_segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve line: %d.",
		 function,
		 *line_index );

		return( -1 );
	}
	if( line_string_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing line string segment: %d.",
		 function,
		 *line_index );

		return( -1 );
	}
	/* Ignore trailing white space
	 */
	if( line_string_segment_size >= 2 )
	{
		line_string_segment_index = line_string_segment_size - 2;

		while( line_string_segment_index > 0 )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index--;
			line_string_segment_size--;
		}
	}
	/* Ignore leading white space
	 */
	line_string_segment_index = 0;

	while( line_string_segment_index < line_string_segment_size )
	{
		if( ( line_string_segment[ line_string_segment_index ] != '\t' )
		 && ( line_string_segment[ line_string_segment_index ] != '\n' )
		 && ( line_string_segment[ line_string_segment_index ] != '\f' )
		 && ( line_string_segment[ line_string_segment_index ] != '\v' )
		 && ( line_string_segment[ line_string_segment_index ] != '\r' )
		 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
		{
			break;
		}
		line_string_segment_index++;
	}
	if( ( ( line_string_segment_size - line_string_segment_index ) != 19 )
	 || ( narrow_string_compare(
	       &( line_string_segment[ line_string_segment_index ] ),
	       "physical_volumes {",
	       18 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported physical volumes signature.",
		 function );

		return( -1 );
	}
	*line_index += 1;

	while( *line_index < number_of_lines )
	{
		if( libcsplit_narrow_split_string_get_segment_by_index(
		     lines,
		     *line_index,
		     &line_string_segment,
		     &line_string_segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve line: %d.",
			 function,
			 *line_index );

			return( -1 );
		}
		if( line_string_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing line string segment: %d.",
			 function,
			 *line_index );

			return( -1 );
		}
		/* Ignore trailing white space
		 */
		if( line_string_segment_size >= 2 )
		{
			line_string_segment_index = line_string_segment_size - 2;

			while( line_string_segment_index > 0 )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index--;
				line_string_segment_size--;
			}
		}
		/* Ignore leading white space
		 */
		line_string_segment_index = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		/* Skip an empty line
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Check for the end of section
		 */
		if( ( ( line_string_segment_size - line_string_segment_index ) == 2 )
		 && ( line_string_segment[ line_string_segment_index ] == '}' ) )
		{
			*line_index += 1;

			break;
		}
		/* Check for the start of a sub section
		 */
		if( ( line_string_segment_size >= 3 )
		 && ( line_string_segment[ line_string_segment_size - 3 ] == ' ' )
		 && ( line_string_segment[ line_string_segment_size - 2 ] == '{' ) )
		{
			if( libvslvm_metadata_read_physical_volume(
			     metadata,
			     volume_group,
			     lines,
			     number_of_lines,
			     line_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read physical volume.",
				 function );

				return( -1 );
			}
		}
		else
		{
/* TODO debug print other lines ? */
			*line_index += 1;
		}
	}
	return( 1 );
}

/* Reads the physical volume
 * Returns the 1 if succesful or -1 on error
 */
int libvslvm_metadata_read_physical_volume(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t *volume_group,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error )
{
	libvslvm_physical_volume_t *physical_volume = NULL;
	char *line_string_segment                   = NULL;
	char *value                                 = NULL;
	char *value_identifier                      = NULL;
	static char *function                       = "libvslvm_metadata_read_physical_volume";
	size_t line_string_segment_index            = 0;
	size_t line_string_segment_size             = 0;
	size_t value_identifier_length              = 0;
	size_t value_length                         = 0;
	uint64_t value_64bit                        = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
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
	if( line_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid line index.",
		 function );

		return( -1 );
	}
	if( number_of_lines <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of lines value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( *line_index < 0 )
	 || ( *line_index >= number_of_lines ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcsplit_narrow_split_string_get_segment_by_index(
	     lines,
	     *line_index,
	     &line_string_segment,
	     &line_string_segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve line: %d.",
		 function,
		 *line_index );

		goto on_error;
	}
	if( line_string_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing line string segment: %d.",
		 function,
		 *line_index );

		goto on_error;
	}
	/* Ignore trailing white space
	 */
	if( line_string_segment_size >= 2 )
	{
		line_string_segment_index = line_string_segment_size - 2;

		while( line_string_segment_index > 0 )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index--;
			line_string_segment_size--;
		}
	}
	/* Ignore leading white space
	 */
	line_string_segment_index = 0;

	while( line_string_segment_index < line_string_segment_size )
	{
		if( ( line_string_segment[ line_string_segment_index ] != '\t' )
		 && ( line_string_segment[ line_string_segment_index ] != '\n' )
		 && ( line_string_segment[ line_string_segment_index ] != '\f' )
		 && ( line_string_segment[ line_string_segment_index ] != '\v' )
		 && ( line_string_segment[ line_string_segment_index ] != '\r' )
		 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
		{
			break;
		}
		line_string_segment_index++;
	}
	if( ( line_string_segment_size < 3 )
	 || ( line_string_segment[ line_string_segment_size - 3 ] != ' ' )
	 || ( line_string_segment[ line_string_segment_size - 2 ] != '{' ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported physical volume signature.",
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
	if( ( line_string_segment_size < 2 )
	 || ( line_string_segment_index >= ( line_string_segment_size - 2 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line string segment size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libvslvm_physical_volume_set_name(
	     physical_volume,
	     &( line_string_segment[ line_string_segment_index ] ),
	     line_string_segment_size - ( line_string_segment_index + 2 ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set physical volume name.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: name\t\t\t\t: %s\n",
		 function,
		 ( (libvslvm_internal_physical_volume_t *) physical_volume )->name );
	}
#endif
	*line_index += 1;

	while( *line_index < number_of_lines )
	{
		if( libcsplit_narrow_split_string_get_segment_by_index(
		     lines,
		     *line_index,
		     &line_string_segment,
		     &line_string_segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve line: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		if( line_string_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing line string segment: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		/* Ignore trailing white space
		 */
		if( line_string_segment_size >= 2 )
		{
			line_string_segment_index = line_string_segment_size - 2;

			while( line_string_segment_index > 0 )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index--;
				line_string_segment_size--;
			}
		}
		/* Ignore leading white space
		 */
		line_string_segment_index = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		/* Skip an empty line
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Check for the end of section
		 */
		if( ( ( line_string_segment_size - line_string_segment_index ) == 2 )
		 && ( line_string_segment[ line_string_segment_index ] == '}' ) )
		{
			*line_index += 1;

			break;
		}
		/* Determine the value identifier
		 */
		value_identifier        = &( line_string_segment[ line_string_segment_index ] );
		value_identifier_length = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] == '\t' )
			 || ( line_string_segment[ line_string_segment_index ] == '\n' )
			 || ( line_string_segment[ line_string_segment_index ] == '\f' )
			 || ( line_string_segment[ line_string_segment_index ] == '\v' )
			 || ( line_string_segment[ line_string_segment_index ] == '\r' )
			 || ( line_string_segment[ line_string_segment_index ] == ' ' )
			 || ( line_string_segment[ line_string_segment_index ] == '=' ) )
			{
				break;
			}
			value_identifier_length++;

			line_string_segment_index++;
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Make sure the value identifier is terminated by an end of string
		 */
		line_string_segment[ line_string_segment_index ] = 0;

		line_string_segment_index++;

		/* Ignore whitespace
		 */
		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		if( line_string_segment[ line_string_segment_index ] == '=' )
		{
			line_string_segment_index++;

			while( line_string_segment_index < line_string_segment_size )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index++;
			}
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Determine the value
		 */
		value        = &( line_string_segment[ line_string_segment_index ] );
		value_length = line_string_segment_size - 1;

		/* Ingore quotes at the beginning of the value data
		 */
		if( ( line_string_segment[ line_string_segment_index ] == '"' )
		 || ( line_string_segment[ line_string_segment_index ] == '\'' ) )
		{
			line_string_segment_index++;
			value++;
			value_length--;
		}
		/* Ingore quotes at the end of the value data
		 */
		if( ( line_string_segment[ value_length - 1 ] == '"' )
		 || ( line_string_segment[ value_length - 1 ] == '\'' ) )
		{
			value_length--;
		}
		/* Make sure the value is terminated by an end of string
		 */
		line_string_segment[ value_length ] = 0;

		value_length -= line_string_segment_index;

		if( value_identifier_length == 2 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "id",
			     2 ) == 0 )
			{
				if( libvslvm_physical_volume_set_identifier(
				     physical_volume,
				     value,
				     value_length + 1,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set physical volume identifier.",
					 function );

					goto on_error;
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: identifier\t\t\t: %s\n",
					 function,
					 ( (libvslvm_internal_physical_volume_t *) physical_volume )->identifier );
				}
#endif
			}
		}
		else if( value_identifier_length == 5 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "flags",
			     5 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: flags\t\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
		}
		else if( value_identifier_length == 6 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "device",
			     6 ) == 0 )
			{
				if( libvslvm_physical_volume_set_device_path(
				     physical_volume,
				     value,
				     value_length + 1,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set physical volume device path.",
					 function );

					goto on_error;
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: device path\t\t\t: %s\n",
					 function,
					 ( (libvslvm_internal_physical_volume_t *) physical_volume )->device_path );
				}
#endif
			}
			else if( narrow_string_compare(
			          value_identifier,
			          "status",
			          6 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: status flags\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}

		}
		else if( value_identifier_length == 8 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "dev_size",
			     8 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: volume size\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
				if( libfvalue_utf8_string_copy_to_integer(
				     (uint8_t *) value,
				     value_length + 1,
				     &value_64bit,
				     64,
				     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set volume size.",
					 function );

					goto on_error;
				}
				if( value_64bit > (uint64_t) ( UINT64_MAX / 512 ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid volume size value exceeds maximum.",
					 function );

					goto on_error;
				}
				value_64bit *= 512;

				( (libvslvm_internal_physical_volume_t *) physical_volume )->size = value_64bit;
			}
			else if( narrow_string_compare(
			          value_identifier,
			          "pe_count",
			          8 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: pe_count\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
			else if( narrow_string_compare(
			          value_identifier,
			          "pe_start",
			          8 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: pe_start\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		else if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %d\t\t\t: %s = %s\n",
			 function,
			 *line_index,
			 value_identifier,
			 value );
		}
#endif
		*line_index += 1;
	}
	if( libvslvm_volume_group_append_physical_volume(
	     volume_group,
	     physical_volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append physical volume to volume group.",
		 function );

		goto on_error;
	}
	physical_volume = NULL;

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

/* Reads the logical volumes
 * Returns the 1 if succesful or -1 on error
 */
int libvslvm_metadata_read_logical_volumes(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t *volume_group,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error )
{
	char *line_string_segment        = NULL;
	static char *function            = "libvslvm_metadata_read_logical_volumes";
	size_t line_string_segment_index = 0;
	size_t line_string_segment_size  = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( line_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid line index.",
		 function );

		return( -1 );
	}
	if( number_of_lines <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of lines value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( *line_index < 0 )
	 || ( *line_index >= number_of_lines ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcsplit_narrow_split_string_get_segment_by_index(
	     lines,
	     *line_index,
	     &line_string_segment,
	     &line_string_segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve line: %d.",
		 function,
		 *line_index );

		return( -1 );
	}
	if( line_string_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing line string segment: %d.",
		 function,
		 *line_index );

		return( -1 );
	}
	/* Ignore trailing white space
	 */
	if( line_string_segment_size >= 2 )
	{
		line_string_segment_index = line_string_segment_size - 2;

		while( line_string_segment_index > 0 )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index--;
			line_string_segment_size--;
		}
	}
	/* Ignore leading white space
	 */
	line_string_segment_index = 0;

	while( line_string_segment_index < line_string_segment_size )
	{
		if( ( line_string_segment[ line_string_segment_index ] != '\t' )
		 && ( line_string_segment[ line_string_segment_index ] != '\n' )
		 && ( line_string_segment[ line_string_segment_index ] != '\f' )
		 && ( line_string_segment[ line_string_segment_index ] != '\v' )
		 && ( line_string_segment[ line_string_segment_index ] != '\r' )
		 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
		{
			break;
		}
		line_string_segment_index++;
	}
	if( ( ( line_string_segment_size - line_string_segment_index ) != 18 )
	 || ( narrow_string_compare(
	       &( line_string_segment[ line_string_segment_index ] ),
	       "logical_volumes {",
	       17 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported logical volumes signature.",
		 function );

		return( -1 );
	}
	*line_index += 1;

	while( *line_index < number_of_lines )
	{
		if( libcsplit_narrow_split_string_get_segment_by_index(
		     lines,
		     *line_index,
		     &line_string_segment,
		     &line_string_segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve line: %d.",
			 function,
			 *line_index );

			return( -1 );
		}
		if( line_string_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing line string segment: %d.",
			 function,
			 *line_index );

			return( -1 );
		}
		/* Ignore trailing white space
		 */
		if( line_string_segment_size >= 2 )
		{
			line_string_segment_index = line_string_segment_size - 2;

			while( line_string_segment_index > 0 )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index--;
				line_string_segment_size--;
			}
		}
		/* Ignore leading white space
		 */
		line_string_segment_index = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		/* Skip an empty line
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Check for the end of section
		 */
		if( ( ( line_string_segment_size - line_string_segment_index ) == 2 )
		 && ( line_string_segment[ line_string_segment_index ] == '}' ) )
		{
			*line_index += 1;

			break;
		}
		/* Check for the start of a sub section
		 */
		if( ( line_string_segment_size >= 3 )
		 && ( line_string_segment[ line_string_segment_size - 3 ] == ' ' )
		 && ( line_string_segment[ line_string_segment_size - 2 ] == '{' ) )
		{
			if( libvslvm_metadata_read_logical_volume(
			     metadata,
			     volume_group,
			     lines,
			     number_of_lines,
			     line_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read logical volume.",
				 function );

				return( -1 );
			}
		}
		else
		{
/* TODO debug print other lines ? */
			*line_index += 1;
		}
	}
	return( 1 );
}

/* Reads the logical volume
 * Returns the 1 if succesful or -1 on error
 */
int libvslvm_metadata_read_logical_volume(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t *volume_group,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error )
{
	libvslvm_logical_volume_values_t *logical_volume_values = NULL;
	char *line_string_segment                               = NULL;
	char *value                                             = NULL;
	char *value_identifier                                  = NULL;
	static char *function                                   = "libvslvm_metadata_read_logical_volume";
	size_t line_string_segment_index                        = 0;
	size_t line_string_segment_size                         = 0;
	size_t value_identifier_length                          = 0;
	size_t value_length                                     = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
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
	if( line_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid line index.",
		 function );

		return( -1 );
	}
	if( number_of_lines <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of lines value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( *line_index < 0 )
	 || ( *line_index >= number_of_lines ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcsplit_narrow_split_string_get_segment_by_index(
	     lines,
	     *line_index,
	     &line_string_segment,
	     &line_string_segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve line: %d.",
		 function,
		 *line_index );

		goto on_error;
	}
	if( line_string_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing line string segment: %d.",
		 function,
		 *line_index );

		goto on_error;
	}
	/* Ignore trailing white space
	 */
	if( line_string_segment_size >= 2 )
	{
		line_string_segment_index = line_string_segment_size - 2;

		while( line_string_segment_index > 0 )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index--;
			line_string_segment_size--;
		}
	}
	/* Ignore leading white space
	 */
	line_string_segment_index = 0;

	while( line_string_segment_index < line_string_segment_size )
	{
		if( ( line_string_segment[ line_string_segment_index ] != '\t' )
		 && ( line_string_segment[ line_string_segment_index ] != '\n' )
		 && ( line_string_segment[ line_string_segment_index ] != '\f' )
		 && ( line_string_segment[ line_string_segment_index ] != '\v' )
		 && ( line_string_segment[ line_string_segment_index ] != '\r' )
		 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
		{
			break;
		}
		line_string_segment_index++;
	}
	if( ( line_string_segment_size < 3 )
	 || ( line_string_segment[ line_string_segment_size - 3 ] != ' ' )
	 || ( line_string_segment[ line_string_segment_size - 2 ] != '{' ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported logical volume signature.",
		 function );

		goto on_error;
	}
	if( libvslvm_logical_volume_values_initialize(
	     &logical_volume_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create logical volume values.",
		 function );

		goto on_error;
	}
	if( ( line_string_segment_size < 2 )
	 || ( line_string_segment_index >= ( line_string_segment_size - 2 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line string segment size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libvslvm_logical_volume_values_set_name(
	     logical_volume_values,
	     &( line_string_segment[ line_string_segment_index ] ),
	     line_string_segment_size - ( line_string_segment_index + 2 ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set logical volume name.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: name\t\t\t\t: %s\n",
		 function,
		 logical_volume_values->name );
	}
#endif
	*line_index += 1;

	while( *line_index < number_of_lines )
	{
		if( libcsplit_narrow_split_string_get_segment_by_index(
		     lines,
		     *line_index,
		     &line_string_segment,
		     &line_string_segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve line: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		if( line_string_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing line string segment: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		/* Ignore trailing white space
		 */
		if( line_string_segment_size >= 2 )
		{
			line_string_segment_index = line_string_segment_size - 2;

			while( line_string_segment_index > 0 )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index--;
				line_string_segment_size--;
			}
		}
		/* Ignore leading white space
		 */
		line_string_segment_index = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		/* Skip an empty line
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Check for the end of section
		 */
		if( ( ( line_string_segment_size - line_string_segment_index ) == 2 )
		 && ( line_string_segment[ line_string_segment_index ] == '}' ) )
		{
			*line_index += 1;

			break;
		}
		/* Check for the start of a sub section
		 */
		if( ( line_string_segment_size >= 3 )
		 && ( line_string_segment[ line_string_segment_size - 3 ] == ' ' )
		 && ( line_string_segment[ line_string_segment_size - 2 ] == '{' )
		 && ( ( line_string_segment_size - line_string_segment_index ) >= 7 )
		 && ( narrow_string_compare(
		       &( line_string_segment[ line_string_segment_index ] ),
		       "segment",
		       7 ) == 0 ) )
		{
			if( libvslvm_metadata_read_segment(
			     metadata,
			     logical_volume_values,
			     lines,
			     number_of_lines,
			     line_index,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read segment.",
				 function );

				goto on_error;
			}
			continue;
		}
		/* Determine the value identifier
		 */
		value_identifier        = &( line_string_segment[ line_string_segment_index ] );
		value_identifier_length = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] == '\t' )
			 || ( line_string_segment[ line_string_segment_index ] == '\n' )
			 || ( line_string_segment[ line_string_segment_index ] == '\f' )
			 || ( line_string_segment[ line_string_segment_index ] == '\v' )
			 || ( line_string_segment[ line_string_segment_index ] == '\r' )
			 || ( line_string_segment[ line_string_segment_index ] == ' ' )
			 || ( line_string_segment[ line_string_segment_index ] == '=' ) )
			{
				break;
			}
			value_identifier_length++;

			line_string_segment_index++;
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Make sure the value identifier is terminated by an end of string
		 */
		line_string_segment[ line_string_segment_index ] = 0;

		line_string_segment_index++;

		/* Ignore whitespace
		 */
		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		if( line_string_segment[ line_string_segment_index ] == '=' )
		{
			line_string_segment_index++;

			while( line_string_segment_index < line_string_segment_size )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index++;
			}
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Determine the value
		 */
		value        = &( line_string_segment[ line_string_segment_index ] );
		value_length = line_string_segment_size - 1;

		/* Ingore quotes at the beginning of the value data
		 */
		if( ( line_string_segment[ line_string_segment_index ] == '"' )
		 || ( line_string_segment[ line_string_segment_index ] == '\'' ) )
		{
			line_string_segment_index++;
			value++;
			value_length--;
		}
		/* Ingore quotes at the end of the value data
		 */
		if( ( line_string_segment[ value_length - 1 ] == '"' )
		 || ( line_string_segment[ value_length - 1 ] == '\'' ) )
		{
			value_length--;
		}
		/* Make sure the value is terminated by an end of string
		 */
		line_string_segment[ value_length ] = 0;

		value_length -= line_string_segment_index;

		if( value_identifier_length == 2 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "id",
			     2 ) == 0 )
			{
				if( libvslvm_logical_volume_values_set_identifier(
				     logical_volume_values,
				     value,
				     value_length + 1,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set logical volume identifier.",
					 function );

					goto on_error;
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: identifier\t\t\t: %s\n",
					 function,
					 logical_volume_values->identifier );
				}
#endif
			}
		}
		else if( value_identifier_length == 5 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "flags",
			     5 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: flags\t\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
		}
		else if( value_identifier_length == 6 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "status",
			     6 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: status flags\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}

		}
		else if( value_identifier_length == 13 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "segment_count",
			     13 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: number of segments\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}

		}
#if defined( HAVE_DEBUG_OUTPUT )
		else if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %d\t\t\t: %s = %s\n",
			 function,
			 *line_index,
			 value_identifier,
			 value );
		}
#endif
		*line_index += 1;
	}
	if( libvslvm_volume_group_append_logical_volume(
	     volume_group,
	     logical_volume_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append logical volume to volume group.",
		 function );

		goto on_error;
	}
	logical_volume_values = NULL;

	return( 1 );

on_error:
	if( logical_volume_values != NULL )
	{
		libvslvm_logical_volume_values_free(
		 &logical_volume_values,
		 NULL );
	}
	return( -1 );
}

/* Reads the segment
 * Returns the 1 if succesful or -1 on error
 */
int libvslvm_metadata_read_segment(
     libvslvm_metadata_t *metadata,
     libvslvm_logical_volume_values_t *logical_volume_values,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	libvslvm_segment_t *segment                             = NULL;
	char *line_string_segment                               = NULL;
	char *value                                             = NULL;
	char *value_identifier                                  = NULL;
	static char *function                                   = "libvslvm_metadata_read_segment";
	size_t line_string_segment_index                        = 0;
	size_t line_string_segment_size                         = 0;
	size_t value_identifier_length                          = 0;
	size_t value_length                                     = 0;
	uint64_t value_64bit                                    = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( metadata->volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid metadata - missing volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) metadata->volume_group;

	if( internal_volume_group->extent_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid volume group - extent size value out of bounds.",
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
	if( line_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid line index.",
		 function );

		return( -1 );
	}
	if( number_of_lines <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of lines value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( *line_index < 0 )
	 || ( *line_index >= number_of_lines ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line index value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcsplit_narrow_split_string_get_segment_by_index(
	     lines,
	     *line_index,
	     &line_string_segment,
	     &line_string_segment_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve line: %d.",
		 function,
		 *line_index );

		goto on_error;
	}
	if( line_string_segment == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing line string segment: %d.",
		 function,
		 *line_index );

		goto on_error;
	}
	/* Ignore trailing white space
	 */
	if( line_string_segment_size >= 2 )
	{
		line_string_segment_index = line_string_segment_size - 2;

		while( line_string_segment_index > 0 )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index--;
			line_string_segment_size--;
		}
	}
	/* Ignore leading white space
	 */
	line_string_segment_index = 0;

	while( line_string_segment_index < line_string_segment_size )
	{
		if( ( line_string_segment[ line_string_segment_index ] != '\t' )
		 && ( line_string_segment[ line_string_segment_index ] != '\n' )
		 && ( line_string_segment[ line_string_segment_index ] != '\f' )
		 && ( line_string_segment[ line_string_segment_index ] != '\v' )
		 && ( line_string_segment[ line_string_segment_index ] != '\r' )
		 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
		{
			break;
		}
		line_string_segment_index++;
	}
	if( ( line_string_segment_size < ( 7 + 3 ) )
	 || ( line_string_segment[ line_string_segment_size - 3 ] != ' ' )
	 || ( line_string_segment[ line_string_segment_size - 2 ] != '{' )
	 || ( narrow_string_compare(
	       &( line_string_segment[ line_string_segment_index ] ),
	       "segment",
	       7 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported segment signature.",
		 function );

		goto on_error;
	}
	if( libvslvm_segment_initialize(
	     &segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create segment.",
		 function );

		goto on_error;
	}
	if( ( line_string_segment_size < 2 )
	 || ( line_string_segment_index >= ( line_string_segment_size - 2 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line string segment size value out of bounds.",
		 function );

		goto on_error;
	}
	if( libvslvm_internal_segment_set_name(
	     (libvslvm_internal_segment_t *) segment,
	     &( line_string_segment[ line_string_segment_index ] ),
	     line_string_segment_size - ( line_string_segment_index + 2 ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set segment name.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: name\t\t\t\t\t: %s\n",
		 function,
		 ( (libvslvm_internal_segment_t *) segment )->name );
	}
#endif
	*line_index += 1;

	while( *line_index < number_of_lines )
	{
		if( libcsplit_narrow_split_string_get_segment_by_index(
		     lines,
		     *line_index,
		     &line_string_segment,
		     &line_string_segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve line: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		if( line_string_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing line string segment: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		/* Ignore trailing white space
		 */
		if( line_string_segment_size >= 2 )
		{
			line_string_segment_index = line_string_segment_size - 2;

			while( line_string_segment_index > 0 )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index--;
				line_string_segment_size--;
			}
		}
		/* Ignore leading white space
		 */
		line_string_segment_index = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		/* Skip an empty line
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Check for the end of section
		 */
		if( ( ( line_string_segment_size - line_string_segment_index ) == 2 )
		 && ( line_string_segment[ line_string_segment_index ] == '}' ) )
		{
			*line_index += 1;

			break;
		}
		/* Determine the value identifier
		 */
		value_identifier        = &( line_string_segment[ line_string_segment_index ] );
		value_identifier_length = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] == '\t' )
			 || ( line_string_segment[ line_string_segment_index ] == '\n' )
			 || ( line_string_segment[ line_string_segment_index ] == '\f' )
			 || ( line_string_segment[ line_string_segment_index ] == '\v' )
			 || ( line_string_segment[ line_string_segment_index ] == '\r' )
			 || ( line_string_segment[ line_string_segment_index ] == ' ' )
			 || ( line_string_segment[ line_string_segment_index ] == '=' ) )
			{
				break;
			}
			value_identifier_length++;

			line_string_segment_index++;
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Make sure the value identifier is terminated by an end of string
		 */
		line_string_segment[ line_string_segment_index ] = 0;

		line_string_segment_index++;

		/* Ignore whitespace
		 */
		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		if( line_string_segment[ line_string_segment_index ] == '=' )
		{
			line_string_segment_index++;

			while( line_string_segment_index < line_string_segment_size )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index++;
			}
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Ingore quotes at the beginning of the value data
		 */
		if( ( line_string_segment[ line_string_segment_index ] == '"' )
		 || ( line_string_segment[ line_string_segment_index ] == '\'' ) )
		{
			line_string_segment_index++;
		}
		/* Determine the value
		 */
		value        = &( line_string_segment[ line_string_segment_index ] );
		value_length = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] == 0 )
			 || ( line_string_segment[ line_string_segment_index ] == '\t' )
			 || ( line_string_segment[ line_string_segment_index ] == '\n' )
			 || ( line_string_segment[ line_string_segment_index ] == '\f' )
			 || ( line_string_segment[ line_string_segment_index ] == '\v' )
			 || ( line_string_segment[ line_string_segment_index ] == '\r' )
			 || ( line_string_segment[ line_string_segment_index ] == '#' ) )
			{
				break;
			}
			line_string_segment_index++;
			value_length++;
		}
		/* Ingore quotes at the end of the value data
		 */
		if( ( line_string_segment[ line_string_segment_index - 1 ] == '"' )
		 || ( line_string_segment[ line_string_segment_index - 1 ] == '\'' ) )
		{
			line_string_segment_index--;
			value_length--;
		}
		/* Make sure the value is terminated by an end of string
		 */
		line_string_segment[ line_string_segment_index ] = 0;

		if( value_identifier_length == 4 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "type",
			     4 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: type\t\t\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
		}
		else if( value_identifier_length == 7 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "stripes",
			     7 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: stripes list:\n",
					 function );
				}
#endif
				if( ( value_length != 1 )
				 || ( value[ 0 ] != '[' )
				 || ( libvslvm_metadata_read_stripes_list(
				       metadata,
				       segment,
				       lines,
				       number_of_lines,
				       line_index,
				       error ) != 1 ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read stripes list.",
					 function );

					goto on_error;
				}
/* TODO validate number of stripes */
			}
		}
		else if( value_identifier_length == 12 )
		{
			if( narrow_string_compare(
			     value_identifier,
			     "extent_count",
			     12 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: number of extents\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
				if( libfvalue_utf8_string_copy_to_integer(
				     (uint8_t *) value,
				     value_length + 1,
				     &value_64bit,
				     64,
				     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set number of extents.",
					 function );

					goto on_error;
				}
				if( value_64bit > (uint64_t) ( UINT64_MAX / internal_volume_group->extent_size ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid number of extents value exceeds maximum.",
					 function );

					goto on_error;
				}
				value_64bit *= internal_volume_group->extent_size;

				( (libvslvm_internal_segment_t *) segment )->size = value_64bit;
			}
			else if( narrow_string_compare(
			          value_identifier,
			          "start_extent",
			          12 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: start extent\t\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
				if( libfvalue_utf8_string_copy_to_integer(
				     (uint8_t *) value,
				     value_length + 1,
				     &value_64bit,
				     64,
				     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set start extent.",
					 function );

					goto on_error;
				}
				if( value_64bit > (uint64_t) ( UINT64_MAX / internal_volume_group->extent_size ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid start extent value exceeds maximum.",
					 function );

					goto on_error;
				}
				value_64bit *= internal_volume_group->extent_size;

				( (libvslvm_internal_segment_t *) segment )->offset = value_64bit;
			}
			else if( narrow_string_compare(
			          value_identifier,
			          "stripe_count",
			          12 ) == 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: number of stripes\t\t\t: %s\n",
					 function,
					 value );
				}
#endif
/* TODO */
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		else if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %d\t\t\t\t: %s = %s\n",
			 function,
			 *line_index,
			 value_identifier,
			 value );
		}
#endif
		*line_index += 1;
	}
	if( libvslvm_logical_volume_values_append_segment(
	     logical_volume_values,
	     segment,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append segment to logical volume values.",
		 function );

		goto on_error;
	}
	segment = NULL;

	return( 1 );

on_error:
	if( segment != NULL )
	{
		libvslvm_internal_segment_free(
		 (libvslvm_internal_segment_t **) &segment,
		 NULL );
	}
	return( -1 );
}

/* Reads the stripes list
 * Returns the 1 if succesful or -1 on error
 */
int libvslvm_metadata_read_stripes_list(
     libvslvm_metadata_t *metadata,
     libvslvm_segment_t *segment,
     libcsplit_narrow_split_string_t *lines,
     int number_of_lines,
     int *line_index,
     libcerror_error_t **error )
{
	libvslvm_internal_volume_group_t *internal_volume_group = NULL;
	libvslvm_stripe_t *stripe                               = NULL;
	char *line_string_segment                               = NULL;
	char *value                                             = NULL;
	char *value_identifier                                  = NULL;
	static char *function                                   = "libvslvm_metadata_read_stripes_list";
	size_t line_string_segment_index                        = 0;
	size_t line_string_segment_size                         = 0;
	size_t value_identifier_length                          = 0;
	size_t value_length                                     = 0;
	uint64_t value_64bit                                    = 0;

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
	if( metadata->volume_group == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid metadata - missing volume group.",
		 function );

		return( -1 );
	}
	internal_volume_group = (libvslvm_internal_volume_group_t *) metadata->volume_group;

	if( internal_volume_group->extent_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid volume group - extent size value out of bounds.",
		 function );

		return( -1 );
	}
	if( line_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid line index.",
		 function );

		return( -1 );
	}
	if( number_of_lines <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of lines value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( *line_index < 0 )
	 || ( *line_index >= number_of_lines ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid line index value out of bounds.",
		 function );

		return( -1 );
	}
	*line_index += 1;

	while( *line_index < number_of_lines )
	{
		if( libcsplit_narrow_split_string_get_segment_by_index(
		     lines,
		     *line_index,
		     &line_string_segment,
		     &line_string_segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve line: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		if( line_string_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing line string segment: %d.",
			 function,
			 *line_index );

			goto on_error;
		}
		/* Ignore trailing white space
		 */
		if( line_string_segment_size >= 2 )
		{
			line_string_segment_index = line_string_segment_size - 2;

			while( line_string_segment_index > 0 )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index--;
				line_string_segment_size--;
			}
		}
		/* Ignore leading white space
		 */
		line_string_segment_index = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		/* Skip an empty line
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Check for the end of section
		 */
		if( ( ( line_string_segment_size - line_string_segment_index ) == 2 )
		 && ( line_string_segment[ line_string_segment_index ] == ']' ) )
		{
			break;
		}
		/* Ingore quotes at the beginning of the value data
		 */
		if( ( line_string_segment[ line_string_segment_index ] == '"' )
		 || ( line_string_segment[ line_string_segment_index ] == '\'' ) )
		{
			line_string_segment_index++;
		}
		/* Determine the value identifier
		 */
		value_identifier        = &( line_string_segment[ line_string_segment_index ] );
		value_identifier_length = 0;

		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] == '\t' )
			 || ( line_string_segment[ line_string_segment_index ] == '\n' )
			 || ( line_string_segment[ line_string_segment_index ] == '\f' )
			 || ( line_string_segment[ line_string_segment_index ] == '\v' )
			 || ( line_string_segment[ line_string_segment_index ] == '\r' )
			 || ( line_string_segment[ line_string_segment_index ] == ' ' )
			 || ( line_string_segment[ line_string_segment_index ] == ',' ) )
			{
				break;
			}
			value_identifier_length++;

			line_string_segment_index++;
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Ingore quotes at the end of the value identifier
		 */
		if( ( line_string_segment[ line_string_segment_index - 1 ] == '"' )
		 || ( line_string_segment[ line_string_segment_index - 1 ] == '\'' ) )
		{
			value_identifier_length--;

			/* Make sure the value identifier is terminated by an end of string
			 */
			line_string_segment[ line_string_segment_index - 1 ] = 0;
		}
		else
		{
			/* Make sure the value identifier is terminated by an end of string
			 */
			line_string_segment[ line_string_segment_index ] = 0;
		}
		line_string_segment_index++;

		/* Ignore whitespace
		 */
		while( line_string_segment_index < line_string_segment_size )
		{
			if( ( line_string_segment[ line_string_segment_index ] != '\t' )
			 && ( line_string_segment[ line_string_segment_index ] != '\n' )
			 && ( line_string_segment[ line_string_segment_index ] != '\f' )
			 && ( line_string_segment[ line_string_segment_index ] != '\v' )
			 && ( line_string_segment[ line_string_segment_index ] != '\r' )
			 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
			{
				break;
			}
			line_string_segment_index++;
		}
		if( line_string_segment[ line_string_segment_index ] == ',' )
		{
			line_string_segment_index++;

			while( line_string_segment_index < line_string_segment_size )
			{
				if( ( line_string_segment[ line_string_segment_index ] != '\t' )
				 && ( line_string_segment[ line_string_segment_index ] != '\n' )
				 && ( line_string_segment[ line_string_segment_index ] != '\f' )
				 && ( line_string_segment[ line_string_segment_index ] != '\v' )
				 && ( line_string_segment[ line_string_segment_index ] != '\r' )
				 && ( line_string_segment[ line_string_segment_index ] != ' ' ) )
				{
					break;
				}
				line_string_segment_index++;
			}
		}
		/* Skip a line not containing a value
		 */
		if( ( line_string_segment_index >= line_string_segment_size )
		 || ( line_string_segment[ line_string_segment_index ] == 0 ) )
		{
			*line_index += 1;

			continue;
		}
		/* Determine the value
		 */
		value        = &( line_string_segment[ line_string_segment_index ] );
		value_length = line_string_segment_size - 1;

		/* Make sure the value is terminated by an end of string
		 */
		line_string_segment[ value_length ] = 0;

		value_length -= line_string_segment_index;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value: %d\t\t\t\t: %s, %s\n",
			 function,
			 *line_index,
			 value_identifier,
			 value );
		}
#endif
		*line_index += 1;

		if( libfvalue_utf8_string_copy_to_integer(
		     (uint8_t *) value,
		     value_length + 1,
		     &value_64bit,
		     64,
		     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL_UNSIGNED,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to set data area offset.",
			 function );

			goto on_error;
		}
		if( value_64bit > (uint64_t) ( UINT64_MAX / internal_volume_group->extent_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid data area offset value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_64bit *= internal_volume_group->extent_size;

		if( libvslvm_stripe_initialize(
		     &stripe,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create stripe.",
			 function );

			goto on_error;
		}
		if( libvslvm_internal_stripe_set_physical_volume_name(
		     (libvslvm_internal_stripe_t *) stripe,
		     value_identifier,
		     value_identifier_length + 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set physical volume name.",
			 function );

			goto on_error;
		}
		if( libvslvm_stripe_set_data_area_offset(
		     stripe,
		     value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set data area offset.",
			 function );

			goto on_error;
		}
		if( libvslvm_segment_append_stripe(
		     segment,
		     stripe,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append stripe to segment.",
			 function );

			goto on_error;
		}
		stripe = NULL;
	}
	return( 1 );

on_error:
	if( stripe != NULL )
	{
		libvslvm_internal_stripe_free(
		 (libvslvm_internal_stripe_t **) &stripe,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the volume group
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libvslvm_metadata_get_volume_group(
     libvslvm_metadata_t *metadata,
     libvslvm_volume_group_t **volume_group,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_metadata_get_volume_group";

	if( metadata == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid metadata.",
		 function );

		return( -1 );
	}
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
	if( metadata->volume_group == NULL )
	{
		return( 0 );
	}
	*volume_group = metadata->volume_group;

	return( 1 );
}

