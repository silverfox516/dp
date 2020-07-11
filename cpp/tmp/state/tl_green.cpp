#include <iostream>
#include "tl_net_traffic.h"
#include "tl_green.h"
#include "tl_yellow.h"

TLGreen::TLGreen(TLNetTraffic* context) : context(context)
{
}

void TLGreen::handle()
{
	std::cout << "green light" << std::endl;
	context->setState(new TLYellow(context));
}
