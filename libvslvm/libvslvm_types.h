/*
 * The internal type definitions
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

#if !defined( _LIBVSLVM_INTERNAL_TYPES_H )
#define _LIBVSLVM_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBVSLVM for local use of libvslvm
 * The definitions in <libvslvm/types.h> are copied here
 * for local use of libvslvm
 */
#if defined( HAVE_LOCAL_LIBVSLVM )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libvslvm_handle {}		libvslvm_handle_t;
typedef struct libvslvm_logical_volume {}	libvslvm_logical_volume_t;
typedef struct libvslvm_physical_volume {}	libvslvm_physical_volume_t;
typedef struct libvslvm_segment {}		libvslvm_segment_t;
typedef struct libvslvm_stripe {}		libvslvm_stripe_t;
typedef struct libvslvm_volume_group {}		libvslvm_volume_group_t;

#else
typedef intptr_t libvslvm_handle_t;
typedef intptr_t libvslvm_logical_volume_t;
typedef intptr_t libvslvm_physical_volume_t;
typedef intptr_t libvslvm_segment_t;
typedef intptr_t libvslvm_stripe_t;
typedef intptr_t libvslvm_volume_group_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBVSLVM ) */

#endif /* !defined( _LIBVSLVM_INTERNAL_TYPES_H ) */

