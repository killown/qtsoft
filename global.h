#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
// ALL THE GLOBAL DECLARATIONS

// don't use #include <QString> here, instead do this:

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

// that way you aren't compiling QString into every header file you put this in...
// aka faster build times.

#define MAGIC_NUM 42

extern bool ok;
extern QString username_loggedin;
extern QString usuario_selecionado_na_tabela;
#endif // GLOBALS_H

