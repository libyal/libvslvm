/*
 * Library logical_volume type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vslvm_test_libcerror.h"
#include "vslvm_test_libvslvm.h"
#include "vslvm_test_macros.h"
#include "vslvm_test_memory.h"
#include "vslvm_test_unused.h"

#include "../libvslvm/libvslvm_logical_volume.h"

/* Tests the libvslvm_logical_volume_free function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_logical_volume_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvslvm_logical_volume_free(
	          NULL,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc VSLVM_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] VSLVM_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc VSLVM_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] VSLVM_TEST_ATTRIBUTE_UNUSED )
#endif
{
	VSLVM_TEST_UNREFERENCED_PARAMETER( argc )
	VSLVM_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

	/* TODO: add tests for libvslvm_logical_volume_initialize */

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

	VSLVM_TEST_RUN(
	 "libvslvm_logical_volume_free",
	 vslvm_test_logical_volume_free );

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

	/* TODO: add tests for libvslvm_logical_volume_read_buffer */

	/* TODO: add tests for libvslvm_logical_volume_read_buffer_at_offset */

	/* TODO: add tests for libvslvm_logical_volume_seek_offset */

	/* TODO: add tests for libvslvm_logical_volume_get_offset */

	/* TODO: add tests for libvslvm_logical_volume_get_size */

	/* TODO: add tests for libvslvm_logical_volume_get_name_size */

	/* TODO: add tests for libvslvm_logical_volume_get_name */

	/* TODO: add tests for libvslvm_logical_volume_get_identifier_size */

	/* TODO: add tests for libvslvm_logical_volume_get_identifier */

	/* TODO: add tests for libvslvm_logical_volume_get_number_of_segments */

	/* TODO: add tests for libvslvm_logical_volume_get_segment */

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

