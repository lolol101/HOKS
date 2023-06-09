#ifndef COMMANDS_H
#define COMMANDS_H

enum Command {
    //DataBaseChecks
    checkAuthoriziatonData,
    checkRegistrationData,

    // Client`s appeals to Server
    registrateUser,
    appendMessage,
    getFile,
    appendRoom,
    getRooms,
    getAllUsers,
    loadMsgs,
    userEnterApp,
    uploadFile,

    //Server`s appeals to Client
    otherUserMessage,
    roomCreated,

    // Account profile commands
    accountRegisration, // Create a new user
    accountdelete, // Delete user account & user data

    // Connection status
    checkConnection
};

#endif // COMMANDS_H
