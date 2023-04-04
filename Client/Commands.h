#ifndef COMMANDS_H
#define COMMANDS_H

enum Command {
        //DataBaseChecks
        checkLogin,
        checkPassword,

        // Account profile commands
        accountRegisration, // Create a new user
        accountdelete, // Delete user account & user data

        // Connection status
        checkConnection
};

#endif // COMMANDS_H
