default:
	# write command to test your files (you do not need it for your submissions)
	g++ -Wall q1.cpp -o q1.out 
	g++ -Wall q2.cpp -o q2.out 
	g++ -Wall main.cpp -o main.out

clean:
	rm *.out
