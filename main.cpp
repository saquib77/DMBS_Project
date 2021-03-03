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
#define INF 1000000000

class City{
	public:
    int cityId;
    vector<pair<int,int>> neighbour;
    City(int cityId){
        this->cityId=cityId;
    }
    void add_Neighbour(int cityId,int fare){
        pair<int,int>p;
        p.first=fare;
        p.second=fare;
        neighbour.push_back(p);
    }
};
int minFare(vector<City*>g,int s,int d,vector<int>& path){
	vector<int>dist(g.size());
	bool visited[g.size()];
	for(int i=0;i<g.size();i++){
		visited[i]=false;
		path[i]=-1;
		dist[i]=INF;
	}
	dist[s]=0;
	path[s]=-1;
	int current =s;
	unordered_set<int>sett;
	while(true){
		visited[current]=true;
		for(int i=0;i< g[current]->neighbour.size();i++){
			int v=g[current]->neighbour[i].first;
			if(visited[v]) continue;
			sett.insert(v);
			int alt=dist[current]+g[current]->neighbour[i].second;
			if(alt<dist[v]){
				dist[v]=alt;
				path[v]=current;
			}
		}
		sett.erase(current);
		if(sett.empty())
			break;
		int minDist=INF;
		int index=0;
		for(int a:sett){
			if(dist[a]<minDist){
				minDist=dist[a];
				index=a;
			}
		}
		current=index;
	}
	return dist[d];
}

void populate(int ar[8][8],int n){
	for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                      if(i==j&& i>=1 && j>=1) ar[i][j]=0;
                      else ar[i][j]=-1;
        	}
	}
}
int main(int argc,char*argv[]){
    Reader cr;
    Value cob;
    ifstream cifs("credential.json");
    cr.parse(cifs,cob);

    const string url = cob["url"].asString();
    const string user = cob["username"].asString();
    const string password = cob["password"].asString();
    const string database = cob["database"].asString();
    
    try{
        Driver& driver = *get_driver_instance();
        Connection& con = *driver.connect(url,user,password);
        con.setSchema(database);
        Statement& stmt = *con.createStatement();
        
        ResultSet& rs = *stmt.executeQuery("select count(*) from City_Master");
        int n;
        if(rs.next()){
            n=rs.getInt(1);
        }
    
        ResultSet& res = *stmt.executeQuery("SELECT * FROM City_Master");
		cout<<"City Id     City Name"<<endl;
        while(res.next()){
            cout<<"  "<<res.getInt(1)<<"           "<<res.getString(2)<<endl;
        }
    
        int id1,id2;
		a:
		cout<<"Enter City Id of Source"<<"(1 to "<<n<<") :";
		cin>>id1;
		if(id1 > n){
			cout<<"City Id "<<id1<<" not Found!"<<endl;
			cout<<"WRONG CITY ID ! Enter it Again !"<<endl;
			goto a;
		}
		b:
		cout<<"Enter City Id of Destination<<"<<"(1 to "<<n<<") :";
		cin>>id2;
		if(id2>n){
			cout<<"City Id "<<id2<<" not Found!"<<endl;
			cout<<"WRONG CITY ID ! Enter it Again !"<<endl;
			goto b;
		}
    
        int a,b,c,city_data[8][8];
		populate(city_data,n+1);

		vector<City*>v;
		for(int i=0;i<n+1;i++){
			City* a0=new City(i);
			v.push_back(a0);
		}
    
        ResultSet& rs1=*stmt.executeQuery("SELECT * FROM farelist");
		while(rs1.next()){
			a=rs1.getInt(1);
			b=rs1.getInt(2);
			c=rs1.getInt(3);
			city_data[a][b]=c;
			if(city_data[a][b]>0){
				v[a]->add_Neighbour(b,c);
			}
		}
    
        vector<int>pt(v.size());
		int fare=minFare(v,id1,id2,pt);
		if(fare!=INF && fare!=0){
			cout<<"Min Fare From "<<id1<<" to "<<id2<<" is : "<<fare<<endl;
        }else{
			cout<<"No Path Found for "<<id1<<" to "<<id2<<endl;
        }
    }catch(SQLException& e){
        cout<<"Error !"<<e.what()<<endl;
    }
    return 0;
}