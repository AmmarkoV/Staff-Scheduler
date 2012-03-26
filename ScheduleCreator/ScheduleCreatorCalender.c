#include "ScheduleCreatorCalender.h"


int YearIsLeapYear(unsigned int year)
{
    int res=0;
    if ( year % 400 == 0 ) { res=1; }
    if ( year % 4 == 0 ) {
                            if ( year % 100 != 0 ) { res=1; }
                         }

    return res;
}

int TotalDaysOfMonth(unsigned int month , unsigned int year)
{
    switch ( month )
    {
      case 1 : return 31; break;
      case 2 : if ( YearIsLeapYear(year) ) { return 29; }
               return 28;
               break;
      case 3 : return 31; break;
      case 4 : return 30; break;
      case 5 : return 31; break;
      case 6 : return 30; break;
      case 7 : return 31; break;
      case 8 : return 31; break;
      case 9 : return 30; break;
      case 10 : return 31; break;
      case 11 : return 30; break;
      case 12 : return 31; break;
      default :
        return 0;
      break;
    };
}



//

// given month, day, year, returns day of week, eg. Monday = 0 etc.

// tested for 1901 to 2099 (seems to work from 1800 on too)

//

int GetWeekDay(int day,int month,  int year)

{

int ix=0, tx=0, vx=0;

switch (month)
{
case 2 :
case 6 : vx = 0; break;
case 8 : vx = 4; break;
case 10 : vx = 8; break;
case 9 :
case 12 : vx = 12; break;
case 3 :
case 11 : vx = 16; break;
case 1 :
case 5 : vx = 20; break;
case 4 :
case 7 : vx = 24; break;

}
if (year > 1900) // 1900 was not a leap year
year -= 1900;
ix = ((year - 21) % 28) + vx + (month > 2); // take care of February
tx = (ix + (ix / 4)) % 7 + day; // take care of leap year
return (tx % 7);

}


char * GetWeekDayStr(unsigned int dayofweek)
{
    switch (dayofweek)
    {
        case 0 : return "Δευτέρα"; break;
        case 1 : return "Τρίτη"; break;
        case 2 : return "Τετάρτη"; break;
        case 3 : return "Πέμπτη"; break;
        case 4 : return "Παρασκεύή"; break;
        case 5 : return "Σάββατο"; break;
        case 6 : return "Κυριακή"; break;
    };

  return "?";
}



/*




function Main_Calender_Function(day,month,year,mode:integer):integer;
var a,y,m,JD,reslt,d1,d4,L:integer;
begin
// mode=0 return DayofYear , mode=1 return DayOfWeek , mode=2 return WeekofYear
a:=0;
y:=0;
m:=0;
JD:=0;
reslt:=0;
if ((day>=1)and(day<=31)) then reslt:=reslt+1;
if ((month>=1)and(month<=12)) then  reslt:=reslt+1;
if ((mode>=0)and(mode<=2)) then  reslt:=reslt+1;

if (reslt=3) then
begin
a:=(14-month) div 12;
y:=year+4800-a;
m:=month+12*a-3;
JD:=day+(153*m+2)div 5+y*365+y div 4-y div 100+y div 400-32045;

case mode of

0:           begin
               y:=year+4799; //Day of Year
               reslt:=JD-(y*365+y div 4-y div 100+y div 400-31739);
             end;
1:           begin
               reslt:=JD mod 7+1;
             end;
2:           begin
                d4:=(JD+31741 - (JD mod 7)) mod 146097 mod 36524 mod 1461;
                L:=d4 div 1460;
                d1:=((d4-L) mod 365) + L;
                reslt:=d1 div 7+1;
             end;
3:          reslt:=JD;  //RETURN JULIAN DATE
end;


end else
  begin
  //OuttextCenter('Wrong input - Calender_Function()');
  reslt:=-1;
  end;

Main_Calender_Function:=reslt;
end;





procedure GetEasterDate (y, method : word; var d, m : integer);
var
   FirstDig, Remain19, temp,              {intermediate results}
   tA, tB, tC, tD, tE         : integer;  {table A to E results}
begin

{ :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
  *  This algorithm is an arithmetic interpretation
  *  of the 3 step Easter Dating Method developed
  *  by Ron Mallen 1985, as a vast improvement on
  *  the method described in the Common Prayer Book

  *  Published Australian Almanac 1988
  *  Refer to this publication, or the Canberra Library
  *  for a clear understanding of the method used

  *  Because this algorithm is a direct translation of the
  *  official tables, it can be easily proved to be 100%
  *  correct

  *  It's free!  Please do not modify code or comments!

  *  11.7.99 - Pascal converting by Thomas Koehler, www.thkoehler.de

   :=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=}


    FirstDig := y div 100;            {first 2 digits of year}
    Remain19 := y mod 19;             {remainder of year / 19}

    if (method = 1) or (method = 2) then
        begin
         {calculate PFM date}
        tA := ((225 - 11 * Remain19) mod 30) + 21;

         {find the next Sunday}
        tB := (tA - 19) mod 7;
        tC := (40 - FirstDig) mod 7;

        temp := y mod 100;
        tD := (temp + temp div 4) mod 7;

        tE := ((20 - tB - tC - tD) mod 7) + 1;
        d := tA + tE;

        if method = 2 then  {convert Julian to Gregorian date}
            begin
            {10 days were skipped
            in the Gregorian calendar from 5-14 Oct 1582}
            temp := 10;
            {Only 1 in every 4 century years are leap years in the Gregorian
            calendar (every century is a leap year in the Julian calendar)}
            if y > 1600 then
                temp := temp + FirstDig - 16 - ((FirstDig - 16) div 4);
            d := d + temp;
            end;
        end
    else
        begin
       {calculate PFM date}
        temp := (FirstDig - 15) div 2 + 202 - 11 * Remain19;
        if (FirstDig > 26) then temp := temp - 1;
        if (FirstDig > 38) then temp := temp - 1;
        if (FirstDig = 21) Or (FirstDig = 24) Or (FirstDig = 25)
          Or (FirstDig = 33) Or (FirstDig = 36) Or (FirstDig = 37) then
            temp := temp - 1;

        temp := temp mod 30;
        tA := temp + 21;
        if (temp = 29) then
            tA := tA - 1;
        if (temp = 28) and (Remain19 > 10) then
            tA := tA - 1;

       {find the next Sunday}
        tB := (tA - 19) mod 7;

        temp := (40 - FirstDig) mod 4;
        {//tC := temp - (temp > 1) - (temp := 3)}
        tC := temp;
        if temp > 1 then tC := tC + 1;
        if temp = 3 then tC := tC + 1;

        temp := y mod 100;
        tD := (temp + temp div 4) mod 7;

        tE := ((20 - tB - tC - tD) mod 7) + 1;
        d := tA + tE;

        end;

  {return the date}
    m := 3;
    if (d > 61) then
    begin
        d := d - 61;  {when the original calculation is converted to the}
        m := 5;       {Gregorian calendar, Easter Sunday can occur in May}
    end;
    if (d > 31) then
      begin
          d := d - 31;
          m := 4;
      end;
end;








{

procedure moon_posit( Y, M, D : int )

    var AG : real;                          // % Moon's age
        DI : real;                          // % Moon's distance in earth radii
        LA : real;                          // % Moon's ecliptic latitude
        LO : real;                          // % Moon's ecliptic longitude
        Phase : string;
        Zodiac : string;

        YY, MM, K1, K2, K3, JD : integer;
        IP, DP, NP, RP : real;

    if not isdayofmonth( Y, M, D ) then
        put "invalid date"
        return
    end if

    //% calculate the Julian date at 12h UT
    YY := Y - floor( ( 12 - M ) / 10 );
    MM := M + 9;
    if (MM >= 12) then   MM := MM - 12;

    K1 := floor( 365.25 * ( YY + 4712 ) );
    K2 := floor( 30.6 * MM + 0.5 );
    K3 := floor( floor( ( YY / 100 ) + 49 ) * 0.75 ) - 38;

    JD := K1 + K2 + D + 59;                  //% for dates in Julian calendar
    if (JD > 2299160) then JD := JD - K3;                       //% for Gregorian calendar

    //% calculate moon's age in days
    IP := normalize( ( JD - 2451550.1 ) / 29.530588853 );
    AG := IP*29.53;

    if    AG <  1.84566 then Phase := 'NEW';
    else if AG <  5.53699 then Phase := 'Waxing crescent';
    else if AG <  9.22831 then Phase := 'First quarter';
    else if AG < 12.91963 then Phase := 'Waxing gibbous';
    else if AG < 16.61096 then Phase := 'FULL';
    else if AG < 20.30228 then Phase := 'Waning gibbous';
    else if AG < 23.99361 then Phase := 'Last quarter';
    else if AG < 27.68493 then Phase := 'Waning crescent';
    else                     Phase := 'NEW';

    IP := IP*2*PI;                           //% Convert phase to radians

    //% calculate moon's distance
    DP := 2*PI*normalize( ( JD - 2451562.2 ) / 27.55454988 );
    DI := 60.4 - 3.3*cos( DP ) - 0.6*cos( 2*IP - DP ) - 0.5*cos( 2*IP );

    //% calculate moon's ecliptic latitude
    NP := 2*PI*normalize( ( JD - 2451565.2 ) / 27.212220817 );
    LA := 5.1*sin( NP );

    //% calculate moon's ecliptic longitude
    RP := normalize( ( JD - 2451555.8 ) / 27.321582241 );
    LO := 360*RP + 6.3*sin( DP ) + 1.3*sin( 2*IP - DP ) + 0.7*sin( 2*IP );

    if      LO <  33.18 then Zodiac := 'Pisces'
    else if LO <  51.16 then Zodiac := 'Aries'
    else if LO <  93.44 then Zodiac := 'Taurus'
    else if LO < 119.48 then Zodiac := 'Gemini'
    else if LO < 135.30 then Zodiac := 'Cancer'
    else if LO < 173.34 then Zodiac := 'Leo'
    else if LO < 224.17 then Zodiac := 'Virgo'
    else if LO < 242.57 then Zodiac := 'Libra'
    else if LO < 271.26 then Zodiac := 'Scorpio'
    else if LO < 302.49 then Zodiac := 'Sagittarius'
    else if LO < 311.72 then Zodiac := 'Capricorn'
    else if LO < 348.58 then Zodiac := 'Aquarius'
    else                     Zodiac := 'Pisces';

    //% display results
    //put "phase         = ", Phase
    //put "age           = ", round2( AG ), " days"
    //put "distance      = ", round2( DI ), " earth radii"
    //put "ecliptic"
    //put " latitude     = ", round2( LA ), '°'
    //put " longitude    = ", round2( LO ), '°'
    //put "constellation = ", Zodiac

end;

//% check for valid date
function isdayofmonth( year, month, day : int ) : boolean
var daysofmonth : int
begin

    if (month < 1) or (12 < month) then isdayofmonth:=false else                        //% invalid month
begin
    case month of                           //% get days in this month
     4,6,9,11:
        daysofmonth := 30;                   //% Apr, Jun, Sep, Nov
     2:
        daysofmonth := 28                   //% Feb normal
        if year mod 4 = 0 then
            if not((year mod 100 = 0) and
                   (year mod 400 ~= 0)) then
                daysofmonth := 29;           //% Feb leap year
            end;
        end;
    1,3,5,7,8,12:
        daysofmonth := 31;                   //% other months
    end;

isdayofmonth:= (0 < day) and (day <= daysofmonth) ;
end;


end;

//% round to 2 decimal places
function round2( x : real ) : real;
begin
 round2 := ( round( 100*x )/100.0 );
end;

//% normalize values to range 0...1
function normalize( v : real ) : real;
begin
 v := v - floor( v );
 if v < 0 then v := v + 1;
 normalize:=v;
end;
                }
begin
end.*/
