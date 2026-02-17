#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

// ==================== BOOK CLASS ====================
class book {
private:
    char bno[6];
    char bname[50];
    char aname[20];

public:
    void createbook() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nENTER BOOK NO. ";
        cin >> bno;
        cin.ignore();
        cout << "\nENTER BOOK NAME ";
        cin.getline(bname, 50);
        cout << "\nENTER AUTHOR NAME ";
        cin.getline(aname, 20);
        cout << "\n\n\nBook Created..";
    }

    void showbook() {
        cout << "\nBook Number: " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nBook Author Name: " << aname;
    }

    void modifybook() {
        cout << "\nBook Number: " << bno;
        cout << "\nModify Book Name: ";
        cin.getline(bname, 50);
        cout << "\nModify Author's Name: ";
        cin.getline(aname, 20);
    }

    char* retbno() {
        return bno;
    }

    void report() {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

// ==================== STUDENT CLASS ====================
class student {
private:
    char admno[6];
    char name[20];
    char stbno[6];
    int token;

public:
    void createstudent() {
        system("clear || cls");
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The Admission No. ";
        cin >> admno;
        cin.ignore();
        cout << "Enter The Student Name ";
        cin.getline(name, 20);
        token = 0;
        stbno[0] = '\0';
        cout << "\n\nStudent Record Created...";
    }

    void showstudent() {
        cout << "\nAdmission Number: " << admno;
        cout << "\nStudent Name: " << name;
        cout << "\nNo of Book Issued: " << token;
        if(token == 1) {
            cout << "\nBook Number " << stbno;
        }
    }

    void modifystudent() {
        cout << "\nAdmission No. " << admno;
        cout << "\nModify Student Name: ";
        cin.getline(name, 20);
    }

    char* retadmno() {
        return admno;
    }

    char* retstbno() {
        return stbno;
    }

    int rettoken() {
        return token;
    }

    void addtoken() {
        token = 1;
    }

    void resettoken() {
        token = 0;
    }

    void getstbno(char t[]) {
        strcpy(stbno, t);
    }

    void report() {
        cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
    }
};

// ==================== GLOBAL OBJECTS ====================
fstream fp, fp1;
book bk;
student st;

// ==================== FUNCTION PROTOTYPES ====================
void writebook();
void writestudent();
void displayspb(char n[]);
void displaysps(char n[]);
void modifybook();
void modifystudent();
void deletestudent();
void deletebook();
void displayalls();
void displayallb();
void bookissue();
void bookdeposit();
void adminmenu();
void intro();



// ==================== INTRODUCTION SCREEN ====================
void intro() {
    system("clear || cls");
    cout << "\n\n\n\t\t==================================";
    cout << "\n\t\t    LIBRARY";
    cout << "\n\t\t    MANAGEMENT";
    cout << "\n\t\t    SYSTEM";
    cout << "\n\t\t==================================";
    cout << "\n\n\t\tPress Enter to continue...";
    cin.get();
}

// ==================== ADMINISTRATOR MENU ====================
void adminmenu() {
    system("clear || cls");
    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL STUDENT RECORD";
    cout << "\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\t6.CREATE BOOK";
    cout << "\n\n\t7.DISPLAY ALL BOOKS";
    cout << "\n\n\t8.DISPLAY SPECIFIC BOOK";
    cout << "\n\n\t9.MODIFY BOOK RECORD";
    cout << "\n\n\t10.DELETE BOOK RECORD";
    cout << "\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\tPLEASE ENTER YOUR CHOICE(1-11) ";
    cin >> ch2;
    
    switch(ch2) {
        case 1:
            writestudent();
            break;
        case 2:
            displayalls();
            break;
        case 3: {
            char num[6];
            system("clear || cls");
            cout << "\n\n\tPlease enter admission no. ";
            cin >> num;
            displaysps(num);
            break;
        }
        case 4:
            modifystudent();
            break;
        case 5:
            deletestudent();
            break;
        case 6:
            writebook();
            break;
        case 7:
            displayallb();
            break;
        case 8: {
            char num[6];
            system("clear || cls");
            cout << "\n\n\tPlease enter book no. ";
            cin >> num;
            displayspb(num);
            break;
        }
        case 9:
            modifybook();
            break;
        case 10:
            deletebook();
            break;
        case 11:
            return;
        default:
            cout << "Invalid choice";
    }
    adminmenu();
}

// ==================== BOOK FUNCTIONS ====================
void writebook() {
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do {
        system("clear || cls");
        bk.createbook();
        fp.write((char*)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record...(y/n?) ";
        cin >> ch;
    } while(ch == 'y' || ch == 'Y');
    fp.close();
}

void displayspb(char n[]) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.dat", ios::in);
    while(fp.read((char*)&bk, sizeof(book))) {
        if(strcasecmp(bk.retbno(), n) == 0) {
            bk.showbook();
            flag = 1;
        }
    }
    fp.close();
    if(flag == 0) {
        cout << "\n\nBook does not exist";
    }
    cin.ignore();
    cin.get();
}

void modifybook() {
    char n[6];
    int found = 0;
    system("clear || cls");
    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter the book no. ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while(fp.read((char*)&bk, sizeof(book)) && found == 0) {
        if(strcasecmp(bk.retbno(), n) == 0) {
            bk.showbook();
            cout << "\nEnter the new details of book";
            cin.ignore();
            bk.modifybook();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&bk, sizeof(book));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if(found == 0) {
        cout << "\n\nRecord Not Found";
    }
    cin.ignore();
    cin.get();
}

void deletebook() {
    char n[6];
    int flag = 0;
    system("clear || cls");
    cout << "\n\n\n\tDELETE BOOK...";
    cout << "\n\nEnter the Book no. : ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while(fp.read((char*)&bk, sizeof(book))) {
        if(strcasecmp(bk.retbno(), n) != 0) {
            fp2.write((char*)&bk, sizeof(book));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    if(flag == 1) {
        cout << "\n\n\tRecord Deleted...";
    } else {
        cout << "\n\nRecord not Found";
    }
    cin.ignore();
    cin.get();
}

void displayallb() {
    system("clear || cls");
    fp.open("book.dat", ios::in);
    if(!fp) {
        cout << "File Could Not Be Open";
        cin.get();
        return;
    }
    cout << "\n\n\t\tBook List\n\n";
    cout << "==================================================================\n";
    cout << "\tBook No." << setw(20) << "Book Name" << setw(25) << "Book Author\n";
    cout << "==================================================================\n";
    while(fp.read((char*)&bk, sizeof(book))) {
        bk.report();
    }
    fp.close();
    cin.ignore();
    cin.get();
}

// ==================== STUDENT FUNCTIONS ====================
void writestudent() {
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do {
        st.createstudent();
        fp.write((char*)&st, sizeof(student));
        cout << "\n\nDo you want to add more record...(y/n?) ";
        cin >> ch;
    } while(ch == 'y' || ch == 'Y');
    fp.close();
}

void displaysps(char n[]) {
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.dat", ios::in);
    while(fp.read((char*)&st, sizeof(student))) {
        if(strcasecmp(st.retadmno(), n) == 0) {
            st.showstudent();
            flag = 1;
        }
    }
    fp.close();
    if(flag == 0) {
        cout << "\n\nStudent does not exist";
    }
    cin.ignore();
    cin.get();
}

void modifystudent() {
    char n[6];
    int found = 0;
    system("clear || cls");
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the Admission no. ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while(fp.read((char*)&st, sizeof(student)) && found == 0) {
        if(strcasecmp(st.retadmno(), n) == 0) {
            st.showstudent();
            cout << "\nEnter the new details of student";
            cin.ignore();
            st.modifystudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(student));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if(found == 0) {
        cout << "\n\nRecord Not Found";
    }
    cin.ignore();
    cin.get();
}

void deletestudent() {
    char n[6];
    int flag = 0;
    system("clear || cls");
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter the Admission no. : ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while(fp.read((char*)&st, sizeof(student))) {
        if(strcasecmp(st.retadmno(), n) != 0) {
            fp2.write((char*)&st, sizeof(student));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if(flag == 1) {
        cout << "\n\n\tRecord Deleted..";
    } else {
        cout << "\n\nRecord not Found";
    }
    cin.ignore();
    cin.get();
}

void displayalls() {
    system("clear || cls");
    fp.open("student.dat", ios::in);
    if(!fp) {
        cout << "File Could Not Be Open";
        cin.get();
        return;
    }
    cout << "\n\n\t\tStudent List\n\n";
    cout << "==================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
    cout << "==================================================================\n";
    while(fp.read((char*)&st, sizeof(student))) {
        st.report();
    }
    fp.close();
    cin.ignore();
    cin.get();
}

// ==================== BOOK ISSUE/DEPOSIT FUNCTIONS ====================
void bookissue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    system("clear || cls");
    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter Admission no. ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    
    while(fp.read((char*)&st, sizeof(student)) && found == 0) {
        if(strcasecmp(st.retadmno(), sn) == 0) {
            found = 1;
            if(st.rettoken() == 0) {
                cout << "\n\n\tEnter The Book No. ";
                cin >> bn;
                while(fp1.read((char*)&bk, sizeof(book)) && flag == 0) {
                    if(strcasecmp(bk.retbno(), bn) == 0) {
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char*)&st, sizeof(student));
                        cout << "\n\n\tBook Issued Successfully\n\nPlease Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day";
                    }
                }
                if(flag == 0) {
                    cout << "Book No. Does Not Exist";
                }
            } else {
                cout << "You Have Not Returned The Last Book";
            }
        }
    }
    
    if(found == 0) {
        cout << "Student Record Not Exists...";
    }
    cin.ignore();
    cin.get();
    fp.close();
    fp1.close();
}

void bookdeposit() {
    char sn[6];
    int found = 0, flag = 0, day, fine;
    system("clear || cls");
    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter Admission no. Of Student ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    
    while(fp.read((char*)&st, sizeof(student)) && found == 0) {
        if(strcasecmp(st.retadmno(), sn) == 0) {
            found = 1;
            if(st.rettoken() == 1) {
                while(fp1.read((char*)&bk, sizeof(book)) && flag == 0) {
                    if(strcasecmp(bk.retbno(), st.retstbno()) == 0) {
                        flag = 1;
                        bk.showbook();
                        cout << "\n\nBook Deposited In No. Of Days ";
                        cin >> day;
                        if(day > 15) {
                            fine = (day - 15) * 1;
                            cout << "\n\nFine = " << fine;
                        }
                        st.resettoken();
                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char*)&st, sizeof(student));
                        cout << "\n\n\tBook Deposited Successfully";
                    }
                }
                if(flag == 0) {
                    cout << "Book No. Does Not Exist";
                }
            } else {
                cout << "No Book Issued";
            }
        }
    }
    
    if(found == 0) {
        cout << "Student Record Not Exists...";
    }
    cin.ignore();
    cin.get();
    fp.close();
    fp1.close();
}
// ==================== MAIN FUNCTION ====================
int main() {
    char ch;
    intro();
    
    do {
        system("clear || cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\n\t1 BOOK ISSUE";
        cout << "\n\n\n\t2 BOOK DEPOSIT";
        cout << "\n\n\n\t3 ADMINISTRATOR MENU";
        cout << "\n\n\n\t4 EXIT";
        cout << "\n\n\n\tPLEASE SELECT YOUR OPTION(1-4) ";
        cin >> ch;

        switch(ch) {
            case '1':
                bookissue();
                break;
            case '2':
                bookdeposit();
                break;
            case '3':
                adminmenu();
                break;
            case '4':
                exit(0);
                break;
            default:
                cout << "INVALID CHOICE";
        }
    } while(ch != '4');

    return 0;
}