//Jason общий диалог праздношатающихся по улицам капитанов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
			if (npchar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Avast. Navigi sotto la bandiera di "+NationNameGenitive(sti(pchar.nation))+", mozzo. Non ho alcun desiderio di parlare con te e non voglio problemi... Levati dai piedi!";
					link.l1 = "E ti chiami capitano...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < 5)//боевые генераторные квесты 2015
				{
					dialog.text = "Ah! Sei arrivato proprio in tempo, capitano... Ho una proposta d'affari per te. Hai qualche ora per me?";
					link.l1 = "Non lo faccio. Sono di fretta, compagno. Forse la prossima volta.";
					link.l1.go = "exit_quest";
					link.l2 = "Sì, potrei. Dipende da cosa mi offri. Che ne dici di andare alla taverna per discutere?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Salute e ben ritrovato! È bello vedere un altro capitano prospero!";
				link.l1 = "Contento di vederti, signore! Il mio nome è "+GetFullName(pchar)+". Hai un minuto per parlare?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Dovrei ripetermi? Non voglio essere sospettato di essere un amico di "+NationNameAblative(sti(pchar.nation))+"! Sparisci o chiamerò le guardie!";
					link.l1 = "Bene, bene, calmati. Me ne sto andando.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Cosa vuoi?";
					link.l1 = "Niente.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" al vostro servizio, buon signore! Cosa vorreste sapere?","Contento di parlare con te, capitano!","Beh, suppongo di avere un minuto libero per parlare...","Sfortunatamente, devo andare. Arrivederci!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hai qualcosa di interessante da raccontarmi?","Hai qualcosa di interessante da raccontarmi?","Hai qualcosa di interessante da raccontarmi?","Certo. Buona fortuna!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "No, capitano ci sono molti occhi e orecchie per le strade e nella taverna e non ne abbiamo bisogno, credimi. Questa proposta riguarda un... diciamo, un'acquisizione ostile di un'attività commerciale. Parliamo sulla mia nave.";
				link.l1 = "Bene, morderò... Qual è la tua nave e come si chiama?";
				link.l1.go = "march_1";
				link.l2 = "Ah! Sembra sospetto a me. Non credo. Addio, signore!";
				link.l2.go = "exit_quest";
			break;
			
			case "march_1":
				//генерируем и запоминаем параметры в пчар, т.к. через нпчар не хочет нормально работать :(
				pchar.GenQuest.MarchCap.Startisland = Islands[GetCharacterCurrentIsland(PChar)].id;
				pchar.GenQuest.MarchCap.Parts = GetCompanionQuantity(pchar)+1;
				pchar.GenQuest.MarchCap.shiptype = SelectCaptainShipType();
				pchar.GenQuest.MarchCap.shipname = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.MarchCap.nation = sti(npchar.Nation);
				pchar.GenQuest.MarchCap.model = npchar.model;
				pchar.GenQuest.MarchCap.rank = sti(npchar.rank);
				pchar.GenQuest.MarchCap.name = npchar.name;
				pchar.GenQuest.MarchCap.lastname = npchar.lastname;
				pchar.GenQuest.MarchCap.BaseNation = npchar.nation;
				pchar.GenQuest.MarchCap.Nation = hrand(NON_PIRATES);
				pchar.GenQuest.MarchCap.basecity = npchar.city;
				dialog.text = "La mia nave è "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype),"Name")))+" '"+pchar.GenQuest.MarchCap.shipname+". È in porto ora. Non fare tardi capitano, partirò tra sei ore!";
				link.l1 = "Capisco, cercherò di essere puntuale. Ci vediamo!";
				link.l1.go = "march_2";
			break;
			
			case "march_2":
			DialogExit();
				LAi_SetActorType(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 30.0);
				npchar.lifeday = 0;
				pchar.quest.MarchCapOver.win_condition.l1 = "Timer";
				pchar.quest.MarchCapOver.win_condition.l1.date.hour  = sti(GetTime() + 6);
				pchar.quest.MarchCapOver.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.MarchCapOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.MarchCapOver.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.MarchCapOver.function = "MarchCap_Over";
				pchar.quest.MarchCap_Create.win_condition.l1 = "location";
				pchar.quest.MarchCap_Create.win_condition.l1.location = pchar.GenQuest.MarchCap.Startisland;
				pchar.quest.MarchCap_Create.function = "MarchCap_Create";
				log_Testinfo(pchar.GenQuest.MarchCap.Startisland);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ascolta, come cittadino di questa città ti chiedo di infilare la tua spada nel fodero.","Ascolta, come cittadino di questa città ti chiedo di mettere via la tua spada.");
			link.l1 = LinkRandPhrase("Bene.","Come desideri.","Come dici tu...");
			link.l1.go = "exit";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectCaptainShipType()
{
	int iClassFlag = FLAG_SHIP_CLASS_6;
	if (sti(pchar.rank) >= 19) iClassFlag = FLAG_SHIP_CLASS_2;	
	if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 19) iClassFlag = FLAG_SHIP_CLASS_3;	
	if (sti(pchar.rank) >= 8 && sti(pchar.rank) < 12) iClassFlag = FLAG_SHIP_CLASS_4;
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 8) iClassFlag = FLAG_SHIP_CLASS_5;
	if (sti(pchar.rank) < 5) iClassFlag = FLAG_SHIP_CLASS_6;
	
	return GetRandomShipType(iClassFlag, FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}
