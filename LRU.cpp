#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){
    int noOfFrames;
    cout << "Enter number of frames : ";
    cin >> noOfFrames;
    
    int noOfPageReferences;
    cout << "Enter number of page references : ";
    cin >> noOfPageReferences;

    vector<int> pageReference(noOfPageReferences);
    cout << "Enter page references : ";
    for(int i = 0; i < noOfPageReferences; i++){
        cin >> pageReference[i];
    }

    vector<int> frames;

    int pageFaults = 0;

    cout << "Page Referred\t" << "Frames from 1 to " << noOfFrames << endl;   
    for(int i = 0; i < noOfPageReferences; i++){
        cout << pageReference[i] << "\t\t";
        if(frames.size() < noOfFrames){
            frames.push_back(pageReference[i]);
            pageFaults++;
        }else{
            int temp = pageReference[i];
            bool found = false;
            for(int j = 0; j < noOfFrames; j++){
                if(frames[j] == temp){
                    found = true;
                    break;
                }
            }
            if(!found){
                int min = INT_MAX;
                int index = -1;
                for(int k = 0; k < noOfFrames; k++){
                    int m = i - 1;
                    while(m >= 0){
                        if(frames[k] == pageReference[m]){
                            break;
                        }
                        m--;
                    }
                    if(m < min){
                        min = m;
                        index = k;
                    }
                }
                frames[index] = temp;
                pageFaults++;
            }
        }
        for(int j = 0; j < frames.size(); j++){
            cout << frames[j] << "\t\t";
        }
        cout << endl;
    }

    cout << "Number of page faults = " << pageFaults << endl;
    cout << "Number of hits = " << noOfPageReferences - pageFaults << endl;
    return 0;
}
