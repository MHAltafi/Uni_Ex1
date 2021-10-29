#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <sstream>

using namespace std;

void addmatrix();
void appinfo();
bool option_tokenizer(const string option);
void deletematrix(string **mat, int satr, int sotun, string Name);

struct Matrix
{
    string name;
    string **mat; //string mitoone shamele string, int, double va char mishe age ehtiaj be conversion bashe stod estefade mishe (convert be double ke double am shamele int e)
    int satr;
    int sotun;
};

vector<Matrix> matrixes(0);

vector<string> string_split(const string &option, char delimiter)
{
    //tabe baraye joda kardane commande dade shode ba delimiter dade shode va pushbacke har bakhsh tooye vector
    //(dar yek bakhsh az delimiter ' ' va dar yek bakhsh ',' estefade mishe)

    vector<string> result;
    stringstream stringinsstream(option);
    string item;

    while (getline(stringinsstream, item, delimiter))
    {
        result.push_back(item);
    }

    return result;
}

int main()
{
    cout << "Welcome to the MATRIX APPLICATION!!" << endl;
    string option;
    appinfo();                  //chape moshakhasate barname
    while (option != "end_app") //while baraye daryafte option ta zamani ke mokhalefe end_app bashe
    {
        cout << "enter your command:" << endl;
        getline(cin, option); //cin baraye in ke be space hasas nabashe
        if (option == "end_app") //agar "end_app" bood kharej she, OS ha khodeshoon bad az etmame barname dynamic memory ro delete mikonan, ehtiaji be delete kardan nist
        {
            break;
        }
        option_tokenizer(option); //farakhani tabe asli barname yani option_tokenizer baraye token kardane option va ejraye commande dade shode ba tabe e makhsoos
    }

    return 0;
}

bool namecheckerForAddMatrix(string name) //tabe e ke dar addmatrix estefade mishe ta agar esme tekrari dade shod, false bargardoone
{
    for (auto i : matrixes)
    {
        if (i.name == name)
        {
            return false;
        }
    }
    return true;
}

void addmatrix(string &name, const int satr, const int sotun, string initializes = "")
{
    //dar in tabe matris ezafe mishe va default argument baraye mogheye initialize dar vorudi estefade mishe
    //agar initializes dade beshe, varede else mishe ke string dade shode be forme [x,y,z,...] baraye initialize estefade she
    //agar initializes dade nashe, "" baghi mimoone ke varede else nmishe

    for (auto i : matrixes) //check kardane name matris haye mojud baraye tekrari naboodan
    {
        if (name == i.name)
        {
            while (name == i.name) //agar name tekrari vojud dasht name jadid dade beshe
            {
                cout << "This name is already used for another matrix. Please enter another name : ";
                cin >> name;
                if (namecheckerForAddMatrix) //agar esme dade shode dar tabe namecheckerForAddMatrix peyda nashe, true mishe
                {
                    break;
                }
            }
        }
    }

    Matrix newmat;                   //matrisi be nam newmat az struct matrix misazim
    newmat.name = name;              //gharar dadane name dade shode dar matris
    newmat.satr = satr;              //gharar dadane meghdare satr dar satre dakhele struct
    newmat.sotun = sotun;            //gharar dadane meghdare sotun dar sotune dakhele struct
    newmat.mat = new string *[satr]; //new kardane hafeze baraye bode aval
    for (int i = 0; i < satr; i++)
    {
        newmat.mat[i] = new string[sotun]; //edame new kardane hafeze baraye bode 2vom
    }

    if (initializes == "") //halate default argument
    {
        for (int i = 0; i < satr; i++)
        {
            for (int j = 0; j < sotun; j++)
            {
                printf("enter element for place [%d][%d] : ", i + 1, j + 1);
                cin >> newmat.mat[i][j]; //daryafte matris
            }
        }
        cin.ignore();               //rafe moshkele gereftane vorudi be khatere vojude newline dar cin >>
    }
    else //baraye halati ke command dade shode daraye [x,y,z,...] bashad
    {
        initializes.erase(0, 1);                                          //hazfe khane aval
        initializes.pop_back();                                           //hazfe khane akhar
        vector<string> initializetokens = string_split(initializes, ','); //tokenize kardan ba ,
        initializetokens.shrink_to_fit();
        int k = 0;
        for (int i = 0; i < satr; i++)
        {
            for (int j = 0; j < sotun; j++)
            {
                newmat.mat[i][j] = initializetokens[k]; //gharar dadan khane haye vector dar matris
                k++;
            }
        }
    }
    matrixes.push_back(newmat); //pushback kardane matris dar vector
    matrixes.shrink_to_fit();
}

bool is_number(const string &str) //check kardan baraye adad boodan
{
    int dotcount = 0;
    for (char const &c : str)
    {
        if (c == '.') //shomordane . ha baraye in ke double bashad ya na (agar adad bashad va yek . dashte bashad, adad ast va dar gheyre in soorat adad nist)
        {
            dotcount++;
        }
        if (isdigit(c) == 0)
        {
            if (c == '.' && dotcount == 1)
            {
                continue;
            }
            return false;
        }
    }
    return true;
}

bool is_diagonal(const int &len, string **mat) //tabe ghotri boodane matris
{
    //in tabe faghat baraye matris haye adadie
    int zerocount = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if ((i > j) || (j > i))
            {
                if (mat[i][j] == "0")
                {
                    zerocount++;
                }
            }
        }
    }
    if (zerocount == ((len * len) - len)) //shomareshe tedad sefr haye gheyre ghotri ke bayad barabar ba len^2 - len bashad
    {
        return true;
    }
    return false;
}

bool is_upper_triangular(const int &len, string **mat) //tabe check kardane bala mosalasi boodane matris
{
    //in tabe faghat baraye matris haye adadie
    int zerocount = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (i > j)
            {
                if (mat[i][j] == "0")
                {
                    zerocount++; //shomareshe tedad sefr haye zire ghotre asli
                }
            }
        }
    }
    if (zerocount == (((len * len) - len) / 2)) //tedad sefr haye zire ghotre asli bayad barabar bashad ba: ((len * len) - len) / 2)
    {
        return true;
    }
    return false;
}

bool is_lower_triangular(const int &len, string **mat) //tabe check kardane payeen mosalasi boodane matris
{
    //in tabe faghat baraye matris haye adadie
    int zerocount = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (j > i)
            {
                if (mat[i][j] == "0")
                {
                    zerocount++; //shomareshe tedad ghotr haye balaye ghotre asli
                }
            }
        }
    }
    if (zerocount == (((len * len) - len) / 2)) //tedade sefr haye balaye ghotre asli bayad barabar bashad ba : ((len * len) - len) / 2)
    {
        return true;
    }
    return false;
}

bool is_triangular(const int &len, string **mat) //tabe check kardane mosalasi boodane matris
{
    //in tabe faghat baraye matris haye adadie o az 2 tabe is_upper_triangular o is_lower_triangular estefade mikone
    bool lower = is_lower_triangular(len, mat);
    bool upper = is_upper_triangular(len, mat);
    if (lower == true && upper == true) //halati ke ham bala mosalasi va ham payeen mosalasi ast
    {
        cout << "The matrix is both upper and lower triangular." << endl;
        return true;
    }
    else if (lower) //halati ke faghat payeen mosalasi ast
    {
        cout << "The matrix is only lower triangular." << endl;
        return true;
    }
    else if (upper) //halati ke faghat bala mosalasi ast
    {
        cout << "The matrix is only upper triangular." << endl;
        return true;
    }
    cout << "The matrix is not upper nor lower triangular." << endl; //agar dar if va else if haye bal avared nashe chap mishe ke hich no mosalasi nist
    return false;
}

bool is_identity(const int &len, string **mat) //tabe check kardane hamani boodane matris
{
    //in tabe faghat baraye matris haye adadie
    int zerocount = 0;
    int diagonalOnes = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if ((i > j) || (j > i))
            {
                if (mat[i][j] == "0")
                {
                    zerocount++; //shomareshe tedade sefr hayi ke rooye ghotre asli nistand
                }
            }
            if ((i == j) && (mat[i][j] == "1"))
            {
                diagonalOnes++; //shomareshe 1 haye rooye ghotre asli
            }
        }
    }
    if (zerocount == ((len * len) - len) && (diagonalOnes == len)) //2 shart hamzaman bayad bargharar bashand
    {
        return true;
    }
    return false;
}

bool is_normal_symmetric(const int &len, string **mat) //tabe check kardane motegharen boodane matris
{
    //in tabe ham baraye matris adadi ham string ghabele estefade ast
    //tedade counter dar in tabe 2barabar ast chon ham mat[i][j] check mishe ham vaghti i o j taghir kard, mat[j][i] ham baraye bare dovom check mishe
    int counter = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (mat[i][j] == mat[j][i])
            {
                counter++;
            }
        }
    }
    if (counter == ((len * len) - len))
    {
        return true;
    }
    return false;
}

bool is_skew_symmetric(const int &len, string **mat) //tabe check kardane pad motegharen boodane matris
{
    //in tabe ham baraye matris adadi ham string ghabele estefade ast
    //tabe 4 string motefavet dar nazar migirad ke tamame mavared mesle : 1 va -1 , -1 va 1 ,  qwe va -qwe , -qwe va qwe     mishavad
    //in tabe ham mesle tabe normal symmetric tedade counter 2barabar ast
    int counter = 0;
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (i == j)
            {
                continue;
            }
            string x = mat[i][j];
            string y = "-" + mat[j][i];
            string a = mat[j][i];
            string b = "-" + mat[i][j];
            if (x == y || a == b)
            {
                counter++;
            }
        }
    }
    if (counter == ((len * len) - len)) //tedade counter bayad barabar ba  (len * len) - len) bashad
    {
        return true;
    }
    return false;
}

bool is_symmetric(const int &len, string **mat) //tabe check kardane noe tagharone matris
{
    //ba estefade az farakhani 2 tabe ghabl, noe tagharon tashkhis dade mishavad, ham zaman matris nmiatoone har 2 noe tagharon ro dashte bashe
    bool normal = is_normal_symmetric(len, mat);
    bool skew = is_skew_symmetric(len, mat);

    if (skew)
    {
        cout << "The matrix is skew symmetric." << endl; //pad motegharen boodan
        return true;
    }

    if (normal)
    {
        cout << "The matrix is normal symmetric." << endl; //motegharen boodan
        return true;
    }

    cout << "The matrix is not skew nor normal symmetric." << endl; // na motegharen va na pad motegharen boodan
    return false;
}

void inverse(const int &len, string **mat, string newmatrixname = "") //tabe inverse kardane matris be 2 halat
{
    if (newmatrixname == "") //baraye halati ke mikhaim khode matris inverse she
    {
        for (size_t i = 0; i < len; i++)
        {
            for (size_t j = 0; j < len; j++)
            {
                if (i < j)
                {
                    string temp = mat[j][i]; //estefade az string temp
                    mat[j][i] = mat[i][j];
                    mat[i][j] = temp;
                }
            }
        }
        cout << "Matrix inversed successfully." << endl;
    }
    else //ye string ba jaye baraxe i o j  dar nazar migirim ke befrestim be newmatrix ta matris jadid sakhte beshe (be forme [a,b,...])
    {
        string sendtonewmat = "[";
        for (size_t i = 0; i < len; i++)
        {
            for (size_t j = 0; j < len; j++)
            {
                sendtonewmat.append(mat[j][i]);
                if (i == (len - 1) && j == (len - 1)) //mikhaim ke akhare string [...,x,y,] nashe o [...,x,y] beshe
                {
                }
                else
                {
                    sendtonewmat.append(",");
                }
            }
        }
        sendtonewmat.append("]");
        addmatrix(newmatrixname, len, len, sendtonewmat);
        cout << "New inversed matrix was made successfully." << endl;
    }
}

void showmatrix(const int &satr, const int &sotun, string **const &mat, string &name) //tabe namayeshe matris
{
    //tabe matris ra chap mikonad
    cout << "Matrix name : " << name << endl;
    for (size_t i = 0; i < satr; i++)
    {
        for (size_t j = 0; j < sotun; j++)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

void deletematrix(string **mat, int satr, int sotun, string Name) //tabe hazfe matris
{
    //dar in tabe hafeze hayi ke moghe sakhtane matris new shode bood, delete mishavad va structe marboot be matris az vector hazf mishavad
    for (size_t i = 0; i < satr; i++)
    {
        delete[] mat[i]; //delete bode 2vom
    }
    delete[] mat; //delete bode aval

    for (size_t i = 0; i < matrixes.size(); i++)
    {
        if (matrixes[i].name == Name)
        {
            matrixes.erase(matrixes.begin() + i); //hazfe structe marboot be matris
        }
    }
}

void change(string **mat, const int &satr, const int &sotun, const string &newvalue) //tabe avaz kardane yek khane az yek matris
{
    mat[satr - 1][sotun - 1] = newvalue;
}

void appinfo() //tabe informatione dastoorat
{
    cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Templates of commands that could be used in this application :" << endl;
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

bool option_tokenizer(const string option) //tabeE token kardan va tashkhise noe dastoore vared shode
{
    //dar in tabe bar asase template commandha(sakhtar haye command ha) va makane gharar giri dar vector, tavabe makhsoose har command farakhani mishe
    vector<string> optiontokens = string_split(option, ' '); //token kardan va gharar dadan dar vector ba tabe string_split va delimitere ' '
    optiontokens.shrink_to_fit();                            //shrink

    //check kardane dastoorat , sharte vorud be halghe, dorost boodane noe dastoore vorudie ke dar khate zir check mishe dastoor vojud dare ya na
    if ((optiontokens[0] == "add" && optiontokens[1] == "matrix") || (optiontokens[0] == "is_diagonal" || "is_upper_triangular" || "is_lower_triangular" || "is_triangular" || "is_identity" || "is_normal_symmetric" || "is_skew_symmetric" || "is_symmetric" || "inverse" || "show" || "delete" || "change"))
    {
        if (optiontokens[0] == "add" && optiontokens[1] == "matrix") //farakhani tabe marboot be add dar halat haye mokhtalef
        {
            if (optiontokens.size() == 2) //halati ke faghat dastoore add matrix neveshte shode bashad
            {
                cout << "Enter the Matrix Name : ";
                string name;
                cin >> name;
                cout << "Enter the number of Lines : ";
                int satr;
                cin >> satr;
                cout << "Enter the number of Columns : ";
                int sotun;
                cin >> sotun;
                addmatrix(name, satr, sotun);

                return true;
            }

            if (optiontokens.size() == 3) //halati ke tedade satr o sotun dade nmishavad
            {
                cout << "Enter the number of Lines : ";
                int satr;
                cin >> satr;
                cout << "Enter the number of Columns : ";
                int sotun;
                cin >> sotun;
                addmatrix(optiontokens[2], satr, sotun);

                return true;
            }

            if (optiontokens.size() == 4) //halati ke matris morabaE va initialize dar vorudi dade nmishavad
            {
                addmatrix(optiontokens[2], stoi(optiontokens[3]), stoi(optiontokens[3])); //estefade az stoi chon avalesh be halate stringe o bayad be int tabdil she

                return true;
            }

            if (optiontokens.size() == 5) //2 halat
            {
                string temp = optiontokens[4];
                char x = temp.at(0);
                if (isdigit(x)) //halati ke satr o sotun dade shode va initialize dade nmishavad
                {
                    addmatrix(optiontokens[2], stoi(optiontokens[3]), stoi(optiontokens[4])); //estefade az stoi chon avalesh be halate stringe o bayad be int tabdil she

                    return true;
                }
                else // halati ke matris morabaE va initialize dade mishavad
                {
                    addmatrix(optiontokens[2], stoi(optiontokens[3]), stoi(optiontokens[3]), optiontokens[4]); //estefade az stoi chon avalesh be halate stringe o bayad be int tabdil she

                    return true;
                }
            }

            if (optiontokens.size() == 6) // halati ke satr o sotun dade shode va initialize niz dade mishavad
            {
                addmatrix(optiontokens[2], stoi(optiontokens[3]), stoi(optiontokens[4]), optiontokens[5]); //estefade az stoi chon avalesh be halate stringe o bayad be int tabdil she
                return true;
            }
        }

        if (optiontokens[0] == "is_diagonal") //farakhani tabe marboot be ghotri boodan
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {

                    if (i.satr == i.sotun) //sharte morabaE boodan
                    {
                        int count = 0; //tarif shode baraye check kardane adad boodane matris ba estefade az tabe is_number
                        for (size_t j = 0; j < i.satr; j++)
                        {
                            for (size_t k = 0; k < i.sotun; k++)
                            {
                                if (is_number(i.mat[j][k]))
                                {
                                    count++;
                                }
                            }
                        }
                        if (count == i.satr * i.sotun) //agar adad bashad va count(tedade adad ha) ba zarbe satr o sotun barabar bashad vared mishavad
                        {
                            if (is_diagonal(i.satr, i.mat)) //check kardane ghotri boodan
                            {
                                cout << "The matrix is diagonal." << endl;
                                return true;
                            }
                            else
                            {
                                cout << "The matrix isn't diagonal." << endl;
                                return true;
                            }
                        }
                        else
                        {
                            cout << "The matrix is not numbers, so it can't be checked for being diagonal." << endl; //adad naboodane matris
                            return false;
                        }
                    }
                    else
                    {
                        cout << "The matrix isn't a square matrix, so it can't be checked for being diagonal." << endl; //morabaE naboodane matris
                        return false;
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "is_upper_triangular") //farakhani tabe marboot be bala mosalasi boodan
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    if (i.satr == i.sotun) //sharte morabaE boodan
                    {
                        int count = 0; //tarif shode baraye check kardane adad boodane matris ba estefade az tabe is_number
                        for (size_t j = 0; j < i.satr; j++)
                        {
                            for (size_t k = 0; k < i.sotun; k++)
                            {
                                if (is_number(i.mat[j][k]))
                                {
                                    count++;
                                }
                            }
                        }
                        if (count == i.satr * i.sotun) //agar adad bashad va count(tedade adad ha) ba zarbe satr o sotun barabar bashad vared mishavad
                        {
                            if (is_upper_triangular(i.satr, i.mat)) //farakhani tabe is_upper_triangular
                            {
                                cout << "The matrix is upper triangular." << endl; //bala mosalasi boodan
                                return true;
                            }
                            else
                            {
                                cout << "The matrix isn't upper triangular." << endl; //bala mosalasi naboodan
                                return true;
                            }
                        }
                        else
                        {
                            cout << "The matrix is not numbers, so it can't be checked for being being upper triangular." << endl; //adad naboodane matris
                            return false;
                        }
                    }
                    else
                    {
                        cout << "The matrix isn't a square matrix, so it can't be checked for being upper triangular." << endl; //morabaE naboodane matris
                        return false;
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "is_lower_triangular") //farakhani tabe marboot be payeen mosalasi boodan
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    if (i.satr == i.sotun) //sharte morabaE boodan
                    {
                        int count = 0; //tarif shode baraye check kardane adad boodane matris ba estefade az tabe is_number
                        for (size_t j = 0; j < i.satr; j++)
                        {
                            for (size_t k = 0; k < i.sotun; k++)
                            {
                                if (is_number(i.mat[j][k]))
                                {
                                    count++;
                                }
                            }
                        }
                        if (count == i.satr * i.sotun) //agar adad bashad va count(tedade adad ha) ba zarbe satr o sotun barabar bashad vared mishavad
                        {
                            if (is_lower_triangular(i.satr, i.mat)) //farakhani tabe
                            {
                                cout << "The matrix is lower triangular." << endl; //payeen mosalasi boodan
                                return true;
                            }
                            else
                            {
                                cout << "The matrix isn't lower triangular." << endl; //payeen mosalasi naboodan
                                return true;
                            }
                        }
                        else
                        {
                            cout << "The matrix is not numbers, so it can't be checked for being being lower triangular." << endl; //adad naboodane matris
                            return false;
                        }
                    }
                    else
                    {
                        cout << "The matrix isn't a square matrix, so it can't be checked for being lower triangular." << endl; //morabaE naboodane matris
                        return false;
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "is_triangular") //farakhani tabe marboot be mosalasi boodan
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    if (i.satr == i.sotun) //sharte morabaE boodan
                    {
                        int count = 0; //tarif shode baraye check kardane adad boodane matris ba estefade az tabe is_number
                        for (size_t j = 0; j < i.satr; j++)
                        {
                            for (size_t k = 0; k < i.sotun; k++)
                            {
                                if (is_number(i.mat[j][k]))
                                {
                                    count++;
                                }
                            }
                        }
                        if (count == i.satr * i.sotun) //agar adad bashad va count(tedade adad ha) ba zarbe satr o sotun barabar bashad vared mishavad
                        {
                            is_triangular(i.satr, i.mat); //farakhani tabe
                            return true;
                        }
                        else
                        {
                            cout << "The matrix is not numbers, so it can't be checked for being being triangular." << endl; //adad naboodane matris
                            return false;
                        }
                    }
                    else
                    {
                        cout << "The matrix isn't a square matrix, so it can't be checked for being triangular." << endl; //morabaE naboodane matris
                        return false;
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "is_identity") //farakhani tabe marboot be hamani boodan
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    if (i.satr == i.sotun) //sharte morabaE boodan
                    {
                        int count = 0; //tarif shode baraye check kardane adad boodane matris ba estefade az tabe is_number
                        for (size_t j = 0; j < i.satr; j++)
                        {
                            for (size_t k = 0; k < i.sotun; k++)
                            {
                                if (is_number(i.mat[j][k]))
                                {
                                    count++;
                                }
                            }
                        }
                        if (count == i.satr * i.sotun) //agar adad bashad va count(tedade adad ha) ba zarbe satr o sotun barabar bashad vared mishavad
                        {
                            if (is_identity(i.satr, i.mat)) //farakhani tabe
                            {
                                cout << "The matrix is identity." << endl; //hamani boodan
                                return true;
                            }
                            else
                            {
                                cout << "The matrix isn't identity." << endl; //hamani naboodan
                                return true;
                            }
                        }
                        else
                        {
                            cout << "The matrix is not numbers, so it can't be checked for being being identity." << endl; //adad naboodane matris
                            return false;
                        }
                    }
                    else
                    {
                        cout << "The matrix isn't a square matrix, so it can't be checked for being identity." << endl; //morabaE naboodane matris
                        return false;
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "is_normal_symmetric") //farakhani tabe marboot be motegharen boodan (inja adad boodan ya naboodane matris mohem nist)
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    if (i.satr == i.sotun) //sharte morabaE boodan
                    {
                        if (is_normal_symmetric(i.satr, i.mat)) //farakhani tabe
                        {
                            cout << "The matrix is normal symmetric." << endl; //motegharen boodan
                            return true;
                        }
                        else
                        {
                            cout << "The matrix isn't normal symmetric." << endl; //motegharen naboodan
                            return true;
                        }
                    }
                    else
                    {
                        cout << "The matrix isn't a square matrix, so it can't be checked for being normal symmetric." << endl; //morabaE naboodane matris
                        return false;
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "is_skew_symmetric") //farakhani tabe marboot be pad motegharen boodan(inja adad boodan ya naboodan matris mohem nist)
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    if (i.satr == i.sotun) //sharte morabaE boodan
                    {
                        if (is_skew_symmetric(i.satr, i.mat)) //farakhani tabe
                        {
                            cout << "The matrix is skew symmetric." << endl; //pad motegharen boodan
                            return true;
                        }
                        else
                        {
                            cout << "The matrix isn't skew symmetric." << endl; //pad motegharen naboodan
                            return true;
                        }
                    }
                    else
                    {
                        cout << "The matrix isn't a square matrix, so it can't be checked for being skew symmetric." << endl; //morabaE naboodane matris
                        return false;
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "is_symmetric") //farakhani tabe marboot be check kardane noe tagharon
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    if (i.satr == i.sotun) //sharte morabaE boodan
                    {
                        is_symmetric(i.satr, i.mat); //farakhani tabe
                        return true;
                    }
                    else
                    {
                        cout << "The matrix isn't a square matrix, so it can't be checked for being symmetric." << endl; //morabaE naboodane matris
                        return false;
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "inverse") //farakhni tabe marboot be inverse kardane matris
        {
            //dar in halat ba tavajoh be size vector baraye farakhani tasmim gerefte mishe ke aya inverse dar ja bashad ya matris jadid ijad shavad
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    if (optiontokens.size() == 2) //halati ke inverse dar ja bashad
                    {
                        if (i.satr == i.sotun) //sharte morabaE boodane matris
                        {
                            inverse(i.satr, i.mat); //farakhani tabe (default argument dare o 3vomi dade nashode)
                            return true;
                        }
                        else
                        {
                            cout << "The matrix isn't a square matrix, so it can't be inversed." << endl; //morabaE naboodane matris
                            return false;
                        }
                    }
                    if (optiontokens.size() == 3) //halati ke inverse dar matris jadidi bashad
                    {
                        if (i.satr == i.sotun) //sharte morabaE boodane matris
                        {
                            inverse(i.satr, i.mat, optiontokens[2]); //farakhani tabe bedoone estefade az default argument
                            return true;
                        }
                        else
                        {
                            cout << "The matrix isn't a square matrix, so it can't be inversed." << endl; //morabaE naboodane matris
                            return false;
                        }
                    }
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "show") //farakhani tabe marboot be chape matris
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    showmatrix(i.satr, i.sotun, i.mat, i.name); //farakhani tabe
                    return true;
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "delete") //farakhani tabe marboot be delete kardane matris
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    deletematrix(i.mat, i.satr, i.sotun, i.name); //farakhani tabe
                    cout << "Matrix deleted successfully." << endl;
                    return true;
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }

        if (optiontokens[0] == "change") //farakhani tabe marboot be taghire yek khane az matris
        {
            for (auto i : matrixes) //check kardane name vorudi ba name haye mojud dar vector struct ha
            {
                if (optiontokens[1] == i.name) //sharte vojude name
                {
                    change(i.mat, stoi(optiontokens[2]), stoi(optiontokens[3]), optiontokens[4]); //farakhani tabe (estefade az stoi baraye tabdile string be int)
                    cout << "Successfully changed." << endl;
                    return true;
                }
            }
            cout << "No such matrix name found." << endl; //peyda nashodane esme matris
            return false;
        }
    }

    cout << "No such command found." << endl; //commande eshtebah
    return false;
}
