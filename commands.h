#ifndef COMMANDS_H
#define COMMANDS_H

enum Command {
        // Account commands
        createNewAccount, // Create a new user
        logInToAccount, // Autotrization in the app
        logOutOfAccount, // Log out of user account
        deleteAccount, // Delete user account & user data

        // Load menu data commands
        loadUserFriends, // Load the user's friends list from the serrver
        loadOtherUsersForSearch, // Load a list of users matching the entered query during search
        loadUserRoomsFromServer, // Load a list of rooms available to this user from the server
        loadUserAccauntData, // Load user data from the server, such as: name, photo, etc
        loadUserSettins, // Load user settings from the server

        // Rooms & messages commands
        loadClickedRoom, // Load clicked room from server
        createNewRoom, // Create a new room on the server
        deleteRoom, // Delete room from server
        gotMessageFromServer, // Load message from server
        gotMessageFromClient, // <----- TODO: delete this
        deleteMessage, // Delete the message on the server (for everyone)
        editMessage, // Edit the message
        loadCurrentRoomParticipants, // Load information about the participants of the current room

        // Change user data commands
        changeUsername, // Change username
        changeUserPassword, // Change user password
        changeUserEmail, // Change user email
        changeUserFirstName, // Change user first name
        changeUserLastName, // Change user last name
        changeUserProfilePicture, // Change user profile picture
        changeUserBio, // Change change user information

        // Change room data commands
        changeRoomName, // Change room name
        changeDescriptionRoomName, // Change description of room

        // Board commands
        loadRoomboard // Load Roomboard from server
        // TODO
};

#endif // COMMANDS_H
