#include "init.h"
#include "Debug.h"
#include "DBHandler.h"
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************
							����������
*******************************************************************/
	DLLAPI int B2nkbz_register_callbacks()
	{
		int ifail = ITK_ok;
		//ע�ắ����������ע��user service����������Ҫ���ⶨ��
		ifail = CUSTOM_register_exit(
			"B2nkbz",
			"USER_gs_shell_init_module",
			(CUSTOM_EXIT_ftn_t)CUST_init_module);
		if (ifail == 0) {
			Debug("��ʼ��CUST_init_module�ɹ�");
		}
		else {
			Debug("��ʼ��CUST_init_moduleʧ��");
		}
		//B2nkbz_save(USERNAME, PASSWORD, DBNAME,NULL);
		return ifail;
	}

#ifdef __cplusplus
}
#endif

