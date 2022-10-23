#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
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

vector<Human> people;

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

bool is_number(const string& s){
    return !s.empty() &&
            /*
                find_if checks every char from s[0] to s[n] if it is digit and if it comes to the last one whole right part would be True

                unsigned stands for some possible extensions of the default ASCII table
            */
            find_if(
                s.begin(),
                s.end(),
                [](unsigned char c) {
                    return !isdigit(c);
                }
            ) == s.end();
}

void printPerson(ostream& stream, int i, string by_id){
    if(by_id==""){
        stream << people[i].FirstName << " " << people[i].LastName << " " << people[i].sex << " " << people[i].age << endl;
    }else{
        stream << "ID = "<< i << " "<< people[i].FirstName << " " << people[i].LastName << " " << people[i].sex << " " << people[i].age << endl;
    }
}

void printPeople(ostream& stream, string by_id = ""){
    for(int i=0; i < people.size(); i++){
        printPerson(stream, i, by_id);
    }
}

string remove_white_spaces(string s){
    s.erase(
        remove_if(
            s.begin(),
            s.end(),
            ::isspace
        ),
        s.end()
    );
    return s;
}

int input_id(){
    string id;
    while(true) {
        cin >> id;

        cin.clear();
        cin.ignore(10000,'\n');

        if(is_number(id) && stoi(id) < people.size())
                break;

        if (is_number(id)) {
            cout << "Please enter valid integer value. Maximum is " << people.size()-1 << endl;
        } else {
            cout << "Please enter an integer value" << endl;
        }
    }
    return stoi(id);
}

string input_first_name(){
    string FirstName = "";
    do {
        cout << "Let's start from First Name:" << endl;
        getline(cin, FirstName);
    } while (FirstName == "");
    return FirstName;
}

string input_last_name(){
    string LastName;
    do {
        cout << "Now enter Last Name : " << endl;
        getline(cin, LastName);
    } while (LastName == "");
    return LastName;
}

string input_sex(){
    string Sex;
    while(true) {
        cin >> Sex;

        cin.clear();
        cin.ignore(10000,'\n');

        if (validate_sex(Sex))
            break;

        cout << "Please enter valid sex ( Male or Female) : " << endl;
    }
    return Sex;
}

int input_age(){
    string age;
    while(true) {
        cin >> age;

        cin.clear();
        cin.ignore(10000,'\n');

        if(is_number(age))
                break;

        cout << "Please enter valid age:" << endl;
    }
    return stoi(age);
}

int main() {

    cout << "Please enter file name" << endl;
    while (true){

        string file;
        getline(cin, file);
        file = remove_white_spaces(file);
        if(file == "exit"){
            break;
        }

        ifstream input_file;
        string input_file_line;
        input_file.open(file);

        if(!input_file.is_open()){
            cout << "\nUnable to open the file!" << endl;
            cout << "Try to enter valid file name or print exit to quit" << endl;
            continue;
        }

        int line_index = 0;

        while(getline(input_file, input_file_line)){

            string  name,
                    surname,
                    extra;
            string age;
            string sex;

            try {
                stringstream sstream(input_file_line);
                sstream >> name >> surname >> sex >> age >> extra;
                if(input_file_line == ""){
                    line_index++;
                    continue;
                }
                if (!validate_sex(sex)) {
                    throw "Incorrect sex in line ";
                }
                if (!is_number(age)) {
                    throw "Invalid age in line ";
                }
                if(!extra.empty()){
                    throw "Extra words found in line ";
                }
                Human person(name, surname, sex, stoi(age));

                people.push_back(person);
            }catch (const char* msg) {
                cout << msg  << line_index + 1 << endl;
                line_index++;
                continue;
            }
                line_index++;
        }
        input_file.close();

        while (true){
            cout << endl;
            cout << "The vector now looks this way :\n" << endl;

            printPeople(cout, "");

            cout << endl << "If you want to create new object - print ADD" << endl;
            cout << "If you want to delete certain object - print DELETE"<< endl;
            cout << "If you want to change certain object - print EDIT"<< endl;
            cout << "If you don't want to do any changes - print PASS"<< endl;

            string action;
            getline(cin, action);
            action = remove_white_spaces(action);

            if(action == "ADD"){
                cout << "\nIn order to ADD new object you should enter such fields as First Name, Last Name, Sex and Age."<< endl;

                string FirstName = input_first_name();

                string LastName = input_last_name();

                cout << "Now enter Sex ( Male or Female) : " << endl;
                string Sex = input_sex();

                cout << "Now enter age (it should be an integer number) : " << endl;
                int age = input_age();

                cout << "Your object is : " << FirstName << " " << LastName << " " << Sex << " " << age << endl;

                Human person(FirstName, LastName, Sex, age);
                people.push_back(person);
                cout << "You added new object."<< endl;
            }
            else if(action == "DELETE"){
                cout << "\nIn order to delete object you should specify index of object to delete. Here are objects and its id's: "<< endl;

                printPeople(cout, "ID");

                cout << "Enter the id of object you want to delete. It should be an integer number" << endl;

                int id = input_id();

                cout << "Here is your object : ";
                printPerson(cout, id, "ID");

                cout << "If you want to delete this object type YES, if not - type anything you want" << endl;

                string verify;
                cin >> verify;
                if(verify == "YES"){
                    cout << "DELETED" << endl;
                    people.erase(people.begin() + id);
                    cout << "Now vector looks this way : " << endl;
                    printPeople(cout, "ID");
                }else{
                    cout << "Action canceled" << endl;
                }
            }
            else if(action == "EDIT"){
                cout << "\nIn order to edit certain object - you should enter an id of the object you want to edit ( it should be an integer value ) : "<< endl;
                printPeople(cout, "ID");

                int id = input_id();
                printPeople(cout, "ID");
                while(true){
                    cout << "Now choose the field you want to edit :\nL - for Last Name\nF - for First Name\nS - for Sex\nA - for Age\nEnter PASS to finish editing" << endl;
                    string value;
                    getline(cin, value);
                    value = remove_white_spaces(value);

                    if(value == "L"){
                        cout << "Enter Last Name you want to put instead of previous one" << endl;
                        people[id].FirstName = input_last_name();
                    }
                    else if(value == "F"){
                        cout << "Enter First Name you want to put instead of previous one" << endl;
                        people[id].FirstName = input_first_name();
                    }
                    else if(value == "S"){
                        cout << "Enter Sex you want to put instead of previous one (Male or Female)" << endl;
                        people[id].sex = input_sex();

                    }
                    else if(value == "A"){
                        cout << "Enter Age you want to put instead of previous one" << endl;
                        people[id].age = input_age();
                    }
                    else if(value == "PASS"){
                        cout << "Now object looks this way : " << endl;
                        printPerson(cout, id, "ID");
                        cout << "You have just edited an object.\n"<< endl;
                        break;
                    }
                    else{
                        cout << "Incorrect value selected, please try again" << endl;
                    }
                }
            }
            else if(action == "PASS"){
                while(true){
                    cout << "You skipped all the editing operations.  Now please enter the name of output file : "<< endl;
                    string output_file_name;
                    getline(cin, output_file_name);
                    output_file_name = remove_white_spaces(output_file_name);
                    ofstream myfile(output_file_name);
                    try{
                        if(myfile.is_open()){
                            ofstream ofs;
                            ofs.open(output_file_name, std::ofstream::out | std::ofstream::trunc);
                            ofs.close();

                            printPeople(myfile);

                            myfile.close();
                            cout << "Success" << endl;
                            return 0;
                        }else{
                            throw;
                        }
                    }catch(...){
                        cout << "Unable to open the file!" << endl;
                        cout << "Try to enter valid file name or print exit to quit" << endl;
                    }
                }
            }else{
                cout << "\nPlease select one of the actions: ADD, DELETE, EDIT, PASS"<< endl;
            }
        }
        break;
    }

    return 0;
}
