#ifndef LOGGER_H
#define LOGGER_H

/* 
 * Log Formats:
 */

/* Log format is: sourcefile: message */
#define LOG_FORMAT "%s: %s"

/* Log format is: sourcefile:linenum: message */
#define LOG_LINE_FORMAT "%s:%d: %s"

/* Log format is: sourcefile:linenum:column: message */
#define LOG_LINE_COLUMN_FORMAT "%s:%d: %s"

/* 
 * Error Formats:
 */

/* Log format is: sourcefile: message */
#define ERROR_FORMAT "%s: error: %s"

/* Log format is: sourcefile:linenum: message */
#define ERROR_LINE_FORMAT "%s:%d: error: %s"

/* Log format is: sourcefile:linenum:column: message */
#define ERROR_LINE_COLUMN_FORMAT "%s:%d: error: %s"

#endif