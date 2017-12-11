/**
* @file common_itk_util.h
* @brief itk warpper utility function 
* @author James
* @history
* ===================================================================================
* Date             Name                   Description of Change
* 09-July-2008     James                  
*/
#include <vector>
#ifndef COMMON_ITK_UTIL
#define COMMON_ITK_UTIL

#ifdef __cplusplus
extern "C" {
#endif

#define DOFREE(obj)								\
{												\
	if(obj)										\
	{											\
		MEM_free(obj);							\
		obj = NULL;								\
	}											\
}
void ECHO(char *format, ...);
void CreateLogFile(char* FunctionName, char **fullname);
void WriteLog(const char* format, ...);
void CloseLog(void);
void set_bypass(logical bypass);
int getPrefStrings(const char *preference, TC_preference_search_scope_t scope, vector<string> &pref_vec);
//int FindDatasetReferenceExt( tag_t datasettype, const char *datasettype_ref, char ext[10] );
//int CompareDate( date_t date1, date_t date2 );
//int GetRandomTempFile( char tempFile[256] );
//logical IsItemRevisionType( char object_type[WSO_name_size_c + 1] );

#ifdef __cplusplus
}
#endif

#endif