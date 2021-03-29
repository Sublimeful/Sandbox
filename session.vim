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
badd +20 Makefile
badd +19 src/main.cpp
badd +1 src/Sprite.cpp
badd +1 test.sh
badd +1 include/Sprite.hpp
badd +1 ~/AppData/Local/nvim/init.vim
badd +1 ~/.config/nvim/coc-settings.json
badd +1 include/Tetrimino.h
badd +1 src/App.cpp
badd +1 include/App.h
badd +1 include/Renderer.h
badd +1 init.vim
badd +2 a.exe
badd +5 session.vim
badd +2 zlib1.dll
badd +1 ~/.config/nvim/init.vim
badd +1 src/Game.cpp
badd +1 src/Renderer.cpp
badd +1 src/Tetrimino.cpp
badd +1 ~/.config/nvim/plugged/nerdtree//autoload//nerdtree.vim
badd +1 [Plugins]
badd +1 ;
badd +16 compile_commands.json
badd +1 ~/AppData/Local//nvim/init.vim
badd +1 include/Game.h
badd +1 ~/.config/nvim/plugged//nerdtree//lib//nerdtree/opener.vim
argglobal
%argdel
edit src/main.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
setlocal fdm=marker
setlocal fde=0
setlocal fmr=<--,-->
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 22 - ((13 * winheight(0) + 18) / 37)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 22
normal! 0
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0&& getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 winminheight=1 winminwidth=1 shortmess=filnxtToOF
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
