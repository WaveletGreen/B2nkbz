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
----SubTable �ӱ����������ݿ���һ��
*/
int B2nkbz_CommonHandler(EPM_action_message_t msg,const char* SubTable) {

	/*
	��ȡ��ѡ�����������ֵ��ȡ���������϶�����ֶ�
	*/
	/*ͷ�����ѡ��*/
	Debug("��ʼ��ȡ��ѡ��");
	vector<string> HeadTable_pref_vec;
	/*Ʒ����ѡ��*/
	vector<string> B2nkbzpzz_SubTable_pref_vec;
	/*��ȡͷ�����ѡ��*/
	getPrefStrings("B2nkbz_HeadTable", TC_preference_site, HeadTable_pref_vec);
	/*��ȡƷ����ѡ��"B2nkbzpzz"*/
	getPrefStrings(SubTable, TC_preference_site, B2nkbzpzz_SubTable_pref_vec);
	//�����ѡ��ļ�¼������ѡ��һ���м���ֵ
	size_t HeadTableNums = 0;
	size_t SunTableNums = 0;
	//���в����������ֱ����п������������͵ı�����
	int SubTableParamsNums = 0;

	int HeadTableParamsNums = 0;
	//char ***subParams = NULL;
	//�����ӱ����������������
	char **subParams = NULL;

	/**������ѡ��ĳ��������м��ֶ�**/
	HeadTableNums = HeadTable_pref_vec.size();
	SunTableNums = B2nkbzpzz_SubTable_pref_vec.size();
	//�������
	Debug(HeadTableNums);
	Debug(SunTableNums);

	//��ȡ����ͷ���ֵ
	//char **HeadTableParams = (char**)calloc(HeadTableNums, sizeof(char*));
	char **HeadTableParams = NULL;

	//for (int i = 0; i < HeadTableNums; i++) {
	//	HeadTableParams[i] = NULL;
	//}
	//for (int i = 0; i < HeadTable_pref_vec.size(); i++) {
	//	Debug("��������");
	//	strcpy(HeadTableParams[i],HeadTable_pref_vec[i].c_str());
	//	Debug(HeadTableParams[i]);
	//	Debug("������");
	//}
	//for (size_t i = 0; i < sizeof(HeadTableParams)/8; i++)
	//{
	//	Debug(HeadTableParams[i]);
	//}

	vector<char**> SubTableEachSQL;
	vector<char*> HeadTableEachParam;
	int *SubTableParamsCounter = (int*)calloc(SunTableNums, sizeof(int));

	Debug("������ȡ��ѡ��");
	//���̴������
	int ifail = ITK_ok, rcode = 0;
	int maxIndex = 0;
	//�������
	/*char arg1value[1024] = "", arg2value[1024] = "", arg3value[1024] = "", arg4value[1024] = "",
	signcounter_info[1024] = "", *value = NULL;
	char *argflag = NULL, *argvalue = NULL, *arg = NULL;*/
	//BOOL bypass = FALSE;
	int arg_cnt = 0;
	//���̽ڵ����
	tag_t root_task = NULLTAG, *sub_tasks = NULL, current_task = NULLTAG, type_tag = NULLTAG;
	//���������
	int sub_task_count = 0;
	//������
	char root_task_name[128] = "", task_name[128] = "";
	//��ǰ����
	int occur_of_counts = 0;
	//�����������ϵĽڵ���
	tag_t *taskAttches = NULLTAG;

	char tgt_type[WSO_name_size_c + 1] = "", type_class[TCTYPE_class_name_size_c + 1] = "";
	//////ѭ���ڲ�����
	//tag_t cur_task = NULLTAG;
	//char task_type[WSO_name_size_c + 1] = "";
	////ѭ������
	int count = 0;
	//item�汾��
	tag_t itemrevision = NULLTAG, master_form_rel_type = NULLTAG;
	//int i = 0, j = 0, k = 0, count = 0, n = 0;
	////�ڵ���Ϣ����
	//char sign_info[2048] = "";
	//�ڵ�ѭ���������
	char rev_id[ITEM_id_size_c + 1] = "";
	tag_t item = NULLTAG;
	char item_id[ITEM_id_size_c + 1] = "";
	tag_t *form_list = NULL, master_form = NULLTAG;
	int form_count = 0;
	/*
	char local_path[128] = "";
	���ƽڵ�
	/*int s = 0;
	char *timeinfo2 = "";
	EPM_decision_t decision = EPM_nogo;
	tag_t aUserTag, responsibleParty;
	char *userName;
	date_t decision_date;
	char person_name[SA_name_size_c + 1] = "";
	char *prop_name = "last_mod_date";
	��ǩ���
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
	ECHO("\t\t\t\%sHandler ��ʼִ��\n",SubTable);
	ECHO("=========================================================\n");
	//��ȡ����������һ���ڽ�������ģ���ʱ�򣬿�ѡ����handler�м���������ò������и������Ƶ�
	arg_cnt = TC_number_of_arguments(msg.arguments);
	ECHO("��������Ϊ��%d\n", arg_cnt);
	//����·����Ȩ�ޣ�����ĳЩ�û��޷�����
	POM_AM__set_application_bypass(true);

	//if (arg_cnt > 0)
	//{
	//	Debug("���뵽>3<");
	//	for (i = 0; i<arg_cnt; i++)
	//	{
	//		Debug("���뵽>4<");
	//		arg = TC_next_argument(msg.arguments);
	//		Debug(arg);
	//		ifail = ITK_ask_argument_named_value((const char*)arg, &argflag, &argvalue);
	//		Debug(argflag);
	//		if (stricmp(argflag, "SignName") == 0)
	//		{
	//			Debug("���뵽>4<");
	//			if (argvalue != NULL)
	//			{
	//				Debug("���뵽>4<");
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

	//��ȡ����
	EPM_ask_root_task(msg.task, &root_task);
	EPM_ask_sub_tasks(root_task, &sub_task_count, &sub_tasks);
	EPM_ask_attachments(root_task, EPM_target_attachment, &occur_of_counts, &taskAttches);
	ECHO("%d target attachment found\t", occur_of_counts);
	for (count = 0; count < occur_of_counts; count++)
	{
		ECHO("the %dth work", count);
		TCTYPE_ask_object_type(taskAttches[count], &type_tag);
		//ѯ������
		ifail = TCTYPE_ask_class_name(type_tag, type_class);
		//��ȡ����
		ECHO("type_class : %s", type_class);
		//���˵��ǰ汾����
		if (((strstr(type_class, "Revision") != NULL) || (strstr(type_class, "revision") != NULL))
			&& (strstr(type_class, "Master") == NULL) && (strstr(type_class, "master") == NULL)
			&& (strstr(type_class, "BOM") == NULL) && (strstr(type_class, "bom") == NULL) && (strstr(type_class, "Bom") == NULL))
		{
			itemrevision = taskAttches[count];
			ITEM_ask_rev_id(itemrevision, rev_id);

			//ѯ��item
			ITEM_ask_item_of_rev(itemrevision, &item);
			//ѯ��item_id
			ITEM_ask_id(item, item_id);
			//Ѱ�ҹ�ϵ
			char form_object_type[WSO_name_size_c + 1];
			GRM_find_relation_type(TC_master_form_rtype, &master_form_rel_type);
			GRM_list_secondary_objects_only(itemrevision, master_form_rel_type, &form_count, &form_list);

			printf("=====rfCount======%d\n", form_count);
			ITKCALL(WSOM_ask_object_type(form_list[0], form_object_type));
			printf("=====form_object_type======%s\n", form_object_type);
			{
				ITKCALL(AOM_lock(form_list[0]));
				{

					/****�������ȡform����Ϣ****/
					/*��ȡͷ������ݣ�ͷ���е�������Ψһ��*/
					for (size_t i = 0; i < HeadTableNums; i++)
					{
						//���ԣ������ѡ���ֵ
						//cout << ">>>" << HeadTable_pref_vec[i].c_str() << "<<<" << endl;
						//������ѡ���ȡ���ϵ�����
						//ITKCALL(AOM_ask_value_string(form_list[0], "b210", &HeadTableParams[i]));
						//Debug(HeadTableParams[i]);
						AOM_ask_value_strings(form_list[0], HeadTable_pref_vec[i].data(), &HeadTableParamsNums, &HeadTableParams);
						//����
						if (HeadTableParamsNums <1) {
							HeadTableParams[0] = "";
						}
						HeadTableEachParam.push_back(HeadTableParams[0]);

					}
					Debug("������Ի�ȡ�ֱ�����");
					/*��ȡ�ֱ�����ݣ��ֱ�������Ƕ�ֵ�ģ��������ͣ�*/
					for (size_t i = 0; i < SunTableNums; i++)
					{
						//������ѡ���ȡ���ϵ�����
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
				Debug("����6");
				qrySQL = (char *)calloc(10240, sizeof(char));
				if (ConnServer(USERNAME, USERNAME, DBNAME) == -1)
				{
					ECHO("��ʾ:ORACLE���ݿ��¼ʧ��\n");
					rcode = -1;
				}
				else
				{

					ECHO("��ʾ:ORACLE���ݿ��¼�ɹ�\n");
					string sql_HeadTable = "";
					string SqlSubTable = "";
					char ***HeadTableID = NULL;
					int SqlSubTableID = 0;
					int outputColumn = 0;
					int outputValueCount = 0;
					int isOK = -1;
					//����sequence��ȡ�����id B2nkbz_HeadTable
					//string sStr_HeadTable_id = "";
					////��̬ƴ�Ӳ�ѯ�ַ���
					//sStr_HeadTable_id.append("select seq_").append(HeadTable).append("_id.nextval from dual");
					char* Str_HeadTable_id = "select seq_b2nkbz_headtable_id.nextval from dual";
					//�����ַ���
					//strcpy(Str_HeadTable_id, sStr_HeadTable_id.c_str());
					//��ѯ���id
					QuerySQLNoInputParam(Str_HeadTable_id, &outputColumn, &outputValueCount, &HeadTableID);
					//����������̬������䣬������һ��Ҫ�е�
					sql_HeadTable.append("insert into B2nkbz_HeadTable(B2nkbz_HeadTable_ID");
					for (size_t i = 0; i < HeadTableNums; i++)
					{
						sql_HeadTable.append(",").append(HeadTable_pref_vec[i]);
					}
					//������
					Debug(HeadTableID[0][0]);
					Debug(HeadTableNums);
					sql_HeadTable.append(") values(").append(HeadTableID[0][0]);
					for (size_t i = 0; i < HeadTableNums; i++)
					{
						sql_HeadTable.append(",'").append(HeadTableEachParam[i]).append("'");
					}
					sql_HeadTable.append(")");
					Debug("���sql���");
					strcpy(qrySQL, sql_HeadTable.c_str());
					//ECHO("DEBUG: %s\n", qrySQL);
					isOK=ExecuteSQLNoInputParam(qrySQL);
					/*rcode = ExecuteSQLNoInputParam("commit");*/
					/*�����ӱ�,�ֱ����������̬��������*/
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
								/*������ô��ȡ����ĳ����أ�*/
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
					Debug("��ʼ��������");
					if (maxIndex > 0) {
						for (size_t i = 0; i < maxIndex; i++)
						{
							strcpy(qrySQL, SubTable_Sql[i].c_str());
							//ECHO("DEBUG: %s\n", qrySQL);
							isOK = ExecuteSQLNoInputParam(qrySQL);
						}
						
					}
					if (isOK == 0) {
						Debug("�ύ");
						rcode = ExecuteSQLNoInputParam("commit");
					}
					else
					{
						Debug("�ع�");
						rcode = ExecuteSQLNoInputParam("rollback");
					}
					//�ͷ�
					free(qrySQL);
					ECHO("�ر�ORACLE����\n");
					DisConnServer();
				}
				Debug("������1");
				ITKCALL(AOM_save(form_list[0]));
				ITKCALL(AOM_unlock(form_list[0]));
				Debug("������2");
				ITKCALL(AOM_refresh(form_list[0], true));
			}
			Debug("������3");
			MEM_free(form_list);
		}
	}
	Debug("������3.5");
	//�ͷ��ڴ�
	MEM_free(HeadTableParams);
	Debug("������4");
	MEM_free(subParams);
	Debug("������5");
	free(SubTableParamsCounter);
	//�ر���·
	POM_AM__set_application_bypass(false);
	DOFREE(taskAttches);
	ECHO("=========================================================\n");
	ECHO("\%sHandler ִ�н���\n",SubTable);
	ECHO("=========================================================\n");
	return rcode;
}