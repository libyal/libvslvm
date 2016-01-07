/*
 * Physical volume table functions
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
#include <memory.h>
#include <types.h>

#include "libvslvm_definitions.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_libfcache.h"
#include "libvslvm_libfdata.h"
#include "libvslvm_physical_volume.h"
#include "libvslvm_physical_volume_table.h"

/* Creates a physical volume table
 * Make sure the value physical_volume_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_table_initialize(
     libvslvm_physical_volume_table_t **physical_volume_table,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_physical_volume_table_initialize";

	if( physical_volume_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume table.",
		 function );

		return( -1 );
	}
	if( *physical_volume_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid physical volume table value already set.",
		 function );

		return( -1 );
	}
	*physical_volume_table = memory_allocate_structure(
	                          libvslvm_physical_volume_table_t );

	if( *physical_volume_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create physical volume table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *physical_volume_table,
	     0,
	     sizeof( libvslvm_physical_volume_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear physical volume table.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *physical_volume_table != NULL )
	{
		memory_free(
		 *physical_volume_table );

		*physical_volume_table = NULL;
	}
	return( -1 );
}

/* Frees a physical volume table
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_table_free(
     libvslvm_physical_volume_table_t **physical_volume_table,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_physical_volume_table_free";
	int result            = 1;

	if( physical_volume_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume table.",
		 function );

		return( -1 );
	}
	if( *physical_volume_table != NULL )
	{
		if( libvslvm_physical_volume_table_clear(
		     *physical_volume_table,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to clear physical volume table.",
			 function );

			result = -1;
		}
		memory_free(
		 *physical_volume_table );

		*physical_volume_table = NULL;
	}
	return( result );
}

/* Clears the physical volume table
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_table_clear(
     libvslvm_physical_volume_table_t *physical_volume_table,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_physical_volume_table_clear";
	int result            = 1;

	if( physical_volume_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume table.",
		 function );

		return( -1 );
	}
	if( physical_volume_table->physical_volumes_list != NULL )
	{
		if( libfdata_list_free(
		     &( physical_volume_table->physical_volumes_list ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free physical volumes list.",
			 function );

			result = -1;
		}
	}
	if( physical_volume_table->physical_volumes_cache != NULL )
	{
		if( libfcache_cache_free(
		     &( physical_volume_table->physical_volumes_cache ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free physical volumes cache.",
			 function );

			result = -1;
		}
	}
	if( memory_set(
	     physical_volume_table,
	     0,
	     sizeof( libvslvm_physical_volume_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to physical_volume table.",
		 function );

		result = -1;
	}
	return( result );
}

/* Initializes the phyiscal volumes
 * Returns 1 if successful or -1 on error
 */
int libvslvm_physical_volume_table_initialize_physical_volumes(
     libvslvm_physical_volume_table_t *physical_volume_table,
     int number_of_physical_volumes,
     libcerror_error_t **error )
{
	static char *function = "libvslvm_physical_volume_table_initialize_physical_volumes";
	int result            = 0;

	if( physical_volume_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid physical volume table.",
		 function );

		return( -1 );
	}
/* TODO add write support ? */
	result = libfdata_list_initialize(
	          &( physical_volume_table->physical_volumes_list ),
	          NULL,
	          NULL,
	          NULL,
	          (int (*)(intptr_t *, intptr_t *, libfdata_list_element_t *, libfcache_cache_t *, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libvslvm_physical_volume_read_element_data,
	          NULL,
	          LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create physical volumes list.",
		 function );

		goto on_error;
	}
	if( libfdata_list_resize(
	     physical_volume_table->physical_volumes_list,
	     number_of_physical_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize physical volumes list.",
		 function );

		goto on_error;
	}
	result = libfcache_cache_initialize(
		  &( physical_volume_table->physical_volumes_cache ),
		  LIBVSLVM_MAXIMUM_CACHE_ENTRIES_PHYSICAL_VOLUMES,
		  error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create physical volumes cache.",
		 function );

		goto on_error;
	}
	physical_volume_table->number_of_physical_volumes = number_of_physical_volumes;

	return( 1 );

on_error:
	if( physical_volume_table->physical_volumes_list != NULL )
	{
		libfdata_list_free(
		 &( physical_volume_table->physical_volumes_list ),
		 NULL );
	}
	return( -1 );
}

