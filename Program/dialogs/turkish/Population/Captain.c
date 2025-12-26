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
					dialog.text = "Dur! Hangi bayrak altında yelken açıyorsun? "+NationNameGenitive(sti(pchar.nation))+", çaylak. Seninle konuşmak istemiyorum ve başıma dert açmanı da istemem... Defol git!";
					link.l1 = "Ve sen kendine kaptan diyorsun...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < COMPANION_MAX)//боевые генераторные квесты 2015
				{
					dialog.text = "Ha! Tam zamanında geldin, kaptan... Sana bir iş teklifim var. Bana birkaç saatin var mı?";
					link.l1 = "Hayır, istemiyorum. Acelem var dostum. Belki bir dahaki sefere.";
					link.l1.go = "exit_quest";
					link.l2 = "Olabilir, belki. Ne teklif edeceğine bağlı. Ne dersin, bunu konuşmak için meyhaneye geçelim mi?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Selam ve hoş geldiniz! Başarılı bir kaptanı daha görmek güzel!";
				link.l1 = "Sizi görmek ne güzel, efendim! Benim adım "+GetFullName(pchar)+". Konuşmak için bir dakikanız var mı?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Tekrar mı edeyim? Birinin dostu olduğumdan şüphelenilmek istemem "+NationNameAblative(sti(pchar.nation))+"! Defol git yoksa muhafızları çağırırım!";
					link.l1 = "Pekala, pekala, sakin ol. Gidiyorum.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Ne istiyorsun?";
					link.l1 = "Hiçbir şey.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" hizmetinizdeyim, efendim! Ne öğrenmek istersiniz?","Sizinle konuşmak güzel, Kaptan!","Pekâlâ, sanırım konuşmak için bir dakikam var...","Maalesef gitmem gerekiyor. Görüşürüz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Bana anlatacak ilginç bir şeyin var mı?","Bana anlatacak ilginç bir şeyin var mı?","Bana anlatacak ilginç bir şeyin var mı?","Tabii. İyi şanslar!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "Hayır kaptan, sokaklarda ve meyhanede çok fazla göz ve kulak var, onlara ihtiyacımız yok, bana güvenin. Bu teklif tamamen... düşmanca bir iş devralma meselesi, tabiri caizse. Gelin, gemimde konuşalım.";
				link.l1 = "Pekâlâ, anlat bakalım... Gemin ne, adı ne?";
				link.l1.go = "march_1";
				link.l2 = "Ha! Bana pek güvenilir gelmedi. Sanmıyorum. Hoşça kalın, bayım!";
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
				dialog.text = "Gemi m   "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype),"Name")))+" '"+pchar.GenQuest.MarchCap.shipname+" . Şu anda limanda. Geç kalma kaptan, altı saat sonra ayrılmış olacağım!";
				link.l1 = "Anladım, zamanında gelmeye çalışacağım. Görüşürüz!";
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
			dialog.text = NPCharSexPhrase(NPChar,"Dinle, bu kasabanın bir vatandaşı olarak senden kılıcını kınına koymanı istiyorum.","Dinle, bu kasabanın bir vatandaşı olarak senden kılıcını indirmeni istiyorum.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Dediğiniz gibi olsun.","Dediğiniz gibi...");
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
