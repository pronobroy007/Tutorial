# Install bandle.
    git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
# Install Base16 theam.
    git clone https://github.com/chriskempson/base16-shell.git ~/.config/base16-shell	


# Install developer tools.
    sudo apt install git build-essential g++ ruby ruby-dev npm -y

# For make color and folder icon in terminal
# https://www.addictivetips.com/ubuntu-linux-tips/make-linux-terminal-user-friendly-colorls/
    sudo gem install colorls

# Install c# language server.
    wget -q https://packages.microsoft.com/config/ubuntu/19.10/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
    sudo dpkg -i packages-microsoft-prod.deb
    sudo apt-get update
    sudo apt-get install apt-transport-https
    apt update
    sudo apt-get install dotnet-sdk-3.1

    sudo apt install apt-transport-https dirmngr gnupg ca-certificates
    sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
    echo "deb https://download.mono-project.com/repo/debian stable-buster main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list
    sudo apt update
    sudo apt install mono-devel

    # Install vscode and also install unity too extension on it.


distro=`cat /etc/os-release | grep '^NAME' | cut -d"\"" -f 2`
case "$distro" in
    "Linux Mint") 
        # For linux mint Install ccls, nvim.
        sudo apt install snapd
        sudo snap install ccls --classic
        sudo snap install nvim --beta --classic
        ;;

    "Kali GNU/Linux") 
        # For c++ .
        apt install ccls neovim -y
        ;;

    *) echo "hell" 
        ;;
esac

# For neovim config.
    mkdir ~/.config/nvim
    ln -s ~/.vimrc ~/.config/nvim/init.vim



# Install zsh, oh-my-zsh, powerlevel10k
    sudo apt install zsh -y
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
    git clone --depth=1 https://github.com/romkatv/powerlevel10k.git $ZSH_CUSTOM/themes/powerlevel10k
    # p10k configure        To configure p10k
    # Set ZSH_THEME="powerlevel10k/powerlevel10k" in ~/.zshrc.



# Install Nerd font............ 









