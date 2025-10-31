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
            dialog.Text = "Biztosíthatlak, hogy gazdagok lesztek. Ha akarod, becsomagolom neked egy kendôbe és egy zsebkendôbe.";
			Link.l1 = "Maradj ott, mindjárt jövök!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Figyelj ide... Van valami érdekes a számodra...";
			Link.l1 = "Mirôl beszélsz?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "Egy italról! H-Hic... igyál velem!";
    			Link.l1 = "Ó, fogd be. Azt hittem, komolyan gondolod.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "Van valamim a számodra, elfogadható áron.";
    			Link.l1 = "És mi lehet az?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Ó, tûnj el. Erre nincs idôm.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "Ez egy nagyszerû térkép. Soha nem fogsz ilyet venni egyetlen boltban sem. Megmutatja, hol van elrejtve a kincs. Én magam nem tudok odajutni, de a térkép valódi, esküszöm.";
			Link.l1 = "Ez érdekes. Mennyit kérsz?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Ó, tûnj el. Erre nincs idôm.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
            dialog.Text = "Mindössze "+Pchar.GenQuest.TreasureMoney+" dublonokba kerül."; // Addon-2016 Jason
			Link.l1 = "Rendben. És csomagold be egy szép ruhadarabba.";
			if (PCharDublonsTotal() >= sti(Pchar.GenQuest.TreasureMoney)) // Addon-2016 Jason
			{
			   Link.l1.go = "map_treasure_buy";
			}
			else
			{
			   Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = "Az túl drága. Nincs rá szükségem.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Tessék. Most gazdag leszel!";
			Link.l1 = "Köszönjük!";
			Link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(sti(Pchar.GenQuest.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Igyunk egyet, rendben? Hic... Remek rumot szolgálnak fel itt!";
			Link.l1 = "Nincs idôm!";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "Eladtál nekem egy hamis térképet!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "Ki vagy te? Hic! Nem ismerlek és nem is érdekel!";
			Link.l1 = "Mindegy...";
			Link.l1.go = "exit";
			Link.l2 = "Te adtad el nekem ezt a hamisítványt! A szart is kiverem belôled...";
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
