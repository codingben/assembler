#ifndef LOGGER_H
#define LOGGER_H

/* Log format is: sourcefile: message */
#define LOG_FORMAT "%s: %s"

/* Log format is: sourcefile:linenum: message */
#define LOG_LINE_FORMAT "%s:%d: %s"

/* Log format is: sourcefile:linenum:column: message */
#define LOG_LINE_COLUMN_FORMAT "%s:%d: %s"

#endif