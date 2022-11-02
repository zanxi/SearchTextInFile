#pragma once

#include "libh.h"

//*******************************************************
// ������� ����������� ������ �������
int numQuastionMask(const std::string& mask);

// ���������� mask � � ��������� � ������� pos, 
//������� ����������� ��������� ��������
int cols_eq_chars(int pos, const std::string& subject, const std::string& mask);

// ���������� ������� ��������� �����, 0 - ���� �� ���������� � ������
int Col(const std::string& subject, const std::string& mask);
bool match(const std::string& subject, const std::string& mask);




//*******************************************************
