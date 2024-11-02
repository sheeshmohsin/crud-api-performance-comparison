// students_api.h
#ifndef STUDENTS_API_H
#define STUDENTS_API_H

#include <microhttpd.h>

#define PORT 8888

enum MHD_Result answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url,
                         const char *method, const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls);

#endif // STUDENTS_API_H

