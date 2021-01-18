/*
 * Library handle type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vslvm_test_getopt.h"
#include "vslvm_test_functions.h"
#include "vslvm_test_libcerror.h"
#include "vslvm_test_libclocale.h"
#include "vslvm_test_libuna.h"
#include "vslvm_test_libvslvm.h"
#include "vslvm_test_macros.h"
#include "vslvm_test_memory.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make vslvm_test_handle generate verbose output
#define VSLVM_TEST_HANDLE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int vslvm_test_handle_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "vslvm_test_handle_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int vslvm_test_handle_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "vslvm_test_handle_get_wide_source";
	size_t source_length    = 0;
	size_t wide_source_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source handle
 * Returns 1 if successful or -1 on error
 */
int vslvm_test_handle_open_source(
     libvslvm_handle_t **handle,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "vslvm_test_handle_open_source";
	int result            = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libvslvm_handle_initialize(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvslvm_handle_open_wide(
	          *handle,
	          source,
	          LIBVSLVM_OPEN_READ,
	          error );
#else
	result = libvslvm_handle_open(
	          *handle,
	          source,
	          LIBVSLVM_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *handle != NULL )
	{
		libvslvm_handle_free(
		 handle,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source handle
 * Returns 1 if successful or -1 on error
 */
int vslvm_test_handle_close_source(
     libvslvm_handle_t **handle,
     libcerror_error_t **error )
{
	static char *function = "vslvm_test_handle_close_source";
	int result            = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( libvslvm_handle_close(
	     *handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close handle.",
		 function );

		result = -1;
	}
	if( libvslvm_handle_free(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libvslvm_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libvslvm_handle_t *handle       = NULL;
	int result                      = 0;

#if defined( HAVE_VSLVM_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvslvm_handle_initialize(
	          &handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvslvm_handle_free(
	          &handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvslvm_handle_initialize(
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

	handle = (libvslvm_handle_t *) 0x12345678UL;

	result = libvslvm_handle_initialize(
	          &handle,
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

	handle = NULL;

#if defined( HAVE_VSLVM_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvslvm_handle_initialize with malloc failing
		 */
		vslvm_test_malloc_attempts_before_fail = test_number;

		result = libvslvm_handle_initialize(
		          &handle,
		          &error );

		if( vslvm_test_malloc_attempts_before_fail != -1 )
		{
			vslvm_test_malloc_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libvslvm_handle_free(
				 &handle,
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
			 "handle",
			 handle );

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
		/* Test libvslvm_handle_initialize with memset failing
		 */
		vslvm_test_memset_attempts_before_fail = test_number;

		result = libvslvm_handle_initialize(
		          &handle,
		          &error );

		if( vslvm_test_memset_attempts_before_fail != -1 )
		{
			vslvm_test_memset_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libvslvm_handle_free(
				 &handle,
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
			 "handle",
			 handle );

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
	if( handle != NULL )
	{
		libvslvm_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_handle_free function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvslvm_handle_free(
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

/* Tests the libvslvm_handle_open function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libvslvm_handle_t *handle = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = vslvm_test_handle_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvslvm_handle_initialize(
	          &handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvslvm_handle_open(
	          handle,
	          narrow_source,
	          LIBVSLVM_OPEN_READ,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvslvm_handle_open(
	          handle,
	          narrow_source,
	          LIBVSLVM_OPEN_READ,
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

	/* Clean up
	 */
	result = libvslvm_handle_free(
	          &handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

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
	if( handle != NULL )
	{
		libvslvm_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libvslvm_handle_open_wide function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_handle_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libvslvm_handle_t *handle = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = vslvm_test_handle_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvslvm_handle_initialize(
	          &handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libvslvm_handle_open_wide(
	          handle,
	          wide_source,
	          LIBVSLVM_OPEN_READ,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvslvm_handle_open_wide(
	          handle,
	          wide_source,
	          LIBVSLVM_OPEN_READ,
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

	/* Clean up
	 */
	result = libvslvm_handle_free(
	          &handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

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
	if( handle != NULL )
	{
		libvslvm_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libvslvm_handle_close function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_handle_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvslvm_handle_close(
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

/* Tests the libvslvm_handle_open and libvslvm_handle_close functions
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_handle_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error  = NULL;
	libvslvm_handle_t *handle = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libvslvm_handle_initialize(
	          &handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvslvm_handle_open_wide(
	          handle,
	          source,
	          LIBVSLVM_OPEN_READ,
	          &error );
#else
	result = libvslvm_handle_open(
	          handle,
	          source,
	          LIBVSLVM_OPEN_READ,
	          &error );
#endif

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvslvm_handle_close(
	          handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvslvm_handle_open_wide(
	          handle,
	          source,
	          LIBVSLVM_OPEN_READ,
	          &error );
#else
	result = libvslvm_handle_open(
	          handle,
	          source,
	          LIBVSLVM_OPEN_READ,
	          &error );
#endif

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvslvm_handle_close(
	          handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libvslvm_handle_free(
	          &handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

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
	if( handle != NULL )
	{
		libvslvm_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvslvm_handle_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_handle_signal_abort(
     libvslvm_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvslvm_handle_signal_abort(
	          handle,
	          &error );

	VSLVM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvslvm_handle_signal_abort(
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

/* Tests the libvslvm_handle_get_volume_group function
 * Returns 1 if successful or 0 if not
 */
int vslvm_test_handle_get_volume_group(
     libvslvm_handle_t *handle )
{
	libcerror_error_t *error              = NULL;
	libvslvm_volume_group_t *volume_group = 0;
	int result                            = 0;
	int volume_group_is_set               = 0;

	/* Test regular cases
	 */
	result = libvslvm_handle_get_volume_group(
	          handle,
	          &volume_group,
	          &error );

	VSLVM_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSLVM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	volume_group_is_set = result;

	if( volume_group_is_set != 0 )
	{
		VSLVM_TEST_ASSERT_IS_NOT_NULL(
		 "volume_group",
		 volume_group );

		result = libvslvm_volume_group_free(
		          &volume_group,
		          &error );

		VSLVM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSLVM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libvslvm_handle_get_volume_group(
	          NULL,
	          &volume_group,
	          &error );

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

	if( volume_group_is_set != 0 )
	{
		result = libvslvm_handle_get_volume_group(
		          handle,
		          NULL,
		          &error );

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
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_group != NULL )
	{
		libvslvm_volume_group_free(
		 &volume_group,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	libvslvm_handle_t *handle  = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = vslvm_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSLVM_TEST_HANDLE_VERBOSE )
	libvslvm_notify_set_verbose(
	 1 );
	libvslvm_notify_set_stream(
	 stderr,
	 NULL );
#endif

	VSLVM_TEST_RUN(
	 "libvslvm_handle_initialize",
	 vslvm_test_handle_initialize );

	VSLVM_TEST_RUN(
	 "libvslvm_handle_free",
	 vslvm_test_handle_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		VSLVM_TEST_RUN_WITH_ARGS(
		 "libvslvm_handle_open",
		 vslvm_test_handle_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		VSLVM_TEST_RUN_WITH_ARGS(
		 "libvslvm_handle_open_wide",
		 vslvm_test_handle_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSLVM_HAVE_BFIO )

		/* TODO add test for libvslvm_handle_open_file_io_handle */

#endif /* defined( LIBVSLVM_HAVE_BFIO ) */

		VSLVM_TEST_RUN(
		 "libvslvm_handle_close",
		 vslvm_test_handle_close );

		VSLVM_TEST_RUN_WITH_ARGS(
		 "libvslvm_handle_open_close",
		 vslvm_test_handle_open_close,
		 source );

		/* Initialize test
		 */
		result = vslvm_test_handle_open_source(
		          &handle,
		          source,
		          &error );

		VSLVM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSLVM_TEST_ASSERT_IS_NOT_NULL(
	         "handle",
	         handle );

	        VSLVM_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		VSLVM_TEST_RUN_WITH_ARGS(
		 "libvslvm_handle_signal_abort",
		 vslvm_test_handle_signal_abort,
		 handle );

		/* TODO: add tests for libvslvm_handle_open_physical_volume_files */

		/* TODO: add tests for libvslvm_handle_open_physical_volume_files_wide */

		/* TODO: add tests for libvslvm_handle_open_physical_volume_files_file_io_pool */

#if defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT )

		/* TODO: add tests for libvslvm_handle_open_physical_volume_file */

		/* TODO: add tests for libvslvm_handle_open_physical_volume_file_wide */

		/* TODO: add tests for libvslvm_handle_open_physical_volume_file_io_handle */

		/* TODO: add tests for libvslvm_handle_open_read_data_area_table */

		/* TODO: add tests for libvslvm_handle_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBVSLVM_DLL_IMPORT ) */

		VSLVM_TEST_RUN_WITH_ARGS(
		 "libvslvm_handle_get_volume_group",
		 vslvm_test_handle_get_volume_group,
		 handle );

		/* Clean up
		 */
		result = vslvm_test_handle_close_source(
		          &handle,
		          &error );

		VSLVM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		VSLVM_TEST_ASSERT_IS_NULL(
	         "handle",
	         handle );

	        VSLVM_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		vslvm_test_handle_close_source(
		 &handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

