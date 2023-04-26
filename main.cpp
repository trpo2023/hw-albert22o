#include <fstream>
#include <iostream>
#include <string>

class Figure {};

struct Curcle {
    int _number;
    float _radius;
    float _point_x;
    float _point_y;
};
class Triangle {};
class Polygon {};

// Пропускает пустые символы
int SkipSpace(std::string& line)
{
    int count = 0; // Счетчик для символов
    while (line[0] == ' ') {
        line.erase(0, 1);
        count++;
    } // Если символ кустой - Мы его пропускаем и увеличиваем счетчик на 1
    return count; // Возвращаем количество пустых символов
}
// Проверяет на равество не зависимо от регистра (проверять слово в нижнем регистре)
bool Compare(std::string word1, std::string& line, int& errorind)
{
    int size = word1.length();                // Размер слова
    std::string word2 = line.substr(0, size); // Вырезает слово из строки
    for (char x : word2)
        x = tolower(x); // Переводит его в нижний регистр
    if (word1 == word2) {    // Если слова равны
        line.erase(0, size); // то удаляет слово
        errorind += size;    // Увеличивает индекс ошибки
        return true;         // и возвращает true
    }
    return false; // Иначе - false
}
// Проверяет строку на число и получет его
bool GetDigit(std::string& line, int& errorind, float& digit)
{
    std::string digitstr;
    bool pointexist = false;
    if (!isdigit(line[0]))
        return false;
    while ((isdigit(line[0]) || ((line[0] == '.') && (!pointexist)))) {
        if (line[0] == '.')
            pointexist = true;
        digitstr += line[0];
        errorind++;
        line.erase(0, 1);
    }
    digit = std::stod(digitstr);
    return true;
}
// Проверяет тип фигуры
int CheckFigure(std::string& line, int& errorind)
{
    if (Compare("circle", line, errorind))
        return 1;
    if (Compare("triangle", line, errorind))
        return 2;
    if (Compare("polygon", line, errorind))
        return 3;
    return 0; // возвращает 0 Если фигура не нашлась
}
// Рисует указатель на ошибку
void ErrorMark(int errorind)
{
    for (int i = 0; i < errorind; i++)
        std::cout << " ";
    std::cout << "^" << std::endl;
}
// Вывод сообщения об ошибке по её номеру
void Errorout(int numerror,int errorind){
    ErrorMark(errorind);
    std::cout << "Error in colomn " << errorind;
    if (numerror == 1)
        std::cout << ": can not detect figure \n";
    if (numerror == 2)
        std::cout << ": expected '(' \n";
    if (numerror == 3)
        std::cout << ": expected <float> \n";
    if (numerror == 4)
        std::cout << ": expected ',' \n";
    if (numerror == 5)
        std::cout << ": expected ')' \n";
    std::cout << std::endl;
}

int main()
{
    int errorind = 0;   // Индекс ошибки
    std::ifstream file; // Файл для проверки

    file.open("Input.txt"); // Открываемм файл
    if (!file.is_open()) {  // Если файла не существет
        std::cout << "Error: cannot open file. Check name of file \n"; // Выводим человекопонятное сообщение
        return 1; // И возвращаем ошибку
    }
    std::string line; // Строка из файла для проверки
    while (getline(file, line)) { // Построчно проверяем файл
        errorind = 0;
        std::cout << line << std::endl;
        size_t pos = 0; // Указатель на позицию
        errorind += SkipSpace(line);
        int figure = CheckFigure(line, errorind); // Тип фигуры
        if (figure == 0) { // Если фигура не найдена
            Errorout(1, errorind); 
            continue; 
        }
        errorind += SkipSpace(line);
        if (!Compare("(", line, errorind)) {
            Errorout(2, errorind);
            continue; 
        }
        if (figure == 1) {
            Curcle curcle;
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, curcle._point_x)) {
                Errorout(3, errorind);
                continue; 
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, curcle._point_y)) {
                Errorout(3, errorind);
                continue; 
            }
            errorind += SkipSpace(line);
            if (!Compare(",", line, errorind)) {
                Errorout(4, errorind);
                continue; 
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, curcle._radius)) {
                Errorout(3, errorind);
                continue; 
            }
            errorind += SkipSpace(line);
            if (!Compare(")", line, errorind)) {
                Errorout(5, errorind);
                continue; 
            }
        }
        std::cout << "No Errors!\n\n";
    }
    file.close();
    return 0;
}