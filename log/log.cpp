#include "log.h"

size_t log(FILE *fp, int log_level, char *format, ...)
{
	const char *level[5] = {"FETAL", "ERROR", "WARNNING", "INFO", "DEBUG"};
	if (fp == NULL)
		return 0;

	if (log_level < 0 || log_level > 3)	
		return 0;	
	
	struct timeb tb;	
	ftime(&tb);
	struct tm *pTm = localtime(&tb.time);
	char time[24] = {'\0'};
	sprintf(time, "%04d-%02d-%02d %02d:%02d:%02d:%03d", pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday, \
			pTm->tm_hour, pTm->tm_min, pTm->tm_sec, tb.millitm);

	va_list args;
	char log_buff[1024 * 1024] = {'\0'};
	va_start(args, format);
	vsprintf(log_buff, format, args);
	va_end(args);
	return fprintf(fp, "[%ld][%s][%s]%s\n", syscall(SYS_gettid), time, level[log_level], log_buff);
}
