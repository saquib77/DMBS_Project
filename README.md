                                                    
# Decision Making Bash Script

### How to use  :
> Run 'run.sh' file with one command line argument that must '.sh' file that have information.
first give permission to run the shell script `chmod +x run.sh`
then run the script on terminal Example: `./run.sh`

### portability :
> We have a file name credentials.json file you can edit that file in order to change credential 
information according to user  the contain information about  database,user,password and localhost.

### Description :
> In this project we are creating database that ketp tables:
1. citydata.json:  
> We are insert all city informatin in 'citydata.json'.
2. citySeeder.cpp:
> Run this file and then it will fetch all data from `citydata.json` file and after that it will invoke
mysql server. In mysql server is create two table **1. citymaster** and **2. cityId** 
both are information will fetch from `citydata.json` & **city id**, **city name** and **fare**
it will seed path and cost between two city and then it will view all city in CLI.
3. main.cpp:
> The './main' file used to create database and and tables store the information in the table by 
any json file the json file have the information about the fare between the cities.
after that, './app' file ask for source and destination cities that app file get the fare_list 
table and create a graph .

> Then we apply `Min-cost algorithm` on that graph in order to get the min fare between the cities.

> Finally, the it will output the result that shows that minimum cost between the cities. 


### Commands :

> Internaly all this command using run.sh shell scripting file and we are using terminal and simply ./run.sh command into terminal.

```
g++ -std=c++11 -I/usr/include/cppconn -o run citySeeder.cpp -ljsoncpp -L/usr/lib -lmysqlcppconn
**and**
g++ -std=c++11 -I/usr/include/cppconn -o run main.cpp -ljsoncpp -L/usr/lib -lmysqlcppconn

```
	
> RUN COMMAND
``` ./run.sh ```
**Note :**
1.	-lmysqlcppconn	`use for mysql`
2.	-ljsoncpp	`use for json`
3.  g++ -std=c++11 `use for c++11`


### Pre-Requirements :

1.	jsoncpp setup
2.	mysql
3.	mysqlcpp-connector setup
4.  g++ compiler 

### Future Enhancement : 
> 1. Add city data & fare API.

> 2. Total Time taken to reach to Source to Destination.

> 3. GUI using QT5+.

> 4. Core Algorithm(Min-Path) Enhancement.

> 5. Remote DATABASE Implementation.