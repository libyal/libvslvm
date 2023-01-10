/*
 * Raid functions
 *
 * 20190306
 * liubo
 */

#if !defined( _LIBVSLVM_INTERNAL_RAID_H )
#define _LIBVSLVM_INTERNAL_RAID_H

#include <common.h>
#include <types.h>

#include "libvslvm_extern.h"
#include "libvslvm_libcerror.h"
#include "libvslvm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

	/* eg
	raids = [
					"lv0_rmeta_0", "lv0_rimage_0",
					"lv0_rmeta_1", "lv0_rimage_1",
					"lv0_rmeta_2", "lv0_rimage_2",
					"lv0_rmeta_3", "lv0_rimage_3"
				]
	*/

	typedef struct libvslvm_internal_raid libvslvm_internal_raid_t;

	struct libvslvm_internal_raid
	{
		/* The meta name
		 */
		char *meta_name;

		/* The mata name size
		 */
		size_t meta_name_size;

		/* The image name
		 */
		char *image_name;

		/* The image name size
		 */
		size_t image_name_size;
	};

	int libvslvm_raid_initialize(
		libvslvm_raid_t **raid,
		libcerror_error_t **error);

	LIBVSLVM_EXTERN \
		int libvslvm_raid_free(
			libvslvm_raid_t **raid,
			libcerror_error_t **error);

	int libvslvm_internal_raid_free(
		libvslvm_internal_raid_t **internal_raid,
		libcerror_error_t **error);

	LIBVSLVM_EXTERN \
		int libvslvm_raid_get_meta_name_size(
			libvslvm_raid_t *raid,
			size_t *meta_name_size,
			libcerror_error_t **error);

	LIBVSLVM_EXTERN \
		int libvslvm_raid_get_meta_name(
			libvslvm_raid_t *raid,
			char *meta_name,
			size_t meta_name_size,
			libcerror_error_t **error);

	int libvslvm_raid_set_meta_name(
		libvslvm_raid_t *raid,
		const char *meta_name,
		size_t meta_name_size,
		libcerror_error_t **error);

	LIBVSLVM_EXTERN \
		int libvslvm_raid_get_image_name_size(
			libvslvm_raid_t *raid,
			size_t *image_name_size,
			libcerror_error_t **error);

	LIBVSLVM_EXTERN \
		int libvslvm_raid_get_image_name(
			libvslvm_raid_t *raid,
			char *image_name,
			size_t image_name_size,
			libcerror_error_t **error);

	int libvslvm_raid_set_image_name(
		libvslvm_raid_t *raid,
		const char *image_name,
		size_t image_name_size,
		libcerror_error_t **error);
#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSLVM_INTERNAL_RAID_H ) */

