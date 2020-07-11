#include "tl_net_traffic.h"

TLNetTraffic::TLNetTraffic()
{
	state = nullptr;
}

void TLNetTraffic::setState(TLState* state)
{
	if (this->state)
		delete this->state;
	this->state = state;
}

void TLNetTraffic::handle()
{
	state->handle();
}
