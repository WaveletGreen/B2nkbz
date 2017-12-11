#include "B2nkbz_ActionHandler.h"
#include "MethodManager.h"
#include "Debug.h"
/*
####################################################################################

						
						
						注册必要的Handler，实现注册手段



####################################################################################

*/
/**注册制造handler*/
extern int Regist_ActionHandler_B2nkbzzz() {
	int ifail = ITK_ok;
	(ifail = EPM_register_action_handler("B2nkbzzz", "B2nkbzzz", (EPM_action_handler_t)ActionHandler_B2nkbzzz));
	if (ifail == 0) {
		Debug("注册ActionHandler B2nkbzzz(内控标准-制造)成功");
	}
	else {
		Debug("注册ActionHandler B2nkbzzz(内控标准-制造)失败");
	}
	return ifail;
}
/**注册品质handler**/
extern int Regist_ActionHandler_B2nkbzpz() {
	int ifail = ITK_ok;
	(ifail = EPM_register_action_handler("B2nkbzpz", "B2nkbzpz", (EPM_action_handler_t)ActionHandler_B2nkbzpz));
	if (ifail == 0) {
		Debug("注册ActionHandler B2nkbzpz(内控标准-品质)成功");
	}
	else {
		Debug("注册ActionHandler B2nkbzpz(内控标准-品质)失败");
	}
	return ifail;
}