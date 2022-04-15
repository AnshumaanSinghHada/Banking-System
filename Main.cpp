
/* ***************************
        Header Files
*************************** */

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>




using namespace std;
#define MIN_BALANCE 500
class InsufficientFunds{};



/* ***************************
        Class Account
*************************** */



class Account
{
private:
 long accountNumber;
 string firstName;
 string lastName;
 float balance;
 static long NextAccountNumber;


public:
 Account(){}

 Account(string fname,string lname,float balance)
 {
    NextAccountNumber++;
    accountNumber=NextAccountNumber;
    firstName=fname;
    lastName=lname;
    this->balance=balance;
 }

 long getAccNo()
 {
     return accountNumber;
 }

 string getFirstName()
 {
     return firstName;
 }

 string getLastName()
 {
     return lastName;
 }

 float getBalance()
 {
     return balance;
 }

 void Deposit(float amount)
 {
     balance+=amount;
 }

 void Withdraw(float amount)
 {
    if(balance-amount<MIN_BALANCE)
    throw InsufficientFunds();
    balance-=amount;
}

 static void setLastAccountNumber(long accountNumber)
 {
      NextAccountNumber=accountNumber;
 }
 static long getLastAccountNumber()
 {
     return NextAccountNumber;
 }

 /* ***************************
     Operator Overloading
*************************** */


 friend ofstream & operator<<(ofstream &ofs,Account &acc)
 {
    ofs<<acc.accountNumber<<endl;
    ofs<<acc.firstName<<endl;
    ofs<<acc.lastName<<endl;
    ofs<<acc.balance<<endl;
    return ofs;
 }
 friend ifstream & operator>>(ifstream &ifs,Account &acc)
 {
     ifs>>acc.accountNumber;
     ifs>>acc.firstName;
     ifs>>acc.lastName;
     ifs>>acc.balance;
     return ifs;
 }
 friend ostream & operator<<(ostream &os,Account &acc)
 {
    os<<"First Name:"<<acc.getFirstName()<<endl;
    os<<"Last Name:"<<acc.getLastName()<<endl;
    os<<"Account Number:"<<acc.getAccNo()<<endl;
    os<<"Balance:"<<acc.getBalance()<<endl;
 return os;
 }
};
long Account::NextAccountNumber=0;



/* ***************************
        Class Bank
*************************** */




class Bank
{
private:
 map<long,Account> accounts;
public:
 Bank()
 {

 Account account;
 ifstream infile;
 infile.open("Bank.data");
 if(!infile)
 {
 //cout<<"Error in Opening! File Not Found!!"<<endl;
 return;
 }
 while(!infile.eof())
 {
 infile>>account;
 accounts.insert(pair<long,Account>(account.getAccNo(),account));
 }
 Account::setLastAccountNumber(account.getAccNo());

 infile.close();

}


 Account OpenAccount(string fname,string lname,float balance)
 {
 ofstream outfile;
 Account account(fname,lname,balance);
 accounts.insert(pair<long,Account>(account.getAccNo(),account));

 outfile.open("Bank.data", ios::trunc);

 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
 return account;
}


 Account BalanceEnquiry(long accountNumber)
 {
 map<long,Account>::iterator itr=accounts.find(accountNumber);
 return itr->second;
}


 Account Deposit(long accountNumber,float amount)
 {
 map<long,Account>::iterator itr=accounts.find(accountNumber);
 itr->second.Deposit(amount);
 return itr->second;
}


 Account Withdraw(long accountNumber,float amount)
 {
 map<long,Account>::iterator itr=accounts.find(accountNumber);
 itr->second.Withdraw(amount);
 return itr->second;
}


 void CloseAccount(long accountNumber)
 {
 map<long,Account>::iterator itr=accounts.find(accountNumber);
 cout<<"Account Deleted"<<endl<<itr->second;
 accounts.erase(accountNumber);
}


 void ShowAllAccounts()
 {
 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
 }
}

 ~Bank()
 {
 ofstream outfile;
 outfile.open("Bank.data", ios::trunc);

 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
}
};




/* ***************************
        Main Function
*************************** */





int main()
{
 Bank b;
 Account acc;

 int choice;
 string fname,lname;
 long accountNumber;
 float balance;
 float amount;
 cout<<"================================================================================"<<endl;

cout<<"\t\t           Welcome To Banking System Project            "<<endl;

cout<<"\t\t                  Coded By:                           "<<endl;

cout<<"\t\t         ####  Anshumaan Singh Hada  ####               "<<endl;

cout<<"================================================================================\n";
cout<<endl;
cout<<endl;
 do
 {
 cout<<"\t\t*******************************************"<<endl;

cout<<"\t\t                 Main Menu                 "<<endl;

cout<<"\t\t*******************************************"<<endl;

cout<<"\t\t*           1 - Open an Account           *"<<endl;

cout<<"\t\t*           2 - Balance Enquiry           *"<<endl;

cout<<"\t\t*           3 - Deposit Funds             *"<<endl;

cout<<"\t\t*           4 - Withdrawal Funds          *"<<endl;

cout<<"\t\t*           5 - Close an Account          *"<<endl;

cout<<"\t\t*           6 - Show All Accounts         *"<<endl;

cout<<"\t\t*           7 - Quit                      *"<<endl;

cout<<"\t\t*******************************************"<<endl;

cout<<endl;

cout<<"\t\t*******************************************"<<endl;cout<<"\n";
cout<<"\t\t            Enter Option: ";
cin>>choice;
 switch(choice)
 {
 case 1:
 cout<<"Enter First Name: ";
cin>>fname;
cout<<"Enter Last Name: ";
cin>>lname;
cout<<"Enter initial Balance: ";
cin>>balance;
 acc=b.OpenAccount(fname,lname,balance);
 cout<<endl<<"CONGRATULATIONS "<<fname<<"! ACCOUNT IS CREATED"<<endl;
 cout<<acc;
break;
 case 2:
 cout<<"Enter Account Number:";
cin>>accountNumber;
 acc=b.BalanceEnquiry(accountNumber);
 cout<<endl<<"Your Account Details"<<endl;
 cout<<acc;
break;
 case 3:
 cout<<"Enter Account Number:";
cin>>accountNumber;
cout<<"Enter Amount:";
cin>>amount;
 acc=b.Deposit(accountNumber, amount);
 cout<<endl<<"Amount is Deposited"<<endl;
 cout<<acc;
break;
 case 4:
 cout<<"Enter Account Number:";
cin>>accountNumber;
cout<<"Enter Amount:";
cin>>amount;
 acc=b.Withdraw(accountNumber, amount);
 cout<<endl<<"Amount Withdrawn"<<endl;
 cout<<acc;
break;
 case 5:
 cout<<"Enter Account Number:";
cin>>accountNumber;
 b.CloseAccount(accountNumber);
 cout<<endl<<"Account is Closed"<<endl;
 case 6:
 b.ShowAllAccounts();
 break;
 case 7: break;
 default:
 cout<<"\nEnter correct choice";
exit(0);
 }
 }while(choice!=7);

 return 0;
}


