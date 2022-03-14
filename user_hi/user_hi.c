#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

void printStatsArray(long stats[]);
void removeSpaces(char *s)
{
    char *d = s;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    } while (*s++ = *d++);
}
int main(int argc, char *argv[])
{
    char *commandToLaunch = argv[1];
    char pciDevArg[] = "pci_dev";
    char netDeviceArg[] = "net_device";
    char helloArg[] = "hello";
    if (strcmp(commandToLaunch, pciDevArg) == 0)
    {
        printf("call pci\n");
        int ans = 0;
        char packet[20000];
        ans = syscall(335, &packet);
        removeSpaces(packet);
        printf("no_pci_dev: %d\n", ans);
        printf("packet: %s\n", packet);
    }
    else if (strcmp(commandToLaunch, netDeviceArg) == 0)
    {
        printf("call net\n");
        int ans = 0;
        char name[16];
        long stats[24];
        ans = syscall(334, &stats, &name);
        if (ans == 1)
        {
            printf("there is no net devices left\n");
            return;
        }
        printf("net_device_name: %s\n", name);
        printf("net_stats: %d\n", stats[23]);
        printStatsArray(stats);
    }
    else if (strcmp(commandToLaunch, helloArg) == 0)
    {
        printf("call hello\n");
        int ans = 0;
        ans = syscall(333);
    }
    else
    {
        printf("ups, no such command as %s\n", commandToLaunch);
    }
    printf("\n");

    return 0;
}

void printStatsArray(long stats[])
{
    // statsArray[0] = stats->rx_packets;
    // statsArray[1] = stats->tx_packets;
    // statsArray[2] = stats->rx_bytes;
    // statsArray[3] = stats->tx_bytes;
    // statsArray[4] = stats->rx_errors;
    // statsArray[5] = stats->tx_errors;
    // statsArray[6] = stats->rx_dropped;
    // statsArray[7] = stats->tx_dropped;
    // statsArray[8] = stats->multicast;
    // statsArray[9] = stats->collisions;
    // statsArray[10] = stats->rx_length_errors;
    // statsArray[11] = stats->rx_over_errors;
    // statsArray[12] = stats->rx_crc_errors;
    // statsArray[13] = stats->rx_frame_errors;
    // statsArray[14] = stats->rx_fifo_errors;
    // statsArray[15] = stats->rx_missed_errors;
    // statsArray[16] = stats->tx_aborted_errors;
    // statsArray[17] = stats->tx_carrier_errors;
    // statsArray[18] = stats->tx_fifo_errors;
    // statsArray[19] = stats->tx_heartbeat_errors;
    // statsArray[20] = stats->tx_window_errors;
    // statsArray[21] = stats->rx_compressed;
    // statsArray[22] = stats->tx_compressed;
    // statsArray[23] = 24;
    if (stats[23] != 24)
    {
        printf("Stats array is not valid\n");
        return;
    }
    printf("\nrx_packets: %d", stats[0]);
    printf("\ntx_packets: %d", stats[1]);
    printf("\nrx_bytes: %d", stats[0]);
    printf("\ntx_bytes: %d", stats[0]);
    printf("\nrx_errors: %d", stats[0]);
    printf("\ntx_errors: %d", stats[0]);
    printf("\nrx_dropped: %d", stats[0]);
    printf("\ntx_dropped: %d", stats[0]);
    printf("\nmulticast: %d", stats[0]);
    printf("\ncollisions: %d", stats[0]);
    printf("\nrx_length_errors: %d", stats[0]);
    printf("\nrx_over_errors: %d", stats[0]);
    printf("\nrx_crc_errors: %d", stats[0]);
    printf("\nrx_frame_errors: %d", stats[0]);
    printf("\nrx_fifo_errors: %d", stats[0]);
    printf("\nrx_missed_errors: %d", stats[0]);
    printf("\ntx_aborted_errors: %d", stats[0]);
    printf("\ntx_carrier_errors: %d", stats[0]);
    printf("\ntx_fifo_errors: %d", stats[0]);
    printf("\ntx_heartbeat_errors: %d", stats[0]);
    printf("\ntx_window_errors: %d", stats[0]);
    printf("\nrx_compressed: %d", stats[0]);
    printf("\ntx_compressed: %d", stats[0]);
}