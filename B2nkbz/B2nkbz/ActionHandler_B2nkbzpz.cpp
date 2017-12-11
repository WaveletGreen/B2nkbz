#include "epm_handler_common.h"
#include "B2nkbz_CommonHandler.h"
/*
##################################################################################



						获取“内控标准-品质”表单上的内容并传递到中间表上



#################################################################################*/
int ActionHandler_B2nkbzpz(EPM_action_message_t msg)
{
	return B2nkbz_CommonHandler(msg,"B2nkbzpzz");
}


