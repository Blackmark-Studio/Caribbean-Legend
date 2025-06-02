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
					dialog.text = "Avast. Vous naviguez sous le drapeau de "+NationNameGenitive(sti(pchar.nation))+", moussaillon. Je n'ai aucune envie de parler avec toi et je ne veux pas d'ennuis... Déguerpis !";
					link.l1 = "Et tu te prétends capitaine...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < 5)//боевые генераторные квесты 2015
				{
					dialog.text = "Ha ! Vous arrivez juste à temps, capitaine... J'ai une proposition d'affaire pour vous. Avez-vous quelques heures à me consacrer ?";
					link.l1 = "Je ne peux pas. Je suis pressé, compagnon. Peut-être la prochaine fois.";
					link.l1.go = "exit_quest";
					link.l2 = "Oui, peut-être. Cela dépend de ce que tu m'offres. Que dirais-tu de nous rendre à la taverne pour en discuter ?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Salut et bien rencontré ! Cela fait plaisir de voir un autre capitaine prospère !";
				link.l1 = "Ravi de vous voir, monsieur ! Je m'appelle "+GetFullName(pchar)+" . Avez-vous une minute pour parler ?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Dois-je me répéter ? Je ne veux pas être soupçonné d'être un ami de "+NationNameAblative(sti(pchar.nation))+"Fiche le camp ou j'appelle la garde !";
					link.l1 = "D'accord, d'accord, calme-toi. Je m'en vais.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Que veux-tu ?";
					link.l1 = "Rien.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" à votre service, bon monsieur ! Que souhaitez-vous savoir ?","Ravi de parler avec vous, capitaine !","Eh bien, je suppose que j'ai une minute libre pour discuter...","Malheureusement, je dois y aller. À bientôt !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("As-tu quelque chose d'intéressant à me raconter ?","Avez-vous quelque chose d'intéressant à me raconter ?","As-tu quelque chose d'intéressant à me raconter ?","Bien sûr. Bonne chance !",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "Non, capitaine, il y a beaucoup d'yeux et d'oreilles dans les rues et dans la taverne et nous n'en avons pas besoin, croyez-moi. Cette proposition concerne une... prise de contrôle hostile d'affaires, pour ainsi dire. Parlons-en sur mon navire.";
				link.l1 = "Bien, je vais mordre à l'hameçon... Quel est ton navire et comment s'appelle-t-il ?";
				link.l1.go = "march_1";
				link.l2 = "Ha ! Cela me semble suspect. Je ne pense pas. Adieu, monsieur !";
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
				dialog.text = "Mon navire est "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype),"Nom")))+" ' "+pchar.GenQuest.MarchCap.shipname+"Elle est au port en ce moment. Ne soyez pas en retard capitaine, je partirai dans six heures !";
				link.l1 = "Je vois, j'essaierai d'être à l'heure. À bientôt !";
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
			dialog.text = NPCharSexPhrase(NPChar,"Ecoutez, en tant que citoyen de cette ville, je vous demande de rengainer votre lame.","Ecoutez, en tant que citoyen de cette ville, je vous demande de rengainer votre acier.");
			link.l1 = LinkRandPhrase("Très bien.","Comme vous le souhaitez.","Comme tu dis...");
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
