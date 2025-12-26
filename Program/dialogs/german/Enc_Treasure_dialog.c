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
	
	bool bPesosMap = Statistic_AddValue(PChar, "Treasure", 0) < 3;
	int iTreasureMapPesosCost = TreasureMapPesosCost();

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();			
		break;

        case "Map_NotBuy":
            dialog.Text = "Ich versichere Ihnen, Sie werden reich. Ich werde es für Sie in ein Tuch und in ein Taschentuch einwickeln, wenn Sie möchten.";
			Link.l1 = "Bleib da, ich bin gleich wieder da!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Hör zu... Ich habe etwas Interessantes für dich...";
			Link.l1 = "Wovon redest du?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (!CheckAttribute(NPChar, "TreasureMoney") || GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "Über ein Getränk! H-Hicks... trink mit mir!";
    			Link.l1 = "Ach, halt die Klappe. Ich dachte, du meinst es ernst.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "Ich habe etwas für dich zu einem vernünftigen Preis.";
    			Link.l1 = "Und was könnte das sein?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Oh, verschwinde. Ich habe keine Zeit für so etwas.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "Es ist eine großartige Karte. So etwas wirst du in keinem Laden kaufen. Sie zeigt, wo ein Schatz versteckt ist. Ich kann dort selbst nicht hingehen, aber die Karte ist echt, ich schwöre.";
			Link.l1 = "Das ist interessant, Wie viel willst du?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Oh, verschwinde. Ich habe keine Zeit für so etwas.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
			if(bPesosMap)
			{
				dialog.Text = "Es kostet nur "+FindRussianMoneyString(iTreasureMapPesosCost)+"."; // Addon-2016 Jason
				Link.l1 = "In Ordnung. Und wickle es in ein schönes Stück Stoff ein.";
				if (sti(pchar.money) >= iTreasureMapPesosCost) // Addon-2016 Jason
				{
				   Link.l1.go = "map_treasure_buy";
				}
				else
				{
				   Link.l1.go = "Map_NotBuy";
				}
			}
			else
			{
				dialog.Text = "Es kostet nur "+NPChar.TreasureMoney+" Dublonen."; // Addon-2016 Jason
				Link.l1 = "In Ordnung. Und wickle es in ein schönes Stück Stoff ein.";
				if (PCharDublonsTotal() >= sti(NPChar.TreasureMoney)) // Addon-2016 Jason
				{
				   Link.l1.go = "map_treasure_buy";
				}
				else
				{
				   Link.l1.go = "Map_NotBuy";
				}
			}
			Link.l2 = "Das ist zu teuer. Ich brauche es nicht.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Hier hast du es. Jetzt wirst du reich!";
			Link.l1 = "Danke!";
			Link.l1.go = "exit";
			if(bPesosMap) AddMoneyToCharacter(pchar, -iTreasureMapPesosCost);
			else RemoveDublonsFromPCharTotal(sti(NPChar.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Lass uns einen trinken, oder? Hic... Sie servieren hier einen tollen Rum!";
			Link.l1 = "Ich habe keine Zeit!";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "Du hast mir eine gefälschte Karte verkauft!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "Wer bist du? Hic! Ich kenne dich nicht und es ist mir egal!";
			Link.l1 = "Macht nichts...";
			Link.l1.go = "exit";
			Link.l2 = "Du hast mir diese Fälschung verkauft! Ich werde dir gründlich den Hintern versohlen...";
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
