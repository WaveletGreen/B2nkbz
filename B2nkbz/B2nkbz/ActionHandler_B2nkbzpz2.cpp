//#pragma warning(disable:4995 )
//
//#include"B2nkbz_ActionHandler.h"
//#include "epm_handler_common.h"
//#include "error_handling.h"
//#include "common_itk_util.h"
//#include "string_helper.h"
//#include <epm/epm.h>
//#include <epm/epm_toolkit_tc_utils.h>
//#include <ict/ict_userservice.h>
//#include <tccore/item.h>
//#include <ae/ae.h>
//#include <tc/folder.h>
//#include <tccore/aom.h>
//#include <sa/sa.h>
//#include <tccore/aom_prop.h>
//#include <property/prop_errors.h>
//#include <tccore/workspaceobject.h>
//#include <tc/preferences.h>
//#include <tccore/imantype.h>
//#include <tccore//grm.h>
//#include <tccore/grmtype.h>
//#include <sa/am.h>
//#include <cfm/cfm.h>
//#include <bom/bom.h>
//#include <tccore/uom.h>
//#include <ps/ps.h>
//#include <epm/signoff.h>
//#include <fclasses/tc_date.h>
//
//
//typedef struct
//{
//	string name;
//	string value;
//}CAD_ATTR_STRUCT;
//extern "C" int POM_AM__set_application_bypass(logical bypass);
///**
//* @headerfile			standard c & cpp header files
//*/
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
////#include <time.h>
////#include <math.h>
//#include <string>
//#include <vector>
//#include <map>
//#include <fstream>
//#include <iostream>
//#include <algorithm>
//#include <time.h>
//
//#include"Debug.h"
//using namespace std;
///*
//##################################################################################
//
//
//
//��ȡ���ڿر�׼-Ʒ�ʡ����ϵ����ݲ����ݵ��м����
//
//
//
//#################################################################################*/
//int ActionHandler_B2nkbzpz2(EPM_action_message_t msg)
//{
//	int create_signinfo_file2(char *file_content, char *item_id, char **file_name);
//	int ifail = ITK_ok, rcode = 0;
//	//�������
//	char arg1value[1024] = "", arg2value[1024] = "", arg3value[1024] = "", arg4value[1024] = "",
//		signcounter_info[1024] = "", *value = NULL;
//	char *argflag = NULL, *argvalue = NULL, *arg = NULL;
//	BOOL bypass = FALSE;
//	int arg_cnt = 0;
//	//���̽ڵ����
//	tag_t root_task = NULLTAG, *sub_tasks = NULL, current_task = NULLTAG, type_tag = NULLTAG;
//	int sub_task_count = 0;
//	char root_task_name[128] = "", task_name[128] = "";
//	int occur_of_counts = 0;
//	tag_t *taskAttches = NULLTAG;
//	char tgt_type[WSO_name_size_c + 1] = "", type_class[TCTYPE_class_name_size_c + 1] = "";
//	////ѭ���ڲ�����
//	tag_t cur_task = NULLTAG;
//	char task_type[WSO_name_size_c + 1] = "";
//	//ѭ������
//	int i = 0, j = 0, k = 0, count = 0, n = 0;
//	//�ڵ���Ϣ����
//	char sign_info[2048] = "";
//	//�ڵ�ѭ���������
//	tag_t itemrevision = NULLTAG, master_form_rel_type = NULLTAG;
//	char rev_id[ITEM_id_size_c + 1] = "";
//	char item_id[ITEM_id_size_c + 1] = "";
//	int form_count = 0;
//	tag_t *form_list = NULL, master_form = NULLTAG;
//	char local_path[128] = "";
//	//���ƽڵ�
//	int s = 0;
//	char *timeinfo2 = "";
//	EPM_decision_t decision = EPM_nogo;
//	tag_t aUserTag, responsibleParty;
//	char *userName;
//	date_t decision_date;
//	char person_name[SA_name_size_c + 1] = "";
//	char *prop_name = "last_mod_date";
//	//��ǩ���
//	int n_prop = 0, q = 0;
//	char **prop_names = NULL, hq_name[128] = "", hq_time_name[128] = "", *hq_value = NULL;
//	char exclude_type[256] = "", item_type[ITEM_type_size_c + 1] = "";
//	tag_t item = NULLTAG;
//	logical is_sign = false;
//
//	map<string, CAD_ATTR_STRUCT> sign_map;
//	vector<string> prop_vec;
//	current_task = msg.task;
//	//CreateLogFile("PLA8_signoff",&txtfile);
//	ECHO("=========================================================\n");
//	ECHO("\t\t\tB2nkbzpzHandler ��ʼִ��\n");
//	ECHO("=========================================================\n");
//
//	Debug("���뵽>1<");
//	arg_cnt = TC_number_of_arguments(msg.arguments);
//	ECHO("��������Ϊ��%d\n", arg_cnt);
//	POM_AM__set_application_bypass(true);
//	Debug("���뵽>2<");
//	//��ȡ����
//	EPM_ask_root_task(msg.task, &root_task);
//	Debug(root_task);
//	EPM_ask_sub_tasks(root_task, &sub_task_count, &sub_tasks);
//	Debug(sub_task_count);
//	Debug(*sub_tasks);
//	EPM_ask_attachments(root_task, EPM_target_attachment, &occur_of_counts, &taskAttches);
//	ECHO("%d target attachment found\t", occur_of_counts);
//	/*��Ʒ��*/
//	char *b21;
//	/*��Ʒ��*/
//	char *b22;
//	/*Ʒ��*/
//	char *b23;
//	/*���*/
//	char *b24;
//	/*����*/
//	char *b25;
//	/*״̬��*/
//	char *b26;
//	/*�汾*/
//	char *b27;
//	/*������*/
//	char *b28;
//	/*��������*/
//	char *b29;
//	/*�����*/
//	char*b210;
//	/*�������*/
//	char *b211;
//	/*�����Ŀ���*/
//	char **b212;
//	/*������*/
//	char **b213;
//	/*�����Ŀ*/
//	char **b214;
//	/*�������*/
//	char **b215;
//	/*��λ*/
//	char **b216;
//	/*���ұ�׼��*/
//	char **b217;
//	/*��ҵ��׼��*/
//	char **b218;
//	/*����λ*/
//	char **b219;
//	/*��Ҫ��*/
//	char **b220;
//	/*���Ʊ�׼*/
//	char **b221;
//	/*������׼*/
//	char **b222;
//	/*�ռ�Ƶ��*/
//	char **b223;
//	/*��ע*/
//	char **b224;
//	/*��������ֵ*/
//	int num;
//	char *b[11] = {b21,b22,b23,b24,b25,b26,b27,b28,b29,b210,b211};
//	for (count = 0; count<occur_of_counts; count++)
//	{
//		ECHO("the %dth work", count);
//		TCTYPE_ask_object_type(taskAttches[count], &type_tag);
//		ifail = TCTYPE_ask_class_name(type_tag, type_class);
//		//��ȡ����
//		ECHO("type_class : %s", type_class);
//
//		//���˵��ǰ汾����
//		if (((strstr(type_class, "Revision") != NULL) || (strstr(type_class, "revision") != NULL))
//			&& (strstr(type_class, "Master") == NULL) && (strstr(type_class, "master") == NULL)
//			&& (strstr(type_class, "BOM") == NULL) && (strstr(type_class, "bom") == NULL) && (strstr(type_class, "Bom") == NULL))
//		{
//			itemrevision = taskAttches[count];
//			ITEM_ask_rev_id(itemrevision, rev_id);
//			//����
//			cout << "�汾id=" << rev_id << endl;
//			//ѯ��item
//			ITEM_ask_item_of_rev(itemrevision, &item);
//			//ѯ��item_id
//			ITEM_ask_id(item, item_id);
//			//Ѱ�ҹ�ϵ
//			char form_object_type[WSO_name_size_c + 1];
//			GRM_find_relation_type(TC_master_form_rtype, &master_form_rel_type);
//			GRM_list_secondary_objects_only(itemrevision, master_form_rel_type, &form_count, &form_list);
//			Debug("���뵽>3<");
//			printf("=====form_count======%d\n", form_count);
//			ITKCALL(WSOM_ask_object_type(form_list[0], form_object_type));
//			printf("=====form_object_type======%s\n", form_object_type);
//			{
//				ITKCALL(AOM_lock(form_list[0]));
//				{
//					/****�������ȡform����Ϣ****/
//					//��Ʒ��
//					ITKCALL(AOM_ask_value_string(form_list[0], "b21", &b21));
//					Debug(b21);
//					//��Ʒ��
//					ITKCALL(AOM_ask_value_string(form_list[0], "b22", &b22));
//					Debug(b22);
//					//Ʒ��
//					ITKCALL(AOM_ask_value_string(form_list[0], "b23", &b23));
//					Debug(b23);
//					//���
//					ITKCALL(AOM_ask_value_string(form_list[0], "b24", &b24));
//					Debug(b24);
//					//����
//					ITKCALL(AOM_ask_value_string(form_list[0], "b25", &b25));
//					Debug(b25);
//					//״̬
//					ITKCALL(AOM_ask_value_string(form_list[0], "b26", &b26));
//					Debug(b26);
//					//�汾
//					ITKCALL(AOM_ask_value_string(form_list[0], "b27", &b27));
//					Debug(b27);
//					//������
//					ITKCALL(AOM_ask_value_string(form_list[0], "b28", &b28));
//					Debug(b28);
//					//��������
//					ITKCALL(AOM_ask_value_string(form_list[0], "b29", &b29));
//					Debug(b29);
//					//�����
//					ITKCALL(AOM_ask_value_string(form_list[0], "b210", &b210));
//					Debug(b210);
//					//�������
//					ITKCALL(AOM_ask_value_string(form_list[0], "b211", &b211));
//					Debug(b211);
//					ITKCALL(AOM_ask_value_strings(form_list[0], "b212", &num,&b212));
//					for (size_t i = 0; i < num; i++)
//					{
//						Debug(b212[i]);
//
//					}
//					ITKCALL(AOM_save(form_list[0]));
//					
//				}
//				ITKCALL(AOM_unlock(form_list[0]));
//				ITKCALL(AOM_refresh(form_list[0], true));
//			}
//			for (size_t i = 0; i < sizeof(b)/8; i++)
//			{
//				MEM_free(b[i]);
//			}
//			MEM_free(form_list);
//
//		}
//	}
//
//
//
//	POM_AM__set_application_bypass(false);
//	DOFREE(taskAttches);
//	ECHO("=========================================================\n");
//	ECHO("ActionHandler_B2nkbzpz ִ�н���\n");
//	ECHO("=========================================================\n");
//	return rcode;
//}
//
//int create_signinfo_file2(char *file_content, char *item_id, char **file_name)
//{
//	time_t now;
//	struct tm *p;
//	FILE *filePtr = NULL;
//
//	char *temp_dir = getenv("TEMP");
//	char local_path[MAX_PATH] = "";
//
//	time(&now);
//	p = localtime(&now);
//	if (temp_dir[strlen(temp_dir) - 1] == '\\')
//	{
//		sprintf_s(local_path, "%s%s-%d-%d-%d-%d-%d-%d.dat", temp_dir, item_id,
//			1900 + p->tm_year, p->tm_mon + 1, p->tm_mday + 1, p->tm_hour, p->tm_min, p->tm_sec);
//	}
//	else
//	{
//		sprintf_s(local_path, "%s\\%s-%d-%d-%d-%d-%d-%d.dat", temp_dir, item_id,
//			1900 + p->tm_year, p->tm_mon + 1, p->tm_mday + 1, p->tm_hour, p->tm_min, p->tm_sec);
//	}
//
//	if ((filePtr = fopen(local_path, "wt")) == NULL)
//	{
//		printf("Can not create the temp dat file!\n");
//		return -1;
//	}
//	*file_name = (char *)MEM_alloc(sizeof(char) * 512);
//	strcpy((*file_name), local_path);
//
//	fwrite(file_content, sizeof(char), strlen(file_content), filePtr);
//	fclose(filePtr);
//
//	return ITK_ok;
//}