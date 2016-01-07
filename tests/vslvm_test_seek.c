/*
 * Library seek testing program
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
#include "vslvm_test_libvslvm.h"

/* Define to make vslvm_test_seek generate verbose output
#define VSLVM_TEST_SEEK_VERBOSE
 */

/* Tests libvslvm_logical_volume_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vslvm_test_seek_offset(
     libvslvm_logical_volume_t *logical_volume,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	libvslvm_error_t *error   = NULL;
	const char *whence_string = NULL;
	off64_t result_offset     = 0;
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
	 "Testing seek of offset: %" PRIi64 " and whence: %s\t",
	 input_offset,
	 whence_string );

	result_offset = libvslvm_logical_volume_seek_offset(
	                 logical_volume,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == output_offset )
	{
		result = 1;
	}
	if( result != 0 )
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

	if( error != NULL)
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

/* Tests seeking in a logical volume
 * Returns 1 if successful, 0 if not or -1 on error
 */
int vslvm_test_seek_logical_volume(
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
		 "Volume size exceeds maximum.\n" );

		return( -1 );
	}
	/* Test: SEEK_SET offset: 0
	 * Expected result: 0
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          0,
	          SEEK_SET,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <volume_size>
	 * Expected result: <volume_size>
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          (off64_t) volume_size,
	          SEEK_SET,
	          (off64_t) volume_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <volume_size / 5>
	 * Expected result: <volume_size / 5>
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          (off64_t) ( volume_size / 5 ),
	          SEEK_SET,
	          (off64_t) ( volume_size / 5 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <volume_size + 987>
	 * Expected result: <volume_size + 987>
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          (off64_t) ( volume_size + 987 ),
	          SEEK_SET,
	          (off64_t) ( volume_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: -987
	 * Expected result: -1
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          -987,
	          SEEK_SET,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: 0
	 * Expected result: <volume_size + 987>
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          0,
	          SEEK_CUR,
	          (off64_t) ( volume_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <-1 * (volume_size + 987)>
	 * Expected result: 0
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          -1 * (off64_t) ( volume_size + 987 ),
	          SEEK_CUR,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <volume_size / 3>
	 * Expected result: <volume_size / 3>
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          (off64_t) ( volume_size / 3 ),
	          SEEK_CUR,
	          (off64_t) ( volume_size / 3 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	if( volume_size == 0 )
	{
		/* Test: SEEK_CUR offset: <-2 * (volume_size / 3)>
		 * Expected result: 0
		 */
		result = vslvm_test_seek_offset(
		          logical_volume,
		          -2 * (off64_t) ( volume_size / 3 ),
		          SEEK_CUR,
		          0 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: SEEK_CUR offset: <-2 * (volume_size / 3)>
		 * Expected result: -1
		 */
		result = vslvm_test_seek_offset(
		          logical_volume,
		          -2 * (off64_t) ( volume_size / 3 ),
		          SEEK_CUR,
		          -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	/* Test: SEEK_END offset: 0
	 * Expected result: <volume_size>
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          0,
	          SEEK_END,
	          (off64_t) volume_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * volume_size>
	 * Expected result: 0
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          -1 * (off64_t) volume_size,
	          SEEK_END,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (volume_size / 4)>
	 * Expected result: <volume_size - (volume_size / 4)>
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          -1 * (off64_t) ( volume_size / 4 ),
	          SEEK_END,
	          (off64_t) volume_size - (off64_t) ( volume_size / 4 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: 542
	 * Expected result: <volume_size + 542>
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          542,
	          SEEK_END,
	          (off64_t) ( volume_size + 542 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (volume_size + 542)>
	 * Expected result: -1
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          -1 * (off64_t) ( volume_size + 542 ),
	          SEEK_END,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: UNKNOWN (88) offset: 0
	 * Expected result: -1
	 */
	result = vslvm_test_seek_offset(
	          logical_volume,
	          0,
	          88,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	return( result );
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
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSLVM_TEST_SEEK_VERBOSE )
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

		if( vslvm_test_seek_logical_volume(
		     logical_volume,
		     volume_size ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to seek in logical volume.\n" );

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

