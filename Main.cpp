#include "Main.h"

int main(){
    bool isWorking = true;
    int choice;

    Setup();

    do{
        ShowMainMenu();
        choice = GetUserChoice();
        switch(choice){
            case 0:
                cout << "Program ended. Please, wait..." << endl;
                isWorking = false;
                break;

            case 1:
                ShowArchive();
                break;

            case 2:
                bool result = SearchBook();
                if(result){
                    cout << "OK" << endl;
                }else{
                    cout << "NO" << endl;
                }
        }
    }while(isWorking);

    return 0;
}