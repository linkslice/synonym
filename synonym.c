#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256

// Enum for alias generation method
typedef enum {
    FIRST_LETTER,
    FIRST_TWO_LETTERS,
    FIRST_THREE_LETTERS
} AliasMethod;

// Enum for supported platforms
typedef enum {
    LINUX,
    MACOS,
    FREEBSD,
    OPENBSD,
    SOLARIS,
    AIX,
    HPUX,
    OTHER
} Platform;

// Function to print help screen
void print_help(const char* program_name) {
    printf("Usage: %s [-m method] [-f file] [-p] [-h] [-t target] <command>\n", program_name);
    printf("Options:\n");
    printf("  -m <method>   : Alias generation method\n");
    printf("                  1 : Use first letter of each word (default)\n");
    printf("                  2 : Use first two letters of each word\n");
    printf("                  3 : Use first three letters of each word\n");
    printf("  -f <file>     : Specify file to check for existing aliases (default: .profile)\n");
    printf("  -p            : Display a list of popular aliases\n");
    printf("  -h            : Display this help screen\n");
    printf("  -t <target>   : Specify target OS for alias generation (linux, macos, freebsd, openbsd, solaris, aix, hpux)\n");
}

// Function to print popular aliases
void print_popular_aliases() {
    printf("# Popular aliases people use:\n");
    printf("alias ll='ls -la'\n");
    printf("alias la='ls -A'\n");
    printf("alias l='ls -CF'\n");
    printf("alias grep='grep --color=auto'\n");
    printf("alias df='df -h'\n");
    printf("alias du='du -h'\n");
    printf("alias vi='vim'\n");
    printf("alias cls='clear'\n");
    printf("alias cpv='rsync -ah --info=progress2'\n");
    printf("alias mv='mv -i'\n");
}

// Function to generate a smart alias for a given command based on the chosen method
void generate_alias(const char* command, char* alias, AliasMethod method) {
    const char* delim = " ";
    char* token;
    char command_copy[MAX_LINE];
    strncpy(command_copy, command, MAX_LINE - 1);
    command_copy[MAX_LINE - 1] = '\0';

    token = strtok(command_copy, delim);
    int index = 0;

    // Create an alias based on the selected method
    while (token != NULL) {
        int chars_to_take = 1; // Default to first letter

        switch (method) {
            case FIRST_LETTER:
                chars_to_take = 1;
                break;
            case FIRST_TWO_LETTERS:
                chars_to_take = 2;
                break;
            case FIRST_THREE_LETTERS:
                chars_to_take = 3;
                break;
        }

        // Ensure that we do not exceed the token length
        for (int i = 0; i < chars_to_take && token[i] != '\0'; i++) {
            alias[index++] = tolower(token[i]);
        }

        token = strtok(NULL, delim);
    }
    alias[index] = '\0';
}

// Function to check if an alias already exists in the specified file
int check_alias_in_file(const char* alias, const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        return 0; // If the file doesn't exist, assume no collision
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        // Look for lines that define aliases
        if (strncmp(line, "alias ", 6) == 0) {
            char* token = strtok(line, "=");
            token += 6; // Skip 'alias ' part
            if (strcmp(token, alias) == 0) {
                fclose(file);
                return 1; // Alias already exists
            }
        }
    }
    fclose(file);
    return 0;
}

// Function to get the current platform
Platform detect_platform() {
    #ifdef __linux__
        return LINUX;
    #elif __APPLE__
        return MACOS;
    #elif __FreeBSD__
        return FREEBSD;
    #elif __OpenBSD__
        return OPENBSD;
    #elif __sun
        return SOLARIS;
    #elif _AIX
        return AIX;
    #elif __hpux
        return HPUX;
    #else
        return OTHER;
    #endif
}

// Function to print aliases for the target platform
void print_platform_aliases(Platform target) {
    switch (target) {
        case LINUX:
            print_popular_aliases();
            break;
        case MACOS:
            printf("# macOS-specific aliases:\n");
            printf("alias flushdns='sudo killall -HUP mDNSResponder'\n");
            printf("alias o='open .'\n");
            printf("alias battery='pmset -g batt'\n");
            printf("alias sysprof='sudo system_profiler'\n");
            printf("alias brewup='brew update && brew upgrade'\n");
            break;
        case FREEBSD:
            printf("# FreeBSD-specific aliases:\n");
            printf("alias pkginstall='sudo pkg install'\n");
            printf("alias portsup='sudo portsnap fetch update'\n");
            printf("alias fstat='fstat | grep $USER'\n");
            break;
        case OPENBSD:
            printf("# OpenBSD-specific aliases:\n");
            printf("alias pkgup='doas pkg_add -u'\n");
            printf("alias pfstat='doas pfctl -si'\n");
            printf("alias pflog='doas tcpdump -n -e -ttt -i pflog0'\n");
            break;
        case SOLARIS:
            printf("# Solaris-specific aliases:\n");
            printf("alias prstat='prstat -a'\n");
            printf("alias pvs='zpool status'\n");
            printf("alias svcs='svcs -xv'\n");
            break;
        case AIX:
            printf("# AIX-specific aliases:\n");
            printf("alias lsdev='lsdev -Cc adapter'\n");
            printf("alias lscpu='lsattr -El proc0'\n");
            printf("alias errpt='errpt -a'\n");
            break;
        case HPUX:
            printf("# HP-UX-specific aliases:\n");
            printf("alias ioscan='ioscan -fn'\n");
            printf("alias swapinfo='swapinfo -tam'\n");
            break;
        default:
            printf("# No specific aliases for this platform.\n");
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-m method] [-f file] [-p] [-h] [-t target] <command>\n", argv[0]);
        return 1;
    }

    // Default alias generation method and file
    AliasMethod method = FIRST_LETTER;
    const char* alias_file = ".profile"; // Default to checking .profile
    int print_popular = 0; // Flag to print popular aliases
    int show_help = 0;     // Flag to show help
    Platform target_platform = detect_platform(); // Detect the current platform

    // Parse command-line arguments for method flag, file flag, popular alias flag, help flag, and target flag
    int command_start = 1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            int method_choice = atoi(argv[i + 1]);
            switch (method_choice) {
                case 1:
                    method = FIRST_LETTER;
                    break;
                case 2:
                    method = FIRST_TWO_LETTERS;
                    break;
                case 3:
                    method = FIRST_THREE_LETTERS;
                    break;
                default:
                    fprintf(stderr, "Invalid method choice. Defaulting to first letter.\n");
                    method = FIRST_LETTER;
            }
            i += 1; // Skip past the method flag and choice
            command_start += 2;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            alias_file = argv[i + 1];
            i += 1; // Skip past the file flag and file name
            command_start += 2;
        } else if (strcmp(argv[i], "-p") == 0) {
            print_popular = 1; // Set flag to print popular aliases
            command_start += 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            show_help = 1; // Set flag to show help
            command_start += 1;
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "linux") == 0) {
                target_platform = LINUX;
                        } else if (strcmp(argv[i + 1], "macos") == 0) {
                target_platform = MACOS;
            } else if (strcmp(argv[i + 1], "freebsd") == 0) {
                target_platform = FREEBSD;
            } else if (strcmp(argv[i + 1], "openbsd") == 0) {
                target_platform = OPENBSD;
            } else if (strcmp(argv[i + 1], "solaris") == 0) {
                target_platform = SOLARIS;
            } else if (strcmp(argv[i + 1], "aix") == 0) {
                target_platform = AIX;
            } else if (strcmp(argv[i + 1], "hpux") == 0) {
                target_platform = HPUX;
            } else {
                fprintf(stderr, "Unknown target platform. Defaulting to current platform.\n");
            }
            i += 1; // Skip past the target flag and target name
            command_start += 2;
        }
    }

    if (show_help) {
        print_help(argv[0]);
        return 0;
    }

    if (print_popular) {
        print_platform_aliases(target_platform);
        return 0;
    }

    if (command_start >= argc) {
        fprintf(stderr, "No command provided.\n");
        return 1;
    }

    const char* command = argv[command_start];
    char alias[MAX_LINE];
    generate_alias(command, alias, method);

    // Check if alias already exists in the specified file
    if (check_alias_in_file(alias, alias_file)) {
        printf("# Alias '%s' already exists in '%s'\n", alias, alias_file);
    } else {
        printf("alias %s='%s'\n", alias, command);
    }

    return 0;
}
