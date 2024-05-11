git:
	@echo "Building dagit"
	@g++ -c *.cpp **/*.cpp
	@g++ *.o -o dagit -lz -lssl -lcrypto