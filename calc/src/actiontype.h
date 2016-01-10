#ifndef ACTIONTYPE_H
#define ACTIONTYPE_H
/**
 * @brief The ActionType enum is used in action tokens to tell which action it represents
 */
enum class ActionType{
    BATTLE = 1,
    MOVE = 2,
    PUSH = 3,
    NONE = 0,
};

#endif // ACTIONTYPE_H
