
    
class StreetFighter{
public:
    StreetFighter(string playername);
    void AddBullets();
    void Fight(StreetFighter &B);
    bool checkBullets(int input);
    void viewWeapons();
    void Scores(StreetFighter &B);
private:
    int scoreplayer1;
    int scoreplayer2;
    string player;
    int matcheswon;
    int matcheslost;
    int numberofweapons;
    string weapons[50];// Maximum Number of Weapons allowed in the Game
    int bullet[50]; // Each weapons corresponds to a bullet in the array
    
    
};

StreetFighter::StreetFighter(string playername){  //Randomly Assigns weapons to the player
    scoreplayer1=0;
    scoreplayer2=0;
    
    player=playername;
    numberofweapons=0;
    string custom[6]={"AK47","Knife","Arrow","RayGun","ShotGun","Tank"};
    int customebullets[5]={5,10,12,20,1};
    for(int i=0;i<4;i++){
        numberofweapons=numberofweapons+1;
        int random = rand() % 6;
        int newrandom=rand()%5;
        weapons[i]=custom[random];
        bullet[i]=customebullets[newrandom];
    }
}

void StreetFighter::StreetFighter::Scores(StreetFighter &B){
    cout<<"Scores"<<endl;
    cout<<this->scoreplayer1<<" Player Name "<<this->player<<endl;
    cout<<B.scoreplayer2<<" Player Name" <<B.player<<endl;
    if (this->scoreplayer1==B.scoreplayer2){
        cout<<"TIE"<<endl;
    }
    else if( this->scoreplayer1 > B.scoreplayer2){
        cout<<this->player<<" WON" <<endl;
    }
    
    else{
        cout<<B.player<< "Won the Game"<<endl;
        
    }
}
void StreetFighter::StreetFighter::viewWeapons(){
    cout<<"------------------------------------------------------"<<endl;
    cout<<"Hello "<<player<<" Welcome to StreetFighter 2019"<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    for(int i=0;i<numberofweapons;i++){
        cout<<"Weapon Number "<<i<<" "<<weapons[i]<<" Total Bullets "<<bullet[i]<<endl;
    }
}

bool StreetFighter::StreetFighter::checkBullets(int input){
    if(this->bullet[input]>0){
        return true;
    }
    else{
        return false;
    }
}
void StreetFighter::StreetFighter::Fight(StreetFighter &B){
    int input;
    int playerinput;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"You are about to Fight with "<< B.player<<" Are you ready? "<<endl;

    this->viewWeapons();
    cout<<this->player<< " Please Enter Weapon Number you would like to fight with"<<endl;
    cout<<"Enter Weapons Number? ";
    bool repeat=true;
    while (repeat==true){
        cin>>input;
        bool status=checkBullets(input);
        if (status==true){
            
            cout<<"You have selected to fight with "<<weapons[input]<<endl;
            cout<<"-----------------WEAPON ASSIGNED---------------------------"<<endl;
            repeat=false;
        }
        else{
            cout<<"Unsuccesful as the weapon you picked has no bullets :("<<endl;
        }
    }
    B.viewWeapons();
    cout<<B.player<< " Please Enter Weapon Number you would like to fight with"<<endl;
    cout<<"Enter Weapons Number? ";
    cin>>playerinput;
    cout<<"You have selected to fight with "<<B.weapons[playerinput]<<endl;
    
    
    string weaponA= this->weapons[input];
    string weaponB= B.weapons[playerinput];
    if(weaponA=="AK47" & weaponB=="AK47"){
        bullet[input]=bullet[input]-1;//each loose a bullet and no wins
        B.bullet[playerinput]=B.bullet[playerinput]-1;
        this->scoreplayer1++;
        B.scoreplayer2++;
        cout<<"TIE"<<endl;
        char answer;
        cout<<"Do you want to play again y/n? "<< endl;
        cin>>answer;
        if( answer=='y'){
            Fight(B);
        }
        else{
            Scores(B);
        }
    }
    else if (weaponA=="AK47"&& weaponB!="AK47"){
        cout<<B.player<<" ouch you lost the battle with " << this->player<< endl;
        bullet[input]=bullet[input]-1;//each loose a bullet and no wins
        B.bullet[playerinput]=B.bullet[playerinput]-1;
        this->scoreplayer1++;
         //ak47 is the most powerfull here
        char answer;
        cout<<"Do you want to play again y/n? "<< endl;
        cin>>answer;
        if( answer=='y'){
            Fight(B);
        }
        else{
            Scores(B);
        }
    }
    else if (weaponA!="AK47"&& weaponB=="AK47"){
        cout<<this->player<<" ouch you lost the battle with " << B.player<< endl;
        bullet[input]=bullet[input]-1;//each loose a bullet and no wins
        B.bullet[playerinput]=B.bullet[playerinput]-1;
        B.scoreplayer2++;
        char answer;
        cout<<"Do you want to play again y/n? "<< endl;
        cin>>answer;
        if( answer=='y'){
            Fight(B);
        }
        else{
            Scores(B);
        }
    }
}

void StartGame(){
    cout<<"WELCOME TO ZEESHAAN DEVELOPMENT OF STREET FIGHTER"<<endl;
    string a;
    cout<<"Please Enter Player 1 Name"<<endl;
    cin>>a;
    StreetFighter player1(a);
    string b;
    cout<<"Please Enter Player 2 Name"<<endl;
    cin>> b;
    StreetFighter player2(b);
    char ans;
    cout<<"Do you want to Begin the Fight (y/n) ?"<<endl;
    cin>>ans;
    if( ans=='y' ){
        player1.Fight(player2);
    }
}

int main(){
    srand(time(0));
    StartGame();
}
