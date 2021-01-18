/*
 * Stripe functions
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

#if !defined( _LIBVSLVM_INTERNAL_STRIPE_H )
#define _LIBVSLVM_INTERNAL_STRIPE_H

#include <common.h>
#include <types.h>

#include "libvslvm_extern.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvslvm_internal_stripe libvslvm_internal_stripe_t;

struct libvslvm_internal_stripe
{
	/* The physical volume name
	 */
	char *physical_volume_name;

	/* The physical volume name size
	 */
	size_t physical_volume_name_size;

	/* The data area offset
	 */
	off64_t data_area_offset;
};

int libvslvm_stripe_initialize(
     libvslvm_stripe_t **stripe,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_stripe_free(
     libvslvm_stripe_t **stripe,
     libcerror_error_t **error );

int libvslvm_internal_stripe_free(
     libvslvm_internal_stripe_t **internal_stripe,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_stripe_get_physical_volume_name_size(
     libvslvm_stripe_t *stripe,
     size_t *physical_volume_name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_stripe_get_physical_volume_name(
     libvslvm_stripe_t *stripe,
     char *physical_volume_name,
     size_t physical_volume_name_size,
     libcerror_error_t **error );

int libvslvm_internal_stripe_set_physical_volume_name(
     libvslvm_internal_stripe_t *internal_stripe,
     const char *physical_volume_name,
     size_t physical_volume_name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_stripe_get_data_area_offset(
     libvslvm_stripe_t *stripe,
     off64_t *data_area_offset,
     libcerror_error_t **error );

int libvslvm_stripe_set_data_area_offset(
     libvslvm_stripe_t *stripe,
     off64_t data_area_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_INTERNAL_STRIPE_H ) */

