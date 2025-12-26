//#include "DIALOGS\convoy_traider.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("Ahhh, kahretsin! Kim olduğunu biliyorum! Gemisini sana emanet edecek kadar aptal ancak tam bir budala olabilir. Elveda!","Ah, seni tanıyorum! Beni koruman için tutmak mı diyorsun? Ben aptal değilim...");
				link.l1 = RandPhraseSimple("Heh, ne yazık!","İnsanlar bugünlerde gerçekten de çok kolay korkuyor!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ben "+GetFullName(NPChar)+", bir tüccar. Duyduğuma göre iş arıyormuşsun?";
				link.l1 = "Öyle bir şey. Ve duyduğuma göre, siz de varış noktanıza sizi ve geminizi götürecek bir kaptan arıyormuşsunuz?";
				link.l1.go = "prepare_convoy_quest_2";
			}
		break;
		
		case "prepare_convoy_quest_2":
			dialog.text = "Aynen öyle. Üstelik, bana eşlik edecek en doğru kişinin sen olduğuna inanıyorum. Ne dersin?";
			link.l1 = "Pekâlâ, bana bir teklif yap, belki bir anlaşmaya varırız.";
			link.l1.go = "prepare_convoy_quest_3";
		break;
		
		case "prepare_convoy_quest_3":
			LookShipConvoy();
			GenerateConvoyQuest(npchar);
			dialog.text = "Beni   eşlik ederek   götürmenizi   istiyorum "+XI_ConvertString("Colony"+pchar.quest.destination+"Gen")+",   şu adreste bulunuyor: "+XI_ConvertString(GetIslandByCityName(pchar.quest.destination)+"Dat")+", içinde "+FindRussianDaysString(sti(pchar.ConvoyQuest.iDay))+", ve bunun için sana ödeme yapacağım "+FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney))+". Yani, kararın ne?";
			link.l1 = "Ben varım.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "Bence bu ilginç bir teklif değil.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_refused");
		break;
		
		case "convoy_agreeded":
			chrDisableReloadToLocation = false;
		    pchar.convoy_quest = pchar.quest.destination;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_agreeded");
		break;
		
		case "complete_convoy_quest":
			dialog.text = "Oh! Teşekkür ederim. Senin koruman altında, kendimi hiç olmadığım kadar güvende hissettim. İşte hak ettiğin ödülün.";
			Link.l1 = "Rica ederim.";
			link.l1.go = "exit";
			//слухи
			AddSimpleRumour(LinkRandPhrase("A merchant captain by the name of " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted when one needs an escort.", 
				"Negociant named " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("He","She") +" protected his ship in the best way possible while escorting him to " + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ".", 
				"I heard that you keep the word given to trader captains that ask you for an escort. A trader named " + GetFullName(npchar) + " speaks well about you."), sti(npchar.nation), 40, 1);
			pchar.quest.generate_convoy_quest_progress = "completed";
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			AddDialogExitQuest("convoy_refused");
		break;
	}
} 

// boal 03.05.04 квест сопроводить торговца -->
void GenerateConvoyQuest(ref npchar)
{
	int iTradeMoney, iNation;

	DeleteAttribute(NPChar, "Ship");
    int iShipCoef = SetShipConvoyQuest_Traider(NPChar);

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.ConvoyQuest.City), GetArealByCityName(pchar.quest.destination));
	if (sti(daysQty) > 14) daysQty = 14;
	pchar.ConvoyQuest.iDay = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (makeint(daysQty * 400 * stf(pchar.GenQuest.Convoy.Shipmod))) + (iShipCoef * 700);

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(pchar.quest.destination);
	//Log_Info(pchar.ConvoyQuest.City);

	SetTimerCondition("generate_convoy_quest_timer", 0, 0, sti(pchar.ConvoyQuest.iDay), false);

	pchar.quest.generate_convoy_quest_progress = "begin";

	pchar.quest.generate_convoy_quest_failed.win_condition.l1 = "NPC_Death";
	pchar.quest.generate_convoy_quest_failed.win_condition.l1.character = "QuestTrader";
	pchar.quest.generate_convoy_quest_failed.win_condition = "generate_convoy_quest_failed";
}

void LookShipConvoy()
{
	switch(sti(RealShips[sti(Pchar.Ship.Type)].Class))
	{
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1.0;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3.0;
		break;
		case 6:
			pchar.GenQuest.GetPassenger.Shipmod = 4.5;
		break;
		case 7:
			pchar.GenQuest.GetPassenger.Shipmod = 5.5;
		break;
	}
}

int SetShipConvoyQuest_Traider(ref _chr)
{
	int iRank = sti(pchar.rank);
	int iShip, iShipCoef;
	
	if(iRank < 5)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_LUGGER;
				iShipCoef = 3;
			break;
			case 2:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
		}
	}
	if(iRank >= 5 && iRank < 11)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
			case 2:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
		}
	}
	if(iRank >= 11 && iRank < 18)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
			case 1:
				iShip = SHIP_FLEUT;
				iShipCoef = 6;
			break;
			case 2:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 3:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
		}
	}
	if(iRank >= 18 && iRank < 25)
	{
		switch (rand(4))
		{
			case 0:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 1:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
			case 2:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 3:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 4:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
		}
	}
	if(iRank > 25)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 1:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 2:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
			case 3:
				iShip = SHIP_NAVIO;
				iShipCoef = 12;
			break;
		}
	}
	
	_chr.Ship.Type = GenerateShipExt(iShip, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, "trade");
    Fantom_SetBalls(_chr, "trade");
	Fantom_SetGoods(_chr, "trade");
	
	return iShipCoef;
	
}
