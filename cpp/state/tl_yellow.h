#ifndef _TL_YELLOW_H_
#define _TL_YELLOW_H_

class TLYellow : public TLState
{
public:
	TLYellow(TLNetTraffic* context);
	void handle();

private:
	TLNetTraffic* context;
};

#endif /* _TL_YELLOW_H_ */
