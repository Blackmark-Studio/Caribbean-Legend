//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("흠. 그대는 ... 깃발 아래에서 항해하고 있군. "+NationNameGenitive(sti(pchar.nation))+", 이봐. 대체 우리 마을에 뭐 하러 온 거야? 썩 꺼져!","나는 ~의 친구로 의심받고 싶지 않아 "+NationNameAblative(sti(pchar.nation))+"꺼져, 아니면 경비병한테 신고할 거야!","도망칠 마지막 기회야. 그렇지 않으면 모든 책임은 네게 있어.","경고했지. 이제 네 건방짐에 대한 대가를 치르게 될 거다, 이 자식아!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("그렇게 애국자인가, 응!","좋아, 좋아, 진정해. 나 간다.","시끄럽게 굴지 마라. 나는 간다.","뭐라고?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("저것 좀 봐! 그런데 우리 경비병들은 어떻게 너 같은 잡놈이 거리를 돌아다니게 그냥 두는 거지? 말도 안 돼...","꺼져, 너랑 말도 섞기 싫어! 교수형 감이군...","도망칠 마지막 기회야. 그렇지 않으면 네 잘못이니 후회하지 마라.","경고했었다. 이제 네 건방짐에 대한 대가를 치르게 될 거다, 이 자식아!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("이봐 이봐! 나리, 나 좀 존중해 줘!","너 자신을 좀 봐, 성인님...","진정해...","뭐라고?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "안녕하시오, "+GetAddress_Form(NPChar)+". 훌륭한 배의 선장이라는 걸 알겠소. 부탁할 일이 있소. 받아들여도 되고 거절해도 되오.";
					link.l1 = "듣고 있소, "+GetAddress_FormToNPC(NPChar)+". 무슨 뜻이오?";
					link.l1.go = "passenger";
					link.l2 = "실례합니다, "+GetAddress_FormToNPC(NPChar)+", 하지만 나는 급하오.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "안녕하시오, "+GetAddress_Form(NPChar)+". 훌륭한 배의 선장이시군요. 부탁이 하나 있습니다. 들어주셔도 되고, 거절하셔도 됩니다.";
					link.l1 = "듣고 있네, "+GetAddress_FormToNPC(NPChar)+". 무슨 뜻이오?";
					link.l1.go = "passenger";
					link.l2 = "실례합니다, "+GetAddress_FormToNPC(NPChar)+", 하지만 나는 급하오.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "아하, 우리 작은 마을에 신사분이 오시다니 반갑군요! 분명 유럽에서 막 도착하신 게 틀림없겠지요. 들어보시오, 신사 대 신사로서 부탁드릴 일이 있소. 부디 제 뜻을 잘 이해해 주시길 바라오.";
					link.l1 = "좋은 하루입니다, 나리. 말씀하십시오.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "좋은 하루입니다, "+GetAddress_Form(NPChar)+"! 우리 마을 거리에서 신사를 만나게 되어 반갑습니다! 잠시 시간 좀 내주실 수 있겠습니까?";
					link.l1 = "물론입니다, 나리. 듣고 있습니다.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "좋은 하루입니다, 선장님! 문제를 해결할 수 있을 것 같은 분을 만나 뵙게 되어 기쁩니다.";
					link.l1 = "문제에 따라 다르지. 나는 주로 폭력으로 문제를 해결하는 데 특화되어 있거든. 그게 자네가 원하는 건가, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("안녕하세요, "+GetAddress_Form(NPChar)+". 나에게 원하는 게 있소?","무슨 일이십니까, 나리?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". 시간을 많이 뺏지 않겠소, 그냥 한 가지만 묻고 싶어서...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("그대네 식민지에 대한 정보가 필요하오.","정보가 필요해.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("도시 전체가 긴장하고 있어 - 왕실 감찰관인 돈 페르난도 데 알라미다가 도착했거든. 있잖아, 나도 여기서 별걸 다 봤지만, 이번 일은... 사람을 바꾸는 건 슬픔이 아니라, 그 슬픔을 어떻게 견디느냐더군. 그의 아버지가 돌아가신 뒤로 완전히 달라졌다고들 해. 이제 군도 전체를 뒤져도 그보다 더 청렴하고... 무자비한 왕실의 하수인은 없을 거야.","'홀리 머시'를 좀 봐! 왕께서 특별한 설계로 직접 건조를 명하셨다더군. 그리고 봐, 흠집 하나 없어. 마치 성모 마리아께서 직접 지켜주시는 것 같지. 하지만 소문도 들었어... 어쩌면 성모가 아닐 수도 있다더군.","자네, 돈 페르난도를 죽이려고 몇 번이나 시도한 줄 아나? 지난 1년 동안만 해도 공해상에서 열두 번이나 습격을 당했지! 그래도 저렇게 충성스럽고 잘 훈련된 선원들과 주님의 가호 아래라면, 열세 번째도 무사히 넘길 걸세!"),LinkRandPhrase("들었어? 돈 페르난도 데 알라미다가 우리 도시에 도착했대. 지금 어딘가 거리에서 돌아다니고 있다던데. 직접 한 번 보고 싶다...","복잡한 사람이오, 이 돈 페르난도는. 어떤 이들은 그가 조국을 더러운 것들로부터 정화하는 구세주라 말하지. 다른 이들은 그의 아버지가 죽은 뒤로 뭔가 그 안에서 부서졌다고 수군대며, 곧 우리 모두가 눈물을 흘리게 될 거라 하오. 하지만 내 말 명심하시오: 그를 두려워하지 마시오. 그를 그렇게 만든 자들을 두려워해야 하오.","참 잘생긴 남자야, 이 돈 페르난도! 그런데 이상한 거 알아? 마치 아무도 안 보이는 것처럼 행동해. 오직 의무와 봉사뿐이야. 예전에 어떤 아가씨가 있었다고 들었는데... 어느 신부를 만난 뒤로는 세속의 즐거움을 완전히 끊었다더라. 마치 서약이라도 한 것처럼 말이야."),RandPhraseSimple(RandPhraseSimple("젠장할 검사 놈! 저 자가 있는 동안엔 도시가 마치 죽은 것 같아. 장사도, 재미도 없어. 심지어 숨 쉬는 것조차 조용히 해야 할 판이야. 그리고 제일 무서운 게 뭔지 알아? 모든 항구가 다 똑같다는 거야. 마치 기계처럼. 국왕 폐하께서 우리 모두를 괴롭히려고 일부러 이런 고문을 만든 게 아닐까 싶다니까!","돈 페르난도께서 고아원을 또 방문하셨소. 그는 아낌없이 기부하고, 몇 시간씩 기도하시오. 저주받은 횡령범들에게 본보기가 되어야 할 훌륭한 분이오!"),RandPhraseSimple("하! '성자' 페르난도가 또다시 모든 사창가를 닫아버렸네. 뭐, 괜찮아, 곧 떠날 테니 다시 열릴 거야.","그 감... 감찰관이 도착했지, 그거야! 돈 페르난도 데 알메이다, 아니면, 이름이 뭐더라, 알메이다! 얼마나 대단한지 총독조차도 그 사람 앞에선 살금살금 걷는다더군. 사람들 말로는 그가 네 눈을 들여다보면 네 모든 죄를 단번에 꿰뚫어본다지. 무섭지 않아?")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("뭐라고? 또야? 나는 너한테 쓸 시간이 없다. 다른 사람을 찾아가 보거라. 거리에 평민들이 많이 돌아다니지 않느냐. 그리고 나는 가봐야 하오, 오늘 밤 총독 관저에서 연회가 있어서 옷차림을 준비해야 하니...\n","아니, 이젠 정말 짜증나잖아! 아직도 모르겠어? 아니면 머리가 둔한 거야?","나리, 이제 보니 그대는 그냥 바보가 아니라 촌뜨기에 무례한 자 같군. 경고하오, 나를 내버려 두지 않으면 반드시 후회하게 될 것이오.","그만해라. 버릇없는 놈, 내가 가르쳐주마!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("알겠소. 안녕히 가시오.","그래, 그래, 내가 뭘 물어보려 했는지 깜빡했네...","나를 오해하셨군...","뭐라고?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("계속해.","뭘 원하지?","질문 있나? 좋아, 선원, 듣고 있지.");
			link.l1 = LinkRandPhrase("당신네 마을의 최신 소문 좀 들려주지 않겠소?","최근에 여기서 무슨 흥미로운 일이 있었나?","카리브에서 소식이 있습니까, 나리?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = ""+GetSexPhrase("Sir","Madam")+", 식민지로 가야 해"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+", 가능한 한 빨리, 진행 중이오 "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", 위해 "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+". 당신 배는 여기 떠다니는 대부분의 작은 배들에 비해 튼튼하고 빠르게 보이네요. 당신에게 돈을 지불할 수 있습니다 "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". 뭐라고 하겠소?"; // belamour gen
			}
			else
			{
				dialog.text = "안녕하세요, "+GetSexPhrase("나리","부인")+"! 나는 가야 해 "+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"! 그건 "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", 그런데 말이야. 그래, 그래, 나도 알아 - 그 놈들이 우리가 거기 나타나기만을 기다리고 있다는 거. 하지만 거기서 정말 급하고 중요한 만남이 있어! 나는 인색한 사람이 아니야 - 돈 주는 건 별로 좋아하지 않지만, 항상 내긴 해. 하던 일 다 멈추고, 우리가 도착하자마자 내가 너에게\n "+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+".";
			}
			link.l1 = "흠. 나도 이쪽으로 가는 길이니, 이런 조건이라면 너를 태워줄 준비가 되어 있다.";
			link.l1.go = "passenger_1";
			link.l2 = "미안하오, "+GetAddress_FormToNPC(NPChar)+", 하지만 나는 다른 방향으로 항해 중이오. 도와줄 수 없소.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "안타깝군. 뭐, 다른 배를 기다릴 수밖에. 잘 가라.";
			link.l1 = "또 보자.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "좋아! 기다리는 것도 이제 지겹군. 우리가 도착하면 네 보수를 주겠다.";
			link.l1 = "내 배로 가라, "+GetAddress_FormToNPC(NPChar)+". 곧 출발할 거야.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "여기 도착했군요, 아주 훌륭합니다! 당신의 배를 타고 여행하는 건 정말 만족스러웠소. 선원들은 규율이 잘 잡혀 있고 갑판도 깨끗하더군요! 감사하오. 자, 돈을 받으시오, 나리.";
			link.l1 = "행운을 빌어, "+GetAddress_FormToNPC(NPChar)+"! 안녕히 가시오.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "꽤나 민감한 일이 있소..."+sTemp+" 지금 당장 돈이 필요하오, 아니면 큰일이 날 것이오. 평소라면 다른 신사에게 돈을 부탁하지 않겠지만, 이번 상황은 정말 절박하오.";
			link.l1 = "얼마나 필요하오?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "금액이 꽤 적소, 이건 "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+". 그래서, 도와줄 수 있겠소?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "네, 물론이지. 가져가.";
				link.l1.go = "donation_2";
			}
			link.l2 = "기꺼이 도와주고 싶지만, 내 주머니도 텅 비었어 – 남는 페소 한 푼도 없어.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "감사합니다, "+GetAddress_Form(NPChar)+"! 당신이 나를 구해주었소! 나는 총독 관저에 친구들이 있는데, 그들에게 당신의 관대함을 꼭 전하겠소. 다시 한 번 천 번 감사하오!";
			link.l1 = "천만에요, 나리. 저라면 역시 그렇게 했을 거라 확신합니다.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "당신의 도움이 필요합니다. 당신은 부유하고 신사이니, 제 사정을 이해해 주시리라 믿습니다. 얼마 전, 저는 돈이 급하게 필요해서 은행가에게 가서 전당잡힐 수밖에 없었습니다. "+pchar.GenQuest.Noblelombard.Item+"\n그가 좋은 조건을 제시했지. 한 달에 십 퍼센트, 총 삼 개월이었어. 하지만 불운한 사정 때문에 기한이 다 되었는데도 물건을 되찾을 돈이 없어\n이제 그는 그 물건을 사겠다는 사람을 찾았다고 하네 "+pchar.GenQuest.Noblelombard.Item+" 그리고 내가 지금 당장 빚과 이자를 갚지 않으면 그가 그걸 팔아버릴 거야. 하지만 지금은 돈이 별로 없고, 내가 맡긴 물건은 정말 값진 거란 말이야...";
			link.l1 = "그 일에 내가 어떻게 도와줄 수 있소, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "우리 은행가와 이야기해 주길 부탁하오. 그에게 돈을 제안하거나, 내 신용을 보증해 주거나... 아니면 다른 무언가를 해 주시오. 안타깝게도, 이제 의지할 사람이 아무도 없소; 내 좋은 친구들은 모두 갑자기 '파산'해 버렸으니. 세 달 안에\n "+pchar.GenQuest.Noblelombard.Text+", 그리고 내가 당신의 모든 비용을 두 배로 갚겠소! 신사의 명예를 걸고 약속하오!";
			link.l1 = "좋아, 이 일은 내가 도와주도록 하지.";
			link.l1.go = "lombard_2";
			link.l2 = "안타깝게도, 지금 나도 '파산' 상태야. 그래서 도와줄 수 없어, 정말 미안해!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "이해해 주셔서 감사합니다. 선술집에서 기다리고 있겠습니다. 가능한 한 빨리 오십시오.";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard.id = npchar.id;
			AddDialogExitQuestFunction("Noblelombard_TookQuest");
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "무슨 말을 할 수 있겠소, "+GetAddress_Form(NPChar)+"? 은행에 다녀왔나? 좋은 소식이야, 나쁜 소식이야?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "내가 그랬소. 내가 네 빚을 모두 대신 갚았으니, 이제 그곳에 가서 네 유물을 되찾아도 되오.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "그렇소. 지난 3개월치 이자와 앞으로 3개월치 이자까지 모두 갚았소. 돈은 안심하고 기다리셔도 됩니다. 다만 3개월 후에는 반드시 원금을 갚는 걸 잊지 마시오.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "있습니다. 지난 3개월치 이자는 모두 갚았습니다. 은행가는 당신이 전액을 마련할 때까지 3개월 더 기다려주기로 했습니다.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "무슨 말을 할 수 있겠소, "+GetAddress_Form(NPChar)+"? 은행에 다녀왔나? 좋은 소식이야, 나쁜 소식이야?";
				link.l1 = "있어. 그 구두쇠가 터무니없는 돈을 요구했지. 어떠한 양보 요청도 거절했고, 난 그만한 돈이 없어. 그래서 도와줄 수 없었어. 미안하다.";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "무슨 말을 할 수 있겠소, "+GetAddress_Form(NPChar)+"? 은행에 다녀왔나? 좋은 소식이야, 아니면 나쁜 소식이야?";
				link.l1 = "내가 할게. 기다려.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "에이, "+GetAddress_Form(NPChar)+"... 이제 그 지독하게 탐욕스러운 고리대금업자들의 억누를 수 없는 욕심을 당신도 직접 보았소. 맙소사, 나리, 저들은 유대인들조차 무색하게 만든다오! 내가 그랬듯이, 그들에게 돈을 빌리려 할 때 이 점을 꼭 기억하시오. 그래도 시도라도 해줘서 고맙소...";
			link.l1 = "난 그놈들이 원래 싫었어. 뭐, 고리대금업자를 좋아하는 사람이 어디 있겠어? 미안하군, "+GetAddress_FormToNPC(NPChar)+". 안녕히 가시오.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_fail");
		break;
		
		case "lombard_5":
			dialog.text = "믿을 수가 없어! 방금 나를 구해줬군, "+GetAddress_Form(NPChar)+"! 결코 잊지 않겠습니다. 모든 비용을 두 배로 갚아드릴 것을 약속합니다. 세 달 후에 우리 은행가를 찾아오십시오. 당신 이름으로 예금을 개설해 두겠습니다.";
			link.l1 = "좋아, 네 말대로 할게. 또 보자!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "다시 한 번 감사하오, 선장님. 행운을 빕니다!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_success");
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "나는 가지고 있지 "+LinkRandPhrase("공장","내 것","플랜테이션")+" 나는 항상 새로운 노예가 필요하지. 이 기후가 녀석들을 정말 힘들게 하거든. 지금 내가 필요한 건\n "+sti(npchar.quest.slaves.qty)+" 머리다. 나는 그걸 한 묶음 주문할 생각이네. 머리 하나당 금으로 지불하지, "+sti(npchar.quest.slaves.price)+" 두블룬\n서두를 필요 없어. 내가 필요한 걸 가져오면 시간 제한은 두지 않겠어. 물론 상식적인 선에서 말이지, 반년 이상 끌지는 말고. 어때? 거래할 건가?";
			link.l1 = "거래하자! 노예 장사는 더러운 일이지만, 그만한 위험을 감수할 만한 가치가 있지.";
			link.l1.go = "slaves_1";
			link.l2 = "실례하지만, 나는 노예상이 아니오. 내 업이 아니지.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "좋소. 화물을 가져오면 기다리고 있겠소. 매일 오전 11시부터 오후 1시까지 교회에서 나를 찾을 수 있소. 그 외 시간에는 바쁘거나 일하고 있소.";
			link.l1 = "좋아. 기억해 둘게. 또 보자, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "가져왔나 "+sti(npchar.quest.slaves.qty)+" 내가 부탁한 노예들은 데려왔소, 선장?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "그래. 전부 내 화물창에 있다네. 자네에게 넘겨줄 준비가 되어 있지.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "아니, 내가 처리할게.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "선장님, 노예들 때문에 오신 거라면... 이미 충분히 샀으니 지금은 더 필요 없소. 너무 늦으셨군, 미안하오.";
				link.l1 = "정말 안타깝군! 하지만 네 말이 맞아, 내가 충분히 재빠르지 못했지. 잘 가라!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "훌륭하군. 즉시 그들을 데리러 작은 배를 보내겠다.";
			link.l1 = "내 보수는 어떻게 되는 거지?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "걱정 마시오, 기억하고 있소. 여기, 돈을 받으시오, "+sti(npchar.quest.slaves.price)+" 두블론씩이네. 우리 둘 다 좋은 거래지, 그렇지?";
			link.l1 = "고맙소. 당신과 거래해서 즐거웠소.";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "그래야지... 이제 실례하겠소, 가봐야 하오. 또 보세!";
			link.l1 = "행운을 빌어요, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 이 마을 시민으로서 부탁하네, 검을 집어넣어 주게.","이봐, 이 마을 시민으로서 부탁하네, 검을 집어넣어 주게.");
			link.l1 = LinkRandPhrase("좋아.","원하시는 대로 하겠습니다.","좋아.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with a... certain lady of the evening, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with some money?" break;
		case 2: sText = "I ran through a local fool with my rapier recently and now the commandant demands a bribe to hush up the event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky enough to lose a bet and I don't have a trifling sum to repay the debt of honor. Can you help me?" break;
		case 4: sText = "Some bastard knows about my... indiscreet activities concerning a married woman. I don't have enough money to shut his mouth. Just a few gold coins are needed... " break;
		case 5: sText = "Some bastard has stolen important papers from my house and demanding a significant sum for their return. I've almost got it, just a few more coins needed. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler in Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spices and silk");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from the Spanish Main with gold ingots","I will get my inheritance");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get the profits from my plantation");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo hold stuffed with black ivory");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo hold filled with silks and spices","I will receive my interest from a European bank");
		break;
	}
}
