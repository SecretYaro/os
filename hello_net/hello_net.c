#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>

struct net_device *netDev;

long statsArray[24];
char netDeviceName[16]; //16
int sendOnceNet = 0;

void copy_string(char *target, char *source)
{
    while (*source)
    {
        *target = *source;
        source++;
        target++;
    }
    *target = '\0';
}

SYSCALL_DEFINE2(hello_net, long *, arrayAddress, char *, nameAddress)
{

    struct net_device_stats *stats;
    // char *name[IFNAMSIZ]; //16
    // if (sendOnceNet == 1)
    // {
    //     _copy_to_user(nameAddress, &netDeviceName, sizeof netDeviceName);
    //     _copy_to_user(arrayAddress, &statsArray, sizeof statsArray);
    //     // put_user(netDeviceName, nameAddress);
    //     // put_user(statsArray, arrayAddress);
    //     printk("sys_hello_net fast answer\n");
    //     return 0;
    // }

    printk("v.5");
    printk("sys_hello_net started\n");

    read_lock(&dev_base_lock);

    if (netDev)
    {
        netDev = next_net_device(netDev);
    }
    else
    {
        netDev = first_net_device(&init_net);
    }
    if (netDev)
    {
        while (netDev)
        {
            printk(KERN_INFO "found [%s]\n", netDev->name);
            stats = &netDev->stats;
            copy_string(netDeviceName, netDev->name);

            printk("sys_hello_net: %s", &netDev->name);
            printk("sys_hello_net: %d", &netDev->stats);
            if (stats)
            {
                break;
            }
            netDev = next_net_device(netDev);
        }
    }
    else
    {
        return 1;
        printk("sys_hello_net looks like there is no net_device\n");
    }
    read_unlock(&dev_base_lock);

    statsArray[0] = stats->rx_packets;
    statsArray[1] = stats->tx_packets;
    statsArray[2] = stats->rx_bytes;
    statsArray[3] = stats->tx_bytes;
    statsArray[4] = stats->rx_errors;
    statsArray[5] = stats->tx_errors;
    statsArray[6] = stats->rx_dropped;
    statsArray[7] = stats->tx_dropped;
    statsArray[8] = stats->multicast;
    statsArray[9] = stats->collisions;
    statsArray[10] = stats->rx_length_errors;
    statsArray[11] = stats->rx_over_errors;
    statsArray[12] = stats->rx_crc_errors;
    statsArray[13] = stats->rx_frame_errors;
    statsArray[14] = stats->rx_fifo_errors;
    statsArray[15] = stats->rx_missed_errors;
    statsArray[16] = stats->tx_aborted_errors;
    statsArray[17] = stats->tx_carrier_errors;
    statsArray[18] = stats->tx_fifo_errors;
    statsArray[19] = stats->tx_heartbeat_errors;
    statsArray[20] = stats->tx_window_errors;
    statsArray[21] = stats->rx_compressed;
    statsArray[22] = stats->tx_compressed;
    statsArray[23] = 24;

    _copy_to_user(nameAddress, &netDeviceName, sizeof netDeviceName);
    _copy_to_user(arrayAddress, &statsArray, sizeof statsArray);
    // put_user(netDeviceName, nameAddress);
    // put_user(statsArray, arrayAddress);
    sendOnceNet = 1;
    printk("sys_hello_net: %d", statsArray[2]);
    printk("sys_hello_net finished\n");
    return 0;
}