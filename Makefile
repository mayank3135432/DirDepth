depth: main.c
	gcc -o depth main.c
install: depth
	install -m 0755 depth ~/.local/bin/depth
clean:
	rm -f depth