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
					dialog.text = "Stój. Żeglujesz pod banderą "+NationNameGenitive(sti(pchar.nation))+", szczurze pokładowy. Nie mam ochoty z tobą rozmawiać i nie chcę żadnych problemów... Spływaj!";
					link.l1 = "A ty nazywasz siebie kapitanem...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < 5)//боевые генераторные квесты 2015
				{
					dialog.text = "Ha! Jesteś tu w samą porę, kapitanie... Mam dla ciebie propozycję biznesową. Czy masz dla mnie kilka godzin?";
					link.l1 = "Nie. Spieszę się, kumplu. Może następnym razem.";
					link.l1.go = "exit_quest";
					link.l2 = "Aye, może i tak. Zależy, co mi zaoferujesz. A może pójdziemy do tawerny, by o tym porozmawiać?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Witaj i dobrze spotkać! Miło widzieć innego zamożnego kapitana!";
				link.l1 = "Cieszę się, że cię widzę, panie! Nazywam się "+GetFullName(pchar)+"Masz chwilę, by porozmawiać?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Czy mam się powtórzyć? Nie chcę być podejrzewany o przyjaźń z "+NationNameAblative(sti(pchar.nation))+"Zjeżdżaj, albo wezwę straż!";
					link.l1 = "Dobrze, dobrze, uspokój się. Odchodzę.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Czego chcesz?";
					link.l1 = "Niczego.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" do usług, dobry panie! Czego chciałbyś się dowiedzieć?","Miło z tobą rozmawiać, kapitanie!","Cóż, przypuszczam, że mam wolną chwilę na rozmowę...","Niestety, muszę iść. Do zobaczenia!","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Czy masz coś ciekawego do opowiedzenia?","Masz coś ciekawego do opowiedzenia?","Masz mi coś ciekawego do opowiedzenia?","Pewnie. Powodzenia!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "Nie, kapitanie, na ulicach i w tawernie jest wiele oczu i uszu, a nam ich nie potrzeba, uwierz mi. Ta propozycja dotyczy... wrogiego przejęcia interesów, że tak powiem. Porozmawiajmy na moim statku.";
				link.l1 = "Dobra, spróbuję... Jak się nazywa twój statek i jaka jest jej nazwa?";
				link.l1.go = "march_1";
				link.l2 = "Ha! Brzmi podejrzanie dla mnie. Myślę, że nie. Żegnaj, panie!";
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
				dialog.text = "Mój statek to "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype),"Imię")))+" '"+pchar.GenQuest.MarchCap.shipname+"Jest teraz w porcie. Nie spóźnij się, kapitanie, wyjeżdżam za sześć godzin!";
				link.l1 = "Rozumiem, postaram się być na czas. Do zobaczenia!";
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
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jako obywatel tego miasta proszę cię, abyś schował swój miecz.","Słuchaj, jako obywatel tego miasta proszę cię, byś schował swój oręż.");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz.","Jak powiadasz...");
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
