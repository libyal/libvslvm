/*
 * Segment functions
 *
 * Copyright (C) 2014-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVSLVM_SEGMENT_H )
#define _LIBVSLVM_SEGMENT_H

#include <common.h>
#include <types.h>

#include "libvslvm_extern.h"
#include "libvslvm_libcdata.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

	/*
	* 20190306
	* liubo
	* 为了兼容，raid lvm情况，当前添加raid类型枚举
	*/
#define STRIPED		"striped"
#define  RAID1		"raid1"			//RAID1 mirroring
#define  RAID4		"raid4"  		//RAID4 dedicated parity disk
#define  RAID5		"raid5"  		//Same as raid5_ls
#define RAID5_LA	"raid5_la"		//RAID5 left asymmetric.				Rotating parity 0 with data continuation
#define RAID5_RA	"raid5_ra"	 	//RAID5 right asymmetric.				Rotating parity N with data continuation
#define RAID5_LS	"raid5_ls"		//RAID5 left symmetric.					Rotating parity 0 with data restart
#define RAID5_RS	"raid5_rs"		//RAID5 right symmetric.				Rotating parity N with data restart
#define RAID6 		"raid6"			//Same as raid6_zr
#define RAID6_ZR	"raid6_zr"		//RAID6 zero restart					Rotating parity zero (left-to-right) with data restart
#define RAID6_NR	"raid6_nr"	//RAID6 N restart						Rotating parity N (left-to-right) with data restart
#define RAID6_NC	"raid6_nc"	//RAID6 N continue					Rotating parity N (left-to-right) with data continuation
#define RAID10 		"raid10"		//(Red Hat Enterprise Linux 6.4 and later						Striped mirrors 				Striping of mirror sets


typedef struct libvslvm_internal_segment libvslvm_internal_segment_t;

struct libvslvm_internal_segment
{
	/* The name
	 */
	char *name;

	/* The name size
	 */
	size_t name_size;

	/* The stripes array
	 */
	libcdata_array_t *stripes_array;

	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;

	/************************************************************
	20190306 	liubo	考虑到兼容热raid的情况，做以下添加	
	****************************************************************/
	/* the type stripe or raids，use E_SEGMENT_TYPE
	*/
	int type;  
	
   /*the stripe size ；only type = RAIDS ,the value makeing sense, sec; 
	*/
	 uint32_t  stripe_size;
	
	/*the raids array
	*/
	libcdata_array_t* raids_array; 
};

int libvslvm_segment_initialize(
     libvslvm_segment_t **segment,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_free(
     libvslvm_segment_t **segment,
     libcerror_error_t **error );

int libvslvm_internal_segment_free(
     libvslvm_internal_segment_t **internal_segment,
     libcerror_error_t **error );

int libvslvm_internal_segment_set_name(
     libvslvm_internal_segment_t *internal_segment,
     const char *name,
     size_t name_size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_range(
     libvslvm_segment_t *segment,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_offset(
     libvslvm_segment_t *segment,
     off64_t *offset,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_size(
     libvslvm_segment_t *segment,
     size64_t *size,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_number_of_stripes(
     libvslvm_segment_t *segment,
     int *number_of_stripes,
     libcerror_error_t **error );

LIBVSLVM_EXTERN \
int libvslvm_segment_get_stripe(
     libvslvm_segment_t *segment,
     int stripe_index,
     libvslvm_stripe_t **stripe,
     libcerror_error_t **error );

int libvslvm_segment_append_stripe(
     libvslvm_segment_t *segment,
     libvslvm_stripe_t *stripe,
     libcerror_error_t **error );

/*************************************************************************
* 20190306 liubo raid
**************************************************************************/
//int libvslvm_segment_set_type(
//	libvslvm_segment_t *segment,
//	const char *type,
//	size_t type_size,
//	libcerror_error_t **error);

LIBVSLVM_EXTERN \
int libvslvm_segment_get_number_of_raids(
	libvslvm_segment_t *segment,
	int *number_of_raids,
	libcerror_error_t **error);

LIBVSLVM_EXTERN \
int libvslvm_segment_get_raid(
	libvslvm_segment_t *segment,
	int raid_index,
	libvslvm_raid_t **raid,
	libcerror_error_t **error);

int libvslvm_segment_append_raid(
	libvslvm_segment_t *segment,
	libvslvm_raid_t *raid,
	libcerror_error_t **error);

LIBVSLVM_EXTERN \
int libvslvm_segment_get_type(
	libvslvm_segment_t *segment,
	uint32_t *type,
	libcerror_error_t **error);

LIBVSLVM_EXTERN \
int libvslvm_segment_get_stripe_size(
	libvslvm_segment_t *segment,
	uint32_t *stripe_size,
	libcerror_error_t **error);


#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_SEGMENT_H ) */

