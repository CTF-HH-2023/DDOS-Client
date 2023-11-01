#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>


void ddos(void){

    CURL *curl = curl_easy_init();
    CURLcode resolution;

  if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
        curl_easy_setopt(curl, CURLOPT_PORT, 443);

        resolution = curl_easy_perform(curl);

        if (resolution != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resolution));
        }

        curl_easy_cleanup(curl);
    }
}

int main(void) {

    struct addrinfo hints;
    struct addrinfo *result;

    const char *hostname = "cloud.elveli.net";


    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;  
    
    int exists = getaddrinfo(hostname, NULL, &hints, &result);

    if (exists == 0){
        printf("DNS exists. \n");
        freeaddrinfo(result);
        ddos();
    }

    else{
        printf("DNS doesn't exist or may have a problem");
    }
}
