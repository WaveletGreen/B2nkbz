#include <server_exits/user_server_exits.h>
#include <tccore/custom.h>
#include "B2nkbz_ActionHandler.h"
/*************************************************************************************
							��ʼ������
*************************************************************************************/
extern DLLAPI int CUST_init_module(int *decision, va_list args)
{
	int ifail = ITK_ok;
	//����ע����ע�ắ��
	*decision = ALL_CUSTOMIZATIONS;
	//ע���ڿر�׼-����action handler
	ifail = Regist_ActionHandler_B2nkbzzz();
	//ע���ڿر�׼-Ʒ��action handler
	ifail = Regist_ActionHandler_B2nkbzpz();
	return ifail;
}