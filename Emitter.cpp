#include "Emitter.hpp"
#include <assert.h>
#include <ostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;



namespace {
    const char indent[] = "    ";
}



Emitter::Emitter(ostream *os_, const string &r)
 : os(os_), replacement(r), indent_level(0) {}


void
Emitter::emitLineStartF(int il, const char *fmt, ... ) {
    indent_level += il;
    assert(indent_level >= 0);
    va_list ap;
    va_start(ap, fmt);
    emitHelper(fmt, ap, true, false);
    va_end(ap);
}

void
Emitter::emitLineStartF(const char *fmt, ... ) const {
    assert(indent_level >= 0);
    va_list ap;
    va_start(ap, fmt);
    emitHelper(fmt, ap, true, false);
    va_end(ap);
}

void
Emitter::emitString(const string &s) const {
    emitStringF("%s", s.c_str());
}

void
Emitter::emitStringF(const char *fmt, ... ) const {
    assert(indent_level >= 0);
    va_list ap;
    va_start(ap, fmt);
    emitHelper(fmt, ap, false, false);
    va_end(ap);
}

void
Emitter::emitLineEnd(const string &s) const {
    emitLineEndF("%s", s.c_str());
}

void
Emitter::emitLineEndF(const char *fmt, ... ) const {
    assert(indent_level >= 0);
    va_list ap;
    va_start(ap, fmt);
    emitHelper(fmt, ap, false, true);
    va_end(ap);
}

void
Emitter::emitLine(const string &s) const {
    emitLineF("%s", s.c_str());
}

void
Emitter::emitLine(int id, const string &s) {
    emitLineF(id, "%s", s.c_str());
}

void
Emitter::emitLineF(const char *fmt, ... ) const {
    assert(indent_level >= 0);
    va_list ap;
    va_start(ap, fmt);
    emitHelper(fmt, ap, true, true);
    va_end(ap);
}

void
Emitter::emitLineF(int il, const char *fmt, ... ) {
    indent_level += il;
    assert(indent_level >= 0);
    va_list ap;
    va_start(ap, fmt);
    emitHelper(fmt, ap, true, true);
    va_end(ap);
}

void
Emitter::emitHelper(const char *fmt, va_list ap, bool is_start, bool is_end) const {

    int ec = -1;
    string str;

    /*
     * First do the formatted printing.  We need to use a complicated
     * loop because we don't know in advance how long the string is going
     * to be.
     */
    {
        /*
         * Start with a buffer that is twice fmt length and double every iteration if
         * it is too small.  Not very efficient, but should be okay for most
         * applications of this class.
         */
        // Make it at least 1 to avoid problems when it is 0.
        int len = max<size_t>(2*strlen(fmt), 1);
        char *buf = new char[len];

        while (true) {

            va_list ap2;
            va_copy(ap2, ap);
            ec = vsnprintf(buf, len, fmt, ap2);
            va_end(ap2);
            assert(ec >= 0);

            // Some versions of [v]snprintf() return the number of characters
            // that would have been printed had the buffer been long enough.
            // Others just return size - 1 if the buffer is too small.
            if (ec < len - 1) {
                str = buf;
                delete [] buf;
                break;
            }

            // Buffer was too small, so double it and do it again.
            len *= 2;
            delete [] buf;
            buf = new char[len];
            buf[0] = '\0';
        }
    }

    // All newlines should be supplied by the emitHelper, so verify that there
    // are no newlines.
    assert(str.find('\n') == string::npos);

    // If we need to output the beginning of the line.
    if (is_start) {
        // First add the indent.
        assert(indent_level >= 0);
        for (int i = 0; i < indent_level; i++) {
            *os << indent;
        }
    }

    // Now do variable name substitution.
    {
        // First, reserve our buffer to be the right length, to avoid
        // O(N^2) behavior.
        string tmp_buf;
        {
            // Count the number of variable names in the string.  Not very
            // efficient, but speed of code generation is likely not an issue.
            int n = 0;
            for (size_t i = 0; (i = str.find(var_name, i)) != string::npos; i += 2, n++);
            //for (char *p = tmp_buf; p = str(p, var_name.c_str()); p+=2, n++);

            tmp_buf.reserve(str.size() + n*(replacement.size() - var_name.size()));
        }

        // Now step through string, appending to tmp_buf as we go along, and
        // doing the substitution.
        int i = 0;
        while (true) {
            size_t ni = str.find(var_name, i);
            if (ni != string::npos) {
                tmp_buf.append(str.substr(i, ni - i));
                tmp_buf.append(replacement);
                i = ni + 2;
            } else {
                tmp_buf.append(str.substr(i));
                break;
            }
        }

        str = tmp_buf;
    }
    // Output the actual stuff.
    *os << str;
    // Output the newline if needed.
    if (is_end) {
        *os << "\n";
    }
}

void
Emitter::increment_indent_level() { indent_level++; }

void
Emitter::decrement_indent_level() { indent_level--; }

void
Emitter::setReplacement(const std::string &r) {
    replacement = r;
}

const string Emitter::var_name("$$");
