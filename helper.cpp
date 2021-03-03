#include<bits/stdc++.h>
#include<fstream>
#include<mysql_connection.h>
#include<cppconn/resultset.h>
#include<cppconn/driver.h>
#include<jsoncpp/json/json.h>
#include<cppconn/connection.h>
#include<cppconn/statement.h>
#include<cppconn/exception.h>

using namespace std;
using namespace sql;
using namespace Json;

int main(int argc,char* argv[]){
	Reader cr;
        Value cob;
        ifstream cifs("credential.json");
        cr.parse(cifs,cob);

        const string url=cob["url"].asString();
        const string user=cob["username"].asString();
        const string password=cob["password"].asString();
        const string database=cob["database"].asString();

	try{
		Driver& driver = *get_driver_instance();
        Connection& con = *driver.connect(url,user,password);
        con.setSchema(database);
        Statement& stmt=*con.createStatement();

		//ResultSet& rs=*stmt.executeQuery("SELECT count(*) FROM City_master");
		
		int n=8;//rs.getInt(0);
		int city_data[n][n];
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i==j) city_data[i][j]=0;
				else city_data[i][j]=-1;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<city_data[i][j]<<" ";
			}
			cout<<endl;
		}
		ResultSet& rs1=*stmt.executeQuery("SELECT city_id,connected_city_id,fare FROM farelist");

		while(rs1.next()){
			int a=rs1.getInt(1);
			int b=rs1.getInt(2);
			int c=rs1.getInt(3);
			city_data[a][b]=c;
		}

		cout<<endl;
		cout<<"City Matrix :"<<endl<<endl;

		for(int i=0;i<n;i++){
                        for(int j=0;j<n;j++){
                                cout<<city_data[i][j]<<"   ";
                        }
                        cout<<endl;
                }

	}catch(SQLException& e){
		cout<<"Error! "<<e.what()<<endl;
	}
	return 0;
}
