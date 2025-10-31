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
					dialog.text = "Avast. A "+NationNameGenitive(sti(pchar.nation))+", swabbie zászlaja alatt hajózol. Nem kívánok veled beszélgetni, és nem akarok problémákat... Tûnj el!";
					link.l1 = "És még te nevezed magad kapitánynak...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < COMPANION_MAX)//боевые генераторные квесты 2015
				{
					dialog.text = "Ha! Épp idôben jöttél, kapitány... Van egy üzleti ajánlatom a számodra. Van néhány órája a számomra?";
					link.l1 = "Nincs. Sietek, pajtás. Talán majd legközelebb.";
					link.l1.go = "exit_quest";
					link.l2 = "Igen, lehet. Attól függ, mit ajánl nekem. Mi lenne, ha a tavernába mennénk, hogy megbeszéljük?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Üdvözletem és üdvözletem! Örülök, hogy látok egy jólétben élô kapitánytársat!";
				link.l1 = "Örülök, hogy látom, uram! A nevem "+GetFullName(pchar)+". Van egy perce, hogy beszéljünk?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Megismételjem magam? Nem akarom, hogy a "+NationNameAblative(sti(pchar.nation))+"barátjaként gyanúsítsanak ! Tûnj el, vagy hívom az ôrséget!";
					link.l1 = "Rendben, rendben, nyugodjon meg. Elmegyek.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Mit szeretne?";
					link.l1 = "Semmi.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" szolgálatára, jó uram! Mit szeretne tudni?", 
				"Örülök, hogy beszélhetek önnel, kapitány!", 
				"Nos, azt hiszem, van egy szabad percem, hogy beszélgessünk...",
                "Sajnos, mennem kell. Viszlát!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Van valami érdekes mondanivalója?", 
				"Van valami érdekes mondanivalód?",
                "Van valami érdekes mondanivalód?", 
				"Persze. Sok szerencsét!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "Nem, kapitány, rengeteg szem és fül van az utcákon és a kocsmában, és nincs szükségünk rájuk, hidd el. Ez a javaslat egy... ellenséges üzleti átvételrôl szól, hogy úgy mondjam. Beszéljük meg a hajómon.";
				link.l1 = "Rendben, harapok... Mi a hajója és a neve?";
				link.l1.go = "march_1";
				link.l2 = "Ha! Nekem gyanúsan hangzik. Szerintem nem. Viszontlátásra, uram!";
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
				dialog.text = "A hajóm "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype), "Név")))+" '"+pchar.GenQuest.MarchCap.shipname+". Most éppen a kikötôben van. Ne késs el kapitány, hat óra múlva indulok!";
				link.l1 = "Értem, megpróbálok idôben érkezni. Viszlát!";
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
			dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, mint a város polgára arra kérem, hogy tegye hüvelybe a pengéjét.", "Figyelj, mint e város polgára arra kérlek, hogy tedd fel a pengédet.");
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod.", "Ahogy mondod...");
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
