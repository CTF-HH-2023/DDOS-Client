> ⚠️ This is a client for educational purpose, used for a scenarios during a ctf organized by 2 university. We will not support the usage outside the CTF context.

# DDOS-Client
A simple ddos client written in C to reverse.

## Usage
1. Clone the repository
2. Compile the client
    ```bash
    gcc -o ddos ddos.c -lcurl
    ```
3. Run
   ```bash
   ./ddos [FLAG]
   ```
4. Analyze and reverse the client

## Optional
### Botnet
* Remove the .example extension to the credentials.csv file
* Edit the file with the following structure
   ``username;password;ip;port``

## Requirements
### Dependencies
| Name                 | Context      | Required |
|:---------------------|:-------------|:--------:|
| libcurl4-openssl-dev | Compile      |    ✔️    |
| sshpass              | Run - Botnet |    ❌     |
| openssh-client       | Run - Botnet |    ❌     |

## File for participants
```bash
./build.sh
```

## Writeups
By reversing the code and analyzing the network traffic, participants should notice:

### Program's behavior
* To run the code, the program needs one specific argument (i.e. the flag).
* The program will try to launch a botnet.
* As long as the DNS query fails, the ddos continues.
* Get requests are sent on the targeted website.

### Interesting values
* Flag (i.e. the argument): `HHCTF{R3v3r51n9_C_15_T00_3a5y}`
* DNS entry checked: `stopattack.killer`
* Targeted website: `wafflevikings.hh`
* User-Agent used by the client: `RedStarBrowser/3.0 (XK-256; Zarnitsa OS x86_64)`