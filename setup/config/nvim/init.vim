" __   _(_)_ __ ___  _ __ ___ 
" \ \ / / | '_ ` _ \| '__/ __|
"  \ V /| | | | | | | | | (__ 
" (_)_/ |_|_| |_| |_|_|  \___|
set path+=**
set t_Co=256

syntax on
set number             "turn absolute line numbers on

" open new split panes to right and below
set splitright splitbelow

"For insert mode.
let &t_SI = "\e[5 q"
let &t_SR = "\<esc>[5 q"
let &t_EI = "\e[2 q"

set nowrap              "If line gose off the screen it will keep going.
set noswapfile          "Create no .swp files.
set tabstop=4           "tab space = 4 space.
set shiftwidth=4        "use >> = 4 space.
set softtabstop=4
set expandtab
filetype off            " required

"For Folding / hiding text.
autocmd BufWinLeave *.* mkview 
autocmd BufWinEnter *.* silent loadview  

call plug#begin('~/.vim/plugged')
    "File manager.
        Plug 'scrooloose/nerdtree'
        Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
        Plug 'junegunn/fzf.vim'
    "For syntex checker.
        Plug 'scrooloose/syntastic'
        Plug 'octol/vim-cpp-enhanced-highlight'
    "For Theam.
        Plug 'morhetz/gruvbox'
        Plug 'vim-airline/vim-airline'
    "For code complition.
        Plug 'neoclide/coc.nvim', {'branch': 'release'}
        Plug 'omnisharp/omnisharp-vim'
        Plug 'mattn/emmet-vim'
    "For Comment. key = gc in visual mode
        Plug 'tpope/vim-commentary'
call plug#end()

"==========================================================================================
" Function to rename a function name across the entire project
function! RenameFunction() abort
  " Ask for current function name
  let l:old_name = input('Current function name: ')
  if empty(l:old_name)
    echo "No function name provided"
    return
  endif

  " Ask for new function name
  let l:new_name = input('New function name: ')
  if empty(l:new_name)
    echo "No new name provided"
    return
  endif

  " Search for all occurrences (whole word only)
  execute 'vimgrep /\<' . l:old_name . '\>/ **/*'
  
  " Open quickfix window to preview changes
  copen
  
  " Confirm before making changes
  let l:choice = confirm("Replace all occurrences?", "&Yes\n&No", 1)
  if l:choice != 1
    echo "Renaming canceled"
    return
  endif

  " Perform the replacement
  execute 'cdo %s/\<' . l:old_name . '\>/' . l:new_name . '/g | update'
  
  echo "Renamed " . l:old_name . " to " . l:new_name . " across project"
endfunction

" Map <Leader>rN to call RenameFunction
nmap <Leader>rN :call RenameFunction()<CR>

" Create command to call the function
command! -nargs=0 RenameFunction call RenameFunction()
"==========================================================================================

" For key map :
"---------------
    "Map the leader key to a comma.
     let mapleader = ','

    "Function Key :
    "---------------
        map<F12> :source ~/.config/nvim/init.vim<cr>
        autocmd FileType cs          map<F8> :OmniSharpReloadProject<cr>
        "Spell checker 
        map<F6> :set spell!<cr>



    "For Visual Mode :
    "-----------------
        "Copy to clipboard.
        vmap<C-c> "+y


    "For Normal Mode :
    "-----------------
        "Paste last thing yenked, not deleted
        nmap<Leader>p "0p
        "Goto Next / Previous vim buffer
        nmap<Leader>bn :bnext<cr>
        nmap<Leader>bp :bprevious<cr>
        "Vim Macros 
        "-----------
            "zo => open folding line.
            "zO => opens all folds at the cursor.
            "zc => close folding line.
            "zM => closes all open folds.
            "zd => delete folding line.
            "zE => deletes all folds.

            "<Leader>=\ ^M=<CR> ^[=<ESC>
            "Code Folding.
            nmap cf Vj%zf  
            "zo = open folding and zc = close Folding
            "Code Comment. gc

        "For vim tab
        "------------
            nnoremap tn :tabnew<space>
            nnoremap tl :tabnext<cr>
            nnoremap th :tabprev<cr>
            nnoremap tj :tabfirst<cr>
            nnoremap tk :tablast<cr>
            "Ex : tm 0 	-->  this will move current tab in first position.
            nnoremap tm :tabm<space>

        "For select all
        "--------------
            nmap<C-a> ggVG

        "For vim split :
        "---------------
            "CTrl navigation. shift + h/l/k/l
            "nnoremap <C-h> <C-w>h
            nmap <C-h> <C-W>h
            nnoremap <C-j> <C-w>j
            nnoremap <C-k> <C-w>k
            nnoremap <C-l> <C-w>l

            "Resize split
            noremap <silent> <C-Left> :vertical resize -2<cr>
            noremap <silent> <C-Right> :vertical resize +2<cr>
            noremap <silent> <C-UP> :res +2<cr>
            noremap <silent> <C-Down> :res -2<cr>

            noremap Zz <c-w>_ \| <c-w>\|
            noremap Zo <c-w>=

            "For vim terminal <Esc> bact to normal mode.
            "tnoremap <C-t> <C-\><C-n> 
            tnoremap <leader>t <C-\><C-n> 
            nnoremap Tt :10sp\|:terminal<CR>
            nnoremap TT :30vs\|:terminal<CR>




        "For Emmet :
        "-----------
            "AutoComplite <C-Space>, 
            "Enable just for html/css
            let g:user_emmet_install_global = 0
            autocmd FileType html,css,php EmmetInstall

            "To remap the default <C-Y> leader to ctrl+space
            let g:user_emmet_leader_key='<C-Space>'


        "For OmniSharp
        "-------------
            autocmd FileType cs          nnoremap <Leader>fu :OmniSharpFindUsages<cr>
            autocmd FileType cs          nnoremap <Leader>rn :OmniSharpRename<cr>
            autocmd FileType cs          nnoremap gd :OmniSharpGotoDefinition<cr>
            autocmd FileType cs          nnoremap <s-k> :OmniSharpSignatureHelp<cr>
            autocmd FileType cs          nnoremap <Leader>l :OmniSharpNavigateDown<cr>
            autocmd FileType cs          nnoremap <Leader>h :OmniSharpNavigateUp<cr>
            
        "For nerdtree
        "-------------
            nnoremap nt :NERDTree<cr>

        "For FZF 
        "--------
            nmap <silent> <C-p> :Files<cr> 
            nmap <silent> <Leader><C-b> :Buffers<cr> 



"For cpp code highlighting :
"---------------------------
    "colorscheme dracula
    colorscheme gruvbox

"For nvim status line :
"---------------------
    let g:airline_powerline_fonts=1
    let g:airline#extensions#tabline#enabled = 1

" For FZF :
"----------
    "let $FZF_DEFAULT_COMMAND = 'find . ! -name "*.meta" ! -name "*.cs"'
    "let $FZF_DEFAULT_COMMAND = 'find . ! -name "*.meta"'
    "let $FZF_DEFAULT_COMMAND = 'find $DIR -not -path '*/\.*' -ype f \( ! -iname ".*" \) ! -name "*.meta"'
    let $FZF_DEFAULT_COMMAND = 'find $DIR -not -path "*/\.*" -type f \( ! -iname "*.meta" \) -type f \( ! -iname "*.asset" \)' 



"For nerdtree
"------------
    "put this in your .vimrc
    set wildignore+=*.pyc,*.o,*.obj,*.svn,*.swp,*.class,*.hg,*.DS_Store,*.min.*,*.meta
    "Nerdtree config for wildignore
    let NERDTreeRespectWildIgnore=1

"For Syntastic :
"---------------
    set statusline+=%#warningmsg#
    set statusline+=%{SyntasticStatuslineFlag()}
	set statusline+=%*
    let g:syntastic_quiet_messages={'level':'warnings'}
    let g:syntastic_always_populate_loc_list = 1
    let g:syntastic_auto_loc_list = 1
    let g:syntastic_check_on_wq = 0
    let g:syntastic_check_on_open = 0
	let g:syntastic_python_checkers=['flake8']

    let g:syntastic_cpp_checkers = ['clang_check', 'clang_tidy', 'gcc']
    let g:syntastic_cpp_checkers = ['gcc']
    let g:syntastic_cpp_compiler = "g++"
    let g:syntastic_cpp_compiler_options = "-std=c++17"

    "It will only work if Syntastic and OmniSharp installed.
    let g:syntastic_cs_checkers = ['code_checker']
    "Ignore some of the messages in syntastic.
    let g:syntastic_quiet_messages = { 'regex': 'Unnecessary using directive.' }


"For C# omnisharp :
"------------------
    " Use the stdio OmniSharp-roslyn server
    "let g:OmniSharp_server_stdio = 1
    "let g:OmniSharp_server_use_mono = 1
    let g:OmniSharp_server_use_net6 = 1

    " Set the type lookup function to use the preview window instead of echoing it
    let g:OmniSharp_typeLookupInPreview = 1

    " Timeout in seconds to wait for a response from the server
    let g:OmniSharp_timeout = 5

    " Don't autoselect first omnicomplete option, show options even if there is only
    " one (so the preview documentation is accessible). Remove 'preview' if you
    " don't want to see any documentation whatsoever.
    set completeopt=longest,menuone,preview

    " Fetch full documentation during omnicomplete requests.
    " By default, only Type/Method signatures are fetched. Full documentation can
    " still be fetched when you need it with the :OmniSharpDocumentation command.
    let g:omnicomplete_fetch_full_documentation = 1 

    " Set desired preview window height for viewing documentation.
    " You might also want to look at the echodoc plugin.
    set previewheight=5

    " Update semantic highlighting after all text changes
    let g:OmniSharp_highlight_types = 0
    " Update semantic highlighting on BufEnter and InsertLeave
    "let g:OmniSharp_highlight_types = 3
    
    ":OmniSharpFindUsages results instead of the quickfix list
    let g:OmniSharp_selector_findusages = 'fzf'
    let g:OmniSharp_selector_ui = 'fzf'    " Use fzf


"For Coc.Nvim :
"--------------
" Some servers have issues with backup files, see #649.
set nobackup
set nowritebackup

" Having longer updatetime (default is 4000 ms = 4 s) leads to noticeable
" delays and poor user experience.
set updatetime=300

" Always show the signcolumn, otherwise it would shift the text each time
" diagnostics appear/become resolved.
set signcolumn=yes

" Use tab for trigger completion with characters ahead and navigate.
" NOTE: Use command ':verbose imap <tab>' to make sure tab is not mapped by
" other plugin before putting this into your config.
inoremap <silent><expr> <TAB>
      \ coc#pum#visible() ? coc#pum#next(1):
      \ CheckBackspace() ? "\<Tab>" :
      \ coc#refresh()
inoremap <expr><S-TAB> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"

" Make <CR> to accept selected completion item or notify coc.nvim to format
" <C-g>u breaks current undo, please make your own choice.
inoremap <silent><expr> <CR> coc#pum#visible() ? coc#pum#confirm()
                              \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"

function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

" Use <c-space> to trigger completion.
if has('nvim')
  inoremap <silent><expr> <c-space> coc#refresh()
else
  inoremap <silent><expr> <c-@> coc#refresh()
endif

" Use `[g` and `]g` to navigate diagnostics
" Use `:CocDiagnostics` to get all diagnostics of current buffer in location list.
nmap <silent> [g <Plug>(coc-diagnostic-prev)
nmap <silent> ]g <Plug>(coc-diagnostic-next)

" GoTo code navigation.
nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)

" Use K to show documentation in preview window.
nnoremap <silent> K :call ShowDocumentation()<CR>

function! ShowDocumentation()
  if CocAction('hasProvider', 'hover')
    call CocActionAsync('doHover')
  else
    call feedkeys('K', 'in')
  endif
endfunction

" Highlight the symbol and its references when holding the cursor.
autocmd CursorHold * silent call CocActionAsync('highlight')

" Symbol renaming.
nmap <leader>rn <Plug>(coc-rename)

" Formatting selected code.
xmap <leader>f  <Plug>(coc-format-selected)
nmap <leader>f  <Plug>(coc-format-selected)

augroup mygroup
  autocmd!
  " Setup formatexpr specified filetype(s).
  autocmd FileType typescript,json setl formatexpr=CocAction('formatSelected')
  " Update signature help on jump placeholder.
  autocmd User CocJumpPlaceholder call CocActionAsync('showSignatureHelp')
augroup end

" Applying codeAction to the selected region.
" Example: `<leader>aap` for current paragraph
xmap <leader>a  <Plug>(coc-codeaction-selected)
nmap <leader>a  <Plug>(coc-codeaction-selected)

" Remap keys for applying codeAction to the current buffer.
nmap <leader>ac  <Plug>(coc-codeaction)
" Apply AutoFix to problem on the current line.
nmap <leader>qf  <Plug>(coc-fix-current)

" Run the Code Lens action on the current line.
nmap <leader>cl  <Plug>(coc-codelens-action)

" Map function and class text objects
" NOTE: Requires 'textDocument.documentSymbol' support from the language server.
xmap if <Plug>(coc-funcobj-i)
omap if <Plug>(coc-funcobj-i)
xmap af <Plug>(coc-funcobj-a)
omap af <Plug>(coc-funcobj-a)
xmap ic <Plug>(coc-classobj-i)
omap ic <Plug>(coc-classobj-i)
xmap ac <Plug>(coc-classobj-a)
omap ac <Plug>(coc-classobj-a)

" Remap <C-f> and <C-b> for scroll float windows/popups.
if has('nvim-0.4.0') || has('patch-8.2.0750')
  nnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
  nnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
  inoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(1)\<cr>" : "\<Right>"
  inoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(0)\<cr>" : "\<Left>"
  vnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
  vnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
endif

" Use CTRL-S for selections ranges.
" Requires 'textDocument/selectionRange' support of language server.
nmap <silent> <C-s> <Plug>(coc-range-select)
xmap <silent> <C-s> <Plug>(coc-range-select)

" Add `:Format` command to format current buffer.
command! -nargs=0 Format :call CocActionAsync('format')

" Add `:Fold` command to fold current buffer.
command! -nargs=? Fold :call     CocAction('fold', <f-args>)

" Add `:OR` command for organize imports of the current buffer.
command! -nargs=0 OR   :call     CocActionAsync('runCommand', 'editor.action.organizeImport')

" Add (Neo)Vim's native statusline support.
" NOTE: Please see `:h coc-status` for integrations with external plugins that
" provide custom statusline: lightline.vim, vim-airline.
set statusline^=%{coc#status()}%{get(b:,'coc_current_function','')}

" Mappings for CoCList
" Show all diagnostics.
nnoremap <silent><nowait> <space>a  :<C-u>CocList diagnostics<cr>
" Manage extensions.
nnoremap <silent><nowait> <space>e  :<C-u>CocList extensions<cr>
" Show commands.
nnoremap <silent><nowait> <space>c  :<C-u>CocList commands<cr>
" Find symbol of current document.
nnoremap <silent><nowait> <space>o  :<C-u>CocList outline<cr>
" Search workspace symbols.
nnoremap <silent><nowait> <space>s  :<C-u>CocList -I symbols<cr>
" Do default action for next item.
nnoremap <silent><nowait> <space>j  :<C-u>CocNext<CR>
" Do default action for previous item.
nnoremap <silent><nowait> <space>k  :<C-u>CocPrev<CR>
" Resume latest coc list.
nnoremap <silent><nowait> <space>p  :<C-u>CocListResume<CR>
