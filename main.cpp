#include <iostream>
#include <sstream>

using namespace std;

void delete_pamyat (char** matrix, unsigned int rows) {
	for(unsigned int i=0; i<rows; i++){	
		delete []matrix[i];
	}			
	delete []matrix;
}

char** pamyat_dlya_matritzi(char** matrix, unsigned int rows, unsigned int columns){
	matrix = new char *[ rows ];
	for( unsigned int i = 0; i < rows; ++i ) {
    	matrix[ i ] = new char[ columns ];
   		for( unsigned int j = 0; j < columns; ++j ) {
     		matrix[ i ][ j ] = ' ';
   		}
	}
	return matrix;
}

bool true_size (unsigned int &size) {
	bool ok=true;
	unsigned int size1, size2;
	char op;
	
	std::string line;
	std::getline( std::cin, line );
	std::istringstream stream (line);
	if (stream>>size1 && size1>1 && stream>>op && op=='X' && stream>>size2 && size1==size2) {	
		ok=!ok;
		size=size1;
	}
	return ok;
}

unsigned int read_size (void) {
	cout << "Hello! Glad to see you in this game! Please, write size of table for X-0 game in format <<size X size>> (size>1!): ";
	unsigned int size;
	
	while (true_size(size)) {		
		cout << endl << "You`ve made a mistake. Please, try again: ";
	}
	
	return size;
}

void show_game (char **array, unsigned int size) {
	char op='a';
	unsigned int k=0;
	
	cout << "    ";
	for (unsigned int i=0; i<size; i++){
		cout << i+1 << "   ";
	}
	
	cout << endl << "  +";
	for (unsigned int i=0; i<size; i++){
		cout << "---+";
	};
	cout << endl;
	for (unsigned int i=0; i<size; i++){
		for (unsigned int j=0; j<size; j++){
			if(i==k && j==0) {
				cout << op << " | ";
			}
			if (array[i][j]=='X' || array[i][j]=='O') {
				cout << array[i][j] << " | ";
			}
			else cout << "  | ";
			if (j==size-1) {
				cout << endl;
				cout << "  +";
				for (unsigned int i=0; i<size; i++){
					cout << "---+";
				};
				cout << endl;
			}
			k++;
		}
		k=i+1;
		op++;
	}
}

void show_available_moves (char **array, char op, unsigned int size){
	unsigned int k=0;
	unsigned int t=0;
	char letter='a';
	
	for (unsigned int i=0; i<size; i++){
		for (unsigned int j=0; j<size; j++){
			if (!(array[i][j]=='X' || array[i][j]=='O')) {
				//if (i==k){
					cout << ++k << ". mark cell " << letter << j+1 << " as " << op << endl;
				//}
			}
		}
		letter++;
	}
	cout << ++k << ". quit" << endl;
}

bool making_move (char **array, short move, char op, unsigned int size){
	unsigned int k=0;
	for (unsigned int i=0; i<size; i++){
		for (unsigned int j=0; j<size; j++){
			if (!(array [i][j] == 'X' || array [i][j] == 'O')) {
				k++;
			}
			if (k==move) {
				array [i][j] = op;
				return true;
			}
		}	
	}
	return false;
}

bool win_game(char** array, unsigned int size){
	unsigned int k=0, t=0;
	for (unsigned j=0; j<size; j++){
		for (unsigned int i=0; i<size-1; i++){
			if ((array[i][j]=='X' || array[i][j]=='O') && array[i][j]==array[i+1][j]) k++;
			if (k==size-1) return true;
		}
		k=0;
	}
	for (unsigned int i=0; i<size; i++){
		for (unsigned int j=0; j<size-1; j++){
			if ((array[i][j]=='X' || array[i][j]=='O') && array[i][j]==array[i][j+1]) k++;
			if (k==size-1) return true;
		}
		k=0;
	}
	for (unsigned int i=0; i<size-1; i++){
		if ((array[i][i]=='X' || array[i][i]=='O') && array[i][i]==array[i+1][i+1]) k++;
		if ((array[i][size-1-i]=='X' || array[i][size-1-i]=='O') && array[i][size-1-i]==array[i+1][size-1 - (i+1)]) t++;
		if (k==size-1 || t==size-1) return true;
	}
	return false;
}

bool proverka(char** array, unsigned int size){
	unsigned int k=0;
	for (unsigned int i=0; i<size; i++){
		for (unsigned int j=0; j<size-1; j++){
			if (!(array[i][j]=='X' || array[i][j]=='O')){
				k++;
			}
			if (k>0) return true;
		}
	}
	return false;
}

int main (){
	unsigned int size=read_size(), i=0;
	char **array;
	char op;
	short move;
	bool ok=true, letter=true;
	
	array=pamyat_dlya_matritzi(array, size, size);
	
	show_game(array, size);
	
	while(proverka(array, size)) {
		if(letter==true) op='X';
		else op='O';
		show_available_moves (array, op, size);
		cin >> move;
		if (move == (size*size+1) -i) {
			break;
		}
		while (move<1 || move>(size*size-i)){
			cout << endl << "You can`t use this number, please, try again: ";
			cin >> move;
		}
		ok=making_move (array, move, op, size);
		if (ok!=true) break;
		show_game(array, size);
		if (win_game(array, size)) {
			cout << endl << "Player " << op << " is winner!";
			cin.get();
			return 0;
		}
		letter=!letter;
		i++;
	}
	
	cout << endl << "Thanks for the game!";
	delete_pamyat (array, size);
	cin.get();
	return 0;
}
