#include<iostream>
#include<string>
#include<sstream>
#include<mysql_connection.h>
#include<cppconn/resultset.h>
#include<cppconn/driver.h>
#include<fstream>
#include<jsoncpp/json/json.h>
#include<cppconn/connection.h>
#include<cppconn/statement.h>
#include <cppconn/exception.h>

#define DBHOST "localhost"
#define USER "root"
#define PASSWORD "Saquib@77"
#define DATABASE "DMBS"

using namespace std;
using namespace sql;
using namespace Json;

int main(int argc,char* argv[]){
	const string url=DBHOST;
        const string user=USER;
        const string password=PASSWORD;
        const string database=DATABASE;
	try{
		if(argc!=2){
			cout<<"JSON File Missing"<<endl;
			return 0;
		}
		ifstream ifs(argv[1]);
		Reader r;
		Value ob;
		r.parse(ifs,ob);
		Driver& driver = *get_driver_instance();
                Connection& con = *driver.connect(url,user,password);
                con.setSchema(database);
                Statement& stmt=*con.createStatement();
		for(auto i : ob.getMemberNames()){
                        string s=i;
                        for(auto j : ob[s].getMemberNames()){
                                string s1=j;
                                string a=ob[s][s1].asString();
                                stmt.execute("INSERT INTO farelist VALUES( (SELECT city_id FROM City_Master WHERE (city_name = '"+s+"'))"
                                ",(SELECT city_id FROM City_Master WHERE (city_name = '"+s1+"')), '"+a+"')");
                        }
                }
	}catch(SQLException& e){
		cout<<"Error! "<<e.what()<<endl;
	}
	return 0;
}