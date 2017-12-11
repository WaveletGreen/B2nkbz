#include <server_exits/user_server_exits.h>
#include <tccore/custom.h>
#include "B2nkbz_ActionHandler.h"
/*************************************************************************************
							初始化函数
*************************************************************************************/
extern DLLAPI int CUST_init_module(int *decision, va_list args)
{
	int ifail = ITK_ok;
	//允许注册多个注册函数
	*decision = ALL_CUSTOMIZATIONS;
	//注册内控标准-制造action handler
	ifail = Regist_ActionHandler_B2nkbzzz();
	//注册内控标准-品质action handler
	ifail = Regist_ActionHandler_B2nkbzpz();
	return ifail;
}