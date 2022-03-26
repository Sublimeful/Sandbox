let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Desktop/Sandbox
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
tabnew
tabnew
tabrewind
edit src/Game.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
balt src/Algorithms.cpp
setlocal fdm=marker
setlocal fde=0
setlocal fmr=<--,-->
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 177 - ((17 * winheight(0) + 10) / 21)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 177
normal! 0
tabnext
edit src/Game.hpp
argglobal
setlocal fdm=marker
setlocal fde=0
setlocal fmr=<--,-->
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 27 - ((26 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 27
normal! 024|
tabnext
argglobal
if bufexists("term://~/Desktop/Sandbox//800:C:/Windows/system32/cmd.exe") | buffer term://~/Desktop/Sandbox//800:C:/Windows/system32/cmd.exe | else | edit term://~/Desktop/Sandbox//800:C:/Windows/system32/cmd.exe | endif
if &buftype ==# 'terminal'
  silent file term://~/Desktop/Sandbox//800:C:/Windows/system32/cmd.exe
endif
balt term://~/Desktop/Sandbox//800:C:/Windows/system32/cmd.exe
setlocal fdm=marker
setlocal fde=0
setlocal fmr=<--,-->
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 10016 - ((15 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10016
normal! 0
tabnext 1
badd +177 src/Game.cpp
badd +7 src/Algorithms.cpp
badd +85 src/Game.hpp
badd +2 src/Material.hpp
badd +25 src/Renderer.hpp
badd +17 src/Renderer.cpp
badd +10 src/main.cpp
badd +1 src/Material.cpp
badd +6 src/DataTypes.hpp
badd +13 src/GamePad.hpp
badd +11 src/Timer.hpp
badd +47 src/Timer.cpp
badd +5 term://~/Desktop/Sandbox//2836:C:/Windows/system32/cmd.exe
badd +4 term://~/Desktop/Sandbox//15424:C:/Windows/system32/cmd.exe
badd +6 src/Algorithms.hpp
badd +0 term://~/Desktop/Sandbox//800:C:/Windows/system32/cmd.exe
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOFs
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
