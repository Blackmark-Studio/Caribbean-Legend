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
            dialog.Text = "Je vous assure, vous deviendrez riche. Je l'empaquetterai pour vous dans un tissu et dans un mouchoir, si vous voulez.";
			Link.l1 = "Reste là, je reviens tout de suite !";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Écoute ici... J'ai quelque chose d'intéressant pour toi...";
			Link.l1 = "De quoi parlez-vous ?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (!CheckAttribute(NPChar, "TreasureMoney") || GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "À propos d'un verre! H-Hic... bois avec moi!";
    			Link.l1 = "Oh, tais-toi. Je pensais que tu étais sérieux.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "J'ai quelque chose pour toi à un prix raisonnable.";
    			Link.l1 = "Et qu'est-ce que ce pourrait être?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Oh, va te faire voir. Je n'ai pas de temps à perdre avec ça.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "C'est une excellente carte. Vous n'achèterez jamais quelque chose de semblable dans aucun magasin. Elle indique où un trésor est caché. Je ne peux pas y aller moi-même, mais la carte est authentique, je le jure.";
			Link.l1 = "C'est intéressant, combien voulez-vous ?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Oh, va-t'en. Je n'ai pas de temps pour ça.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
			if(bPesosMap)
			{
				dialog.Text = "Cela coûte seulement "+FindRussianMoneyString(iTreasureMapPesosCost)+"."; // Addon-2016 Jason
				Link.l1 = "D'accord. Et enveloppez-le dans un joli morceau de tissu.";
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
				dialog.Text = "Cela coûte seulement "+NPChar.TreasureMoney+" doublons."; // Addon-2016 Jason
				Link.l1 = "D'accord. Et enveloppez-le dans un joli morceau de tissu.";
				if (PCharDublonsTotal() >= sti(NPChar.TreasureMoney)) // Addon-2016 Jason
				{
				   Link.l1.go = "map_treasure_buy";
				}
				else
				{
				   Link.l1.go = "Map_NotBuy";
				}
			}
			Link.l2 = "C'est trop cher. Je n'en ai pas besoin.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Voici. Maintenant, tu vas devenir riche!";
			Link.l1 = "Merci!";
			Link.l1.go = "exit";
			if(bPesosMap) AddMoneyToCharacter(pchar, -iTreasureMapPesosCost);
			else RemoveDublonsFromPCharTotal(sti(NPChar.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Allons prendre un verre, n'est-ce pas? Hic... Ils servent un excellent rhum ici!";
			Link.l1 = "Je n'ai pas de temps !";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "Vous m'avez vendu une fausse carte !";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "Qui êtes-vous? Hic! Je ne vous connais pas et je m'en fiche!";
			Link.l1 = "Peu importe...";
			Link.l1.go = "exit";
			Link.l2 = "Tu m'as vendu cette contrefaçon ! Je vais te foutre une raclée...";
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
