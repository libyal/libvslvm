/*
 * Library volume_group type test program
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

#include "../libvslvm/libvslvm_volume_group.h"

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

/* Tests the libvslvm_volume_group_initialize function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_volume_group_initialize(
     void )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	int result                            = 0;

#if defined( HAVE_VSLVM_TEST_MEMORY )
	int number_of_malloc_fail_tests       = 1;
	int number_of_memset_fail_tests       = 1;
	int test_number                       = 0;
#endif

	/* Test regular cases
	 */
	result = libvslvm_volume_group_initialize(
	          &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "volume_group",
	 volume_group );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvslvm_internal_volume_group_free(
	          (libvslvm_internal_volume_group_t **) &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "volume_group",
	 volume_group );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvslvm_volume_group_initialize(
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

	volume_group = (libvslvm_volume_group_t *) 0x12345678UL;

	result = libvslvm_volume_group_initialize(
	          &volume_group,
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

	volume_group = NULL;

#if defined( HAVE_VSLVM_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvslvm_volume_group_initialize with malloc failing
		 */
		vslvm_test_malloc_attempts_before_fail = test_number;

		result = libvslvm_volume_group_initialize(
		          &volume_group,
		          &error );

		if( vslvm_test_malloc_attempts_before_fail != -1 )
		{
			vslvm_test_malloc_attempts_before_fail = -1;

			if( volume_group != NULL )
			{
				libvslvm_internal_volume_group_free(
				 (libvslvm_internal_volume_group_t **) &volume_group,
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
			 "volume_group",
			 volume_group );

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
		/* Test libvslvm_volume_group_initialize with memset failing
		 */
		vslvm_test_memset_attempts_before_fail = test_number;

		result = libvslvm_volume_group_initialize(
		          &volume_group,
		          &error );

		if( vslvm_test_memset_attempts_before_fail != -1 )
		{
			vslvm_test_memset_attempts_before_fail = -1;

			if( volume_group != NULL )
			{
				libvslvm_internal_volume_group_free(
				 (libvslvm_internal_volume_group_t **) &volume_group,
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
			 "volume_group",
			 volume_group );

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
	if( volume_group != NULL )
	{
		libvslvm_internal_volume_group_free(
		 (libvslvm_internal_volume_group_t **) &volume_group,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

/* Tests the libvslvm_volume_group_free function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_volume_group_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvslvm_volume_group_free(
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

/* Tests the libvslvm_volume_group_get_name_size function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_volume_group_get_name_size(
     void )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	size_t name_size                      = 0;
	int name_size_is_set                  = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libvslvm_volume_group_initialize(
	          &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "volume_group",
	 volume_group );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_volume_group_get_name_size(
	          volume_group,
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
	result = libvslvm_volume_group_get_name_size(
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
		result = libvslvm_volume_group_get_name_size(
		          volume_group,
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
	result = libvslvm_internal_volume_group_free(
	          (libvslvm_internal_volume_group_t **) &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "volume_group",
	 volume_group );

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
	if( volume_group != NULL )
	{
		libvslvm_internal_volume_group_free(
		 (libvslvm_internal_volume_group_t **) &volume_group,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_volume_group_get_identifier_size function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_volume_group_get_identifier_size(
     void )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	size_t identifier_size                = 0;
	int identifier_size_is_set            = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libvslvm_volume_group_initialize(
	          &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "volume_group",
	 volume_group );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_volume_group_get_identifier_size(
	          volume_group,
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
	result = libvslvm_volume_group_get_identifier_size(
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
		result = libvslvm_volume_group_get_identifier_size(
		          volume_group,
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
	result = libvslvm_internal_volume_group_free(
	          (libvslvm_internal_volume_group_t **) &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "volume_group",
	 volume_group );

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
	if( volume_group != NULL )
	{
		libvslvm_internal_volume_group_free(
		 (libvslvm_internal_volume_group_t **) &volume_group,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_volume_group_get_sequence_number function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_volume_group_get_sequence_number(
     void )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	uint32_t sequence_number              = 0;
	int result                            = 0;
	int sequence_number_is_set            = 0;

	/* Initialize test
	 */
	result = libvslvm_volume_group_initialize(
	          &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "volume_group",
	 volume_group );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_volume_group_get_sequence_number(
	          volume_group,
	          &sequence_number,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	sequence_number_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_volume_group_get_sequence_number(
	          NULL,
	          &sequence_number,
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

	if( sequence_number_is_set != 0 )
	{
		result = libvslvm_volume_group_get_sequence_number(
		          volume_group,
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
	result = libvslvm_internal_volume_group_free(
	          (libvslvm_internal_volume_group_t **) &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "volume_group",
	 volume_group );

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
	if( volume_group != NULL )
	{
		libvslvm_internal_volume_group_free(
		 (libvslvm_internal_volume_group_t **) &volume_group,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_volume_group_get_extent_size function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_volume_group_get_extent_size(
     void )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	size64_t extent_size                  = 0;
	int extent_size_is_set                = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libvslvm_volume_group_initialize(
	          &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "volume_group",
	 volume_group );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_volume_group_get_extent_size(
	          volume_group,
	          &extent_size,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	extent_size_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_volume_group_get_extent_size(
	          NULL,
	          &extent_size,
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

	if( extent_size_is_set != 0 )
	{
		result = libvslvm_volume_group_get_extent_size(
		          volume_group,
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
	result = libvslvm_internal_volume_group_free(
	          (libvslvm_internal_volume_group_t **) &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "volume_group",
	 volume_group );

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
	if( volume_group != NULL )
	{
		libvslvm_internal_volume_group_free(
		 (libvslvm_internal_volume_group_t **) &volume_group,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_volume_group_get_number_of_physical_volumes function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_volume_group_get_number_of_physical_volumes(
     void )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	int number_of_physical_volumes        = 0;
	int number_of_physical_volumes_is_set = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libvslvm_volume_group_initialize(
	          &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "volume_group",
	 volume_group );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_volume_group_get_number_of_physical_volumes(
	          volume_group,
	          &number_of_physical_volumes,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_physical_volumes_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_volume_group_get_number_of_physical_volumes(
	          NULL,
	          &number_of_physical_volumes,
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

	if( number_of_physical_volumes_is_set != 0 )
	{
		result = libvslvm_volume_group_get_number_of_physical_volumes(
		          volume_group,
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
	result = libvslvm_internal_volume_group_free(
	          (libvslvm_internal_volume_group_t **) &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "volume_group",
	 volume_group );

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
	if( volume_group != NULL )
	{
		libvslvm_internal_volume_group_free(
		 (libvslvm_internal_volume_group_t **) &volume_group,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_volume_group_get_number_of_logical_volumes function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_volume_group_get_number_of_logical_volumes(
     void )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = NULL;
	int number_of_logical_volumes         = 0;
	int number_of_logical_volumes_is_set  = 0;
	int result                            = 0;

	/* Initialize test
	 */
	result = libvslvm_volume_group_initialize(
	          &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "volume_group",
	 volume_group );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvslvm_volume_group_get_number_of_logical_volumes(
	          volume_group,
	          &number_of_logical_volumes,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_logical_volumes_is_set = result;

	/* Test error cases
	 */
	result = libvslvm_volume_group_get_number_of_logical_volumes(
	          NULL,
	          &number_of_logical_volumes,
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

	if( number_of_logical_volumes_is_set != 0 )
	{
		result = libvslvm_volume_group_get_number_of_logical_volumes(
		          volume_group,
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
	result = libvslvm_internal_volume_group_free(
	          (libvslvm_internal_volume_group_t **) &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "volume_group",
	 volume_group );

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
	if( volume_group != NULL )
	{
		libvslvm_internal_volume_group_free(
		 (libvslvm_internal_volume_group_t **) &volume_group,
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
	 "libvslvm_volume_group_initialize",
	 vslvm_test_volume_group_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

	VSLVM_TEST_RUN(
	 "libvslvm_volume_group_free",
	 vslvm_test_volume_group_free );

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

	/* TODO: add tests for libvslvm_volume_group_set_io_values */

	VSLVM_TEST_RUN(
	 "libvslvm_volume_group_get_name_size",
	 vslvm_test_volume_group_get_name_size );

	/* TODO: add tests for libvslvm_volume_group_get_name */

	/* TODO: add tests for libvslvm_volume_group_set_name */

	VSLVM_TEST_RUN(
	 "libvslvm_volume_group_get_identifier_size",
	 vslvm_test_volume_group_get_identifier_size );

	/* TODO: add tests for libvslvm_volume_group_get_identifier */

	/* TODO: add tests for libvslvm_volume_group_set_identifier */

	VSLVM_TEST_RUN(
	 "libvslvm_volume_group_get_sequence_number",
	 vslvm_test_volume_group_get_sequence_number );

	VSLVM_TEST_RUN(
	 "libvslvm_volume_group_get_extent_size",
	 vslvm_test_volume_group_get_extent_size );

	VSLVM_TEST_RUN(
	 "libvslvm_volume_group_get_number_of_physical_volumes",
	 vslvm_test_volume_group_get_number_of_physical_volumes );

	/* TODO: add tests for libvslvm_volume_group_get_physical_volume */

	/* TODO: add tests for libvslvm_volume_group_get_physical_volume_by_name */

	/* TODO: add tests for libvslvm_volume_group_append_physical_volume */

	VSLVM_TEST_RUN(
	 "libvslvm_volume_group_get_number_of_logical_volumes",
	 vslvm_test_volume_group_get_number_of_logical_volumes );

	/* TODO: add tests for libvslvm_volume_group_get_logical_volume */

	/* TODO: add tests for libvslvm_volume_group_append_logical_volume */

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

