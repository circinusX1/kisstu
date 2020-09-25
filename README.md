# CDBL Curly Bracket Document Layout
# Sept 25 2020
### FreeBSD License
#### Existent parser is for demo purposes.

### Like this
```JSON
x{
    %include:./included.css;
    long{"a long string with escape \" and \\  and \} and \{ and \, characters "}
    xi{
        shape{
             rect{10,
                  10,
                  1000,
                  1000}
             color{355,255,0}
        }
        circle{
          center{@../shape/rect[0],@../shape/rect[1]}
          color{@x/x1/shape/rect/color}
          }
    }
    css_style:333;         # must end with ;
    ini_style=has_column;  # must end with ;
    
}

```

### An Alternative to JSON 

   * simple JSON alternative, string based
   * 100 lines parser
   * string based, encapsulate your types and do it in your space
   * Write a wrapper in user space for custome needs is sinple (qt QSettings wrapper at the end of the post)


### Work in progress.

#### syntax

```
<{>
  KEY{ENTITY,<ENTITY>...}
  KEY=STRING_VALUE;
  KEY:STRING_VALUE;
<}>
  where
    ENTITY=string
    ENTITY=@path/to/another/key/from_root
    ENTITY=@../../relative_path_to_another_key
    ENTITY=" a atring with \" \} \{ \, \= \# \} \: escapes and apsces string"
    ENTITY=KEY{ENTITY}
  
```

#### keywords

```
  %include:filename
  # commented line
 
```

#### lookup

```
   * string based.
   * why having some.toInt()  some.toString()  some.toFloat() and delegate the type convertions into parsers, use strings and do conversion on the fly
   * like using the std  std::stof() std::stod() std::stold()
       *  or write an adapter. Better having in user space, and convert only what you need instead all string to types.

```cpp   
 float pi = std::stof ( aj["x"]["pi"].value() );
 
```
  
### Lookup
 
 ```cpp
   const Aka& pd = aka["x"]["list"]["object"];
   size_t  elems = pd.count();
   for(size_t i=0;i<pd.count();i++)
   {
        const std::string& v = pd.value(i);
        OOO << v.c_str() << "\n";
   }
   
 ```
 
### making

```cpp
    Cbdler aj;

    Cbdler::Node* root = aj.begin("root");
    root->add("string-value");
    root->add("allways string-value");

    Cbdler::Node* keyval = aj.make("key");
    keyval->add("value");
    root->add(keyval);

    Cbdler::Node* rect = aj.make("colorred_rect");
    rect->add("2,2,100,100");

    Cbdler::Node* color = aj.make("color");
    color->add("255,255,255");

    rect->add(color);
    root->add(rect);
    aj.print(aj.root(), 0);
```
   
### TODO
   * optimised lookup
   * java parser
   * php parser
   * python wrapper

### A wrapperr to custom types

```cpp
class QtKisstu : public Cbdler
{
    QString _fn;
public:
    QtKisstu()
    {
        _curent = this->root();
    }
    QtKisstu(const QString& file)
    {
        _fn=file;
        parse(file);
        _curent = this->root();
    }
    const QString& fileName(){return _fn;}
    struct Typoc{
        std::string _s[4]={"0","-1","-1","0"};
        Typoc(const Cbdler::Node* pn){
            if(pn!=nullptr){
                size_t els = pn->count();
                for(size_t e=0;e<els;e++)
                {
                    _s[e] = pn->value(e);
                    if(_s[e]=="MAX")_s[e]="-1";
                    if(_s[e]=="NEXT")_s[e]="-2";
                }
            }
        }
        QString toString()const{return QString(_s[0].c_str());}
        bool toBool()const{return _s[0]=="true";}
        int toInt()const{return std::stod(_s[0]);}
        QRect toRect()const{
            QRect r;
            r.setX(std::stod(_s[0]));
            r.setY(std::stod(_s[1]));
            r.setRight(std::stod(_s[2]));
            r.setBottom(std::stod(_s[3]));
            return r;
        }
        QSize toSize()const{
            return QSize(std::stod(_s[0]),
                         std::stod(_s[1]));
        }
        QPoint toPoint()const{
            return QPoint(std::stod(_s[0]),
                          std::stod(_s[1]));
        }
    };

    const Typoc value(const char* key, int dev=0){
        const Node* pn = _curent->pnode(key);
        if(pn==nullptr)
        {
            printf("null \n");
        }
        return Typoc(pn);
    }

    const Typoc value(const QString& key, int dev0=0){
        const Node* pn = _curent->pnode(key.toUtf8());
        return Typoc(pn);
    }

    bool beginGroup(const char* ks)
    {
        const Node* pn = _curent->pnode(ks);
        if(pn){
            _curent = _curent->pnode(ks);
            return true;
        }
        return false;
    }

    void endGroup()
    {
        _curent = root();
    }
    const Cbdler::Node*  _curent;
};
// usage
_hidden= s.value("Hidden").toBool();
_icwh= s.value("Isize").toPoint();
_rpos = s.value("Xrect").toInt();
_icon = s.value("Icon").toString();



```

