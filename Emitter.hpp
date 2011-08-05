#ifndef EMITTER_HPP
#define EMITTER_HPP



#include <stdarg.h>
#include <iosfwd>
#include <string>



class Emitter {

    public:

        // Create an Emitter.  Replace all $$ with replacement.
        Emitter(std::ostream *, const std::string &replacement = var_name);

        // Start a line.  Will not print newline.  fmt is used as a format
        // string.
        void emitLineStartF(const char *fmt, ...) const;
        // Same as above, but increase or decrease indent level by
        // indent_delta.
        void emitLineStartF(int indent_delta, const char *fmt, ...);
        // Emit one string.
        void emitString(const std::string &) const;
        // Emit some stuff using the fmt string.
        void emitStringF(const char *fmt, ...) const;
        // Emit some stuff, and print the newline.
        void emitLineEnd(const std::string &) const;
        void emitLineEndF(const char *fmt, ...) const;
        void emitLine(const std::string &) const;
        void emitLine(int indent_delta, const std::string &);
        void emitLineF(const char *fmt, ...) const;
        void emitLineF(int indent_delta, const char *fmt, ...);

        void increment_indent_level();
        void decrement_indent_level();

        void setReplacement(const std::string &);

    private:

        void emitHelper(const char *fmt, va_list ap, bool is_start, bool is_end) const;

        std::ostream *os;
        std::string replacement;

        int indent_level;

	static const std::string var_name;
};



#endif
