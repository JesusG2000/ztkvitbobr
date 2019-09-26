#pragma once

#include<fstream>
#include"In.h"
#include"Parm.h"
#include"Error.h"
#include"LT.h"
#include"IT.h"
namespace Log {	//������ � ����������
	struct LOG {	//��������
		wchar_t logfile[PARM_MAX_SIZE] = L"";		//��� ����� ���������
		ofstream  stream;				//�������� ����� ���������
		bool access = true;
	};
	//��������� ��� ��������� ������������� LOG

	LOG getLog(wchar_t logfile[]);					//������������ ��������� LOG
	void writeLine(LOG log, const char* c, ...);			//������� � �������� ������������ �����
	void writeLine(LOG log, wchar_t* c, ...);		//������� � �������� ������������ �����
	void writeLog(LOG log);							//������� � �������� ���������
	void writeParm(LOG log, Parm::PARM parm);		//������� � �������� ���������� � ������� ����������
	void writeLexTable(LOG log, LT::LexTable& ltable);				//������� � �������� ���������� � ������� ������
	void writeOut(Parm::PARM parm, const char* c, ...);				//������� � �������� ���������� � ������� ������
	void writeError(LOG log, Error::ERROR e);	//������� � �������� ���������� �� ������� ������
	void close(LOG log);			
	void WriteId(LOG log, IT::IdTable& itable);//������� ��������

}