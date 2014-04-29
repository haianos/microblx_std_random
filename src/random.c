#include "random.h"

/* define a structure for holding the block local state. By assigning an
 * instance of this struct to the block private_data pointer (see init), this
 * information becomes accessible within the hook functions.
 */
struct rnd_info
{
        /* add custom block local data here */
        struct random_info info;
        /* this is to have fast access to ports for reading and writing, without
         * needing a hash table lookup */
        struct random_port_cache ports;
};

struct random_port_cache ports;
/* init */
int random_init(ubx_block_t *b)
{
        int ret = -1;
        struct rnd_info *inf;

        /* allocate memory for the block local state */
        if ((inf = (struct rnd_info*)calloc(1, sizeof(struct rnd_info)))==NULL) {
                ERR("random: failed to alloc memory");
                ret=EOUTOFMEM;
                goto out;
        }
        b->private_data=inf;
        update_port_cache(b, &inf->ports);
        ret=0;
out:
        return ret;
}

/* start */
int random_start(ubx_block_t *b)
{
  DBG("in");
  uint32_t seed, ret;
  unsigned int clen;
  struct random_config* rndconf;
  struct rnd_info* inf;

  inf=(struct rnd_info*) b->private_data;

  /* get and store min_max_config */
  rndconf = (struct random_config*) ubx_config_get_data_ptr(b, "min_max_config", &clen);
  inf->info.min = rndconf->min;
  inf->info.max = (rndconf->max == 0) ? INT_MAX : rndconf->max;

  /* seed is allowed to change at runtime, check if new one available */
  ubx_port_t* seed_port = ubx_port_get(b, "seed");
  ret = read_seed(seed_port, &seed);

  if(ret>0) {
    DBG("starting component. Using seed: %d, min: %d, max: %d", seed, inf->info.min, inf->info.max);
    srandom(seed);
  } else {
    DBG("starting component. Using min: %d, max: %d", inf->info.min, inf->info.max);
  }
  return ret;
}

/* stop */
void random_stop(ubx_block_t *b)
{
}

/* cleanup */
void random_cleanup(ubx_block_t *b)
{
        free(b->private_data);
}

/* step */
void random_step(ubx_block_t *b)
{
  unsigned int rand_val;
  struct rnd_info* inf;

  inf=(struct rnd_info*) b->private_data;

  ubx_port_t* rand_port = ubx_port_get(b, "rnd");
  rand_val = random();
  rand_val = (rand_val > inf->info.max) ? (rand_val%inf->info.max) : rand_val;
  rand_val = (rand_val < inf->info.min) ? ((inf->info.min + rand_val)%inf->info.max) : rand_val;

  write_rnd(rand_port, &rand_val);
}

