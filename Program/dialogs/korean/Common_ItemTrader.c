#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar,"선장님, 본인이나 부하 장교들을 위한 장비를 구매하시겠습니까? 그렇다면 제대로 찾아오셨습니다!","오, 선장님, 당신이 저에게 올 줄 알았어요! 당신과 당신의 장교들에게 필요한 장비를 비롯해 여러 가지 유용한 물건들을 제공할 수 있습니다.");
			link.l1 = "뭘 가지고 있는지 보여 줘.";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "나는 다른 일로 왔다.";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "이봐, 근처에서 흥미로운 식물을 발견했어. 이게 물약이나 달임약을 만드는 데 쓸 수 있는지 말해줄 수 있어? 그냥 눈에 띄어서 말이야. 한 번 봐줄래?";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "저기, 좋은 유럽산 와인 한 병 팔 수 있겠어?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "이봐, 네가 유럽산 와인을 판다는 거 알아. 나한테 60병 필요해.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "또 나야. 이게 다 무슨 뜻이지, 응?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "권총 두 자루와 스무 발 쏠 만큼의 탄환과 화약이 필요해.";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "이봐, 'Juan'이라는 이름 들어본 적 있어?";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "좋은 상인 나리, 나는 평범한 장신구가 아니라 특별한 품질의 물건을 찾고 있소. 대부분을 만족시키는 흔한 장식이 아니라 진정한 세련미가 느껴지는 것, 이를테면 정교하게 만든 귀걸이 한 쌍이나 귀족의 취향에 어울릴 만한 우아한 펜던트 같은 것이 필요하오. 고귀한 혈통의 숙녀를 기쁘게 할 선물이 필요하오.";
				link.l4.go = "UV_Lavochniki_1";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "혹시 당신의 물품 중에 상당한 가치를 지닌 것이 있습니까?\n가장 까다로운 귀부인조차 만족시킬 만한, 평범한 시민들이 좋아할 만한 것과는 차원이 다른 독특하고 세련된 물건을 찾고 있습니다.\n예를 들어, 보기 드문 예술성이 담긴 펜던트나 정교하게 디자인된 팔찌 같은 것이 있을까요?";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "말해보시오, 훌륭한 상인 나리, 귀금속에 대해 잘 아시오? 나는 고귀한 숙녀에게 드릴 특별한 보석을 찾고 있소. 솔직히 말해 평범한 장신구에는 관심이 없소. 내가 원하는 것은 진정으로 뛰어난 작품이오. 예를 들면, 보석이 박힌 브로치나 비할 데 없는 솜씨로 만든 반지 같은 것이 필요하오.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "이봐, 너 온갖 물건을 다 다루잖아... 어제나 오늘, 누가 너한테 팔겠다고 한 사람 있었어?  "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "감사하지만, 관심 없어.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "물론이지. 한 병에 칠백 페소야.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "훌륭하군. 돈을 가져와서 내게 넘겨라.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "훌륭해! 살 마음이 들면 다시 올게.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "부디, 병을 가져가시오.";
			link.l1 = "감사합니다!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "하! 나는 도매상이 아니라 소매상이야. 그 정도 병수를 팔려면 반 년은 걸릴걸 – 그 와인은 귀하고 비싸서 아무나 살 수 있는 게 아니거든. 그렇게 많이는 없어.";
			link.l1 = "좋아, 네가 그걸 가지고 있지 않다니 문제 없어. 하지만 너도 어딘가에서 구해오지 않냐? 혹시 네가 거래하는 공급자의 이름을 알려줄 수 있겠어? 내가 직접 그 사람에게서 사면 되니까. 아니면 유럽에서 와인이 배달되는 거야?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "아니, 그렇지 않아. 여기서 구하지. 하지만 그냥 내 공급자를 밝힐 순 없어. 하지만 천 페소라면... 어쩌면 말해줄 수도 있지...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "좋아. 여기 천이다 – 이제 네 공급자가 누구인지 말해.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "이제 너희 장사치들이 너무 뻔뻔해졌군! 그 정도면 너희한테는 과분하지 않겠어? 네네 공급업자 없어도 나는 잘 살 수 있으니까, 됐어.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "알겠소... 좋소, 여기 당신의 쪽지요. 언젠가 나도 신세를 갚을 수 있길 바라오.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "내 와인 공급업자의 이름은 "+pchar.questTemp.Wine.Name+", 그는 이 지역 가게 주인이야.";
			link.l1 = "알겠어! 고마워!";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "내 포도주 공급업자의 이름은 "+pchar.questTemp.Wine.Name+", 그는 이 지역 상점의 주인이야.";
			link.l1 = "알겠어! 고마워!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "원하시는 대로 하겠습니다, 선장님. 행운을 빕니다.";
			link.l1 = "또 보자.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "그게 무슨 뜻이야? 설명해 봐.";
			link.l1 = "날 속였군, 이 악당아! 방금 상점에 다녀왔는데, "+pchar.questTemp.Wine.Name+" 자기는 절대 와인을 거래하지 않는다고 직접 말했어! 내 돈 돌려줘!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "오해가 있었어... 내가 창고지기에게 갔는데, "+pchar.questTemp.Wine.Name+" 그자는 포도주 거래를 한 적이 없다고 주장했소. 이걸 어떻게 설명하시겠소?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "헤! 그 자는 포도주 장사라면 확실하지. 아무한테나 포도주를 파는 건 아니야 – 다른 몇몇 물건도 마찬가지고. 그럴 만한 이유가 몇 가지 있지... 그한테서 포도주를 사고 싶으면 내가 쪽지를 써줄 수 있어. 그는 나와 내 글씨를 아니까, 그걸 읽고 나면 너한테 포도주를 팔 거야. 물론, 이 호의도 공짜는 아니지.";
			link.l1 = "이게 말이 돼? 방금 나한테서 천 금화를 가져갔잖아!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "정보 값으로 천 페소를 받았지. 그리고 편지 값은 따로 이천 페소를 내야 해, 그 이하로는 절대 안 돼.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "오... 너희 상인들은 정말 욕심이 끝이 없구나. 그러니 아무도 너희 같은 부류를 좋아하지 않는 거야. 뭐, 어쨌든 여기 돈이 있으니 어서 영수증이나 써 줘.";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(믿을 만한 사람) 타협을 하자. 지금 네가 무료로 추천서를 써주면, 나도 나중에 너에게 무료로 추천서를 써주지. 이 와인 거래는 시작일 뿐이야.";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "이건 정말 도가 지나쳤군! 차라리 이 일 자체를 포기하겠소; 그런 교활한 구두쇠를 부유하게 만들 생각은 없으니. 그리고 그 구두쇠가 바로 자네요. 작별이오.";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "그렇다면... 알겠소. 여기 쪽지요, 앞으로 나도 신세를 질 수 있길 바라오.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "넌 참 별난 사람이구나, 선장! 물론 네 금전 관리는 급사가 맡고 있다는 거 알지만, 가끔은 네 머리도 좀 써야지. 내 마진 없이 와인을 도매로 꽤 괜찮게 살 기회가 있을 거야, 그럼 꽤 큰 이익을 볼 수 있지. 그러니 서로 돈 버는 길에 방해하지 말자고, 지금은 네가 더 욕심 많아 보이니까.\n그래... (적으며) 자, 이 편지를 받아 - "+pchar.questTemp.Wine.Name+"  아무 질문도 하지 않고 당신에게 와인을 팔 거요.";
			link.l1 = "그러길 바란다... 또 무슨 일이 생기면 다시 올 거야. 잘 있어!";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "원하시는 대로 하겠습니다, 선장님. 안녕히 가십시오.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "오, 그래서 나를 협박하고 무례하게 굴려고 온 건가? 그럼 경비병을 부르겠어! 이봐, 경비병들! 여기야!";
			link.l1 = "아, 닥쳐! 네가 이겼다, 나 간다! 젠장할 놈아 "+NPCharSexPhrase(npchar,"","")+"이런, 가마우지 자식아, 망해 버려라!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <-- мини-квест Дефицитный товар
		
		//Sinistra --> мини-квест "Знакомство с индейцами"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "아, 그렇군. 원주민들과 거래를 했다고? 이번 건으로 이미 꽤나 큰돈을 썼다던데, 하하!";
			}
			else
			{
				dialog.text = "문제가 생길까 걱정되십니까, 선장님? 아니면 정글 모험이라도 계획 중이신가요? 하하!";
			}
			link.l1 = "그럼, 거래를 할 수 있겠나?";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "물론이죠! 손님은 언제나 환영입니다. 삼천 페소만 주시면, 요청하신 대로 믿을 수 있는 권총과 탄환, 화약을 드리겠습니다.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "비싸긴 한데, 좋아. 살게.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "가격이 너무 비싼 것 같군. 모스크바 사람 파데이의 친구에게는 할인 좀 해줄 수 있겠나?";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "삼천이라고? 그건 강도질이잖아! 잘 있어라, 나리!";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "밖에서도 잘 지내시오, 선장님!";
			link.l1 = "안녕히 가십시오, 나리.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				Notification_Skill(true, 19, SKILL_COMMERCE);
				dialog.text = "그렇습니다, 선장님. 파데이의 친구들은 언제나 여기서 환영받지요. 전부 해서 이천삼백이면 어떻습니까?";
				link.l1 = "그게 더 낫군. 받아들이지.";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				Notification_Skill(false, 19, SKILL_COMMERCE);
				dialog.text = "파데이 나리의 친구라면 언제든 환영이오. 하지만 값에는 친구가 없지. 삼천 페소입니다, 선장님.";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "비싸긴 하지만, 좋아. 살게.";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "삼천이라고? 그건 강도질이잖아! 잘 있어라, 나리!";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "밖에서도 잘 지내시오, 선장님!";
			link.l1 = "안녕히 가십시오, 나리.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "아니, 그렇지 않아... 이제 그만 귀찮게 해, 나는 지금 아주 바쁘거든... 정말 바보 같은 질문이군...";
			link.l1 = "알겠소. 시간 뺏어서 미안하오...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "흠, "+pchar.GenQuest.Device.Shipyarder.Type+"? 처음 들어보는데... 그게 대체 뭐지? 내가 살아오면서 그런 건 한 번도 들어본 적 없어"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "음, 그건 조선공의 도구야, "+pchar.GenQuest.Device.Shipyarder.Describe+". 그런 제안을 한 사람이 있었소?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "흠... 그래, 이상한 녀석이 한 명 있었지. 근데 그게 뭔지 말도 안 해주고 그냥 나한테 팔려고만 하더라고. 근데 그게 뭔지도 모르는데 내가 그걸 왜 사? 어떻게 다시 팔겠어? 그래서 그냥 거절했지\n"+NPCharSexPhrase(npchar,"","")+", 그리고 그는 걸어갔다";
				link.l1 = "그 사람은 어떻게 생겼고, 어디로 갔지? 그 기구가 정말 절실히 필요해.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "아니, 그런 건 아니야. 미안하지만 도와줄 수 없어. 주변에 물어봐.";
				link.l1 = "알겠어. 자, 이제 사람들에게 물어볼 시간이군!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "나에게 보여줘... 그래, 흥미로운 식물이군. 그리고 아주, 아주 희귀한 거야. 망가 로사라고 불리지. 어디에 쓰는지는 모르겠지만, 이 식물에 관한 흥미로운 사실이 있어...";
				link.l1 = "무슨 뜻이야?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("나에게 보여 줘... 그래, 흥미로운 식물이군. 하지만 유감스럽게도 그 이상은 말해 줄 수 없어. 만약 이게 정말로 어떤 용도로 쓰인다면, 나는 그걸 몰라.","어디 보자... 흠... 약초처럼 보이긴 하는데, 나도 잘 몰라. 미안하지만 도와줄 수 없어.","어디 있지? 흠... 아니, 이건 처음 보는데. 확실히 아주 흥미로워 보이긴 하지만, 어디에 쓰는 건지 전혀 모르겠어...");
				link.l1 = "알겠어. 그럼 좀 더 알아볼게. 미안하다.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "유랑 집시들과 야만인들이 이 식물에 큰 관심을 보이더군. 예전에 집시가 이런 줄기 하나에 금 한 줌을 내는 걸 본 적이 있어. 하지만 그들이 왜 이걸 필요로 하는지는 전혀 모르겠어.";
			link.l1 = "알겠어... 뭐, 이 정도라도 다행이지! 이제 다음에 어디서 물어봐야 할지 알겠군. 정말 고마워!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
			dialog.text = "유감스럽게도, "+GetAddress_Form(NPChar)+", 내 가게에는 이렇게 훌륭한 상품이 들어온 지 여러 달이 되었소. 요즘처럼 힘든 시기에는 사치품에 대한 수요가 줄었지요. 내 가게를 찾는 평민들은 값싼 장신구밖에 살 수 없고, 상류층은 내 보잘것없는 물건들을 좀처럼 구경조차 하지 않소.";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_2":
			dialog.text = "유감스럽게도, 선장님, 그런 훌륭한 물건들은 꽤 오랜 시간 제 가게에 들어온 적이 없습니다. 이 항구의 부유한 손님들은 좀처럼 제 소박한 가게를 찾지 않고, 단골 손님들은 그저 형편에 맞는 물건만 찾을 뿐입니다.";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_3":
			dialog.text = "아, 선장님, 정말 안타까운 시기에 오셨군요... 불과 몇 시간 전에 정말 훌륭한 목걸이를 다른 부유한 선장에게 팔아버렸습니다. 저희 가게는 안목 높은 숙녀의 마음도 녹일 만한 보석을 늘 들여오고 있지요\n내일 다시 오시는 게 어떻겠습니까? 지젤... 그러니까... 제 공급업자들이라면 분명 당신이 흠모하는 분의 마음을 영원히 사로잡을 보물을 구해올 수 있을 겁니다.";
			link.l1 = "나는 시간이 없어, 지체할 여유가 없네. 그 목걸이를 손에 넣은 행운의 선장 이름이 무엇인지 어서 말해주게.";
			link.l1.go = "UV_Lavochniki_3_1";
		break;

		case "UV_Lavochniki_3_1":
			dialog.text = "트리스탄 르니에, '골든 시걸'의 선장이지. 그의 배는 아직 우리 항구에 정박해 있다네.\n솔직히 말하자면, 그가 그렇게 귀한 것을 내줄지 의문이 드는군. 만약 그가 내주지 않겠다면, 내일 다시 나를 찾아오게.\n명예를 걸고 맹세하네, 선장. 자네에게 아주 만족스러운 합의를 보장하겠네.";
			link.l1 = "...";
			link.l1.go = "UV_Lavochniki_exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		
		case "UV_Lavochniki_exit":
			DialogExit();
			AddQuestRecord("UV", "3");
			/*AddQuestUserData("UV", "sSex", NPCharSexPhrase(NPChar,"ца","ки"));
			AddQuestUserData("UV", "sSex1", NPCharSexPhrase(NPChar,"ец","ка"));
			AddQuestUserData("UV", "sSex2", NPCharSexPhrase(NPChar,"","а"));*/
		break;
		//<-- Украденное воспоминание
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
