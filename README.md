# kisstu: 
### dumb  alternative to JSON 

   * simple JSON alternative, string based
   * 100 lines parser
   * string based, encapsulate your types and do it in your space


### Work in progress.

#### syntax

```
  KEY{ENTITY,<ENTITY>...}
  where
    ENTITY=string
    ENTITY=KEY{ENTITY}
```

### Just like that


```cpp
# run
g++ ./comar.cpp -o comar
./comar

# sintax 

x{
    width{100}
    height{200}
    label_y {1,3,4}
    escaping {"sdfgsdf \"  and \{  and \} and \, and \" also in a long string "}
    list{
        sadf,
        asdf,
        asdf,
        object{d,d,d,sdf,1,3,4,"a string"}  // will fix the space for long strings
    }
    rect {45,45,45,45}
    # almost supports references. Not fully tested
    size{../@width,x/@height}                    // o["x"]["size"](0) = 100 & o["x"]["size"](1) = 200
    label2{@x/label_y}                           // o["x"]["label2"] = {1,3,4}
}

```
   * string based.
   * why having some.toInt()  some.toString()  some.toFloat() and delegate the type convertions into parsers, use strings and do conversion on the fly
   * like using the std  std::stof() std::stod() std::stold() 

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
    Kisstu aj;

    Kisstu::Node* root = aj.begin("root");
    root->add("string-value");
    root->add("allways string-value");

    Kisstu::Node* keyval = aj.make("key");
    keyval->add("value");
    root->add(keyval);

    Kisstu::Node* rect = aj.make("colorred_rect");
    rect->add("2,2,100,100");

    Kisstu::Node* color = aj.make("color");
    color->add("255,255,255");

    rect->add(color);
    root->add(rect);
    aj.print(aj.root(), 0);
```
   
### TODO
   * optimised lookup
   * runtime build the doc
   * make references int withn like key{&value}  or key{&value}


