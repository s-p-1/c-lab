all :
	@gcc display.c helper.c asscop.c graph.c expcalc.c avltree.c -lm -O3 -o spreadsheet
	@mv spreadsheet target/release

t1:
	@gcc display.c helper.c asscop.c graph.c expcalc.c avltree.c -lm -O3 -o spreadsheet
	@mv spreadsheet tests

test: t1
	@cd tests; \
	for i in test*.txt; do \
		./spreadsheet 999 18278 < $$i > $$i.out; \
		if diff -q $$i.out $$i.expected >/dev/null; then \
			echo "$$i: ✅ Passed"; \
		else \
			echo "$$i: ❌ Failed"; \
		fi; \
		rm $$i.out; \
	done

clean:
	-@cd tests; \
	rm -r *.out \
	rm spreadsheet || true
	-@cd target/release; \
	rm spreadsheet || true
	-@rm copasscode.aux copasscode.log copasscode.pdf copasscode.out || true


extreme: all
	@for i in tests/extremetest*.txt; do \
		./target/release/spreadsheet  < $$i > $$i.out; \
	done

report:
	@pdflatex copasscode.tex
	@xdg-open copasscode.pdf

