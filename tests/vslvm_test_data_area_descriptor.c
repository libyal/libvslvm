/*
 * Library data_area_descriptor type test program
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

#include "../libvslvm/libvslvm_data_area_descriptor.h"

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

/* Tests the libvslvm_data_area_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_data_area_descriptor_initialize(
     void )
{
	libcerror_error_t *error                              = NULL;
	libvslvm_data_area_descriptor_t *data_area_descriptor = NULL;
	int result                                            = 0;

#if defined( HAVE_VSLVM_TEST_MEMORY )
	int number_of_malloc_fail_tests                       = 1;
	int number_of_memset_fail_tests                       = 1;
	int test_number                                       = 0;
#endif

	/* Test regular cases
	 */
	result = libvslvm_data_area_descriptor_initialize(
	          &data_area_descriptor,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "data_area_descriptor",
	 data_area_descriptor );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvslvm_data_area_descriptor_free(
	          &data_area_descriptor,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "data_area_descriptor",
	 data_area_descriptor );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvslvm_data_area_descriptor_initialize(
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

	data_area_descriptor = (libvslvm_data_area_descriptor_t *) 0x12345678UL;

	result = libvslvm_data_area_descriptor_initialize(
	          &data_area_descriptor,
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

	data_area_descriptor = NULL;

#if defined( HAVE_VSLVM_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvslvm_data_area_descriptor_initialize with malloc failing
		 */
		vslvm_test_malloc_attempts_before_fail = test_number;

		result = libvslvm_data_area_descriptor_initialize(
		          &data_area_descriptor,
		          &error );

		if( vslvm_test_malloc_attempts_before_fail != -1 )
		{
			vslvm_test_malloc_attempts_before_fail = -1;

			if( data_area_descriptor != NULL )
			{
				libvslvm_data_area_descriptor_free(
				 &data_area_descriptor,
				 NULL );
			}
		}
		else
		{
			VSLVM_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSLVM_TEST_ASSERT_IS_NULL(
			 "data_area_descriptor",
			 data_area_descriptor );

			VSLVM_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvslvm_data_area_descriptor_initialize with memset failing
		 */
		vslvm_test_memset_attempts_before_fail = test_number;

		result = libvslvm_data_area_descriptor_initialize(
		          &data_area_descriptor,
		          &error );

		if( vslvm_test_memset_attempts_before_fail != -1 )
		{
			vslvm_test_memset_attempts_before_fail = -1;

			if( data_area_descriptor != NULL )
			{
				libvslvm_data_area_descriptor_free(
				 &data_area_descriptor,
				 NULL );
			}
		}
		else
		{
			VSLVM_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSLVM_TEST_ASSERT_IS_NULL(
			 "data_area_descriptor",
			 data_area_descriptor );

			VSLVM_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSLVM_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_area_descriptor != NULL )
	{
		libvslvm_data_area_descriptor_free(
		 &data_area_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_data_area_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_data_area_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvslvm_data_area_descriptor_free(
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

	VSLVM_TEST_RUN(
	 "libvslvm_data_area_descriptor_initialize",
	 vslvm_test_data_area_descriptor_initialize );

	VSLVM_TEST_RUN(
	 "libvslvm_data_area_descriptor_free",
	 vslvm_test_data_area_descriptor_free );

	/* TODO: add tests for libvslvm_data_area_descriptor_get */

	/* TODO: add tests for libvslvm_data_area_descriptor_set */

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

