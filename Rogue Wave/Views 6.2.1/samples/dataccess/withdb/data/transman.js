var empno = 0;
var err = new IliErrorList();
var numdept = 0;

static function OnLoad(cont) {
  var tcb2 = cont.tcb2;
  tcb2.readOnly = true;
}

static function jaccept(g) {
  var cont = g.container;
  var tab = cont.EMP.table;
  var tm = tab.transactionManager;
  var tmer = new IliErrorList();
  if (tm.accept()) {
    tab.sqlSession.commit();
  } else {
    err.report();
    tab.sqlSession.rollback();
    err.removeAllErrors();
  }
}

static function jcancel(g) {
  var cont = g.container;
  var tab2 = cont.DEPT.table;
  var tm = tab2.transactionManager;
  tm.cancel();
}

static function jstart(g) {
  var cont = g.container;
  var tab = cont.EMP.table;
  var tab2 = cont.DEPT.table;
  tab.transactionManagerName = "TM";
  tab2.transactionManagerName = "TM";
  var tm = tab2.transactionManager;
  tm.addErrorSink(err);
  tm.start();
  tab2.select();
  tab.getParameter("dept").value = 99;
  tab.select();
  var tg = cont.tg;
  tg.readOnly = true;
  var tcb2 = cont.tcb2;
  tcb2.readOnly = true;
  var butc = cont.butc;
  butc.sensitive = true;
  butc.active = true;
  var buta = cont.buta;
  buta.sensitive = true;
  buta.active = true;
  var butst = cont.butst;
  butst.sensitive = true;
  butst.active = true;
  var buts = cont.buts;
  buts.sensitive = false;
  buts.active = false;
}

static function jstop(g) {
  var cont = g.container;
  var tab = cont.EMP.table;
  var tab2 = cont.DEPT.table;
  var tm = tab2.transactionManager;
  if (tm && tm.eventCount!=0) {
    var error = new IliErrorList();
    IliErrorMessage.addErrorSink(err);
    var msg = new IliErrorMessage;
    msg.message = "choose Cancel/Accept to cancel/validate the changes";
    error.addError(msg);
    error.report();
    error.removeAllErrors();
  } else {
    tm.stop();
    tab.getParameter("dept").value = 99;
    tab.select();
    var tg = cont.tg;
    tg.readOnly = true;
    var tcb2 = cont.tcb2;
    tcb2.readOnly = true;
    var butc = cont.butc;
    butc.sensitive = false;
    butc.active = false;
    var buta = cont.buta;
    buta.sensitive = false;
    buta.active = false;
    var butst = cont.butst;
    butst.sensitive = false;
    butst.active = false;
    var buts = cont.buts;
    buts.sensitive = true;
    buts.active = true;
  }
}

static function jfetchrow(g) {
  if (g.table.at(g.fetchedRow, 0) > empno) 
    empno = g.table.at(g.fetchedRow, 0);
}

static function jout(g) {
  var ds = g.container.DEPT;
  ds.validate();
}

static function jselect(g) {
  var cont = g.container;
  var tab = cont.EMP.table;
  var tm = tab.transactionManager;
  var tcb = cont.tcb;
  if (tm && tm.eventCount!=0) {
    var msg = new IliErrorMessage;
    msg.message = "choose Cancel/Accept to cancel/validate the changes";
    err.addError(msg);
    err.report();
    err.removeAllErrors();
    tcb.value = numdept;
  } else {
    tab.getParameterAt(0).value = tcb.value;
    numdept = tcb.value;
    tab.select();
    if (tm && tm.isStarted()) {
      var tg = cont.tg;
      tg.readOnly = false;
      var tcb2 = cont.tcb2;
      tcb2.readOnly = false;
    }
    var ds = cont.DEPT;
    var row = ds.table.getColumn("DEPTNO").findFirstRow(tcb.value);
    ds.gotoRow(row);
  }
}

static function jtimer(g) {
  var cont = g.container;
  var tm = cont.EMP.table.transactionManager;
  if (tm) {
    var msg = cont.msg;
    msg.label = tm.eventCount;
  }
}

static function jvalrow(g) {
  var cont = g.container;
  var ds = cont.EMP;
  var tcb = cont.tcb;
  ds.getColumn("EMPNO").value = ++empno;
  ds.getColumn("DEPTNO").value = tcb.value;
}
