#include "init.h"
#include "Debug.h"
#include "DBHandler.h"
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************
							程序主函数
*******************************************************************/
	DLLAPI int B2nkbz_register_callbacks()
	{
		int ifail = ITK_ok;
		//注册函数，并非是注册user service函数，其需要另外定义
		ifail = CUSTOM_register_exit(
			"B2nkbz",
			"USER_gs_shell_init_module",
			(CUSTOM_EXIT_ftn_t)CUST_init_module);
		if (ifail == 0) {
			Debug("初始化CUST_init_module成功");
		}
		else {
			Debug("初始化CUST_init_module失败");
		}
		//B2nkbz_save(USERNAME, PASSWORD, DBNAME,NULL);
		return ifail;
	}

#ifdef __cplusplus
}
#endif

