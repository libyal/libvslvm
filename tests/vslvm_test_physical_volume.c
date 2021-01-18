/*
 * Library physical_volume type test program
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

#include "../libvslvm/libvslvm_physical_volume.h"

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

/* Tests the libvslvm_physical_volume_initialize function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_physical_volume_initialize(
     void )
{
	libcerror_error_t *error                    = NULL;
	libvslvm_physical_volume_t *physical_volume = NULL;
	int result                                  = 0;

#if defined( HAVE_VSLVM_TEST_MEMORY )
	int number_of_malloc_fail_tests             = 1;
	int number_of_memset_fail_tests             = 1;
	int test_number                             = 0;
#endif

	/* Test regular cases
	 */
	result = libvslvm_physical_volume_initialize(
	          &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvslvm_internal_physical_volume_free(
	          (libvslvm_internal_physical_volume_t **) &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvslvm_physical_volume_initialize(
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

	physical_volume = (libvslvm_physical_volume_t *) 0x12345678UL;

	result = libvslvm_physical_volume_initialize(
	          &physical_volume,
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

	physical_volume = NULL;

#if defined( HAVE_VSLVM_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvslvm_physical_volume_initialize with malloc failing
		 */
		vslvm_test_malloc_attempts_before_fail = test_number;

		result = libvslvm_physical_volume_initialize(
		          &physical_volume,
		          &error );

		if( vslvm_test_malloc_attempts_before_fail != -1 )
		{
			vslvm_test_malloc_attempts_before_fail = -1;

			if( physical_volume != NULL )
			{
				libvslvm_internal_physical_volume_free(
				 (libvslvm_internal_physical_volume_t **) &physical_volume,
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
			 "physical_volume",
			 physical_volume );

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
		/* Test libvslvm_physical_volume_initialize with memset failing
		 */
		vslvm_test_memset_attempts_before_fail = test_number;

		result = libvslvm_physical_volume_initialize(
		          &physical_volume,
		          &error );

		if( vslvm_test_memset_attempts_before_fail != -1 )
		{
			vslvm_test_memset_attempts_before_fail = -1;

			if( physical_volume != NULL )
			{
				libvslvm_internal_physical_volume_free(
				 (libvslvm_internal_physical_volume_t **) &physical_volume,
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
			 "physical_volume",
			 physical_volume );

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
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

/* Tests the libvslvm_physical_volume_free function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_physical_volume_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvslvm_physical_volume_free(
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

/* Tests the libvslvm_physical_volume_get_name_size function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_physical_volume_get_name_size(
     void )
{
	libcerror_error_t *error                    = NULL;
	libvslvm_physical_volume_t *physical_volume = NULL;
	size_t name_size                            = 0;
	int name_size_is_set                        = 0;
	int result                                  = 0;

	/* Initialize test
	 */
	result = libvslvm_physical_volume_initialize(
	          &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_physical_volume_get_name_size(
	          physical_volume,
	          &name_size,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	name_size_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_physical_volume_get_name_size(
	          NULL,
	          &name_size,
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

	if( name_size_is_set != 0 )
	{
		result = libvslvm_physical_volume_get_name_size(
		          physical_volume,
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
	}
	/* Clean up
	 */
	result = libvslvm_internal_physical_volume_free(
	          (libvslvm_internal_physical_volume_t **) &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_physical_volume_get_identifier_size function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_physical_volume_get_identifier_size(
     void )
{
	libcerror_error_t *error                    = NULL;
	libvslvm_physical_volume_t *physical_volume = NULL;
	size_t identifier_size                      = 0;
	int identifier_size_is_set                  = 0;
	int result                                  = 0;

	/* Initialize test
	 */
	result = libvslvm_physical_volume_initialize(
	          &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_physical_volume_get_identifier_size(
	          physical_volume,
	          &identifier_size,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	identifier_size_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_physical_volume_get_identifier_size(
	          NULL,
	          &identifier_size,
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

	if( identifier_size_is_set != 0 )
	{
		result = libvslvm_physical_volume_get_identifier_size(
		          physical_volume,
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
	}
	/* Clean up
	 */
	result = libvslvm_internal_physical_volume_free(
	          (libvslvm_internal_physical_volume_t **) &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_physical_volume_get_device_path_size function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_physical_volume_get_device_path_size(
     void )
{
	libcerror_error_t *error                    = NULL;
	libvslvm_physical_volume_t *physical_volume = NULL;
	size_t device_path_size                     = 0;
	int device_path_size_is_set                 = 0;
	int result                                  = 0;

	/* Initialize test
	 */
	result = libvslvm_physical_volume_initialize(
	          &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_physical_volume_get_device_path_size(
	          physical_volume,
	          &device_path_size,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	device_path_size_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_physical_volume_get_device_path_size(
	          NULL,
	          &device_path_size,
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

	if( device_path_size_is_set != 0 )
	{
		result = libvslvm_physical_volume_get_device_path_size(
		          physical_volume,
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
	}
	/* Clean up
	 */
	result = libvslvm_internal_physical_volume_free(
	          (libvslvm_internal_physical_volume_t **) &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_physical_volume_get_size function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_physical_volume_get_size(
     void )
{
	libcerror_error_t *error                    = NULL;
	libvslvm_physical_volume_t *physical_volume = NULL;
	size64_t size                               = 0;
	int result                                  = 0;
	int size_is_set                             = 0;

	/* Initialize test
	 */
	result = libvslvm_physical_volume_initialize(
	          &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_physical_volume_get_size(
	          physical_volume,
	          &size,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_physical_volume_get_size(
	          NULL,
	          &size,
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

	if( size_is_set != 0 )
	{
		result = libvslvm_physical_volume_get_size(
		          physical_volume,
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
	}
	/* Clean up
	 */
	result = libvslvm_internal_physical_volume_free(
	          (libvslvm_internal_physical_volume_t **) &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_physical_volume_get_number_of_data_area_descriptors function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_physical_volume_get_number_of_data_area_descriptors(
     void )
{
	libcerror_error_t *error                    = NULL;
	libvslvm_physical_volume_t *physical_volume = NULL;
	int number_of_data_area_descriptors         = 0;
	int number_of_data_area_descriptors_is_set  = 0;
	int result                                  = 0;

	/* Initialize test
	 */
	result = libvslvm_physical_volume_initialize(
	          &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_physical_volume_get_number_of_data_area_descriptors(
	          physical_volume,
	          &number_of_data_area_descriptors,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_data_area_descriptors_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_physical_volume_get_number_of_data_area_descriptors(
	          NULL,
	          &number_of_data_area_descriptors,
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

	if( number_of_data_area_descriptors_is_set != 0 )
	{
		result = libvslvm_physical_volume_get_number_of_data_area_descriptors(
		          physical_volume,
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
	}
	/* Clean up
	 */
	result = libvslvm_internal_physical_volume_free(
	          (libvslvm_internal_physical_volume_t **) &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_physical_volume_get_number_of_metadata_area_descriptors function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_physical_volume_get_number_of_metadata_area_descriptors(
     void )
{
	libcerror_error_t *error                       = NULL;
	libvslvm_physical_volume_t *physical_volume    = NULL;
	int number_of_metadata_area_descriptors        = 0;
	int number_of_metadata_area_descriptors_is_set = 0;
	int result                                     = 0;

	/* Initialize test
	 */
	result = libvslvm_physical_volume_initialize(
	          &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_physical_volume_get_number_of_metadata_area_descriptors(
	          physical_volume,
	          &number_of_metadata_area_descriptors,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_metadata_area_descriptors_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_physical_volume_get_number_of_metadata_area_descriptors(
	          NULL,
	          &number_of_metadata_area_descriptors,
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

	if( number_of_metadata_area_descriptors_is_set != 0 )
	{
		result = libvslvm_physical_volume_get_number_of_metadata_area_descriptors(
		          physical_volume,
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
	}
	/* Clean up
	 */
	result = libvslvm_internal_physical_volume_free(
	          (libvslvm_internal_physical_volume_t **) &physical_volume,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "physical_volume",
	 physical_volume );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( physical_volume != NULL )
	{
		libvslvm_internal_physical_volume_free(
		 (libvslvm_internal_physical_volume_t **) &physical_volume,
		 NULL );
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
	 "libvslvm_physical_volume_initialize",
	 vslvm_test_physical_volume_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

	VSLVM_TEST_RUN(
	 "libvslvm_physical_volume_free",
	 vslvm_test_physical_volume_free );

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

	VSLVM_TEST_RUN(
	 "libvslvm_physical_volume_get_name_size",
	 vslvm_test_physical_volume_get_name_size );

	/* TODO: add tests for libvslvm_physical_volume_get_name */

	/* TODO: add tests for libvslvm_physical_volume_set_name */

	/* TODO: add tests for libvslvm_physical_volume_compare_by_name */

	VSLVM_TEST_RUN(
	 "libvslvm_physical_volume_get_identifier_size",
	 vslvm_test_physical_volume_get_identifier_size );

	/* TODO: add tests for libvslvm_physical_volume_get_identifier */

	/* TODO: add tests for libvslvm_physical_volume_set_identifier */

	VSLVM_TEST_RUN(
	 "libvslvm_physical_volume_get_device_path_size",
	 vslvm_test_physical_volume_get_device_path_size );

	/* TODO: add tests for libvslvm_physical_volume_get_device_path */

	/* TODO: add tests for libvslvm_physical_volume_set_device_path */

	VSLVM_TEST_RUN(
	 "libvslvm_physical_volume_get_size",
	 vslvm_test_physical_volume_get_size );

	VSLVM_TEST_RUN(
	 "libvslvm_physical_volume_get_number_of_data_area_descriptors",
	 vslvm_test_physical_volume_get_number_of_data_area_descriptors );

	/* TODO: add tests for libvslvm_physical_volume_get_data_area_descriptor */

	/* TODO: add tests for libvslvm_physical_volume_get_data_area_descriptor_by_offset */

	VSLVM_TEST_RUN(
	 "libvslvm_physical_volume_get_number_of_metadata_area_descriptors",
	 vslvm_test_physical_volume_get_number_of_metadata_area_descriptors );

	/* TODO: add tests for libvslvm_physical_volume_get_metadata_area_descriptor */

	/* TODO: add tests for libvslvm_physical_volume_read_label */

	/* TODO: add tests for libvslvm_physical_volume_read_element_data */

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

