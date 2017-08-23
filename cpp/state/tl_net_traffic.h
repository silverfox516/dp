#ifndef _TL_NET_TRAFFIC_H_
#define _TL_NET_TRAFFIC_H_

#include "tl_state.h"

class TLNetTraffic
{
public:
	TLNetTraffic();
	void setState(TLState* state);
	void handle();

private:
	TLState* state;
};

#endif /* _TL_NET_TRAFFIC_H_ */
