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
            dialog.Text = "Sana garanti veriyorum, zengin olacaksın. İstersen onu bir beze ya da bir mendile sarıp sana veririm.";
			Link.l1 = "Orada kal, hemen döneceğim!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Dinle bak... Sana ilginç bir şeyim var...";
			Link.l1 = "Ne diyorsun?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (!CheckAttribute(NPChar, "TreasureMoney") || GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "Bir içki! H-hıç... benimle bir içki iç!";
    			Link.l1 = "Ah, sus artık. Ciddi olduğunu sanmıştım.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "Sana uygun bir fiyata verebileceğim bir şeyim var.";
    			Link.l1 = "Ve o ne olabilir?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Defol git. Bununla uğraşacak vaktim yok.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "Bu harita çok değerli. Hiçbir dükkânda böyle bir şey bulamazsın. Bir hazinenin saklandığı yeri gösteriyor. Ben kendim ulaşamıyorum ama harita gerçek, yemin ederim.";
			Link.l1 = "Bu ilginç. Ne kadar istiyorsun?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Defol git. Bununla uğraşacak vaktim yok.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
			if(bPesosMap)
			{
				dialog.Text = "Sadece   "+FindRussianMoneyString(iTreasureMapPesosCost)+"."; // Addon-2016 Jason
				Link.l1 = "Pekâlâ. Ve güzel bir kumaşa sar.";
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
				dialog.Text = "Sadece   "+NPChar.TreasureMoney+" dublon."; // Addon-2016 Jason
				Link.l1 = "Pekala. Ve güzel bir kumaşa sar.";
				if (PCharDublonsTotal() >= sti(NPChar.TreasureMoney)) // Addon-2016 Jason
				{
				   Link.l1.go = "map_treasure_buy";
				}
				else
				{
				   Link.l1.go = "Map_NotBuy";
				}
			}
			Link.l2 = "Bu çok pahalı. İhtiyacım yok.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Al bakalım. Artık zengin olacaksın!";
			Link.l1 = "Teşekkürler!";
			Link.l1.go = "exit";
			if(bPesosMap) AddMoneyToCharacter(pchar, -iTreasureMapPesosCost);
			else RemoveDublonsFromPCharTotal(sti(NPChar.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Bir içki içelim, ne dersin? Hık... Burada harika rom servis ediyorlar!";
			Link.l1 = "Vaktim yok!";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "Bana sahte bir harita sattın!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "Sen kimsin? Hık! Seni tanımıyorum ve umurumda da değilsin!";
			Link.l1 = "Boşver...";
			Link.l1.go = "exit";
			Link.l2 = "Bana bu sahte şeyi sattın! Seni gebertirim...";
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
