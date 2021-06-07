#! /bin/bash
name="citydata.json"
g++ -std=c++11 -I/usr/include/cppconn -o run citySeeder.cpp -ljsoncpp -L/usr/lib -lmysqlcppconn
if [ "$name" = "citydata.json" ]
then
	./run "$name"
	g++ -std=c++11 -I/usr/include/cppconn -o run showCity.cpp -ljsoncpp -L/usr/lib -lmysqlcppconn
	./run
	g++ -std=c++11 -I/usr/include/cppconn -o run main.cpp -ljsoncpp -L/usr/lib -lmysqlcppconn
	./run
else
	echo "Please Specify JSON File!"
fi
