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
            dialog.Text = "Zapewniam cię, że się wzbogacisz. Opakuję to dla ciebie w płótno i w chustkę, jeśli chcesz.";
			Link.l1 = "Zostań tu, zaraz wracam!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Słuchaj... Mam dla ciebie coś interesującego...";
			Link.l1 = "O czym ty mówisz?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "O drinku! H-Hic... napij się ze mną!";
    			Link.l1 = "Och, zamknij się. Myślałem, że mówisz poważnie.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "Mam coś dla ciebie w rozsądnej cenie.";
    			Link.l1 = "A co to może być?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Och, spadaj. Nie mam na to czasu.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "To wspaniała mapa. Nigdy nie kupisz czegoś takiego w żadnym sklepie. Pokazuje, gdzie ukryty jest skarb. Sam nie mogę tam dotrzeć, ale mapa jest prawdziwa, przysięgam.";
			Link.l1 = "To interesujące, ile chcesz?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "O, znikaj. Nie mam na to czasu.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
            dialog.Text = "To kosztuje tylko "+Pchar.GenQuest.TreasureMoney+" dublony."; // Addon-2016 Jason
			Link.l1 = "W porządku. I zawij to w ładny kawałek materiału.";
			if (PCharDublonsTotal() >= sti(Pchar.GenQuest.TreasureMoney)) // Addon-2016 Jason
			{
			   Link.l1.go = "map_treasure_buy";
			}
			else
			{
			   Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = "To za drogo. Nie potrzebuję tego.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Proszę bardzo. Teraz będziesz bogaty!";
			Link.l1 = "Dzięki!";
			Link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(sti(Pchar.GenQuest.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Chodźmy się napić, co ty na to? Hic... Podają tu świetny rum!";
			Link.l1 = "Nie mam czasu!";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "Sprzedałeś mi fałszywą mapę!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "Kim jesteś? Hic! Nie znam cię i nie obchodzi mnie to!";
			Link.l1 = "Nieważne...";
			Link.l1.go = "exit";
			Link.l2 = "Sprzedałeś mi tę falsyfikację! Zbiję cię na kwaśne jabłko...";
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
