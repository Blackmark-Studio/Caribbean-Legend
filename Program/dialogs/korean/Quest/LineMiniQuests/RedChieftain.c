void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "이건 버그야. 개발자들에게 알려 줘.";
			link.l1 = "내가 할게!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "어떻게 지내나, 창백한 얼굴이여. 큰 카누의 선장인 것을 보았네. 나는 카나우리다. 나는 카이만의 족장이며, 강대한 아라와크 부족의 우두머리다. 너와 이야기하고 싶다.";
			link.l1 = "듣고 있어, 대장. 무슨 골치 아픈 일이 날 찾아왔지?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "나한테 뭘 원하지, 이 더러운 붉은 피부 원숭이야? 네 정글로 돌아가서 내게 부탁 따윈 하지 마라.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "구-우! 하얀 선장은 예의도 안 배웠나? 나는 제안을 했지. 너는 엄청난 와움펌을 벌 수 있었는데, 이제 간다. 잘 있어라, 창백한 얼굴.";
			link.l1 = "가, 꺼져...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "하얀 형제여, 부엉이처럼 통찰력 있고, 뱀처럼 교활하구나. 인디언에게 곧 문제가 닥쳐온다. 백인들의 아주 큰 카누가 내 마을에 왔다네.\n그들은 많은 카이만, 내 동족을 잡아 그들의 카누에 태우고 모든 물의 어머니로 데려갔지...";
			link.l1 = "잠깐만... 네 사람들을 배에서 온 백인들에게 노예로 잡혀갔다고 말하는 거야?";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "네 말이 맞아, 하얀 형제여. 저 창백한 얼굴들이 네 친구가 아니라는 걸 나도 알아. 이 잔인한 스페인 부족의 백인들 말이야. 내 사람들을 데려가 버리지. 하지만 내가 그들을 찾아내지. 스페인 놈들은 인디언들에게 새벽부터 해질 때까지 일하게 하고, 물의 어머니 속 깊은 곳까지 잠수하게 해. 신의 눈물이 담긴 조개껍데기를 찾으라고 말이지.";
			link.l1 = "진주 채취라니... 그건 정말 고된 일이야.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "네 말이 맞아, 백인 형제여. 나도 그 자들이 네 친구가 아니라는 걸 알아. 그들은 영국 부족이지. 내 사람들을 데려가. 하지만 내가 그들을 찾아내지. 영국인들은 인디언들에게 새벽부터 해 질 때까지 일하게 하고, 물의 어머니 깊은 곳까지 잠수하게 해. 신의 눈물이 담긴 조개껍데기를 찾으라고 시키지.";
			link.l1 = "진주 채취라니... 이거 정말 힘든 일이야.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "인디언들은 노예 생활로 병들고 죽는다. 백인들은 인디언들에게 아무런 연민도 없다. 채찍과 권총이야말로 백인들이 인디언들에게 내세우는 법이다. 나는 늙었다. 더 이상 싸울 남자들도 남아 있지 않다. 카이만 아라와크족은 평화로운 민족이오, 우리가 평화의 파이프를 발명했소. 나는 당신에게 부탁하오, 백인 형제여, 당신의 채찍과 권총을 악한 백인들에게 겨누어 아라와크 인디언들을 구해주시오.";
			link.l1 = "나한테 전쟁을 선포하라고 하는 건가? 이해해야지, 두목, 내 자원은 한정돼 있어.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "전쟁하러 가지 마라. 나는 자유로운 인디언이다. 내 부족이다. 우리가 가진 신의 눈물을 모두 카누에 담아 주겠다. 나쁜 백인 놈 죽이고, 인디언을 도우면 신의 눈물을 얻을 수 있다. 그걸 팔면 와움펌을 많이 벌 수 있다. 와움펌 한가득이다\n";
			link.l1 = "아, 이제 알겠군. 아니, 카나우리, 나는 도와줄 수 없어. 지금은 안 돼 - 내 배가 수리가 필요하고, 보급품도 하나도 남지 않았거든...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "그렇다면 기꺼이 도와드리겠소. 세부 사항을 이야기해 봅시다. 네 사람들은 어디 있지? 이미 찾았다고 했잖아...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "구-우! 기다릴 수 있지, 하얀 형제여... 나는 이 항구에 한 달 더 머물며 우리 부족을 지켜줄 보호자를 찾을 거야. 준비되면 여기서 나를 찾아.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "돌아왔군, 백인 형제? 나쁜 놈들을 벌주고 인디언을 구하는 데 도와줄 건가?";
			link.l1 = "언제든 준비됐지.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "아직 준비를 더 해야 해.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "나는 여기 있을게, 백인 형제.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "네가 동의해 줘서 정말 기쁘다, 백인 형제야!";
			link.l1 = "자세한 얘기를 해보자, Canauri. 네 사람들이 어디 있지? 이미 찾았다고 했잖아...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "그들은 스페인 진영인 쿠마나 근처의 카루파노 만에 진을 치고 있어. 매일 배를 타고 바다로 나가서, 물속으로 잠수하지, 아주 깊이, 깊이...";
				link.l1 = "알겠소. 그리고 스페인 놈들이 저들이 잠수하는 동안 지켜보고 있단 말이오?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "그들은 블루웰드라고 불리는 영국인 야영지 근처의 페를라스 곶에 야영지를 차린다네.\n매일 배를 타고 바다로 나가, 아주 깊이, 깊이 잠수하지...";
				link.l1 = "알겠소. 그리고 물론, 영국 놈들이 그들을 감시하고 있겠지?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "그래, 불붙은 막대기랑 큰 칼을 든 창백한 얼굴 두 무리가 큰 카누를 타고 왔어. 해변에 있는 그들의 야영지도 경비가 삼엄해서 인디언은 도망칠 수 없어.";
			link.l1 = "무슨 종류의 배였지? 설명할 수 있나? 크기는 얼마나 됐지? 돛은 어떤 모양이었나?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "이 카누는 크지만, 카나우리보다 더 큰 것도 본 적 있어. 앞 돛이 아주, 아주 기울어져 있어서 이렇게 세 면이 돼. (그가 흙바닥에 라틴 세일 세 개와 사다리꼴 돛 하나를 그린다) 위는 좁고, 아래는 넓어.";
			link.l1 = "소리가 나고 생김새도 스쿠너 같은데...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "카나우리 그 말 모른다. 창백한 얼굴, 다른 카누를 보면 아주 조심해야 해. 그들은 인디언을 상륙시키고, 다른 카누가 떠날 때까지 기다린다.";
			link.l1 = "조심성 많은 개자식들... 어떻게 다가가야 하지?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "창백한 얼굴 형제가 작은 카누를 타면 해안 가까이 몰래 갈 수 있다네. 내가 길을 알려주지. 하지만 작은 카누 하나만 가져와야 해. 아니면 창백한 얼굴 개들이 보고 인디언을 배에서 쫓아내 정글로 몰아넣을 거야...";
			link.l1 = "알겠어. 이번 작전엔 루거선이나 슬루프가 필요하겠군. 좋아. 슬루프로 슈너 두 척을 상대하라니... 이런... 이게 쉬울 줄 알았는데!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "가자, 하얀 형제. 달이 채 차기 전에 시간이 얼마 남지 않았어.";
			link.l1 = "그래. 내 배에 타, 족장. 시간 낭비하지 말자!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "고마워, 백인 형제여! 너 덕분에 케이맨 아라와크 부족이 구원받았어! 우리는 너에게 큰 빚을 졌다네. 이제 창백한 얼굴의 개들은 사라졌고, 인디언들은 정글에서 자유롭게 달릴 수 있어. 신들의 눈물이 남아 있는 모든 것을 배에서 네게 주겠네.";
			link.l1 = "그래, 어디 한번 네가 뭘 가져왔는지 보자...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("The Chief has given you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("신들의 눈물이 그대의 것이라니 기쁘구나, 아라와크의 형제여!","인디언, 고맙다, 용감한 창백이!","우리의 잡은 고기 가져가라, 하얀 형제!");
			link.l1 = LinkRandPhrase("도와줄 수 있어서 기뻐!","고맙다, 붉은 피부 형제여!","대단하군!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "카나우리, 다시 한 번 고맙다네, 창백한 얼굴 형제여! 자네가 인디언들과 함께 모든 카누를 구해줬지! 카나우리에게는 모든 카누를 지키는 것이 매우 중요하다네, 왜냐하면 자네가 악한 창백한 얼굴들이 노예로 끌고 간 카나우리의 손자도 구해줬으니까. 내 손자는 어릴 때 수영을 무척 좋아했기에, 카나우리는 그가 물에 빠지지 않도록 이 부적을 주었지. 이제 손자는 더 이상 수영을 원하지 않아서, 이 부적을 나에게 돌려주었고, 내가 자네에게 주라고 했네, 창백한 얼굴 형제여. 신들의 눈물과 이 선물이 아라와크 한 사람의 생명에 대한 충분한 보상이 되길 바라네. 이제 우리는 작별을 고하네 - 우리 고향 마을로 돌아갈 시간이 되었으니.";
				link.l1 = "행운을 빌어, 쿠나우리! 네 손자가 살아남아서 정말 기쁘다! 이런 불행이 다시는 네게 닥치지 않기를 기도할게!";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "카나우리, 다시 한 번 고맙다네, 창백한 얼굴의 형제여! 신들의 눈물이 인디언들의 목숨에 대한 충분한 보상이 되기를 바라네. 이제 잘 있게, 우리는 우리 고향 마을로 돌아가네.";
				link.l1 = "행운을 빌어, 쿠나우리! 다시는 노예가 되지 마라!";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received Seeker's obereg");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
