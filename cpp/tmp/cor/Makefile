targets = help simple1
help-objs = help_handler.o widget.o dialog.o button.o application.o cor_main.o
simple1-objs = simple_example1.o

all: $(targets)

help: $(help-objs)
	$(CXX) -o $@ $(help-objs)

simple1: $(simple1-objs)
	$(CXX) -o $@ $(help-objs)

clean:
	rm -rf $(help-objs) $(simple1-objs) $(targets)
