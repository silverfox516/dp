#include <iostream>
#include "tl_net_traffic.h"
#include "tl_red.h"
#include "tl_green.h"

TLRed::TLRed(TLNetTraffic* context) : context(context)
{
}

void TLRed::handle()
{
	std::cout << "reg light" << std::endl;
	context->setState(new TLGreen(context));
}
