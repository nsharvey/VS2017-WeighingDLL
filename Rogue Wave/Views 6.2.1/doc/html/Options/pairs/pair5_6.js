var pairs =
{
"creating":{"definition":1}
,"definition":{"steps":1}
,"steps":{"described":1}
,"described":{"previous":1}
,"previous":{"section":1}
,"section":{"carried":1}
,"carried":{"coding":1}
,"coding":{"following":1}
,"following":{"example":1,"(note":1,"code":1,"sql":1}
,"example":{"shows":1}
,"shows":{"done":1}
,"done":{"create":1}
,"create":{"ilisqltable":1}
,"ilisqltable":{"object":1,"(display)":1,":getquery":1}
,"object":{"ilvdisplay*display":1,"defined":1}
,"ilvdisplay*display":{"ilisqltable*sqltbl":1}
,"ilisqltable*sqltbl":{"=new":1}
,"=new":{"ilisqltable":1}
,"(display)":{"sqltbl->":1}
,"sqltbl->":{"lock":1,"addjoin":1,"setcolumnpartofkey":1,"setcolumnsqltext":1,"setcolumntable":1,"insertconjunct":1,"setcolumnpredicat":1,"setcolumnorderby":1,"settableupdatable":1,"makequery":1}
,"lock":{"specify":1}
,"specify":{"database":1,"joins":1,"columns":1,"criteria":1,"sort":1,"updatable":1}
,"database":{"tables":1}
,"tables":{"ilisqltableref":1}
,"ilisqltableref":{"refemp":1,"refdept":1}
,"refemp":{"emp":1}
,"emp":{"scott":1}
,"scott":{"ilisqltableref":1,"ilint":1}
,"refdept":{"dept":1}
,"dept":{"scott":1,"ilistringtype)":1}
,"ilint":{"tblemp":1,"tbldept":1,"cid":1,"cname":1,"cdept":1,"ctotal":1,"sqltbl->":1}
,"tblemp":{"=sqltbl->":1}
,"=sqltbl->":{"addtable":1,"appendcolumn":1}
,"addtable":{"(refemp)":1,"(refdept)":1}
,"(refemp)":{"ilint":1}
,"tbldept":{"=sqltbl->":1,"specify":1}
,"(refdept)":{"specify":1}
,"joins":{"sqltbl->":1}
,"addjoin":{"(tblemp":1}
,"(tblemp":{"deptno":1,"iltrue)":1}
,"deptno":{"tbldept":1}
,"columns":{"ilint":1}
,"cid":{"=sqltbl->":1}
,"appendcolumn":{"iliintegertype)":1,"name":1,"dept":1,"total":1}
,"iliintegertype)":{"sqltbl->":1}
,"setcolumnpartofkey":{"(cid":1}
,"(cid":{"ilvtrue)":1,"sqltbl->":1,"tblemp)":1}
,"ilvtrue)":{"sqltbl->":1,"specify":1}
,"setcolumnsqltext":{"(cid":1,"(cname":1,"(cdept":1,"(ctotal":1}
,"setcolumntable":{"(cid":1,"(cname":1,"(cdept":1}
,"tblemp)":{"ilint":1}
,"cname":{"=sqltbl->":1}
,"name":{"ilistringtype)":1,"sqltbl->":1}
,"ilistringtype)":{"sqltbl->":1}
,"(cname":{"name":1,"tblemp)":1,"smith":1,"ilisqlascending)":1}
,"cdept":{"=sqltbl->":1}
,"(cdept":{"name":1,"tbldept)":1}
,"tbldept)":{"computed":1}
,"computed":{"column":1}
,"column":{"defined":1}
,"defined":{"following":1,"ready":1}
,"(note":{"following":1}
,"code":{"excerpt":1}
,"excerpt":{"part":1}
,"part":{"example)":1}
,"example)":{"ilint":1}
,"ctotal":{"=sqltbl->":1}
,"total":{"iliintegertype)":1}
,"(ctotal":{"price":1}
,"price":{"*qty":1}
,"*qty":{"specify":1}
,"criteria":{"ilint":1}
,"insertconjunct":{"(where":1}
,"(where":{"ilvtrue)":1}
,"setcolumnpredicat":{"(cname":1}
,"smith":{"ilvtrue)":1,"order":1}
,"sort":{"sqltbl->":1}
,"setcolumnorderby":{"(cname":1}
,"ilisqlascending)":{"specify":1}
,"updatable":{"table":1}
,"table":{"sqltbl->":1}
,"settableupdatable":{"(tblemp":1}
,"iltrue)":{"generate":1}
,"generate":{"sql":1}
,"sql":{"select":1,"statement":1}
,"select":{"statement":1,"emp.id":1}
,"statement":{"sqltbl->":1,"select":1}
,"makequery":{"point":1}
,"point":{"ilisqltable":1}
,"ready":{"calling":1}
,"calling":{"ilisqltable":1}
,":getquery":{"member":1}
,"member":{"function":1}
,"function":{"generates":1}
,"generates":{"following":1}
,"emp.id":{"emp.name":1}
,"emp.name":{"dept.name":1,"smith":1}
,"dept.name":{"scott.emp":1}
,"scott.emp":{"scott.dept":1}
,"scott.dept":{"emp.deptno":1}
,"emp.deptno":{"=dept.id":1}
,"=dept.id":{"emp.name":1}
}
;Search.control.loadWordPairs(pairs);
