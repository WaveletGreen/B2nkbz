#include "B2nkbz_ActionHandler.h"
#include "MethodManager.h"
#include "Debug.h"
/*
####################################################################################

						
						
						ע���Ҫ��Handler��ʵ��ע���ֶ�



####################################################################################

*/
/**ע������handler*/
extern int Regist_ActionHandler_B2nkbzzz() {
	int ifail = ITK_ok;
	(ifail = EPM_register_action_handler("B2nkbzzz", "B2nkbzzz", (EPM_action_handler_t)ActionHandler_B2nkbzzz));
	if (ifail == 0) {
		Debug("ע��ActionHandler B2nkbzzz(�ڿر�׼-����)�ɹ�");
	}
	else {
		Debug("ע��ActionHandler B2nkbzzz(�ڿر�׼-����)ʧ��");
	}
	return ifail;
}
/**ע��Ʒ��handler**/
extern int Regist_ActionHandler_B2nkbzpz() {
	int ifail = ITK_ok;
	(ifail = EPM_register_action_handler("B2nkbzpz", "B2nkbzpz", (EPM_action_handler_t)ActionHandler_B2nkbzpz));
	if (ifail == 0) {
		Debug("ע��ActionHandler B2nkbzpz(�ڿر�׼-Ʒ��)�ɹ�");
	}
	else {
		Debug("ע��ActionHandler B2nkbzpz(�ڿر�׼-Ʒ��)ʧ��");
	}
	return ifail;
}