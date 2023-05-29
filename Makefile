build:
	gcc src/*.c src/music/*.c src/vector/*.c src/utils/*.c src/words_repo/*.c src/bstree/*.c src/avl/*.c src/avl_freq/*.c -o main

run:
	./main
