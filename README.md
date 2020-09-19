# comar a dumb alternative to JSON

   * simple JSON alternative, string based
   * 100 lines parser
   * string based, encapsulate your types and do it in your space


### Work in progress.

### Just like that

```
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
      
### Lookup
   ```
   const Aka& pd = (*_pnode)["x"]["list"]["object"];
   
   ```
   
### TODO
   * optimised lookup
   * runtime build the doc
   * make references int withn like x{@label}
