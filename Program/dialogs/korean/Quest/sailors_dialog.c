// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "우리 선장한테 말해. 난 해줄 말 없어.";
			Link.l1 = "좋아.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "우리 선장한테 말해 봐. 난 해줄 말 없어.";
			Link.l1 = "좋아.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "나리, 누구를 찾고 계십니까?";
					Link.l1 = "그래, 이봐. 선장 좀 볼 수 있을까?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "우리 선장을 찾고 있다면, 그는 최근에 상륙했어.";
					Link.l1 = "Fine";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("오, 혼자 여기 왔구나. 하! 그렇다면 우리 선장한테 가 봐. 네 한심한 짓거리에 대해 말씀드려라...","이런 젠장, 넌 미친 것 같구나, 친구. 우리 선장에게 가 봐, 그분이 너랑 얘기해 줄 거야.");
				Link.l1 = "안타깝군...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "항구에서 그를 찾아보는 게 좋겠어.";
			Link.l1 = "고맙다, 친구야.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "음, 진짜 심각한 난장판이었어, 선장! 우린 평소처럼 선술집에서 술 마시고 있었는데, 갑자기 비명 소리가 들렸지. 그래서 선술집 밖으로 뛰쳐나갔더니, 놈들이 당신을 체포하려고 하고 있더라고. 젠장할 것들! 그래서 우린 이 적대적인 항구를 떠나기로 했어.";
			link.l1 = "그래, 확실히 어떤 사람들은 정의를 참 이상하게 생각하지.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "선장님! 그렇게 초조해하지 마십시오! 조용히 빠져나갈 방법이 없다는 건 뻔했으니, 우리는 현지 은행가를 찾아가 그의 금고를 확인하기로 했습니다. 여기 선장님의 몫입니다 - "+sti(pchar.questTemp.ReasonToFast.p9)+" 페소...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "선장님! 그렇게 초조해하지 마십시오! 조용히 빠져나갈 방법이 없다는 건 분명했으니, 저희는 현지 은행가를 찾아가 그의 금고를 확인하기로 했습니다. 전당포 상자에는 훌륭한 검도 있었습니다. 여기 선장님의 몫입니다 - "+sti(pchar.questTemp.ReasonToFast.p9)+" 페소와 검...";
			}		
			link.l1 = "잘했어, 이 녀석들! 잘했다! 내가 너희들이 자랑스럽다.";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "선장님, 당신 친구가 도망쳤습니다.";
			link.l1 = "어떤 친구?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "그래, 자네가 감옥에서 데려온 그 친구 말이야.";
			link.l1 = "도대체 어떻게 그놈을 놓친 거야?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "우리 잘못이 아니었어요, 선장님. 그가 변소를 통해 바다로 뛰어내렸어요... 우리가 쏘려고 했지만, 거긴 너무 어두웠어요...";
			link.l1 = "젠장! 너희들 정말 제멋대로구나! 전부 상륙시켜서 사탕수수 밭에나 보내버릴 거다! 이렇게 귀한 거물을 잃다니! 믿을 수가 없군!";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "선장님, 용서해 주십시오, 저희 잘못입니다 – 죄수가 도망쳤습니다.";
			link.l1 = "무슨 죄수? 누가 도망쳤다는 거야?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "음, 아, 그 사람 이름을 잊어버렸네, "+pchar.GenQuest.Hold_GenQuest.CapName+", 맞지?";
			link.l1 = "젠장! 어디 보고 있었어?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "그가 화물창에서 나와 불워크를 뛰어넘었어. 우리는 소란을 피하지 않으려고 쏘지 않았지, 그리고 우리가 보트를 준비하는 사이에 그 놈은 그 빌어먹을 어부들에게 구출당했어.";
			link.l1 = "내가 너희한테 왜 돈을 주는 거냐! 당장 당직 책임자를 매질하고, 일주일 동안 럼도 금지해라. 모두 각오해! 이제 닻을 올린다...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "안녕하십니까, 선장님. 항해 중에 아무런 사고도 없었습니다...";
			link.l1 = "좋아, 좋아, 알겠어.... 우리 화물창에 죄수가 한 명 있어. 이름은 "+pchar.GenQuest.Hold_GenQuest.CapName+". 몇 명 데리고 그를 항구까지 호위하라. 이제 그는 자유다.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "정말로 그 자가 자유란 말인가? 우리가 그를 작은 배에 태워 보내야 하나?";
			link.l1 = "아니, 씨발 거북이 타고 왔겠냐... 내가 충분히 말했잖아. 그리고 서둘러! 썰물이 시작되기 전에 닻을 올려야 해.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "선장님, 배에 아무도 없습니다! 뭔가 크게 잘못됐습니다... 토미가 조타실에서 고양이를 봤다고 했는데, 살아 있는 건 그것뿐이었어요...";
			Link.l1 = "멍청아, 고양이한테 영혼이란 없어. 저 녀석은 교회에 오래 안 갔거나, 아예 한 번도 안 가본 것 같군. \n선장 선실에 가봤나? 항해일지가 필요해.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "아니, 그들도 영혼이 있어. 항해일지도 없었고, 항해 도구 하나도 없었어. 심지어 단 한 척의 장정선도 없었지...";
			Link.l1 = "아니야. 폭풍에 쫓겨난 건가?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "그렇습니다, 선장님. 고양이도 영혼이 있죠. 선장님, 장정선이 끊어졌고 조타실 바닥에서 칼 한 자루를 발견했습니다. 녹슬고 피가 묻어 있습니다. 여기, 한번 보십시오...\n";
			Link.l1 = "이런 쓰레기 그만 줘, 다 버리고, 고양이 얘기도 그만해, 젠장! 창고 확인하고 떠나자... 아, 뭔가 아주 잘못됐는데, 영 마음에 안 들어...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "선장님, 이곳이 영 불길한 느낌이 듭니다... 이제 우리 떠날 때가 된 것 아닙니까?";
					Link.l1 = "그래... 배의 보트로 가.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "선장님, 이 배를 항구로 가져가실 생각이라면 저는 이 이상 이 낯선 배에 머물지 않겠소. 차라리 바다에 몸을 던지겠소.";
					Link.l1 = "나는 그걸 하고 싶지 않아... 나도 좀 두렵거든...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "가라앉혀 버릴까요, 선장님?";
					Link.l1 = "여기 머무는 죽은 선원들의 영혼이 우리의 악몽에 찾아오게 하자는 거야?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "이런, 맙소사! 선장님... 왜 그런 말씀을 하십니까?";
			Link.l1 = "겁먹지 마, 농담이었어... 배의 보트로 가. 그리고 네 말이 맞을지도 모르지, 고양이에게도 정말 영혼이 있을 수도 있으니까...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("두목한테 말해. 난 너한테 할 말 없어.","나는 내 자리에서 근무 중이오. 모든 질문은 요새 사령관에게 하시오.");
			Link.l1 = "좋아.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("나 지금 정말 바쁘다. 내버려 둬.","내 일 방해하지 마라. 할 말 없다.");
			Link.l1 = "안됐군...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("모건이 너한테 '한마디 할 게 있다'고 하더라... 그는 여기 어딘가, 갑판에 있어.","헤, 모건을 찾아. 나쁜 소식이 널 기다리고 있어...");
			Link.l1 = "좋아.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
