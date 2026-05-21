#include<iostream>
#include<set>
#include<vector>
#include<unordered_map>
#include<climits>

// #include<bits/stdc++.h>

using namespace std;

class wallet{
    public:
    string name;
    int netBalance;
    set<string> cryptos;
}; 

int getMinIndex(wallet listOfNetBalances[],int numWallets){
    int min=INT_MAX, minIndex=-1;
    for(int i=0;i<numWallets;i++){
        if(listOfNetBalances[i].netBalance == 0) continue;
        
        if(listOfNetBalances[i].netBalance < min){
            minIndex = i;
            min = listOfNetBalances[i].netBalance;
        }
    }
    return minIndex;
}

int getSimpleMaxIndex(wallet listOfNetBalances[],int numWallets){
    int max=INT_MIN, maxIndex=-1;
    for(int i=0;i<numWallets;i++){
        if(listOfNetBalances[i].netBalance == 0) continue;
        
        if(listOfNetBalances[i].netBalance > max){
            maxIndex = i;
            max = listOfNetBalances[i].netBalance;
        }
    }
    return maxIndex;
}

pair<int,string> getMaxIndex(wallet listOfNetBalances[],int numWallets,int minIndex,wallet input[],int maxNumCryptos){
    int max=INT_MIN;
    int maxIndex=-1;
    string matchingCrypto;
    
    for(int i=0;i<numWallets;i++){
        if(listOfNetBalances[i].netBalance == 0) continue;
        
        if(listOfNetBalances[i].netBalance < 0) continue;
        
        vector<string> v(maxNumCryptos);
        vector<string>::iterator ls=set_intersection(listOfNetBalances[minIndex].cryptos.begin(),listOfNetBalances[minIndex].cryptos.end(), listOfNetBalances[i].cryptos.begin(),listOfNetBalances[i].cryptos.end(), v.begin());
        
        if((ls-v.begin())!=0 && max<listOfNetBalances[i].netBalance ){
            max=listOfNetBalances[i].netBalance;
            maxIndex=i;
            matchingCrypto = *(v.begin());
        } 
    }
    
    return make_pair(maxIndex,matchingCrypto);
}

void printAns(vector<vector<pair<int,string>>> ansGraph, int numWallets,wallet input[]){
    
    cout<<"\n========================================\n";
    cout<<"OPTIMIZED SETTLEMENT TRANSACTIONS\n";
    cout<<"========================================\n\n";
    
    int transactionCount = 0;
    
    for(int i=0;i<numWallets;i++){
        for(int j=0;j<numWallets;j++){
            
            if(i==j) continue;
            
            if(ansGraph[i][j].first != 0 && ansGraph[j][i].first != 0){
                
                if(ansGraph[i][j].first == ansGraph[j][i].first){
                    ansGraph[i][j].first=0;
                    ansGraph[j][i].first=0;
                }
                else if(ansGraph[i][j].first > ansGraph[j][i].first){
                    ansGraph[i][j].first -= ansGraph[j][i].first; 
                    ansGraph[j][i].first =0;
                    
                    transactionCount++;
                    cout<<transactionCount<<". "<<input[i].name<<" transfers "<<ansGraph[i][j].first<<" units of "<<ansGraph[i][j].second<<" to "<<input[j].name<<endl;
                }
                else{
                    ansGraph[j][i].first -= ansGraph[i][j].first;
                    ansGraph[i][j].first = 0;
                    
                    transactionCount++;
                    cout<<transactionCount<<". "<<input[j].name<<" transfers "<<ansGraph[j][i].first<<" units of "<<ansGraph[j][i].second<<" to "<<input[i].name<<endl;
                    
                }
            }
            else if(ansGraph[i][j].first != 0){
                transactionCount++;
                cout<<transactionCount<<". "<<input[i].name<<" transfers "<<ansGraph[i][j].first<<" units of "<<ansGraph[i][j].second<<" to "<<input[j].name<<endl;
                
            }
            else if(ansGraph[j][i].first != 0){
                transactionCount++;
                cout<<transactionCount<<". "<<input[j].name<<" transfers "<<ansGraph[j][i].first<<" units of "<<ansGraph[j][i].second<<" to "<<input[i].name<<endl;
                
            }
            
            ansGraph[i][j].first = 0;
            ansGraph[j][i].first = 0;
        }
    }
    cout<<"\nTotal Optimized Transactions: "<<transactionCount<<endl;
    cout<<"========================================\n\n";
}

void minimizeCashFlow(int numWallets,wallet input[],unordered_map<string,int>& indexOf,int numTransactions,vector<vector<int>>& graph,int maxNumCryptos){
    
    wallet listOfNetBalances[numWallets];
    
    for(int w=0;w<numWallets;w++){
        listOfNetBalances[w].name = input[w].name;
        listOfNetBalances[w].cryptos = input[w].cryptos;
        
        int balance = 0;
        
        for(int i=0;i<numWallets;i++){
            balance += (graph[i][w]);
        }
        
        for(int j=0;j<numWallets;j++){
            balance += ((-1) * graph[w][j]);
        }
        
        listOfNetBalances[w].netBalance = balance;
    }
    
    vector<vector<pair<int,string>>> ansGraph(numWallets,vector<pair<int,string>>(numWallets,{0,""}));
    
    int numZeroBalances=0;
    
    for(int i=0;i<numWallets;i++){
        if(listOfNetBalances[i].netBalance == 0) numZeroBalances++;
    }
    
    while(numZeroBalances!=numWallets){
        
        int minIndex=getMinIndex(listOfNetBalances, numWallets);
        pair<int,string> maxAns = getMaxIndex(listOfNetBalances, numWallets, minIndex,input,maxNumCryptos);
        
        int maxIndex = maxAns.first;
        
        if(maxIndex == -1){
            
            (ansGraph[minIndex][0].first) += abs(listOfNetBalances[minIndex].netBalance);
            (ansGraph[minIndex][0].second) = *(input[minIndex].cryptos.begin());
            
            int simpleMaxIndex = getSimpleMaxIndex(listOfNetBalances, numWallets);
            (ansGraph[0][simpleMaxIndex].first) += abs(listOfNetBalances[minIndex].netBalance);
            (ansGraph[0][simpleMaxIndex].second) = *(input[simpleMaxIndex].cryptos.begin());
            
            listOfNetBalances[simpleMaxIndex].netBalance += listOfNetBalances[minIndex].netBalance;
            listOfNetBalances[minIndex].netBalance = 0;
            
            if(listOfNetBalances[minIndex].netBalance == 0) numZeroBalances++;
            
            if(listOfNetBalances[simpleMaxIndex].netBalance == 0) numZeroBalances++;
            
        }
        else{
            int transactionAmount = min(abs(listOfNetBalances[minIndex].netBalance), listOfNetBalances[maxIndex].netBalance);
            
            (ansGraph[minIndex][maxIndex].first) += (transactionAmount);
            (ansGraph[minIndex][maxIndex].second) = maxAns.second;
            
            listOfNetBalances[minIndex].netBalance += transactionAmount;
            listOfNetBalances[maxIndex].netBalance -= transactionAmount;
            
            if(listOfNetBalances[minIndex].netBalance == 0) numZeroBalances++;
            
            if(listOfNetBalances[maxIndex].netBalance == 0) numZeroBalances++;
        }
        
    }
    
    printAns(ansGraph,numWallets,input);
}

int main() 
{ 
    cout<<"\n\t\t\t\t*** CRYPTOCURRENCY MULTI-WALLET SETTLEMENT SYSTEM ***\n\n";
    cout<<"This system minimizes settlement transactions among multiple cryptocurrency wallets across the world.\n";
    cout<<"Different wallets support different cryptocurrencies. A Central Exchange Wallet acts as an intermediary\n";
    cout<<"between wallets that have no common cryptocurrency support.\n\n";
    cout<<"Enter the number of wallets participating in transactions:\n";
    int numWallets;
    cin>>numWallets;
    
    wallet input[numWallets];
    unordered_map<string,int> indexOf;
    
    cout<<"\nEnter wallet details as follows:\n";
    cout<<"Wallet name, number of cryptocurrencies supported, and the cryptocurrency types.\n";
    cout<<"Wallet names and cryptocurrency types should not contain spaces.\n\n";
    
    int maxNumCryptos;
    for(int i=0; i<numWallets;i++){
        if(i==0){
            cout<<"Central Exchange Wallet: ";
        }
        else{
            cout<<"Wallet "<<i<<": ";
        }
        cin>>input[i].name;
        indexOf[input[i].name] = i;
        int numCryptos;
        cin>>numCryptos;
        
        if(i==0) maxNumCryptos = numCryptos;
        
        string crypto;
        while(numCryptos--){
            cin>>crypto;
            input[i].cryptos.insert(crypto);
        }   
    }
    
    cout<<"\nEnter number of transactions:\n";
    int numTransactions;
    cin>>numTransactions;
    
    vector<vector<int>> graph(numWallets,vector<int>(numWallets,0));
    
    cout<<"\nEnter transaction details as follows:\n";
    cout<<"Sender Wallet, Receiver Wallet, Amount (in smallest unit)\n";
    cout<<"Transactions can be in any order.\n\n";
    for(int i=0;i<numTransactions;i++){
        cout<<"Transaction "<<(i+1)<<": ";
        string s1,s2;
        int amount;
        cin >> s1>>s2>>amount;
        
        graph[indexOf[s1]][indexOf[s2]] = amount;
    }
     
    cout<<"\n";
    minimizeCashFlow(numWallets,input,indexOf,numTransactions,graph,maxNumCryptos);
    return 0; 
}
