.PHONY: all clean
all: ../x86optab.h
clean:
	$(RM) x86optab.h x86gentab
../x86optab.h: x86optab.h
	cp x86optab.h ../x86optab.h
x86optab.h: x86optab.txt x86gentab 
	./x86gentab <$< >$@
x86gentab: x86gentab.c
	$(LINK.c) $< $(LDLIBS) -o $@
