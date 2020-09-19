# comar very dumb  alternative to JSON

   * simple JSON alternative, string based
   * 100 lines parser
   * string based, encapsulate your types and do it in your space


### Work in progress.

### Just like that

```
# run
g++ ./comar.cpp -o comar
./comar

# sintax 

x{
    label_y {1,3,4}
    some {sdfgsdf,"sdf to come"}
    list{
        sadf,
        asdf,
        asdf,
        object{d,d,d,sdf,1,3,4,"a string"}
    }
}

```
   * string based.
   * why having some.toInt()  some.toString()  some.toFloat() and delegate the type convertions into parsers, use strings and do conversion on the fly
   * like using the std  std::stof() std::stod() std::stold() 

```   
 float pi = std::stof ( aj["x"]["pi"].value() );
 
```
  
### Lookup
   ```
   const Aka& pd = aka["x"]["list"]["object"];
   size_t  elems = pd.count();
   for(size_t i=0;i<pd.count();i++)
   {
        const std::string& v = pd.value(i);
        OOO << v.c_str() << "\n";
   }

   
   ```
   
### TODO
   * optimised lookup
   * runtime build the doc
   * make references int withn like x{@label}
