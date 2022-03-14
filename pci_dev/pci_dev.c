#include <linux/kernel.h>
// #include <linux/syscalls.h>
// #include <linux/mod_devicetable.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/types.h>

// #include "./names.h"
// #include <linux/usb/us>
// #include <linux/usb/typec.h>
// #include <linux/fs.h>

void atoa(char *buck, long number)
{
	sprintf(buck, "%ld", number);
}
char packet[20000] = "Packet Start\n";
int sendOncePci = 0;

SYSCALL_DEFINE1(pci_dev, char *, packetAddress)
{

	struct pci_dev *pdev;
	int count = 0;

	if (sendOncePci == 1)
	{
		printk("sys_pci_dev fast answer\n");
		_copy_to_user(packetAddress, &packet, sizeof(packet));
		// put_user(packet, packetAddress);
		return no_pci_devices();
	}
	printk("v.5.5");
	printk("sys_pci_dev started\n");

	pdev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pdev);
	printk("sys_pci_dev test\n");
	printk("sys_pci_dev %s\n", pci_name(pdev));

	printk("sys_pci_dev test_end\n");
	while (pdev)
	{
		printk("sys_pci_dev device exists\n");
		char *pciName = pci_name(pdev);
		char vendorName[16];
		atoa(vendorName, (long)&pdev->vendor);

		char className[16];
		atoa(className, (long)&pdev->class);

		char sVendorName[16];
		atoa(sVendorName, (long)&pdev->subsystem_vendor);

		char sDeviceName[16];
		atoa(sDeviceName, (long)&pdev->subsystem_device);

		strcat(packet, "#count: ");

		char countString[16];
		atoa(countString, (long)count);

		strcat(packet, countString);

		strcat(packet, "\nname: ");
		strcat(packet, pciName);
		;

		strcat(packet, "\nvendor: ");
		strcat(packet, vendorName);

		strcat(packet, "\nclass: ");
		strcat(packet, className);

		strcat(packet, "\nsubsystem_vendor: ");
		strcat(packet, sVendorName);

		strcat(packet, "\nsubsystem_device: ");
		strcat(packet, sDeviceName);
		strcat(packet, "\n");

		pdev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pdev);
		count++;
		printk("sys_pci_dev count done");
	}
	strcat(packet, "Packet End\n");
	printk("sys_pci_dev spacket ready");
	_copy_to_user(packetAddress, &packet, sizeof packet);
	// put_user(packet, packetAddress);
	sendOncePci = 1;
	printk("sys_pci_dev: %s", packet);
	printk("sys_pci_dev finished\n");
	return no_pci_devices();
}
