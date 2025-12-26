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
					dialog.text = "이봐. 너는 어떤 깃발 아래에서 항해하나 "+NationNameGenitive(sti(pchar.nation))+", 꼬마야. 너랑 얘기하고 싶지도 않고, 문제 일으키고 싶지도 않으니... 꺼져!";
					link.l1 = "이래서야 네가 선장이라고 할 수 있겠어...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < COMPANION_MAX)//боевые генераторные квесты 2015
				{
					dialog.text = "하! 딱 맞춰 오셨군요, 선장님... 당신께 제안할 일이 있습니다. 저에게 몇 시간 내주실 수 있습니까?";
					link.l1 = "아니. 난 지금 바빠, 이봐. 다음에 보자.";
					link.l1.go = "exit_quest";
					link.l2 = "그래, 그럴 수도 있지. 네가 뭘 제안하느냐에 따라 다르겠군. \n술집에 가서 얘기나 좀 해볼까?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "안녕하시오! 또 한 명의 번영하는 선장을 만나 기쁘구려!";
				link.l1 = "뵙게 되어 반갑습니다, 나리! 제 이름은 "+GetFullName(pchar)+". 잠시 이야기할 시간 있소?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "내가 다시 말해야겠나? 나는 친구로 오해받고 싶지 않으니 "+NationNameAblative(sti(pchar.nation))+"! 썩 꺼지지 않으면 경비병을 부를 거야!";
					link.l1 = "알았어, 알았어, 진정해. 나 간다.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "뭘 원하지?";
					link.l1 = "아무것도 아니다.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" 항상 대기 중입니다, 나리! 무엇을 알고 싶으신가요?","대화하게 되어 기쁩니다, 선장님!","글쎄, 잠깐 이야기할 시간은 있겠군...","유감이지만, 나는 가야 해. 또 보자!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나에게 흥미로운 이야기가 있나?","나한테 해줄 만한 흥미로운 이야기가 있나?","나한테 해줄 만한 흥미로운 이야기가 있나?","물론이지. 행운을 빌어!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "아니요, 선장님, 거리와 선술집에는 눈과 귀가 많으니 그들은 필요 없습니다, 믿으십시오. 이 제안은 말하자면... 적대적 사업 인수에 관한 것입니다. 제 배에서 이야기합시다.";
				link.l1 = "좋아, 궁금하군... 네 배는 어떤 배고, 이름은 뭐지?";
				link.l1.go = "march_1";
				link.l2 = "하! 수상하게 들리는데. 난 사양하겠소. 안녕히 가시오, 나리!";
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
				dialog.text = "내 배는 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype),"Name")))+" '"+pchar.GenQuest.MarchCap.shipname+". 그녀는 지금 항구에 있어요. 늦지 마십시오, 선장님, 여섯 시간 후면 저는 떠날 겁니다!";
				link.l1 = "알겠어, 제시간에 맞추도록 할게. 또 보자!";
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
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 이 마을 시민으로서 부탁하네, 칼을 집어넣어 주게.","이봐, 이 마을 시민으로서 부탁하는데, 무기를 거둬 줘.");
			link.l1 = LinkRandPhrase("좋아.","원하시는 대로 하겠습니다.","말씀대로 하겠습니다...");
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
