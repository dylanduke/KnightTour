
#include <vector>
#include <iomanip>
class knightType
{
public:
    struct position
    {
        position(int r=0, int c=0, int o=0)
        {
            row=r;
            col=c;
            onwardMoves=o;
        }
        int row;
        int col;
        int onwardMoves;
    };
    //std::vector<std::vector<int>> board;
    knightType(int=8);
    bool knightTour(int,int);
    void outputTour() const;
private:
    bool knightTour(int,int,int);
    std::vector<position> getAvailableMoves(int, int);
    bool fullBoard();
    std::vector<std::vector<int>> board;
    int functionsCalled;
};


knightType::knightType(int dim){
    std::vector<std::vector<int>> fun(dim,std::vector<int>(dim,0));
    board=fun;
    functionsCalled=0;
}

std::vector<knightType::position> knightType::getAvailableMoves(int r, int c){
    std::vector<position> knightMoves;
    //the knight has at most 8 possible moves from a given point on the board, so
    //we look at the 8 possible moves and see if they haven't been visited and are on the
    //board. if so, we add them to the knightmoves vector.
    //the possible move combinations are
    //(1,2),(2,1)(-1,2),(-2,1),(-1,-2),(-2,-1),(-2,1),and(2,-1)
    //so we have to check each of these.
    int rmoves[]={1,2,1,-2,-1,-2,-1,2};
    int cmoves[]={2,1,-2,-1,-2,1,2,-1};
    //trying all possible knight moves to see if they're legal on the board and the spot hasn't been visited
    for(int i=0;i<8;i++){
        int rnext=r+rmoves[i];
        int cnext=c+cmoves[i];
        if (rnext<board.size() and rnext>=0 and cnext<board.size() and cnext>=0 and board[rnext][cnext]==0){
            position newMove;
            newMove.row=rnext;
            newMove.col=cnext;
            for (int j=0;j<8;j++){
                int rnextsub=rnext+rmoves[j];
                int cnextsub=cnext+cmoves[j];
                if (rnextsub<board.size() and rnextsub>=0 and cnextsub<board.size() and cnextsub>=0 and board[rnextsub][cnextsub]==0){
                    newMove.onwardMoves+=1;
            }
        }
            knightMoves.push_back(newMove);
            //i only push back at the end so i dont end up losing the index or messing around too much with that
    }
    }
    return knightMoves;
}



bool knightType::fullBoard(){
    for (int i=0;i<board.size();i++){
        for (int j=0;j<board.size();j++){
            if (board[i][j]==0){
                return false;
                //linear search to find a zero
            }
        }
    }
    return true;
}



void knightType::outputTour() const{
    char currentLetter='A';
    std::cout<<" ";
    for (int i=0;i<board.size();i++){
        std::cout<<std::setw(2)<<currentLetter<<" ";
        currentLetter++;
    }
    //format printing the first line
    std::cout<<std::endl;
    currentLetter='A';
    //current letter prints for each row.
    for (int i=0;i<board.size();i++){
        std::cout<<currentLetter<<" ";
        currentLetter++;
        for (int j=0;j<board.size();j++){
            //inner loop prints the row values
            std::cout<<std::setw(2)<<board[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl<<"Functions called: "<<functionsCalled<<std::endl;
}
            
            
            
            
            
            
            

bool knightType::knightTour(int r, int c){
    return knightTour(r,c,1);
}

            
            
            
            
            
            
            
bool knightType::knightTour(int r, int c, int tourIndex){
    functionsCalled++;
    board[r][c]=tourIndex;
    //increment functionscalled and tourindex, call fullboard, continue if not full
    tourIndex++;
    if (fullBoard()==true){
        return true;
    }
    std::vector<position> knightMoves=getAvailableMoves(r,c);
    bool fun=false;
    //get moves and find the smallest by searching.
    for (int f=0;f<knightMoves.size();f++){
        int smallestmove=knightMoves[0].onwardMoves;
        int index=0;
        for (int i=1;i<knightMoves.size();i++){
            if(smallestmove>knightMoves[i].onwardMoves){
                smallestmove=knightMoves[i].onwardMoves;
                index=i;
            }
        }
        fun=knightTour(knightMoves[index].row,knightMoves[index].col,tourIndex);
        if(fun==true){
            return true;
        } else{
        // if this doesnt return true, clear that as the smallest and search again, call the function recursively again
            knightMoves.erase(knightMoves.begin()+index);
            continue;
        }
    }
    return false;
}







