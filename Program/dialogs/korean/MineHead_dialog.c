// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("여기 impudently 나타나다니?! 네가 용감한 건지 그냥 멍청한 건지 모르겠군...","이 게으름뱅이들이 어떻게 적이 내 저택에 침입하게 놔뒀지? 도무지 이해가 안 되는군...","분명히, 이런 놈들이 여기서 돌아다니고 있다면 내 경비들은 구리 한 닢 값어치도 없겠군..."),LinkRandPhrase("무슨 일이야?"+GetSexPhrase("놈","냄새나는 놈")+"?! 내 병사들이 이미 너를 쫓고 있다, "+GetSexPhrase(", 더러운 해적놈","")+"!","더러운 살인자, 당장 내 집에서 나가라! 경비병들!","나는 너 따위 안 무서워, "+GetSexPhrase("쥐","걸레")+"! 곧 우리 요새에서 목이 매달릴 테니, 그 다음엔 더 이상 도망치지 못할 거다..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("이 병사들은 페소 한 푼의 값어치도 없어...","걔네들은 절대 날 못 잡아."),RandPhraseSimple("입 다물어, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 그 더러운 혀를 뽑아버릴 테니까!","가만히 앉아 있는 게 좋을 거다, 그러면 어쩌면 살아남을 수도 있겠지..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "광산에 적이 나타났다! 경보 울려라!";
				link.l1 = "아아, 악마 놈!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", 나리. 나는 "+GetFullName(npchar)+", 로스-테케스 광산의 광산 기사입니다. 무슨 일로 여기 오셨습니까?","안녕하시오, 나리. 무슨 일로 오셨소?","흠... 나한테 뭐 원하는 거라도 있나, 나리? 듣고 있네.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "나는 여기 처음인데, 이 광산에 대해 더 알고 싶어...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "내 창고에 네가 관심 가질 만한 화물이 있지. 정확히 말하면 네 광산에서 쓸 노예들이야. 흥정해 볼래?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "난 그냥 인사하러 들어왔는데, 벌써 나가네.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Los-Teques 광산은 스페인 왕실을 위해 금을 채굴한다네. 우리가 채굴하는 모든 것은 스페인 소유지. 여기서는 금뿐만 아니라 은 덩어리와 귀한 보석들도 발견되지. 우리는 이곳에서 금을 팔지 않아. 채굴한 모든 것은 강화된 호위대와 함께 구세계로 보내지. 하지만 금과 은 덩어리에 한해서 두 가지 예외가 있네. 첫째, 일정량은 우리 지역 상점에서 병참장교에게서 살 수 있지. 가끔 급여가 제때 도착하지 않아서, 그런 경우를 대비해 여기서 약간의 동전을 남겨두어야 하거든. 그래서 지역 거래가 허용되는 거야. 둘째, 우리는 항상 인력이 부족하니, 덩어리를 노예와 교환하기도 해. 그러니 제안할 것이 있으면 나에게 말하게. 우리가 거래를 하도록 하지. 광산의 행동 규칙은 분명하다고 생각하네: 훔치지 말고, 죄수들을 방해하지 말고, 병사들에게 폐를 끼치지 마시오. 그렇지 않으면 결과가 마음에 들지 않을 걸세.";
			link.l1 = "좋아요, 감사합니다!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "물론이지, 나리! 몇 개나 가지고 있나?";
			link.l1 = "나는 가지고 있다 "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "나리, 유감스럽게도 지금은 노예가 더 필요하지 않소. 하지만 상황은 언제든 바뀔 수 있으니, 몇 주 후나 다른 때에 다시 찾아오시오.";
				link.l1 = "알겠소, 나리. 지금은 그들이 필요 없겠지만, 언젠가는 필요할지도 모르지.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "물론이오, 나리! 몇 개나 가지고 있소?";
				link.l1 = "나는 가지고 있다 "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "노예 한 명당 금괴 하나나 은괴 두 개를 줄 생각이오. 어느 쪽을 택하겠소?";
			link.l1 = "금괴.";
			link.l1.go = "slaves_g";
			link.l2 = "은괴.";
			link.l2.go = "slaves_s";
			link.l3 = "미안하오, 나리, 하지만 방금 마음이 바뀌었소. 다음에 하도록 하지.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "좋아. 노예를 몇 명이나 팔 생각이오?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "좋아. 나한테 노예를 몇 명이나 팔 생각이지?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "나리, 나는 어리석은 농담에 쓸 시간이 없소. 농담할 기분이면 선술집에나 가시오!";
				link.l1 = "흠...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "나리, 쉬셔야 할 것 같습니다. 아마 많이 피곤하시거나 일사병을 겪으신 것 같군요. 선술집에 가서 좀 쉬시고, 그 다음에 다시 흥정을 계속하죠.";
				link.l1 = "흠...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "유감이지만, 나리, 지금은 그렇게 많은 노예가 필요하지 않소. 현재 광산에서는\n "+FindRussianQtyString(sti(location.quest.slaves.qty))+". 그렇게 많이 팔 생각이오?";
				link.l1 = "네, 물론이지!";
				link.l1.go = "slaves_max";
				link.l2 = "흠... 그런 것 같진 않군.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"좋아. 그들을 마을 입구로 데려오라고 명령을 내리시오. 내가 부하들을 보내겠소.";
			link.l1 = "걱정 마시오, 나리. 노예들은 제때에 당신께 인도될 것이오. 즉시 모든 관련 명령을 내리겠소.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "훌륭하오. 그들을 마을 문으로 데려오라고 명령해 주시오. 내가 내 부하들을 보내겠소.";
			link.l1 = "걱정 마시오, 나리. 노예들은 제때에 당신께 인도될 것이오. 내가 즉시 모든 관련 명령을 내리겠소.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
