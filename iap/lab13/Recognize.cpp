
#include"fst.h"
#include"Recognize.h"
#include "In.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#pragma warning(disable: 4996)

LT::Entry *forLex;
string keyWords[7] = { "integer","string","function","declare","return","print","main" };
char keySigns[11] = { ';',',','{','}','(',')','+','-','*','/','=' };
int fstIndex = 0;
char emptyStr[] = "";
FST::FST fstIntType(emptyStr, 8, //�������� ������� 
	FST::NODE(1, FST::RELATION('i', 1)),
	FST::NODE(1, FST::RELATION('n', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE(1, FST::RELATION('e', 4)),
	FST::NODE(1, FST::RELATION('g', 5)),
	FST::NODE(1, FST::RELATION('e', 6)),
	FST::NODE(1, FST::RELATION('r', 7)),
	FST::NODE()
);

FST::FST fstStrType(emptyStr, 7,
	FST::NODE(1, FST::RELATION('s', 1)),
	FST::NODE(1, FST::RELATION('t', 2)),
	FST::NODE(1, FST::RELATION('r', 3)),
	FST::NODE(1, FST::RELATION('i', 4)),
	FST::NODE(1, FST::RELATION('n', 5)),
	FST::NODE(1, FST::RELATION('g', 6)),
	FST::NODE()
);

FST::FST fstDeclare(emptyStr, 8,
	FST::NODE(1, FST::RELATION('d', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('c', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE(1, FST::RELATION('a', 5)),
	FST::NODE(1, FST::RELATION('r', 6)),
	FST::NODE(1, FST::RELATION('e', 7)),
	FST::NODE()
);

FST::FST fstFunction(emptyStr, 9,
	FST::NODE(1, FST::RELATION('f', 1)),
	FST::NODE(1, FST::RELATION('u', 2)),
	FST::NODE(1, FST::RELATION('n', 3)),
	FST::NODE(1, FST::RELATION('c', 4)),
	FST::NODE(1, FST::RELATION('t', 5)),
	FST::NODE(1, FST::RELATION('i', 6)),
	FST::NODE(1, FST::RELATION('o', 7)),
	FST::NODE(1, FST::RELATION('n', 8)),
	FST::NODE()
);

FST::FST fstV(emptyStr, 2,
	FST::NODE(5, FST::RELATION('-', 1), FST::RELATION('+', 1), FST::RELATION('/', 1), FST::RELATION('*', 1), FST::RELATION('=', 1)),
	FST::NODE()
);

FST::FST fstMain(emptyStr, 5,
	FST::NODE(1, FST::RELATION('m', 1)),
	FST::NODE(1, FST::RELATION('a', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('n', 4)),
	FST::NODE()
);

FST::FST fstPrint(emptyStr, 6,
	FST::NODE(1, FST::RELATION('p', 1)),
	FST::NODE(1, FST::RELATION('r', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('n', 4)),
	FST::NODE(1, FST::RELATION('t', 5)),
	FST::NODE()
);

FST::FST fstReturn(emptyStr, 7,
	FST::NODE(1, FST::RELATION('r', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE(1, FST::RELATION('u', 4)),
	FST::NODE(1, FST::RELATION('r', 5)),
	FST::NODE(1, FST::RELATION('n', 6)),
	FST::NODE()
);

FST::FST fstLeftThesis(emptyStr, 2,
	FST::NODE(1, FST::RELATION('(', 1)),
	FST::NODE()
);

FST::FST fstRightThesis(emptyStr, 2,
	FST::NODE(1, FST::RELATION(')', 1)),
	FST::NODE()
);

FST::FST fstSemiColon(emptyStr, 2,
	FST::NODE(1, FST::RELATION(';', 1)),
	FST::NODE()
);

FST::FST fstComma(emptyStr, 2,
	FST::NODE(1, FST::RELATION(',', 1)),
	FST::NODE()
);

FST::FST fstLeftBrace(emptyStr, 2,
	FST::NODE(1, FST::RELATION('{', 1)),
	FST::NODE()
);

FST::FST fstRightBrace(emptyStr, 2,
	FST::NODE(1, FST::RELATION('}', 1)),
	FST::NODE()
);
//�������� 
FST::FST fstIntegerLiteral(emptyStr, 2, // ��� �������� , 2 ��������� ��� ������� ������� ,����� �� ������ ��������� ���������� �������� ������ 
	FST::NODE(20, FST::RELATION('0', 1), FST::RELATION('0', 0),
		FST::RELATION('1', 1), FST::RELATION('1', 0),
		FST::RELATION('2', 1), FST::RELATION('2', 0),
		FST::RELATION('3', 1), FST::RELATION('3', 0),
		FST::RELATION('4', 1), FST::RELATION('4', 0),
		FST::RELATION('5', 1), FST::RELATION('5', 0),
		FST::RELATION('6', 1), FST::RELATION('6', 0),
		FST::RELATION('7', 1), FST::RELATION('7', 0),
		FST::RELATION('8', 1), FST::RELATION('8', 0),
		FST::RELATION('9', 1), FST::RELATION('9', 0)),
	FST::NODE()
);

FST::FST fstStringLiteral(emptyStr, 4, //���� ����� ��� ����� 
	FST::NODE(1, FST::RELATION('\'', 1)),
	FST::NODE(164,
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('�', 2), FST::RELATION('�', 1),
		FST::RELATION('\t', 2), FST::RELATION('\t', 1),
		FST::RELATION('{', 2), FST::RELATION('{', 1),
		FST::RELATION('}', 2), FST::RELATION('}', 1),
		FST::RELATION('(', 2), FST::RELATION('(', 1),
		FST::RELATION(')', 2), FST::RELATION(')', 1),
		FST::RELATION('=', 2), FST::RELATION('=', 1),
		FST::RELATION('-', 2), FST::RELATION('-', 1),
		FST::RELATION('+', 2), FST::RELATION('+', 1),
		FST::RELATION('*', 2), FST::RELATION('*', 1),
		FST::RELATION('/', 2), FST::RELATION('/', 1),
		FST::RELATION(',', 2), FST::RELATION(',', 1),
		FST::RELATION(';', 2), FST::RELATION(';', 1),
		FST::RELATION(' ', 2), FST::RELATION(' ', 1),
		FST::RELATION('0', 2), FST::RELATION('0', 1),						//72
		FST::RELATION('1', 2), FST::RELATION('1', 1),
		FST::RELATION('2', 2), FST::RELATION('2', 1),
		FST::RELATION('3', 2), FST::RELATION('3', 1),
		FST::RELATION('4', 2), FST::RELATION('4', 1),
		FST::RELATION('5', 2), FST::RELATION('5', 1),
		FST::RELATION('6', 2), FST::RELATION('6', 1),
		FST::RELATION('7', 2), FST::RELATION('7', 1),
		FST::RELATION('8', 2), FST::RELATION('8', 1),
		FST::RELATION('9', 2), FST::RELATION('9', 1),
		FST::RELATION('a', 2), FST::RELATION('a', 1),
		FST::RELATION('b', 2), FST::RELATION('b', 1),
		FST::RELATION('c', 2), FST::RELATION('c', 1),
		FST::RELATION('d', 2), FST::RELATION('d', 1),
		FST::RELATION('e', 2), FST::RELATION('e', 1),
		FST::RELATION('f', 2), FST::RELATION('f', 1),
		FST::RELATION('g', 2), FST::RELATION('g', 1),
		FST::RELATION('h', 2), FST::RELATION('h', 1),
		FST::RELATION('i', 2), FST::RELATION('i', 1),
		FST::RELATION('j', 2), FST::RELATION('j', 1),
		FST::RELATION('k', 2), FST::RELATION('k', 1),
		FST::RELATION('l', 2), FST::RELATION('l', 1),
		FST::RELATION('m', 2), FST::RELATION('m', 1),
		FST::RELATION('n', 2), FST::RELATION('n', 1),
		FST::RELATION('o', 2), FST::RELATION('o', 1),
		FST::RELATION('p', 2), FST::RELATION('p', 1),
		FST::RELATION('q', 2), FST::RELATION('q', 1),
		FST::RELATION('r', 2), FST::RELATION('r', 1),
		FST::RELATION('s', 2), FST::RELATION('s', 1),
		FST::RELATION('t', 2), FST::RELATION('t', 1),
		FST::RELATION('u', 2), FST::RELATION('u', 1),
		FST::RELATION('v', 2), FST::RELATION('v', 1),
		FST::RELATION('w', 2), FST::RELATION('w', 1),
		FST::RELATION('x', 2), FST::RELATION('x', 1),
		FST::RELATION('y', 2), FST::RELATION('y', 1),
		FST::RELATION('z', 2), FST::RELATION('z', 1)),
	FST::NODE(1, FST::RELATION('\'', 3)),
	FST::NODE()
);

namespace RE {
	int line = 0, col = 0;
	int character = 0;
	char word[LT_MAXSIZE];
	LT::LexTable* ltable;
	IT::IdTable* itable;
	IT::IDDATATYPE dataType;
	IT::IDTYPE idType;

	bool newLex(FST::FST& fst, char* word, char lexema)
	{
		bool rc = false;
		FST::newFST(fst, word);
		if (FST::execute(fst))
		{
			rc = true;
			addLex(lexema, word);
		}
		return rc;
	}

	void addLex(char lexema, char* word)
	{
		LT::Entry lEntry = { LT::NONE, lexema, line, (int)LT_TI_NULLIDX };
		if (word && lexema == LEX_SIGN)
		{
			switch (word[0])
			{
			case LEX_PLUS:
				lEntry.sign = LT::PLUS;
				break;
			case LEX_MINUS:
				lEntry.sign = LT::MINUS;
				break;
			case LEX_STAR:
				lEntry.sign = LT::STAR;
				break;
			case LEX_DIRSLASH:
				lEntry.sign = LT::DIRSLASH;
				break;
			default:
				std::cout << lEntry.sn << "NONE" << std::endl;
				break;
			}
		}
		LT::Add(*ltable, lEntry);
	}

	void addId(char* word, IT::IDDATATYPE dataType, IT::IDTYPE idType)//�������������� 
	{
		if (word[0] != LEX_APOS && (word[0] <= 47 || word[0] >= 58))								//for ID
		{
			IT::Entry iEntry;
			bool std = false;
			for (int i = 0; i < STD_BIBLE_SIZE; i++)
				if (strcmp(StdBible[i], word) == 0)
				{
					std = true;
					break;
				}
			if ((strlen(word) > ID_MAXSIZE) && !std)
				word[ID_MAXSIZE] = LEX_END;
			bool isExecute = false;
			for (int i = 0; i <= (*itable).size; i++)
				if (strcmp((*itable).table[i].id, word) == 0)
				{
					isExecute = true;
					break;
				}
			if (isExecute)																		//���� ���������� ��� ���������
			{
				if (dataType == IT::NONE)
				{
					strcpy(iEntry.id, word);
					iEntry.iddatatype = IT::NONE;
					iEntry.idtype = IT::V;
					iEntry.value.vint = TI_INT_DEFAULT;
					iEntry.value.vstr->len = TI_STR_DEFAULT;
					strcpy(iEntry.value.vstr->str, "");
					iEntry.idxfirstLE = (short)IT::IsId(*itable, word, false);								// ������
				}
				else
				{
					strcpy(iEntry.id, word);
					iEntry.iddatatype = dataType;
					iEntry.idtype = idType;
					iEntry.value.vint = TI_INT_DEFAULT;
					iEntry.value.vstr->len = TI_STR_DEFAULT;
					strcpy(iEntry.value.vstr->str, "");
					iEntry.idxfirstLE = (short)IT::IsId(*itable, word, true);								// = line;
				}
				IT::Add(*itable, iEntry);
				ltable->table[ltable->size].indxTI = iEntry.idxfirstLE;
			}
			else
			{
				if (dataType == IT::NONE)
					throw ERROR_THROW_IN(9, line, col);
				strcpy(iEntry.id, word);
				iEntry.iddatatype = dataType;
				iEntry.idtype = idType;
				iEntry.value.vint = TI_INT_DEFAULT;
				iEntry.value.vstr->len = TI_STR_DEFAULT;
				strcpy(iEntry.value.vstr->str, "");
				iEntry.idxfirstLE = (short)IT::IsId(*itable, word, true);								// = line;
				IT::Add(*itable, iEntry);
				ltable->table[ltable->size].indxTI = iEntry.idxfirstLE;
			}
		}
		else																				//for literal
		{
			IT::Entry iEntry;
			char finalString[255] = "LITERAL";
			char bufL[255];
			char bufC[255];
			itoa(line, bufL, 10);
			itoa(col, bufC, 10);
			strcat(finalString, bufL);
			strcat(finalString, bufC);
			strcpy(iEntry.id, finalString);
			iEntry.iddatatype = dataType;
			iEntry.idtype = idType;
			if (dataType == IT::INT)
			{
				long double bufNum = std::atoi(word);
				if (bufNum > INT_MAX)
					throw ERROR_THROW_IN(12, line, col);
				iEntry.value.vint = (int)bufNum;
			}
			else
			{
				if (strlen(word) > 255)
					throw ERROR_THROW_IN(11, line, col);
				iEntry.value.vstr->len = strlen(word);
				strcpy(iEntry.value.vstr->str, word);
			}
			iEntry.idxfirstLE = line;
			IT::Add(*itable, iEntry);
		}
	}

	bool isLetter(char ch)
	{
		return ch == LEX_SPACE || ch == LEX_APOS || ch == LEX_ENDL || ch == LEX_MINUS || ch == LEX_PLUS || ch == LEX_COMPARE || ch == LEX_DIRSLASH || ch == LEX_STAR || ch == LEX_LEFTHESIS || ch == LEX_RIGHTHESIS || ch == LEX_LEFTBRACE || ch == LEX_BRACELET || ch == LEX_SEMICOLON || ch == LEX_COMMA || ch == LEX_END;
	}

	void ChainRecognition(Log::LOG& log, In::IN& in, Parm::PARM &parm, LT::LexTable& lextable, IT::IdTable& idtable) {




	
		ltable = &lextable;
		itable = &idtable;
		dataType = IT::NONE;
		idType = IT::L;

		for (int i = 0; i < in.text.length(); i++) {
			bool rc = false;
			word[character] = in.text[i];
			character++;
			if (isLetter(in.text[i]))
			{
				word[1] = LEX_END;
				character = 0;
			}
			switch (in.text[i])
			{
			case LEX_ENDL:
			{
				col = 0;
				line++;
				rc = true;
				continue;
			}
			case LEX_TAB:
			{
				rc = true;
				break;
			}
			case LEX_SPACE:
			{
				rc = true;
				while (in.text[i + 1] == LEX_SPACE)
					i++;
				break;
			}
			case LEX_LEFTHESIS:
			{
				rc = newLex(fstLeftThesis, word, LEX_LEFTHESIS);
				break;
			}
			case LEX_RIGHTHESIS:
			{
				rc = newLex(fstRightThesis, word, LEX_RIGHTHESIS);
				break;
			}
			case LEX_LEFTBRACE:
			{
				rc = newLex(fstLeftBrace, word, LEX_LEFTBRACE);
				break;
			}
			case LEX_BRACELET:
			{
				rc = newLex(fstRightBrace, word, LEX_BRACELET);
				break;
			}
			case LEX_SEMICOLON:
			{
				rc = newLex(fstSemiColon, word, LEX_SEMICOLON);
				break;
			}
			case LEX_COMMA:
			{
				rc = newLex(fstComma, word, LEX_COMMA);
				break;
			}
			case LEX_PLUS:
			case LEX_STAR:
			case LEX_DIRSLASH:
			case LEX_MINUS:
				rc = newLex(fstV, word, LEX_SIGN);
				break;
			case LEX_COMPARE:
			{
				rc = newLex(fstV, word, LEX_COMPARE);
				break;
			}
			case LEX_APOS:
			{
				word[0] = LEX_END;
				character = 0;
				char strLex[TI_STR_MAXSIZE];
				int j = 0;
				do
				{
					strLex[j] = in.text[i];
					j++;
					if (in.text[i + 1] == LEX_END)
						throw ERROR_THROW_IN(7, line, col);
					i++;
				} while (in.text[i] != LEX_APOS);
				strLex[j] = in.text[i];
				strLex[j + 1] = LEX_END;
				newLex(fstStringLiteral, strLex, LEX_LITERAL);
				addId(strLex, IT::STR, IT::L);
				rc = true;
				break;
			}
			default:
				rc = true;
				if (isLetter(in.text[i + 1]))
				{
					word[character] = LEX_END;
					bool wordLex = isThatLexem(word);
					if (!wordLex)													//when 'word' is id
					{
						if (word[0] > 47 && word[0] < 58)
							throw ERROR_THROW_IN(10, line, col);
						addLex(LEX_ID, nullptr);
						addId(word, dataType, idType);
						dataType = IT::NONE;
					}
					word[0] = LEX_END;
					character = 0;
				}
				break;
			}
			col++;
			if (!rc)
				throw ERROR_THROW_IN(2, line, col);
		}
		//char *strrr = new char[in.text.length()];
			//string toCheck = "";
		//	int lineIndex = 0;*/
		 // in.text = modernizeText(in.text);
		//	cout << in.text;*/	
	  //int i, j;
			//FST::FST fst1(
			//	strrr, 21,
			//	FST::NODE(1, FST::RELATION('s', 1)), //0
			//	FST::NODE(1, FST::RELATION('t', 2)), //1
			//	FST::NODE(1, FST::RELATION('a', 3)), //2
			//	FST::NODE(1, FST::RELATION('r', 4)), //3
			//	FST::NODE(1, FST::RELATION('t', 5)), //4
			//	FST::NODE(1, FST::RELATION(' ', 6)), //5
			//	FST::NODE(4, FST::RELATION(' ', 6), FST::RELATION('s', 7), FST::RELATION('w', 13), FST::RELATION(' ', 16)),//6
			//	FST::NODE(2, FST::RELATION('e', 8), FST::RELATION('h', 11)), //7
			//	FST::NODE(1, FST::RELATION('n', 9)), //8
			//	FST::NODE(1, FST::RELATION('d', 10)), //9
			//	FST::NODE(2, FST::RELATION(' ', 16), FST::RELATION(' ', 6)), //10
			//	FST::NODE(1, FST::RELATION('o', 12)), //11
			//	FST::NODE(1, FST::RELATION('w', 10)), //12
			//	FST::NODE(1, FST::RELATION('a', 14)), //13
			//	FST::NODE(1, FST::RELATION('i', 15)), //14
			//	FST::NODE(1, FST::RELATION('t', 10)), //15
			//	FST::NODE(2, FST::RELATION(' ', 16), FST::RELATION('s', 17)), //16
			//	FST::NODE(1, FST::RELATION('t', 18)), //17
			//	FST::NODE(1, FST::RELATION('o', 19)), //18
			//	FST::NODE(1, FST::RELATION('p', 20)) //19
			//);
			//for (i = j = 0; i < in.text.length(); i++, j++) {
			//	if (in.text[i] == '|') {
			//		lineIndex++;
			//	}
			//	if (in.text[i] == ' ') {
			//		
			//		if (check(toCheck)) {
			//			//cout << toCheck <<"         "<< fstIndex<<"  "<<lineIndex <<endl;
			//			//cout << toCheck <<"  "<<lineIndex ;
			//		write(strrr, j, fst1[fstIndex], parm); 
			//		}
			//		else {
			//			toCheck=fomateOther(toCheck);
			//			if (toCheck != "") {
			//				cout << toCheck << " " << lineIndex << endl;
			//			}
			//		}
			//		toCheck = "";
			//		j = -1;
			//	}
			//	else {
			//		strrr[j] = in.text[i];
			//		toCheck+= in.text[i];
			//	}
			//}
		std::cout << 1;
	}

	bool isThatLexem(char word[])
	{
		bool rc = false;
		rc = newLex(fstIntType, word, LEX_INTEGER);
		if (rc)
		{
			dataType = IT::INT;
			if (idType == IT::F)
				idType = IT::P;
			return rc;
		}
		rc = newLex(fstStrType, word, LEX_STRING);
		if (rc)
		{
			dataType = IT::STR;
			if (idType == IT::F)
				idType = IT::P;
			return rc;
		}
		rc = newLex(fstDeclare, word, LEX_DECLARE);
		if (rc)
		{
			idType = IT::V;
			return rc;
		}
		rc = newLex(fstFunction, word, LEX_FUNCTION);
		if (rc)
		{
			idType = IT::F;
			return rc;
		}
		rc = newLex(fstMain, word, LEX_MAIN);
		if (rc) return rc;
		rc = newLex(fstPrint, word, LEX_PRINT);
		if (rc)
		{
			idType = IT::V;
			return rc;
		}
		rc = newLex(fstReturn, word, LEX_RETURN);
		if (rc)
		{
			idType = IT::V;
			return rc;
		}
		rc = newLex(fstIntegerLiteral, word, LEX_LITERAL);
		if (rc)
		{
			addId(word, IT::INT, IT::L);
			return rc;
		}
		return rc;
	}
	

	//void defineAVT(char * strrr)
	//{
	//	fst1[0] = FST::FST(
	//		strrr, 8,
	//		FST::NODE(1, FST::RELATION('i', 1)), //0
	//		FST::NODE(1, FST::RELATION('n', 2)), //1
	//		FST::NODE(1, FST::RELATION('t', 3)), //2
	//		FST::NODE(1, FST::RELATION('e', 4)), //3
	//		FST::NODE(1, FST::RELATION('g', 5)), //4
	//		FST::NODE(1, FST::RELATION('e', 6)), //5
	//		FST::NODE(1, FST::RELATION('r', 7))  //6
	//	);
	//	fst1[1] = FST::FST(
	//		strrr, 7,
	//		FST::NODE(1, FST::RELATION('s', 1)), //0
	//		FST::NODE(1, FST::RELATION('t', 2)), //1
	//		FST::NODE(1, FST::RELATION('r', 3)), //2
	//		FST::NODE(1, FST::RELATION('i', 4)), //3
	//		FST::NODE(1, FST::RELATION('n', 5)), //4
	//		FST::NODE(1, FST::RELATION('g', 6)) //5
	//	);
	//	fst1[2] = FST::FST(
	//		strrr, 9,
	//		FST::NODE(1, FST::RELATION('f', 1)), //0
	//		FST::NODE(1, FST::RELATION('u', 2)), //1
	//		FST::NODE(1, FST::RELATION('n', 3)), //2
	//		FST::NODE(1, FST::RELATION('c', 4)), //3
	//		FST::NODE(1, FST::RELATION('t', 5)), //4
	//		FST::NODE(1, FST::RELATION('i', 6)), //6
	//		FST::NODE(1, FST::RELATION('o', 7)), //7
	//		FST::NODE(1, FST::RELATION('n', 8))  //8
	//	);
	//	fst1[3] = FST::FST(
	//		strrr, 8,
	//		FST::NODE(1, FST::RELATION('d', 1)), //0
	//		FST::NODE(1, FST::RELATION('e', 2)), //1
	//		FST::NODE(1, FST::RELATION('c', 3)), //2
	//		FST::NODE(1, FST::RELATION('l', 4)), //3
	//		FST::NODE(1, FST::RELATION('a', 5)), //4
	//		FST::NODE(1, FST::RELATION('r', 6)), //6
	//		FST::NODE(1, FST::RELATION('e', 7))
	//	);
	//	fst1[4] = FST::FST(
	//		strrr, 7,
	//		FST::NODE(1, FST::RELATION('r', 1)), //0
	//		FST::NODE(1, FST::RELATION('e', 2)), //1
	//		FST::NODE(1, FST::RELATION('t', 3)), //2
	//		FST::NODE(1, FST::RELATION('u', 4)), //3
	//		FST::NODE(1, FST::RELATION('r', 5)), //4
	//		FST::NODE(1, FST::RELATION('n', 6))
	//	);
	//	fst1[5] = FST::FST(
	//		strrr, 6,
	//		FST::NODE(1, FST::RELATION('p', 1)), //0
	//		FST::NODE(1, FST::RELATION('r', 2)), //1
	//		FST::NODE(1, FST::RELATION('i', 3)), //2
	//		FST::NODE(1, FST::RELATION('n', 4)), //3
	//		FST::NODE(1, FST::RELATION('t', 5))
	//	);
	//	fst1[6] = FST::FST(
	//		strrr, 5,
	//		FST::NODE(1, FST::RELATION('m', 1)), //0
	//		FST::NODE(1, FST::RELATION('a', 2)), //1
	//		FST::NODE(1, FST::RELATION('i', 3)), //2
	//		FST::NODE(1, FST::RELATION('n', 4))
	//	);
	//	fst1[7] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION(';', 1))
	//	);
	//	fst1[8] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION(',', 1))
	//	);
	//	fst1[9] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION('{', 1))
	//	);
	//	fst1[10] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION('}', 1))
	//	);
	//	fst1[11] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION('(', 1))
	//	);
	//	fst1[12] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION(')', 1))
	//	); fst1[13] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION('+', 1))
	//	); fst1[14] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION('-', 1))
	//	); fst1[15] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION('*', 1))
	//	); fst1[16] = FST::FST(
	//		strrr, 2,
	//		FST::NODE(1, FST::RELATION('/', 1))
	//	);
	//}
	//void write(char * strrr, int j, FST::FST &fst1, Parm::PARM & parm)
	//{
	//	strrr[j] = '\0';
	//	if (strcmp(strrr, "") != 0) {
	//		FST::udpdate(fst1, strrr);
	//		if (FST::execute(fst1)) {
	//			//cout << fst1.string<<endl;
	//			Log::writeOut(parm, "������� ", fst1.string, " ����������", "");
//		}
	//		else {
	//			Log::writeOut(parm, "������� ", fst1.string, " �� ����������", "");
	//		}
	//	}
	//}
	//string modernizeText(string text) {
		//	string newText = "";
	//	string line = "";
	//	for (int i = 0; i < text.length(); i++) {
	//		if (text[i] != '\n') {
	//			line += text[i];
//		}
	//		else {
	//			newText += modernizeLine(line) + "|";
	//			line = "";
	//		}
	//	}
	//	return newText;
	//}
	//string modernizeLine(string line) {
	//	string textPart = "";
	//	string newLine = "";
	//	int letterCount = 0;
	//	for (int i = 0; i < line.length(); i++) {
	//		if (line[i] != ' ') {
	//			letterCount++;
	//			textPart += line[i];
	//		}
	//		for (int y = 0; y < 13; y++) {
	//			if (line[i] == keySigns[y]) {
	//				newLine += " " + textPart.insert(letterCount - 1, " ");
	//				textPart = "";
	//				letterCount = 0;
	//			}
	//		}
	//		for (int y = 0; y < 8; y++) {
	//			if (textPart == keyWords[y]) {
	//				newLine += " " + keyWords[y];
	//				textPart = "";
	//				letterCount = 0;
	//			}
	//		}
	//	}
	//	return newLine;
	//}
	//bool check(string str) {
	//	for (int i = 0; i < 7; i++) {
	//		
	//		if (str == keyWords[i]) {
	//			fstIndex = i;
	//			return true;
	//		}
	//	}
	//	if (str.length() == 1) {
	//		cout << str[0];
	//		return check(str[0]);
	//	}
	//	return false;
	//}
	//bool check(char str) {
	//	
	//	for (int i = 0; i < 11; i++) {
	//		if (str == keySigns[i]) {//cout << str;
	//			/*if (str != '+'&&str != '-'&&str != '*'&&str != '/') {
	//		*/
	//					fstIndex = 7 +i;
	//				
	//			}
	//		/*	else {
	//				cout << str;
	//				fstIndex = 13;
	//			}*/
	//			return true;
	//		}
	//	}
	//	return false;
	//}
	//string fomateOther(string toCheck) {
	//	string newStr = "";
	//	for (int i = 0; i < toCheck.length(); i++) {
	//		if (toCheck[i] != ' ' && toCheck[i] != '|') {
	//			newStr += toCheck[i];
	//		}
	//	}
	//	return newStr;
	//}
	//
	//
	// 

	


}