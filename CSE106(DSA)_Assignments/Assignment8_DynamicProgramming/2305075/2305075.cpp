#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

const int N= 205;
int dp[N][N];

void GlobalAlignment(string seq1,string seq2,int match,int mismatch,int gap){
    int len1 = seq1.length();
    int len2 = seq2.length();

    for(int i=0;i<=len1;i++){
        for(int j=0;j<=len2;j++){
            if(i==0 && j==0){
                dp[i][j] = 0;
            }
            else if(i==0){
                dp[i][j] = j*gap;
            }
            else if(j==0){
                dp[i][j] = i*gap;
            }
            else{
                int up = dp[i-1][j]+gap;
                int left = dp[i][j-1]+gap;
                int diagonal = dp[i-1][j-1];
                if(seq1[i-1]==seq2[j-1]){
                    diagonal += match;
                }
                else{
                    diagonal += mismatch;
                }
                int maximum = max(up,left);
                maximum = max(maximum,diagonal);
                dp[i][j] = maximum;
            }
        }
    }

    string aligned_subseq1 = "";
    string aligned_subseq2 = "";
    int i = len1;
    int j = len2;

    while(i>0 || j>0){
        if(i>0 && j>0){
            int corner = dp[i-1][j-1];
            if(seq1[i-1]==seq2[j-1]){
                corner += match;
            }
            else{
                corner += mismatch;
            }

            if(dp[i][j]==corner){
                aligned_subseq1 += seq1[i-1];
                aligned_subseq2 += seq2[j-1];
                i--;
                j--;
                continue;
            }
            
        }
        if(i>0 && dp[i][j]==(dp[i-1][j]+gap)){
            aligned_subseq1 += seq1[i-1];
            aligned_subseq2 += '-';
            i--;
        }
        else if(j>0 && dp[i][j]==(dp[i][j-1]+gap)){
            aligned_subseq1 += '-';
            aligned_subseq2 += seq2[j-1];
            j--;
        }

    }

    string reversed_subseq1 = "";
    string reversed_subseq2 = "";
    for(int i=aligned_subseq1.length()-1;i>=0;i--){
        reversed_subseq1 += aligned_subseq1[i];
    }
    for(int i=aligned_subseq2.length()-1;i>=0;i--){
        reversed_subseq2 += aligned_subseq2[i];
    }

    cout << endl;
    cout << "Global Alignment: " << endl;
    cout << reversed_subseq1 << endl;
    cout << reversed_subseq2 << endl;
    cout << endl;
    cout << "Maximum Score: " << dp[len1][len2] << endl;
    cout << endl;
}


void LocalAlignment(string seq1,string seq2,int match,int mismatch,int gap){
    int len1 = seq1.length();
    int len2 = seq2.length();

    int max_score = 0;
    int Last_i = 0, Last_j = 0;

    for(int i=0;i<=len1;i++){
        for(int j=0;j<=len2;j++){
            if(i==0 || j==0){
                dp[i][j] = 0;
            }
            else{
                int up = dp[i-1][j]+gap;
                int left = dp[i][j-1]+gap;
                int diagonal = dp[i-1][j-1];
                if(seq1[i-1]==seq2[j-1]){
                    diagonal += match;
                }
                else{
                    diagonal += mismatch;
                }
                
                int maximum = max(up,left);
                maximum = max(maximum,diagonal);
                if(maximum<0){
                    dp[i][j] = 0;
                }
                else{
                    dp[i][j] = maximum;
                }

                if(dp[i][j]>max_score){
                    max_score = dp[i][j];
                    Last_i = i;
                    Last_j = j;
                }
            }
        }
    }


    string aligned_subseq1 = "";
    string aligned_subseq2 = "";
    int i = Last_i;
    int j = Last_j;

    while(i>0 && j>0 && dp[i][j]>0){
        int corner = dp[i-1][j-1];
        if(seq1[i-1]==seq2[j-1]){
            corner += match;
        }
        else{
            corner += mismatch;
        }
        if(dp[i][j]==corner){
            aligned_subseq1 += seq1[i-1];
            aligned_subseq2 += seq2[j-1];
            i--;
            j--;
            continue;
        }
        if(dp[i][j] == (dp[i-1][j]+gap)){
            aligned_subseq1 += seq1[i-1];
            aligned_subseq2 += '-';
            i--;
        }
        else if(dp[i][j] == (dp[i][j-1]+gap)){
            aligned_subseq1 += '-';
            aligned_subseq2 += seq2[j-1];
            j--;
        }
    }

    string reversed_subseq1 = "";
    string reversed_subseq2 = "";
    for(int i=aligned_subseq1.length()-1;i>=0;i--){
        reversed_subseq1 += aligned_subseq1[i];
    }
    for(int i=aligned_subseq2.length()-1;i>=0;i--){
        reversed_subseq2 += aligned_subseq2[i];
    }

    cout << endl;
    cout << "Local Alignment: " << endl;
    cout << reversed_subseq1 << endl;
    cout << reversed_subseq2 << endl;
    cout << endl;
    cout << "Maximum Score: " << max_score << endl;
    cout << endl;
}

int main()
{
    string seq1,seq2;
    int match,mismatch,gap;
    
    cout << "Enter first sequence: " ;
    //cin >> seq1;
    getline(cin,seq1);
    cout << "Enter second sequence: ";
    //cin >> seq2;
    getline(cin,seq2);
    cout << "Enter match score: ";
    cin >> match;
    cout << "Enter mismatch penalty: ";
    cin >> mismatch;
    cout << "Enter gap penalty: ";
    cin >> gap;
    
    GlobalAlignment(seq1,seq2,match,mismatch,gap);
    LocalAlignment(seq1,seq2,match,mismatch,gap);
    return 0;
}


