#include <map>
#include <string>

#include "../../lib/filehandler/filehandler.h"
#include "../../lib/logger/logger.h"

#ifndef __MARKOV__
#define __MARKOV__

namespace liv1 {

/* This class holds a 
 * histogram key, 
 * how many times it occurres 
 * and how often other keys occurres after */
class HistogramKey {
public:
    HistogramKey(std::string KEY) { key = KEY; occurrences = 1; };

    /* This method will add a relation between 
     * If one already exists, we'll increment the occurrences counter */
    void add(std::string key);

    /* Print occurrences of this key
     * and how often other keys occurres after.
     * Format: [T: occurrences, keys[0]->key: keys[0]->occurrences, ..., keys[n]->key: keys[n]->occurrences]
     */
    void pretty_print();

    std::string key;
    int occurrences;
    std::map<std::string, int> keys;
};

class Histogram {
public:
    Histogram() { std::string start = "START"; HistogramKey hk(start); keys.insert(std::pair<std::string, HistogramKey> (start, hk));  };

    void add(std::string before, std::string token);
    
    /* This methods creates .js file
     * this file is ready to be integrated with boostrap: https://mdbootstrap.com/javascript/charts/ 
     * Format: 
     * labels: [keys[0]->key, .., keys[n]->key] 
     * data: [keys[0]->occurrences, .., keys[n]->occurrences]
     */
    void chart(const char *filename);

    /* This method creates .json file
     * this file is ready to be integrated with sigma.js: http://sigmajs.org/
     */
    void graph(const char *filename);

    std::map<std::string, HistogramKey> keys;
    };

class Markov
    {
public:
    Markov(const char *filename);

    void graph(const char *filename) { hist.graph(filename); };
    void chart(const char *filename) { hist.chart(filename); };

private:
    Histogram hist;
    };

};

#endif