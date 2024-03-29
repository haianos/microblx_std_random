/*
 * random microblx function block (autogenerated, don't edit)
 */

#include <ubx.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* includes types and type metadata */
#include "../types/random_info.h"
#include "../types/random_info.h.hexarr"
#include "../types/random_config.h"
#include "../types/random_config.h.hexarr"


/* block meta information */
char random_meta[] =
        " { doc='A random number generator function block',"
        "   real-time=true,"
        "}";

/* declaration of block configuration */
ubx_config_t random_config[] = {
        { .name="min_max_config", .type_name = "struct random_config", .doc="" },
        { NULL },
};

/* declaration port block ports */
ubx_port_t random_ports[] = {
        { .name="seed", .in_type_name="unsigned int", .in_data_len=1, .doc=""  },
        { .name="rnd", .out_type_name="unsigned int", .out_data_len=1, .doc=""  },
        { NULL },
};

/* declare a struct port_cache */
struct random_port_cache {
        ubx_port_t* seed;
        ubx_port_t* rnd;
};

/* declare a helper function to update the port cache this is necessary
 * because the port ptrs can change if ports are dynamically added or
 * removed. This function should hence be called after all
 * initialization is done, i.e. typically in 'start'
 */
static void update_port_cache(ubx_block_t *b, struct random_port_cache *pc)
{
        pc->seed = ubx_port_get(b, "seed");
        pc->rnd = ubx_port_get(b, "rnd");
}


/* for each port type, declare convenience functions to read/write from ports */
def_read_fun(read_seed, unsigned int)
def_write_fun(write_rnd, unsigned int)

/* block operation forward declarations */
int random_init(ubx_block_t *b);
int random_start(ubx_block_t *b);
void random_stop(ubx_block_t *b);
void random_cleanup(ubx_block_t *b);
void random_step(ubx_block_t *b);


/* put everything together */
ubx_block_t random_block = {
        .name = "random/random",
        .type = BLOCK_TYPE_COMPUTATION,
        .meta_data = random_meta,
        .configs = random_config,
        .ports = random_ports,

        /* ops */
        .init = random_init,
        .start = random_start,
        .stop = random_stop,
        .cleanup = random_cleanup,
        .step = random_step,
};


/* random module init and cleanup functions */
int random_mod_init(ubx_node_info_t* ni)
{
        DBG(" ");
        int ret = -1;

        if(ubx_block_register(ni, &random_block) != 0)
                goto out;

        ret=0;
out:
        return ret;
}

void random_mod_cleanup(ubx_node_info_t *ni)
{
        DBG(" ");
        ubx_block_unregister(ni, "random/random");
}

