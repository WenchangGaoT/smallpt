main: main.cpp
	g++ -O3 -fopenmp main.cpp ./src/object.cpp ./src/_random.cpp ./src/canvas.cpp -o main

test:
	time ./main 70
	# python3 show_image.py
