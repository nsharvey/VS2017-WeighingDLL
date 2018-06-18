function cbNewDs(g) {
 var cont = g.container;
 var val  = g.value;
 var tg   = cont.TGData; 
 if (val == 0)
   tg.dataSourceName = "RES_MS";
 if (val == 1)
   tg.dataSourceName = "ACT_MS";
 if (val == 2)
   tg.dataSourceName = "CNT_MS";
 if (val == 3)
   tg.dataSourceName = "PRE_MS";
 if (val == 4)
   tg.dataSourceName = "BRK_MS";
 if (val == 5)
   tg.dataSourceName = "LOA_MS";  
}

function cbIsActivePeriod(g) {
 if (g.periodInfoWeekDay == 1)
   g.setInactivePeriod();
 if (g.periodInfoWeekDay == 7)
   g.setInactivePeriod();
 if ((g.periodInfoMonth == 1) && (g.periodInfoDay == 1))
   g.setInactivePeriod();
 if ((g.periodInfoWeekDay == 2) && (g.periodInfoDay < 8))
   g.setInactivePeriod();
}
