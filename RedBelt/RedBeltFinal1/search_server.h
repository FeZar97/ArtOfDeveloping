#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

class InvertedIndex {
    map<string, list<size_t>> index;
    vector<string> docs;
public:
    void Add(string document);
    list<size_t> Lookup(const string& word) const;
    
    const string& GetDocument(size_t id) const {
        return docs[id];
    }
};

class SearchServer {
    InvertedIndex index;

public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);
};
