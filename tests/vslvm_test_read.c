/*
 * Library read testing program
 *
 * Copyright (C) 2014-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "vslvm_test_libcstring.h"
#include "vslvm_test_libcerror.h"
#include "vslvm_test_libvslvm.h"
#include "vslvm_test_unused.h"

/* Define to make vslvm_test_read generate verbose output
#define VSLVM_TEST_READ_VERBOSE
 */

#define VSLVM_TEST_READ_BUFFER_SIZE	4096

/* Tests libvslvm_logical_volume_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vslvm_test_seek_offset(
     libvslvm_logical_volume_t *logical_volume,
     off64_t input_offset,
     int input_whence,
     off64_t expected_offset )
{
	libvslvm_error_t *error = NULL;
	off64_t result_offset   = 0;
	int result              = 0;

	if( logical_volume == NULL )
	{
		return( -1 );
	}
	result_offset = libvslvm_logical_volume_seek_offset(
	                 logical_volume,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected result offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
	if( error != NULL )
	{
		if( result != 1 )
		{
			libvslvm_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libvslvm_error_free(
		 &error );
	}
	return( result );
}

/* Tests libvslvm_logical_volume_read_buffer
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vslvm_test_read_buffer(
     libvslvm_logical_volume_t *logical_volume,
     size64_t input_size,
     size64_t expected_size )
{
	uint8_t buffer[ VSLVM_TEST_READ_BUFFER_SIZE ];

	libvslvm_error_t *error = NULL;
	size64_t remaining_size = 0;
	size64_t result_size    = 0;
	size_t read_size        = 0;
	ssize_t read_count      = 0;
	int result              = 0;

	if( logical_volume == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		read_size = VSLVM_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libvslvm_logical_volume_read_buffer(
			      logical_volume,
			      buffer,
			      read_size,
			      &error );

		if( read_count < 0 )
		{
			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( error != NULL )
	{
		if( result != 1 )
		{
			libvslvm_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libvslvm_error_free(
		 &error );
	}
	return( result );
}

/* Tests libvslvm_logical_volume_read_buffer_at_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vslvm_test_read_buffer_at_offset(
     libvslvm_logical_volume_t *logical_volume,
     off64_t input_offset,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	uint8_t buffer[ VSLVM_TEST_READ_BUFFER_SIZE ];

	libvslvm_error_t *error = NULL;
	off64_t result_offset   = 0;
	size64_t remaining_size = 0;
	size64_t result_size    = 0;
	size_t read_size        = 0;
	ssize_t read_count      = 0;
	int result              = 0;

	if( logical_volume == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 " and size: %" PRIu64 "\t",
	 input_offset,
	 input_size );

	while( remaining_size > 0 )
	{
		read_size = VSLVM_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libvslvm_logical_volume_read_buffer_at_offset(
			      logical_volume,
			      buffer,
			      read_size,
			      input_offset,
			      &error );

		if( read_count < 0 )
		{
			break;
		}
		input_offset   += (size64_t) read_count;
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( libvslvm_logical_volume_get_offset(
	     logical_volume,
	     &result_offset,
	     &error ) != 1 )
	{
		result = -1;
	}
	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected offset: %" PRIi64 "\n",
		 result_offset );
	}
	else if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		if( result != 1 )
		{
			libvslvm_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libvslvm_error_free(
		 &error );
	}
	return( result );
}

/* Tests reading data at a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vslvm_test_seek_offset_and_read_buffer(
     libvslvm_logical_volume_t *logical_volume,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	const char *whence_string = NULL;
	int result                = 0;

	if( logical_volume == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 ", whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = vslvm_test_seek_offset(
	          logical_volume,
	          input_offset,
	          input_whence,
	          expected_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = vslvm_test_read_buffer(
				  logical_volume,
				  input_size,
				  expected_size );
		}
	}
	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	return( result );
}

/* Tests reading data from a logical volume
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vslvm_test_read_from_logical_volume(
     libvslvm_logical_volume_t *logical_volume,
     size64_t volume_size )
{
	int result = 0;

	if( logical_volume == NULL )
	{
		return( -1 );
	}
	if( volume_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Media size exceeds maximum.\n" );

		return( -1 );
	}
	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <volume_size>
	 * Expected result: offset: 0 size: <volume_size>
	 */
	result = vslvm_test_seek_offset_and_read_buffer(
	          logical_volume,
	          0,
	          SEEK_SET,
	          volume_size,
	          0,
	          volume_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	/* Test: offset: 0 size: <volume_size>
	 * Expected result: offset: 0 size: <volume_size>
	 */
	result = vslvm_test_seek_offset_and_read_buffer(
	          logical_volume,
	          0,
	          SEEK_SET,
	          volume_size,
	          0,
	          volume_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 1: test buffer at offset read
	 */

	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: <volume_size / 7> size: <volume_size / 2>
	 */
	result = vslvm_test_seek_offset_and_read_buffer(
	          logical_volume,
	          (off64_t) ( volume_size / 7 ),
	          SEEK_SET,
	          volume_size / 2,
	          (off64_t) ( volume_size / 7 ),
	          volume_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: <volume_size / 7> size: <volume_size / 2>
	 */
	result = vslvm_test_seek_offset_and_read_buffer(
	          logical_volume,
	          (off64_t) ( volume_size / 7 ),
	          SEEK_SET,
	          volume_size / 2,
	          (off64_t) ( volume_size / 7 ),
	          volume_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 2: test read beyond volume size
	 */

	if( volume_size < 1024 )
	{
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = vslvm_test_seek_offset_and_read_buffer(
		          logical_volume,
		          (off64_t) ( volume_size - 1024 ),
		          SEEK_SET,
		          4096,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = vslvm_test_seek_offset_and_read_buffer(
		          logical_volume,
		          (off64_t) ( volume_size - 1024 ),
		          SEEK_SET,
		          4096,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: <volume_size - 1024> size: 1024
		 */
		result = vslvm_test_seek_offset_and_read_buffer(
		          logical_volume,
		          (off64_t) ( volume_size - 1024 ),
		          SEEK_SET,
		          4096,
		          (off64_t) ( volume_size - 1024 ),
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			return( result );
		}
		/* Test: offset: <volume_size - 1024> size: 4096
		 * Expected result: offset: <volume_size - 1024> size: 1024
		 */
		result = vslvm_test_seek_offset_and_read_buffer(
		          logical_volume,
		          (off64_t) ( volume_size - 1024 ),
		          SEEK_SET,
		          4096,
		          (off64_t) ( volume_size - 1024 ),
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	/* Case 3: test buffer at offset read
	 */

	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: < ( volume_size / 7 ) + ( volume_size / 2 ) > size: <volume_size / 2>
	 */
	result = vslvm_test_read_buffer_at_offset(
	          logical_volume,
	          (off64_t) ( volume_size / 7 ),
	          volume_size / 2,
	          (off64_t) ( volume_size / 7 ) + ( volume_size / 2 ),
	          volume_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	/* Test: offset: <volume_size / 7> size: <volume_size / 2>
	 * Expected result: offset: < ( volume_size / 7 ) + ( volume_size / 2 ) > size: <volume_size / 2>
	 */
	result = vslvm_test_read_buffer_at_offset(
	          logical_volume,
	          (off64_t) ( volume_size / 7 ),
	          volume_size / 2,
	          (off64_t) ( volume_size / 7 ) + ( volume_size / 2 ),
	          volume_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	return( 1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libvslvm_error_t *error                   = NULL;
	libvslvm_handle_t *handle                 = NULL;
	libvslvm_logical_volume_t *logical_volume = NULL;
	libvslvm_volume_group_t *volume_group     = NULL;
	size64_t volume_size                      = 0;
	int logical_volume_index                  = 0;
	int number_of_logical_volumes             = 0;

	if( argc < 2 )
	{
		fprintf(
		 stderr,
		 "Missing filename.\n" );

		return( EXIT_FAILURE );
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSLVM_TEST_READ_VERBOSE )
	libvslvm_notify_set_verbose(
	 1 );
	libvslvm_notify_set_stream(
	 stderr,
	 NULL );
#endif
	/* Initialization
	 */
	if( libvslvm_handle_initialize(
	     &handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create handle.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvslvm_handle_open_wide(
	     handle,
	     argv[ 1 ],
	     LIBVSLVM_OPEN_READ,
	     &error ) != 1 )
#else
	if( libvslvm_handle_open(
	     handle,
	     argv[ 1 ],
	     LIBVSLVM_OPEN_READ,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open handle.\n" );

		goto on_error;
	}
/* TODO determine if the first file is a metadata only file and change argv/argc accordingly
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvslvm_handle_open_physical_volume_files_wide(
	     handle,
	     &( argv[ 1 ] ),
	     argc - 1,
	     &error ) != 1 )
#else
	if( libvslvm_handle_open_physical_volume_files(
	     handle,
	     &( argv[ 1 ] ),
	     argc - 1,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open physical volume files.\n" );

		goto on_error;
	}
	if( libvslvm_handle_get_volume_group(
	     handle,
	     &volume_group,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve volume group.\n" );

		goto on_error;
	}
	if( libvslvm_volume_group_get_number_of_logical_volumes(
	     volume_group,
	     &number_of_logical_volumes,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve number of logical volumes.\n" );

		goto on_error;
	}
	for( logical_volume_index = 0;
	     logical_volume_index < number_of_logical_volumes;
	     logical_volume_index++ )
	{
		if( libvslvm_volume_group_get_logical_volume(
		     volume_group,
		     logical_volume_index,
		     &logical_volume,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to retrieve logical volume: %d.\n",
			 logical_volume_index );

			goto on_error;
		}
		if( libvslvm_logical_volume_get_size(
		     logical_volume,
		     &volume_size,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to retrieve volume size.\n" );

			goto on_error;
		}
		fprintf(
		 stdout,
		 "Volume size: %" PRIu64 " bytes\n",
		 volume_size );

		if( vslvm_test_read_from_logical_volume(
		     logical_volume,
		     volume_size ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to read from logical volume.\n" );

			goto on_error;
		}
		if( libvslvm_logical_volume_free(
		     &logical_volume,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to free logical volume: %d.\n",
			 logical_volume_index );

			goto on_error;
		}
	}
	/* Clean up
	 */
	if( libvslvm_volume_group_free(
	     &volume_group,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free volume group.\n" );

		goto on_error;
	}
	if( libvslvm_handle_close(
	     handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close handle.\n" );

		goto on_error;
	}
	if( libvslvm_handle_free(
	     &handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libvslvm_error_backtrace_fprint(
		 error,
		 stderr );
		libvslvm_error_free(
		 &error );
	}
	if( logical_volume != NULL )
	{
		libvslvm_logical_volume_free(
		 &logical_volume,
		 NULL );
	}
	if( volume_group != NULL )
	{
		libvslvm_volume_group_free(
		 &volume_group,
		 NULL );
	}
	if( handle != NULL )
	{
		libvslvm_handle_close(
		 handle,
		 NULL );
		libvslvm_handle_free(
		 &handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

