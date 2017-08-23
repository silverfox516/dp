targets = tl
tl-objs = tl_net_traffic.o tl_red.o tl_green.o tl_yellow.o tl_main.o

all: $(targets)

tl: $(tl-objs)
	$(CXX) -o $@ $(tl-objs)

clean:
	rm -rf $(tl-objs) $(targets)
