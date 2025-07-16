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
            dialog.Text = "Ti assicuro, diventerai ricco. Lo avvolgerò per te in un panno e in un fazzoletto, se vuoi.";
			Link.l1 = "Resta lì, torno subito!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Ascolta qui... Ho qualcosa di interessante per te...";
			Link.l1 = "Di cosa stai parlando?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "Su un bicchiere! H-Hic... bevi con me!";
    			Link.l1 = "Oh, smettila. Pensavo fossi serio.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "Ho qualcosa per te a un prezzo ragionevole.";
    			Link.l1 = "E cosa potrebbe essere?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Oh, vattene. Non ho tempo per questo.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "È una mappa grandiosa. Non ne comprerai mai una del genere in nessun negozio. Mostra dove è nascosto un tesoro. Non posso arrivarci da solo, ma la mappa è autentica, lo giuro.";
			Link.l1 = "È interessante, quanto vuoi?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Oh, vattene. Non ho tempo per questo.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
            dialog.Text = "Costa solo "+Pchar.GenQuest.TreasureMoney+" dobloni."; // Addon-2016 Jason
			Link.l1 = "Bene. E avvolgilo in un bel pezzo di stoffa.";
			if (PCharDublonsTotal() >= sti(Pchar.GenQuest.TreasureMoney)) // Addon-2016 Jason
			{
			   Link.l1.go = "map_treasure_buy";
			}
			else
			{
			   Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = "È troppo costoso. Non ne ho bisogno.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Eccolo qui. Ora diventerai ricco!";
			Link.l1 = "Grazie!";
			Link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(sti(Pchar.GenQuest.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Prendiamo qualcosa da bere, che ne dici? Hic... Servono un ottimo rum qui!";
			Link.l1 = "Non ho tempo!";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "Mi hai venduto una mappa falsa!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "Chi sei tu? Hic! Non ti conosco e non me ne importa!";
			Link.l1 = "Mai mente...";
			Link.l1.go = "exit";
			Link.l2 = "Mi hai venduto questo falso! Ti farò a pezzi...";
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
