// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/cstenum.h
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the enums and constantes for Data Access
// --------------------------------------------------------------------------
#ifndef __Ili_Cstenum_H
#define __Ili_Cstenum_H

enum IliTableFittingMode {
  IliFitNone,
  IliFitProportional,
  IliFitLast
};

enum IliShowMode {
  IliShowNever,
  IliShowAsNeeded,
  IliShowAlways
};

enum IliTableResizeTag {
  IliRTNone,
  IliRTColumnWidth,
  IliRTRowsHeight,
  IliRTHeadersHeight,
  IliRTMarkersWidth
};

enum IliLinkType {
  IliLinkDirect = 0,
  IliLinkOneBreak,
  IliLinkOneBreakSpline,
  IliLinkOneBreakVert,
  IliLinkOneBreakVertSpline,
  IliLinkDoubleBreak,
  IliLinkDoubleBreakSpline,
  IliLinkTypeNbTag
};

enum IliDbScaleType {
  IliDbScaleTypeDate = 0,
  IliDbScaleTypeDateWeek,
  IliDbScaleTypeDateHour,
  IliDbScaleTypeDate2Hours,
  IliDbScaleTypeDate30Minutes,
  IliDbScaleTypeDate15Minutes,
  IliDbScaleTypeMinute,
  IliDbScaleTypeSecond,
  IliDbScaleType5Seconds,
  IliDbScaleType15Seconds,
  IliDbScaleType30Seconds,
  IliDbScaleTypeWeekMinute,
  IliDbScaleTypeWeek5Minutes,
  IliDbScaleTypeWeek15Minutes,
  IliDbScaleTypeWeek30Minutes,
  IliDbScaleTypeNumeric,
  IliDbScaleTypeCount
};

enum IliScaleUnit {
  IliScaleUnitSecond = 0,
  IliScaleUnit5Seconds,
  IliScaleUnit15Seconds,
  IliScaleUnit30Seconds,
  IliScaleUnitMinute,
  IliScaleUnit5Minutes,
  IliScaleUnit15Minutes,
  IliScaleUnit30Minutes,
  IliScaleUnitHour,
  IliScaleUnit2Hours,
  IliScaleUnitDay,
  IliScaleUnitNumeric,
  IliScaleUnitCount
};

enum IliWeekDay {
  IliSunday = 1,
  IliMonday,
  IliTuesday,
  IliWednesday,
  IliThursday,
  IliFriday,
  IliSaturday
};

enum IliMonth {
  IliJanuary = 1,
  IliFebruary,
  IliMarch,
  IliApril,
  IliMay,
  IliJune,
  IliJuly,
  IliAugust,
  IliSeptember,
  IliOctober,
  IliNovember,
  IliDecember
};

enum IliDateInfo {
  IliDateInfoYear = 0,
  IliDateInfoMonth,
  IliDateInfoDay,
  IliDateInfoWeekDay,
  IliDateInfoHour,
  IliDateInfoMinute,
  IliDateInfoSecond,
  IliDateInfoMilliSecond,
  IliDateInfoNumeric,
  IliDateInfoCount
};

enum IliPeriodUnit {
  IliPeriodUnitMonth = 1,
  IliPeriodUnitDay,
  IliPeriodUnitWeekDay,
  IliPeriodUnitHour,
  IliPeriodUnitMinute,
  IliPeriodUnitSecond,
  IliPeriodUnitMonthDay,
  IliPeriodUnitHourMinute,
  IliPeriodUnitCount
};

enum IliPeriodTest {
  IliPeriodEqual = 0,
  IliPeriodNotEqual,
  IliPeriodLess,
  IliPeriodGreater,
  IliPeriodInclude,
  IliPeriodExclude,
  IliPeriodTestCount
};

enum IliDbFieldStyle {
  IliEntryFieldStyle,
  IliTextStyle,
  IliOptionMenuStyle,
  IliTableComboBoxStyle,
  IliToggleStyle,
  IliToggleSelectorStyle,
  IliStringListStyle
};

enum IliFetchPolicy {
  IliFP_AsNeeded,
  IliFP_Immediate
};

enum IliSQLOrderByType {
  IliSQLNoOrder,
  IliSQLAscending,
  IliSQLDescending
};

//---- Compability ----
#define IliGrapherLinkType IliLinkType
#define IliGrapherLinkDirect IliLinkDirect
#define IliGrapherLinkOneBreak IliLinkOneBreak
#define IliGrapherLinkOneBreakSpline IliLinkOneBreakSpline
#define IliGrapherLinkOneBreakVert IliLinkOneBreakVert
#define IliGrapherLinkOneBreakVertSpline IliLinkOneBreakVertSpline
#define IliGrapherLinkDoubleBreak IliLinkDoubleBreak
#define IliGrapherLinkDoubleBreakSpline IliLinkDoubleBreakSpline
#define IliGrapherLinkTypeNbTag IliLinkTypeNbTag

#define IliDbGanttScaleType IliDbScaleType
#define IliDbGanttScaleTypeDate IliDbScaleTypeDate
#define IliDbGanttScaleTypeDateWeek IliDbScaleTypeDateWeek
#define IliDbGanttScaleTypeDateHour IliDbScaleTypeDateHour
#define IliDbGanttScaleTypeDate2Hours IliDbScaleTypeDate2Hours
#define IliDbGanttScaleTypeDate30Minutes IliDbScaleTypeDate30Minutes
#define IliDbGanttScaleTypeDate15Minutes IliDbScaleTypeDate15Minutes
#define IliDbGanttScaleTypeMinute IliDbScaleTypeMinute
#define IliDbGanttScaleTypeSecond IliDbScaleTypeSecond
#define IliDbGanttScaleType5Seconds IliDbScaleType5Seconds
#define IliDbGanttScaleType15Seconds IliDbScaleType15Seconds
#define IliDbGanttScaleType30Seconds IliDbScaleType30Seconds
#define IliDbGanttScaleTypeWeekMinute IliDbScaleTypeWeekMinute
#define IliDbGanttScaleTypeWeek5Minutes IliDbScaleTypeWeek5Minutes
#define IliDbGanttScaleTypeWeek15Minutes IliDbScaleTypeWeek15Minutes
#define IliDbGanttScaleTypeWeek30Minutes IliDbScaleTypeWeek30Minutes
#define IliDbGanttScaleTypeNumeric IliDbScaleTypeNumeric
#define IliDbGanttScaleTypeCount IliDbScaleTypeCount

#define IliDbGanttScaleUnit IliScaleUnit
#define IliDbGanttScaleUnitSecond IliScaleUnitSecond
#define IliDbGanttScaleUnit5Seconds IliScaleUnit5Seconds
#define IliDbGanttScaleUnit15Seconds IliScaleUnit15Seconds
#define IliDbGanttScaleUnit30Seconds IliScaleUnit30Seconds
#define IliDbGanttScaleUnitMinute IliScaleUnitMinute
#define IliDbGanttScaleUnit5Minutes IliScaleUnit5Minutes
#define IliDbGanttScaleUnit15Minutes IliScaleUnit15Minutes
#define IliDbGanttScaleUnit30Minutes IliScaleUnit30Minutes
#define IliDbGanttScaleUnitHour IliScaleUnitHour
#define IliDbGanttScaleUnit2Hours IliScaleUnit2Hours
#define IliDbGanttScaleUnitDay IliScaleUnitDay
#define IliDbGanttScaleUnitNumeric IliScaleUnitNumeric
#define IliDbGanttScaleUnitCount IliScaleUnitCount

#define IliDbGanttWeekDay IliWeekDay
#define IliDbGanttSunday IliSunday
#define IliDbGanttMonday IliMonday
#define IliDbGanttTuesday IliTuesday
#define IliDbGanttWednesday IliWednesday
#define IliDbGanttThursday IliThursday
#define IliDbGanttFriday IliFriday
#define IliDbGanttSaturday IliSaturday

#define IliDbGanttMonth IliMonth
#define IliDbGanttJanuary IliJanuary
#define IliDbGanttFebruary IliFebruary
#define IliDbGanttMarch IliMarch
#define IliDbGanttApril IliApril
#define IliDbGanttMay IliMay
#define IliDbGanttJune IliJune
#define IliDbGanttJuly IliJuly
#define IliDbGanttAugust IliAugust
#define IliDbGanttSeptember IliSeptember
#define IliDbGanttOctober IliOctober
#define IliDbGanttNovember IliNovember
#define IliDbGanttDecember IliDecember

#define IliDbGanttPeriodUnit IliPeriodUnit
#define IliDbGanttPeriodUnitMonth IliPeriodUnitMonth
#define IliDbGanttPeriodUnitDay IliPeriodUnitDay
#define IliDbGanttPeriodUnitWeekDay IliPeriodUnitWeekDay
#define IliDbGanttPeriodUnitHour IliPeriodUnitHour
#define IliDbGanttPeriodUnitMinute IliPeriodUnitMinute
#define IliDbGanttPeriodUnitSecond IliPeriodUnitSecond
#define IliDbGanttPeriodUnitMonthDay IliPeriodUnitMonthDay
#define IliDbGanttPeriodUnitHourMinute IliPeriodUnitHourMinute
#define IliDbGanttPeriodUnitCount IliPeriodUnitCount

#define IliDbGanttPeriodTest IliPeriodTest
#define IliDbGanttPeriodEqual IliPeriodEqual
#define IliDbGanttPeriodNotEqual IliPeriodNotEqual
#define IliDbGanttPeriodLess IliPeriodLess
#define IliDbGanttPeriodGreater IliPeriodGreater
#define IliDbGanttPeriodInclude IliPeriodInclude
#define IliDbGanttPeriodExclude IliPeriodExclude
#define IliDbGanttPeriodTestCount IliPeriodTestCount

#define IliScaleDate IliDate
#define IliScaleDateInfo IliDateInfo
#define IliScaleDateYear IliDateInfoYear
#define IliScaleDateMonth IliDateInfoMonth
#define IliScaleDateDay IliDateInfoDay
#define IliScaleDateWeekDay IliDateInfoWeekDay
#define IliScaleDateHour IliDateInfoHour
#define IliScaleDateMinute IliDateInfoMinute
#define IliScaleDateSecond IliDateInfoSecond
#define IliScaleDateNumeric IliDateInfoNumeric
#define IliScaleDateInfoCount IliDateInfoCount

#endif
