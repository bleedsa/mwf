#!/usr/bin/env -S rlwrap etc/k.com

/ utils
has:{~0N~y?x}

/ filters
ext:{x~|#[x]#|y} / y has ext x?
cpp:ext".cpp"
srcs:{[fil;dir](dir,"/",)'d@&fil'd:0:dir}
libcpp:srcs[cpp;"lib"]
srccpp:srcs[cpp;"src"]
win:srcs[cpp;"src/win"]

/ config
A:has[;`argv[]]
rel:A["--release"]|A"--rel"
cfg:!/+((`name;"mwf")
        (`rel;rel)
        (`cc; "clang")
        (`cxx;"clang++"))
cfg,:(!).,'(`cflags;    " "/($[~cfg`rel;"-g -DDBG=1";""]
                             "-Wall -Wextra -Wno-unused-parameter"
                             "-Wno-unused-variable -Wno-unused-function"
                             "-Wno-enum-enum-conversion"
                             "-Io/include"))
cfg,:(!).,'(`cxxflags;  " "/(cfg`cflags
                             "-Iinc"
                             "-Wno-c99-designator"
                             "-std=gnu++2b"))
cfg,:(!).,'(`lnkxxflags;" "/(cfg`cxxflags;""))

/ ninja
rule:{[n;c]$[`m~@c;[(cmd;dep):(c@)'`cmd`dep / deconstruct
                    "rule ",n,"\n command = ",cmd,"\n depfile = ",dep]
             "rule ",n,"\n command = ",c]}
bld:{[R;out;in]"build ",out,": ",R," "," "/in}
cc:bld"cc"
cxx:bld"cxx"
lnk:bld"lnkxx"

/ files
outof:{"o/",x}
(exeof;objof):{outof y,".",x}@'("exe";"o")
libof:{outof "lib/",y,".",x}@"a"
srcof:{outof "src/",x}
bldcxx:{cxx[objof x;,x]}

outd:,[`dep]!,"$out.d"

/ flags
`0:"cc = ",cfg`cc
`0:"cxx = ",cfg`cxx
`0:"cflags = ",cfg`cflags
`0:"cxxflags = ",cfg`cxxflags
`0:"lnkflags = ",cfg`lnkxxflags

/ your basic rules
`0:rule["exe";"$in"]
`0:rule["cxx";outd,(!).,'(`cmd;" "/("$cxx -c $cxxflags -MD -MF $out.d"
                                    "-o $out $in"))]
`0:rule["lnkxx";outd,(!).,'(`cmd;" "/("$cxx $lnkflags $cxxflags -MD -MF $out.d"
                                      "-o $out $in"))]
`0:rule["ar";"ar rcs $out $in"]

/ 3rd
`0:rule["enet";"etc/mk/enet.sh"]
`0:bld["enet";ENET:"o/lib/libenet.a";""]
`0:rule["sdl";"etc/mk/sdl.sh"]
`0:bld["sdl";SDL:"o/lib/libSDL3.a";""]

/ phony
`0:rule["run";"$in"]
`0:bld["run";"run";,exe:exeof cfg`name]

/ objs
`0:"\n"/bldcxx'libcpp
`0:"\n"/bldcxx'win
`0:"\n"/bldcxx'srccpp

/ out
libout:libof cfg`name
`0:bld["ar";libout;objof'libcpp]
`0:lnk[exe;(" "/objof'win;objof"src/0.cpp";libout;ENET;SDL)]
`0:lnk[srv:exeof "srv";(objof"src/srv.cpp";libout;ENET;SDL)]
`0:"default "," "/(SDL;libout;exe;srv);
