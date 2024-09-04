#include "Polygon.h"
#include <sstream>

using std::istream;
using std::string;
using std::vector;
using std::cout;
using std::endl;


namespace nspace
{
    istream& operator>>(istream& in, DelimiterIO&& dest)
    {
        istream::sentry sentry(in);
        if (!sentry) // ��������� ��������� ������ � ��� ��������
        {
            return in;
        }
        
        char c = '0';
        in >> c;
        
        if (in and c != dest.exp)
        { // ���� ������ �� ������������� ������������, �� ������������ ���� ������ ������
            in.setstate(std::ios::failbit);
        }
        
        return in;
    }
    
    istream& operator>>(istream& in, Point& dest)
    {
        istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        
        in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
        return in; // ����������� ������
    }
    
    istream& operator>>(istream& in, Polygon& dest)
    {
        istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        
        dest.points.clear(); // ��������� ������
        int size = 0;
        in >> size;
        
        if (size > 2) // ���� ������ ������ 2, �� ������ ������ ������
        {
            char ch;

            vector <Point> temp{};
            int i = 0;
            while (i < size)
            {
                in.get(ch); // ���������� get, ����� �� ���������� �������
                if (ch == ' ')
                {
                    Point point;
                    in >> point;
                    if (std::find(temp.begin(), temp.end(), point) == temp.end()) // ������� ���� �� ����� ��� � �������
                    {
                        temp.push_back(point);
                    }
                }
                ++i;

            }
            dest.points = temp;
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        
        return in;
    }
}
