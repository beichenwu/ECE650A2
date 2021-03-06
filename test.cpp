//
// Created by wu on 10/18/18.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <cstdlib>


using namespace std;

vector<vector<int> > Create_Node_list(int NumberofVertices, vector<vector<int> >& Edge_List){  //Define an array to store all node information
    vector<vector<int> > Vertex_Vector;
    for(int i = 0; i < NumberofVertices; i++){  //For Loop to create an array has size equal to number of Vertices
        vector<int> Vertex;                    //Set vector for each vertex
        Vertex.push_back(i);                   //Set the name for each Vertex
        Vertex.push_back(-1);                   //Set the parts for 0(For None)
        Vertex.push_back(0);                   //Set the Node Status(0 for searched and 1 for searched)
        Vertex_Vector.push_back(Vertex);       //Create the Vector
    }
    Edge_List.clear();                         //Reset Edge List
    return  Vertex_Vector;
}

int Read_Number_Of_Vertices(string User_Input){                //Define an function to analyze the user input and return number of vertices
    int Number_Of_vertices;                                    //Create a variable to store the number of vertices
    int String_Index;                                          //a variable to find where the space from the input
    int String_Length;                                         //a variable to store the length of string
    String_Index = User_Input.find(" ");                       //Locate the position of " "
    String_Length = User_Input.length();                       //The length of the string
    istringstream(User_Input.substr(String_Index+1, String_Length-String_Index)) >> Number_Of_vertices;     //Read the string and get the number of vertex
    return  Number_Of_vertices;
}


vector<string> String_Split(string String_Input, string Deliminator){           //A Function split a string and return a vector
    int String_Index = 0;                                                       //Initialized the String Index
    vector<string> Splited_String;                                              //Initialized the Vector
    string Sub_String;                                                          //Initialized the substring
    string String_For_Split = String_Input;                                     //Record the string for split
    while(String_Index != -1){                                                  //Stop the loop if deliminator is not found
        String_Index = String_For_Split.find(Deliminator);
        Sub_String = String_For_Split.substr(0,String_Index);                   //Find the substring
        Splited_String.push_back(Sub_String);                                   //Added the substring to vector
        String_For_Split.erase(0, String_Index+1);                              //Re-size the string
    }
    return Splited_String;
}

vector<vector<int> > Read_Edge_list(string User_Input, vector<vector<int> > VerticesVector){                  //Define an function to analyze the user input and return array of edge
    int String_Index1;
    int String_Index2;                                                                                      //a variable to find where the space from the input
    int Edge_Number;                                                                                        //a variable to store the number of edge
    int Node_Length = VerticesVector.size();
    string Edge_String = User_Input;                                                                        //Local String to store the user input
    vector<string> Tmp_Edge_List = String_Split(Edge_String, "<");                                          //Store the string in a temporary vector
    Edge_Number = Tmp_Edge_List.size();                                                                     //Determine the length of the edge list
    vector<vector<int> > Edge_List;                                                                         //Initialized Pointer for 2D Edge_list
    for(int i=0; i < Edge_Number; i++){
        if(i >=1) {                                                                                        //Loop Start from 1(Since index 0 is "E {"
            vector<int> Edge_Pair;
            String_Index1 = Tmp_Edge_List[i].find(",");                                                    //Substring to find the vertex number
            String_Index2 = Tmp_Edge_List[i].find(">");
            int tmp_int;
            istringstream(Tmp_Edge_List[i].substr(0, String_Index1)) >> tmp_int;
            Edge_Pair.push_back(tmp_int);
            istringstream(Tmp_Edge_List[i].substr(String_Index1+1, (String_Index2-String_Index1-1))) >> tmp_int;
            Edge_Pair.push_back(tmp_int);
            Edge_List.push_back(Edge_Pair);                                                                //A Function is needed to validate the edge list
        }
    }
    for(int i = 0; i < Edge_List.size(); i++){                                                             //Error Check
        if(Edge_List[i][0]> Node_Length || Edge_List[i][1]> Node_Length ){
            cerr << "Edge List contains nodes beyond the node list" << endl;
            break;
        }
    }
    return Edge_List;
}

vector<int> Find_Start_End(string User_Input){                                                             //Function to find Start End
    vector<int> Start_End_Vector;
    vector<string> Tmp_Edge_List = String_Split(User_Input, " ");                                          //Split String by ","
    int tmp_int;
    istringstream(Tmp_Edge_List[1]) >> tmp_int;
    Start_End_Vector.push_back(tmp_int);                                                                  //Push the first item
    istringstream(Tmp_Edge_List[2]) >> tmp_int;
    Start_End_Vector.push_back(tmp_int);                                                                  //Push the second item
    return  Start_End_Vector;
}

vector<int> Find_Connected_Vertex(int Input_Vertex, vector<vector<int> >& VerticesVector, vector<vector<int> > Edge_List){      //A Function to find the connected Vertex
    int Orgin = Input_Vertex;                                                                                                   //Assign the Input
    int Edge_list_Length = Edge_List.size();                                                                                    //Assign the length of Edge_list
    vector<int> Connected_Vertex;                                                                                               //Define the vector list for Connected Vertex
    VerticesVector = VerticesVector;                                                                                            //Assign the VerticesVector
    for(int i = 0; i < Edge_list_Length; i++) {                                                                                 //Bellman-Ford Search
        if (Orgin == Edge_List[i][0]) {                                                                                         //Check if input vertex match
            int Tmp_Connected_Vertex = Edge_List[i][1];                                                                         //Assign Connected the vertex
            if (VerticesVector[Tmp_Connected_Vertex][2] != 1) {                                                                 //Check if the vertex has been searched or not
                Connected_Vertex.push_back(Tmp_Connected_Vertex);                                                               //Push to the Vector
                VerticesVector[Tmp_Connected_Vertex][1] = Input_Vertex;                                                         //Set Parent
                VerticesVector[Tmp_Connected_Vertex][2] = 1;                                                                    //Searched
            }
        }
        if (Orgin == Edge_List[i][1]) {                                                                                         //Check if input vertex match
            int Tmp_Connected_Vertex = Edge_List[i][0];                                                                         //Same
            if (VerticesVector[Tmp_Connected_Vertex][2] != 1) {
                Connected_Vertex.push_back(Tmp_Connected_Vertex);
                VerticesVector[Tmp_Connected_Vertex][1] = Input_Vertex;
                VerticesVector[Tmp_Connected_Vertex][2] = 1;
            }
        }
    }
    VerticesVector[Orgin][2] = 1;
    return Connected_Vertex;
}

vector<int> Shortest_Path(int Start, int End, vector<vector<int> >& VerticesVector, vector<vector<int> > Edge_List ){
    int Start_Vertex =  Start;                                                           //Start Vertex
    int End_Vertex = End;                                                                //End Vertex
    int Current_Vertex;                                                                  //empty variable to store being search vertex
    int Count = 0;                                                                       //Count
    VerticesVector = VerticesVector;                                                     //Empty Vector
    vector<int> Tmp_Vertex_Vector;
    queue<int> Vertex_Queue;
    Vertex_Queue.push(Start_Vertex);
    vector<int> Short_Path;
    for(int i = 0; i< VerticesVector.size();i++){                                        //Initialized the VerticesVector
        VerticesVector[i][1] = -1;
        VerticesVector[i][2] = 0;
    }

    do{
        Current_Vertex = Vertex_Queue.front();                                                            //store the vector into the queue
        Tmp_Vertex_Vector = Find_Connected_Vertex(Current_Vertex, VerticesVector, Edge_List);             //Find the connected vector
        Vertex_Queue.pop();                                                                               //Pop the vertex been searched
        for (int i = 0; i < Tmp_Vertex_Vector.size(); i++) {
            Vertex_Queue.push(Tmp_Vertex_Vector[i]);                                                      //Push the searched vertices
        }
        Count++;
    }while(Current_Vertex != End_Vertex && Count < VerticesVector.size() && Vertex_Queue.size() != 0);           //stop if the end vertex been searched or Queue been cleaned

    int Parent_Name = End;
    while(Parent_Name != -1){                                                                      //Check if the End vertex has parent
        Short_Path.push_back(Parent_Name);                                                         //Loop and push parents
        Parent_Name = VerticesVector[Parent_Name][1];
    }
    return Short_Path;
}

string Return_Short_Path(vector<int> Short_Path){
    string Shortest_Path;
    int Count = 0;
    while(Short_Path.size()!=0){                                                                 //For Loop and add the string
        if (Count != 0){                                                                         //Case if not the first vertex
            string tmp_string;
            tmp_string = static_cast<ostringstream*>( &(ostringstream() << Short_Path.back()) )->str();
            Shortest_Path = Shortest_Path + "-" + tmp_string;
            Short_Path.pop_back();
        }else{
            string tmp_string;
            tmp_string = static_cast<ostringstream*>( &(ostringstream() << Short_Path.back()) )->str();
            Shortest_Path = Shortest_Path + tmp_string;                        //Case if for the first vertex
            Short_Path.pop_back();
        }
        Count++;
    }
    return Shortest_Path;
}

bool Check_Node_Within_Range(int node, int size){                //Check if the node is within the input node range
    if(node >= size) {
        return false;
    }
    else{
        return true;
    }
}

TEST_CASE("Create_Node_list"){
    vector<vector<int> > Edge_List;
    vector<vector<int> > fun_output = Create_Node_list(5, Edge_List);
            CHECK(fun_output.size()==5);
    for(int i = 0; i< 5; i++){
        CHECK(fun_output[i][0]==i);
        CHECK(fun_output[i][1]==-1);
        CHECK(fun_output[i][2]==0);
    }
}

TEST_CASE("Read_Number_Of_Vertices") {
    CHECK(Read_Number_Of_Vertices("V 15") == 15);
    CHECK(Read_Number_Of_Vertices("V 12") == 12);
    CHECK(Read_Number_Of_Vertices("V 8") == 8); // will fail
}

TEST_CASE("String_Split") {
    vector<string> fun_output = String_Split("<0,2>,<2,1>,<2,3>,<3,4>,<4,1>", ",");
    CHECK(fun_output.size()==10);
    CHECK(fun_output[0] == "<0");
    CHECK(fun_output[1] == "2>");
    CHECK(fun_output[2] == "<2");
    CHECK(fun_output[3] == "1>");
    CHECK(fun_output[4] == "<2");
    CHECK(fun_output[5] == "3>");
    CHECK(fun_output[6] == "<3");
    CHECK(fun_output[7] == "4>");
    CHECK(fun_output[8] == "<4");
    CHECK(fun_output[9] == "1>");
}

TEST_CASE("Read_Edge_list"){
    vector<vector<int> > Edge_List;
    vector<vector<int> > fun_input = Create_Node_list(10, Edge_List);
    vector<vector<int> > fun_output = Read_Edge_list("E {<0,2>,<2,1>,<2,3>,<3,4>,<4,1>}", fun_input);
    CHECK(fun_output.size()== 5);
    CHECK(fun_output[0][0] == 0);
    CHECK(fun_output[0][1] == 2);
    CHECK(fun_output[1][0] == 2);
    CHECK(fun_output[1][1] == 1);
    CHECK(fun_output[2][0] == 2);
    CHECK(fun_output[2][1] == 3);
    CHECK(fun_output[3][0] == 3);
    CHECK(fun_output[3][1] == 4);
    CHECK(fun_output[4][0] == 4);
    CHECK(fun_output[4][1] == 1);
}

TEST_CASE("Find_Start_End"){
    vector<int> fun_output1 = Find_Start_End("s 10 2");
    CHECK(fun_output1.size()== 2);
    CHECK(fun_output1[0] == 10);
    CHECK(fun_output1[1] == 2);
    vector<int> fun_output2 = Find_Start_End("s 2 8");
    CHECK(fun_output2.size()== 2);
    CHECK(fun_output2[0] == 2);
    CHECK(fun_output2[1] == 8);
}

TEST_CASE("Return Short Path"){
    vector<vector<int> > edge_list;
    vector<vector<int> > Vertice_list = Create_Node_list(5, edge_list);
    edge_list = Read_Edge_list("E {<0,2>,<2,1>,<2,3>,<3,4>,<4,1>}", Vertice_list);
    vector<int> Short_path = Shortest_Path(2, 4, Vertice_list, edge_list);
    string fun_out = Return_Short_Path(Short_path);
    CHECK(fun_out == "2-1-4");
    Short_path = Shortest_Path(0, 4, Vertice_list, edge_list);
    fun_out = Return_Short_Path(Short_path);
    CHECK(fun_out == "0-2-1-4");
    Vertice_list = Create_Node_list(15, edge_list);
    edge_list = Read_Edge_list("E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>,<1,7>,<5,1>,<1,2>,<3,5>,<9,6>,<1,6>,<4,2>,<7,4>,<0,1>,<0,6>}", Vertice_list);
    Short_path = Shortest_Path(2, 7, Vertice_list, edge_list);
    fun_out = Return_Short_Path(Short_path);
    CHECK(fun_out == "2-1-7");
    Short_path = Shortest_Path(1, 9, Vertice_list, edge_list);
    fun_out = Return_Short_Path(Short_path);
    CHECK(fun_out == "1-6-9");
}

TEST_CASE("Check_Node_Within_Range"){
    CHECK(Check_Node_Within_Range(2,10)==true);
    CHECK(Check_Node_Within_Range(10,10)==false);
}