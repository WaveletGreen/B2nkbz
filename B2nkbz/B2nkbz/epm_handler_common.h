/** 
* @addtogroup			handler
* @{
*/

/**
* @file					epm_handler_common.h
* @brief				handler functions declation
* @date					2011/4/12
* @author				Ray
* @history
* ===================================================================================
* Date					Name				Description
* 12-Apr-2011			Ray				created
*/


#ifndef EPM_HANDLER_COMMON
#define EPM_HANDLER_COMMON

#include <epm/epm.h>
#include <string>
#include <map>


#ifdef __cplusplus
extern "C" {
#endif


	using namespace std;


#define TC_specification	"IMAN_specification"
//#define NX_3W_DATASET_TYPE		"UGMASTER"
//#define NX_2W_DATASET_TYPE		"UGPART"
//#define DATASET_REF_TYPE		"UGPART"
int ORIGIN_set_bypass(void *returnValue);
int USERSEVICE_TEST(void * returnValue);
int ORIGIN_close_bypass(void *returnValue);
int jf_sign_ir_master(EPM_action_message_t msg);

int check_target_null( EPM_rule_message_t msg );
int tm_sign_tongzhi(EPM_action_message_t msg);
int tm_show_object_name(EPM_action_message_t msg);
	//user service end
#ifdef __cplusplus
}
#endif

#endif 


/**
* @}
*/