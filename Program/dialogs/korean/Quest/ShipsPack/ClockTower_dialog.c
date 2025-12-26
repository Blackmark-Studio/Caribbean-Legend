int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "뭐 필요해?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "멈춰, 선장 나리. 이 지점 너머로는 통과할 수 없어.";
			link.l1 = "왜 안 되는데?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "저 탑 보이지? 네덜란드 서인도 회사 사무소야. 선박 등록부서랑 기록 보관소지. 예약 없이는 들어갈 수 없어.";
			link.l1 = "그럼 어떻게 약속을 잡지?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "알아야 할 놈들은 이미 알고 있지. 그 마인헤르 이사는 아무하고나 일하지 않아.";
			link.l1 = "'디렉터 나리'? 그게 누구야?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "반 도른 이사. 사실 완전한 이사는 아니지만, 다들 그렇게 부르지. 여기서 10년째 일하고 있어 — 모든 걸 정돈했지. 이제 카리브 해의 모든 배가 그의 사무실을 거치게 돼.";
			link.l1 = "모든 배 말인가? 전함까지도?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "최고급 선박과 가장 부유한 선장들만이 있지. 우리 사무소의 고객이 된다는 건 큰 영광이야!";
			link.l1 = "어떤 서비스를 제공하시오?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "나는 자세한 건 몰라 — 그냥 입구만 지킬 뿐이야. 하지만 사람들이 만족하고 나간다는 소문은 들었어.";
			link.l1 = "인상적이군.";
			link.l1.go = "ClockTower_Johan_7";
		break;
		
		case "ClockTower_Johan_7":
			dialog.text = "그리고 한 가지 더 말해주지. 저 시계 보이지? 유럽의 경이야 — 우리 촌구석에서는 절대 구경 못 할 물건이지. 그 미네르 이사 나리께서 직접 관리하신다네.";
			link.l1 = "혹시 우리 서로 협상을 할 수 있을까?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "안에 들어갈 수 있게 뭔가 방법이 있을 텐데?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "나는 뇌물 안 받아!";
			link.l1 = "미안하오. 자네, 좋은 사람이군. 이름이 무엇인가?";
			link.l1.go = "ClockTower_Johan_9";
		break;
		
		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... 봐라... 네가 이 근방 사람이 아니라는 건 알아. 하지만 여기엔 질서가 있다. 미네르 이사님이 항상 말씀하시지: 한 번 약함을 보이면, 우리 탑은 무너진다고. 안에 들어가고 싶어? 도시를 도와라 — 그러면 눈에 띌 거다.";
			link.l1 = "알겠다. 방심하지 마, 병사.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "글쎄, 잘 모르겠군. 미네르 이사님은 빌렘스타트의 친구들에게 보상을 주지. 도시를 도우면 — 눈에 띌 거야. 듣자하니 당신은 이곳 사람이 아닌 것 같군. 하지만 우리는 여기서 질서를 지키고 있어. 미네르 이사님이 항상 말씀하시지: 한 번이라도 약해지면, 우리 탑은 무너진다고.";
			link.l1 = "알겠어. 그런데 네 이름이 뭐지?";
			link.l1.go = "ClockTower_Johan_10";
		break;
		
		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "그리고 나는 "+GetTitle(NPChar, false)+" "+GetFullName(pchar)+". 방심하지 마라, 병사.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "무슨 일이라도 있었나?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". 제가 뭘 도와드릴까요?";
				link.l1 = "아니, "+npchar.name+". 계속해.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "무슨 일이라도 있었나?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "축하합니다. 약속이 잡혀 있습니다.";
			link.l1 = "약속? 누구랑?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "네덜란드 국장 나리의 대리와 함께요. 당신이 도시에 도움을 준 소식을 듣고 저더러 당신을 초대하라고 명령하셨소.";
			link.l1 = "감독 자신은 어쩌지?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "어... 그 일에 대해서는 말할 권한이 없어. 안에서 행운을 빌어, "+GetTitle(NPChar, true)+".";
			link.l1 = "감사합니다.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "DWIC 선박 등록부에 오신 것을 환영합니다. 선장님...?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+",\n" +
							"마르텐 비서, 부국장.\n" +
							"윌렘스타드에 꽤 도움이 되었다고 들었소. 아마 우리 사무실도 자네에게 도움이 될 수 있을 것이오.";
			link.l1 = "그래서 내가 여기 온 거야.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "쿠라사오 수도에 도움이 될 수 있어 기쁩니다.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "프랑스든, 스페인이든, 네덜란드든 어떤 선장이라도 우리에게 선박 점검을 의뢰할 수 있지. 우리는 돛대, 대포, 장비를 검사한다네. 약점을 찾아내고, 조언도 해주지\n";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "프랑스, 스페인, 네덜란드 어느 나라 선장이든 우리에게 선박 점검을 의뢰할 수 있소. 우리는 돛대, 대포, 장비를 검사하지. 약점을 찾아내고, 조언도 해주지\n";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "그리고 심사가 한 번으로 부족하다면, 새 선박 서류도 마련해 드릴 수 있소. 다시 말해, 우리 사무실의 일은 귀하의 배를 개선해 줄 것이오 — 소중한 마호가니나 비단을 쓰지 않고도 말이오.";
			link.l1 = "그게 어떻게 가능하지?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = "선장님, 당신이 얼마나 강력한 곳에 들어왔는지, 그리고 펜 한 번 움직이는 것만으로 얼마나 많은 일이 이루어질 수 있는지 전혀 모르실 겁니다.";
			link.l1 = "두블룬 때문이겠지?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "당연하지. 우리 서비스는 싸지 않고, 네 배의 크기에 따라 달라진다. 하지만 항상 그 값어치를 한다. 우리 문을 통과한 선장은 좀처럼 실패하지 않지\n" +
						"하지만 우리는 네 금화를 그냥 빼앗는 것만은 아니야 — 네가 금화를 벌 기회도 주지. 해적들이 너무 불어나서, 이제는 소앤틸리스에서도 선장들이 이 해충들을 쫓아내려고 함대를 꾸려야 할 지경이지. 해적을 처치했다는 증거를 가져오면 — 똑같은 두블룬으로 보수를 받을 거다.";
			link.l1 = "무슨 증거?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "선박 일지. 저런 오합지졸이라도 최소한의 기록은 남겨야 해 — 그렇지 않으면 루거 한 척도 제대로 지휘할 수 없지. 게다가 일지는 악행의 명백한 증거일 뿐만 아니라, 언제나 우리 기록 보관소에 자리를 잡게 되지. 보험 분쟁 때도 쓸모가 있거든\n" +
						"우리 서비스에 관심이 있다면, 고객 명단에 자리가 하나 났어 — 최근에 우리 선장 중 한 명이 계약을 끝냈거든. 일을 완수하면 — 그 자리는 네 거야.";
			link.l1 = "왜 이렇게 복잡하게 구는 거야? 내 두블룬이면 충분하지 않아?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", 우리는 양이 아니라 질로 승부하지. 우리 사무실의 모든 고객은 최고의 서비스와 직접 mynheer 이사님의 세심한 배려를 받게 되네. 그리고 그 이사님의 시간은, 믿어주게, 우리처럼 결코 가난하지 않은 회사에게도 상당한 비용이 드는 일이야. 한 달이 삼십 일뿐이니, 고객도 삼십 명만 받을 수 있네.";
			link.l1 = "무엇을 해야 하지?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "해적선의 항해일지 다섯 개를 가져와라 — 그게 네 실력을 증명해 주겠지. 보상은 그 일지 주인들이 얼마나 위험한 놈들이었는지에 따라 달라진다.";
			link.l1 = "좋아. 내가 하지.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "생각 좀 해봐야겠어.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "감독 본인은 어디 있지?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "훌륭하군. 결과를 기다리겠네, 그리고 우리의 협력이 기대되는군.";
			link.l1 = Goodbye(true) + ".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "원하시는 대로 하십시오. 제 제안은 유효합니다. 하지만 생각보다 빨리 자리가 차버릴 수도 있습니다.";
			link.l1 = Goodbye(true) + ".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "바다에서. 반 도른 나리는 사무실 관리와 기함 지휘를 겸하고 있다.";
			link.l1 = "어떻게 그걸 해내는 거지?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "그 사람은 하루에 열여덟 시간씩 일해. 위층 사무실에서 자고. 잠은 시간 낭비라고 하더군. 네 시간만 자도 충분하대.";
			link.l1 = "저 거대한 시계 장치들에서 나는 소음은 어쩔 건데? 여기서 도대체 누가 잠을 잘 수 있겠어?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "직접 그에게 물어볼 수 있을 거야, 아마 뭔가를 알게 될지도 모르지. 그는 항상 손님들과 이야기하는 걸 좋아하거든. 우리 서로 이해한 거지?";
			link.l1 = "완벽하지.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "꼭 그렇진 않아...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "좋은 하루 되십시오, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;
		
		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! 기록을 가지고 있나?";
			link.l1 = "잘 알고 있군, "+npchar.name+".";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "하! 여긴 부두도 아니고 성문도 아니야. 그리고 나는 그냥 근무 중인 경비병이 아니라 회사 직원이라고.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"! 기록을 가지고 있나?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "통나무를 가져왔어. 지나가게 해줄 거야?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "다음에 보자.";
			link.l2.go = "ClockTower_Johan_34";
		break;
		
		case "ClockTower_Johan_33":
			dialog.text = "잘 돼서 다행이야! 어서 가, 너를 기다리고 있어.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;
		
		case "ClockTower_Johan_34":
			dialog.text = "좋은 하루 보내십시오, 선장 나리, "+GetTitle(NPChar, true)+".";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "선장님! 돌아오셨군요. 기록을 가져오셨습니까?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "그래. 다섯 명 전부다.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "다음에 보자.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
			// link.l1.go = "ClockTower_Visser_36";	
			
		break;

		case "ClockTower_Visser_22":
			dialog.text = "훌륭하군. 내게 보여 줘봐.\n"+
							"그래, 다 제대로 되어 있어. 이건 진짜 해적선들이야. 제대로 만든 물건이지. 네가 받을 몫이야 " + SellJournals() + " 두블론\n자, 가져가십시오. 그리고 여기에도 서명해 주시기 바랍니다.";
			link.l1 = "그럼 나도 명단에 있는 거야?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromKPTotal("ClockTower_PirateJournal", 5);	// 
		break;

		case "ClockTower_Visser_23":
			dialog.text = "거의 다 됐어. 먼저 서류 작업을 처리해야 해. 몇 분 걸릴 거야\n"+
							"성함이 어떻게 되십니까?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "국적이 뭐지?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "네 배 이름이 뭐지?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "어떤 종류의 선박인가?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "포의 수는?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "선원 수?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "좋아. 이제 여기에 서명해. 그리고 여기에도. 여기도 마찬가지야.";
			link.l1 = "그게 다야?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "거의 다 됐소. 이제 당신을 등록부에 올리기만 하면 돼. 물론, 나리 이사님께서 직접 당신을 만나셔야 하겠지만... 그건 형식적인 절차일 뿐이오 — 나는 신규 고객을 받아들일 권한이 있소\n"+
			"...하지만 또 딴길로 새고 있군. 이제 반복 가능한 서비스에 대해 말하자면...\n"+
			"보험이지. 비싸긴 하지만, 회사에서 보험 든 배는 어떤 해군 함대도 건드리지 않아. 식민지가 포위당해도 항구 창고에 원하는 만큼 배를 안전하게 보관할 수 있지, 잃을 걱정 없이\n"+
			"선박 점검 — 전략 자원을 소모하지 않고 모든 특성을 소폭 향상시킵니다. 우리가 모든 것을 점검하죠: 돛대, 화물칸, 선원실까지. 개선 방안도 제시합니다. 가격은 선박 크기에 따라 달라집니다\n"+
			"우리 기록에 등록됩니다. 카리브 해역에서 선박의 안전이 높아져 현상금 사냥꾼, 해적, 군인들이 당신을 공격하기 전에 두 번 생각하게 될 것입니다\n"+
			"특정 선박에 대한 심사와 등록은 한 번만 할 수 있어. 그러니 돈을 썼다면 네 배를 잘 챙기라고. 선장들이 자기 배를 아무렇게나 다루고 장갑 갈아끼듯 바꿀 때마다 내 상관들이 얼마나 열받는지 너는 모를 거야!\n"+
			"하지만 또 딴길로 새고 있군. 이제 반복 가능한 서비스에 대해 말하자면...\n"+
			"서류 교체. 배마다 각기 다른 전문 분야가 있다는 건 알고 있겠지. 하지만 그게 주로 배의 서류가 어떻게 작성되어 있느냐에 달려 있다는 건 짐작도 못 했을 거야. 네 전함이 요새 공략용으로 서류가 작성된 게 마음에 들지 않는다면, 누구에게 가야 할지 알겠지\n"+
			"음, 해적선의 항해일지를 넘기면 보상을 준다는 얘기는 이미 들었겠지... 해적이 위험할수록 그 일지에 더 많은 돈을 쳐줄 거야.";
			link.l1 = "인상적이군. 솔직히 말해서, Visser 나리, 당신의 집무실은 정말...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "암스테르담 호가 항구에 들어왔어! 감독관 나리가 돌아오셨다!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "뭐?! 벌써?! 하지만 그는 아직 사흘이나 더 있다가 돌아올 예정이었잖아!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "그 네덜란드 국장 나리께서 이미 상륙하셨소! 곧장 이쪽으로 오고 계셔!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "세상에... 그가 너를 보면...";
			link.l1 = "무슨 문제야? 네가 직접 새 손님을 받을 권한이 있다고 방금 말했잖아.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "나도 그래! 하지만 그는... 아니야, 됐어. 선장, 밖에서 기다리시오. 입구 근처에서. 감독관 나리께서 당신과 이야기하고 싶어하실 거요.";
			link.l1 = "나랑 같이?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "그 사람은 새 의뢰인을 직접 심사하지. 항상 그래. 어서 가!";
			link.l1 = "통나무 때문에 두블룬은 안 돌려줘!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "아쉽군, 나도 남아서 듣고 싶었는데.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "뭐였지, 요한?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "마인헤르 이사 나리가 돌아왔소.";
			link.l1 = "그게 뭐가 그렇게 끔찍하다는 거야?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "별일 아니야! 그냥... 그 나리 이사님은 뜻밖의 일을 싫어하시거든. 모든 게 계획대로 진행되어야 해. 그런데 아직 심사하지 않은 새 손님이 나타난 거지.";
			link.l1 = "마르텐이 자기가 나를 명부에 올릴 권한이 있다고 했어.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "아니, 그게 문제가 아니야. 그 나리 이사 양반은 그냥... 그러니까, 모든 걸 자기가 직접 통제하고 싶어 해. 사소한 것까지 전부. 그렇지 않으면 다 망가진다고 하더라고. 이제 곧 자기 시계 걱정 또 시작할 거야, 두고 봐.";
			link.l1 = "뭐?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "반 도른 나리께서는 짜증이 나면 시계를 멈추고 만지작거리기 시작하십니다. 가끔은 도시 전체가 반나절 동안 시간을 잃기도 하죠. 그리고 그런 일이...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "오... 들리나? 시작됐어.";
			link.l1 = "두목이 돌아왔다. 평소처럼 일하자.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "잘 들려. 저놈들 마르텐을 아주 박살내고 있어.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "안타깝게도, 이젠 익숙해졌지.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "너 참 심하구나. 내 생각엔 그건 불공평해.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "조용해진 것 같군. 곧 너를 안으로 들일 거야.";
			link.l1 = "나 곤란해진 거야?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "걱정 마. 너는 아무 잘못도 안 했어.";
			link.l1 = "안심이 되는군.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "자, 이제 가자! 그 마인헤르 이사 나리는 가끔 너무 엄격하긴 하지만... 그래도 인심도 후하고 예의도 바르지... 오, 봤지?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "아, 내가 말했잖아!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "마인헤르 이사 나리께서 안에서 기다리고 계십니다.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". 네 배 — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" 총과 "+GetMaxCrewQuantity(pchar)+" 선원들.";
			link.l1 = "모두 맞았어.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "내가 너에 대해 모든 걸 아는 반면, 너는 요한의 험담 말고는 나에 대해 아무것도 모른다는 게 불공평하지. 헨드릭 판 도른. 카리브 해 네덜란드 서인도 회사 등기부 부서의 책임자. 프리깃 암스테르담의 지휘관. "+shipType+". "+GetCannonQuantity(npchar)+" 총과\n "+GetMaxCrewQuantity(npchar)+" 선원들.";
			link.l1 = "만나서 반갑소.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "너는 해적선의 항해일지 다섯 개를 손에 넣었지. 내 부관이 너를 높이 평가해서 고객 명부에 올렸고, 내 사무실의 서비스도 안내해 주었어\n"+
						"하지만 입학에 대한 최종 결정은 언제나 내 몫이지. 직접 말이야. 면담 후에. 마르텐은 후보를 추천할 수 있을 뿐, 그 이상은 아니야.";
			link.l1 = "시작하자.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "나는 해적을 효과적으로 상대하면서도 우리 서비스를 이용할 만큼 상업적으로 성공한 선장이 필요하오. 그 조건에 부합하시오?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "나는 모르티머 그림을 해치웠다. 브리그 멤토의 선장이다.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "네 동료들이 내가 알버트 블랙우드를 이긴 걸 높이 평가한 것 같군. 스노우쉽 레이디 베스는 정말 만만치 않은 상대였지.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida는 해적이 아니었지만...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "나는 모든 항해자들이 두려워하던 공포를 쓰러뜨렸어. 너도 알아둬야 해.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "너 지금 내 배를 선적부에 등록했지. 무능한 선장이 그걸 제대로 관리할 수 있을 것 같아?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "나는 잘 지내고 있어, 그리고 카리브 해에서는 돈이 나무에서 열려.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Visser 나리께서 이미 내 능력을 확인하셨소. 당신 부하의 평가만으로는 부족하단 말이오?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "그림? 우리 조직은 그림에 대해 불만을 가진 적이 없어, 오히려 반대였지. 하지만 그의 자리를 차지한 자... 내가 그가 누구였는지, 그리고 처음에 무슨 목적으로 카리브에 왔는지 알고 있지. 그런 악행에는 공소시효 따위 없어. 네가 그 범죄자이자 내 조국의 진정한 적을 처단해 줘서 기쁘다.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "내가 케이맨 사건 보고서를 제대로 기억한다면, 그 주장에 대해 확인할 기회가 없었지. 내 생각엔 상황이 완전히 명확하진 않지만, 네 승리는 확실히 능숙했어.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "하지만 훨씬 더 끔찍한 존재가 될 수도 있었지, 정말 그래. 가치 있는 적이었어, 비록 너한테 진 게 아니라 은혜도 모르는 상관들에게 진 거지만. 나는 네덜란드 사람이니까, 카스티야와의 전쟁에 대해서라면 내가 할 말이 있지.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("플라잉 하트")+"'. 아직도 저런 괴물이 항구에 들어올 때 정직한 사람들이 도망치지 않는 게 신기할 따름이오. 이 이야기에는 놀랄 일이 많소, 선장. 하지만 언젠가 이 이야기도 우리 기록에 남아 신비로움을 잃게 되겠지. 그리고 그대는... 이미 스스로를 불멸로 만들었소.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "놀랄지도 모르지. 하지만 너의 경우에는 의심의 여지가 없어, 그건 사실이야.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "그러니 아무 가치도 없지. 물론 두블룬이라면 얘기가 다르지만.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\n사무실의 서비스를 이용할 수 있도록 승인되셨습니다. 존경받는 네덜란드 서인도 회사 해군 등록부에 오신 것을 환영합니다.";
			link.l1 = "감사합니다.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "이건 서로에게 이득이 되는 협력이지. 너는 카리브 해에서 최고의 서비스를 이용할 수 있고, 우리는 믿을 만한 동료를 얻는 거야.";
			link.l1 = "좋아.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "잠깐! 저 소리 들려?";
			link.l1 = "아무 소리도 안 들려.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "바로 그거야! 딱 일주일만 비웠더니 이런 일이...";
			link.l1 = "뭐 문제라도 있나?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "시계 때문에. 기계장치를 확인해야 해. 미안하네. 이건... 중요한 일이야.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "이제 괜찮아 보이네. 다시 한 번 미안하다. 궁금한 거 있나?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "더 물어볼 거 있나?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "당신의 부관이 사무실의 서비스를 자세히 설명했어. 이게 도대체 어떻게 가능한 거지?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "두 자리를 어떻게 겸하나? 선장에 감독까지?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "이런 환경에서 어떻게 일하지? 시계 장치에서 나는 소음, 어둠, 그리고 두꺼운 커튼으로 가려진 창문들까지.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "아니요, 시간 내주셔서 감사합니다. 사무실의 서비스는 어떤가요?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "여기엔 마법 따윈 없어, 선장. 세상을 지배하는 건 펜과 잉크지. 교회는 사람의 출생, 세례, 결혼, 죽음을 기록한다네. 한 줄만 바꿔도 운명이 달라지지. 배는 좀 더 복잡하지만, 그것도 펜 한 번 놀리면 많은 게 달라져. 숨기지 않겠네, 내가 이룬 걸 자랑스럽게 생각해. 하지만 아직 더 나아질 수 있다는 것도 알고 있지. 만약 우리가 장부에 배와 사람만이 아니라, 온 세상을 기록한다면 어떨까?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "누군가는 해야 하니까. 암스테르담의 전임 선장은 앤티가 출신 무리와의 전투에서 전사했지. 회사에서는 마땅한 후임을 찾지 못했어. 그래서 내가 자원했지. 훈련을 받고, 시험을 통과하고, 임명장을 받았어\n"+
			"그래, 나는 한심한 선장이야. 너보다 훨씬 못하지 — 그건 확실해. 하지만 좋은 관리자는 배뿐만 아니라 뭐든 이끌 수 있지. 세 사람을 지휘하는 법을 배우는 게 제일 어렵다. 그걸 익히면 삼천 명도 지휘할 수 있어. 사무실이든, 배든, 마을이든, 아니면 거대한 회사든 — 유능한 사람을 찾아서 네 대신 믿고 맡길 수만 있다면 한계는 없어... 마지막이 제일 어렵지. 진짜 저주야.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "그리고 숨 쉴 공기조차 거의 없어. 선장, 인간은 자기만의 환경을 만드는 법이지. 여기서는 아무것도, 아무도 나를 방해하지 않아. 모든 것이 내 손이 닿는 곳에 있고, 오직 나와 시간만이 지배하지. 가능하다면, 나는 바깥 세상과 오직 종이로만 소통하고 싶어. 안타깝게도, 그건 불가능하지. 너무 신경 쓰지 마, 선장. 혼자인 게 낫지, 외로운 것보다는. 내 말이 무슨 뜻인지 알겠나?\n";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "우리는 예약 손님만 받습니다. 당신의 예약은... "+pchar.quest.ClockTower.date+" "+month+". 지정된 날에 오지 않아도 상관없어. 요한에게 연락하면, 다음 가능한 약속을 알려줄 거야.";
			link.l1 = "왜 이렇게 복잡하게 굴지?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "우리의 일은 값이 비싼 편이오. 우리는 진정한 기적을 일으키고, 의뢰인들에게 큰 이익을 가져다주기 때문이오. 이해관계 충돌은 있을 수 없으며, 그래서 특정 개인을 위해 하루 전체를 할당하오. 다음 예약 가능 날짜:\n "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"Visser를 보거든... Maarten이 자네를 후보로 추천한 건 옳은 판단이었네. 그 말을 꼭 전해 주게. 그는 훌륭한 부관이야. 절대 의심하지 않길 바라네.";
			link.l1 = "좋아.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "좋은 하루요, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "어떻게 됐어?";
			link.l1 = "긴 하루였지만, 반 도른이 당신의 결정을 확인해 주었소.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "신이시여, 감사합니다. 내가 모든 걸 제대로 했군.";
			link.l1 = "그가 당신에게 전하라고 했어. 네가 좋은 부관이라고.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "정말이야? 그가... 그렇게 말했다고?";
			link.l1 = "그래. 그렇게 말했다.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "젠장. 그가 그런 말을 하지 말았어야 했는데. 이제 내가 고마움을 모르는 놈처럼 느껴지잖아. 아니면 이걸 다 예견하고 일부러 그런 걸까?";
			link.l1 = "대리 나리, 갑자기 예전 같지 않으시군요.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "선장, 나도 장사꾼이고 당신도 그렇잖아, 그러니 바로 본론으로 들어가자.\n"+
						 "그 미네르 이사 나리는 우리와 오래 일하지 않았어.";
			link.l1 = "뭐라고, 뭐라구?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "그는 한 가지 목표로 계약을 맺고 이곳에 왔지 — 선박 등록 부서를 설립하는 거였어. 그 일은 훌륭하게 해냈고, 후임자를 직접 가르쳤고, 나까지 승진시켰지... 그리고 그걸로 끝이야.";
			link.l1 = "뭐야, 그게 다야?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "그의 계약은 오래전에 끝났어. 정확히 언제인지는 모르지만, 이 자가 더 이상 그 자리를 지킬 권리가 없다는 건 우리 모두 확신하고 있지.";
			link.l1 = "알겠어. 이 건물 중앙 구역에 있는 배부른 졸부 놈들이 다들 안절부절하지.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "알겠어. 네가 그 자리를 차지할 때까지 기다리는 게 지겨운 거구나.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "맞아! 그리고 저놈들은 아무것도 할 수 없어!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "솔직히 말할게. 나 정말 피곤해. 젠장, 반 두른이 계약 끝나면 자길 대신하게 하려고 일부러 나를 승진시킨 거야!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "그래도 내가 속았다고 느낀다고 해서 저 자식 밑에서 이 빌어먹을 의자를 흔들 생각은 없어! 신만이 아시겠지만, 나는 이 사람에게 감사하고 존경하고 있거든!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "아니요, 마인헤르. 판 도른은 우리 모두의 상관들을 쫓아내려 하고 있어요. 바로 저 탑 벽 뒤, 이 건물 중앙 동에 앉아 있는 그 사람들이요! 하지만 그들조차도 그를 통제할 방법을 찾지 못하고 있어요!\n";
			link.l1 = "그게 뭐가 그렇게 어렵다고? 반 도른이 스타이베선트보다 더 대단한 인물도 아니잖아.";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "여긴 배도 아니고 왕실 궁정도 아니오, 선장. 우리 회사는 완전히 새로운 유형의 조직이오. 그렇게 소중한 사람을 그냥 손가락질하며 내칠 수는 없소.\n"+
						 "첫째, 아무도 반 도른 계약서 원본이 어디 있는지 모른다. 그러니 해임할 근거도 없어. 우리가 시도했다간 변호사 떼거지 몰려오고, 결국 우리가 그에게 빚지게 될 거야.\n"+
						 "둘째로, 경영진이 암스테르담 호의 임무를 반 도른에게 맡긴 건 실수였지. 그는 약한 선장일지 몰라도, 이 지역에서 최고인 선원들을 모았거든. 명령만 내리면 회사의 정예 병사들이 눈 하나 깜빡이지 않고 이 건물을 점령할 거야.\n"+
						 "셋째, 그의 아내는 그를 정말로 사랑하지. 몇 년째 얼굴도 못 봤다는 건 중요하지 않아. 드 비트의 딸은 사랑하는 남편을 위해 뭐든 할 수 있는 여자야. 그리고 십칠인 평의회도 그 사실을 받아들일 수밖에 없지.\n"+
						 "오늘의 폭발을 직접 봤지, 선장. 비밀 하나 알려주지: 이런 일이 점점 더 자주 일어나고 있어. 이사들은 언젠가 그가 자신들을 내쫓을까 봐 두려워하지. 그리고 아무것도 할 수 없을 거야. 암스테르담 호는 항구에 있고, 판 도른은 사무실에 귀한 손님이 와 있고, 집에는 장인어른인 네덜란드 연합공화국의 대연금관이 든든하게 버티고 있으니까!\n"+
						 "다시 말해, 국장은 당신의 도움에 대해 아주 후하게 보상할 것이오. 그리고 선박 등록소에서의 특권도 보장해 주겠소.";
			link.l1 = "인상적이군. 너 정말 장사꾼이야, Maarten. 네가 얼마 전 네 사무실의 서비스를 팔던 그 전문성으로 지금은 배신을 팔고 있잖아.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "반 두른이 직접 협상술을 가르쳐줬고, 네가 말하는 걸 진심으로 믿고 있다면 어려울 게 없지.";
			link.l1 = "그래서 나한테 뭘 원하는 거야?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "외부인만 할 수 있는 일이야. 밤에 사무실에 침입해서 거기서 반 도른의 원본 계약서를 찾아. 내가 문은 열어 둘게.";
			link.l1 = "왜 직접 하지 않는 거지? 그리고 내가 지금 당장 네 상관에게 이 모든 걸 말하러 가지 못할 이유라도 있나?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "반 도른은 회사 직원만 빼고 밤에는 누구든 받아들이는 버릇이 있거든. 그러니 네가 이 탑을 이상한 시간에 나가도 아무도 놀라지 않을 거야.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "네 위협 말인데... 이제는 이사님을 만날 수 없어, 오늘은 다른 일정이 잡혀 있거든. "+pchar.quest.ClockTower.date+" "+month+", 맞지? 그때쯤이면 소식의 긴급함도 좀 줄어들 거야. 게다가, 이사장은 밀고자에게 절대 보상을 주지 않아. 그리고 항상 자기 직원들을 보호하지.";
			link.l1 = "네게 편하겠군.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "이건 배신이 아니오, 선장. 우리는 단지 계약을 지키고 회사를 지키고 싶을 뿐이오. 그리고, 그동안 당신이 그렇게 많이 도와준 윌렘스타드도 말이오.";
			link.l1 = "생각해 보지. 하지만 아무것도 약속하지 않겠어.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "더 이상 바랄 게 없소, 선장. 무엇보다도, 당신은 우리 고객이니까. 어떻게 되든, 내가 당신을 찾아내서 사무실 명부에 올린 사람이란 게 정말 자랑스럽소.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "언제나 중앙 동에서 나를 찾을 수 있소. 좋은 하루 되시오.";
			link.l1 = "다시 만날 때까지.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "안녕, "+GetTitle(NPChar, false)+". 소식 있나?";
			link.l1 = "아직 아무것도 없어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", 오늘은 네 날이야. 자, 어서 해봐.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "좋은 하루요, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", 다른 날에 오시기로 되어 있습니다. 다시 뵙게 되어 기쁘겠습니다: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "좋은 하루요, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "감사합니다, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", 꽤 늦으셨군. 사무실은 이미 닫았어.";
					link.l1 = "안녕, "+npchar.name+". 밤에도 운행한다고 들었어.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "맞아. 별별 인간들이 다 오지. 신부들도 가끔 들르곤 해, 크크. 하지만 전부 나를 먼저 거쳐야 해. 그런데 너에 대한 지시는 받은 적 없어.";
			link.l1 = "잠깐, 네가 여기서 하루 종일 경계 서는 거야? 그게 어떻게 가능하지?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "그래. 감독관 나리가 방금 그렇게 지시했어. 어떻게 그 양반이 그걸 해내는지 난 모르겠지만, 그래도 쉴 시간도 있고 일할 시간도 충분해. 그리고 월급도 올려줬으니 불평할 게 없지!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "또 뭐 있나?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "나를 통과시켜야 해. 나는 회사 고위 경영진 소속이야.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(그를 죽여라)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "계속해, 병사.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;
		
		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;
		
		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;
		
		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "어... 나한테 뭘 원하지, 선장 나리? 나는 그냥 평범한 병사일 뿐이야, 아무것도 몰라.";
				link.l1 = "넌 정말 모든 걸 다 알고 있잖아, Johan. 그렇게 겸손하게 굴지 마. 높은 자리에 있는 양반들이 너한테 직접 보고하진 않을지 몰라도, 그들 사이에 악감정이 있다는 소문쯤은 분명 들었을 거 아냐.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "나는 소인배지만, 내 직속 상관을 넘어서지는 않겠소. 미안하오, "+GetTitle(NPChar, true)+".";
				link.l1 = "이 대화는 나중에 다시 하자.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;
		
		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "그렇지, "+GetTitle(NPChar, true)+". 감독관 나리께서 너무 오래 머무르셨군. 폭풍이 몰려오고 있어.";
			link.l1 = "정확히 뭘 들었지?";
			link.l1.go = "ClockTower_Johan_56";
		break;
		
		case "ClockTower_Johan_56":
			dialog.text = "오늘이 아니면 내일이라도 저자가 권력을 잡을까 모두 두려워하고 있지. 이 촌구석엔 너무 큰 인물이야. 저자의 단속 때문에 모두 숨이 막혀, 모든 서류에 자기 결재를 강요하지\n솔직히 말할게, 너도 봤잖아: 암스테르담이 항구에 들어올 때마다, 곧장 불길한 긴장이 감돌아.";
			link.l1 = "내가 이 일을 해결할 수 있어. 하지만 그러려면 날 통과시켜야 해.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "계속해, "+GetTitle(NPChar, true)+". 제발 부탁이오, 나를 망치지만 말아주시오. 만약 미네르 이사 나리께서 알게 되면 내 목이 날아갈 것이고, 먹여 살려야 할 가족도 있소.";
			link.l1 = "최선을 다하겠다.";
			// if (sti(pchar.reputation.nobility) >= 71) link.l1.go = "ClockTower_Johan_58_hint";
			// else link.l1.go = "ClockTower_Johan_NightSuccess";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "넌 괜찮은 놈이야, "+GetTitle(NPChar, true)+". 어쩌면 내가 도와줄 수 있을지도 모르지:\n내가 알기로는, 그 미네르 이사님이 가진 책 중 하나에 열쇠를 보관하고 있어. 그게 뭐에 쓰는 건지는 모르겠지만, 어쩌면 쓸모가 있을지도 몰라.";
			link.l1 = "감사합니다, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
			// if (sti(pchar.reputation.nobility) >= 71) Notification_Reputation(true, 71, "low");
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "멈춰라. 여기는 네덜란드 서인도 회사 소유지다.\n해군 등록부와 기록 보관소다.\n예약한 자만 들어올 수 있다.";
			link.l1 = "나는 "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "약속이 있나? 들어가.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "당신의 약속은 다른 날로 예정되어 있습니다: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "안녕, "+GetTitle(NPChar, false)+". 소식 있나?";
			link.l1 = "그래. 여기 계약서다.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "믿을 수가 없군... 7년 전에 만료됐어!";
			link.l1 = "그래서 이게 네가 필요했던 거야?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "정확해! 이 문서만 있으면 회사에서 그를 합법적으로 소환할 수 있어. 빠져나갈 구멍도, 변명도 없어. 시간 끝났어 — 끝.";
			link.l1 = "이제 뭐하지?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "계약서를 암스테르담으로 보내겠다. \n17인 평의회가 결정을 내릴 것이다. \n두른에게 귀환 명령이 내려질 거다. \n거절하지 못할 거야.";
			link.l1 = "그가 거절하면 어쩌지?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "그럴 수 없어. 그의 아내가 주주이자 대연금관의 딸일지라도, 그녀의 아버지조차 평의회에 맞설 수는 없어. 그리고 카타리나 본인도... 그녀는 10년을 기다렸어. 만약 그가 돌아올 수 있는데도 거부한다는 걸 알게 되면 — 그녀는 견디지 못할 거야.";
			link.l1 = "잔인하군.";
			link.l1.go = "ClockTower_Visser_76";
		break;
		
		case "ClockTower_Visser_76":
			dialog.text = "그래. 하지만 이 방법뿐이야. 고맙소, 선장님. 중요한 일을 해냈소.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;
		
		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "보상은 오백 두블론이오. 그리고 맹세하오: 두세 달 후 내가 국장 자리에 오르면, 그대는 사무국의 모든 서비스를 무제한으로 이용할 수 있을 것이오. 줄 설 필요도, 예약도 없소. 언제든지.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "그리고 너는 요한까지 죽였지. 나는 이미 내가 존경하고 모든 것을 빚진 사람을 배신했어. 이제 이것까지도\n"+
				"네 배에서는 사람이 땔감 취급일지 몰라도, 우리 회사는 직원들을 소중히 여긴다. 그리고 내가 살인에 가담하는 게 역겹군\n"+
				"네 더블룬은 요한의 가족에게 갈 거야, 하지만 거래의 두 번째 조건은 내가 지킬게\n"+
				"내가 약속하지. 두세 달 안에 내가 국장 자리에 오르면, 너는 사무실의 모든 서비스를 무제한으로 이용할 수 있을 거야.";
			}
			link.l1 = "네 말을 믿겠네. 좋은 하루 보내시오.";
			link.l1.go = "ClockTower_Visser_78";
		break;
		
		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;
		
		case "ClockTower_Visser_79":
			dialog.text = "안녕, "+GetTitle(NPChar, false)+". 아직 소식 없어. 걱정 마, 우리 약속 기억하고 있어.";
			link.l1 = "그러길 바란다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;
		
		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"! 들어오시오, 들어오시오. 만나서 반갑소.";
			link.l1 = "임명되신 것을 축하드립니다.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "감사합니다. 십칠인 평의회가 내가 예상한 것보다 더 빨리 결정을 내렸군요.\n계약서가 충분한 증거가 되었습니다.\n반 도른 나리는 사무소 관리에서 해임되었습니다.";
			link.l1 = "그가 어떻게 받아들였지?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "그는 패배하는 법을 아는 사람이야. 그냥 사무실에서 자기 물건 챙기고 떠났지. 하지만 정말로 진 거였을까?\n"+
			"그들은 암스테르담호의 지휘권을 그에게 계속 맡겼지. 그 점에서 회사는 확실히 실수한 거야. 그때 그 배를 그에게 줘서는 안 됐어.\n"+
			"우리가 그를 얕봤어. 결국 일이 더 나빠지지 않길 바란다\n"+
			"그리고 그게 전부가 아니야.";
			link.l1 = "이보다 더 나쁠 수가 있을까?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "반 도른 나리가 누가 그의 사무실에서 계약서를 가져갔는지 알고 있다.";
			link.l1 = "어떻게?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "나 그렇게 쳐다보지 마! 난 아무 말도 안 했어. 그 자식이 스스로 알아낸 거야.";
			link.l1 = "이제 뭐하지?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "이제 그는 너를 적으로 여긴다. 하지만 네가 일곱 연합 주 공화국에 위협이 되지 않는 한 — 그는 너를 건드리지 않을 거다\n"+
			"반 두른은 언제나 사적인 일과 공적인 일을 구분할 줄 알았지. 문제는, 네가 그럴 수 있느냐는 거다.";
			link.l1 = "내가 못 하면 어쩔 건데?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "그럼 그가 널 찾을 거야. 그리고 자기 할 일을 하지. 그에게 구실을 주지 마.";
			link.l1 = "해볼게.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "좋은 하루 되십시오, "+GetTitle(NPChar, false)+". 언제든 우리... 내 사무실을 자유롭게 이용하시오.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", 기다리고 있었습니다. 비서 나리께서 모든 손님을 자유롭게 들여보내라고 명하셨습니다. 예전 규칙이 너무 엄격했다고 하시더군요.";
			link.l1 = "감사합니다, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "영업 시간 중 언제든 들어가시오. 예약은 폐지되었소.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "잠깐 시간 있어?";
			link.l1 = "너를 위해서라면 — 언제나.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "아, 그랬으면 좋겠네요, 선장님. 당신은 인생에 다른 열정이 있잖아요. 지금도, 예를 들면, 당신의 잘생긴 머릿속엔 나 말고 다른 누군가가 자리 잡고 있지, 맞죠?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "내가 그럴 줄 알았지. 내 사람은 내가 잘 알아. 그리고 선원들의 들뜬 기분은, 그보다 더 잘 알지. 그러니 솔직하게 말해봐, 자기야\n"+
			"존경받는 네덜란드 서인도 무역회사의 기함을 우리가 나포하려면 얼마가 들까?";
			link.l1 = "반 도른이 직접 우리를 잡으러 오게 하려면, 내가 빌렘스타트의 적이 되어야겠군.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "아이고, 우리 선장님... 결국 이렇게 되는군. 이번이 처음은 아니잖아?";
			link.l1 = "마치 네가 못마땅해하는 것처럼.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "나는 있는 그대로의 당신을 사랑하게 되었소. 그리고 언제나 당신 편이 될 거요. 다만 우리가... 아니, 당신이 백성들 앞에서 짊어진 책임의 무게를 잊지 마시오.";
			link.l1 = "그래서 알론소가 있는 거지. 그 녀석이 네게 상기시켜 줄 거야.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "우리가 출항하자마자입니다, 선장님.";
			link.l1 = "그럼 지체하지 말자, 자기야.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "찰스? 물어볼 게 있어.";
			link.l1 = "물론이지, Mary. 무슨 일이야?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "나... 나 너 걱정돼, 알겠어. 그 표정 알아. 뭔가 안 좋은 생각하고 있잖아.";
			link.l1 = "헛소리 하지 마. 나도 방금 무슨 생각했는지 기억도 안 나. 네가 어떻게 알겠어?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "나 그냥 알아! 암스테르담 그 배, 내가 봤거든. 멋진 배야. 정말 멋지지. 하지만\n"+
			"넌 이미 다 정했잖아... 예전처럼, 알겠지?";
			link.l1 = "반 두른이 직접 우리를 찾아올 거야, 하지만 그러려면 내가 빌렘스타트의 적이 되어야 해.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "그럴 만한 가치가 있나, Charles?";
			link.l1 = "나도 모르겠어, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "네가 행복하길 바란다, 알겠지. 그래도 알론소에게 이 일에서 널 말려보라고 부탁할 거야, 알겠지!";
			link.l1 = "그 사람답네. 가자, 자기야.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "선장, 우리 얘기 좀 해야겠어.";
			link.l1 = "듣고 있다.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "지금은 안 돼, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "있잖아, 선장, 내 말 좀 끝까지 들어봐야 해. 그게, 어, 뭐랄까\n"+
			"급한 일이다 — 바로 그거야!\n"+
			"그래, 소문에 따르면 네가 직접 회사 이사 중 한 놈을 편한 자리에서 쫓아냈다더군. 그 자식이 앙심을 품고 지금 자기 멋진 프리깃함으로 우리를 쫓고 있대.";
			link.l1 = "그건 너무 과장된 말이야.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "사람들이 얼마나 수다 떠는 걸 좋아하는지 알잖아, 선장. 소문이 일주일만 돌아다녀도 — 반 도른이 어느 플랜터의 딸한테 유혹당했다느니, 암스테르담 호에는 산 자도 죽은 자도 아닌 선원들이 있다느니, 심지어 선창에 코르테스의 보물까지 숨겨져 있다느니 별별 얘기가 다 들릴 거야\n"+
			"하지만 난 진짜 상황이 더 궁금한데. 그래서, 선장, 싸움이 있을 거야, 아니면 말 거야?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;
		
		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;
		
		case "ClockTower_Alonso_4_2":
			dialog.text = "그건 그렇고, 그거 정말 끝내주게 재밌겠지, 나도 부정 못 해! 네덜란드 기함이라니! 하! 우리가... 그 치즈나 먹는 놈들 얼굴 표정이 딱 떠오르네\n";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;
		
		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;
		
		case "ClockTower_Alonso_4_4":
			dialog.text = "토미, 닥쳐.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;
		
		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "싸움이 벌어진다면, 당장은 아닐 거야. 반 두른은 복수를 추구하지 않아, 그는 그런 사람이 아니거든. 먼저 우리가 네덜란드 놈들을 제대로 화나게 만들어야 할 거야.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "ClockTower_Alonso_4_6":
			dialog.text = "고마워, 선장. 그 말에 선원들이 안심하겠어.";
			link.l1 = "너는?";
			link.l1.go = "ClockTower_Alonso_5";
		break;
		
		case "ClockTower_Alonso_5":
			dialog.text = "내가 신경 쓰는 건 선원들을 지키는 거야. 그들 자신으로부터, 그리고... 가능하다면 너로부터도. 어차피 네가 계획한 대로 할 거잖아.";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "계속해, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;
		
		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;
		
		case "ClockTower_Alonso_6":
			dialog.text = "스페인 노새처럼 고집이 세군!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;
		
		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;
		
		case "ClockTower_Alonso_7":
			dialog.text = "주여, 어찌하여 저입니까.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;
		
		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "너무 복잡하게 생각하지 마! 선장님이 멋진 배를 원하신다니까, 우리가 멋진 배 구해드리면 되잖아! 우린 한 배의 선원이야!";
			link.l1 = "계속해, 알론소. 토미, 나가.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". 네 배 — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" 총과\n "+GetMaxCrewQuantity(pchar)+" 선원.";
			link.l1 = "여전히 정확하시군요, 감독관 나리.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "그 칭호는 이제 내 것이 아니야 — 네 덕분이지. 하지만 내가 너를 공격한 게 하찮은 복수심 때문이라고는 생각하지 마. 나는 내 할 일을 했을 뿐이야.\n"+
			"그리고 당연히 실패했지. 내가 성공할 수도 없었어. 한 번 말했잖아, 너는 나보다 훨씬 더 뛰어난 선장이야.";
			link.l1 = "네가 스스로 이 짐을 짊어졌잖아! 네 계약은 7년 전에 끝났어. 그냥 집에 돌아가는 걸 막은 게 뭐였지?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "뭐가 너를 막고 있지? 답은 알고 있잖아, 선장. 너에겐 꿈이 있어. 다른 삶은 없어. 그리고 통제를 놓아버리면—모든 게 무너져버리지.\n"+
			"이 지역에 질서를 가져올 수도 있었지. 끝없는 폭력의 악순환을 멈출 수도 있었고. 내가 손을 놓지만 않았더라면. 오래전에 마땅히 했어야 할 일을 두려움을 짓밟고 했더라면. \n"+
			"이제 감상은 그만두지. 나는 선장으로서나 싸움꾼으로서나 형편없지만, 내 사람을 고르는 눈은 있지. 넌 내 마지막 과업이 되었어, 선장. 오늘로써 선적부에는 선장이 두 명 줄겠군!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "두려움에 대해 뭐라고 했지. 그럼 이 편지를 읽어봐."; // Доступно, если игрок принёс письмо
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "딱 한 놈이다. 싸우자!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "카타리나에서 온 거라고?! 사사로운 감정을 일에 끌어들이다니, 감히 어디서 그런 짓을 해?!";
			link.l1 = "보다시피, 편지는 아직 봉인되어 있소. 기다리고 있네.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...더는 못 기다린다고... 다른 사람에게 갈 거라고... 내가 돌아오지 않으면?!";
			link.l1 = "이미 직위를 잃었지. 네 선원들도 지금 죽어가고 있어. 가족까지 잃을 준비가 됐나?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "이렇게 끝내긴 싫소. 선장님, 내 항복을 받아주시겠소?";
			link.l1 = "그래. 당장 내 배에서 꺼져."; // Отпускает, повышает честь
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "아니. 그건 사형수에게 주는 마지막 예의였지. 전투다!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "그럼 승리를 축하하오, 선장 "+GetFullName(pchar)+". 오늘 선원 명부에는 선장이 한 명 줄겠군.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE); // нужно два раза, чтобы сработало...
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". 네가 impudently 여기 올 줄은 몰랐는데.";
			link.l1 = "왜 안 되지? 난 아직도 네 고객이고, 사무실의 서비스가 필요하거든.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "서비스? 서비스라고?! 네가 무슨 짓을 했는지 알고도? 너는 존경받는 네덜란드 서인도 회사의 적이야! 다른 선장이 네 자리 차지할 거다!";
			link.l1 = "그럴 리 없지. 내가 반 도른의 서류에서 뭘 찾았는지 봐.";
			link.l1.go = "ClockTower_Visser_103";
		break;
		
		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "네 전임자는 이 문서를 사용하는 것이 자신의 품위를 떨어뜨린다고 여겼지 — 의자가 흔들리기 시작했을 때조차도.";
			link.l1.go = "ClockTower_Visser_104";
			// отдаём Ключ к Маартену Виссеру
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;
		
		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "운이 좋았군, 그렇게 훌륭한 상관이 있어서. 그런 장난을 쳤으면, 잘해야 재판에 넘겨졌을 거야.";
			link.l1.go = "ClockTower_Visser_105";
		break;
		
		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "너는 장사꾼이잖아. 내가 무슨 말을 하려는지 알겠지.";
			link.l1.go = "ClockTower_Visser_106";
		break;
		
		case "ClockTower_Visser_106":
			dialog.text = "너... 네 기록이 다시 복구됐다.";
			link.l1 = "아, 마르텐. 너는 원장이 모든 걸 줬는데도 그 자리를 차지하고 싶었지. 그는 너를 재판에서 구해줬고, 네게 알릴 필요조차 없다고 생각했어.";
			link.l1.go = "ClockTower_Visser_107";
		break;
		
		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "이 작은 죄가 너를 결코 더 높이 오르지 못하게 하고, 끊임없는 두려움 속에 살게 만들 거야.";
			link.l1.go = "ClockTower_Visser_108";
		break;
		
		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "이제 네가 이곳에 사슬로 묶일 차례다. 하지만 분명히 반 도른처럼 충직한 부하 따위는 없겠지.";
			link.l1.go = "ClockTower_Visser_109";
		break;
		
		case "ClockTower_Visser_109":
			dialog.text = "그만해. 정말 나를 끝장내고 싶은 거야?!";
			link.l1 = "그렇진 않아. 내 새 배를 등록부에 올려 줬으면 해. 오해가 생기지 않게 말이야.";
			link.l1.go = "ClockTower_Visser_110";
		break;
		
		case "ClockTower_Visser_110":
			dialog.text = "네 배는 '"+GetShipName("Amsterdam")+"'. DWIC 기함이야. 그게 그냥... 다시 등록될 리가 없지.'";
			link.l1 = "왜 안 되겠어? 종이는 뭐든 다 견디잖아. 네네 방식이 원래 그런 거 아니야?";
			link.l1.go = "ClockTower_Visser_111";
		break;
		
		case "ClockTower_Visser_111":
			dialog.text = "세상에, 아무리 그래도 한계는 있지!";
			link.l1 = "나는 이곳의 힘을 믿어. 너도 그래야 해.";
			link.l1.go = "ClockTower_Visser_112";
		break;
		
		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;
		
		case "ClockTower_Visser_113":
			dialog.text = "성함이 어떻게 되십니까?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;
		
		case "ClockTower_Visser_114":
			dialog.text = "신분?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "네 배 이름이 뭐지?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "선박 종류?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "포의 수는?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "선원 수?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "좋아. 이제 여기에 서명해. 그리고 여기도. 여기도 마찬가지야.";
			link.l1 = "그게 다야?";
			link.l1.go = "ClockTower_Visser_120";
		break;
		
		case "ClockTower_Visser_120":
			dialog.text = "그거야.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;
		
		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "뭔가 말을 빼먹었군.";
			link.l1.go = "ClockTower_Visser_122";
		break;
		
		case "ClockTower_Visser_122":
			dialog.text = "\n"+
			"존경받는 네덜란드 서인도 회사 해군 등록부에 오신 것을 환영합니다.";
			link.l1 = "다시 만날 때까지, 감독관 나리.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". 오늘 저와 제 사무실이 어떻게 도와드릴까요?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "다시 보게 되어 반갑군, "+GetTitle(NPChar, false)+"! 언제나 당신을 위해 준비되어 있소. 오늘은 무엇이 궁금하오?\n";
				}
				else
				{
					dialog.text = "그래? 오늘은 뭐가 궁금하지?";
				}
			}
			link.l1 = "내 배를 점검해 줄 수 있겠소? 성능을 좀 더 개선하고 싶네.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "내 배의 전문화가 마음에 들지 않아. 새 서류를 구해줄 수 있겠어?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "내 배를 선적 등록부에 올려 줄 수 있겠나? 해적이든 사냥꾼이든 두 번 생각하게 될 거야.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "항구 보관소에 내 배들을 보험에 들고 싶어. 지금 있는 배들도, 앞으로 가질 배들도.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "너 해적 선장들의 항해일지도 받지?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "오늘은 아닐지도 모르겠군. 좋은 하루 보내시오.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// --> Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "비용은 배의 크기에 따라 달라진다. 어떤 선박을 말하는 거지?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}
 
			if (n == 0)
			{
				dialog.text = "안타깝지만, 감사는 각 선박마다 한 번만 제공되는 서비스요. 다른 궁금한 점 있나?";
				link.l1 = "다음에 하자.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "어디 보자... 이건 비용이 들겠군 " + n + " 두블룬.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "진행하라.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "...그래도, 다음에 하자.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "유감이지만 거절해야겠소. 기록부에 따르면, 그대의 배는 이미 오래전에 바다의 악마에게 넘어갔다 하니, 세월의 유령을 펜 한 번 휘두른다고 되돌릴 수는 없지. 우리가 협력하려면 먼저 그 배를 복원해야 하오. 이슬라 테소로에 그런 일을 맡을 만한 장인이 있다고들 하더군.";
				link.l1 = "알겠어, 고마워.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$선박은 이미 업그레이드되었다";
				link.l1 = "감사합니다.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "끝났다.";
			link.l1 = "감사합니다.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Аудит

		// --> Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "비용은 배의 크기에 따라 달라진다. 어떤 선박을 말하는 거지?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "안타깝지만, 등록은 각 선박마다 한 번만 가능한 서비스요. 다른 필요한 게 있소?";
				link.l1 = "다음에 하자.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "자, 보자... 이건 비용이 들겠군 " + n + " 도블론.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "진행하라.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "...그래도, 다음에 하자.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "유감이지만 거절해야겠소. 기록에 따르면, 당신 배는 이미 여러 해 전에 바다 악마에게 넘어갔다고 되어 있소. 그런 세월의 유령은 펜 한 번 움직인다고 되돌릴 수 있는 게 아니오. 우리가 협력하기 전에, 먼저 그 배를 되살려야 하오. 이슬라 테소로에 그런 일을 맡을 수 있는 장인이 있다고들 하더군.";
				link.l1 = "알겠어, 고마워.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$배는 이미 업그레이드되었다";
				link.l1 = "감사합니다.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "끝났다.";
			link.l1 = "감사합니다.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Улучшение специализации

		// --> Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "비용은 배의 크기에 따라 달라져. 어떤 선박을 말하는 거지?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "흠. 네 배는 항구에 안 보이는데.";
				link.l1 = "다음에 하자.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "보자... 이건 비용이 들겠군 " + n + " 두블룬.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "진행하라.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "...그래도... 다음에 하자.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "유감이지만, 그건 불가능하오. 당신의 배는 전설이 깃든 유일무이한 선박이오. 이런 경우에는 서류 한 장으로는 아무 힘도 쓸 수 없소.";
				link.l1 = "알겠어, 고마워.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "무슨 전문화를 말하는 거지? 네 배는 만능이야, 특별한 특징이 없어.";
				link.l1 = "알려줘서 고마워.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			// тут можно обработать другие причины отказа, но на данный момент таковых не будет
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;
		// <-- Смена трейта корабля

		// --> Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "자, 보자... 이건 비용이 들겠군 " + n + " 두블룬.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "진행하라.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "...그래, 다음에 하자.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "끝났다.";
			link.l1 = "감사합니다.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;
		// <-- Страховка
		
		// Награда за пиратов (раз в сутки) -->
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "전적으로 맞아. 보상은 항해일지의 개수와 그 주인들의 위험도에 따라 달라지지.\n" + 
						  "통나무를 몇 개나 가져왔지?"
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;
		
		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "회사에서 당신의 노고에 감사드립니다. 받을 돈이 있습니다 " + JournalsCost() + " 두블룬입니다. 여기 받으시고 서명해 주십시오"
			link.l1 = "감사합니다.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;
		// <-- Награда за пиратов

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "항구에 네 배가 안 보여.";
	link.l1 = "다음에 하자.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
