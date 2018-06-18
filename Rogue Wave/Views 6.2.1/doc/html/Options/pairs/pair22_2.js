var pairs =
{
"ilixml":{"ilixml":1,"hierarchy":1,"gadget":1}
,"hierarchy":{"example":1}
,"example":{"gadget":1}
,"gadget":{"ilixml":1,"manages":1}
,"manages":{"communication":1,"import":1}
,"communication":{"data":1}
,"data":{"source":1}
,"source":{"xml":1}
,"xml":{"stream":1}
,"stream":{"manages":1}
,"import":{"export":1}
,"export":{"notification":1}
,"notification":{"modification":1}
}
;Search.control.loadWordPairs(pairs);
