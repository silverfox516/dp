#include <iostream>
#include "tl_net_traffic.h"
#include "tl_yellow.h"
#include "tl_green.h"

TLYellow::TLYellow(TLNetTraffic* context) : context(context)
{
}

void TLYellow::handle()
{
	std::cout << "yellow light" << std::endl;
	context->setState(new TLGreen(context));
}
