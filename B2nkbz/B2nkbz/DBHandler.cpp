//#include <string>
//#include <map>
//#include  "ocilib.h"
//#include"common.h"
//using namespace std;
//int SaveOrUpdateItemRevision(char *oraUser, char *pwd, char *address, //map<string,int> &parts_vec,
//	int status)
//{
//	int					ifail = ITK_ok;
//	int					i = 0, j = 0, k = 0;
//	int					outputValueCount = 0, outputColumn = 0;
//	char				*** outputValue = NULL;
//	char				*qrySQL;
//	if (ConnServer(oraUser, pwd, address) == -1)
//	{
//		ECHO("��ʾ:ORACLE���ݿ��¼ʧ��\n");
//		return (1);
//	}
//	ECHO("��ʾ:ORACLE���ݿ��¼�ɹ�\n");
//	//qrySQL = (char *)calloc(10240, sizeof(char));
//	//��ѯ�㲿����
//	char temp[4096] = "";
//	/*for (i = 0; i < parts_vec.size(); i++)
//	{
//		strcat(temp, parts_vec[i].PartNumber.c_str());
//		if (i != parts_vec.size() - 1)
//			strcat(temp, ",");
//	}*/
//
//
//	//ִ�в�ѯ
//
//	/*sprintf(qrySQL, "update %s set received_status=%d where parent_number in (%s)", "Publish_Item_Revision", status, temp);
//	ECHO("DEBUG: %s\n", qrySQL);
//	ExecuteSQLNoInputParam(qrySQL);
//	ExecuteSQLNoInputParam("commit");*/
//	//�ͷ�
//	//free(qrySQL);
//	//for (i=0;i<outputValueCount;i++)
//	//{
//	//	for(j=0;j<outputColumn;j++)
//	//		free(outputValue[i][j]);
//	//	free(outputValue[i]);
//	//}	
//	//if(outputValue!=NULL)
//	//	free(outputValue);
//	//outputValue=NULL;
//	ECHO("�ر�ORACLE����\n");
//	DisConnServer();
//	return ifail;
//}