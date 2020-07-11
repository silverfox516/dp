#ifndef _TL_GREEN_H_
#define _TL_GREEN_H_

class TLGreen : public TLState
{
public:
	TLGreen(TLNetTraffic* context);
	void handle();

private:
	TLNetTraffic* context;
};

#endif /* _TL_GREEN_H_ */
