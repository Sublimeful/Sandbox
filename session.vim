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
edit src/main.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
wincmd =
argglobal
balt src/Timer.cpp
setlocal fdm=marker
setlocal fde=0
setlocal fmr=<--,-->
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 246 - ((0 * winheight(0) + 8) / 17)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 246
normal! 022|
wincmd w
argglobal
if bufexists("term://~/Desktop/Sandbox//10856:C:/Windows/system32/cmd.exe") | buffer term://~/Desktop/Sandbox//10856:C:/Windows/system32/cmd.exe | else | edit term://~/Desktop/Sandbox//10856:C:/Windows/system32/cmd.exe | endif
if &buftype ==# 'terminal'
  silent file term://~/Desktop/Sandbox//10856:C:/Windows/system32/cmd.exe
endif
balt src/main.cpp
setlocal fdm=marker
setlocal fde=0
setlocal fmr=<--,-->
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 28 - ((19 * winheight(0) + 10) / 20)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 28
normal! 0
wincmd w
2wincmd w
wincmd =
tabnext 1
badd +20 src/Timer.h
badd +48 src/Timer.cpp
badd +153 ~/AppData/Local/nvim/init.vim
badd +6 Makefile
badd +1710 term://~/Desktop/Sandbox//1604:C:/Windows/system32/cmd.exe
badd +249 src/main.cpp
badd +1 compile_commands.json
badd +0 term://~/Desktop/Sandbox//10856:C:/Windows/system32/cmd.exe
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOFs
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
