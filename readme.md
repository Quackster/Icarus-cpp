## Outbreak Server

Icarus is a Habbo Hotel private server written in C++ designed for version *PRODUCTION-201512012203-525044429*.

There is **no Linux version available**, the only supported operating system is Windows.

## Install

*For Windows Server 2008 (or higher)*

**Required:**

- A Steam account that has Arma 3 purchased (Arma's server binaries)

**Installation steps**

1. Download the Windows SteamCMD found [here](https://steamcdn-a.akamaihd.net/client/installer/steamcmd.zip), this will allow us to download Arma 3 without using the default Steam client.

- Extract the file somewhere and open *steamcmd.exe*

- Once opened, type the commands below to login *(from [https://developer.valvesoftware.com/wiki/SteamCMD](https://developer.valvesoftware.com/wiki/SteamCMD))*
>
>```
 >   login <username>
>```
>
>Next enter your password.
>
>If Steam Guard is activated on the user account, check your e-mail for a Steam Guard access code and enter it. This is only required the first time you log in (as well as when you delete the files where SteamCMD stores the login information).
>
>You should see a message stating that you have successfully logged in with your account.

- Once logged in type the following ```force_install_dir c:/arma3``` where *c:/arma3* is your desired path to download and setup the Arma 3 server

- After that, to download Arma 3, type in ```app_update 107410 -update``` which will prepare and start to download Arma 3

- Once that is done, navigate to the folder where you downloaded Arma 3 and extract the @OutbreakServer folder from this repository inside of it. So it's in the same directory as arma3server.exe

