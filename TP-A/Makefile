SHELL := /bin/bash
SHARE := src util task.md data task.md task.pdf Makefile src/author/solution.pdf

.PHONY: all clean distclean dist data test

all: $(SHARE)

%.tex: %.md util/pandoc-latex.tex
	pandoc --template $(word 2,$^) --variable monofont='Bitstream Vera Sans Mono' --variable cjkfont='WenQuanYi Micro Hei' $< -t latex | opencc -c /usr/share/opencc/zht2zhs.ini > $@

%.pdf: %.tex
	xelatex -interaction=nonstopmode -output-directory=$(dir $@) $<

data: $(foreach i,$(shell seq -w 20),data/$i.in data/$i.out)

build:
	install -d $@

data/%.in: data/generator.rb
	i=$$(bc <<< $*); \
	((n = 3**((i-1)/3+1)/2)); \
	((nn = (n+5)*n)); \
	$< $$n $$nn > $@

data/%.out: data/%.in | build/queue
	build/queue < $< > $@

build/queue: src/author/solution.cc | build
	$(LINK.cc) $< -o $@

build/queue-hs: src/author/solution.hs | build
	ghc --make -O2 $< -o $@ -outputdir build

test: build/queue-hs
	@for i in `seq -w 20`; do \
		echo -e "\e[36mtesting $$i"; \
		$< < data/$$i.in | diff -u - data/$$i.out && echo '  pass'; \
	done

dist: $(SHARE)
	tar zcf TP-A.tar.gz --transform 's,^,TP-A/,' $(SHARE) --exclude \*.in --exclude \*.out

dist2: $(SHARE)
	tar zcf TP-A.tar.gz --transform 's,^,TP-A/,' $(SHARE)

clean:
	$(RM) -r {.,src/author}/*.{log,aux,out} build

distclean: clean
	$(RM) data/*.{in,out} {.,src/author}/*.pdf
