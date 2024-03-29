﻿#define _USE_MATH_DEFINES

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Point {
    float x, y;
};

struct Circle {
    int number;
    float radius;
    Point point;
    float GetPerimeter()
    {
        return 2 * M_PI * radius;
    }
    float GetArea()
    {
        return (pow(radius, 2)) * M_PI;
    }
};

struct Circles {
    std::vector<Circle> circles;
    int i = 0;
    void AddCircle(Circle circle)
    {
        i++;
        circle.number = i;
        circles.insert(circles.begin(), circle);
    }
    bool IsEmpty()
    {
        return (circles.size() == 0);
    }
    Circle GetCircle()
    {
        Circle circle = circles.back();
        circles.pop_back();
        return circle;
    }
};

struct Triangle {
    int number;
    Point point1;
    Point point2;
    Point point3;
    Point point4;
    bool IsCloses()
    {
        if ((point1.x != point4.x) || (point1.y != point4.y))
            return false;
        return true;
    }
    float GetArea()
    {
        return 0.5
                * abs((point2.x - point1.x) * (point3.y - point1.y)
                      - (point3.x - point1.x) * (point2.y - point1.y));
    }
    float GetPerimeter()
    {
        float AB, BC, AC;
        AB = sqrt(
                pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2));
        BC = sqrt(
                pow((point3.x - point2.x), 2) + pow((point3.y - point2.y), 2));
        AC = sqrt(
                pow((point3.x - point1.x), 2) + pow((point3.y - point1.y), 2));
        return AB + BC + AC;
    }
};

struct Triangles {
    std::vector<Triangle> triangles;
    int i = 0;
    void AddTriangle(Triangle triangle)
    {
        i++;
        triangle.number = i;
        triangles.insert(triangles.begin(), triangle);
    }
    bool IsEmpty()
    {
        return (triangles.size() == 0);
    }
    Triangle GetTriangle()
    {
        Triangle triangle = triangles.back();
        triangles.pop_back();
        return triangle;
    }
};

struct Polygon {
    int number;
    std::vector<Point> points;
    void AddPoint(Point newpoint)
    {
        points.push_back(newpoint);
    }
    bool IsCloses()
    {
        return ((points[0].x == (points.back()).x)
                && (points[0].y == (points.back()).y));
    }
    void Clear()
    {
        points.clear();
    }
    float GetPerimeter()
    {
        int n = points.size();
        float perimeter = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            perimeter
                    += sqrt(pow(points[i].x - points[j].x, 2)
                            + pow(points[i].y - points[j].y, 2));
        }
        return perimeter;
    }
    float GetArea()
    {
        int n = points.size();
        float area = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += points[i].x * points[j].y - points[j].x * points[i].y;
        }
        return abs(area) / 2;
    }
};

struct Polygons {
    std::vector<Polygon> polygons;
    int i = 0;
    void AddPolygon(Polygon polygon)
    {
        i++;
        polygon.number = i;
        polygons.insert(polygons.begin(), polygon);
    }
    bool IsEmpty()
    {
        return (polygons.size() == 0);
    }
    Polygon GetPolygon()
    {
        Polygon polygon = polygons.back();
        polygons.pop_back();
        return polygon;
    }
};

// Вычисяет расстояние от отрезка до точки
float Distance(Point point, Point start, Point end)
{
    float x1 = start.x, y1 = start.y;
    float x2 = end.x, y2 = end.y;
    float x = point.x, y = point.y;

    // вычисляем длину отрезка
    float length = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));

    // если длина отрезка равна нулю, возвращаем расстояние до начальной точки
    if (length == 0) {
        return std::sqrt(std::pow(x - x1, 2) + std::pow(y - y1, 2));
    }

    // вычисляем параметр t, который задает ближайшую точку отрезка к точке
    float t = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1))
            / std::pow(length, 2);

    // если t находится между 0 и 1, ближайшая точка находится на отрезке
    if (0 <= t && t <= 1) {
        Point closest_point = {x1 + t * (x2 - x1), y1 + t * (y2 - y1)};
        return std::sqrt(
                std::pow(x - closest_point.x, 2)
                + std::pow(y - closest_point.y, 2));
    }

    // если t меньше 0, ближайшая точка находится на прямой продолжении отрезка
    // за начальной точкой
    if (t < 0) {
        return std::sqrt(std::pow(x - x1, 2) + std::pow(y - y1, 2));
    }

    // если t больше 1, ближайшая точка находится на прямой продолжении отрезка
    // за конечной точкой
    if (t > 1) {
        return std::sqrt(std::pow(x - x2, 2) + std::pow(y - y2, 2));
    }
}
// Вычисляет Векторное произведение
float CrossProduct(Point A, Point B, Point C)
{
    float ABx = B.x - A.x;
    float ABy = B.y - A.y;
    float ACx = C.x - A.x;
    float ACy = C.y - A.y;
    return ABx * ACy - ABy * ACx;
}
// Проверяет пересечение отрезков
bool IntersectLines(Point A, Point B, Point C, Point D)
{
    float cp1 = CrossProduct(A, B, C);
    float cp2 = CrossProduct(A, B, D);
    float cp3 = CrossProduct(C, D, A);
    float cp4 = CrossProduct(C, D, B);
    return (cp1 * cp2 < 0 && cp3 * cp4 < 0);
}
// Проверяет, пересекаются ли фигуры
bool Intersect(Circle circle1, Circle circle2)
{
    float distance
            = sqrt(pow((circle1.point.x - circle2.point.x), 2)
                   + pow((circle1.point.y - circle2.point.y), 2));
    return (distance <= (circle1.radius + circle2.radius));
}
bool Intersect(Triangle triangle1, Triangle triangle2)
{
    bool FF = IntersectLines(
            triangle1.point1,
            triangle1.point2,
            triangle2.point1,
            triangle2.point2);
    bool FS = IntersectLines(
            triangle1.point1,
            triangle1.point2,
            triangle2.point2,
            triangle2.point3);
    bool FT = IntersectLines(
            triangle1.point1,
            triangle1.point2,
            triangle2.point3,
            triangle2.point1);
    bool SF = IntersectLines(
            triangle1.point2,
            triangle1.point3,
            triangle2.point1,
            triangle2.point2);
    bool SS = IntersectLines(
            triangle1.point2,
            triangle1.point3,
            triangle2.point2,
            triangle2.point3);
    bool ST = IntersectLines(
            triangle1.point2,
            triangle1.point3,
            triangle2.point3,
            triangle2.point1);
    bool TF = IntersectLines(
            triangle1.point3,
            triangle1.point1,
            triangle2.point1,
            triangle2.point2);
    bool TS = IntersectLines(
            triangle1.point3,
            triangle1.point1,
            triangle2.point2,
            triangle2.point3);
    bool TT = IntersectLines(
            triangle1.point3,
            triangle1.point1,
            triangle2.point3,
            triangle2.point1);
    return FF || FS || FT || SF || SS || ST || TF || TS || TT;
}
bool Intersect(Triangle triangle, Circle circle)
{
    bool F
            = (Distance(circle.point, triangle.point1, triangle.point2)
               <= circle.radius);
    bool S
            = (Distance(circle.point, triangle.point2, triangle.point3)
               <= circle.radius);
    bool T
            = (Distance(circle.point, triangle.point3, triangle.point1)
               <= circle.radius);
    return F || S || T;
}
bool Intersect(Circle circle, Triangle triangle)
{
    bool F
            = (Distance(circle.point, triangle.point1, triangle.point2)
               <= circle.radius);
    bool S
            = (Distance(circle.point, triangle.point2, triangle.point3)
               <= circle.radius);
    bool T
            = (Distance(circle.point, triangle.point3, triangle.point1)
               <= circle.radius);
    return F || S || T;
}
bool Intersect(Polygon polygon, Circle circle)
{
    int n = polygon.points.size();
    for (int i = 0; i < n - 1; i++)
        if (Distance(circle.point, polygon.points[i], polygon.points[i + 1])
            <= circle.radius)
            return true;
    return false;
}
bool Intersect(Circle circle, Polygon polygon)
{
    int n = polygon.points.size();
    for (int i = 0; i < n - 1; i++)
        if (Distance(circle.point, polygon.points[i], polygon.points[i + 1])
            <= circle.radius)
            return true;
    return false;
}
bool Intersect(Triangle triangle, Polygon polygon)
{
    int n = polygon.points.size();
    for (int i = 0; i < n - 1; i++) {
        if (IntersectLines(
                    polygon.points[i],
                    polygon.points[i + 1],
                    triangle.point1,
                    triangle.point2))
            return true;
        if (IntersectLines(
                    polygon.points[i],
                    polygon.points[i + 1],
                    triangle.point2,
                    triangle.point3))
            return true;
        if (IntersectLines(
                    polygon.points[i],
                    polygon.points[i + 1],
                    triangle.point3,
                    triangle.point1))
            return true;
    }
    return false;
}
bool Intersect(Polygon polygon, Triangle triangle)
{
    int n = polygon.points.size();
    for (int i = 0; i < n - 1; i++) {
        if (IntersectLines(
                    polygon.points[i],
                    polygon.points[i + 1],
                    triangle.point1,
                    triangle.point2))
            return true;
        if (IntersectLines(
                    polygon.points[i],
                    polygon.points[i + 1],
                    triangle.point2,
                    triangle.point3))
            return true;
        if (IntersectLines(
                    polygon.points[i],
                    polygon.points[i + 1],
                    triangle.point3,
                    triangle.point1))
            return true;
    }
    return false;
}
bool Intersect(Polygon polygon1, Polygon polygon2)
{
    int n1 = polygon1.points.size();
    int n2 = polygon2.points.size();
    for (int i = 0; i < n1 - 1; i++)
        for (int j = 0; j < n2 - 1; j++)
            if (IntersectLines(
                        polygon1.points[i],
                        polygon1.points[i + 1],
                        polygon2.points[j],
                        polygon2.points[j + 1]))
                return true;
    return false;
}
// Выводит пересечения
void PrintIntersects(
        Circle circle, Circles circles, Triangles triangles, Polygons polygons)
{
    bool none = true;
    while (!circles.IsEmpty()) {
        Circle circle1 = circles.GetCircle();
        if (Intersect(circle, circle1)) {
            std::cout << circle1.number << " circle" << std::endl;
            none = false;
        }
    }
    while (!triangles.IsEmpty()) {
        Triangle triangle1 = triangles.GetTriangle();
        if (Intersect(circle, triangle1)) {
            std::cout << triangle1.number << " triangle" << std::endl;
            none = false;
        }
    }
    while (!polygons.IsEmpty()) {
        Polygon polygon1 = polygons.GetPolygon();
        if (Intersect(circle, polygon1)) {
            std::cout << polygon1.number << " polygon" << std::endl;
            none = false;
        }
    }
    if (none)
        std::cout << "None" << std::endl;
}
void PrintIntersects(
        Triangle triangle,
        Circles circles,
        Triangles triangles,
        Polygons polygons)
{
    bool none = true;
    while (!circles.IsEmpty()) {
        Circle circle1 = circles.GetCircle();
        if (Intersect(triangle, circle1)) {
            std::cout << circle1.number << " circle" << std::endl;
            none = false;
        }
    }
    while (!triangles.IsEmpty()) {
        Triangle triangle1 = triangles.GetTriangle();
        if (Intersect(triangle, triangle1)) {
            std::cout << triangle1.number << " triangle" << std::endl;
            none = false;
        }
    }
    while (!polygons.IsEmpty()) {
        Polygon polygon1 = polygons.GetPolygon();
        if (Intersect(triangle, polygon1)) {
            std::cout << polygon1.number << " polygon" << std::endl;
            none = false;
        }
    }
    if (none)
        std::cout << "None" << std::endl;
}
void PrintIntersects(
        Polygon polygon,
        Circles circles,
        Triangles triangles,
        Polygons polygons)
{
    bool none = true;
    while (!circles.IsEmpty()) {
        Circle circle1 = circles.GetCircle();
        if (Intersect(polygon, circle1)) {
            std::cout << circle1.number << " circle" << std::endl;
            none = false;
        }
    }
    while (!triangles.IsEmpty()) {
        Triangle triangle1 = triangles.GetTriangle();
        if (Intersect(polygon, triangle1)) {
            std::cout << triangle1.number << " triangle" << std::endl;
            none = false;
        }
    }
    while (!polygons.IsEmpty()) {
        Polygon polygon1 = polygons.GetPolygon();
        if (Intersect(polygon, polygon1)) {
            std::cout << polygon1.number << " polygon" << std::endl;
            none = false;
        }
    }
    if (none)
        std::cout << "None" << std::endl;
}

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
// Проверяет на равество не зависимо от регистра (проверять слово в нижнем
// регистре)
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
    bool pointexist = false, minusexist = false;
    if (!isdigit(line[0]) && line[0] != '-')
        return false;
    while ((isdigit(line[0]) || ((line[0] == '-') && (!minusexist))
            || ((line[0] == '.') && (!pointexist)))) {
        if (line[0] == '.')
            pointexist = true;
        if (line[0] == '-')
            minusexist = true;
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
void Errorout(int numerror, int errorind)
{
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
}

int main()
{
    bool mistake = false;
    Triangle newtriangle;
    Circle newcircle;
    Triangles triangles;
    Circles circles;
    Point newpoint;
    Polygon newpolygon;
    Polygons polygons;
    int errorind = 0;   // Индекс ошибки
    std::ifstream file; // Файл для проверки

    file.open("Input.txt"); // Открываемм файл
    if (!file.is_open()) {  // Если файла не существет
        std::cout
                << "Error: cannot open file. Check name of file \n"; // Выводим
        // человекопонятное
        // сообщение
        return 1; // И возвращаем ошибку
    }
    std::string line; // Строка из файла для проверки
    while (getline(file, line)) { // Построчно проверяем файл
        errorind = 0;
        std::cout << std::endl << line << std::endl;
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
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newcircle.point.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newcircle.point.y)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!Compare(",", line, errorind)) {
                Errorout(4, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newcircle.radius)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!Compare(")", line, errorind)) {
                Errorout(5, errorind);
                continue;
            }
            std::cout << "area = " << newcircle.GetArea() << std::endl;
            std::cout << "perimeter = " << newcircle.GetPerimeter()
                      << std::endl;
            std::cout << "intersects:" << std::endl;
            PrintIntersects(newcircle, circles, triangles, polygons);
            circles.AddCircle(newcircle);
        }
        if (figure == 2) {
            errorind += SkipSpace(line);
            if (!Compare("(", line, errorind)) {
                Errorout(2, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newtriangle.point1.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newtriangle.point1.y)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!Compare(",", line, errorind)) {
                Errorout(4, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newtriangle.point2.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newtriangle.point2.y)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!Compare(",", line, errorind)) {
                Errorout(4, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newtriangle.point3.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newtriangle.point3.y)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!Compare(",", line, errorind)) {
                Errorout(4, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newtriangle.point4.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newtriangle.point4.y)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!newtriangle.IsCloses()) {
                std::cout << "First and last points must be equal!\n";
                continue;
            }
            errorind += SkipSpace(line);
            if (!Compare(")", line, errorind)) {
                Errorout(5, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!Compare(")", line, errorind)) {
                Errorout(5, errorind);
                continue;
            }
            std::cout << "area = " << newtriangle.GetArea() << std::endl;
            std::cout << "perimeter = " << newtriangle.GetPerimeter()
                      << std::endl;
            std::cout << "intersects:" << std::endl;
            PrintIntersects(newtriangle, circles, triangles, polygons);
            triangles.AddTriangle(newtriangle);
        }
        if (figure == 3) {
            newpolygon.Clear();
            errorind += SkipSpace(line);
            if (!Compare("(", line, errorind)) {
                Errorout(2, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newpoint.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newpoint.y)) {
                Errorout(3, errorind);
                continue;
            }
            newpolygon.AddPoint(newpoint);
            errorind += SkipSpace(line);
            if (!Compare(",", line, errorind)) {
                Errorout(4, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newpoint.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newpoint.y)) {
                Errorout(3, errorind);
                continue;
            }
            newpolygon.AddPoint(newpoint);
            errorind += SkipSpace(line);
            if (!Compare(",", line, errorind)) {
                Errorout(4, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newpoint.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newpoint.y)) {
                Errorout(3, errorind);
                continue;
            }
            newpolygon.AddPoint(newpoint);
            errorind += SkipSpace(line);
            if (!Compare(",", line, errorind)) {
                Errorout(4, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newpoint.x)) {
                Errorout(3, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!GetDigit(line, errorind, newpoint.y)) {
                Errorout(3, errorind);
                continue;
            }
            newpolygon.AddPoint(newpoint);
            errorind += SkipSpace(line);
            while (true) {
                errorind += SkipSpace(line);
                if (line[0] == ')')
                    break;
                if (!Compare(",", line, errorind)) {
                    Errorout(4, errorind);
                    mistake = true;
                    break;
                }
                errorind += SkipSpace(line);
                if (!GetDigit(line, errorind, newpoint.x)) {
                    Errorout(3, errorind);
                    mistake = true;
                    break;
                }
                errorind += SkipSpace(line);
                if (!GetDigit(line, errorind, newpoint.y)) {
                    Errorout(3, errorind);
                    mistake = true;
                    break;
                }
                newpolygon.AddPoint(newpoint);
            }
            if (mistake)
                continue;
            if (!Compare(")", line, errorind)) {
                Errorout(5, errorind);
                continue;
            }
            errorind += SkipSpace(line);
            if (!Compare(")", line, errorind)) {
                Errorout(5, errorind);
                continue;
            }
            if (!newpolygon.IsCloses()) {
                std::cout << "First and last points must be equal!\n";
                continue;
            }
            std::cout << "area = " << newpolygon.GetArea() << std::endl;
            std::cout << "perimeter = " << newpolygon.GetPerimeter()
                      << std::endl;
            std::cout << "Intersects:" << std::endl;
            PrintIntersects(newpolygon, circles, triangles, polygons);
            polygons.AddPolygon(newpolygon);
        }
    }
    file.close();
    return 0;
}