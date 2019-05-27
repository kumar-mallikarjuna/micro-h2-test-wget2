#include <stdio.h>
#include <string.h>
#include <microhttpd.h>
#include <microhttpd_http2.h>

static int _answer_to_connection (
	void *cls,
	struct MHD_Connection *connection,
	const char *url,
	const char *method,
	const char *version,
	const char *upload_data,
	size_t *upload_data_size,
	void **con_cls)
{
	if (strcmp (method, "GET") != 0){
		fprintf(stderr, "Wrong method.");

		return MHD_NO;
	}

	const char *response_str = "Hola";

	struct MHD_Response *response = MHD_create_response_from_buffer (strlen (response_str), response_str, MHD_RESPMEM_PERSISTENT);

	int ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
	MHD_destroy_response (response);

	printf("%s\n", version);
	return ret;
}

int main () {
	struct MHD_Daemon *d;
	int port = 1312;

	char cert_pem[2500];
	char key_pem[10000];

	FILE *f;

	f = fopen("./certs/x509-server-cert.pem","r");
	int i=0;
	char ch;
	while((ch = fgetc(f)) != EOF){
		cert_pem[i] = ch;
		i++;
	}
	cert_pem[i] = '\0';
	fclose(f);
	f = fopen("./certs/x509-server-key.pem","r");
	i=0;
	while((ch = fgetc(f)) != EOF){
		key_pem[i] = ch;
		i++;
	}
	key_pem[i] = '\0';
	fclose(f);

	d = MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION | MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_ERROR_LOG | MHD_USE_TLS | MHD_USE_HTTP2,
	port, NULL, NULL, &_answer_to_connection, NULL, MHD_OPTION_HTTPS_MEM_KEY, key_pem, MHD_OPTION_HTTPS_MEM_CERT, cert_pem, MHD_OPTION_END);

	if(d == NULL){
		fprintf(stderr, "Could not start HTTP/2 server.");
	}

	getc(stdin);

	return 0;
}
