// Language: fr_FR
// Encoding: windows-1252
with (Ilog) {
  // Messages sur les flots
  SetMessage("IO_READ_ERROR",
	     "erreur de lecture");
  SetMessage("IO_LINE_TOO_LONG",
	     "ligne trop longue (maximum %0 caractères)");
  // Messages de l'analyseur lexical
  SetMessage("TOKEN_BAD_DIGIT",
	     "chiffre %0 incorrect");
  SetMessage("TOKEN_INT_OVERFLOW",
	     "débordement dans une constante entière");
  SetMessage("TOKEN_FLOAT_OVERFLOW",
	     "débordement dans une une constante flottante");
  SetMessage("TOKEN_FLOAT_UNDERFLOW",
	     "constante flottante réduite à zéro");
  SetMessage("TOKEN_BAD_EXPONENT",
	     "exposant de nombre flottant incorrect");
  SetMessage("TOKEN_NEWLINE_STRING",
	     "retour à la ligne dans une chaîne");
  SetMessage("TOKEN_EOS_STRING",
	     "fin de flux d'entrée au milieu d'une chaîne");
  SetMessage("TOKEN_BAD_STRING_ESCAPE",
	     "séquence d'échappement '%0' incorrecte");
  SetMessage("TOKEN_BAD_CHAR",
	     "caractère illégal %0");
  SetMessage("TOKEN_EOS_COMMENT",
	     "fin de flux d'entrée au milieu d'un commentaire");
  // Messages de l'analyseur syntaxique
  SetMessage("PARSE_ELSE_NO_IF",
	     "'else' sans un 'if'");
  SetMessage("PARSE_IN_WITHOUT_FOR",
	     "'in' ne peut être utilisé que dans une boucle 'for/in'");
  SetMessage("PARSE_RESERVED",
	     "utilisation incorrecte d'un mot-clef réservé");
  SetMessage("PARSE_TOO_MANY_CPAREN",
	     "trop de ')'");
  SetMessage("PARSE_TOO_MANY_CBRACE",
	     "trop do '}'");
  SetMessage("PARSE_TOO_MANY_CBRACKET",
	     "il manque un '['");
  SetMessage("PARSE_MISSING_SEMI",
	     "il manque un ';'");
  SetMessage("PARSE_MISSING_COLON",
	     "il manque un ':'");
  SetMessage("PARSE_MISSING_NEWLINE_OR_SEMI",
	     "il manque un ';' ou un retour à la ligne entre deux instructions");
  SetMessage("PARSE_MISSING_OBRACE",
	     "il manque un '{'");
  SetMessage("PARSE_MISSING_CBRACE",
	     "il manque un '}'");
  SetMessage("PARSE_MISSING_OPAREN",
	     "il manque un '('");
  SetMessage("PARSE_MISSING_CPAREN",
	     "il manque un ')'");
  SetMessage("PARSE_MISSING_CBRACKET",
	     "il manque un ']'");
  SetMessage("PARSE_MISSING_VAR_IDENT",
	     "il manque un nom de variable");
  SetMessage("PARSE_MISSING_FUN_IDENT",
	     "il manque un nom de fonction");
  SetMessage("PARSE_MISSING_PARAM_LIST",
	     "il manque un '(' commençant la liste de paramètres");
  SetMessage("PARSE_MISSING_PARAM_IDENT",
	     "nom de paramètre incorrect");
  SetMessage("PARSE_MISSING_COMMA",
	     "il manque un ','");
  SetMessage("PARSE_MISSING_FOR_IN_VAR",
	     "il manque une variable de boucle");
  SetMessage("PARSE_MISSING_EXP",
	     "il manque une expression");
  SetMessage("PARSE_BAD_PROPNAME",
	     "nom de propriété incorrect");
  SetMessage("PARSE_MISSING_FUN_DECLARATION",
	     "il manque une déclaration de fonction");
  // Messages du compilateur
  SetMessage("COM_VAR_REDECLARED",
	     "déclarations multiples pour '%0'");
  SetMessage("COM_REPEATED_PARAM",
	     "paramètre '%0' répété");
  SetMessage("COM_NOT_LVALUE",
	     "cette expression ne peut pas être affectée");
  SetMessage("COM_NOT_ONE_INDEX",
	     "l'opérateur '[]' prend exactement un argument");
  SetMessage("COM_RETURN_OUTSIDE_FUN",
	     "'return' hors d'une fonction");
  SetMessage("COM_BREAK_OUTSIDE_LOOP",
	     "'break' hors d'une boucle");
  SetMessage("COM_CONTINUE_OUTSIDE_LOOP",
	     "'continue' hors d'une boucle");
  SetMessage("COM_BAD_DECL_SYNTAX",
	     "syntaxe de déclaration incorrecte");
  SetMessage("COM_NESTED_FUNCTION_DEF",
	     "on ne peut pas définir des fonctions imbriquées");
  SetMessage("COM_EVAL_FUNCTION_DEF",
	     "on ne peut pas définir une function dans eval");
  SetMessage("COM_DEBUGGER_FUNCTION_DEF",
	     "on ne peut pas définir une function sous débogueur");
  SetMessage("COM_FORBIDDEN_FUNCTION_DEF",
              "les définitions de fonctions ne sont pas autorisées");
  SetMessage("COM_FUNCTION_DEF_ONLY",
              "seules les définitions de fonctions sont autorisées");
  // Messages du testeur
  SetMessage("TEST_MISSING_CHECK_CLAUSE",
	     "il manque une clause de vérification dans le test");
  SetMessage("TEST_MISSING_MSG_IDENT",
	     "il manque l'identificateur d'erreur");
  SetMessage("TEST_STMT_NOT_BOL",
	     "l'instruction ne commence pas à la colonne 0");
  SetMessage("TEST_CHECK_NOT_BOL",
	     "la clause de vérification ne commence pas à la colonne 0");
  // Erreurs
  SetMessage("ERROR_WARNING",
	    "Avertissement");
  SetMessage("ERROR_LINE",
	    "ligne");
  SetMessage("ERROR_USER_INTERRUPTION",
	    "Interruption de l'utilisateur!");
  SetMessage("ERROR_IN_TOSTRING",
	    "erreur lors de la conversion en chaîne");
  // Messages d'erreur d'exécution
  SetMessage("RT_NOT_FUNCTION",
	     "ce n'est pas une fonction");
  SetMessage("RT_NOT_CONSTRUCTOR",
	     "ce n'est pas un constructeur");
  SetMessage("RT_CANNOT_ADD_PROPERTIES",
	     "impossible d'ajouter des propriétés à cette valeur");
  SetMessage("RT_CANNOT_SET_PROPERTY",
	     "impossible d'affecter la propriété '%0'");
  SetMessage("RT_CANNOT_DELETE_PROPERTY",
	     "impossible de détruire la propriété '%0'");
  SetMessage("RT_CANNOT_ADD_LOCAL_VAR",
	     "impossible de créer une variable locale");
  SetMessage("RT_CANNOT_DELETE_LOCAL_VAR",
	     "impossible de détruire une variable locale");
  SetMessage("RT_CANNOT_CONVERT_TO_NUMBER",
	     "ne peut pas être converti en nombre");
  SetMessage("RT_CANNOT_CONVERT_TO_INT",
	     "ne peut pas être converti en nombre entier");
  SetMessage("RT_UNKNOWN_VAR",
	     "variable '%0' inconnue");
  SetMessage("RT_UNKNOWN_FUNCTION",
	     "fonction '%0' inconnue");
  SetMessage("RT_UNKNOWN_METHOD",
	     "méthode '%0' inconnue");
  SetMessage("RT_UNKNOWN_PROPERTY",
	     "propriété '%0' inconnue");
  SetMessage("RT_ARGUMENTS_OUTSIDE_FUN",
	     "'arguments' référencé hors d'une fonction");
  SetMessage("RT_TOO_MANY_ARGS",
	     "trop d'arguments");
  SetMessage("RT_NOT_ENOUGH_ARGS",
	     "pas assez d'arguments");
  SetMessage("RT_DISPLACED_METHOD",
	     "méthode appliquée au mauvais type d'object");
  SetMessage("RT_EVAL_COMPILATION",
	     "erreur de syntaxe: %0");
  SetMessage("RT_NOT_POSITIVE_INT",
	     "ce n'est pas un entier positif");
  SetMessage("RT_STACK_OVERFLOW",
	     "pile pleine");
  SetMessage("RT_BAD_DATE_SYNTAX",
	     "syntaxe de date incorrecte");
  SetMessage("RT_SORT_FN_BAD_RETURN",
	     "valeur de retour incorrect pour la fonction de comparison");
  SetMessage("RT_CANNOT_READ_FILE",
	     "impossible d'ouvrir le fichier %0");
  SetMessage("RT_CANNOT_FIND_FILE",
	     "fichier %0 non trouvé");
  SetMessage("RT_LOAD_COMPILATION",
	     "erreur de syntaxe: %0");
  SetMessage("RT_DELETED_PROXY",
	     "référence à un object détruit");
  SetMessage("RT_WRONG_TYPE",
	     "pas du type type '%0'");
  SetMessage("RT_UNDEFINED_MESSAGE",
              "message indéfini '%0'");
  SetMessage("RT_BAD_FORMAT_ARITY",
              "message d'arité incorrecte %0 (%1 attendu)");
  SetMessage("RT_OTHER",
	     "%0");
  // Console IDE
  SetMessage("CIDE_IN_FUNCTION",
	     "dans la fonction");
  SetMessage("CIDE_NO_PREV_FRAME",
	     "Pas de frame précédent.");
  SetMessage("CIDE_NO_NEXT_FRAME",
	     "Pas de frame suivant.");
  SetMessage("CIDE_HELP",
	     "Les commandes du débogueur sont:\n\
$b\tAffiche la pile.\n\
$u\tRemonte au frame précédent.\n\
$d\tDescend au frame suivant.\n\
$w\tAffiche l'emplacement courant.\n\
$h\tAffiche cette aide.\n\
$c\tContinue l'exécution.\n\
$s\tExécute un pas de programme.\n\
$n\tSaute par dessus l'instruction suivante.\n\
$r\tContinue jusqu'à la sortie du frame courant.\n\
$q\tQuitte le débogueur.\n\
Toute autre commande est interprétée comme une instruction de scripting.\n");
  SetMessage("CIDE_WELCOME",
	     "Vous êtes dans le débogueur. Tapez '$h' pour avoir de l'aide.");
  SetMessage("CIDE_STOPPED",
	     "Arrêté à");
  SetMessage("CIDE_CANNOT_CONTINUE_ERROR",
	     "Impossible de continuer après une erreur.\n\
Utilisez $q pour quitter le débogueur.\n");
  SetMessage("CIDE_RUNNING_TEST_LINE",
	     "Exécution du test sur la ligne");
  SetMessage("CIDE_TEST_FAILED",
	     "Échec du test ligne");
  SetMessage("CIDE_COMPILATION_ERRORS",
	     "Erreurs de compilation");
  SetMessage("CIDE_RUNTIME_ERROR",
	     "Erreurs d'exécution");
  SetMessage("CIDE_VALUE_MISMATCH",
	     "Valeur de retour non conforme.");
  SetMessage("CIDE_EXPECTED_VALUE",
	     "Valeur attendue");
  SetMessage("CIDE_RETURNED_VALUE",
	     "Valeur de retour");
  SetMessage("CIDE_FINAL_CONDITION_FALSE",
	      "Condition finale fausse.");
  SetMessage("CIDE_ERROR_NOT_SIGNALED",
	     "L'erreur attendue n'a pas été signalée.");
  // Graphical IDE
  SetMessage("GIDE_GLOBAL_ENV",
	     "Environnement global");
  SetMessage("GIDE_STOPPING_EXECUTION",
	     "Arrêt de l'exécution.");
  SetMessage("GIDE_SYNTAX_ERROR",
	     "Erreur de syntaxe");
  SetMessage("GIDE_DEBUGGER_LISTENER",
	     "boucle intéractive du débogueur");
  // Source Descriptors
  SetMessage("GENERIC_SOURCE_CODE",
	     "Code source %0");
}
