#ifndef COMMANDS_H
#define COMMANDS_H

enum Command {
        //DataBaseChecks
        checkAuthoriziatonData,
        checkRegistrationData,

        // Client`s requests to Server
        registrateUser,
        getRooms,

        // Account profile commands
        accountRegisration, // Create a new user
        accountdelete, // Delete user account & user data

        // Connection status
        checkConnection
};

#endif // COMMANDS_H
