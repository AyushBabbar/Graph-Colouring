#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h> 
using namespace std;

#define ESC "\033["
#define RESET "\033[m"
#define PURPLE_TXT "41"

map<int, string> stateMap;
map<string, int> inverseStateMap;
map<int, int> fixedColour;
map<int, set<int>> possibleColour;
vector<vector<int>> graph;
int states;

void printCurrStat(int node)
{
    cout << "Setting colour " << fixedColour[node]-40 << " for " << stateMap[node] << endl;
    cout << "Fixed Colours ==>\n";
    for (auto i : fixedColour)
    {
        if (i.second)
        {

            cout << stateMap[i.first] << " - " << i.second - 40 << endl;
        }
    }

    cout<<"Domain of remaining states ==>\n";
    for(auto i: possibleColour) 
    {
        cout<<stateMap[i.first] <<" - ";
        for(auto j: i.second) 
        {
            cout<<j<<", ";
        }
        cout<<endl;
    }
}

void printRawGraph()
{
    for(int i=0; i<graph.size(); i++) {
        cout<<stateMap[i]<<" ===> ";
        for(int child: graph[i]) {
            cout<<stateMap[child]<<" ,";
        }
        cout<<endl;
    }
}
void ClearScreen()
{
    cout << "\033[2J\033[H";
}

void printTop()
{
    cout << "                               .:::." << endl;
    cout << "                           ^~!!~~^^!::" << endl;
    cout << "                         :J~.       ::!~.      .." << endl;
    cout << "                         .:~!^         !::^^!!!!~!!:" << endl;
    cout << "                            .!J^         :~^.     !?" << endl;
    cout << "                            ^:!.                 ~?." << endl;
    cout << "                              ::                 ^!?" << endl;
    cout << "                            ::                ::" << endl;
}

void printIndia(bool finished = false) {
    static int temp = 1;
    if (temp++ == 1)
    {
        ClearScreen();
        printTop();
    }
    cout << "                            ~: "<<ESC << ";" << to_string(fixedColour[0]) <<"m"<<"Jammu & Kashmir"<< RESET<<" ~J" << endl;
    cout << "                              :^!::         .J~~?." << endl;
    cout << "                               ^:!!.     "<<ESC << ";" << to_string(fixedColour[1]) <<"m"<<"HP"<< RESET<<"  ?J." << endl;
    cout << "                              ::              ..~!!^." << endl;
    cout << "                           .^:!  "<<ESC << ";" << to_string(fixedColour[2]) <<"m"<<"Punjab"<< RESET<<"           .^::                                          ::..~!~." << endl;
    cout << "                          :J^.               "<<ESC << ";" << to_string(fixedColour[3]) <<"m"<<"UK"<< RESET<<"    :!^                                       ..?       Y.::" << endl;
    cout << "                        :~?^                      !?                       .:.:.::.          .::~~        :::?~:~" << endl;
    cout << "                 ..   .:::         "<<ESC << ";" << to_string(fixedColour[4]) <<"m"<<"Haryana"<< RESET<<"        ~!!~^                   ||      ||    ~^:!?^  "<<ESC << ";" << to_string(fixedColour[23]) <<"m"<<"Arunachal"<< RESET<<"   J~" << endl;
    cout << "               ^:~J!~~:^                             :~:~^:.             .Y "<<ESC << ";" << to_string(fixedColour[21]) <<"m"<<"Sikkim"<< RESET<<" ::  ?J7^.             :!!!Y." << endl;
    cout << "             ^:~. .:..                                  ..   :!!~~~^^::.J~        ^^^^^:                J~" << endl;
    cout << "             ~?^.                          "<<ESC << ";" << to_string(fixedColour[6]) <<"m"<<"Uttar Pradesh"<< RESET<<"         "<<ESC << ";" << to_string(fixedColour[7]) <<"m"<<"Bihar"<< RESET<<"                  "<<ESC << ";" << to_string(fixedColour[24]) <<"m"<<"Assam"<< RESET<<"       :J." << endl;
    cout << "               ?:                                                            J!~!~~              "<<ESC << ";" << to_string(fixedColour[25]) <<"m"<<"Naga"<< RESET<<" :J." << endl;
    cout << "               ^:!    "<<ESC << ";" << to_string(fixedColour[5]) <<"m"<<"Rajasthan"<< RESET<<"                                             ^!:: Y~ "<<ESC << ";" << to_string(fixedColour[22]) <<"m"<<"Meghalaya"<< RESET<<"         J^" << endl;
    cout << "                 ::                                       "<<ESC << ";" << to_string(fixedColour[10]) <<"m"<<"Jharkhand"<< RESET<<"         :!:~ :~~~~^::Y~        .Y." << endl;
    cout << "          ^^:^::^:5.                                                         ?:^       .~:!     "<<ESC << ";" << to_string(fixedColour[26]) <<"m"<<"Mani"<< RESET<<" ~" << endl;
    cout << "        ?!?^^^~~^~:                                              "<<ESC << ";" << to_string(fixedColour[11]) <<"m"<<"West Bengal"<< RESET<<" .5:      Y^ "<<ESC << ";" << to_string(fixedColour[27]) <<"m"<<"Trip"<< RESET<<"        ^Y^:" << endl;
    cout << "        ~:^                     "<<ESC << ";" << to_string(fixedColour[9]) <<"m"<<"Madhya Pradesh"<< RESET<<"                                ::      ~:     :::     ::" << endl;
    cout << "         .^:!!   "<<ESC << ";" << to_string(fixedColour[8]) <<"m"<<"Gujarat"<< RESET<<"                                                        Y:      .^.::  : "<<ESC << ";" << to_string(fixedColour[28]) <<"m"<<"Mizo"<< RESET<<" // " << endl;
    cout << "          !?!!        .^                                                      . ::             :    :7J." << endl;
    cout << "          .!::        JG:                        "<<ESC << ";" << to_string(fixedColour[14]) <<"m"<<"Chhattisgarh"<< RESET<<"                :~!!~!^           :::.::" << endl;
    cout << "            .:::   ..^JJ~                                                 J~:." << endl;
    cout << "              :!!!!!~^ ^J                                   "<<ESC << ";" << to_string(fixedColour[12]) <<"m"<<"Odisha"<< RESET<<"     :Y" << endl;
    cout << "                       :! "<<ESC << ";" << to_string(fixedColour[13]) <<"m"<<"Maharashtra"<< RESET<<"                              .:^!::" << endl;
    cout << "                       J^                                         ~?:" << endl;
    cout << "                       ^J                "<<ESC << ";" << to_string(fixedColour[16]) <<"m"<<"Telangana"<< RESET<<"             :~:!" << endl;
    cout << "                        J^ "<<ESC << ";" << to_string(fixedColour[15]) <<"m"<<"Goa"<< RESET<<"                                :::." << endl;
    cout << "                        .Y.                               ..^Y." << endl;
    cout << "                         :!               "<<ESC << ";" << to_string(fixedColour[18]) <<"m"<<"Andhra Pradesh"<< RESET<<" ." << endl;
    cout << "                          ?!                           ~." << endl;
    cout << "                           !?."<<ESC << ";" << to_string(fixedColour[17]) <<"m"<<"Karnataka"<< RESET<<"             .Y" << endl;
    cout << "                            ^J                      :Y" << endl;
    cout << "                             J^         "<<ESC << ";" << to_string(fixedColour[19]) <<"m"<<"Tamil Nadu"<< RESET<<"  J^" << endl;
    cout << "                             ^J                    ^J" << endl;
    cout << "                              :J^                 !?" << endl;
    cout << "                                :  "<<ESC << ";" << to_string(fixedColour[20]) <<"m"<<"Kerala"<< RESET<<"        :Y" << endl;
    cout << "                                  ^J           ~!!J" << endl;
    cout << "                                   J^         ~J.." << endl;
    cout << "                                   .Y.     :!!?!" << endl;
    cout << "                                    :?~:  :J:" << endl;
    cout << "                                      :~!!~." << endl;    
    if (!finished)
    {
        Sleep(800);
        ClearScreen();
    }
    else
    {
        printRawGraph();
        exit(0);
    }
}

void makeIndiaStateMap() 
{
    stateMap[0] = "Jammu & Kashmir";
    stateMap[1] = "HP";
    stateMap[2] = "Punjab";
    stateMap[3] = "UK";
    stateMap[4] = "Haryana";
    stateMap[5] = "Rajhasthan";
    stateMap[6] = "Uttar Pradesh";
    stateMap[7] = "Bihar";
    stateMap[8] = "Gujarat";
    stateMap[9] = "Madhya Pradesh";
    stateMap[10] = "Jharkhand";
    stateMap[11] = "West Bengal";
    stateMap[12] = "Odisha";
    stateMap[13] = "Maharashtra";
    stateMap[14] = "Chhatttisgarh";
    stateMap[15] = "Goa";
    stateMap[16] = "Telangana";
    stateMap[17] = "Karnatka";
    stateMap[18] = "Andhra Pradesh";
    stateMap[19] = "Tamil Nadu";
    stateMap[20] = "Kerala";
    stateMap[21] = "Sikkim";
    stateMap[22] = "Meghalaya";
    stateMap[23] = "Arunachal Pradesh";
    stateMap[24] = "Assam";
    stateMap[25] = "Nagaland";
    stateMap[26] = "Manipur";
    stateMap[27] = "Tripura";
    stateMap[28] = "Mizoram";
}

void makeIndiaGraph()
{
    graph[0].insert(graph[0].end(), {1, 2});
    graph[1].insert(graph[1].end(), {0, 2, 3, 4});
    graph[2].insert(graph[2].end(), {0, 1, 4, 5});
    graph[3].insert(graph[3].end(), {1, 6});
    graph[4].insert(graph[4].end(), {1, 2, 5, 6});
    graph[5].insert(graph[5].end(), {2, 4, 6, 8, 9});
    graph[6].insert(graph[6].end(), {3, 4, 5, 7, 9, 10});
    graph[7].insert(graph[7].end(), {6, 10, 11});
    graph[8].insert(graph[8].end(), {5, 9, 13});
    graph[9].insert(graph[9].end(), {5, 6, 8, 13, 14});
    graph[10].insert(graph[10].end(), {6, 7, 11, 12, 14});
    graph[11].insert(graph[11].end(), {7, 10, 12, 21, 24});
    graph[12].insert(graph[12].end(), {10, 11, 14, 18});
    graph[13].insert(graph[13].end(), {8, 9, 14, 15, 16, 17});
    graph[14].insert(graph[14].end(), {9, 10, 12, 13, 16});
    graph[15].insert(graph[15].end(), {13, 17});
    graph[16].insert(graph[16].end(), {13, 14, 17, 18});
    graph[17].insert(graph[17].end(), {13, 15, 16, 18, 19, 20});
    graph[18].insert(graph[18].end(), {12, 16, 17, 19});
    graph[19].insert(graph[19].end(), {17, 18, 20});
    graph[20].insert(graph[20].end(), {17, 19});
    graph[21].insert(graph[21].end(), {11});
    graph[22].insert(graph[22].end(), {24});
    graph[23].insert(graph[23].end(), {24, 25});
    graph[24].insert(graph[24].end(), {11, 22, 23, 25, 26, 27, 28});
    graph[25].insert(graph[25].end(), {23, 24, 26});
    graph[26].insert(graph[26].end(), {24, 25, 28});
    graph[27].insert(graph[27].end(), {24, 28});
    graph[28].insert(graph[28].end(), {24, 26, 27});
}

void printAustralia()
{
    cout << "                                                                                                    " << endl;
    cout << "                                                                                                    " << endl;
    cout << "                                                                     ^^                              " << endl;
    cout << "                                      ....:::.:::........           ^.^.                             " << endl;
    cout << "                                    .::...        ....:^:          :: .^                             " << endl;
    cout << "                      .:::::...    ::               .::           .^   ::..                          " << endl;
    cout << "                    .::.    ..::...^              .^:             ::     .::                         " << endl;
    cout << "                   ::          ..^:.               .::..         .^        ^                         " << endl;
    cout << "                  ::             ::                   ..:^:.     ^.        ::                        " << endl;
    cout << "               ..:.              .^                      ^:.::.::.          ^.                       " << endl;
    cout << "            ..::.                .^  "<<ESC << ";" << to_string(fixedColour[1]) <<"m"<<"Northern Territory"<< RESET<<"  ^.                 .^.                      " << endl;
    cout << "          .::.                    ~                      ^.                  .^.                     " << endl;
    cout << "       .::.                       ~                      ~.                    ::.                   " << endl;
    cout << "     ::.                          ~                      ^.      "<<ESC << ";" << to_string(fixedColour[3]) <<"m"<<"Queensland"<< RESET<<"     ::::.                " << endl;
    cout << "    ^:                            ^.                     ~.                        .::.              " << endl;
    cout << "   .^                             ^:                     ~                            .:.            " << endl;
    cout << "   .^      "<<ESC << ";" << to_string(fixedColour[0]) <<"m"<<"Western Australia"<< RESET<<"      ^^.::::::::::::::::::::^::::::^                       ::           " << endl;
    cout << "    ::                            :^                            ~                        ^.          " << endl;
    cout << "     .^.                          .^     "<<ESC << ";" << to_string(fixedColour[2]) <<"m"<<"South Australia"<< RESET<<"        ~......                  .^          " << endl;
    cout << "      .^.                          ~                            ~......:::::::::::::::::::~          " << endl;
    cout << "        ::                         ~                           .^                        .^          " << endl;
    cout << "         .^.                       ~   ..........              .^  "<<ESC << ";" << to_string(fixedColour[4]) <<"m"<<"New South Wales"<< RESET<<"      .!:          " << endl;
    cout << "           ^:                      ~:::..........::.           :^                      .!~           " << endl;
    cout << "            ::                 .:::..              .::    ..   :^                      ^^            " << endl;
    cout << "             ::         ....:::..                    .^. ::^   ^^::::                 .^             " << endl;
    cout << "            :^...:::..::                                    ^: ^.    ::.::::.:::^    .^             " << endl;
    cout << "               .                                             ::~   "<<ESC << ";" << to_string(fixedColour[5]) <<"m"<<"Victoria"<< RESET<<"    :^  .^               " << endl;
    cout << "                                                              .^:..             :^^^.               " << endl;
    cout << "                                                                 ..:::::::..:::...:                 " << endl;
    cout << "                                                                                                    " << endl;
    cout << "                                                                                                    " << endl;
    cout << "                                                                                                    " << endl;
    cout << "                                                                    .^~^^^^^^^^^^:                  " << endl;
    cout << "                                                                  .^~  "<<ESC << ";" << to_string(fixedColour[6]) <<"m"<<"Tasmania"<< RESET<<" ~.                  " << endl;
    cout << "                                                                    ...:::....:::|                  " << endl;
    cout << "                                                                                                    " << endl;
}

void makeAustraliaStateMap()
{
    stateMap[0] = "Western Australia";
    stateMap[1] = "Northern Territory";
    stateMap[2] = "South Australia";
    stateMap[3] = "Queensland";
    stateMap[4] = "New South Wales";
    stateMap[5] = "Victoria";
    stateMap[6] = "Tasmania";
    // cout<<"Exited statema making\n";
}

void makeAustraliaGraph()
{
    graph[0].insert(graph[0].end(), {1, 2});
    graph[1].insert(graph[1].end(), {0, 2, 3});
    graph[2].insert(graph[2].end(), {0, 1, 3, 4, 5});
    graph[3].insert(graph[3].end(), {1, 2, 4});
    graph[4].insert(graph[4].end(), {2, 3, 5});
    graph[5].insert(graph[5].end(), {2, 4});
    // cout<<"Exited graph making\n";

}

void populatePossibleColour(int colours = 3)
{
    for (int i = 0; i < states; i++)
    {
        for (int j = 1; j <= colours; j++)
        {
            possibleColour[i].insert(j);
        }
        fixedColour[i] = 0;
    }
    // cout<<"Exited possible making\n";

}

void populateReverseStateMap() 
{
    for(auto i: stateMap) 
    {
        inverseStateMap[i.second] = i.first;
    }
}

int calculateCurrNode()
{
    int mini = INT_MAX;
    vector<int> nodes;
    for (auto i : possibleColour)
    {
        if (i.second.size() == mini)
        {
            nodes.push_back(i.first);
        }
        if (i.second.size() < mini)
        {
            nodes.clear();
            nodes.push_back(i.first);
            mini = i.second.size();
        }
    }
    if (nodes.size() == 1)
    {
        return nodes[0];
    }
    int maxDegree = -1, maxDegreeNode = -1;
    for (auto node : nodes)
    {
        if ((int)(graph[node].size()) > maxDegree)
        {
            maxDegree = graph[node].size();
            maxDegreeNode = node;
        }
    }
    return maxDegreeNode;
}

int calculateColour(int node)
{
    int maxi = -1, finalColour = -1;
    for (auto colour : possibleColour[node])
    {
        int curr_min = INT_MAX;
        for (auto child : graph[node])
        {
            if (possibleColour.find(child) != possibleColour.end())
            {
                int choices = possibleColour[child].size();
                if (possibleColour[child].find(colour) != possibleColour[child].end())
                {
                    choices--;
                }
                curr_min = min(curr_min, choices);
            }
        }
        if (curr_min > maxi)
        {
            maxi = curr_min;
            finalColour = colour;
        }
    }
    if(finalColour == -1) 
    {
        cout<<"Graph Colouring not possible with current number of colours!!!";
        exit(0);
    }
    for (auto child : graph[node])
    {
        if (possibleColour.find(child) != possibleColour.end())
        {
            possibleColour[child].erase(finalColour);
        }
    }
    return finalColour;
}


bool areAllColoursColoured()
{
    int res = 0;
    for (auto i : fixedColour)
    {
        if (i.second != 0)
        {
            res++;
        }
    }
    if (res == states)
    {
        return true;
    }
    return false;
}

void colourGraph(bool isIndia)
{
    ClearScreen();
    while (areAllColoursColoured() == false)
    {
        int currNode = calculateCurrNode();     // MRV, Degree
        int colour = calculateColour(currNode); // LCV
        possibleColour.erase(currNode);
        fixedColour[currNode] = colour + 40;
        if (isIndia)
        {
            printIndia();
        }
        else
        {
            printCurrStat(currNode);
            printAustralia();
        }
    }
    if (isIndia)
    {
        printIndia(true);
    }
    else
    {
        printRawGraph();
    }
}


void printCustomCurrStat(int node)
{
    cout << "Setting colour " << fixedColour[node] << " for " << node << endl;
    cout << "Fixed Colours ==>\n";
    for (auto i : fixedColour)
    {
        if (i.second)
        {

            cout << i.first << " - " << i.second << endl;
        }
    }

    cout<<"Domain of remaining states ==>\n";
    for(auto i: possibleColour) 
    {
        cout<<i.first <<" - ";
        for(auto j: i.second) 
        {
            cout<<j<<", ";
        }
        cout<<endl;
    }
}


void customInput()
{
    cout<<"Enter number of different colours\n";
    int colors=0;
    cin>>colors;
    cout<<"Enter number of nodes\n";
    int state=0;
    cin>>state;
    graph.resize(state);
    states=state;
    int edges=0;
    cout<<"Enter number of edges\n";
    cin>>edges;
    cout<<" Now enter node 1 and node 2 of each edge when asked\n";
    while(edges--) 
    {
        int num1,num2;
        cout<<"Enter node1 of current edge\n";
        cin>>num1;
        cout<<"Enter node2 of current edge\n";
        cin>>num2;
        graph[num1].push_back(num2);
        graph[num2].push_back(num1);
    }
    populatePossibleColour(colors);
}

void colourCustomGraph()
{
    ClearScreen();
    while (areAllColoursColoured() == false)
    {
        int currNode = calculateCurrNode();     // MRV, Degree
        int colour = calculateColour(currNode); // LCV
        possibleColour.erase(currNode);
        fixedColour[currNode] = colour;
        printCustomCurrStat(currNode);
    }
}

int main()
{
    int country;
    cout << "For India enter 1, for Australia enter 2, for custom input press 3\n";
    cin >> country;
    if (country == 1)
    {
        states = 29;
        graph.resize(states);
        makeIndiaStateMap();
        makeIndiaGraph();
        populatePossibleColour();
        populateReverseStateMap();
        colourGraph(true);
    }
    if (country == 2)
    {
        states = 7;
        graph.resize(states);
        makeAustraliaStateMap();
        makeAustraliaGraph();
        populateReverseStateMap();
        populatePossibleColour();
        colourGraph(false);
    }

    if(country == 3) 
    {
        customInput();
        colourCustomGraph();
    }
    return 0;
}
