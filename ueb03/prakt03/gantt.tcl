#!/spr1opt1/bin/wish -f

#
# ShowGantt - Display Gantt Chart
#
# Implements the functions to display a 'Gantt Chart'.
# Input is taken from a file which is regularly polled
# if it has new contents. 
#
# Bases on the original code by Prof. L.Thiele. Modified by S.Walter
# for standalone usage and polling. 
#
# Modified by Frank Hannig for the visualization of release times,
# deadline, and periods.
# 
# The following global variables had to be added:
#   p_line         Current line while parsing the file
#   p_file         Open file handle
#   p_filename     The file name
#   p_data         The data from the file
#

# ------------------------------------------------------------
proc GanttChartTest { } {
  global p_data 
  set Data {{Mult_1 {1 3 first} {3 5 second} {8 10 soso}} {Mult_2 {2 3 schrott} {3 5 6} {5 7 8}} {ALU_1 {2 4 10} {4 5 11} {7 8 5} {5 6 4} {9 10 turn}} {ALU_2 {8 10 9}}}

  GanttChart {} -1 -1
}

proc GanttChart {{Data {}} {Min -1} {Max -1} {title "GanttChart"}} {

# Collect information about input-data
# MaxTime = Maximal Time
# MinTime = Minimal Time

  global p_data p_filename
  if {$Data!={}} {set p_data $Data}

  catch {dismiss .frame1}
  catch {dismiss .frame2}
  catch {destroy .frame1}
  catch {destroy .frame2}
  wm minsize . 10 10
  wm title . "$title"
  catch {locate .}

  # build widget .frame1
  frame .frame1 \
    -borderwidth {2} \
    -relief {raised}

  # build widget .frame2
  frame .frame2 \
    -borderwidth {2} \
    -relief {raised}

  # build widget .frame1.scrollbar4
  scrollbar .frame1.scrollbar4 \
    -command ".frame1.canvas2 yview" \
    -relief {ridge}

  # build widget .frame1.scrollbar3
  scrollbar .frame1.scrollbar3 \
    -command ".frame1.canvas2 xview" \
    -orient {horizontal} \
    -relief {ridge}

  # build widget .frame1.canvas2
  canvas .frame1.canvas2 
  
  # bindings
  bind .frame1.canvas2 <Any-Enter> "focus .frame1.canvas2"
  bind .frame1.canvas2 <B3-Motion> ".frame1.canvas2 scan dragto %x %y"
  bind .frame1.canvas2 <Button-3> ".frame1.canvas2 scan mark %x %y"

  # build widget .frame2.button
  button .frame2.button \
    -command "catch {dismiss .}; catch {destroy .}" \
    -text {Dismiss}

  scale .frame2.scalex -from 1 -to 10 -length 5c -orient horizontal -command "GanttNewDraw $Min $Max" -relief {raised} -showvalue 0

   scale .frame2.scaley -from 1 -to 10 -length 5c -orient horizontal -command "GanttNewDraw  $Min $Max" -relief {raised} -showvalue 0
   .frame2.scaley set 5
   .frame2.scalex set 5

  label .frame2.labelx -text "Scale X"
  label .frame2.labely -text "Scale Y"

  # pack widget .frame1
  pack append .frame1 \
    .frame1.scrollbar4 {right frame center filly} \
    .frame1.canvas2 {top frame center expand fill} \
    .frame1.scrollbar3 {bottom frame center fillx}

  # pack widget .frame2
  pack append .frame2 \
    .frame2.scalex {left frame center} \
    .frame2.labelx {left} \
    .frame2.button {left frame center expand} \
    .frame2.labely {left} \
    .frame2.scaley {right frame center}


  # pack widget .
  pack append . \
    .frame1 {top frame center expand fill} \
    .frame2 {bottom frame center fill}

  GanttDraw 1 1 $Min $Max
  set nmod [file mtime $p_filename]
  after 500 [list Poll $Min $Max $nmod ]
}

proc Poll {Min Max lmod} {
  global p_filename
  set nmod [file mtime $p_filename]
  if {$nmod != $lmod} {
    set lmod $nmod
    #puts "$p_filename modified!"
    if { 0==[ReadData] } { puts "error in data while polling, nothing updated" } else {GanttNewDraw $Min $Max 1}
  }
  after 500 [list Poll $Min $Max $lmod ]
}

proc GanttNewDraw {Min Max value} {
	GanttDraw [expr [.frame2.scalex get] / 5.] [expr [.frame2.scaley get] / 5.] $Min $Max
}


# Procedure: GanttDraw
proc GanttDraw {SCALEX SCALEY Min Max} {

  global p_data

  set tmp ""
  foreach res $p_data {
	foreach item [lrange $res 4 end] {
		set tmp [concat $tmp [lrange $item 0 1]]
	}
  }
  set tmp [lsort -real -decreasing $tmp]
  if {$Min >= 0} {
	set MinTime $Min
  } else {
	set MinTime [lindex $tmp [expr [llength $tmp] - 1]]
  }
  if {$Max >= 0} {
	set MaxTime $Max
  } else {
	set MaxTime [lindex $tmp 0]
  }
	
  set CountRes [llength $p_data]

  set StartX 3
  set EndX [expr $SCALEX * $MaxTime + 4]
  set StartY [expr $SCALEY * $CountRes + 1.5]
  set EndY 1

  #configure canvas
  set X "[expr $EndX + 1]\c"
  set Y "[expr $StartY + 1.5]\c"
  .frame1.canvas2 configure \
    -height 5c \
    -insertofftime {600} \
    -relief {sunken} \
    -scrollregion "0c 0c $X $Y" \
    -width 20c \
    -xscrollcommand ".frame1.scrollbar3 set" \
    -yscrollcommand ".frame1.scrollbar4 set"

  .frame1.canvas2 delete all

  #create Axes
  .frame1.canvas2 create line "$StartX\c" "$StartY\c" "$StartX\c" "$EndY\c" -fill black -width 3
  .frame1.canvas2 create line "$StartX\c" "$StartY\c" "$EndX\c" "$StartY\c" -fill black -arrow last -width 3
  .frame1.canvas2 create text "[expr $StartX - 2.5]\c" "[expr $EndY]\c" -text "Resources" -anchor sw -fill blue
  .frame1.canvas2 create text "[expr $EndX + 0.5]\c" "[expr $StartY + 0.5]\c" -text "Cycles" -anchor ne -fill blue

  # vertical scaling
  set count 0
  foreach item $p_data {
    set name [lindex $item 0]
    set tmp [expr $StartY - ($count + 0.5) * $SCALEY]
    .frame1.canvas2 create text "1c" "$tmp\c" -text "$name" -anchor w
    .frame1.canvas2 create text "$EndX\c" "$tmp\c" -text "$name" -anchor w
    set tmp [expr $StartY - ($count + 1) * $SCALEY]
    .frame1.canvas2 create line "$StartX\c" "$tmp\c" "$EndX\c" "$tmp\c" -fill black
    incr count 1
}

# Horizontal scaling
for {set time 0} {$time <= $MaxTime} {incr time 1} {
	set x [expr $StartX + $SCALEX * $time]
	.frame1.canvas2 create line "$x\c" "$StartY\c" "$x\c" "[expr $StartY + .2]\c"  -fill black
}
for {set number 0} {$number <= $MaxTime} {incr number 5} {
	set x [expr $StartX + $SCALEX * $number]
	.frame1.canvas2 create line "$x\c" "[expr $StartY + .4]\c" "$x\c" "$EndY\c"  -fill black
	.frame1.canvas2 create text "$x\c" "[expr $StartY + 0.5]\c" -text $number -anchor n
	.frame1.canvas2 create text "$x\c" "[expr $EndY - 0.1]\c" -text $number -anchor s
}
for {set number 0} {$number <= $MaxTime} {incr number 10} {
	set x [expr $StartX + $SCALEX * $number]
	.frame1.canvas2 create line "$x\c" "[expr $StartY + .4]\c" "$x\c" "$EndY\c"  -fill black -width 2
	.frame1.canvas2 create text "$x\c" "[expr $EndY - 0.1]\c" -text $number -anchor s
}
set x [expr $StartX + $SCALEX * $MinTime]
	.frame1.canvas2 create line "$x\c" "[expr $StartY]\c" "$x\c" "$EndY\c"  -fill red -width 2
	.frame1.canvas2 create text "[expr $x + 0.1]\c" "[expr $EndY - 0.1]\c" -text {start} -anchor nw -fill red
set x [expr $StartX + $SCALEX * $MaxTime]
	.frame1.canvas2 create line "$x\c" "[expr $StartY]\c" "$x\c" "$EndY\c"  -fill red -width 2
	.frame1.canvas2 create text "[expr $x - 0.1]\c" "[expr $EndY - 0.1]\c" -text {end} -anchor ne -fill red



# show boxes
set count 0
foreach res $p_data {
	# F. H., get period draw it to chart
	set period [lindex $res 3]
	if {$period > 0} {
		for {set number $period} {$number < $MaxTime} {incr number $period} {
			set x [expr $StartX + $SCALEX * $number]
			.frame1.canvas2 create line "$x\c" "[expr $StartY - ($count + 0.975) * $SCALEY]\c" "$x\c" "[expr $StartY - ($count + 0.025) * $SCALEY]\c"  -fill MediumTurquoise -dash 5 -width 2
		}
	}

	foreach item [lrange $res 4 end] {
		set first [lindex $item 0]
		set last [lindex $item 1]
		set name [lindex $item 2]
                if {($first < $last)} {
			.frame1.canvas2 create rectangle "[expr $StartX + $first * $SCALEX]\c" "[expr $StartY - ($count + 0.875) * $SCALEY]\c" "[expr $StartX + ($last - 0.1) * $SCALEX]\c" "[expr $StartY - ($count + 0.125) * $SCALEY]\c" -fill blue
			.frame1.canvas2 create text "[expr $StartX + ($first + $last - 0.1) * $SCALEX / 2.]\c" "[expr $StartY - ($count + 0.5) * $SCALEY]\c" -text $name -fill yellow -anchor c
		} else { 
			if {$last == $MinTime} {
				.frame1.canvas2 create rectangle "[expr $StartX + $first * $SCALEX]\c" "[expr $StartY - ($count + 0.875) * $SCALEY]\c" "[expr $StartX + ($MaxTime - 0.1) * $SCALEX]\c" "[expr $StartY - ($count + 0.125) * $SCALEY]\c" -fill blue
				.frame1.canvas2 create text "[expr $StartX + ($first + $MaxTime - 0.1) * $SCALEX / 2.]\c" "[expr $StartY - ($count + 0.5) * $SCALEY]\c" -text $name -fill yellow -anchor c
			} else {
			.frame1.canvas2 create rectangle "[expr $StartX + $first * $SCALEX]\c" "[expr $StartY - ($count + 0.875) * $SCALEY]\c" "[expr $StartX + ($MaxTime - 0.1) * $SCALEX]\c" "[expr $StartY - ($count + 0.125) * $SCALEY]\c" -fill blue
			.frame1.canvas2 create text "[expr $StartX + ($first + $MaxTime - 0.1) * $SCALEX / 2.]\c" "[expr $StartY - ($count + 0.5) * $SCALEY]\c" -text $name -fill yellow -anchor c
			.frame1.canvas2 create line "[expr $StartX + ($MaxTime - 0.1) * $SCALEX]\c" "[expr $StartY - ($count + 0.5) * $SCALEY]\c" "[expr $StartX + $MaxTime * $SCALEX + 0.5]\c" "[expr $StartY - ($count + 0.5) * $SCALEY]\c" -fill black -width 1 -arrow last
			.frame1.canvas2 create rectangle "[expr $StartX + $MinTime * $SCALEX]\c" "[expr $StartY - ($count + 0.875) * $SCALEY]\c" "[expr $StartX + ($last - 0.1) * $SCALEX]\c" "[expr $StartY - ($count + 0.125) * $SCALEY]\c" -fill blue
			.frame1.canvas2 create text "[expr $StartX + ($MinTime + $last - 0.1) * $SCALEX / 2.]\c" "[expr $StartY - ($count + 0.5) * $SCALEY]\c" -text $name -fill yellow -anchor c
			.frame1.canvas2 create line "[expr $StartX + $MinTime * $SCALEX - 0.5]\c" "[expr $StartY - ($count + 0.5) * $SCALEY]\c" "[expr $StartX + $MinTime * $SCALEX]\c" "[expr $StartY - ($count + 0.5) * $SCALEY]\c" -fill black -width 1 -arrow last
			}
		}
	}

	# F. H., get release time and deadline and draw them to chart
	set rtime [lindex $res 1]
	set deadline [lindex $res 2]
	if {$rtime > -1} {
		.frame1.canvas2 create line "[expr $StartX + $rtime * $SCALEX]\c" "[expr $StartY - ($count + 0.975) * $SCALEY]\c" "[expr $StartX + $rtime * $SCALEX]\c" "[expr $StartY - ($count + 0.025) * $SCALEY]\c" -arrow first -fill green3 -width 3
		if {$period > 0} {
			for {set number [expr $period+$rtime]} {$number < $MaxTime} {incr number $period} {
				set x [expr $StartX + $SCALEX * $number]
				.frame1.canvas2 create line "$x\c" "[expr $StartY - ($count + 0.975) * $SCALEY]\c" "$x\c" "[expr $StartY - ($count + 0.025) * $SCALEY]\c"  -arrow first -fill green3 -width 3
			}
		}
	}
	if {$deadline > -1} {
		if {$period > 0} {
			for {set number [expr $deadline]} {$number <= $MaxTime} {incr number $period} {
				set x [expr $StartX + $SCALEX * $number]
				.frame1.canvas2 create line "$x\c" "[expr $StartY - ($count + 0.975) * $SCALEY]\c" "$x\c" "[expr $StartY - ($count + 0.025) * $SCALEY]\c"  -arrow last -fill orange -width 3
			}
		} else {
			.frame1.canvas2 create line "[expr $StartX + $deadline * $SCALEX]\c" "[expr $StartY - ($count + 0.975) * $SCALEY]\c" "[expr $StartX + $deadline * $SCALEX]\c" "[expr $StartY - ($count + 0.025) * $SCALEY]\c" -arrow last -fill orange -width 3
		}
	}
	incr count 1
}

return
}

proc GanttSort {first second} {
	set num1 [lindex $first 0]
	set num2 [lindex $second 0]
	set num3 [lindex $first 1]
	set num4 [lindex $second 1]
	if {$num1 < $num2} {
		return -1
	}
	if {$num1 == $num2} {
		if {$num3 < $num4} {
			return -1
		}
		if {$num3 == $num4} {
			return 0
		}
		if {$num3 > $num4} {
			return 1
		}
	}
	if {$num1 > $num2} {
		return 1
	}
}


proc GetKeyWord { } {
  global p_line p_file
  set done "no"
  while {$done=="no"} {
    set r 0
    if {$p_line==""} { set r [gets $p_file p_line] }
    if {$r == -1} { return "" }
    if {[regexp {^[#\n]} $p_line]} { set p_line ""; continue; }
    if {[regexp {^[ \t]+(.*)} $p_line trash a]} { set p_line $a; continue; }
    if {[regexp {^([\{\}])(.*)} $p_line trash a b]} {
      set p_line $b
      set done "yes"
    } elseif {[regexp {^([^{} \t\n#]+)(.*)} $p_line trash a b]} {
      set p_line $b
      set done "yes"
    }
  }  
  return $a
}

proc SearchBlock { n {a {}}} {
  while {1} {
    if {$a=={}} {set a [GetKeyWord] }
    if {$a==$n} { return 1 }
    if {$a==""} {return 0 }
    set a [SkipBlock]
    if {$a==0} { return 0 }
    set a ""
  }
}

proc SkipBlock { } {
  set a [GetKeyWord]
  if {[regexp {[^\{]} $a]} { return 0 }
  while {[regexp {^[^\}]} $a]} { set a [GetKeyWord]} 
  return 1
}

proc GetListItems { n } {
  set c {}
  set a [GetKeyWord]
  if {[regexp {[^\{]} $a]} { return "" }
  while { $n!=0 } {
    set b [GetKeyWord]
    lappend c $b
    set n [expr $n-1]
  }
  set a [GetKeyWord]
  if {[regexp {[^\}]} $a]} { return "" }
  return $c
}

proc ReadData { } {

global p_data p_line p_file p_filename
set p_file [open $p_filename r]
set p_line ""

if {0==[SearchBlock NUMBER_OF_NODES]} { close $p_file; return 0}
set nofn [GetListItems 1]
if {$nofn==""} {close $p_file; return 0}

set a [GetKeyWord]
if {$a=="NODE_NAMES"} {
  set nnames [GetListItems $nofn]
  if {$nnames==""} {close $p_file; return 0}
  set a [GetKeyWord]
  } else {
  for {set c 1} {$c <= $nofn} {incr c 1} { lappend nnames $c}
  #SkipBlock
}

if {$a!="NUMBER_OF_RESOURCES"} { close $p_file; return 0}
set nofr [GetListItems 1]
if {$nofr==""} {close $p_file; return 0}

set a [GetKeyWord]
if {$a=="RESOURCE_NAMES"} {
  set rnames [GetListItems $nofr]
  if {$rnames==""} {close $p_file; return 0}
  set a [GetKeyWord]
  } else {
  for {set c 1} {$c <= $nofr} {incr c 1} { lappend rnames $c}
  #SkipBlock
  #set a ""
}

#
# F.H.
#
if {0==[SearchBlock RELEASE_TIMES $a]} { close $p_file; return 0}
if {$a=="RELEASE_TIMES"} {
  set releasetimes [GetListItems $nofr]
  if {$releasetimes==""} {close $p_file; return 0}
  set a [GetKeyWord]
  } else {
  for {set c 1} {$c <= $nofr} {incr c 1} { lappend releasetimes $c}
  #SkipBlock
  #set a ""
}
if {0==[SearchBlock DEADLINES $a]} { close $p_file; return 0}
if {$a=="DEADLINES"} {
  set deadlines [GetListItems $nofr]
  if {$deadlines==""} {close $p_file; return 0}
  set a [GetKeyWord]
  } else {
  for {set c 1} {$c <= $nofr} {incr c 1} { lappend deadlines $c}
  #SkipBlock
  #set a ""
}
if {0==[SearchBlock PERIODS $a]} { close $p_file; return 0}
if {$a=="PERIODS"} {
  set periods [GetListItems $nofr]
  if {$periods==""} {close $p_file; return 0}
  set a [GetKeyWord]
  } else {
  for {set c 1} {$c <= $nofr} {incr c 1} { lappend periods $c}
  #SkipBlock
  #set a ""
}
#

if {0==[SearchBlock RESOURCE_MAP $a]} { close $p_file; return 0}
set r_map [GetListItems $nofn]
if {$r_map==""} {close $p_file; return 0}

if {0==[SearchBlock START_TIME]} { close $p_file; return 0}
set t_start [GetListItems $nofn]
if {$t_start==""} {close $p_file; return 0}

if {0==[SearchBlock END_TIME]} { close $p_file; return 0}
set t_end [GetListItems $nofn]
if {$t_end==""} {close $p_file; return 0}

set p_data {}

set ac 0
foreach a $rnames {
  set x {}
  lappend x $a

  # F.H.
  lappend x [lindex $releasetimes $ac]
  lappend x [lindex $deadlines $ac]
  lappend x [lindex $periods $ac]

  set bc 0
  foreach b $nnames {
    if {[lindex $r_map $bc]==[expr $ac+1]} {
      set y {}
      lappend y [lindex $t_start $bc]
      lappend y [lindex $t_end $bc]
      lappend y $b
      if {[lindex $t_start $bc]!=[lindex $t_end $bc]} {lappend x $y}
    }
    incr bc 1
  }
  lappend p_data $x
  incr ac 1
}
close $p_file
return 1
}

proc ShowGantt { n } {
global p_filename
set p_filename $n
if { 0==[ReadData] } { puts "error in data, aborted"; return 0; }
GanttChart {}
}

# -------------------------------------------------------------
#
# Main function, used whan started from the shell as:
#
#      showgantt <file> {min} {max}
#
set p_filename [lindex $argv 0]
catch { set min [lindex $argv 1] }
catch { set max [lindex $argv 2] }
if {$min==""} {set min -1}
if {$max==""} {set max -1}
if { 0==[ReadData] } { puts "error in data"; exit 1; }
GanttChart {} $min $max




