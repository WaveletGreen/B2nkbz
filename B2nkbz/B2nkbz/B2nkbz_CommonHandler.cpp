#pragma warning(disable:4995 )

#include"B2nkbz_ActionHandler.h"
#include "epm_handler_common.h"
#include "error_handling.h"
#include "common_itk_util.h"
#include "string_helper.h"
#include <epm/epm.h>
#include <epm/epm_toolkit_tc_utils.h>
#include <ict/ict_userservice.h>
#include <tccore/item.h>
#include <ae/ae.h>
#include <tc/folder.h>
#include <tccore/aom.h>
#include <sa/sa.h>
#include <tccore/aom_prop.h>
#include <property/prop_errors.h>
#include <tccore/workspaceobject.h>
#include <tc/preferences.h>
#include <tccore/imantype.h>
#include <tccore//grm.h>
#include <tccore/grmtype.h>
#include <sa/am.h>
#include <cfm/cfm.h>
#include <bom/bom.h>
#include <tccore/uom.h>
#include <ps/ps.h>
#include <epm/signoff.h>
#include <fclasses/tc_date.h>
#include  "ocilib.h"
#include "DBHandler.h"

typedef struct
{
	string name;
	string value;
}CAD_ATTR_STRUCT;
extern "C" int POM_AM__set_application_bypass(logical bypass);
/**
* @headerfile			standard c & cpp header files
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
//#include <time.h>
//#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>

#include"Debug.h"
using namespace std;

int getPrefStrings(const char *preference, TC_preference_search_scope_t scope, vector<string> &pref_vec
)
{
	int ifail = ITK_ok, i = 0, j = 0, k = 0, num = 0;
	char **values;
	TC_preference_search_scope_t old_scope;
	ITKCALL(ifail = PREF_ask_search_scope(&old_scope));
	ITKCALL(ifail = PREF_set_search_scope(scope));
	ITKCALL(ifail = PREF_ask_char_values(preference, &num, &values));
	WriteLog("HeadTableNums=%d", num);
	for (i = 0; i < num; i++)
	{
		pref_vec.push_back(values[i]);
	}
	DOFREE(values);
	ITKCALL(ifail = PREF_set_search_scope(old_scope));
	return ifail;
}

void getMaxParam(int *src,int target) {
	*src = *src > target ? *src : target;
}
/*
----SubTable 子表名，与数据库名一致
*/
int B2nkbz_CommonHandler(EPM_action_message_t msg,const char* SubTable) {

	/*
	获取首选项，根据首先项值获取到各个表单上定义的字段
	*/
	/*头表的首选项*/
	Debug("开始获取首选项");
	vector<string> HeadTable_pref_vec;
	/*品质首选项*/
	vector<string> B2nkbzpzz_SubTable_pref_vec;
	/*获取头表的首选项*/
	getPrefStrings("B2nkbz_HeadTable", TC_preference_site, HeadTable_pref_vec);
	/*获取品质首选项"B2nkbzpzz"*/
	getPrefStrings(SubTable, TC_preference_site, B2nkbzpzz_SubTable_pref_vec);
	//标记首选项的记录数，首选项一共有几个值
	size_t HeadTableNums = 0;
	size_t SunTableNums = 0;
	//表单中参数个数，字表中有可能有数组类型的表单属性
	int SubTableParamsNums = 0;

	int HeadTableParamsNums = 0;
	//char ***subParams = NULL;
	//接收子表参数，是数组类型
	char **subParams = NULL;

	/**根据首选项的长度生成中间字段**/
	HeadTableNums = HeadTable_pref_vec.size();
	SunTableNums = B2nkbzpzz_SubTable_pref_vec.size();
	//测试输出
	Debug(HeadTableNums);
	Debug(SunTableNums);

	//获取表单中头表的值
	//char **HeadTableParams = (char**)calloc(HeadTableNums, sizeof(char*));
	char **HeadTableParams = NULL;

	//for (int i = 0; i < HeadTableNums; i++) {
	//	HeadTableParams[i] = NULL;
	//}
	//for (int i = 0; i < HeadTable_pref_vec.size(); i++) {
	//	Debug("进来这里");
	//	strcpy(HeadTableParams[i],HeadTable_pref_vec[i].c_str());
	//	Debug(HeadTableParams[i]);
	//	Debug("输出完成");
	//}
	//for (size_t i = 0; i < sizeof(HeadTableParams)/8; i++)
	//{
	//	Debug(HeadTableParams[i]);
	//}

	vector<char**> SubTableEachSQL;
	vector<char*> HeadTableEachParam;
	int *SubTableParamsCounter = (int*)calloc(SunTableNums, sizeof(int));

	Debug("结束获取首选项");
	//流程处理相关
	int ifail = ITK_ok, rcode = 0;
	int maxIndex = 0;
	//参数相关
	/*char arg1value[1024] = "", arg2value[1024] = "", arg3value[1024] = "", arg4value[1024] = "",
	signcounter_info[1024] = "", *value = NULL;
	char *argflag = NULL, *argvalue = NULL, *arg = NULL;*/
	//BOOL bypass = FALSE;
	int arg_cnt = 0;
	//流程节点相关
	tag_t root_task = NULLTAG, *sub_tasks = NULL, current_task = NULLTAG, type_tag = NULLTAG;
	//子任务计数
	int sub_task_count = 0;
	//任务名
	char root_task_name[128] = "", task_name[128] = "";
	//当前计数
	int occur_of_counts = 0;
	//附加再任务上的节点标记
	tag_t *taskAttches = NULLTAG;

	char tgt_type[WSO_name_size_c + 1] = "", type_class[TCTYPE_class_name_size_c + 1] = "";
	//////循环内部变量
	//tag_t cur_task = NULLTAG;
	//char task_type[WSO_name_size_c + 1] = "";
	////循环变量
	int count = 0;
	//item版本等
	tag_t itemrevision = NULLTAG, master_form_rel_type = NULLTAG;
	//int i = 0, j = 0, k = 0, count = 0, n = 0;
	////节点信息变量
	//char sign_info[2048] = "";
	//节点循环处理变量
	char rev_id[ITEM_id_size_c + 1] = "";
	tag_t item = NULLTAG;
	char item_id[ITEM_id_size_c + 1] = "";
	tag_t *form_list = NULL, master_form = NULLTAG;
	int form_count = 0;
	/*
	char local_path[128] = "";
	编制节点
	/*int s = 0;
	char *timeinfo2 = "";
	EPM_decision_t decision = EPM_nogo;
	tag_t aUserTag, responsibleParty;
	char *userName;
	date_t decision_date;
	char person_name[SA_name_size_c + 1] = "";
	char *prop_name = "last_mod_date";
	会签相关
	//int n_prop = 0, q = 0;
	//char **prop_names = NULL, hq_name[128] = "", hq_time_name[128] = "", *hq_value = NULL;
	//char exclude_type[256] = "", item_type[ITEM_type_size_c + 1] = "";
	//
	//logical is_sign = false;
	//current_task = msg.task;

	/*map<string, CAD_ATTR_STRUCT> sign_map;
	vector<string> prop_vec;
	CreateLogFile("PLA8_signoff",&txtfile);*/
	ECHO("=========================================================\n");
	ECHO("\t\t\t\%sHandler 开始执行\n",SubTable);
	ECHO("=========================================================\n");
	//获取参数个数，一般在建立流程模板的时候，可选的在handler中加入参数，该参数是有个数限制的
	arg_cnt = TC_number_of_arguments(msg.arguments);
	ECHO("参数个数为：%d\n", arg_cnt);
	//开旁路，开权限，否则某些用户无法操作
	POM_AM__set_application_bypass(true);

	//if (arg_cnt > 0)
	//{
	//	Debug("进入到>3<");
	//	for (i = 0; i<arg_cnt; i++)
	//	{
	//		Debug("进入到>4<");
	//		arg = TC_next_argument(msg.arguments);
	//		Debug(arg);
	//		ifail = ITK_ask_argument_named_value((const char*)arg, &argflag, &argvalue);
	//		Debug(argflag);
	//		if (stricmp(argflag, "SignName") == 0)
	//		{
	//			Debug("进入到>4<");
	//			if (argvalue != NULL)
	//			{
	//				Debug("进入到>4<");
	//				//strcpy(arg1value,argvalue);
	//				vector<string> ans, ans1;
	//				Split(argvalue, ";", ans);
	//				for (j = 0; j <ans.size(); j++)
	//				{
	//					CAD_ATTR_STRUCT	one_elem;
	//					Split(ans[j], "=", ans1);
	//					if (ans1.size() > 1)
	//					{
	//						one_elem.name = ans1[1];
	//						sign_map.insert(pair<string, CAD_ATTR_STRUCT>(ans1[0], one_elem));
	//					}
	//				}
	//			}
	//		}
	//		else if (stricmp(argflag, "bypass") == 0)
	//		{
	//			bypass = TRUE;
	//		}
	//	}
	//	MEM_free(argflag);
	//	MEM_free(argvalue);
	//}

	//获取属性
	EPM_ask_root_task(msg.task, &root_task);
	EPM_ask_sub_tasks(root_task, &sub_task_count, &sub_tasks);
	EPM_ask_attachments(root_task, EPM_target_attachment, &occur_of_counts, &taskAttches);
	ECHO("%d target attachment found\t", occur_of_counts);
	for (count = 0; count < occur_of_counts; count++)
	{
		ECHO("the %dth work", count);
		TCTYPE_ask_object_type(taskAttches[count], &type_tag);
		//询问类型
		ifail = TCTYPE_ask_class_name(type_tag, type_class);
		//获取类型
		ECHO("type_class : %s", type_class);
		//过滤掉非版本对象
		if (((strstr(type_class, "Revision") != NULL) || (strstr(type_class, "revision") != NULL))
			&& (strstr(type_class, "Master") == NULL) && (strstr(type_class, "master") == NULL)
			&& (strstr(type_class, "BOM") == NULL) && (strstr(type_class, "bom") == NULL) && (strstr(type_class, "Bom") == NULL))
		{
			itemrevision = taskAttches[count];
			ITEM_ask_rev_id(itemrevision, rev_id);

			//询问item
			ITEM_ask_item_of_rev(itemrevision, &item);
			//询问item_id
			ITEM_ask_id(item, item_id);
			//寻找关系
			char form_object_type[WSO_name_size_c + 1];
			GRM_find_relation_type(TC_master_form_rtype, &master_form_rel_type);
			GRM_list_secondary_objects_only(itemrevision, master_form_rel_type, &form_count, &form_list);

			printf("=====rfCount======%d\n", form_count);
			ITKCALL(WSOM_ask_object_type(form_list[0], form_object_type));
			printf("=====form_object_type======%s\n", form_object_type);
			{
				ITKCALL(AOM_lock(form_list[0]));
				{

					/****从这里获取form的信息****/
					/*获取头表的内容，头表中的内容是唯一的*/
					for (size_t i = 0; i < HeadTableNums; i++)
					{
						//测试，输出首选项的值
						//cout << ">>>" << HeadTable_pref_vec[i].c_str() << "<<<" << endl;
						//根据首选项获取表单上的内容
						//ITKCALL(AOM_ask_value_string(form_list[0], "b210", &HeadTableParams[i]));
						//Debug(HeadTableParams[i]);
						AOM_ask_value_strings(form_list[0], HeadTable_pref_vec[i].data(), &HeadTableParamsNums, &HeadTableParams);
						//测试
						if (HeadTableParamsNums <1) {
							HeadTableParams[0] = "";
						}
						HeadTableEachParam.push_back(HeadTableParams[0]);

					}
					Debug("进入测试获取字表内容");
					/*获取字表的内容，字表的内容是多值的（数组类型）*/
					for (size_t i = 0; i < SunTableNums; i++)
					{
						//根据首选项获取表单上的内容
						ITKCALL(AOM_ask_value_strings(form_list[0], B2nkbzpzz_SubTable_pref_vec[i].data(), &SubTableParamsNums, &subParams));

						Debug(SubTableParamsNums);
						SubTableParamsCounter[i] = SubTableParamsNums;
						SubTableEachSQL.push_back(subParams);
						getMaxParam(&maxIndex, SubTableParamsNums);
						for (size_t j = 0; j < SubTableParamsNums; j++)
						{
							Debug(SubTableEachSQL[i][j]);
						}

					}
				}

				char				*qrySQL;
				Debug("来这6");
				qrySQL = (char *)calloc(10240, sizeof(char));
				if (ConnServer(USERNAME, USERNAME, DBNAME) == -1)
				{
					ECHO("提示:ORACLE数据库登录失败\n");
					rcode = -1;
				}
				else
				{

					ECHO("提示:ORACLE数据库登录成功\n");
					string sql_HeadTable = "";
					string SqlSubTable = "";
					char ***HeadTableID = NULL;
					int SqlSubTableID = 0;
					int outputColumn = 0;
					int outputValueCount = 0;
					int isOK = -1;
					//根据sequence获取主表的id B2nkbz_HeadTable
					//string sStr_HeadTable_id = "";
					////动态拼接查询字符串
					//sStr_HeadTable_id.append("select seq_").append(HeadTable).append("_id.nextval from dual");
					char* Str_HeadTable_id = "select seq_b2nkbz_headtable_id.nextval from dual";
					//复制字符串
					//strcpy(Str_HeadTable_id, sStr_HeadTable_id.c_str());
					//查询获得id
					QuerySQLNoInputParam(Str_HeadTable_id, &outputColumn, &outputValueCount, &HeadTableID);
					//插入主表，动态插入语句，主表是一定要有的
					sql_HeadTable.append("insert into B2nkbz_HeadTable(B2nkbz_HeadTable_ID");
					for (size_t i = 0; i < HeadTableNums; i++)
					{
						sql_HeadTable.append(",").append(HeadTable_pref_vec[i]);
					}
					//测试用
					Debug(HeadTableID[0][0]);
					Debug(HeadTableNums);
					sql_HeadTable.append(") values(").append(HeadTableID[0][0]);
					for (size_t i = 0; i < HeadTableNums; i++)
					{
						sql_HeadTable.append(",'").append(HeadTableEachParam[i]).append("'");
					}
					sql_HeadTable.append(")");
					Debug("输出sql语句");
					strcpy(qrySQL, sql_HeadTable.c_str());
					//ECHO("DEBUG: %s\n", qrySQL);
					isOK=ExecuteSQLNoInputParam(qrySQL);
					/*rcode = ExecuteSQLNoInputParam("commit");*/
					/*插入子表,字表才是真正动态传进来的*/
					///*insert into B2nkbzpzz (B2NKBZ_HEADTABLE_ID,B2nkbzpzz_id,...) values(9,seq_B2nkbzpzz_id.nextval,'xxx','xxx')*/
					SqlSubTable.append("insert into ").append(SubTable).append(" (B2NKBZ_HEADTABLE_ID,").append(SubTable).append("_ID");
					for (size_t i = 0; i < SunTableNums; i++)
					{
						SqlSubTable.append(",").append(B2nkbzpzz_SubTable_pref_vec[i]);
					}
					SqlSubTable.append(") values(").append(HeadTableID[0][0]).append(",seq_").append(SubTable).append("_id.nextval");
					vector<string> SubTable_Sql;
					Debug("-------------------------------");
					Debug(maxIndex);
					Debug("-------------------------------");
					for (size_t i = 0; i < maxIndex; i++)
					{
						string subSql = "";
						subSql.append(SqlSubTable);
						for (size_t j = 0; j < SunTableNums; j++)
						{
							//Debug(SubTableEachSQL[j][i]);
							if (NULL == SubTableEachSQL[j]) {
								subSql.append(",''")/*.append(SubTableEachSQL[j][i]).append("'")*/;
							}
							else {		
								/*这里怎么获取数组的长度呢？*/
								if (i>=SubTableParamsCounter[j]) {
									subSql.append(",''")/*.append(SubTableEachSQL[j][i]).append("'")*/;
								}
								else
								{
									subSql.append(",'").append(SubTableEachSQL[j][i]).append("'");
								}
							}
						}
						subSql.append(")");
						Debug(subSql);
						SubTable_Sql.push_back(subSql);
					}
					Debug("开始插入数据");
					if (maxIndex > 0) {
						for (size_t i = 0; i < maxIndex; i++)
						{
							strcpy(qrySQL, SubTable_Sql[i].c_str());
							//ECHO("DEBUG: %s\n", qrySQL);
							isOK = ExecuteSQLNoInputParam(qrySQL);
						}
						
					}
					if (isOK == 0) {
						Debug("提交");
						rcode = ExecuteSQLNoInputParam("commit");
					}
					else
					{
						Debug("回滚");
						rcode = ExecuteSQLNoInputParam("rollback");
					}
					//释放
					free(qrySQL);
					ECHO("关闭ORACLE连接\n");
					DisConnServer();
				}
				Debug("到这里1");
				ITKCALL(AOM_save(form_list[0]));
				ITKCALL(AOM_unlock(form_list[0]));
				Debug("到这里2");
				ITKCALL(AOM_refresh(form_list[0], true));
			}
			Debug("到这里3");
			MEM_free(form_list);
		}
	}
	Debug("到这里3.5");
	//释放内存
	MEM_free(HeadTableParams);
	Debug("到这里4");
	MEM_free(subParams);
	Debug("到这里5");
	free(SubTableParamsCounter);
	//关闭旁路
	POM_AM__set_application_bypass(false);
	DOFREE(taskAttches);
	ECHO("=========================================================\n");
	ECHO("\%sHandler 执行结束\n",SubTable);
	ECHO("=========================================================\n");
	return rcode;
}