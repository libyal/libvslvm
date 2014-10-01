dnl Function to detect if libvslvm dependencies are available
AC_DEFUN([AX_LIBVSLVM_CHECK_LOCAL],
 [dnl Check for internationalization functions in libvslvm/libvslvm_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

