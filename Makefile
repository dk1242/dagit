git:
	@echo "Building dagit"
	@g++ -c *.cpp
	@g++ *.o -o dagit