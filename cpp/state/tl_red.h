#ifndef _TL_RED_H_
#define _TL_RED_H_

class TLRed : public TLState
{
public:
	TLRed(TLNetTraffic* context);
	void handle();

private:
	TLNetTraffic* context;
};

#endif /* _TL_RED_H_ */
