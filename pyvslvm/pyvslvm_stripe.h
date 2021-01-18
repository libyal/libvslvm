/*
 * Python object wrapper of libvslvm_stripe_t
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

#if !defined( _PYVSLVM_STRIPE_H )
#define _PYVSLVM_STRIPE_H

#include <common.h>
#include <types.h>

#include "pyvslvm_libvslvm.h"
#include "pyvslvm_python.h"
#include "pyvslvm_segment.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvslvm_stripe pyvslvm_stripe_t;

struct pyvslvm_stripe
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvslvm stripe
	 */
	libvslvm_stripe_t *stripe;

	/* The pyvslvm segment object
	 */
	pyvslvm_segment_t *segment_object;
};

extern PyMethodDef pyvslvm_stripe_object_methods[];
extern PyTypeObject pyvslvm_stripe_type_object;

PyObject *pyvslvm_stripe_new(
           libvslvm_stripe_t *stripe,
           pyvslvm_segment_t *segment_object );

int pyvslvm_stripe_init(
     pyvslvm_stripe_t *pyvslvm_stripe );

void pyvslvm_stripe_free(
      pyvslvm_stripe_t *pyvslvm_stripe );

#if defined( __cplusplus )
}
#endif

#endif

