#include <iostream>
#include <unistd.h>
#include "tl_net_traffic.h"
#include "tl_red.h"

int main(void)
{
	TLNetTraffic *netTraffic = new TLNetTraffic();
	int count = 0, i = 0;
	int seconds;

	netTraffic->setState(new TLRed(netTraffic));

	while (1) {
		if (i % 3)
			std::cout << "session " << ((i + 1) / 3) + 1 << std::endl;

		if (count == 0) {
			seconds = 6;
			count = 1;
		} else if (count == 1) {
			seconds = 5;
			count = 2;
		} else if (count == 2) {
			seconds = 5;
			count = 0;
		}

		sleep(seconds);
		netTraffic->handle();
		i++;
	}

	delete netTraffic;

	return 0;
}
