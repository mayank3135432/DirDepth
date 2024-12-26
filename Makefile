a.out: main.c
	gcc -o a.out main.c
install: depth
	install -m 0755 depth ~/.local/bin/depth
clean:
	rm -f a.out