#include <iostream>
using namespace std;

//Graph Variables
class Edge
{
public:
    char src;
    char dest;
    int len;
    Edge()
    {
        src = '0';
        dest = '0';
        len = 32767;
    }
    Edge(char a, char b, int c)
    {
        src = a;
        dest = b;
        len = c;
    }
};

class Graph
{
public:
    int n;
    Edge **edges;
    char *vertexes;
    int vertCount;
    Graph()
    {
        n = 0;
        edges = NULL;
        vertCount = 5;
        // vertCount = 4;
        vertexes = new char[vertCount];
        vertexes[0] = 'A';
        vertexes[1] = 'B';
        vertexes[2] = 'C';
        vertexes[3] = 'D';
        vertexes[4] = 'E';
    }
    Graph(int n)
    {
        this->n = n;
        edges = new Edge *[n];
        vertCount = 5;
        // vertCount = 4;
        vertexes = new char[vertCount];
        vertexes[0] = 'A';
        vertexes[1] = 'B';
        vertexes[2] = 'C';
        vertexes[3] = 'D';
        vertexes[4] = 'E';
    }
    //Function to get length between two vertexes
    int getLength(char sr,char ds){
        if(sr==ds)
            return 0;
        for(int i=0 ; i < n ; i++)
            if(edges[i]->src == sr && edges[i]->dest == ds)
                return  edges[i]->len;
        return 32767;
    }
    //BellMan Ford Function Definition
    void BellMan(char start)
    {
        //Local Variables to be used
        int *lengths = new int[vertCount];
        for (int i = 0; i < n; i++)
            //Set all as Maximum Lengths
            lengths[i] = 32767;
        lengths[0]=0;
        //Print all lengths starting from A
        for (int i = 1; i < vertCount; i++){
            lengths[i] = getLength('A',(i+65));
            // cout << vertexes[i] << ": " << lengths[i] << endl;
        }
        // cout<<"Now Beginning BellMan Ford"<<endl;
        bool negCyc=false;
        for(int j=0 ; j<1.5*vertCount ; j++){
            bool upFlag=false;
            //Run loop to figure out final lengths of all Vertexes
            // cout<<"===================Outer Loop: "<<j<<"===================\n";
            for(int i=0 ; i<n ; i++){
                Edge temp = *(edges[i]);
                // cout<<"Src: "<<temp.src<<"\tDest: "<<temp.dest<<"\tLen: "<<temp.len<<endl;
                // cout<<"Length known of "<<temp.src<<": "<<lengths[temp.src-65]<<endl;
                /////////////////////////////////////////////////////////////
                // cout<<"lengths["<<temp.src<<"] + "<<temp.len<<" < lengths["<<temp.dest<<"]"<<endl;
                // cout<<lengths[temp.src-65]<<" + "<<temp.len<<" < "<<lengths[temp.dest-65]<<endl;
                //If Length known to src is 32767, Continue
                if(lengths[temp.src-65] == 32767)
                    continue;
                //Else if known-Src + src-dest > known - dest 
                if( lengths[temp.src-65] + temp.len < lengths[temp.dest-65] ){
                    // cout<<"len to "<<temp.src<<" + edge: "<<temp.len<<" < len to "<<temp.dest<<endl;
                    //update known-dest = known-Src + src-dest 
                    lengths[temp.dest-65] = lengths[temp.src-65] + temp.len;
                    // cout<<temp.dest<<": updated to "<<lengths[temp.dest-65]<<endl;
                    //update upFlag
                    upFlag=true;
                    // cout<<"upFlag Updated"<<endl;
                }
            }
            if(upFlag==false){
                // cout<<"No Change Detected, Quitting Loop"<<endl;
                break;
            }
            if(j==1.5*vertCount-1){
                cout<<"Negative Cycle Detected"<<endl;
                negCyc=true;
                break;
            }
        }
        //Print out Result
        if(negCyc==false){
            cout<<"Results: "<<endl;
            for (int i = 1; i < vertCount; i++)
                cout << vertexes[i] << ": " << lengths[i] << endl;
        }
    }
};

int main(int argc, const char **argv)
{
    //Initialise the Graph variables
    int N = 8; //No. of Edges
    // int N = 5; //No. of Edges
    Graph *gr = new Graph(N);
    {
        gr->edges[0] = new Edge('A', 'B', -1);
        gr->edges[1] = new Edge('B', 'E', 2);
        gr->edges[2] = new Edge('B', 'D', 2);
        gr->edges[3] = new Edge('E', 'D', -3);
        gr->edges[4] = new Edge('B', 'C', 3);
        gr->edges[5] = new Edge('D', 'C', 5);
        gr->edges[6] = new Edge('A', 'C', 4);
        gr->edges[7] = new Edge('D', 'B', 1);

        // gr->edges[0] = new Edge('A', 'B', 2);
        // gr->edges[1] = new Edge('C', 'B', -10);
        // gr->edges[2] = new Edge('A', 'D', 5);
        // gr->edges[3] = new Edge('D', 'C', 3);
        // gr->edges[4] = new Edge('B', 'D', 5);
        //Print the Graph to Verify it
        // for (int i = 0; i < N; i++)
        // cout << (gr->edges[i]->src) << "\t" << (gr->edges[i]->dest) << "\t" << (gr->edges[i]->len) << endl;
    }
    //Call BellMan Ford and Pass the Graph to it
    gr->BellMan('A');
    //Print Results
    return 0;
}