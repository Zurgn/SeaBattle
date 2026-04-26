#include <iostream>
#include <ctime>

using namespace std;

void Draw(char player[10][10], char bot[10][10])
{
    // Отрисовка поля
    cout<<'\n'<<"        Ваше поле                          Вражеское поле";
    cout<<'\n'<<"   1 2 3 4 5 6 7 8 9 10                 1 2 3 4 5 6 7 8 9 10"<<'\n';
    for(int i=0;i<10;i++)
        {
            cout<<i+1<<" "; if(i!=9){cout<<" ";}
            for(int j=0;j<10;j++)
            {
                cout<<player[i][j]<<" ";
            }
            cout<<"      |       ";

            // Отрисовка поля бота
            cout<<i+1<<" "; if(i!=9){cout<<" ";}
            for(int j=0;j<10;j++)
            {
                // if(bot[i][j]=='#'){cout<<'~'<<" ";}
                // else{cout<<bot[i][j]<<" ";}
                cout<<bot[i][j]<<" ";
            }
            cout<<'\n';
        }
    cout<<'\n';
}


bool Check_ship_set(int y, int x, string direction, int size, char map[10][10])
{
    int endY=y, endX=x;

    if      (direction=="N" || direction=="n") endY=y-(size-1);
    else if (direction=="S" || direction=="s") endY=y+(size-1);
    else if (direction=="E" || direction=="e") endX=x+(size-1);
    else if (direction=="W" || direction=="w") endX=x-(size-1);

    if(endY<0 || endY>9 || endX<0 || endX>9 || x<0 || x>9 || y<0 || y>9){cout<<"info>> выход за пределы поля"<<endl; return false;}

    int startI = (y<endY ? y:endY)-1;
    int endI   = (y>endY ? y:endY)+1;
    int startJ = (x<endX ? x:endX)-1;
    int endJ   = (x>endX ? x:endX)+1;

    for(int i=startI; i<=endI; i++){
        for(int j=startJ; j<=endJ; j++){
            if(i>=0 && i<10 && j>=0 && j<10){
                if(map[i][j]=='#'){cout<<"info>> рядом другой корабль"<<endl; return false;}
            }
        }
    }
    return true;
}


void Set_auto(char map[10][10])
{
    int count=0;
    string direction;
    for(int ship_size=4; ship_size!=0; ship_size--)
    {
        count++;
        for(int step=count; step!=0; step--)
        {
            for(;;){
                int col=rand()%10;
                int row=rand()%10;
                int rand_direction=rand()%2;
                if(rand_direction==0){direction="N";}
                else{direction="E";}

                if(Check_ship_set(row, col, direction, ship_size, map))
                {
                    if(direction=="N" or direction=="n"){for(int i = ship_size; i!=0; i--){map[row][col]='#';row-=1;}}
                    else if(direction=="E" or direction=="e"){for(int i = ship_size; i!=0; i--){map[row][col]='#';col+=1;}}
                    break;
                }
            }
        }
    }
}


void Mark(int y, int x, char map[10][10]) {
    int endY=y, endX=x;
    int startI = (y<endY ? y:endY)-1;
    int endI   = (y>endY ? y:endY)+1;
    int startJ = (x<endX ? x:endX)-1;
    int endJ   = (x>endX ? x:endX)+1;
    for(int i=startI; i<=endI; i++){
        for(int j=startJ; j<=endJ; j++){
            if(map[i][j]=='~'){map[i][j]='o';}}}
    }
    


bool Check_ship_destroy(int y, int x, char map[10][10])
{
    for(int i=y; i>=0 && (map[i][x]=='x' || map[i][x]=='#'); i--){if(map[i][x]=='#') return false;}
    for(int i=y; i<10 && (map[i][x]=='x' || map[i][x]=='#'); i++){if(map[i][x]=='#') return false;}
    for(int j=x; j>=0 && (map[y][j]=='x' || map[y][j]=='#'); j--){if(map[y][j]=='#') return false;}
    for(int j=x; j<10 && (map[y][j]=='x' || map[y][j]=='#'); j++){if(map[y][j]=='#') return false;}
    cout<<"info>> корабль уничтожен!"<<endl;
    for(int i=y; i>=0 && (map[i][x]=='x'); i--){if(map[i][x]=='x') Mark(i, x, map);}
    for(int i=y; i<10 && (map[i][x]=='x'); i++){if(map[i][x]=='x') Mark(i, x, map);}
    for(int j=x; j>=0 && (map[y][j]=='x'); j--){if(map[y][j]=='x') Mark(y, j, map);}
    for(int j=x; j<10 && (map[y][j]=='x'); j++){if(map[y][j]=='x') Mark(y, j, map);}
    return true;
}


bool Check_win(char map[10][10])
{
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){if(map[i][j]=='#'){return false;}}}
    return true;
}


int main()
{
    srand(time(0));
    int row, col, menu, choise, count=0;
    bool game=true;

    char player[10][10];
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){player[i][j]='~';}}

    char bot[10][10]; //Поле боя
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){bot[i][j]='~';}}

    while(game)
    {
        cout<<"\n-----Менью-----"<<"\n1.Начать игру\n2.Выход\n>> "; cin>>menu;
        switch(menu)
        {
            case 1:
            {   
                cout<<"\nКак расставить корабли?\n1.Самостоятельно\n2.Автоматически\n>> "; cin>>choise;
                switch(choise)
                {
                    case 1:
                    {
                        cout<<'\n'<<"info>> Расставьте корабли:"<<endl;
                        string direction;
                        
                        for(int ship_size=4; ship_size!=0; ship_size--)
                        {
                            count++;
                            for(int step=count; step!=0; step--)
                            {
                                for(;;){
                                    Draw(player, bot);
                                    cout<<"Введите координаты носа корабля (размер корабля "<<ship_size<<")"<<endl;
                                    cout<<"Горизонталь: "; cin>>col; col-=1;
                                    cout<<"Вертикаль: "; cin>>row; row-=1;
                                    if(ship_size!=1){cout<<"Направление (N-север, E-восток, S-юг, W-запад): "; cin>>direction; cout<<endl;} 
                                    else{direction="N";}
                                    
                                    if(Check_ship_set(row, col, direction, ship_size, player)==true){
                                        if(direction=="N" or direction=="n"){for(int i = ship_size; i!=0; i--){player[row][col]='#';row-=1;}}
                                        if(direction=="E" or direction=="e"){for(int i = ship_size; i!=0; i--){player[row][col]='#';col+=1;}}
                                        if(direction=="S" or direction=="s"){for(int i = ship_size; i!=0; i--){player[row][col]='#';row+=1;}}
                                        if(direction=="W" or direction=="w"){for(int i = ship_size; i!=0; i--){player[row][col]='#';col-=1;}}
                                        break;}
                                }
                            }
                        }
                        break;
                    }

                    case 2:
                    {
                        Set_auto(player); break;
                    }

                    default:{cout<<"info>> Нет такого пункта"<<endl; break;}
                }

                // расстановка кораблей ботом
                Set_auto(bot);

                int move = 1;
                bool process = true;
                while(process)
                {   
                    if(move==1){               
                        Draw(player, bot);
                        cout<<"Куда стреляем?"<<endl; 
                        cout<<"Горизонталь: "; cin>>col; col-=1;
                        cout<<"Вертикаль: "; cin>>row; row-=1;
                        cout<<"статус: ";
                        if(col>9 or col<0 or row>9 or row<0){cout<<"Выход за пределы поля боя";}
                        else if((bot[row][col]=='o') or (bot[row][col]=='x')){cout<<"Клетка уже подверглась обстрелу";}
                        else if(bot[row][col]=='#') 
                            {
                                cout<<"Попадание"<<endl; 
                                bot[row][col]='x'; 
                                if(Check_ship_destroy(row, col, bot)){
                                    if(Check_win(bot)){
                                        Draw(player, bot);
                                        cout<<"Вы выиграли!"<<endl;
                                        process = false;
                                        }
                                };
                            }
                        else{cout<<"Промах"<<endl; bot[row][col]='o'; move=0;}
                        }

                    if(move==0){    
                        Draw(player, bot);
                        cout<<"Враг атакует!"<<endl;
                        int col=rand()%10;
                        int row=rand()%10;
                        if(player[row][col]=='#') 
                            {
                                cout<<"Попадание"<<endl; 
                                player[row][col]='x'; 
                                if(Check_ship_destroy(row, col, player)){
                                    if(Check_win(player)){
                                        Draw(player, bot);
                                        cout<<"Вы проиграли!"<<endl;
                                        process = false;
                                        }
                                };
                            }
                        else{cout<<"Враг промахнулся"<<endl; player[row][col]='o'; move=1;}
                        }
                }
                break;
            }
            case 2:{return 0; break;}
            default:{cout<<"info>> Нет такого пункта"<<endl; break;}
        }
    }

    return 0;
}