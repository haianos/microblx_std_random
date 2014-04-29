/*
 * module function declaration for library randommod header (autogenerated)
 */
 
#include <ubx.h>

// Initialization and cleanup function declaration
int randommod_mod_init(ubx_node_info_t* ni);
void randommod_mod_cleanup(ubx_node_info_t* ni);


/* declare module init and cleanup functions, so that the ubx core can
 * find these when the module is loaded/unloaded.
 * Please edit your license in macro LICENSE_SPDX */
UBX_MODULE_INIT(randommod_mod_init)
UBX_MODULE_CLEANUP(randommod_mod_cleanup)
UBX_MODULE_LICENSE_SPDX(GPL-2.0+)

