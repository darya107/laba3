#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int selectWorkType(string text)
{
    int choice;
    bool isInCorrect;
    choice = 1;
    cout << text;
    do {
        isInCorrect = false;
        cin >> choice;
        if (cin.fail())
        {
            isInCorrect = true;
            cout << "Ошибка! Выбирите из предложенных вариантов:" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        if (!isInCorrect && (choice != 1) && (choice != 2))
        {
            isInCorrect = true;
            cout << "Ошибка! Выбирите из предложенных вариантов:" << endl;

        }
        if (!isInCorrect && cin.get() != '\n')
        {
            cout << "Ошибка! Выбирите из предложенных вариантов:" << endl;
            isInCorrect = true;
            cin.clear();
            while (cin.get() != '\n');

        }
    } while (isInCorrect);

    return choice;
}
int enterN()
{
    int n;
    const int MIN_N = 0;
    const int MAX_N = 100;
    bool isInCorrect;
    do
    {
        isInCorrect = false;
        cin >> n;
        if (cin.fail())
        {
            isInCorrect = true;
            cout << "Ошибка! Проверьте правильность ввода!!!: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        if (!isInCorrect && (n > MAX_N) || (n < MIN_N))
        {
            isInCorrect = true;
            cout << "Число не входит в диапазон!";
        }
        if (!isInCorrect && cin.get() != '\n')
        {
            cout << "Ошибка! Выбирите из предложенных вариантов:" << endl;
            isInCorrect = true;
            cin.clear();
            while (cin.get() != '\n');

        }
    } while (isInCorrect);
    return n;
}
bool isFileExist(string path) {
    fstream InFile(path);
    if (InFile.is_open()) {
        InFile.close();
        return true;
    }
    return false;
}

bool isTextFile(string path) {
    bool isTxt;
    isTxt = false;
    if ((path[path.length() - 1] == 't') && (path[path.length() - 2] == 'x') &&
        (path[path.length() - 3] == 't') && (path[path.length() - 4] == '.'))
        isTxt = true;
    return isTxt;
}
string inputFilePath()
{
    string path;
    bool isInCorrect;
    do
    {
        isInCorrect = false;
        cin >> path;
        if (!(isTextFile(path)))
        {
            isInCorrect = true;
            cout << "Неправильное расширение файла.Повторите ввод : ";
        }
        else
        {
            if (!isFileExist(path)) 
            {
                isInCorrect = true;
                cout << "Файл недоступен.Повторите ввод : ";
            }

        }
    } while (isInCorrect);
    return path;
}
bool isFileReadable(string path) {
    bool isReadable;
    isReadable = false;
    ifstream InFile(path);
    if (InFile.good()) {
        InFile.close();
        isReadable = true;
    }
    return isReadable;
}
bool isFileWritable(string path) {
    ofstream Res(path);
    if (Res.good()) {
        Res.close();
        return true;
    }
    return false;
}

string inputReadPath()
{
    string path;
    bool isInCorrect;
    ifstream InFile;
    do
    {
        isInCorrect = false;
        path = inputFilePath();
        InFile.open(path);
        if (!isFileReadable(path))
        {
        isInCorrect: true;
            cout << "Программа не может прочиать файл.попробуйте снова";
        }
        else
            isInCorrect = false;
    } while (isInCorrect);
    return path;
}

int** readMatrixInFile(ifstream& InFile, int rows, int cols) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(InFile >> matrix[i][j])) {
                cout << "Ошибка: недостаточно данных в файле" << endl;
                for (int k = 0; k <= i; k++) {
                    delete[] matrix[k];
                }
                delete[] matrix;
                return nullptr; // Возвращаем nullptr, если произошла ошибка
            }
        }
    }
    return matrix; 
}

int** readMatrixFile(int& rows, int& cols) {
    string pathToFile;
    int** matrix = nullptr;
    bool correctInputSize = false;

    while (!correctInputSize) {
        cout << "Введите путь к файлу для матрицы: ";
        pathToFile = inputReadPath();
        ifstream InFile(pathToFile);

        if (InFile.is_open()) {
            InFile >> rows;
            InFile >> cols;
            correctInputSize = true;
            matrix = readMatrixInFile(InFile, rows,cols);
            if (!matrix) {
                cout << "Ошибка при чтении данных матрицы. Попробуйте ещё раз." << endl;
                correctInputSize = false; 
            }
            InFile.close();
        }
        else {
            cout << "Ошибка при открытии файла. Попробуйте ещё раз." << endl;
        }
    }
    return matrix;
}

int** enterMatrixInConsole(int rows, int cols)
{
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    bool isInCorrect;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            do
            {
                isInCorrect = false;
                cout << "Введите элемент матрицы Matrix[" << i + 1 << "," << j + 1 << "]:" << endl;
                cin >> (matrix[i][j]);
                if (cin.fail() || cin.get() != '\n') {
                    cerr << "Ошибка! Введите корректное значение:\n";
                    cin.clear();
                    while (cin.get() != '\n');
                    isInCorrect = true;
                }
            } while (isInCorrect);
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}
string recordResult()
{
    string path;
    bool isInCorrect;
    do
    {
        cout << " Введите путь к файлу для записи результата :" << endl;
        isInCorrect = false;
        path = inputFilePath();
        ofstream Res(path);
        if (!isFileWritable(path))
        {
            cout << "Программа не может записать в файл.попробуйте снова" << endl;
            isInCorrect = true;
        }
        else
        {
            isInCorrect = false;
        }
        Res.close();
    } while (isInCorrect);
    return path;
}
void writeResultInFile(int** matrix, int rows, int cols)
{
    bool isInCorrect;
    ofstream Res;
    Res.open(recordResult());
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            Res << matrix[i][j]<< " ";
        }
        Res << "\n ";

    }
    Res.close();
    cout << "Ответ записан\n";
}
int findMax(int* arr, int cols)
{
    int max = arr[0];
    for (int i = 1; i < cols; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}
int findMin(int* arr, int cols)
{
    int min = arr[0];
    for (int i = 1; i < cols; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}
void sortRow(int* arr, int cols)
{
    int maxElement = findMax(arr, cols);
    int minElement = findMin(arr, cols);

    int sizeCounts = maxElement - minElement + 1;
    int* counts = new int[sizeCounts] {};

    for (int i = 0; i < cols; i++)
    {
        counts[arr[i] - minElement]++;
    }


    int currentIndex = 0;
    for (int val = 0; val < sizeCounts; val++)
    {
        int countValue = counts[val];
        for (int i = 0; i < countValue; i++)
        {
            arr[currentIndex++] = val + minElement;

        }

    }

    delete[] counts;
    counts = NULL;
}
void sortRowsLastElements(int** matrix, int sizeRows, int sizeCols)
{
    for (int i = 1; i < sizeRows; i++)
    {
        for (int j = 0; j < sizeRows - i; j++)
        {
            if (matrix[j][sizeCols - 1] < matrix[j + 1][sizeCols - 1])
            {
                int* temp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp;
            }
        }
    }
}


void sort(int** matrix, int sizeRows, int sizeCols)
{
    for (int i = 0; i < sizeRows; i++)
    {
        sortRow(matrix[i], sizeCols);
    }
    sortRowsLastElements(matrix, sizeRows, sizeCols);
}





int main()
{
    int rows = 0;
    int cols = 0;
    string textInput;
    string textOutput;
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    cout << "Упорядочить в порядке возрастания элементы строк данной матрицы, после чего упорядочить строки по убыванию последних элементов полученных строк. Используйте сортировку подсчётом.\n";
    textInput = "Как вы хотите ввести матрицу, через консоль или использовать файл ? (1 - консоль, 2 - файл)";
    if (selectWorkType(textInput) == 1)
    {
        cout << "Введите количество строк матрицы\n";
        rows = enterN();
        cout << "Введите количество столбцов матрицы\n";
        cols = enterN();
        matrix = enterMatrixInConsole(rows,cols);
        printMatrix(matrix,rows,cols);
    }
    else
    {
        matrix = readMatrixFile(rows,cols);
    }
    sort(matrix, rows, cols);
    textOutput = "Как вы хотите вывести результат, через консоль или использовать файл ? (1 - консоль, 2 - файл)";
    if (selectWorkType(textOutput) == 1)
    {
       
            cout << "Отсортированная матрица:\n ";
            printMatrix(matrix, rows, cols);
      
    }
    else
    {
        writeResultInFile(matrix,rows,cols);
    }
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}
 