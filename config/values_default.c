/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include <allegro/keyboard.h>
#define NUM_CONFIG_GROUPS 8
static struct ConfigGroup config_list[NUM_CONFIG_GROUPS] = {
    {"General", NULL, 0},
    {"Gameplay", NULL, 0},
    {"Radius", NULL, 0},
    {"Player1", NULL, 0},
    {"Player2", NULL, 0},
    {"Player3", NULL, 0},     {"Player4", NULL, 0},
    {"Highscore", NULL, 0} 
};

void configInitializeDefaults()
{
    int id, group;
    static int initialized = 0;
    /* Variavel static em funcoes mantem seu valor entre chamadas. */
    if (initialized != 0)
        return;
    initialized = 1;

    INIT_GROUP("General", 13);
    ADD_CONFIG("MaximumFPS", 30, TYPE_INT,
               "Negativo ou nulo para sem limite.");
    ADD_CONFIG("Fullscreen", 0, TYPE_BOOLEAN, NULL);
    ADD_CONFIG("ResolutionX", 1024, TYPE_INT, NULL);
    ADD_CONFIG("ResolutionY", 768, TYPE_INT, NULL);
    ADD_CONFIG("NumPlayers", 2, TYPE_INT, "Hardcoded maximum: 4");
    ADD_CONFIG("DebugMode", 0, TYPE_BOOLEAN, NULL);
    ADD_CONFIG("ButtonExit", KEY_ESC, TYPE_INT,
               "Aperte 2x seguidas para sair");
    ADD_CONFIGSTRING("GameOver", "Game Over! Thanks for playing!",
                     "Maximo de 254 caracteres");

    ADD_CONFIG("LimitObject", 150, TYPE_INT,
               "<0 da erro, necessita ser capaz de comportar os valores iniciais.");

    ADD_CONFIG("PersonInitialAmmount", 30, TYPE_INT, NULL);
    ADD_CONFIG("PersonCreatePeriod", 5, TYPE_FLOAT, NULL);
    ADD_CONFIG("PersonAverageSpeed", 10, TYPE_FLOAT, NULL);

    ADD_CONFIG("CoralInitialAmount", 12, TYPE_INT, NULL);
    CLOSE_GROUP();

    INIT_GROUP("Radius", 4);
    ADD_CONFIG("Person", 5, TYPE_FLOAT, NULL);
    ADD_CONFIG("Ship", 50, TYPE_FLOAT, NULL);
    ADD_CONFIG("Coral", 10, TYPE_FLOAT, NULL);
    ADD_CONFIG("Boat", 10, TYPE_FLOAT, NULL);
    CLOSE_GROUP();

    INIT_GROUP("Gameplay", 12);
    ADD_CONFIG("Difficulty", 3, TYPE_FLOAT,
               "]-Inf,3[ = Mais facil. ]3,+Inf[ = Mais dificil. (O valor em si influencia e nao apenas o intervalo)");
    ADD_CONFIG("TurnRate", PI / 2, TYPE_FLOAT, NULL);
    ADD_CONFIG("Acceleration", 50, TYPE_FLOAT, NULL);
    ADD_CONFIG("Friction", 0.5, TYPE_FLOAT,
               "Valores negativos geram resultados imprevisiveis.");
    ADD_CONFIG("TimeStuck", 5, TYPE_INT, NULL);
    ADD_CONFIG("InitialLives", 3, TYPE_INT, NULL);
    ADD_CONFIG("UnloadDistance", 120, TYPE_FLOAT, NULL);
    ADD_CONFIG("UnloadTime", 1, TYPE_FLOAT, NULL);
    ADD_CONFIG("BoatCapacity", 10, TYPE_INT, NULL);
    ADD_CONFIG("AnchorFrictionMultiplier", 10, TYPE_FLOAT, NULL);
    ADD_CONFIG("ExtraLifeScore", 500, TYPE_INT, NULL);
    ADD_CONFIG("MaxAnchorSpeed", 20, TYPE_FLOAT, NULL);
    CLOSE_GROUP();

    INIT_GROUP("Highscore", 10);
    ADD_CONFIG("Rank1Score", 9001, TYPE_INT, NULL);
    ADD_CONFIGSTRING("Rank1Name", "Brocoli", NULL);
    ADD_CONFIG("Rank2Score", 1337, TYPE_INT, NULL);
    ADD_CONFIGSTRING("Rank2Name", "Imano Ob", NULL);
    ADD_CONFIG("Rank3Score", 666, TYPE_INT, NULL);
    ADD_CONFIGSTRING("Rank3Name", "Tiozao", NULL);
    ADD_CONFIG("Rank4Score", 42, TYPE_INT, NULL);
    ADD_CONFIGSTRING("Rank4Name", "DarkSzero", NULL);
    ADD_CONFIG("Rank5Score", -0xCAFE, TYPE_INT, NULL);
    ADD_CONFIGSTRING("Rank5Name", "Haruki", NULL);
    CLOSE_GROUP();

    INIT_GROUP("Player1", 7);
    ADD_CONFIGSTRING("Name", "Player 1", NULL);
    ADD_CONFIG("Color", 0xFE0000, TYPE_HEXADECIMAL, NULL);
    ADD_CONFIG("ButtonAccel", KEY_W, TYPE_INT, NULL);
    ADD_CONFIG("ButtonBrake", KEY_S, TYPE_INT, NULL);
    ADD_CONFIG("ButtonTurnLeft", KEY_A, TYPE_INT, NULL);
    ADD_CONFIG("ButtonTurnRight", KEY_D, TYPE_INT, NULL);
    ADD_CONFIG("ButtonAnchor", KEY_Q, TYPE_INT, NULL);
    CLOSE_GROUP();

    INIT_GROUP("Player2", 7);
    ADD_CONFIGSTRING("Name", "Player 2", NULL);
    ADD_CONFIG("Color", 0x00FEFF, TYPE_HEXADECIMAL, NULL);
    ADD_CONFIG("ButtonAccel", KEY_UP, TYPE_INT, NULL);
    ADD_CONFIG("ButtonBrake", KEY_DOWN, TYPE_INT, NULL);
    ADD_CONFIG("ButtonTurnLeft", KEY_LEFT, TYPE_INT, NULL);
    ADD_CONFIG("ButtonTurnRight", KEY_RIGHT, TYPE_INT, NULL);
    ADD_CONFIG("ButtonAnchor", KEY_END, TYPE_INT, NULL);

    INIT_GROUP("Player3", 7);
    ADD_CONFIGSTRING("Name", "Player 3", NULL);
    ADD_CONFIG("Color", 0xFEFEFE, TYPE_HEXADECIMAL, NULL);
    ADD_CONFIG("ButtonAccel", KEY_8_PAD, TYPE_INT, NULL);
    ADD_CONFIG("ButtonBrake", KEY_2_PAD, TYPE_INT, NULL);
    ADD_CONFIG("ButtonTurnLeft", KEY_4_PAD, TYPE_INT, NULL);
    ADD_CONFIG("ButtonTurnRight", KEY_6_PAD, TYPE_INT, NULL);
    ADD_CONFIG("ButtonAnchor", KEY_0_PAD, TYPE_INT, NULL);

    INIT_GROUP("Player4", 7);
    ADD_CONFIGSTRING("Name", "Player 4", NULL);
    ADD_CONFIG("Color", 0x00FE00, TYPE_HEXADECIMAL, NULL);
    ADD_CONFIG("ButtonAccel", KEY_I, TYPE_INT, NULL);
    ADD_CONFIG("ButtonBrake", KEY_K, TYPE_INT, NULL);
    ADD_CONFIG("ButtonTurnLeft", KEY_J, TYPE_INT, NULL);
    ADD_CONFIG("ButtonTurnRight", KEY_L, TYPE_INT, NULL);
    ADD_CONFIG("ButtonAnchor", KEY_U, TYPE_INT, NULL);
    CLOSE_GROUP();
}
