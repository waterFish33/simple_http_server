http_server:http_server.cpp
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -rf http_server
