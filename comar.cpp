#include <iostream>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#define OOO std::cout


class AkaJson
{
public:

    class Aka
    {
    public:
        friend class AkaJson;
        enum E_TYPE{eNODE,eLEAF};
        Aka(Aka::E_TYPE t, const std::string& name):_name(name),_type(t){
            _parent=nullptr;
        }
        Aka(Aka::E_TYPE t):_type(t){
            _parent=nullptr;
        }
        ~Aka(){
            for(const auto& a : _values)
                delete a;
        }
        void name_it(std::string& name){
            _name = name;
            name.clear();
        }
        Aka* store_it(std::string& name){
            Aka* paka = new Aka(Aka::eLEAF, name);
            paka->_parent = this;
            _type = eNODE;
            this->_values.push_back(paka);
            name.clear();
            return paka;
        }

        const Aka& operator[](const char* key)const
        {
            if(key==_name)
                return *this;
            for(const auto& a : _values)
            {
                if(a->_name==key)
                    return *a;
            }
            static Aka Dummy(Aka::eLEAF);
            return Dummy;
        }

        const Aka* parent(){
            return _parent;
        }

        const std::vector<Aka*>& values(){
            return _values;
        }

        const std::string value(int index=0)const{
            static std::string empty="";
            if(_values.size()>=index)
                return _values[index]->_name;
            return empty;
        }

        size_t count()const{
            return _values.size();
        }

    private:
        std::string                 _name;
        std::vector<Aka*>           _values;
        Aka*                        _parent;
        Aka::E_TYPE                 _type;
    };

public:
    AkaJson(const char* fname):_pnode(nullptr)
    {
        _parse(fname);
    }
    // looup todo
    const AkaJson::Aka& operator[](const char* key)const
    {
        return _pnode->operator[](key);
    }
    const std::string value(const char* key)const{
        const Aka& raka = _pnode->operator[](key);

    }
private:
    void _parse(const char* fname)
    {
        char p = 0;
        Aka* paka = nullptr;
        Aka* parent = nullptr;
        std::ifstream fi(fname);
        if(fi.is_open())
        {
            while (std::getline(fi, _line))
            {
                char prev = 0;
                std::istringstream iss(_line);
                if(_line.empty() || _line[0]=='#')
                    continue;
                for(const auto f : _line)
                {
                    switch(f)
                    {
                    case '\t':
                    case ' ':
                        break;
                    case '{':
                        parent = paka;
                        paka = _new();
                        paka->_name=_string;
                        paka->_parent = parent;
                        _string.clear();
                        if(paka!=parent && parent)
                            parent->_values.push_back(paka);
                        break;
                    case '}':
                        if(!_string.empty())
                        {
                            paka->store_it(_string);
                        }
                        paka = paka->_parent;
                        break;
                    case ',':
                        paka->store_it(_string);
                        break;
                    default:
                        _string+=f;
                        break;
                    }
                }
            }
        }

        print(_pnode, 0);


    }

    Aka* _new()
    {
        if(_pnode==nullptr)
        {
            _pnode=new Aka(Aka::eNODE);
            _pnode->_parent = _pnode;
            return _pnode;
        }
        return new Aka(Aka::eLEAF);
    }


    void _wipe()
    {
        OOO << _string.c_str() << "\n";
        _string.clear();
    }

    void print(const Aka* p, int depth)
    {
        ++depth;
        //OOO << "\n";
        for(int i=0;i<depth;i++) OOO<<" ";

        OOO  << p->_name.c_str() << "\n";
        if(p->_values.size())
        {
            //OOO << "\n";
            for(int i=0;i<depth;i++) OOO<<" ";
            OOO << "{\n";
            for(const auto& a : p->_values)
            {
                print(a,depth);
            }
            //OOO << "\n";
            for(int i=0;i<depth;i++) OOO<<" ";
            OOO << "}\n";
        }
        --depth;
    }

    //

private:

    std::string             _string;
    std::string             _line;
    Aka*                    _pnode = nullptr;
    bool                    _escap=false;
    bool                    _toking=false;
};


int main(void)
{
    AkaJson aj("./test.comar");

    const AkaJson::Aka& pd = aj["x"]["list"]["object"];\
    for(size_t i=0;i<pd.count();i++)
    {
        const std::string& v = pd.value(i);
        OOO << v.c_str() << "\n";
    }
    const std::string& pi = aj["x"]["pi"].value();
    

    return 1;
}






