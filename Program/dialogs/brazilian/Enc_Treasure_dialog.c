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
            dialog.Text = "Eu garanto que você vai ficar rico. Posso embrulhar pra você num pano ou num lenço, se preferir.";
			Link.l1 = "Fique aí, já volto!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Escuta aqui... Tenho algo interessante pra você...";
			Link.l1 = "Do que você está falando?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (!CheckAttribute(NPChar, "TreasureMoney") || GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "Sobre uma bebida! H-hic... toma uma comigo!";
    			Link.l1 = "Ah, cala a boca. Achei que você estava falando sério.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "Tenho algo para você por um preço justo.";
    			Link.l1 = "E o que seria isso?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Ah, vai embora. Não tenho tempo pra isso.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "É um mapa valioso. Você nunca vai encontrar nada igual em nenhuma loja. Ele mostra onde um tesouro está escondido. Eu mesmo não consigo chegar lá, mas o mapa é verdadeiro, eu juro.";
			Link.l1 = "Interessante. Quanto você quer?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Ah, vai embora. Não tenho tempo pra isso.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
			if(bPesosMap)
			{
				dialog.Text = "Custa apenas "+FindRussianMoneyString(iTreasureMapPesosCost)+"."; // Addon-2016 Jason
				Link.l1 = "Certo. E embrulhe em um pano bonito.";
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
				dialog.Text = "Custa apenas "+NPChar.TreasureMoney+" dobrões."; // Addon-2016 Jason
				Link.l1 = "Certo. E embrulhe em um pano bonito.";
				if (PCharDublonsTotal() >= sti(NPChar.TreasureMoney)) // Addon-2016 Jason
				{
				   Link.l1.go = "map_treasure_buy";
				}
				else
				{
				   Link.l1.go = "Map_NotBuy";
				}
			}
			Link.l2 = "Está caro demais. Não preciso disso.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Aqui está. Agora você vai ficar rico!";
			Link.l1 = "Obrigado!";
			Link.l1.go = "exit";
			if(bPesosMap) AddMoneyToCharacter(pchar, -iTreasureMapPesosCost);
			else RemoveDublonsFromPCharTotal(sti(NPChar.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Vamos tomar um drink, que tal? Hic... Aqui servem um rum excelente!";
			Link.l1 = "Não tenho tempo!";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "Você me vendeu um mapa falso!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "Quem é você? Hic! Não te conheço e não tô nem aí!";
			Link.l1 = "Deixa pra lá...";
			Link.l1.go = "exit";
			Link.l2 = "Você me vendeu essa falsificação! Vou acabar com você...";
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
