// students_api.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students_api.h"
#include "students_db.h"

enum MHD_Result answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url,
                         const char *method, const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    const char *json_response;
    struct MHD_Response *response;
    int ret;

    if (strcmp(url, "/create") == 0 && strcmp(method, "POST") == 0) {
        const char *name = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");
        const char *age_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "age");
        int age = age_str ? atoi(age_str) : 0;
        if (name && age && create_student(name, age)) {
            json_response = "{\"status\":\"success\"}";
        } else {
            json_response = "{\"status\":\"error\"}";
        }
    } else if (strcmp(url, "/read") == 0 && strcmp(method, "GET") == 0) {
        json_response = read_students();
    } else if (strcmp(url, "/update") == 0 && strcmp(method, "PUT") == 0) {
        const char *id_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "id");
        const char *name = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");
        const char *age_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "age");
        int id = id_str ? atoi(id_str) : 0;
        int age = age_str ? atoi(age_str) : 0;
        if (id && name && age && update_student(id, name, age)) {
            json_response = "{\"status\":\"success\"}";
        } else {
            json_response = "{\"status\":\"error\"}";
        }
    } else if (strcmp(url, "/delete") == 0 && strcmp(method, "DELETE") == 0) {
        const char *id_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "id");
        int id = id_str ? atoi(id_str) : 0;
        if (id && delete_student(id)) {
            json_response = "{\"status\":\"success\"}";
        } else {
            json_response = "{\"status\":\"error\"}";
        }
    } else {
        json_response = "{\"status\":\"unknown endpoint\"}";
    }

    response = MHD_create_response_from_buffer(strlen(json_response), (void *)json_response, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    if (initialize_database()) {
        struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
        if (NULL == daemon) return 1;

        printf("Server is running on http://localhost:%d\n", PORT);
        getchar();  // Wait for user input to terminate
        MHD_stop_daemon(daemon);
    } else {
        fprintf(stderr, "Database initialization failed.\n");
    }

    close_database();
    return 0;
}

