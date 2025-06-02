//navy
#include "DIALOGS\%language%\Common_Duel.c" 
// boal 29.05.04 даем карту клада
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	aref   item;
	bool   ok;
	
	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	ProcessDuelDialog(NPChar, link, Diag); //navy

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();			
		break;

        case "Map_NotBuy":
            dialog.Text = "Te aseguro, te harás rico. Lo envolveré para ti en un pañuelo, si te gusta.";
			Link.l1 = "¡Quédate ahí, volveré enseguida!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Escucha aquí... Tengo algo interesante para ti...";
			Link.l1 = "¿De qué estás hablando?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "¡Sobre una bebida! H-Hic... ¡bebe conmigo!";
    			Link.l1 = "Oh, cállate. Pensé que hablabas en serio.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "Te tengo algo a un precio razonable.";
    			Link.l1 = "¿Y qué podría ser?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Oh, piérdete. No tengo tiempo para esto.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "Es un gran mapa. Nunca comprarás algo así en ninguna tienda. Muestra dónde está escondido un tesoro. No puedo llegar allí yo mismo, pero el mapa es auténtico, lo juro.";
			Link.l1 = "Eso es interesante, ¿Cuánto quieres?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Oh, lárgate. No tengo tiempo para esto.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
            dialog.Text = "Solo cuesta "+Pchar.GenQuest.TreasureMoney+" doblones."; // Addon-2016 Jason
			Link.l1 = "Está bien. Y envuélvelo en un bonito pedazo de tela.";
			if (PCharDublonsTotal() >= sti(Pchar.GenQuest.TreasureMoney)) // Addon-2016 Jason
			{
			   Link.l1.go = "map_treasure_buy";
			}
			else
			{
			   Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = "Eso es demasiado caro. No lo necesito.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Aquí tienes. ¡Ahora vas a hacerte rico!";
			Link.l1 = "¡Gracias!";
			Link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(sti(Pchar.GenQuest.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Tomaremos una jarra, ¿verdad? Hic... ¡Aquí sirven un ron estupendo!";
			Link.l1 = "¡No tengo tiempo!";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "¡Me vendiste un mapa falso!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "¿Quién eres tú? ¡Hic! ¡No te conozco y no me importa!";
			Link.l1 = "No importa...";
			Link.l1.go = "exit";
			Link.l2 = "¡Me vendiste esta falsificación! Te voy a dar una paliza...";
			Link.l2.go = "outraged"; //navy -- дуэли!!!
			Diag.TempNode = "let_s_duel";
			npchar.LifeDay = 1; // чтоб не слетел на выходе
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "tavern_keeper":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}
