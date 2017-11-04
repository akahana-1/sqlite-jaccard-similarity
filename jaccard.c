#include <sqlite3ext.h>
#include <assert.h>
SQLITE_EXTENSION_INIT1

/*
 * @args sqlite3_context *context : 
 * @args int argc : SQLで呼び出された時の引数の数
 * @args sqlite3_value **argv : SQLで呼び出した時の引数が入ってる
 */
static void jaccardsim(sqlite3_context *context, int argc, sqlite3_value **argv){
	assert(sizeof(int) == 4);

	unsigned int *matchinfo = (unsigned int *)sqlite3_value_blob(argv[0]);
	int searchCol = sqlite3_value_int(argv[1]);
	double score;

	int P_OFFSET = 0;
	int C_OFFSET = 1;
	int L_OFFSET = 2;

	int phraseCount = matchinfo[P_OFFSET];
	int colCount = matchinfo[C_OFFSET];
	int searchColSize = matchinfo[L_OFFSET + searchCol];

	int X_OFFSET = L_OFFSET + colCount;

	int unionSize = searchColSize + phraseCount;
	int intersectionSize = 0;

	for(int i = 0;i < phraseCount;++i){
		int index = X_OFFSET + 3 * (i * colCount + searchCol);
		int phraseFreq = matchinfo[index];

		if(phraseFreq > 0) ++intersectionSize;
	}

	score = intersectionSize / (double)(unionSize - intersectionSize);

	sqlite3_result_double(context, score);
}

int sqlite3_extension_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi){
	int rc = SQLITE_OK;
	SQLITE_EXTENSION_INIT2(pApi);

	sqlite3_create_function(db, "jaccard", -1, SQLITE_UTF8, 0, jaccardsim, 0, 0);
	return rc;
}
