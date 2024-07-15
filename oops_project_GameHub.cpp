#include<bits/stdc++.h>
#include <conio.h>  // to accept Esc button and Enter button
#include <unistd.h> // For sleep function
#include <random>// to generate random function

using namespace std;


class ErrorHandler
{
      public:
      int errcode;
      string errmsg;

      ErrorHandler(int code,string msg)
      {
           errcode=code;
           errmsg=msg;
      }
} ;

class BankAccount {
protected:
    long long acc_number;
    double balance;
    
public:
   

    BankAccount(long long accno,double initialBalance = 0.0) : balance(initialBalance),acc_number(accno) {}

    double getBalance()  {
        return balance;
    }

    void credit(double amount) {
        balance += amount;
    }

    virtual void debit(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            throw ErrorHandler(69,"                                          Insufficient balance!");
        }
    }
};


class Owner
{
     public:
     static double currbalance;
     static double initbalance;

     static BankAccount account;
     
   

    static double ownergetBalance()  {
        //return currbalance;
         return account.getBalance();

    }

   static void ownercredit(double amount) {
        //currbalance += amount;
        account.credit(amount);
    }

    static void ownerdebit(double amount) {
        // if (amount <= currbalance) {
        //     currbalance -= amount;
        // } else {
        //     throw ErrorHandler(69,"Insufficient Owner's funds!");
        // }
        account.debit(amount);
    }
    static double getprofit()
    {
         return (account.getBalance()-initbalance);
    }
};


class Statistics
{
     public:
     map<string,double> stats;

     Statistics(string g1,string g2,string g3,string g4,string g5,string g6)
     {
         stats[g1]=0;
         stats[g2]=0;
         stats[g3]=0;
         stats[g4]=0;
         stats[g5]=0;
         stats[g6]=0;
         
     }

     void dispstats(double tot_waged)
     {


        int count=0;
        cout<<"Player's  Statisitics             Total Waged : "<<tot_waged<<endl;
        cout<<"  --------------------------------------------\n";
        cout<<"  |       GAME          |        PROFIT      |\n";
        cout<<"  --------------------------------------------\n";
       
         for(auto i : stats)
         {
            count++;

            cout<<count<<"   "<<i.first;
            for(int p=1;p<=20-i.first.length();p++)
            {
                cout<<" ";
            }
            
              cout<<"|  "<<i.second<<endl;
         }
     }
     void addstats(string g,double amt)
     {
        stats[g]=stats[g]+amt;    
     }
     double totalprof()
     {
        double curr=0;
         for(auto i :stats)
         {
                 curr+=i.second;
         }
         return curr;
     }
};


class BonusRewards
{
    private:
    double wagedmoney;
    vector<bool>v; /// size of four bonuses 250,500,1000,5000

    public:
    BonusRewards() :   wagedmoney(0.0) ,v(4,false){}

    void addwagedmoney(double amt)
    {
        wagedmoney+=amt;
    }

    bool checkbonus()
    {
         if(wagedmoney>=250 && v[0]==false)
         {
            return true;
         }
          if(wagedmoney>=500.0 && v[1]==false)
         {
            return true;
         }
          if(wagedmoney>=1000.0 && v[2]==false)
         {
            return true;
         }
          if(wagedmoney>=5000 && v[3]==false)
         {
            return true;
         }
         return false;
    }
    double claimbonus()
    {
         double bonus=0.0;
         if(wagedmoney>=250 && v[0]==false)
         {
             bonus+=100;
            

             cout<<"      Claimed Bonus 100 !!\n";
             v[0]=true;
         }
         if(wagedmoney>=500 && v[1]==false)
         {
             bonus+=200;
              
             cout<<"      Claimed Bonus 200 !!\n";
             v[1]=true;
         }
         if(wagedmoney>=1000 && v[2]==false)
         {
             bonus+=400;
              
             cout<<"      Claimed Bonus 400 !!\n";
             v[2]=true;
         }
         if(wagedmoney>=5000 && v[3]==false)
         {
             bonus+=800;
             cout<<"      Claimed Bonus 800 !!\n";
             v[3]=true;
         }
         return bonus;

    }
    double total_waged()
    {
       return wagedmoney;
    }
};

class User {
private:
    string username;
    BankAccount account;
    Statistics userstat;
    BonusRewards userbonus;
    
public:
    User(string name,long long accno, double initialBalance = 0.0) : username(name), account(accno,initialBalance),userstat("Mines","Cards","Slots","HorseGambling","Rock_Paper_Scissor","Dice"),userbonus() {}

    string getUsername() const {
        return username;
    }

    double getBalance()  {
        return account.getBalance();
    }

    void credit(double amount) {
        account.credit(amount);
    }

    void debit(double amount) {
        account.debit(amount);
    }

    void add_to_stat(string g,double amt)
    {
         userstat.addstats(g,amt);
    }
    void display_stats()
    {
        userstat.dispstats(userbonus.total_waged());
    }
    void addwagedmoney(double amt)
    {
        userbonus.addwagedmoney(amt);
    }
    bool checkbonus()
    {
        return userbonus.checkbonus();
    }
    void claimbonus()
    {
        
        
         credit(userbonus.claimbonus());
         try
        {
            Owner::ownerdebit(userbonus.claimbonus());
        }
        catch(ErrorHandler E)
        {
            cout<<E.errmsg<<endl;
            account.debit(userbonus.claimbonus());
        }
         
         
    }
    double total_prof()
    {
       return  userstat.totalprof();
    }
    
};
class LeadersBoard
{ 
    public:
    vector<pair<double,string>> v;
 
                  // assuming 10 users
    

    void add_to_table(string n,double p)
    {
        if(v.size()==0)
        {
             v.push_back({p,n});
             return;
        }
         for(int i=0;i<v.size();i++)
         {
             if(n == v[i].second)
             {
                 v[i].first+=p;
                 return;
             }
         }
        
             v.push_back({p,n});
    }
    void view_leadersboard()
    {
        int ct=0;
        sort(v.begin(),v.end());
        cout<<"------------------------------------------------------\n";
        cout<<"  Rank |           Name           |     Profit      \n";
        cout<<"------------------------------------------------------\n";
     
            for(int i=v.size()-1;i>=0;i--)
         {

         
            ct++;
            cout<<"  "<<ct<<"    | ";cout<<v[i].second;
            for(int q=0;q<=24-v[i].second.length();q++)
            {cout<<" ";}
            cout<<"| "<<v[i].first<<endl;
            
         }
    }


};



class Game {
    public:


    virtual void play(User* user) = 0;
    
    double chance_of_winning(double fav,double total)
    {
        return (fav/total)*100;        
    }



};

class MinesGame : public Game {
public:
 char tile[3][3];
 char curtile[3][3];

 
 void setupmines()
 {
      for(int i=0;i<3;i++)
      {
         for(int j=0;j<3;j++)
         {
             tile[i][j]='*';
         }
      }
      int c=0;
      for(int i=0;i<3;i++)
      {
         for(int j=0;j<3;j++)
         {
             c++;
             curtile[i][j]=48 + c;
         }
      }
 }
    void play(User* user)  {
        cout<<"                                                     Mines\n";

        cout<<"                                                                                       Chance of winning : "<<chance_of_winning(7,9)<<" %"<<endl<<endl;
         setupmines();

      map<int,pair<int,int>> m;

      m[1].first=0;
      m[1].second=0;
       m[2].first=0;
      m[2].second=1;
       m[3].first=0;
      m[3].second=2;
       m[4].first=1;
      m[4].second=0;
       m[5].first=1;
      m[5].second=1;
       m[6].first=1;
      m[6].second=2;
       m[7].first=2;
      m[7].second=0;
       m[8].first=2;
      m[8].second=1;
       m[9].first=2;
      m[9].second=2;



      srand(time(NULL));
    
    // Generate random number 1
    int bomb1 = rand() % 9 + 1;
    int bomb2;
    
    // Generate random number 2 until it's different from number 1
    do {
        bomb2 = rand() % 9 + 1;
    } while (bomb2 == bomb1);

    int ind1,ind2;
    ind1=m[bomb1].first;
    ind2=m[bomb1].second;

    tile[ind1][ind2]='!';

    ind1=m[bomb2].first;
    ind2=m[bomb2].second;

    tile[ind1][ind2]='!';


    vector<bool> v(9,false);

        
 
       cout<<"                                                 -------------\n";
       for(int i=0;i<3;i++)
      {
         
          cout<<"                                                 |";
         for(int j=0;j<3;j++)
         {
             cout<<" "<<curtile[i][j]<<" |";
         }
         cout<<endl;
         cout<<"                                                 -------------\n";    
      }
      int ch;
   
    double minesbet;
    double minesprofit=0.0;
    double curramt;
     cout<<"Place bet :  ";cin>>minesbet;
        curramt=minesbet;
        int x=0;
     try
     {  user->debit(minesbet);  
     }
     catch(ErrorHandler E)
     {
         cout<<E.errmsg<<endl;
         x=E.errcode;      
     }
     
    if(x==0)
   { 

               
               Owner::ownercredit(minesbet);
               user->addwagedmoney(minesbet);
  
    while(1)
    {
        
        minesprofit=curramt-minesbet;
        cout<<endl;
        cout<<"CurrentProfit : "<<minesprofit<<endl;
        cout<<"Press -1 ---> cash out \n";  

      
        
        cout<<"                     Enter which tile to pick : ";
         cin>>ch;       
         cout<<endl;
        
       
        
        if(ch==-1)
        {
            break;
        }
        
          if((ch<=0) || (ch) >9)
        {
             cout<<"Invalid Tile choosen\n";
             continue;
        }


       
        if(v[ch]==true)
        {
             cout<<"Tile already choosen\n";
        }
        else
      {  
        int p=0;
        if(tile[m[ch].first][m[ch].second] == '!')
        {
             p=1;
             curtile[m[ch].first][m[ch].second]='!';
             cout<<"You have choosen a bomb !!                       ";
             cout<<"-------------\n";
       for(int i=0;i<3;i++)
      {
         
          cout<<"                                                 |";
         for(int j=0;j<3;j++)
         {
             cout<<" "<<tile[i][j]<<" |";
         }
         cout<<endl;
         cout<<"                                                 -------------\n";    
      }
        
         

         cout<<"-------------------------------------------------    Game  over    ----------------------------------------------\n";

           curramt=0;

           break;
        }
        else
        {
             curtile[m[ch].first][m[ch].second]='*';
             cout<<"You have choosen a Diamond '*'\n";

             curramt=1.5 * curramt;
              
             v[ch]=true;
 
      
        }

      cout<<"                                -------------\n";
       for(int i=0;i<3;i++)
      {
         
          cout<<"                                |";
         for(int j=0;j<3;j++)
         {
             cout<<" "<<curtile[i][j]<<" |";
         }
         cout<<endl;
         cout<<"                                -------------\n";    
      }
      }
    
    }
      minesprofit=curramt-minesbet;
    cout<<"Bet placed  : "<<minesbet<<"    TotalProfit : "<<minesprofit<<endl;

    
         user->add_to_stat("Mines",minesprofit);
         user->credit(curramt);

         try
        {  Owner::ownerdebit(curramt);
        }
        catch(ErrorHandler E)
        {
             cout<<E.errmsg<<endl;
        }

    }
    }
};

class Cards : public Game {
public:
 vector<string> suit;
 vector<int> rank;

vector<pair<int, string>> createDeck() {
    vector<pair<int, string>> deck;
    vector<string> suit = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<int> rank = {2,3,4,5,6,7,8,9,10,11,12,13,14};

    for (int i = 0; i < suit.size(); i++) {
        for (int j = 0; j < rank.size(); j++) {
            deck.push_back(make_pair(rank[j], suit[i]));
        }
    }

    return deck;
}

      
     void play(User* user)  {

        cout<<"                                        CARDS GAME\n";
        



        double cardsbet;
        double curramt;
       vector<pair<int, string>> deck = createDeck();
    srand(static_cast<unsigned int>(time(0))); // Use current time as seed for random generator
    random_shuffle(deck.begin(), deck.end());
    int c = 0;

    char ch;
    char choice;
    int p = 1;
    pair<int, string> currcard = deck[0];



    cout<<"                                        Place  Bet  :  ";cin>>cardsbet;cout<<endl;
    int x=0;
    try
     {  user->debit(cardsbet);  
     }
     catch(ErrorHandler E)
     {
         cout<<E.errmsg<<endl;
         x=E.errcode;      
     }
    curramt=cardsbet;
    // Draw cards from the deck until it is empty

    if(x==0)
    {
          Owner::ownercredit(cardsbet);
               user->addwagedmoney(cardsbet);


        while (p != deck.size()) {
        // Draw the top card
        pair<int, string> nextcard;

            nextcard = deck[p];
            p++;

            map<int,char> face;
            face[11]='J';
            face[12]='Q';
            face[13]='K';
            face[14]='A';
            face[1]='A';

           
            cout<<"                                    CURRENT CARD    \n";
            cout<<"                               +-------------------+\n";
            if(currcard.first>10)
            {
                cout<<"                               | "<<face[currcard.first]<<"                 |\n";
            }
            else if(currcard.first==10)
            {
                        cout<<"                               | "<<currcard.first<<"                |\n";
            }
            else
            {
                 cout<<"                               | "<<currcard.first<<"                 |\n";
            }
            cout<<"                               |                   |\n";
            cout<<"                               |                   |                       "; cout << "----------------------------------------\n";

            
            
             cout<<"                               |         "<<currcard.second[0]<<"         |                       ";cout << "|   H ----> Higher  or   L ----> Lower |\n";
            cout<<"                               |                   |                       |     Curramt :  "<<curramt<<"               |\n"; 
            cout<<"                               |                   |                       ----------------------------------------\n";
            cout<<"                               |                   |                                       |\n";
             if(currcard.first>10)
            cout<<"                               |                 "<<face[currcard.first]<<" |                                       |\n";
             else if(currcard.first==10)
            {
                        cout<<"                               |                "<<currcard.first<<" |                                       |\n";
            }
            else
            {
                cout<<"                               |                 "<<currcard.first<<" |                                       |\n";
            }

            cout<<"                               +-------------------+                                       |\n";

            if(currcard.first > 10)
            cout<<"                                     "<<face[currcard.first];
            else
            cout<<"                                  "<<currcard.first;
            cout<< " of " << currcard.second <<"                              Guess the next Card : ";cin >> choice;"\n";
            while(1)
           { if(choice !='H' && choice!='L')
            {
                cout<<"Invalid choice\n";
                 cout<<"                                                                Guess the next Card : ";cin>>choice;"\n";
            }
            else 
            {
                     break;
            }
           } 
           
           
            cout<<"######################################################################################\n";
            cout << "\nNext card is ------>  ";
            if(nextcard.first >10)
                cout<<face[nextcard.first];
                else
                cout <<nextcard.first;
                cout<<" of " << nextcard.second << endl;
            cout<<"######################################################################################\n";


           if ((currcard.first == nextcard.first) || currcard.first == 14 || currcard.first == 1 || nextcard.first ==14 || nextcard.first==1) {
                cout << "Bet x 1\n";
                curramt=curramt*1.0;
                 cout<<"######################################################################################\n";
            }

            else if ((choice == 'H' && currcard.first < nextcard.first) || (choice == 'L' && currcard.first > nextcard.first)) {
               curramt=curramt*1.25;
                cout << "You won                           Curramt :  "<<curramt<<"\n";
                
                cout<<"######################################################################################\n";
            }  else {
                cout << "You Lost\n";
                curramt=0.0;
                break;
                 cout<<"######################################################################################\n";
            }
            currcard = nextcard;
        
        
        cout << "\nEsc ---> Cash out\n";
        cout<<"Press any key to Continue\n";
        cout<<endl;
        ch =_getch();
        if (ch==27) {
            break;
        }
    }                                              
    cout<<"                                         YOU Won :  "<<curramt<<"\n";
     user->credit(curramt);

    

     user->add_to_stat("Cards",curramt-cardsbet);
       try
        {  Owner::ownerdebit(curramt);
        }
        catch(ErrorHandler E)
        {
             cout<<E.errmsg<<endl;
             user->debit(curramt);
        }

    }
    }
};

class Slots : public Game {
public:
    void play(User* user) override {
     cout<<"                                                SLOTS\n";
      cout<<"                                                                                       Chance of winning : "<<chance_of_winning(280,1000)<<" %"<<endl<<endl;
    

     
        char ch;

        double Slotsbet;
        double curramt;
        double Slotsprofit=0.0;

        
        int x=0;

       char ch2;
      while(1)
    {  
        cout<<"Esc ---> exit from Slots\n";
        cout<<"Press Enter to contiue Slots\n";

         ch=_getch();

         if(ch==27)
         {
             break;
         }
        cout<<endl;
        cout<<"Place Bet : ";cin>>Slotsbet;
        curramt=Slotsbet;
        x=0;

        try
        {
            user->debit(Slotsbet);
        }
        catch(ErrorHandler E)
        {
            cout<<E.errmsg<<endl;
            x=E.errcode;

        }
        if(x!=0)
        {
             break;
        }

                     Owner::ownercredit(Slotsbet);
               user->addwagedmoney(Slotsbet);

        cout<<"                                            Enter any key to spin : ";
         ch=_getch();
         cout<<endl;
        

         srand(time(NULL));

      int n1=rand() % 6;
      int n2=rand() % 6;
      int n3=rand() % 6;

      cout<<"                                            -------------------\n";
      cout<<"                                            |  "<<n1<<"  |  "<<n2<<"  |  "<<n3<<"  |\n"; 
      cout<<"                                            -------------------\n";


        if(n1==n2 && n3==n1 && n2==n3)
      {
          
           cout<<"                                               You Won\n";
           curramt=Slotsbet*5;
      }
      else if(n1==n2 || n2==n3 || n1==n3)
      {

         cout<<"                                               Bet x 1.5\n";
         curramt=Slotsbet*1.5;
      }
      else
      {

           cout<<"                                               You Lost\n";
           curramt=0;
      }
      Slotsprofit=curramt-Slotsbet;
      cout<<"                                  Bet Placed : "<<Slotsbet<<"      SlotsProfit : "<<Slotsprofit<<endl;
       cout<<"------------------------------------------------------------------------------------------------------------\n";
      user->add_to_stat("Slots",Slotsprofit);
      user->credit(curramt);
       try
        {  Owner::ownerdebit(curramt);
        }
        catch(ErrorHandler E)
        {
             cout<<E.errmsg<<endl;
        }
    


 }
    }
};

class Rock_paper_scissor :public Game
{
     public:
     int generateRandomNumber() 
     {
            return rand() % 3 + 1; // Generates a random number between 1 and 3   
    }

    void play(User* user) override
    {

       cout<<"                                                           Rock Paper Scissor\n";
       cout<<"                                                                                       Chance of winning : "<<chance_of_winning(1,3)<<" %"<<endl<<endl;

          srand(time(0)); // Seed the random number generator

     // Rename 'rand' variable to avoid conflict

    map<int,string> m;

    m[1]="ROCK";
    m[2]="PAPER";
    m[3]="SCISSOR";
    int ch = 0; 

    while(ch != -1) {
        for(auto i : m) {
            cout<<i.first<<" ----> ";
            cout<<i.second<<endl;
        }
        cout<<"-1 ----> Exit\n";

        cout<<"Select Your choice\n";

        cin>>ch;

        if(ch==-1)
        {
            break;
        }
        if((ch<0 || ch>3) && ch!=-1)
        {
             cout<<"Invalid Choice\n";
             return;
        }

        double SPSbet;
        cout<<"Place Bet : ";cin>>SPSbet;cout<<endl;
         int x=0;
        try
        {
              user->debit(SPSbet);
              
        }
        catch(ErrorHandler E)
        {
             cout<<E.errmsg<<endl;
             x=E.errcode;
        }


        if(x==0)
      {  
         Owner::ownerdebit(SPSbet);
         
               user->addwagedmoney(SPSbet);
        
        
        int res=0;
        int random = generateRandomNumber();
         

        cout<<"                                             You : "<<m[ch]<<"  X    PC: "<< m[random]<<endl;
        
        if((ch==1 && random ==3) || (ch==2 && random ==1) ||( ch==3 && random==2)) {
               res=1;
        }
        else if(ch==random) {
             res=0;
        }
        else {
             res=-1;
        }

      
        if(res==1) {
             cout<<"                                  ***********   You Won *******\n";
             double SPSprofit = 3.0*SPSbet-SPSbet;
             user->credit(3.0*SPSbet);
             user->add_to_stat("Rock_Paper_Scissor",SPSprofit);
             Owner::ownerdebit(3.0*SPSbet);
        }
        else if(res==0) {
             cout<<"                                    ######      Tie      ######\n";
             user->credit(SPSbet);
        }
        else {
             cout<<"                                  *******      You Lost       ********\n";
             user->add_to_stat("Rock_Paper_Scissor",(SPSbet*-1.0));
        }
    }
    }
    }
       

};
class Horse : public Game
{
      public:
   

      void play(User* user)
      { 
      cout<<"                                       HORSE GAMBLING\n";  
      cout<<"                                                                                       Chance of winning : "<<chance_of_winning(1,4)<<" %"<<endl<<endl;


           int H;
          cout<<"                                   Select Your Horse\n";
          cout<<"                                   Press 1  -----> H1\n";
          cout<<"                                   Press 2  -----> H2\n";
          cout<<"                                   Press 3  -----> H3\n";
          cout<<"                                   Press 4  -----> H4\n";
          cout<<endl;

          double horsebet;
          int x=0;
          cout<<"Horse : ";cin>>H;
          cout<<endl;
          if(H<=0 || H>4)
          {
              cout<<"Invalid Horse choosen\n";
          }


          else
        { 
          cout<<"Place Bet  : ";cin>>horsebet;

          try
          {
              user->debit(horsebet);
          }
          catch(ErrorHandler E)
          {
              cout<<E.errmsg<<endl;
              x=E.errcode;
          }
          
          
          if(x==0)
       { 
                           Owner::ownercredit(horsebet);
                           
               user->addwagedmoney(horsebet);

           // produce 4 unique radnom numbers 1 to 4
        srand(static_cast<unsigned int>(time(0)));

  
    vector<int> numbers = {1, 2, 3, 4};

   
       random_shuffle(numbers.begin(), numbers.end());

           int distance = 30; 
    int steps = 10; 

   
    int speedC1 = numbers[0]; // Speed of Horse 1 (C1)
    int speedC2 = numbers[1]; // Speed of Horse 2 (C2)
    int speedC3 = numbers[2]; // Speed of Horse3 (C3)
    int speedC4 = numbers[3]; // Speed of Horse4 (C4)

    bool horseend = false; // Flag to track if any Horse reached the end

    for (int i = 0; !horseend; ++i) { // Continue until any horse reaches the end
        clearScreen(); // Clear the screen before drawing the next frame
        cout<<"###################      Your horse :  H"<<H<<"      ###################";
        cout << endl << endl;
        cout << "  Start   :  ";
        for (int j = 0; j < distance; ++j) {
            if (j == 0)
                cout << "| "; // display1 start marker
            else if (j == distance - 1)
                cout << "| "; // display1 end marker
            else if (j == i * speedC1 && j < distance - 1) { // Check for position of C1
                cout << "H1 "; // Print the horse at its current position
                if (j >= distance - 2) // Check if C1 reaches the end
                    horseend = true;
            }
            else
                cout << "   ";
        }
        cout << endl;

        cout << "  Start   :  ";
        for (int j = 0; j < distance; ++j) {
            if (j == 0)
                cout << "| "; // display1 start marker
            else if (j == distance - 1)
                cout << "| "; // display1 end marker
            else if (j == i * speedC2 && j < distance - 1) { // Check for position of C2
                cout << "H2 "; // Print the horse at its current position
                if (j >= distance - 2) // Check if C2 reaches the end
                    horseend = true;
            }
            else
                cout << "   ";
        }
        cout << endl;

        cout << "  Start   :  ";
        for (int j = 0; j < distance; ++j) {
            if (j == 0)
                cout << "| "; // display1 start marker
            else if (j == distance - 1)
                cout << "| "; // display1 end marker
            else if (j == i * speedC3 && j < distance - 1) { // Check for position of C3
                cout << "H3 "; // Print the horse at its current position
                if (j >= distance - 2) // Check if C3 reaches the end
                    horseend = true;
            }
            else
                cout << "   ";
        }
        cout << endl;


        cout << "  Start   :  ";
        for (int j = 0; j < distance; ++j) {
            if (j == 0)
                cout << "| "; // display1 start marker
            else if (j == distance - 1)
                cout << "| "; // display1 end marker
            else if (j == i * speedC4 && j < distance - 1) { // Check for position of C2
                cout << "H4 "; // Print the horse at its current position
                if (j >= distance - 2) // Check if C2 reaches the end
                    horseend = true;
            }
            else
                cout << "   ";
        }
        cout << endl;

        // Add some delay between frames for smoother animation
        usleep(600000); // 900 milliseconds
    }
    int max=numbers[0];
       int p=0;
    for(int i=0;i<numbers.size();i++)
    {
      if(numbers[i]>max)
      {
           max=numbers[i];
           p=i;
      }
    }
    cout<<"\n###################      H"<<p+1<<" won the Race !!      ###################"<<endl;

    if(H == p+1)
    {
        cout<<"### Your Horse Won the Race !! ###\n";
        cout<<endl;
        cout<<"You Won "<<4*horsebet<<endl;
        double horseprofit=4.0*horsebet-horsebet;
        user->credit(4.0*horsebet);
     
        user->add_to_stat("HorseGambling",horseprofit);

         try
        {  Owner::ownerdebit(4.0*horsebet);
        }
        catch(ErrorHandler E)
        {
             cout<<E.errmsg<<endl;
        }
    }
    else
    {
      cout<<"\n*****************       You Lost the Bet       *****************\n";
      user->add_to_stat("HorseGambling",-1*horsebet);
    }
       }
    
        }
      }
      void clearScreen() {
    // Clear the screen (works on Unix-like systems)
    cout << "\033[2J\033[1;1H";
        }
};

class Dice : public Game
{
     public:

     void play(User* user)
     {


        cout<<"                                            DICE GAME \n";
        cout<<"                                                                           Chance of winning : "<<chance_of_winning(5.5,12)<<" %"<<endl<<endl;


         srand(time(NULL));

         
 
        double dicebet;
        double curramt;
        int x=0;

        cout<<"Place Bet  : ";cin>>dicebet;cout<<endl;
        try{
            user->debit(dicebet);
        }
        catch(ErrorHandler E)
        {
             cout<<E.errmsg<<endl;
             x=E.errcode;
        }

      string ch;
       if(x==0)
   {
        curramt=dicebet;
               Owner::ownercredit(dicebet);
               user->addwagedmoney(dicebet);
                    
    
    while(1)
      {     
         cout<<"Esc ----->  Cashout\n";
         cout<<"Current amount : "<<curramt<<endl<<endl;;

            int D1=rand()%6 + 1;
         int D2 = rand()%6 +1;

         int sum=D1 + D2;
       
        cout<<" H ---> Higher than 7 \n";
        cout<<" L ---> Lower than 7                 ";cout<<" Enter : ";
         cin>>ch;
         cout<<endl;
         if(ch=="-1")
        {
             break;
        }
        if(ch!="H" && ch!="L" && ch!="-1")
        {
            cout<<"Invalid Choice\n";
            continue;
        }

         cout<<endl;

         cout<<"                                          ---                ---\n";
         cout<<"                                         | "<<D1<<" |      +       | "<<D2<<" |    =  "<<D1+D2<<"\n";
         cout<<"                                          ---                ---\n";
        
         if((ch=="H" && sum>7) || (ch=="L" && sum<7))
        {
            cout<<"                                                  You won\n";
            curramt=curramt*1.5;

        }
        else if(sum==7)
        {
            cout<<"                                                  bet 1x\n";
            curramt=curramt*1.0;
        }
       
        else 
        {
            curramt=curramt*0.0;
             cout<<"                                                  You lost\n";
             user->add_to_stat("Dice",dicebet*-1);
             return;
        }
      }

      cout<<"You   won   ---->  "<<curramt<<endl;

     

      
       user->credit(curramt);
      user->add_to_stat("Dice",curramt-dicebet);


      try
      { 
          Owner::ownerdebit(curramt);
      }
      catch(ErrorHandler E)
      {
          cout<<E.errmsg<<endl;
          user->debit(curramt-dicebet);
          return;
      }


   }

     }

};

class Snake_and_Ladder : public Game
{
     public:

     void play(User* user)
     {

        cout<<"                                            Snake and Ladders \n\n";

        int ch;
        cout<<"1 ---> Single Player\n";
        cout<<"2 ---> Two Player\n";
        cout<<"-1 ---> Exit\n";
        cout<<"\n Enter : ";
        cin>>ch;
        cout<<endl;

        if(ch==1)
        {
             play1();
        }
        else if(ch==2)
        {
            play2();
        }


     }

void clearScreen() {
    // Clear the screen (works on Unix-like systems)
    cout << "\033[2J\033[1;1H";
}
void snakes_and_ladders()
{
      cout<<"##### Ladder at 2 to 6 #####\n";
    cout<<"##### Ladder at 8 to 11 #####\n";
    cout<<endl;

    cout<<"?~~~~ Snake at 9 to 1 ?~~~~~\n";
    cout<<"?~~~~ Snake at 12 to 3 ?~~~~\n";
    cout<<endl;

    cout<<"ESC ---->  Exit\n";
  
}
     void display1(int each, int a[][4]) {
    for (int i = 0; i < 4; i++) {
        cout << "                                       ---------------------------------------------\n";
        cout << "                                       |   ";
        for (int j = 0; j < 4; j++) {
            if (a[i][j] == each) {
                cout << "(o_o)";
                cout << "  |   ";
            } else if (a[i][j] / 10 == 0)
                cout << a[i][j] << "      |   ";
            else
                cout << a[i][j] << "     |   ";
        }
        cout << endl;
    }
    cout << "                                       ---------------------------------------------\n";
}

     void play1()
     {

        int x[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    char f, l;
      


    int a[4][4];
    int pos = 0, i, j, dice, prevpos;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            a[i][j] = x[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        cout << "                                       ---------------------------------------------\n";
        cout << "                                       |   ";
        for (int j = 0; j < 4; j++) {
           if (a[i][j] / 10 == 0)
                cout << a[i][j] << "      |   ";
            else
                cout << a[i][j] << "     |   ";
        }
        cout << endl;
    }
    cout << "                                       ---------------------------------------------\n";
    bool S=false;
    bool L=false;
    
    while (pos <= 16) {
        cout << "\nPress any key to roll Dice\n";
        f=_getch();
        if(f==27)
        {
            goto end;
        }
        srand(time(0)); // seed the random number generator with the current time
        // roll the dice and print the result
        dice = rand() % 6 + 1;
        

        pos = pos + dice;
        prevpos = pos - dice;


         
        

        if (pos <= 16) 
        {

                 // COMMON  JUMP


           for (int dd = prevpos; dd <= pos; dd++)
            {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();


                cout<<"               ---\n";
                cout <<"You rolled a  | "<< dice <<" |\n";
                cout<<"               ---\n";
                display1(dd, a);
                usleep(900000); // Adjust the delay as needed
            }
            S=false;
            L=false;
            if (pos == 2) {
                prevpos=2;
                pos = 6;
               
                L=true;
            } else if (pos == 8) {
                prevpos=8;
                pos = 11;
              

                L=true;
            } 
         
             else if (pos == 12) {
                prevpos=12;
                pos = 3;
                
                S=true;
            }
           
            else if (pos == 9) {
                prevpos=9;
                pos = 1;
              
                S=true;
            }
            cout << "\n";

            if(S)
            {
             

                 for (int dd =prevpos; dd>= pos; dd--)
                  {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();

                cout << "\n ?~~~~~~~~~   You got bitten by a snake   ?~~~~~~~~\n";
                display1(dd, a);
                usleep(700000); // Adjust the delay as needed
                      }
            }
            if(L)
            {
                for (int dd = prevpos; dd <= pos; dd++)
            {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();

                cout << "\nYou got a ladder   H  \n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                display1(dd, a);
                usleep(800000); // Adjust the delay as needed
            }

            }
           
        
           
           
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (pos == a[i][j])
                        a[i][j] = 0;
                }
            }

            if (pos==16) {
                break;
            }
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    a[i][j] = x[i][j];
                }
            }
            cout << "\n";
        }
         else {
            
            pos = pos - dice;
              for (int dd = prevpos; dd <= pos; dd++)
            {
                clearScreen();        ///    clear screeen
                snakes_and_ladders();
                cout << "\nYou rolled a " << dice << endl;
                display1(dd, a);
                usleep(900000); // Adjust the delay as needed
            }
           
        }
    }


    cout << "\n$$$$$$$  YOU WON THE GAME  $$$$$$$$\n";

    end: ;
         
     }

     /////////////  two player game


     void display2(int each, int a[][4],bool turn,int prev2,int pos1) {
    for (int i = 0; i < 4; i++) {
        cout << "                                       ---------------------------------------------\n";
        cout << "                                       |   ";
        for (int j = 0; j < 4; j++) {
            
           if(turn)
          {  
            if(a[i][j]==each && a[i][j]==prev2)
            {
                 cout << "P1^P2";
                cout << "  |   ";
            }
           else if(a[i][j]==prev2)
            {
                 cout << "  P2 ";
                cout << "  |   ";
            }

            
            else if (a[i][j] == each) {
                cout << "  P1 ";
                cout << "  |   ";
            } else if (a[i][j] / 10 == 0)
                cout << a[i][j] << "      |   ";
            else
                cout << a[i][j] << "     |   ";
          }
          else
          {
            

            if(a[i][j]==each && a[i][j]==pos1)
            {
                 cout << "P1^P2";
                cout << "  |   ";
            }
            else if(a[i][j]==pos1)
            {
                cout << "  P1 ";
                cout << "  |   ";          
            }

            else if (a[i][j] == each) {
                cout << "  P2 ";
                cout << "  |   ";
            } else if (a[i][j] / 10 == 0)
                cout << a[i][j] << "      |   ";
            else
                cout << a[i][j] << "     |   ";
          }
        }
        cout << endl;
    }
    cout << "                                       ---------------------------------------------\n";
}


     void play2()
     {
         int x[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    char f, l;
      
    bool endgame=false;  

    int a[4][4];
    int pos1 = 0, i, j, dice, prevpos1;
    int prevpos2;
    int pos2=0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            a[i][j] = x[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        cout << "                                       ---------------------------------------------\n";
        cout << "                                       |   ";
        for (int j = 0; j < 4; j++) {
           if (a[i][j] / 10 == 0)
                cout << a[i][j] << "      |   ";
            else
                cout << a[i][j] << "     |   ";
        }
        cout << endl;
    }
    cout << "                                       ---------------------------------------------\n";
    bool S=false;
    bool L=false;
    
    while (pos1 <16 && pos2<16) {
        cout << "\nPress any key to roll Dice Player1\n";
        f=_getch();
         if(f==27)
        {
            goto end2;
        }
        srand(time(0)); // seed the random number generator with the current time
        // roll the dice and print the result
        dice = rand() % 6 + 1;
        

        pos1 = pos1 + dice;
        prevpos1 = pos1 - dice;


         
        

        if (pos1 <= 16) 
        {
                
           

            // COMMON  JUMP
           for (int dd = prevpos1; dd <= pos1; dd++)
            {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();

                cout << "\nPlayer1 rolled a " << dice << endl;
                display2(dd, a,true,pos2,pos1);
                usleep(900000); // Adjust the delay as needed
            }
            S=false;
            L=false;
            if (pos1 == 2) {
                prevpos1=2;
                pos1 = 6;
              
                L=true;
            } else if (pos1 == 8) {
                prevpos1=8;
                pos1 = 11;
          
                L=true;
            } 
         
             else if (pos1 == 12) {
                prevpos1=12;
                pos1 = 3;
                
                S=true;
            }
           
            else if (pos1 == 9) {
                prevpos1=9;
                pos1 = 1;
                
                S=true;
            }
            cout << "\n";

            if(S)
            {
             

                 for (int dd =prevpos1; dd>= pos1; dd--)
                  {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();

                cout << "\n ?~~~~~~~~~   Player1 got bitten by a snake   ?~~~~~~~~\n";
                display2(dd, a,true,pos2,pos1);
                usleep(700000); // Adjust the delay as needed
                      }
            }
            if(L)
            {
                for (int dd = prevpos1; dd <= pos1; dd++)
            {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();

                cout << "\nPlayer1 got a ladder\n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                display2(dd, a,true,pos2,pos1);
                usleep(800000); // Adjust the delay as needed
            }

            }
           
        

            if (pos1== 16) {
                cout << "\n$$$$$$$  Player1 WON THE GAME  $$$$$$$$\n";
                break;
            }
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    a[i][j] = x[i][j];
                }
            }
            cout << "\n";
        }
         else {
            
            pos1 = pos1 - dice;
              for (int dd = prevpos1; dd <= pos1; dd++)
            {
                clearScreen();        ///    clear screeen
                snakes_and_ladders();
                cout << "\nPlayer1 rolled a " << dice << endl;
                display2(dd, a,true,pos2,pos1);
                usleep(900000); // Adjust the delay as needed
            }
           
        }


         cout << "\nPress any key to roll Dice Player2\n";
        f=_getch();
         if(f==27)
        {
            goto end2;
        }
        srand(time(0)); // seed the random number generator with the current time
        // roll the dice and print the result
        dice = rand() % 6 + 1;
        

        pos2 = pos2 + dice;
        prevpos2 = pos2 - dice;  

        if (pos2 <= 16) 
        {
                
            

            // COMMON  JUMP
           for (int dd = prevpos2; dd <= pos2; dd++)
            {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();

                cout << "\nPlayer2 rolled a " << dice << endl;
                display2(dd, a,false,prevpos2,pos1);
                usleep(900000); // Adjust the delay as needed
            }
            S=false;
            L=false;
            if (pos2 == 2) {
                prevpos2=2;
                pos2 = 6;
               
                L=true;
            } else if (pos2 == 8) {
                prevpos2=8;
                pos2 = 11;
              

                L=true;
            } 
         
             else if (pos2 == 12) {
                prevpos2=12;
                pos2 = 3;
               
                S=true;
            }
           
            else if (pos2 == 9) {
                prevpos2=9;
                pos2 = 1;
     
                S=true;
            }
            cout << "\n";

            if(S)
            {
             

                 for (int dd =prevpos2; dd>= pos2; dd--)
                  {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();

                cout << "\n ?~~~~~~~~~   Player2 got bitten by a snake   ?~~~~~~~~\n";
                display2(dd, a,false,prevpos2,pos1);
                usleep(700000); // Adjust the delay as needed
                      }
            }
            if(L)
            {
                for (int dd = prevpos2; dd <= pos2; dd++)
            {
                clearScreen();        ///    clear screeen
                                snakes_and_ladders();

                cout << "\nPlayer2 got a ladder\n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                cout << "                   H   \n";
                display2(dd, a,false,prevpos2,pos1);
                usleep(800000); // Adjust the delay as needed
            }

            }
           

            if (pos2==16) {
                cout << "\n$$$$$$$  Player2 WON THE GAME  $$$$$$$$\n";
                break;
            }
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    a[i][j] = x[i][j];
                }
            }
            cout << "\n";
        }
         else {
            
            pos2 = pos2 - dice;
              for (int dd = prevpos2; dd <= pos2; dd++)
            {
                clearScreen();        ///    clear screeen
                snakes_and_ladders();
                cout << "\nPlayer2 rolled a " << dice << endl;
                display2(dd, a,false,prevpos2,pos1);
                usleep(900000); // Adjust the delay as needed
            }
           
        }
    }
    end2: ;
     }
};
  
 class XO : public Game
 {
    private:
     char arr[3][3];
    bool visited[3][3];

    public:

bool normalmove(char arr[3][3], char choice, char oppch)
{
    int cnt1 = 0;
    int cnt2 = 0;
    int q = 1;

    // check rows
    for (int i = 0; i < 3; i++)
    {
        q = 1;
        cnt1 = 0;
        cnt2 = 0;
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == choice)
            {
                cnt1++;
            }
            else if (arr[i][j] == oppch)
            {
                q = -1;
                break;
            }
            else if (arr[i][j] == '-')
            {
                cnt2++;
            }
        }
        if (q != -1 && cnt1 == 1 && cnt2 == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (arr[i][j] != choice && arr[i][j] == '-')
                {
                    arr[i][j] = choice;
                    visited[i][j]=true;
                    break;
                }
            }
            return true;
        }
    }

    // check columns
    for (int i = 0; i < 3; i++)
    {
        q = 1;
        cnt1 = 0;
        cnt2 = 0;
        for (int j = 0; j < 3; j++)
        {
            if (arr[j][i] == choice)
            {
                cnt1++;
            }
            else if (arr[j][i] == oppch)
            {
                q = -1;
                break;
            }
            else if (arr[j][i] == '-')
            {
                cnt2++;
            }
        }
        if (q != -1 && cnt2 == 2 && cnt1 == 1)
        {
            for (int j = 0; j < 3; j++)
            {
                if (arr[j][i] != choice && arr[j][i] == '-')
                {
                    arr[j][i] = choice;
                    visited[j][i]=true;
                    break;
                }
            }
            return true;
        }
    }

    // check \ diagonal
    q = 1;
    cnt1 = 0;
    cnt2 = 0;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][i] == choice)
        {
            cnt1++;
        }
        else if (arr[i][i] == oppch)
        {
            q = -1;
            break;
        }
        else if (arr[i][i] == '-')
        {
            cnt2++;
        }
    }
    if (q != -1 && cnt1 == 1 && cnt2 == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (arr[i][i] != choice && arr[i][i] == '-')
            {
                arr[i][i] = choice;
                visited[i][i]=true;
                break;
            }
        }
        return true;
    }

    // check / diagonal
    q = 1;
    cnt1 = 0;
    cnt2 = 0;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][2 - i] == choice)
        {
            cnt1++;
        }
        else if (arr[i][2 - i] == oppch)
        {
            q = -1;
            break;
        }
        else if (arr[i][2 - i] == '-')
        {
            cnt2++;
        }
    }
    if (q != -1 && cnt1 == 1 && cnt2 == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (arr[i][2 - i] != choice && arr[i][2 - i] == '-')
            {
                arr[i][2 - i] = choice;
                visited[i][2-i]=true;
                break;
            }
        }
        return true;
    }

    return false;
}
    bool pcwinning(char arr[3][3], char choice, char oppch)
{
    int cnt = 0;
    int q = 1;

    // check rows
    for (int i = 0; i < 3; i++)
    {
        q = 1;
        cnt = 0;
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == choice)
            {
                cnt++;
            }
            else if (arr[i][j] == oppch)
            {
                q = -1;
                break;
            }
        }
        if (q != -1 && cnt == 2)
        {
            for (int j = 0; j < 3; j++)
            {
         if (arr[i][j] == '-')
                {
                    arr[i][j] = choice;
                    visited[i][j]=true;
                    return true;
                }
            }
        }
    }

    // check columns
    for (int i = 0; i < 3; i++)
    {
        q = 1;
        cnt = 0;
        for (int j = 0; j < 3; j++)
        {
            if (arr[j][i] == choice)
            {
                cnt++;
            }
            else if (arr[j][i] == oppch)
            {
                q = -1;
                break;
            }
        }
        if (q != -1 && cnt == 2)
        {
       for (int j = 0; j < 3; j++)
      {
                if (arr[j][i] == '-')
             {
                    arr[j][i] = choice;
                    visited[j][i]=true;
                    return true;
                }
            }
        }
    }

    // check \ diagonal
    q = 1;
    cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][i] == choice)
        {
            cnt++;
        }
        else if (arr[i][i] == oppch)
        {
            q = -1;
            break;
        }
    }
    if (q != -1 && cnt == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (arr[i][i] == '-')
            {
                arr[i][i] = choice;
                visited[i][i]=true;
                return true;
            }
        }
    }

    // check / diagonal
    q = 1;
    cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][2 - i] == choice)
        {
            cnt++;
        }
        else if (arr[i][2 - i] == oppch)
        {
            q = -1;
            break;
        }
    }
    if (q != -1 && cnt == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (arr[i][2 - i] == '-')
            {
                arr[i][2 - i] = choice;
                visited[i][2-i]=true;
                return true;
            }
        }
    }
    return false;
}

    bool oppwinning(char arr[3][3], char choice, char oppch)
{
    int cnt = 0;
    int q = 1;

    // check rows
    for (int i = 0; i < 3; i++)
    {
        q = 1;
        cnt = 0;
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == choice)
            {
                cnt++;
            }
            else if (arr[i][j] == oppch)
            {
                q = -1;
                break;
            }
        }
        if (q != -1 && cnt == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (arr[i][j] == '-')
                {
                    arr[i][j] = oppch;
                    visited[i][j]=true;
                    return true;
                }
            }
        }
    }

    // check columns
    for (int i = 0; i < 3; i++)
    {
        q = 1;
        cnt = 0;
        for (int j = 0; j < 3; j++)
        {
            if (arr[j][i] == choice)
            {
                cnt++;
            }
            else if (arr[j][i] == oppch)
            {
                q = -1;
                break;
            }
        }
        if (q != -1 && cnt == 2)
        {
            for (int j = 0; j < 3; j++)
            {
                if (arr[j][i] == '-')
                {
                    arr[j][i] = oppch;
                    visited[j][i]=true;
                    return true;
                }
            }
        }
    }

    // check \ diagonal
    q = 1;
    cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][i] == choice)
        {
            cnt++;
        }
        else if (arr[i][i] == oppch)
        {
            q = -1;
            break;
        }
    }
    if (q != -1 && cnt == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (arr[i][i] == '-')
            {
                arr[i][i] = oppch;
                visited[i][i]=true;
                return true;
            }
        }
    }

    // check / diagonal
    q = 1;
    cnt = 0;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][2 - i] == choice)
        {
            cnt++;
        }
        else if (arr[i][2 - i] == oppch)
        {
            q = -1;
            break;
        }
    }
    if (q != -1 && cnt == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (arr[i][2 - i] == '-')
            {
                arr[i][2 - i] = oppch;
                visited[i][2-i]=true;
                return true;
            }
        }
    }
    return false;
}

void pc_turn(char arr[3][3], char choice, int count)
{
     char oppch='X';

     if(choice=='X')
     {
         oppch='O';
     }
    if (pcwinning(arr, choice, oppch))
    {
        
        return;
    }
    if (oppwinning(arr, oppch, choice))
    {
        return;
    }
    else if (count == 1 && visited[1][1]==false)
    {
        if (arr[1][1] == '-')
        {
            arr[1][1] = choice;
            visited[1][1]=true;
        }
    }
    else
   {  if (count <= 2 )
    {
        if (arr[0][2] == '-' && visited[0][2]==false)
        {
            arr[0][2] = choice;
            visited[0][2]=true;
            return;
        }
        if (arr[2][2] == '-' &&  visited[2][2]==false)
        {
            arr[2][2] = choice;
            visited[2][2]=true;
            return;
        }
        if (arr[0][0] == '-' &&  visited[0][0]==false)
        {
            arr[0][0] = choice;
            visited[0][0]=true;
            return;
        }
        if (arr[2][0] == '-'  && visited[2][0]==false)
        {
            arr[2][0] = choice;
            visited[2][0]=true;
            return;
        }
    }
    else
    {
        bool p = normalmove(arr, choice, oppch);

        if (p == false)
        {
             // fill remaining

             for(int i=0;i<3;i++)
             {
                 for(int j=0;j<3;j++)
                 {
                     if(arr[i][j]=='-')
                     {
                         arr[i][j]='X';
                         visited[i][j]=true;
                         return;
                     }
                 }
             }
        }
    }
   }
}
bool checkwinning(char arr[3][3], char choice)
{
    int w = 0;

    // check rows
    for (int i = 0; i < 3; i++)
    {
        w = 0;
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] != choice)
            {
                w = 1;
                break;
            }
        }
        if (w == 0)
        {
            return true;
        }
    }

    // check columns
    for (int i = 0; i < 3; i++)
    {
        w = 0;
        for (int j = 0; j < 3; j++)
        {
            if (arr[j][i] != choice)
            {
                w = 1;
                break;
            }
        }
        if (w == 0)
        {
            return true;
        }
    }

    // check \ diagonal
    w = 0;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][i] != choice)
        {
            w = 1;
            break;
        }
    }
    if (w == 0)
    {
        return true;
    }

    // check / diagonal
    w = 0;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i][2 - i] != choice)
        {
            w = 1;
            break;
        }
    }
    if (w == 0)
    {
        return true;
    }

    return false;
}
bool allvisited(bool visited[][3])
{
     for(int i=0;i<3;i++)
     {
         for(int j=0;j<3;j++)
         {
             if(visited[i][j]==false)
             {
                 return false;
             }
         }
     }
     return true;
}

void clearScreen() {
    // Clear the screen (works on Unix-like systems)
    cout << "\033[2J\033[1;1H";
}

    void play(User* user)
    {
         char playerch;

    cout<<"                                                Tic-Tac-Toe\n\n";
    cout << "                                               +---+---+---+" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            arr[i][j] = '-';
            
            if(j==0)
            {
                 cout <<"                                               | "<<arr[i][j] <<" ";
            }
            else
            cout <<"| "<<arr[i][j] <<" ";

            visited[i][j]=false;
        }
        
        
        cout <<"|"<<endl;
        cout << "                                               +---+---+---+" << endl;
        
    }


    cout<<"Enter Your Choice     'X'   or   'O'  :   ";
    cin>>playerch;
    cout<<endl;

    char pcch='O';

    int count = 0; /// for first move at centre and second at corner

    if(playerch == 'O')
    {
         pcch='X';

          pc_turn(arr, 'X', 1);
       
        cout << "                                               +---+---+---+" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(j==0)
            {
                cout <<"                                               | "<<arr[i][j] <<" ";
            }
            else
            cout <<"| "<<arr[i][j] <<" ";
       
        }
        
        
        cout <<"|"<<endl;
        cout << "                                               +---+---+---+" << endl;
        
    }
    cout<<endl;

    }


    int r, c;
    
    while (1)
    {

        
        count++;
       

        while(1)
       {
        
        cout<<"\n                                                Player  : '"<<playerch<<"'              PC : '"<<pcch<<"'"<<endl;
        
         cout << "\nEnter row and column of player\n";
         cout<<"                                           Row : ";cin >> r ;
         cout<<"                                        Column : ";cin>> c;
        cout<<endl;
        
        if(r>2 || c>2 || r<0 || c<0)
        {
            cout<<"Invalid Choice\n";
            continue;
        }

        
        if(visited[r][c]==true)
        {
             cout<<"Slot is already filled\n";
        }
        else
       { arr[r][c] = playerch;
        visited[r][c]=true;
        break;

       }
       }
       


           cout << "                                               +---+---+---+" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(j==0)
            {
                cout <<"                                               | "<<arr[i][j] <<" ";
            }
           else
            cout <<"| "<<arr[i][j] <<" ";
       
        }
        
        
        cout <<"|"<<endl;
        cout << "                                               +---+---+---+" << endl;
        
    }
    cout<<endl;
    
     if (checkwinning(arr, playerch))
        {                                                          
            cout<<"                                  $$$$$$$$$$$$$   YOU WON   $$$$$$$$$$$$$\n";
            break;
        }

      if(allvisited(visited))
        {
            cout<<"                                   ****************   TIE   ****************\n";
             break;
        }


         pc_turn(arr, pcch, count);
         clearScreen();
       
          cout << "                                               +---+---+---+" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(j==0)
            {
                cout <<"                                               | "<<arr[i][j] <<" ";
            }
            else
            cout <<"| "<<arr[i][j] <<" ";
       
        }
        
        
        cout <<"|"<<endl;
        cout << "                                               +---+---+---+" << endl;
        
    }
    cout<<endl;

        if (checkwinning(arr, pcch))
        {
            cout << "                               #############  PC  WON  #############\n";
            break;
        }
        if(allvisited(visited))
        {
             cout<<"                                   ****************   TIE   ****************\n";
             break;
        }
         usleep(100000); 
    }

    }
 } ;






   
     // owner balance
double Owner::currbalance=10000000.0;
double Owner::initbalance=10000000.0;
BankAccount Owner::account={6969,10000000.0};

int main() {


     
  // cout<<"Owner balance == "<<Owner::ownergetBalance()<<endl;

    map<long long , double> bankmap;
    // bank account numbers registered
          bankmap[123]=100.0;
          bankmap[111]=189.0;
          bankmap[222]=400.0;
          bankmap[333]=980.0;
          bankmap[444]=628.0;
          bankmap[555]=34.0;
          bankmap[666]=4550.0;
          bankmap[777]=1800.0;
          bankmap[888]=199.0;
          bankmap[999]=545.0;
          bankmap[000]=100000.0;
          
          
         
     

      // to get unique user name
     map<string,User*> stake;

    User* userptr=NULL;

    MinesGame minesGame;
    Cards cards;
    Slots Slots;
    Rock_paper_scissor RPS;
    Horse horse;
    Dice dice;
    Snake_and_Ladder SAL;
    XO xo;


    vector<Game*> games{&minesGame,&cards, &Slots,&RPS,&horse,&dice,&SAL,&xo};

    int ch;
    int choice;
    string name="";
    long long accno;


    LeadersBoard LB;
    double prev=0;

  while(1)
{

   // cout<<"\nOwnerProfit --->   "<<Owner::getprofit()<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------\n";    
    cout<<"                                  GAME - HUB\n";  
    cout<<"\n                                1 ---->  signup\n";
    cout<<"                                2 ----> Login\n";
    cout<<"                                Enter your choice : ";cin>>choice;
    cout<<endl;
     if(choice!=1 && choice!=2) 
    {
        cout<<"Invalid Choice \n";
        continue;
    }

    cout<<"Enter username : ";cin>>name;

    if(choice==1)
    {
         if(stake.count(name) ==1)
         {
              cout<<"This name already exists\n";
              continue;
         }
         else
         {
             

             cout<<"Enter the account number : ";cin>>accno;
             cout<<endl;
             if(bankmap.count(accno)!=1)
             {
                 cout<<"Account number not found !\n";
                 continue;
             }
             

             userptr=new User(name,accno,bankmap[accno]);
             stake[name]=userptr;
             
         }
    }
    else if(choice==2)
    {
          if(stake.count(name) !=1)
          {
             cout<<"Username does'nt exits\n";
             continue;
          }
          else
          {
             userptr=stake[name];
          }
    }
   



    while(1)
   {
    
    cout<<"---------------------------------------------------------------------------------------------------------\n";    
    cout<<"                                              HOME\n";
   

    if(choice==1)
    {
          cout<<"  Welcome,"<<userptr->getUsername();
    }
    else
    {cout<<"  Welcome back,"<<userptr->getUsername();}    // 70 spaces - size of usernamee
    for(int q=1;q<=70-userptr->getUsername().length();q++ )
    {
        cout<<" ";
    }
    cout<<" Balance : "<<userptr->getBalance()<<endl<<endl; 
    cout<<"                  +---------------------------------------------------------------+\n"; 
    cout<<"                  |    1-----> Mines              |      9----->Player Statistics |\n";
    cout<<"                  |    2-----> Cards              |     10-----> LeadersBoard     |\n";
    cout<<"                  |    3-----> Slots              |     ";if(userptr->checkbonus()){cout<<"11 -----> Claim Bonus     |\n";}else{cout<<"                          |\n";}
    cout<<"                  |    4-----> Rock Paper Scissor |                               |\n";
    cout<<"                  |    5-----> Horse Gambling     |                               |\n";
    cout<<"                  |    6-----> Dice               |                               |\n";
    cout<<"                  |    7-----> Snake and Ladder   |                               |\n";
    cout<<"                  |    8-----> XO                 |      0 ----> Logout           |\n";
    cout<<"                  +---------------------------------------------------------------+\n";
   
    
    cout<<"\n            Enter your choice which game to play  :  ";cin>>ch;cout<<endl;
    
    cout<<"---------------------------------------------------------------------------------------------------------\n";    
      cout<<endl;
         

    if(ch==0)
    {
        bankmap[accno]=userptr->getBalance();           // to  update that particular account after playing
        LB.add_to_table(userptr->getUsername(),userptr->total_prof()-prev);
        prev=0;
        
         break;
    }
   
    else if(ch==9)
    {
        
        userptr->display_stats();
    }
    else if(ch==10 )
    {
        
         LB.add_to_table(userptr->getUsername(),userptr->total_prof()-prev);
          prev=userptr->total_prof();
         LB.view_leadersboard();
    }
    else if(ch==11 && userptr->checkbonus()==true)
    {
          userptr->claimbonus();
    }
    
     else if(ch >0 && ch<=8)
{
        games[ch-1]->play(userptr);
}
else
{
     cout<<"Invalid Choice\n";
}

   }


}
    
    return 0;
}
