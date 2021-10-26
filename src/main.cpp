#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <sstream>

using namespace std;

void addmatrix();
void appinfo();
void option_tokenizer (string option);

struct Matrix
{
    string name;
    string **mat; //string mitoone shamele string, int, double va char mishe age ehtiaj be conversion bashe stod estefade mishe (convert be double ke double am shamele int e)
    int satr;
    int sotun;
};

vector <Matrix> matrixes (0);

vector<string> string_split (const string &option , char delimiter) {
    //char delimiter = ' ';
    vector<string> result;
    stringstream stringinsstream (option);
    string item;

    while (getline (stringinsstream, item, delimiter)) {
        result.push_back (item);
    }

    return result;
}


int main()
{   
    cout << "Welcome to the MATRIX APPLICATION!!" << endl;
    string option;
    while (option != "end_app")
    {   
        appinfo();
        getline(cin , option);
        option_tokenizer(option);
    }
    /*cout << "size " << matrixes.size() << endl;
    cout << " cap " << matrixes.capacity() << endl;
    cout << matrixes[0].name << endl;
    for (int i = 0; i < matrixes[0].satr; i++)
    {
        for (int j = 0; j < matrixes[0].sotun; j++)
        {   
            cout << matrixes[0].mat[i][j] << "\t";
        }
        cout << endl;
    }
    
*/
    return 0;
}


void addmatrix(string name, int satr , int sotun , string initializes = "") //dar in tabe matris ezafe mishe
{   
    Matrix newmat; //matrisi be nam newmat az struct matrix misazim
    //cout << "name : ";
    newmat.name = name;
    //cout << "satr : ";
    newmat.satr = satr; //gharar dadane meghdare satr dar satre dakhele struct
    //cout << "sotun : ";
    //cin >> sotun;
    newmat.sotun = sotun; //gharar dadane meghdare sotun dar sotune dakhele struct
    newmat.mat = new string*[satr]; //new kardane hafeze baraye bode aval
    for(int i = 0; i < satr; ++i)
    {
        newmat.mat[i] = new string[sotun]; //edame new kardane hafeze baraye bode 2vom
    }
    if(initializes == "")
    {
        for (int i = 0; i < satr; i++)
        {
            for (int j = 0; j < sotun; j++)
            {   
                printf("enter number for place [%d][%d] : ", i+1 , j+1); 
                cin >> newmat.mat[i][j]; //daryafte matris
            }
        }
    }
    else
    {   
        initializes.erase(0,1);
        initializes.pop_back();
        vector <string> initializetokens = string_split(initializes , ',');
        initializetokens.shrink_to_fit();
        int k = 0;
        for (int i = 0; i < satr; i++)
        {
            for (int j = 0; j < sotun; j++)
            {   
                newmat.mat[i][j] = stod(initializetokens[k]);
                k++;
            }
        }
    }
    
    matrixes.push_back(newmat); //pushback kardane matris dar vector
    
}

void MenuOptions()
{
    vector<string> menu_options{"add matrix", "is_diagonal", "is_upper_triangular", "is_lower_triangular", "is_triangular", "is_identity", "is_normal_symmetric",
                                "is_skew_symmetric", "is_symmetric", "inverse", "show", "delete", "change", "end_app"};

    string chosen_option = "vorud";
    while (chosen_option != "end_app")
    {
        cout << "Please choose your option:" << endl;
        getline(cin, chosen_option);
        for (auto const &check_option : menu_options) // const & baraye sorate bala va jelogiri az taghir
        {
            if (chosen_option == check_option)
            {
                if (chosen_option == "add matrix")
                {
                    //addmatrix();
                }
            }
        }
    }
}

bool is_diagonal( int len , string** mat) //tabe ghotri boodane matris
{
    int zerocount = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if((i > j) || (j > i))
            {
                if(mat[i][j] == "0")
                {
                    zerocount++;
                }
            }
            
        }
        
    }
    if(zerocount == ((len*len)-len)) //shomareshe tedad sefr haye gheyre ghotri ke bayad barabar ba len^2 - len bashad
    {
        return true;
    }
    return false;
}


bool is_upper_triangular( int len , string** mat) //
{
    int zerocount = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
         if (i > j)
         {
            if(mat[i][j] == "0")
            {
                zerocount++;
            }

         }   

        }
        
    }
    if (zerocount == (((len*len)-len)/2))
    {
        return true;
    }
    return false;

}

bool is_lower_triangular(int len , string** mat) 
{
    int zerocount = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
         if (j > i)
         {
            if(mat[i][j] == "0")
            {
                zerocount++;
            }

         }   

        }
        
    }
    if (zerocount == (((len*len)-len)/2))
    {
        return true;
    }
    return false;

}

bool is_triangular(int len , string** mat) 
{
    bool lower = is_lower_triangular(len ,mat); 
    bool upper = is_upper_triangular(len ,mat);
    if(lower == true && upper == true)
    {
        cout << "is both upper and lower triangular" << endl;
        return true;
    }
    if(lower)
    {
        cout << "is lower triangular" << endl;
    }
    if(upper)
    {
        cout << "is upper triangular" << endl;
    }
    return false;
}

bool is_identity(int len , string** mat)
{
    int zerocount = 0;
    int diagonalOnes = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if((i > j) || (j > i))
            {
                if(mat[i][j] == "0")
                {
                    zerocount++;
                }
            }
            if ((i == j) && (mat[i][j] == "1"))
            {
                diagonalOnes++;
            }
            
        }
        
    }
    if(zerocount == ((len*len)-len) && (diagonalOnes == len))
    {
        return true;
    }
    return false;
}

bool is_normal_symmetric(int len , string** mat) //dobar mishmore
{
    int counter = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if(i == j)
            {
                continue;
            }
            if (mat[i][j] == mat[j][i])
            {
                counter++;
            }
        }
        
    }
    if (counter == ((len*len) - len))
    {
        return true;
    }
    return false;
}

bool is_skew_symmetric(int len , string** mat)
{
    int counter = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if(i == j)
            {
                continue;
            }
            if (stod(mat[i][j]) == -stod(mat[j][i]))
            {
                counter++;
            }
        }
        
    }
    if (counter == ((len*len) - len))
    {
        return true;
    }
    return false;
}

bool is_symmetric(int len , string** mat)
{
    bool normal = is_normal_symmetric(len, mat);
    bool skew = is_skew_symmetric(len, mat);

    if(skew)
    {
        cout << "is skew symmetric" << endl;
        return true;
    }

    if(normal)
    {
        cout << "is normal symmetric" << endl;
        return true;
    }

    cout << "is not skew or normal symmetric" << endl;
    return false;
}

void inverse(int len , string** mat)
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (i < j)
            {
                string temp = mat[j][i];
                mat[j][i] = mat[i][j];
                mat[i][j] = temp;
            }
        }
        
    }
}

void showmatrix(int satr , int sotun , string** const mat)
{
    cout << "name : " << endl;
    for (size_t i = 0; i < satr; i++)
    {
        for (size_t j = 0; j < sotun; j++)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

void deletematrix(string name)
{

}

void change()
{

}

void appinfo()
{
    cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Templates to use in this application :" << endl;
    cout << "1 - Add matrix :" << endl;
    cout << "    add matrix Name Line Column                                       For example : add matrix first_mat 4 7" << endl;
    cout << "    add matrix Name Line Column (initialize numbers)[1,2,...]         For example : add matrix secondmat 2 3 [1,2,3,4,5,22]" << endl;
    cout << "    add matrix Name SquareMatrixNumber                                For example : add matrix third_mat 5" << endl;
    cout << "    add matrix Name SquareMatrixNumber (initialize numbers)[1,2,...]  For example : add matrix fourthmat 2 [4,6,7,1085]" << endl;
    cout << "2 - Diagonal check :" << endl;
    cout << "    is_diagonal Name                                                  For example : is_diagonal fisrt_mat" << endl;
    cout << "3 - Triangular check templates :" << endl;
    cout << "    is_upper_triangular Name                                          For example : is_upper_triangular secondmat" << endl;
    cout << "    is_lower_triangular Name                                          For example : is_lower_triangular secondmat" << endl;
    cout << "    is_triangular Name                                                For example : is_triangular secondmat" << endl;
    cout << "4 - Identity check :" << endl;
    cout << "    is_identity Name                                                  For example : is_identity first_mat" << endl;
    cout << "5 - Symmetric check :" << endl;
    cout << "    is_normal_symmetric Name                                          For example : is_normal_symmetric first_mat" << endl;
    cout << "    is_skew_symmetric Name                                            For example : is_skew_symmetric first_mat" << endl;
    cout << "    is_symmetric Name                                                 For example : is_symmetric first_mat" << endl;
    cout << "6 - Inverse :" << endl;
    cout << "    inverse Name (Saves the inverse in the original matrix)           For example : inverse first_mat" << endl;
    cout << "    inverse Name NewName (Saves the inversed matrix in a new matrix)  For example : inverse first_mat new_mat" << endl;
    cout << "7 - Show matrix :" << endl;
    cout << "    show Name                                                         For example : show first_mat" << endl;
    cout << "8 - Delete matrix :" << endl;
    cout << "    delete Name                                                       For example : delete first_mat" << endl;
    cout << "9 - Change a value in matrix :" << endl;
    cout << "    change Line Column NewValue                                       For example : change first_mat 2 1 132" << endl;
    cout << "0 - Enter the phrase \"end_app\" to end the program." << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
}

void option_tokenizer (string option)
{
    cout << "enter your option" << endl;
    vector <string> optiontokens = string_split(option , ' ');
    optiontokens.shrink_to_fit();

    //check kardane dastoorat

    if (optiontokens[0] == "add")
    {
        if(optiontokens.size() == 2)
        {   
            cout << "Enter the Matrix Name : ";
            string name;
            cin >> name;
            cout << "Enter the number of Lines : " ;
            int satr;
            cin >> satr;
            cout << "Enter the number of Columns : ";
            int sotun;
            cin >> sotun;
            addmatrix(name , satr , sotun);

        }

        if(optiontokens.size() == 3)
        {   
            cout << "Enter the number of Lines : " ;
            int satr;
            cin >> satr;
            cout << "Enter the number of Columns : ";
            int sotun;
            cin >> sotun;
            addmatrix(optiontokens[2] , satr , sotun);

        }

        if(optiontokens.size() == 4) //halati ke matris morabaE va initialize dar vorudi dade nmishavad
        {
            addmatrix(optiontokens[2] , stoi(optiontokens[3]) , stoi(optiontokens[3]));

        }

        if(optiontokens.size() == 5) //2 halat
        {
            if (stod(optiontokens[4])) //halati ke satr o sotun dade shode va initialize dade nmishavad
            {
                addmatrix(optiontokens[2] , stoi(optiontokens[3]) , stoi(optiontokens[4]));

            }
            else // halati ke matris morabaE va initialize dade mishavad
            {
                addmatrix(optiontokens[2] , stoi(optiontokens[3]) , stoi(optiontokens[3]) , optiontokens[4]);

            }  
        }

        if(optiontokens.size() == 6) // halati ke satr o sotun dade shode va initialize niz dade mishavad
        {
            addmatrix(optiontokens[2] , stoi(optiontokens[3]) , stoi(optiontokens[4]) , optiontokens[5]);

        }
    }
}

