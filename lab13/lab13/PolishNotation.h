#pragma once
#include "LT.h"
#include "IT.h"
#include "iostream"
#define EXP1 28
#define EXP2 3
#define EXP3 24
#define FUNCTION_REF '@'
#define FILL_SYMBOL '#'
/*
	(, ) _____ 1
	+, - _____ 2
	/* - _____ 3

	����������� ������ - #
*/
namespace PN
{
	struct OperationStack
	{
		char operation_;
		int priority;
		OperationStack* next;
	};

	bool PolishNotation(int, LT::LexTable&, IT::IdTable&);				//���������� �������� ������ � ������� ������(������� ��������� � lextable, ���� ������, ���� ��)
//true - ���������� �������� ������ ��������� �������
//false - ���������� �������� ������ �� ���������
	void showPolishNotation(LT::LexTable&, IT::IdTable&);
}