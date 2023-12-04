template <class T1, class T2>
bool Fun(T1* p, T2& r){
return
    typeid(T1) == typeid(T2) // (1) confronta i tipi statici T1 e T2
    &&
    typeid(*p) == typeid(r) // (2) confronta i tipi dinamici di *p e r
    //typeid(p) == typeid(&r) //alternativa strana alla (1)
    &&
    dynamic_cast<std::ios*>(p) // (2) (ii) TD(p) <= std::ios*
    // && typeid(*p) != typeid(std::ios) //INUTILE, perchè std::ios è astratta
    ;
}