compile: src/main.c src/model/hero/hero.c src/model/enemy/enemy.c src/model/map/map.c src/data_structures/stack.c src/feature/heros_journey.c
	gcc -o EXEC_GCC src/main.c src/model/hero/hero.c src/model/enemy/enemy.c src/model/map/map.c src/data_structures/stack.c src/feature/heros_journey.c -g

run:
	./EXEC_GCC

clean:
	rm ./EXEC_GCC

both:
	make compile && make run