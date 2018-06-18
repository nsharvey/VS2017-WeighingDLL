// This file has been generated automatically from ../../src/sysmsg.cpp.
// Language: en_US
// Encoding: US-ASCII
with (Ilog) {
   // Stream messages
  SetMessage("IO_READ_ERROR",
              "read error");
  SetMessage("IO_LINE_TOO_LONG",
              "line too long (max %0 characters)");
   // Tokenizer messages
  SetMessage("TOKEN_BAD_DIGIT",
              "bad digit %0");
  SetMessage("TOKEN_INT_OVERFLOW",
              "overflow in integral constant");
  SetMessage("TOKEN_FLOAT_OVERFLOW",
              "overflow in floating-point constant");
  SetMessage("TOKEN_FLOAT_UNDERFLOW",
              "underflow in floating-point constant");
  SetMessage("TOKEN_BAD_EXPONENT",
              "bad floating-point number exponent");
  SetMessage("TOKEN_NEWLINE_STRING",
              "newline in a string");
  SetMessage("TOKEN_EOS_STRING",
              "end of stream in a string");
  SetMessage("TOKEN_BAD_STRING_ESCAPE",
              "bad escape sequence '%0'");
  SetMessage("TOKEN_BAD_CHAR",
              "illegal character %0");
  SetMessage("TOKEN_EOS_COMMENT",
              "end of stream in a comment");
   // Parser messages
  SetMessage("PARSE_ELSE_NO_IF",
              "'else' without a 'if'");
  SetMessage("PARSE_IN_WITHOUT_FOR",
              "'in' can be used only in a 'for/in' loop");
  SetMessage("PARSE_RESERVED",
              "illegal use of a reserved keyword");
  SetMessage("PARSE_TOO_MANY_CPAREN",
              "too many ')'");
  SetMessage("PARSE_TOO_MANY_CBRACE",
              "too many '}'");
  SetMessage("PARSE_TOO_MANY_CBRACKET",
              "missing '['");
  SetMessage("PARSE_MISSING_SEMI",
              "missing ';'");
  SetMessage("PARSE_MISSING_COLON",
              "missing ':'");
  SetMessage("PARSE_MISSING_NEWLINE_OR_SEMI",
              "missing ';' or newline between statements");
  SetMessage("PARSE_MISSING_OBRACE",
              "missing '{'");
  SetMessage("PARSE_MISSING_CBRACE",
              "missing '}'");
  SetMessage("PARSE_MISSING_OPAREN",
              "missing '('");
  SetMessage("PARSE_MISSING_CPAREN",
              "missing ')'");
  SetMessage("PARSE_MISSING_CBRACKET",
              "missing ']'");
  SetMessage("PARSE_MISSING_VAR_IDENT",
              "missing variable name");
  SetMessage("PARSE_MISSING_FUN_IDENT",
              "missing function name");
  SetMessage("PARSE_MISSING_PARAM_LIST",
              "missing '(' for starting parameter list");
  SetMessage("PARSE_MISSING_PARAM_IDENT",
              "bad parameter name");
  SetMessage("PARSE_MISSING_COMMA",
              "missing ','");
  SetMessage("PARSE_MISSING_FOR_IN_VAR",
              "missing loop variable");
  SetMessage("PARSE_MISSING_EXP",
              "missing expression");
  SetMessage("PARSE_BAD_PROPNAME",
              "bad property name");
  SetMessage("PARSE_MISSING_FUN_DECLARATION",
              "missing function declaration");
   // Compiler messages
  SetMessage("COM_VAR_REDECLARED",
              "multiple declarations for '%0'");
  SetMessage("COM_REPEATED_PARAM",
              "repeated parameter '%0'");
  SetMessage("COM_NOT_LVALUE",
              "this expression cannot be assigned");
  SetMessage("COM_NOT_ONE_INDEX",
              "the '[]' operator requires one argument");
  SetMessage("COM_RETURN_OUTSIDE_FUN",
              "'return' outside of a function");
  SetMessage("COM_BREAK_OUTSIDE_LOOP",
              "'break' outside of a loop");
  SetMessage("COM_CONTINUE_OUTSIDE_LOOP",
              "'continue' outside of a loop");
  SetMessage("COM_BAD_DECL_SYNTAX",
              "bad declaration syntax");
  SetMessage("COM_NESTED_FUNCTION_DEF",
              "cannot define nested functions");
  SetMessage("COM_EVAL_FUNCTION_DEF",
              "cannot define functions in eval");
  SetMessage("COM_DEBUGGER_FUNCTION_DEF",
              "cannot define functions in the debugger");
  SetMessage("COM_FORBIDDEN_FUNCTION_DEF",
              "function definitions are not allowed");
  SetMessage("COM_FUNCTION_DEF_ONLY",
              "only function definitions are allowed");
   // Tester messages
  SetMessage("TEST_MISSING_CHECK_CLAUSE",
              "missing check clause in test");
  SetMessage("TEST_MISSING_MSG_IDENT",
              "missing error identifier");
  SetMessage("TEST_STMT_NOT_BOL",
              "statement does not start at column 0");
  SetMessage("TEST_CHECK_NOT_BOL",
              "check clause does not start at column 0");
   // Errors
  SetMessage("ERROR_WARNING",
              "Warning");
  SetMessage("ERROR_LINE",
              "line");
  SetMessage("ERROR_USER_INTERRUPTION",
              "User interruption!");
  SetMessage("ERROR_IN_TOSTRING",
              "error when converting to a string");
   // Runtime error messages
  SetMessage("RT_NOT_FUNCTION",
              "not a function");
  SetMessage("RT_NOT_CONSTRUCTOR",
              "not a constructor");
  SetMessage("RT_CANNOT_ADD_PROPERTIES",
              "cannot add properties to this value");
  SetMessage("RT_CANNOT_SET_PROPERTY",
              "cannot set the '%0' property");
  SetMessage("RT_CANNOT_DELETE_PROPERTY",
              "cannot delete the '%0' property");
  SetMessage("RT_CANNOT_ADD_LOCAL_VAR",
              "cannot create a local variable");
  SetMessage("RT_CANNOT_DELETE_LOCAL_VAR",
              "cannot delete a local variable");
  SetMessage("RT_CANNOT_CONVERT_TO_NUMBER",
              "cannot convert to a number");
  SetMessage("RT_CANNOT_CONVERT_TO_INT",
              "cannot convert to an integer");
  SetMessage("RT_UNKNOWN_VAR",
              "unknown variable '%0'");
  SetMessage("RT_UNKNOWN_FUNCTION",
              "unknown function '%0'");
  SetMessage("RT_UNKNOWN_METHOD",
              "undefined method '%0'");
  SetMessage("RT_UNKNOWN_PROPERTY",
              "unknown property '%0'");
  SetMessage("RT_ARGUMENTS_OUTSIDE_FUN",
              "'arguments' referenced outside of a function");
  SetMessage("RT_TOO_MANY_ARGS",
              "too many arguments");
  SetMessage("RT_NOT_ENOUGH_ARGS",
              "not enough arguments");
  SetMessage("RT_DISPLACED_METHOD",
              "method applied to the wrong object type");
  SetMessage("RT_EVAL_COMPILATION",
              "parser error: %0");
  SetMessage("RT_NOT_POSITIVE_INT",
              "not a positive integer");
  SetMessage("RT_STACK_OVERFLOW",
              "stack overflow");
  SetMessage("RT_BAD_DATE_SYNTAX",
              "incorrect date syntax");
  SetMessage("RT_SORT_FN_BAD_RETURN",
              "incorrect return value for a comparison function");
  SetMessage("RT_CANNOT_READ_FILE",
              "cannot open file %0");
  SetMessage("RT_CANNOT_FIND_FILE",
              "cannot find file %0");
  SetMessage("RT_LOAD_COMPILATION",
              "syntax error: %0");
  SetMessage("RT_DELETED_PROXY",
              "reference to a deleted object");
  SetMessage("RT_WRONG_TYPE",
              "not of type '%0'");
  SetMessage("RT_UNDEFINED_MESSAGE",
              "undefined message '%0'");
  SetMessage("RT_BAD_FORMAT_ARITY",
              "bad format arity %0 (expected %1)");
  SetMessage("RT_OTHER",
              "%0");
   // Console IDE
  SetMessage("CIDE_IN_FUNCTION",
              "in function");
  SetMessage("CIDE_NO_PREV_FRAME",
              "No previous frame.");
  SetMessage("CIDE_NO_NEXT_FRAME",
              "No next frame.");
  SetMessage("CIDE_HELP",
              "Debugger commands are:\n\
$b\tPrint a backtrace.\n\
$u\tUp to the previous call frame.\n\
$d\tDown to the next call frame.\n\
$w\tPrint the current location.\n\
$h\tPrint this help.\n\
$c\tContinue the execution.\n\
$s\tStep.\n\
$n\tStep over the next statement.\n\
$r\tStep out of the current call frame.\n\
$q\tQuit the debugger.\n\
Any other command is interpreted as a plain script command.\n");
  SetMessage("CIDE_WELCOME",
              "In debugger. Type '$h' for help.");
  SetMessage("CIDE_STOPPED",
              "Stopped at");
  SetMessage("CIDE_CANNOT_CONTINUE_ERROR",
              "Cannot continue after an error.\n\
Use $q to quit the debugger.\n");
  SetMessage("CIDE_RUNNING_TEST_LINE",
              "Running test on line");
  SetMessage("CIDE_TEST_FAILED",
              "Test failed at");
  SetMessage("CIDE_COMPILATION_ERRORS",
              "Compilation errors");
  SetMessage("CIDE_RUNTIME_ERROR",
              "Runtime error");
  SetMessage("CIDE_VALUE_MISMATCH",
              "Returned value mismatch.");
  SetMessage("CIDE_EXPECTED_VALUE",
              "Expected value");
  SetMessage("CIDE_RETURNED_VALUE",
              "Returned value");
  SetMessage("CIDE_FINAL_CONDITION_FALSE",
              "Final condition is false.");
  SetMessage("CIDE_ERROR_NOT_SIGNALED",
              "Expected error not signaled.");
   // Graphical IDE
  SetMessage("GIDE_GLOBAL_ENV",
              "Global environment");
  SetMessage("GIDE_STOPPING_EXECUTION",
              "Stopping execution.");
  SetMessage("GIDE_SYNTAX_ERROR",
              "Syntax error");
  SetMessage("GIDE_DEBUGGER_LISTENER",
              "debugger listener");
   // Source Descriptors
  SetMessage("GENERIC_SOURCE_CODE",
              "%0 source code");
}
