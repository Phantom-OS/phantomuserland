#include <disk.h>
#include <disk_q.h>
#include <device.h>
#include <genode_disk_private.h>

void driver_genode_get_disk_dev();

phantom_device_t *driver_genode_disk_probe();

static phantom_disk_partition_t *phantom_create_genode_partition_struct(long size, genode_disk_dev_t *vd);

// Initialization and registration of a disk inside the system
void driver_genode_disk_init();

// Main function for performing I/O
int driver_genode_disk_asyncIO(struct phantom_disk_partition *part, pager_io_request *rq);