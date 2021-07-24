#ifndef MESSAGES_H
#define MESSAGES_H

#define NO_FILE_TO_COMPILE "error: could not find an assembly file to compile.\n"
#define NO_AS_EXTENSION "error: an assembly file must be with .as extension.\n"
#define FAILED_OPEN_FILE "error: unable to open the assembly file." /* No need '\n' here because used in perror(...). */

#endif