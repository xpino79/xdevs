

/*
 * stringtok.h -- Breaks a string into tokens.  This is an example for lib3.
 *
 * Template function looks like this:
 *
 *    template <typename Container>
 *    void stringtok (Container &container,
 *                    string const &in,
 *                    char const * const delimiters = " \t\n");
 *
 * The final parameter is an array of characters that serve as whitespace.
 * Whitespace characters default to one or more of tab, space, and newline,
 * in any combination.
 *
 * 'l' need not be empty on entry.  On return, 'l' will have the token
 * strings appended.
 *
 *
 * [Example:
 *       list<string> ls;
 *       stringtok (ls, " this  \t is\t\n  a test  ");
 *       for (list<string>::const_iterator i = ls.begin();
 *            i != ls.end(); ++i)
 *       {
 *            cerr << ':' << (*i) << ":\n";
 *       }
 *
 *  would print
 *       :this:
 *       :is:
 *       :a:
 *       :test:
 * -end example]
 *
*/

#ifndef STRINGTOK_H_
#define STRINGTOK_H_

#include <string>

template <typename Container>
void stringtok (Container &container, std::string const &in, const char * const delimiters = " \t\n")
{
    const std::string::size_type len = in.length();
    std::string::size_type i = 0;

    while (i < len) {
        // eat leading whitespace
        i = in.find_first_not_of(delimiters, i);
        if (std::string::npos == i) {
            break;  // nothing left but white space
        }

        // find the end of the token
        std::string::size_type j = in.find_first_of(delimiters, i);

        // push token
        if (std::string::npos == j) {
            container.push_back( in.substr(i) );
            break;
        }
        else {
            container.push_back( in.substr(i, j-i) );
        }

        // set up for next loop
        i = j+1;
    }
}

#endif /* STRINGTOK_H_ */
