// Library Management System using Object-Oriented Programming in C++
// Kushagra Sharma

#include <bits/stdc++.h>
using namespace std;

class user{
protected:
    string password;
public:
    string name;
    string id;
    void setPassword(string s){
        this->password=s;
    };
    string getPassword(){
        return this->password;
    };
    int usertype;// 1 for student, 2 for professor and 3 for librarian
};

class student: public user{
public:
    vector<string> listofissuedbooks;
    int fine;
    string * readList=NULL;
    int sizeOfReadList=0;
    int studentInterface();
    int calculateFine(string returnDate,string dueDate);
    void clearFineAmount();
    void addToReadListS(string nameOfBook);
    void chooseForReadListS();
    void SearchByGenre();
};

class professor: public user{
public:
    vector<string> listofissuedbooks;
    int fine;
    string * readList=NULL;
    int sizeOfReadList=0;
    int professorInterface();
    int calculateFine(string returnDate,string dueDate);
    void clearFineAmount();
    void addToReadList(string nameOfBook);
    void chooseForReadList();
};

class librarian: public user{
public:
    int librarianInterface();
};

class Book{
public:
    string title;
    string author;
    string isbn;
    string publication;
    int available;// 0 if it is issued(not available) and 1 if it is available.
    string issuedto;// - if it is available, else username
    string issuedate;
    string bookRequest(string id);
    string showDueDate(int usertype);
    string genre;

};

class BookDatabase{
public:
    void displayBooks();
    void displayAvailableBooks();
    void checkAvailability();
    void addBook();
    void deleteBook();
    void updateBook();
    bool search();
};

class userDatabase{
public:
    void displayUsers();
    void addUser();
    void updateUser();
    void deleteUser();
    void searchUser();
    bool search();
};

vector<user> listOfUsers;
vector<Book> listOfBooks;
vector<student> listOfStudents;
vector<professor> listOfProfessors;
vector<librarian> listOfLibrarians;

int librarian::librarianInterface(){
    while(1){
        cout << "\n1 - See list of all books.\n";
        cout << "2 - See list of all users.\n";
        cout << "3 - Add user.\n";
        cout << "4 - Update user.\n";
        cout << "5 - Delete user.\n";
        cout << "6 - Add book.\n";
        cout << "7 - Update book.\n";
        cout << "8 - Delete book.\n";
        cout << "9 - Check which book is issued to which user.\n";
        cout << "10 - See due date of a particular book.\n";
        cout << "11 - Check which books are issued by a particular user.\n";
        cout << "12 - See fine amount of a particular user.\n";
        cout << "13 - Clear Fine amount of a particular user.\n";
        cout << "14 - Logout.\n";
        string c;
        cout << "Enter the serial number corresponding to your query: ";
        cin >> c;
        if(c=="1"){BookDatabase temp;temp.displayBooks();}
        else if(c=="2"){userDatabase temp;temp.displayUsers();}
        else if(c=="3"){userDatabase temp;temp.addUser();}
        else if(c=="4"){userDatabase temp;temp.updateUser();}
        else if(c=="5"){userDatabase temp;temp.deleteUser();}
        else if(c=="6"){BookDatabase temp;temp.addBook();}
        else if(c=="7"){BookDatabase temp;temp.updateBook();}
        else if(c=="8"){BookDatabase temp;temp.deleteBook();}
        else if(c=="9"){
            cout << "Enter the book ISBN code: ";
            string temp;
            cin >> temp;
            for(auto i : listOfBooks){
                if(i.isbn==temp){
                    if(i.issuedto=="-"){
                        cout << "This book is not issued by anyone currently.\n";
                        continue;
                    }
                    cout << "   Book: " << i.title << " is issued to: " << i.issuedto << "(userid) and Due date: ";
                    string idi=i.issuedto;
                    int done=1;
                    for(auto j : listOfStudents){
                        if(j.id==idi){
                            cout << i.showDueDate(1)<<"\n";
                            done=0;
                        }
                    }
                    if(done)cout << i.showDueDate(2)<<"\n";

                }
            }
        }else if(c=="10"){
            cout << "Enter is ISBN of the book: ";
            string t;
            cin >> t;
            for(int i=0;i<listOfBooks.size();i++){
                if(listOfBooks[i].isbn==t){
                    for(int j=0;j<listOfUsers.size();j++){
                        if(listOfUsers[j].id==listOfBooks[i].issuedto){
                            if(listOfUsers[j].usertype==1)cout << "Book is issued by: "<< listOfUsers[j].id << " and due date is "<<listOfBooks[i].showDueDate(1) <<"\n";
                            else cout << "Book is issued by: "<< listOfUsers[j].id << " and the due date is "<<listOfBooks[i].showDueDate(2)<<"\n";
                        }
                    }
                }
            }
        }else if(c=="11"){
            cout << "Enter the userid of the person: ";
            string temp;
            cin >> temp;
            int done=0;
            for(auto i : listOfStudents){
                if(i.id==temp){
                    done=1;
                    cout << "Books issued by: " << i.name << "\n";
                    for(auto j : i.listofissuedbooks){
                        for(auto p : listOfBooks){
                            if(p.isbn==j){
                                cout << "   Name: " << p.title << " | ISBN: " << p.isbn << " | Due Date: " << p.showDueDate(1) <<".\n";
                            }
                        }
                    }

                }
            }
            for(auto i : listOfProfessors){
                if(i.id==temp){
                    done=1;
                    cout << "Books issued by: " << i.name << "\n";
                    for(auto j : i.listofissuedbooks){
                        for(auto p : listOfBooks){
                            if(p.isbn==j){
                                cout << "   Name: " << p.title << " | ISBN: " << p.isbn << " | Due Date: " << p.showDueDate(2) <<".\n";
                            }
                        }
                    }
                }
            }
        }else if(c=="12"){
            cout << "Enter the userid: ";
            string t;
            cin >> t;
            for(auto i : listOfStudents){
                if(i.id==t){
                    cout << "Fine to be paid by " << i.name << " " << i.fine << "\n";
                }
            }
            for(auto i : listOfProfessors){
                if(i.id==t){
                    cout << "Fine to be paid by " << i.name << " " << i.fine << "\n";
                }
            }

        }else if(c=="13"){
            cout << "Enter the userid of the person whose fine is cleared: ";
            string t;
            cin >> t;
            for(int i=0;i<listOfStudents.size();i++){
                if(listOfStudents[i].id==t){
                    listOfStudents[i].clearFineAmount();
                }
            }
            for(int i=0;i<listOfProfessors.size();i++){
                if(listOfProfessors[i].id==t){
                    listOfProfessors[i].clearFineAmount();
                }
            }
        }else if(c=="14")return 0;
        else cout << "Please enter a valid serial number.\n";
    }
    return 0;
}

int professor::professorInterface(){
    while(1){
        cout << "\n1 - See list of all books.\n";
        cout << "2 - Books currently issued by " << this->name << "\n";
        cout << "3 - See list of available books\n";
        cout << "4 - See if a particular book is available or not\n";
        cout << "5 - Request a book\n";
        cout << "6 - Return a book\n";
        cout << "7 - View Fine amount\n";
        cout << "8 - view your read list\n";
        cout <<"9 - search By genre\n";
        cout << "10- Logout\n";
        char c;
        cout << "Enter the serial number corresponding to your query: ";
        cin >> c;
        if(c=='1'){BookDatabase temp;temp.displayBooks();}
        else if(c=='2'){
            cout << this->listofissuedbooks.size() << endl;
            for(auto i : this->listofissuedbooks){
                cout << i << endl;
                for(auto j : listOfBooks){
                    if(i==j.isbn){
                        cout << "   " << "Name: " << j.title << " | Author: " << j.author << " | ISBN: " << j.isbn << " | Publication: " << j.publication << " | Due Date: "<< j.showDueDate(2) <<"\n";
                    }
                }
            }
        }else if(c=='3'){BookDatabase temp;temp.displayAvailableBooks();}
        else if(c=='4'){
            BookDatabase temp;
            temp.checkAvailability();
        }else if(c=='5'){
            if(this->fine!=0){
                cout << "You have some existing fine. Please clear you dues.\n";
            }else{
                int yourChoise;
                Book temp;
                string temp2;
                cout<<"1.Add to read list"<<endl<<"2.Request book"<<endl;
                cin>>yourChoise;
                if(yourChoise==1) {
                    cout<<"Enter name of book"<<endl;
                    cin>>temp2;
                    addToReadList(temp2);
                    cout<<"Added to reading list"<<endl;
                }
                else if(yourChoise==2) {
                    string isb = temp.bookRequest(this->id);
                } else
                    return 0;
            }
        }else if(c=='6'){
            cout << "Enter the name of the book you want to return: ";
            string t;
            while(t=="")getline(cin,t);
            for(int i=0;i<this->listofissuedbooks.size();i++){
                for(int j=0;j<listOfBooks.size();j++){
                    if(listOfBooks[j].title==t && this->listofissuedbooks[i]==listOfBooks[j].isbn){
                        cout << "Enter the return date(DDMMYYYY): ";
                        string t;
                        cin >> t;
                        int f = this->calculateFine(t,listOfBooks[j].showDueDate(2));
                        // cout << f << " " << listOfBooks[j].showDueDate() << endl;
                        this->fine+=f;
                        if(f)cout << "You have to pay " << f << " for late return.\n";
                        if(this->fine)cout << "Total outstanding fine to be paid " << this->fine <<"\n";
                        if(!f && !this->fine)cout << "Thank you for returning the book on time!\n";
                        listOfBooks[j].available=1;
                        listOfBooks[j].issuedate="-";
                        listOfBooks[j].issuedto="-";
                        vector<string>::iterator itr;
                        itr=this->listofissuedbooks.begin();
                        while(*itr!=listOfBooks[j].isbn)itr++;
                        this->listofissuedbooks.erase(itr);
                        i--;
                    }
                }
            }

        }else if(c=='7'){
            cout << "The existing fine is: " << this->fine << "\n";
        }
        else if(c=='8'){
            chooseForReadList();
        }
          else if(c=='9')
        {
            student temp;
            temp.SearchByGenre();
        }
        else if(c=='10'){
            return 0;
        }
      
        else cout << "Enter a valid serial number.\n";
    }

}

int professor::calculateFine(string retd,string dued){
    long long i = stoi(retd);
    long long y1 = i%10000;
    i/=10000;
    long long m1 = i%100;
    i/=100;
    long long d1 = i%100;
    i/=100;
    m1=(m1+9)%12;
    y1 = y1-m1/10;
    long long dateno1 = 365*y1+y1/4-y1/100+y1/400 + (m1*306+5)/10 + (d1-1);
    i = stoi(dued);
    long long y2 = i%10000;
    i/=10000;
    long long m2 = i%100;
    i/=100;
    long long d2 = i%100;
    i/=100;
    m2=(m2+9)%12;
    y2 = y2-m2/10;
    long long dateno2 = 365*y2+y2/4-y2/100+y2/400 + (m2*306+5)/10 + (d2-1);
    long long diff = dateno1-dateno2;
    if(diff<=0){
        return 0;
    }else return 5*diff;
}

void professor::clearFineAmount(){
    this->fine=0;
    cout << "Fine of " << this->name << " cleared.\n";
    return;
}

int student::studentInterface(){
    while(1){
        cout << "\n1 - See list of all books.\n";
        cout << "2 - Books currently issued by " << this->name << "\n";
        cout << "3 - See list of available books\n";
        cout << "4 - See if a particular book is available or not\n";
        cout << "5 - Request a book\n";
        cout << "6 - Return a book\n";
        cout << "7 - View Fine amount\n";
        cout << "8 - View read list\n";
        cout << "9 - search By genre\n";
        cout << "10 - Logout\n";
        char c;
        cout << "Enter the serial number corresponding to your query: ";
        cin >> c;
        if(c=='1'){BookDatabase temp;temp.displayBooks();}
        else if(c=='2'){
            cout << this->listofissuedbooks.size() << endl;
            for(auto i : this->listofissuedbooks){
                for(auto j : listOfBooks){
                    if(i==j.isbn){
                        cout << "   " << "Name: " << j.title << " | Author: " << j.author << " | ISBN: " << j.isbn << " | Publication: " << j.publication << " | Due Date: "<< j.showDueDate(1) << "\n";
                    }
                }
            }
        }else if(c=='3'){BookDatabase temp;temp.displayAvailableBooks();}
        else if(c=='4'){
            BookDatabase temp;
            temp.checkAvailability();
        }else if(c=='5'){
            if(this->fine!=0){
                cout << "You have some existing fine. Please clear you dues.\n";
            }else if(this->listofissuedbooks.size()>=5){
                cout << "You already have 5 issued books, return one to issue another.\n";
            }else{
                int yourChoise;
                Book temp;
                string temp2;
                cout<<"1.Add to read list"<<endl<<"2.Request book"<<endl;
                cin>>yourChoise;
                if(yourChoise==1) {
                    cout<<"Enter name of book"<<endl;
                    cin>>temp2;
                    addToReadListS(temp2);
                    cout<<"Added to reading list"<<endl;
                }
                else if(yourChoise==2) {
                    string isb = temp.bookRequest(this->id);
                } else
                    return 0;
            }

        }else if(c=='6'){
            cout << "Enter the name of the book you want to return: ";
            string t;
            while(t=="")getline(cin,t);
            for(int i=0;i<this->listofissuedbooks.size();i++){
                for(int j=0;j<listOfBooks.size();j++){
                    if(listOfBooks[j].title==t && this->listofissuedbooks[i]==listOfBooks[j].isbn){
                        cout << "Enter the return date(DDMMYYYY): ";
                        string t;
                        cin >> t;
                        int f = this->calculateFine(t,listOfBooks[j].showDueDate(1));
                        this->fine+=f;
                        if(f)cout << "You have to pay " << f << " for late return.\n";
                        if(this->fine)cout << "Total outstanding fine to be paid " << this->fine <<".\n";
                        if(!f && !this->fine)cout << "Thank you for returning the book on time!\n";
                        listOfBooks[j].available=1;
                        listOfBooks[j].issuedate="-";
                        listOfBooks[j].issuedto="-";
                        vector<string>::iterator itr;
                        itr=this->listofissuedbooks.begin();
                        while(*itr!=listOfBooks[j].isbn)itr++;
                        this->listofissuedbooks.erase(itr);
                        i--;
                    }
                }
            }

        }else if(c=='7'){
            cout << "The existing fine is: " << this->fine << "\n";
        }
        else if(c=='8'){
            chooseForReadListS();
        }
        else if(c=='9')
        {
            student temp;
            temp.SearchByGenre();
        }
        else if(c=='10'){
            return 0;
        }
        else cout << "Enter a valid serial number.\n";
    }

}

int student::calculateFine(string retd,string dued){
    long long i = stoi(retd);
    long long y1 = i%10000;
    i/=10000;
    long long m1 = i%100;
    i/=100;
    long long d1 = i%100;
    i/=100;
    m1=(m1+9)%12;
    y1 = y1-m1/10;
    long long dateno1 = 365*y1+y1/4-y1/100+y1/400 + (m1*306+5)/10 + (d1-1);
    i = stoi(dued);
    long long y2 = i%10000;
    i/=10000;
    long long m2 = i%100;
    i/=100;
    long long d2 = i%100;
    i/=100;
    m2=(m2+9)%12;
    y2 = y2-m2/10;
    long long dateno2 = 365*y2+y2/4-y2/100+y2/400 + (m2*306+5)/10 + (d2-1);
    long long diff = dateno1-dateno2;
    if(diff<=0){
        return 0;
    }else return 2*diff;
}

void student::clearFineAmount(){
    this->fine=0;
    cout << "Fine of " << this->name << " cleared.\n";
    return;
}

string Book::bookRequest(string id){
    cout << "Enter the name of the book: ";
    string t;
    while(t=="")getline(cin,t);
    Book temp;
    int nb=listOfBooks.size();
    for(int i=0;i<nb;i++){
        if(listOfBooks[i].title==t && listOfBooks[i].available==1){
            listOfBooks[i].issuedto=id;
            listOfBooks[i].available=0;
            cout << "Please Enter the issue date(DDMMYYYY): ";
            cin >> t;
            listOfBooks[i].issuedate=t;
            cout << "Book issued successfully!\n";
            return listOfBooks[i].isbn;
        }
    }
    cout << "Sorry the book is not available to be issued\n";
    return "-";
}

string Book::showDueDate(int usertype){
    // Assigning a number to a date, adding the number and getting back the date from the new number.
    // Reference: https://web.archive.org/web/20170507133619/https://alcor.concordia.ca/~gpkatch/gdate-algorithm.html
    if(this->issuedate=="-"){
        cout << "This book hasn't been issued yet.\n";
        return "-";
    }
    long long i = stoi(this->issuedate);
    long long y = i%10000;
    i/=10000;
    long long m = i%100;
    i/=100;
    long long d = i%100;
    i/=100;
    // cout << y << " " << m <<" "<< d << endl;
    m=(m+9)%12;
    y = y-m/10;
    long long dateno = 365*y+y/4-y/100+y/400 + (m*306+5)/10 + (d-1);

    long long duedatno=dateno;
    if(usertype==1)duedatno+=30;
    else duedatno+=60;
    int duey = (10000*duedatno + 14780)/3652425;
    int ddd = duedatno-(365*duey+duey/4-duey/100+duey/400);
    if(ddd < 0 ){
        duey = duey-1;
        ddd = duedatno - (365*duey + duey/4 - duey/100 + duey/400);
    }
    int mi = (100*ddd + 52)/3060;
    int mm = (mi+2)%12+1;
    duey=duey + (mi+2)/12;
    int dd = ddd- (mi*306 + 5)/10 +1;
    string sdd = to_string(dd),smm=to_string(mm),sduey=to_string(duey);
    if(sdd.length()<2){
        sdd = "0"+sdd;
    }
    if(smm.length()<2)smm="0"+smm;
    if(sduey.length()<4){
        if(sduey.length()==3)sduey="0"+sduey;
        else if(sduey.length()==2)sduey="00"+sduey;
        else if(sduey.length()==1)sduey="000"+sduey;
        else sduey="0000";
    }
    string duedate= sdd+smm+sduey;
    // cout << sdd << " " << smm << " " << sduey <<endl;
    return duedate;
}

void BookDatabase::displayBooks(){
    for(auto i : listOfBooks){
        cout << "   " << "Name: " << i.title << " | Author: " << i.author << " | ISBN: " << i.isbn << " | Publication: " << i.publication << "\n";
    }
}

void BookDatabase::displayAvailableBooks(){
    for(auto i : listOfBooks){
        if(i.available==1)cout << "   " << "Name: " << i.title << " " << "Author: " << i.author << "\n";
    }
}

void BookDatabase::checkAvailability(){
    Book temp;
    string t;
    cout << "Enter the name of book to check its availability: ";
    while(t=="")getline(cin,t);// Loop because getline works differently and takes some extra space from previous input.
    int flag=0,done=0;
    for(auto i : listOfBooks){
        if(i.title==t){
            flag=1;
            if(i.available==1){
                cout << "Yes, " << i.title << " is available!\n";
                done=1;
            }
        }
    }
    if(flag && done==0){
        cout << "Sorry, "<< t << " isn't available right now.\n";
    }else if(flag==0 && done==0) cout << t << " isn't present in the library.\n";
}

void BookDatabase::addBook(){
    Book newBook;
    cout << "Enter the title of the book: ";
    string t;
    while(t=="")getline(cin,t);
    newBook.title=t;
    cout << "Enter the author of the book: ";
    t="";
    while(t=="")getline(cin,t);
    newBook.author=t;
    cout << "Enter the ISBN of the book: ";
    t="";
    while(t=="")getline(cin,t);
    newBook.isbn=t;
    cout << "Enter the book publication: ";
    t="";
    while(t=="")getline(cin,t);
    newBook.available=1;
    newBook.publication=t;
    newBook.issuedate="-";
    newBook.issuedto="-";
    listOfBooks.push_back(newBook);
    cout << "Book added.\n";
    
    
}

void BookDatabase::updateBook(){
    cout << "Enter the isbn of the book to be updated: ";
    string t;
    cin >> t;
    int i=0;
    for(;i<listOfBooks.size();i++){
        if(listOfBooks[i].isbn==t)break;
    }
    cout << "Do you want to update the name of the book? (Yes/No): ";
    cin >> t;
    if(t=="Yes"){
        cout << "Enter the new name of the book: ";
        cin.ignore();
        getline(cin,listOfBooks[i].title);
    }
    cout << "Do you want to update the ISBN of the book? (Yes/No): ";
    cin >> t;
    if(t=="Yes"){
        cout << "Enter the new ISBN of the book: ";
        cin.ignore();
        getline(cin,listOfBooks[i].isbn);
    }
    cout << "Do you want to update the Author of the book? (Yes/No): ";
    cin >> t;
    if(t=="Yes"){
        cout << "Enter the name of the Author of the book: ";
        cin.ignore();
        getline(cin,listOfBooks[i].author);
    }
    cout << "Do you want to update the publication of the book? (Yes/No): ";
    cin >> t;
    if(t=="Yes"){
        cout << "Enter the publication of the book: ";
        cin.ignore();
        getline(cin,listOfBooks[i].publication);
    }
    cout << "Book updated.\n";
}

void BookDatabase::deleteBook(){
    cout << "Enter the book ISBN which you want to delete: ";
    string t;
    cin >> t;
    vector<Book>::iterator itr;
    for(itr=listOfBooks.begin();itr!=listOfBooks.end();itr++){
        if(((*itr).isbn) == t){
            string uid = (*itr).issuedto;
            for(int k=0;k<listOfStudents.size();k++){
                if(listOfStudents[k].id==uid){
                    vector<string>::iterator it;
                    for(it=listOfStudents[k].listofissuedbooks.begin();it!=listOfStudents[k].listofissuedbooks.end();it++){
                        if(*it==t){
                            listOfStudents[k].listofissuedbooks.erase(it);
                            break;
                        }
                    }
                }
            }
            for(int k=0;k<listOfProfessors.size();k++){
                if(listOfProfessors[k].id==uid){
                    vector<string>::iterator it;
                    for(it=listOfProfessors[k].listofissuedbooks.begin();it!=listOfProfessors[k].listofissuedbooks.end();it++){
                        if(*it==t){
                            listOfProfessors[k].listofissuedbooks.erase(it);
                            break;
                        }
                    }
                }
            }
            listOfBooks.erase(itr);
            cout << "Book has been deleted.\n";
            break;
        }
    }
}

bool BookDatabase::search(){
    cout << "Enter the book title: ";
    string t;cin >> t;
    for(auto i : listOfBooks){
        if(i.title==t){
            cout << "Book is present!\n";
            return true;
        }
    }
    return false;
}

void userDatabase::displayUsers(){
    for(auto i : listOfUsers){
        cout << "   Name- " << i.name << " | id- " << i.id;
        if(i.usertype==1){
            cout << " | Category- Student\n";
        }else if(i.usertype==2)cout << " | Category- Professor\n";
        else cout << " | Category- Librarian\n";
    }
}

void userDatabase::addUser(){
    user newUser;
    cout << "Enter the name of the user: ";
    string temp;
    while(temp=="")getline(cin,temp);
    newUser.name=temp;
    cout << "Enter the userid: ";
    temp="";
    while(temp=="")getline(cin,temp);
    newUser.id=temp;
    temp="";
    cout << "Enter the password for the user: ";
    while(temp=="")getline(cin,temp);
    newUser.setPassword(temp);
    cout << "Enter the type of user: (Student/Professor/Librarian): ";
    temp="";
    while(temp=="")getline(cin,temp);
    if(temp=="Student")newUser.usertype=1;
    else if(temp=="Professor")newUser.usertype=2;
    else if(temp=="Librarian")newUser.usertype=3;
    else{
        cout << "Wrong type of user, please retry.\n";
        return;
    }
    cout << "User Created.\n";
    listOfUsers.push_back(newUser);
    if(newUser.usertype==1){
        student n;
        n.name=newUser.name;
        n.setPassword(newUser.getPassword());
        n.id=newUser.id;
        n.usertype=1;
        n.fine=0;
        listOfStudents.push_back(n);
    }else if(newUser.usertype==2){
        professor n;
        n.name=newUser.name;
        n.setPassword(newUser.getPassword());
        n.id=newUser.id;
        n.usertype=2;
        n.fine=0;
        listOfProfessors.push_back(n);
    }else{
        librarian n;
        n.name=newUser.name;
        n.setPassword(newUser.getPassword());
        n.id=newUser.id;
        n.usertype=3;
        listOfLibrarians.push_back(n);
    }
}

void userDatabase::updateUser(){
    cout << "Enter the userid of the user: ";
    string t;
    cin >> t;
    int i=0,j=0;
    for(;i<listOfUsers.size();i++){
        if(listOfUsers[i].id==t)break;
    }
    for(; listOfUsers[i].usertype == 1 && j<listOfStudents.size();j++){
        if(listOfStudents[j].id==t)break;
    }
    for(; listOfUsers[i].usertype == 2 && j<listOfProfessors.size();j++){
        if(listOfProfessors[j].id==t)break;
    }
    for(; listOfUsers[i].usertype == 3 && j<listOfLibrarians.size();j++){
        if(listOfLibrarians[j].id==t)break;
    }
    cout << "Do you want to change the name of the user? (Yes/No): ";
    cin >> t;
    if(t=="Yes"){
        cout << "Enter the new name of the user: ";
        cin.ignore();
        getline(cin,listOfUsers[i].name);
        if(listOfUsers[i].usertype==1)listOfStudents[j].name=listOfUsers[i].name;
        if(listOfUsers[i].usertype==2)listOfProfessors[j].name=listOfUsers[i].name;
        if(listOfUsers[i].usertype==3)listOfLibrarians[j].name=listOfUsers[i].name;
    }
    cout << "Do you want to change the id of the user? (Yes/No): ";
    cin >> t;
    if(t=="Yes"){
        cout << "Enter the new id of the user: ";
        cin.ignore();
        getline(cin,listOfUsers[i].id);
        if(listOfUsers[i].usertype==1)listOfStudents[j].id=listOfUsers[i].id;
        if(listOfUsers[i].usertype==2)listOfProfessors[j].id=listOfUsers[i].id;
        if(listOfUsers[i].usertype==3)listOfLibrarians[j].id=listOfUsers[i].id;
    }
    cout << "Do you want the change the password of the user? (Yes/No): ";
    cin >> t;
    if(t=="Yes"){
        cout << "Enter the new password of the user: ";
        cin.ignore();
        getline(cin,t);
        listOfUsers[i].setPassword(t);
        if(listOfUsers[i].usertype==1)listOfStudents[j].setPassword(listOfUsers[i].getPassword());
        if(listOfUsers[i].usertype==2)listOfProfessors[j].setPassword(listOfUsers[i].getPassword());
        if(listOfUsers[i].usertype==3)listOfLibrarians[j].setPassword(listOfUsers[i].getPassword());
    }
    cout << "User Updated.\n";
}

void userDatabase::deleteUser(){
    cout << "Enter the userid of the user to be deleted: ";
    string t;
    cin >> t;
    vector<user>::iterator itr;
    for(itr=listOfUsers.begin();itr!=listOfUsers.end();itr++){
        if((*itr).id == t){
            int type = (*itr).usertype;
            listOfUsers.erase(itr);
            cout << "User has been deleted.\n";
            if(type==1){
                vector<student>::iterator itr1;
                for(itr1=listOfStudents.begin();itr1!=listOfStudents.end();itr1++){
                    if((*itr1).id==t){
                        for(auto j : (*itr1).listofissuedbooks){
                            for(int k=0;k<listOfBooks.size();k++){
                                if(listOfBooks[k].isbn==j){
                                    listOfBooks[k].issuedate="-";
                                    listOfBooks[k].issuedto="-";
                                    listOfBooks[k].available=1;
                                }
                            }
                        }
                        listOfStudents.erase(itr1);
                        break;
                    }
                }
            }else if(type==2){
                vector<professor>::iterator itr1;
                for(itr1=listOfProfessors.begin();itr1!=listOfProfessors.end();itr1++){
                    if((*itr1).id==t){
                        for(auto j : (*itr1).listofissuedbooks){
                            for(int k=0;k<listOfBooks.size();k++){
                                if(listOfBooks[k].isbn==j){
                                    listOfBooks[k].issuedate="-";
                                    listOfBooks[k].issuedto="-";
                                    listOfBooks[k].available=1;
                                }
                            }
                        }
                        listOfProfessors.erase(itr1);
                        break;
                    }
                }
            }else{
                vector<librarian>::iterator itr1;
                for(itr1=listOfLibrarians.begin();itr1!=listOfLibrarians.end();itr1++){
                    if((*itr1).id==t){
                        listOfLibrarians.erase(itr1);
                        break;
                    }
                }
            }
            break;
        }
    }
}

bool userDatabase::search(){
    cout << "Enter the name of the user: ";
    string t;cin >> t;
    for(auto i : listOfUsers){
        if(i.name == t){
            cout << "User exists and has the username: " << i.id << "!\n";
            return true;
        }
    }
    return false;
}

void getDatabaseData(){
    string line,word;
    vector<string> userdata;
    fstream userfile("user.csv" ,ios:: in);
    if(userfile.is_open()){
        while(getline(userfile,line)){
            userdata.clear();
            stringstream s(line);
            while(getline(s,word,',')){
                userdata.push_back(word);
            }
            user temp;
            temp.name=userdata[0];
            temp.id = userdata[1];
            temp.setPassword(userdata[2]);
            temp.usertype= stoi(userdata[3]);
            listOfUsers.push_back(temp);
            if(temp.usertype==1){
                student n;
                n.name=userdata[0];
                n.setPassword(userdata[2]);
                n.id=userdata[1];
                n.fine=stoi(userdata[4]);
                n.usertype=1;
                listOfStudents.push_back(n);
            }else if(temp.usertype==2){
                professor n;
                n.name=userdata[0];
                n.setPassword(userdata[2]);
                n.id=userdata[1];
                n.fine=stoi(userdata[4]);
                n.usertype=2;
                listOfProfessors.push_back(n);
            }else{
                librarian n;
                n.name=userdata[0];
                n.setPassword(userdata[2]);
                n.id=userdata[1];
                n.usertype=3;
                listOfLibrarians.push_back(n);
            }
        }
    }else{
        cout << "Make sure there is a user.csv file in the same directory" << endl;
    }
    vector<string> bookdata;
    fstream bookfile("books.csv",ios::in);
    if(bookfile.is_open()){
        while(getline(bookfile,line)){
            bookdata.clear();
            stringstream s(line);
            while(getline(s,word,','))bookdata.push_back(word);
            Book temp ;
            temp.title=bookdata[0];
            temp.author=bookdata[1];
            temp.isbn=bookdata[2];
            temp.publication=bookdata[3];
            temp.available=stoi(bookdata[4]);
            temp.issuedto=bookdata[5];
            temp.issuedate=bookdata[6];
            listOfBooks.push_back(temp);
        }
    }else{
        cout << "Make sure there is a books.csv file in the same directory." << endl;
    }
    //initialising books issued by students and professors
    for(auto i : listOfBooks){
        if(i.issuedto!="-"){
            for(int j=0;j<listOfStudents.size();j++){
                if(listOfStudents[j].id==i.issuedto){
                    listOfStudents[j].listofissuedbooks.push_back(i.isbn);
                }
            }
            for(int j=0;j<listOfProfessors.size();j++){
                if(listOfProfessors[j].id==i.issuedto){
                    listOfProfessors[j].listofissuedbooks.push_back(i.isbn);
                }
            }
        }
    }
}

void updateDatabase(){
    remove("books.csv");
    remove("user.csv");
    fstream fout;
    fout.open("user.csv",ios::out);
    for(auto i : listOfStudents){
        fout << i.name << ",";
        fout << i.id << ",";
        fout << i.getPassword() << ",";
        fout << i.usertype << ",";
        fout << i.fine<< "\n";
    }
    for(auto i : listOfProfessors){
        fout << i.name << ",";
        fout << i.id << ",";
        fout << i.getPassword() << ",";
        fout << i.usertype << ",";
        fout << i.fine << "\n";
    }
    for(auto i : listOfLibrarians){
        fout << i.name << ",";
        fout << i.id << ",";
        fout << i.getPassword() << ",";
        fout << i.usertype << "\n";
    }
    fout.close();
    fout.open("books.csv",ios::out);
    for(auto i : listOfBooks){
        fout << i.title << ",";
        fout << i.author << ",";
        fout << i.isbn << ",";
        fout << i.publication << ",";
        fout << i.available << ",";
        fout << i.issuedto << ",";
        fout << i.issuedate << "\n";
    }
    fout.close();
}

int main(){
    getDatabaseData();
    int correctCredentials=0;
    user currUser;
    while(correctCredentials==0){
        string un,pass;
        cout << "Enter the userid: (Eg: defaultLibrarian) ";
        cin >> un;
        cout << "Enter the password: (Eg: 1234) ";
        cin >> pass;
        if(un=="defaultLibrarian"  && pass=="1234"){
            correctCredentials=1;
            break;
        }
        for(auto i : listOfUsers){
            if(i.id==un && pass==i.getPassword()){
                currUser=i;
                correctCredentials=1;
                break;
            }
        }
        if(!correctCredentials)cout << "Incorrect Credentials.\n";
    }
    cout << "Hello " << currUser.name << "!"<< endl;
    if(currUser.usertype==1){
        int i=0;
        for(;i<listOfStudents.size();i++){
            if(listOfStudents[i].id==currUser.id){
                break;
            }
        }
        listOfStudents[i].studentInterface();
    }else if(currUser.usertype==2){
        int i=0;
        for(;i<listOfProfessors.size();i++){
            if(listOfProfessors[i].id==currUser.id){
                break;
            }
        }
        listOfProfessors[i].professorInterface();
    }else{
        int i=0;
        for(;i<listOfLibrarians.size();i++){
            if(listOfLibrarians[i].id==currUser.id){
                break;
            }
        }
        listOfLibrarians[i].librarianInterface();
    }
    updateDatabase();
    return 0;
}
void professor:: addToReadList(string nameOfBook)
{
    this->sizeOfReadList+=1;
    string* newReadList=new string [sizeOfReadList];
    for(int i=0;i<sizeOfReadList;i++)
        newReadList[i]=readList[i];
    newReadList[sizeOfReadList-1]=nameOfBook;
    this->readList=newReadList;
    delete newReadList;
}
void professor:: chooseForReadList(){
    string * str;
    str = new string[sizeOfReadList-1];
    cout<<" choose number to enter press 0"<<endl;
    for(int i=0;i<sizeOfReadList;i++)
        cout<<i-1<<"."<<" "<<readList[i]<<endl;
    int choice;
    cin>>choice;
    if(choice==0)
        return;
    this->listofissuedbooks.push_back(readList[choice-1]);
    for(int i=0;i<sizeOfReadList;i++)
        for(int j=0;j<sizeOfReadList;j++)
            if(i!=j)
                str[j]=readList[i];
    sizeOfReadList-=1;
    readList=str;
}
void student:: addToReadListS(string nameOfBook)
{
    this->sizeOfReadList+=1;
    string* newReadList=new string [sizeOfReadList];
    for(int i=0;i<sizeOfReadList;i++)
        newReadList[i]=readList[i];
    newReadList[sizeOfReadList-1]=nameOfBook;
    this->readList=newReadList;
    delete newReadList;
}
void student:: chooseForReadListS(){
    string * str;
    str = new string[sizeOfReadList-1];
    cout<<" choose number to enter press 0"<<endl;
    for(int i=0;i<sizeOfReadList;i++)
        cout<<i-1<<"."<<" "<<readList[i]<<endl;
    int choice;
    cin>>choice;
    if(choice==0)
        return;
    this->listofissuedbooks.push_back(readList[choice-1]);
    for(int i=0;i<sizeOfReadList;i++)
        for(int j=0;j<sizeOfReadList;j++)
            if(i!=j)
                str[j]=readList[i];
    sizeOfReadList-=1;
    readList=str;
}
void student::SearchByGenre()
{
    cout<<"please enter the genre"<<endl;
    string t;
    while(t=="")getline(cin,t);
    for(auto p : listOfBooks)
    {
        if (p.genre == t)
            cout << "   Name: " << p.title << ".\n";
    }
}//SearchByGenre
