#include "markov.hpp"

namespace liv1 {

/* ***************************************** */
/* HistogramKey */
/* ***************************************** */

void HistogramKey::add(std::string key)
    {
    std::pair<std::map<std::string, int>::iterator, bool> ret;
    ret = keys.insert(std::pair<std::string, int> (key, 1));
    if(ret.second == false)
        ret.first->second++;
    else
        ret.first->second = 1;
    };

void HistogramKey::pretty_print() 
    {
    std::map<std::string, int>::iterator it;
    std::cout << " [T:  " << occurrences << ", ";
    for (it=keys.begin(); it!=keys.end(); ++it) 
        {
        std::cout << it->first.c_str() << ": " << it->second << ", ";
        }
    std::cout << "] ";
    };

/* ***************************************** */
/* Histogram */
/* ***************************************** */

void Histogram::add(std::string before, std::string token)
    {
    /* Insert token, if non existing
    * if token already exists, increment occurrences */
    HistogramKey *hist = &keys.find(before)->second;
    hist->add(token);
    
    /* insert token among keys,  
    * if token already exists incremt occurrences */
    HistogramKey c(token);
    std::pair<std::map<std::string, HistogramKey>::iterator,bool> ret;
    ret = keys.insert( std::pair<std::string, HistogramKey>(token, c) );
    if(ret.second == false)
        (ret.first->second).occurrences++;
    };

void Histogram::chart(const char *filename)
    {
    std::vector<std::string> labels;
    std::vector<int> outdata;
    std::map<std::string, HistogramKey>::iterator it;

    std::string tmp = "var ctx = document.getElementById(\"myChart\").getContext('2d');";
    tmp += "var myChart = new Chart(ctx, {type: 'bar', data: {";

    for(it = keys.begin(); it != keys.end(); ++it)
        {
        labels.push_back(it->first);
        outdata.push_back( (it->second).occurrences );
        }
    tmp += "labels: [";
    for(int i = 0; i < labels.size()-1; i++)
        {
        tmp += "\""; tmp += labels[i]; tmp += "\", ";
        }
    tmp += "\""; tmp += labels[labels.size()-1]; tmp += "\"";
    tmp += "],";
    tmp += "datasets: [{label: 'Word count',";
    tmp += " data: [";
    for(int j = 0; j < outdata.size()-1; j++)
        {
        tmp += filehandler::int_to_string(outdata[j]); tmp += ", ";
        }
    tmp += filehandler::int_to_string(outdata[outdata.size()-1]);
    tmp += "], ";
    tmp += "borderWidth: 1}]}, options: { scales: { yAxes: [{ ticks: { beginAtZero:true } }] } } });";
    filehandler::write_file(filename, tmp.c_str());
    };

void Histogram::graph(const char *filename)
    {
    std::string tmp, tmp2;
    std::vector<std::string> nodes;
    std::vector<std::string> edges;
    std::map<std::string, HistogramKey>::iterator it;
    std::map<std::string, int>::iterator it2;

    int counter = 0, counter2 = 0, x = 0, y = 0;
    for(it = keys.begin(); it != keys.end(); ++it)
        {
        tmp = "{\"id\": \"";
        tmp += it->first;
        tmp += "\",\"label\": \"";
        tmp += it->first;
        tmp += "\",\"x\":";
        tmp += filehandler::int_to_string(x);
        tmp += ",\"y\":";
        tmp += filehandler::int_to_string(y);
        tmp += ",\"size\": 1} ";
        nodes.push_back(tmp);
        
        HistogramKey c = it->second;
        counter2 = 0;
        for(it2 = c.keys.begin(); it2 != c.keys.end(); ++it2)
            {
            tmp2 = "{\"id\": \"e";
            tmp2 += filehandler::int_to_string(counter) + "" + filehandler::int_to_string(counter2);
            tmp2 += "\",\"source\": \"";
            tmp2 += it->first;
            tmp2 += "\",\"target\": \"";
            tmp2 += it2->first;
            tmp2 += "\",\"label\": \"";
            tmp2 += filehandler::int_to_string(it2->second);
            tmp2 += "/";
            tmp2 += filehandler::int_to_string(c.occurrences);
            tmp2 += "\"}";
            edges.push_back(tmp2);
            counter2++;
            }
        
        if(counter % 2 == 0)
            x++;
        else
            y++;
        counter++;
        }
    std::cout << "{ \"nodes\": [";
    for(int i = 0; i < nodes.size()-1; i++)
        std::cout << nodes[i].c_str() << "," << std::endl;
    std::cout << nodes[nodes.size()-1] << "]";
    std::cout << ", \"edges\": [";
    for(int j = 0; j < edges.size()-1; j++)
        std::cout << edges[j].c_str() << "," << std::endl;
    std::cout << edges[edges.size()-1] << "] }";
    };

/* ***************************************** */
/* Markov */
/* ***************************************** */

Markov::Markov(const char *filename)
    {
    Logger log;
    std::string indata = filehandler::get_file_contents(filename, log);
    std::vector<std::string> tokens = filehandler::split_string(indata, ' ');

    std::string start = "START";
    std::string end = "END";
    std::string before = start;

    for(int i = 0; i < tokens.size(); i++)
        {
        hist.add(before, tokens[i]);
        before = tokens[i];
        }
    
    hist.add(before, end);
    };
};