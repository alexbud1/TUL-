#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Human{
    public:
        string FirstName;
        string LastName;
        string sex;
        int age;
    Human(string a, string b, string c, int d){
        FirstName = a;
        LastName = b;
        sex = c;
        age = d;
    }
};
string toLowerCase(string s){
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}
bool validate_sex(string sex){
    if (toLowerCase(sex)== "male" || toLowerCase(sex)== "female"){
        return true;
    }else {
        return false;
    }
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main() {
    int k = 0;
    while (true){
        if (k == 0){
            cout << "Please enter file name" << endl;
        }
        string file;
        getline(cin, file);

        if(file == "exit"){
            break;
        }
        ifstream input_file;
        string input_file_line;

        input_file.open(file);
        vector<Human> people;

        if(input_file.is_open()){
            int counter = 0;
            while(getline(input_file, input_file_line)){
                string word = "";
                vector<string> words;
                int k1 = 0;
                for(int i = 0; i<(int)input_file_line.size(); i++){
                    if(input_file_line[i] != ' '){
                        if(input_file_line[i] != input_file_line.back()){
                            word += input_file_line[i];
                        }else{
                            if (words.size()!=3){
                                cout << "Incorrect values in the line " << counter + 1<< endl;
                                goto values_error;
                            }else{
                                word += input_file_line[i];
                                if(is_number(word)){
                                    Human person(words[0], words[1], words[2], stoi(word));
                                    people.push_back(person);
                                }else{
                                    cout << "Incorrect age in the line " << counter + 1<< endl;
                                    goto age_error;
                                }
                            }
                        }
                        }else{
                            if(input_file_line[i+1] == ' '){
                                continue;
                            }else{
                                if (k1 == 2){
                                    if(!validate_sex(word)){
                                        cout << "Incorrect sex in the line " << counter + 1  << endl;
                                        goto sex_error;
                                    }else{
                                        words.push_back(word);
                                        word = "";
                                    }
                                }else{
                                    words.push_back(word);
                                    word = "";
                                }
                                k1+=1;
                            }
                        }
                    }
                    values_error:
                        k+=1;

                    age_error:
                        k+=1;

                    sex_error:
                        k+=1;
                    k+=1;
                    counter++;
                }
                input_file.close();

            while (true){
            another_action:
                cout << endl;
                cout << "The vector now looks this way :\n" << endl;
                for(int i=0; i < people.size(); i++){
                    cout << people[i].FirstName << " " << people[i].LastName << " " << people[i].sex << " " << people[i].age << endl;
                }
                cout << "\nIf you want to create new object - print ADD"<< endl;
                cout << "If you want to delete certain object - print DELETE"<< endl;
                cout << "If you want to change certain object - print EDIT"<< endl;
                cout << "If you don't want to do any changes - print PASS"<< endl;
                string action;
                getline(cin, action);
                if(action == "ADD"){
                    cout << "\nIn order to ADD new object you should enter such fields as First Name, Last Name, Sex and Age. Let's start from First Name: "<< endl;
                    string FirstName = "";
                    getline(cin, FirstName);
                    if (FirstName!=""){
                        cout << "Now enter Last Name : " << endl;
                    string LastName;
                    getline(cin, LastName);
                    cout << "Now enter Sex ( Male or Female) : " << endl;
                    string Sex;
                    while(true){
                        getline(cin, Sex);
                        if (validate_sex(Sex)){
                            break;
                        }else{
                            cout << "Please enter valid sex ( Male or Female) : " << endl;
                        }
                    }
                    cout << "Now enter age (it should be an integer number) : " << endl;
                     edit_age_error:
                    string age;
                    while(true){
                        getline(cin, age);
                        if(age!=""){
                            cout << "Age = " << age << endl;
                            if(is_number(age)){
                                break;
                            }else{
                                cout << "Please enter valid name" << endl;
                            }
                        }
                    }
                    cout << "Your object is : " << FirstName << " " << LastName << " " << Sex << " " << age << endl;
                    Human person(FirstName, LastName, Sex, stoi(age));
                    people.push_back(person);
                    cout << "You added new object."<< endl;
                    }

                }
                else if(action == "DELETE"){
                    cout << "\nIn order to delete object you should specify index of object to delete. Here are objects and its id's: "<< endl;
                    for(int i=0; i < people.size(); i++){
                        cout << "ID = "<< i << " "<< people[i].FirstName << " " << people[i].LastName << " " << people[i].sex << " " << people[i].age << endl;
                    }
                    cout << "Enter the id of object you want to delete. It should be an integer number" << endl;
                    while (true){
                        string id;
                        getline(cin, id);
                        if(is_number(id)){
                            if(stoi(id) < people.size()){
                                cout << "Here is your object : " << "ID = "<< stoi(id) << " "<< people[stoi(id)].FirstName << " " << people[stoi(id)].LastName << " " << people[stoi(id)].sex << " " <<
                                people[stoi(id)].age << endl;
                                cout << "If you want to delete this object press YES, if not - print anything you want" << endl;
                                string verify;
                                cin >> verify;
                                if(verify == "YES"){
                                    cout << "DELETED" << endl;
                                    people.erase(people.begin() + stoi(id));
                                    cout << "Now vector looks this way : " << endl;
                                    for(int i=0; i < people.size(); i++){
                                        cout << "ID = "<< i << " "<< people[i].FirstName << " " << people[i].LastName << " " << people[i].sex << " " << people[i].age << endl;
                                    }
                                    break;
                                }else{
                                    cout << "Action canceled" << endl;
                                    break;
                                }
                            }else{
                                cout << "Please enter valid value. Maximum is " << people.size()-1 << endl;
                            }
                        }else{
                            cout << "Please enter an integer value" << endl;
                        }
                    }
                }
                else if(action == "EDIT"){
                    cout << "\nIn order to edit certain object - you should enter an id of the object you want to edit ( it should be an integer value ) : "<< endl;
                    for(int i=0; i < people.size(); i++){
                        cout << "ID = "<< i << " "<< people[i].FirstName << " " << people[i].LastName << " " << people[i].sex << " " << people[i].age << endl;
                    }
                    while (true){
                        string id;
                        getline(cin, id);
                        if(is_number(id)){
                            if(stoi(id) < people.size()){
                                cout << "Here is your object : " << "ID = "<< stoi(id) << " "<< people[stoi(id)].FirstName << " " << people[stoi(id)].LastName << " " << people[stoi(id)].sex << " " <<
                                people[stoi(id)].age << endl;
                                while(true){
                                    cout << "Now choose the field you want to edit :\nL - for Last Name\nF - for First Name\nS - for Sex\nA - for Age\nEnter PASS to finish editing" << endl;
                                    string value;
                                    getline(cin, value);
                                    if(value == "L"){
                                        cout << "Enter Last Name you want to put instead of previous one" << endl;
                                        string LastName;
                                        getline(cin, LastName);
                                        people[stoi(id)].LastName = LastName;
                                    }
                                    else if(value == "F"){
                                        cout << "Enter First Name you want to put instead of previous one" << endl;
                                        string FirstName;
                                        getline(cin, FirstName);
                                        people[stoi(id)].FirstName = FirstName;
                                    }
                                    else if(value == "S"){
                                        cout << "Enter Sex you want to put instead of previous one (Male or Female)" << endl;
                                        string Sex;
                                        while(true){
                                            getline(cin, Sex);
                                            if (validate_sex(Sex)){
                                                people[stoi(id)].sex = Sex;
                                                break;
                                            }else{
                                                cout << "Please enter valid sex ( Male or Female) : " << endl;
                                            }
                                        }
                                    }
                                    else if(value == "A"){
                                        cout << "Enter Age you want to put instead of previous one" << endl;
                                        string Age = "";

                                        while(true){
                                            getline(cin, Age);
                                            if(Age!=""){
                                                cout << "Age = " << Age << endl;

                                                if(is_number(Age)){
                                                    people[stoi(id)].age = stoi(Age);
                                                    break;
                                                }else{
                                                    cout << "Please enter valid name" << endl;
                                                }
                                            }
                                        }

                                    }
                                    else if(value == "PASS"){
                                        cout << "Now object looks this way : " << endl;
                                        cout << "ID = "<< stoi(id) << " "<< people[stoi(id)].FirstName << " " << people[stoi(id)].LastName << " " << people[stoi(id)].sex << " " << people[stoi(id)].age << endl;
                                        cout << "You have just edited an object.\n"<< endl;
                                        goto another_action;
                                    }
                                    else{
                                        cout << "Incorrect value selected, please try again" << endl;
                                    }
                                }
                            }else{
                                cout << "Please enter valid value. Maximum is " << people.size()-1 << endl;
                            }
                        }else{
                            cout << "Please enter an integer value" << endl;
                        }
//                        break;
                    }
//                    break;
                }
                else if(action == "PASS"){
                    while(true){
                        cout << "You skipped all the editing operations.  Now please enter the name of output file : "<< endl;
                        string output_file_name;
                        getline(cin, output_file_name);
                        ofstream myfile(output_file_name);

                        if(myfile.is_open()){
                            ofstream ofs;
                            ofs.open(output_file_name, std::ofstream::out | std::ofstream::trunc);
                            ofs.close();
                            for(int i=0; i < people.size(); i++){
                                myfile << people[i].FirstName << " " << people[i].LastName << " " << people[i].sex << " " << people[i].age << endl;
                            }
                            myfile.close();
                            cout << "Success" << endl;
                            break;

                        }else{
                            cout << "Unable to open the file!" << endl;
                            cout << "Try to enter valid file name or print exit to quit" << endl;
                        }
                    }
                break;
                }else{
                    cout << "Please select one of the actions: ADD, DELETE, EDIT, PASS"<< endl;
                    }
                }
            break;
        }else{
            cout << "Unable to open the file!" << endl;
            cout << "Try to enter valid file name or print exit to quit" << endl;
        }

    }


    pass:
        return 0;

    return 0;
}
