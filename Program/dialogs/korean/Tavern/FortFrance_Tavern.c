// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안, 벌써 세 번째로 뭔가를 물어보는군...","질문이 더 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","그래, 정말 이번이 세 번째야...","아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "나리, 일거리를 찾고 있는데, 혹시 할 만한 일이 있소?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "네가 시킨 일을 끝냈어. 럼주가 실린 장주정이 르 프랑수아 만에 도착해서 네 사람들에게 넘겨줬다.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "네 방 중 하나를 이틀이나 사흘 정도 빌려야겠어. 내 배에 부상당한 놈이 있는데, 좀 쉬면서 회복해야 하거든.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "말해 봐, 내가 방을 빌려준 그 친구—떠났나? 나를 기다리겠다고 약속했는데, 방이 비어 있더군.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "내 부하들을 위해 파티를 열려고 한다. 이미 알고 있겠지?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "우리 축하를 위해 필요한 건 전부 가져왔어.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "일거리? 흠... 넌 머리가 좀 돌아가는 녀석처럼 보이는군, 꼬마야. 너한테 줄 만한 게 있을지도 모르지\n이 일은 쉬워 보일지 몰라도 책임감과 머리가 필요해. 저 멍청이들한텐 절대 맡길 수 없지, 분명 망쳐버릴 테니까...";
			link.l1 = "이봐, 도대체 나한테 뭘 맡기려고 하는지 솔직히 말해줄 수 있겠어? 맹세컨대, 절대 실망시키지 않을 거야. 아니면 최소한 최선을 다할게.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = "좋아. 내 선술집에 고급 자메이카 럼주 몇 상자를 운반해 줄 사람이 필요해. 문제는, 수입 관세 때문에 이익이 줄고 내 단골 손님들은 목이 말라 있으니, 세관원들을 피해서 영리하게 움직여야 한다는 거지. '고스트'라는 러거선이 오늘 밤 마르티니크 근처에 도착할 거야\n그들은 라망텐 만에서 멀지 않은 곳에 닻을 내릴 거다. 네가 그 배를 찾아서 올라타야 해. 내가 너에게 노젓는 보트 한 척과 선원 다섯 명을 줄 테니, 그들은 네 명령을 따를 거야\n배에 올라타면 어떤 남자가 다가올 거다. 그에게 암호를 말해야 해: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\n정답은 '럼 한잔 하지, 뱃사람?'이 될 거야. 기회는 딱 한 번뿐이니, 잘 적어두고 실수하지 마라. 틀리면 거래는 끝이니까. 그래서 네놈이 데리고 다니는 멍청이들한테는 맡길 수 없는 거다. 암호를 다시 말해 봐.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "좋아. 몇 번 더 스스로 반복해 보거나, 더 좋게는 어딘가에 적어 두는 게 좋겠군. 너가 루거 선장에게 암호를 말하면 럼 상자들이 롱보트에 실릴 거야. 그 롱보트를 해적 정착지 르 프랑수아 만까지 직접 몰고 가면 돼 - 거기서 환영받을 거야.\n그게 전부야. 르 프랑수아 만에서 생 피에르까지는 걸어서 갈 수 있어 - 롱보트는 만에 남겨 두면 된다. 일이 끝나면 오천 피스의 에잇을 주지.";
			link.l1 = "밀수라니, 짜릿하고 돈도 되겠군. 네 말대로 할게. 장선은 어디 있지?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "그래서, 나보고 밀수나 하라고? 흠... 있잖아, 내 이름에 먹칠할 순 없어. 미안하지만, 아무 말도 못 들은 걸로 해 주게.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "원하시는 대로 하겠습니다, 나리. 다른 일은 없습니다.";
			link.l1 = "알겠소. 그럼 행운을 빌겠소, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "저녁 7시에 장선이 부두에 있을 거야. 장선에 탄 선원들은 능숙하니, 너는 빠르게 루거선에 도착할 수 있을 거다. 전체 임무는 네 시간 이상 걸리지 않을 거야 - 분명 저녁 11시에는 생피에르로 돌아올 수 있을 거다. 이 망원경을 가져가, 쓰레기 같은 물건이지만 없는 것보단 낫지. 라망텐 해변은 섬의 북쪽에 있으니, 항구를 나설 때는 북쪽으로 똑바로 나아가라. 행운을 빈다!\n";
			link.l1 = "알겠어. 곧 보자, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "훌륭해! 자네라면 믿을 수 있을 줄 알았지. 힘들었나?";
			link.l1 = "글쎄, 그게 얼마나 힘든지 어떻게 정의하느냐에 따라 다르지...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "자, 여기 보상이다. 오천 페소지. 망원경은 가져도 돼. 그리고 또 하나 작은 선물이 있어—이 세 병의 럼주도 받아라. 한 번 맛보면 왜 이렇게 인기가 많은지 알게 될 거다.";
			link.l1 = "고마워! 함께 일해서 즐거웠어! 나중에 또 보자!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "문제없어, 방 하나 있지. 50페소면 사흘 동안 네 거야.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "여기 있다.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "재무관에게 가서 돈을 받아오고 곧 돌아오겠소.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "그가 혼자 일어나서 방을 나갔다고는 못 하겠소, 나리. 어제 여기 몇몇 사람들이 들렀지. 그중 하나는 키 크고 마른 외눈박이 남자였는데, 딱 봐도 악당이더군. 그리고 또 한 명은 혀짤배기였는데, 카스티야 사람처럼 보였소. 나는 그냥 놀랐을 뿐인데, 그 혀짤배기가 날 쏘아보더군... 마치 이를 짓밟기 전에 보는 눈빛처럼 말이오. 그래서 그들이 당신 친구에 대해 물었고... 나는 말해줬소. 내가 달리 뭘 할 수 있었겠소?";
			link.l1 = "알고 있어, "+npchar.name+", 너는 영웅이 아니지, 맞아. 또 뭘 봤어? 그놈들은 어디로 갔지?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "그게 전부야... 잠깐, 아니지! 기다려, 외눈박이 사내가 마차에 대해 뭔가 말했어. 아마 그 자들이 마차를 타고 네 친구를 섬 반대편까지 끌고 간 것 같아. 이게 다야, 나리, 맹세해... 경비를 부르고 싶지만, 그 혀 짧은 놈이 떠나기 전에 내 아내가 예쁘다고 하더라고... 알겠지? 내가 이 모든 걸 말했다는 걸 들키면, 그 자들이...\n";
			if (pchar.money >= 1000)
			{
				link.l1 = "겁낼 것 없어, 내가 놈들에게 들려줄 건 총알뿐이야. 정말 큰 도움을 줬군, 고맙다. 자, 보상으로 1000페소 받아라.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "별건 아니지만, 그래도 고맙다. 다음엔 경비병을 부르고 그렇게 겁쟁이처럼 굴지 마라.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "감사합니다, 나리. 당신 친구는 거의 회복했다고 장담할 수 있습니다. 적어도 혼자 걸어 다녔으니까요. 그리고 그 조용한 네덜란드인 한 명, 그가 바로 그때 밖에서 들어왔는데, 그 난장판을 보고는 다시 밖으로 뛰쳐나가 그냥 사라져 버렸습니다.";
			link.l1 = "그 자는 아마 눈에 띄는 첫 배를 타고 이미 떠났을 거요. 정보 고맙소, 이제 나는 가야겠군.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "모든 남자가 칼을 뽑아 들었다고 해서 영웅이 되는 건 아니오, 선장.";
			link.l1 = "흠... 그건 그 남자의 선택이지.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "그래, 네 조수가 다녀갔지. 하지만 그녀에게도 말했고, 너한테도 다시 말하마 - 나는 취한 선원들로 북적이는 건 익숙하지만, 너희 파티가 어떻게 끝나는지는 잘 알지. 남는 건 스페인 테르시오가 들이닥친 뒤의 앤트워프 꼴이 될 거야. 벽이라도 남아 있으면 다행이지. 그러니 군중들이 싸우게 만들고 싶다면, 이미 가져온 것 외에 환불 불가 보증금을 더 받아야겠어. 혹시 무슨 일이 생길 때를 대비해서 말이지.";
			link.l1 = "이 교활한 여우 같으니! 나는 수년간 바다의 사내들과 술을 마셔 왔고, 온갖... 주점들을 다녀 봤지. 내가 가져온 돈이면 네 선술집을 아예 새로 지을 수도 있을 거다! 지금 상황을 이용하려는 거지? 좋아, 난 결혼식에 가야 하고 이런 사소한 일로 신경 쓸 기분도 아니니 - 얼마면 되겠어?\n";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "10만 피스 오브 에잇만 더 있으면 충분해. 걱정 마, 내가 최선을 다해 준비할 테니까. 네 부하들은 이 파티를 오래도록 기억하게 될 거야, 내 말 명심해!";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "정말로 좀 더 힘을 내야 하오 - 오늘은 특별한 날이니까. 그리고 그래, 축제가 끝난 뒤에는 네 술집이 불타버려도 나한테 와서 불평하지 마라.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "벌써 왕의 결혼식을 준비하는 기분이군! 잠깐만, 금방 돌아올게.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "네 놈 부하들이 이 잔치를 오래도록 기억하게 될 거다, 내 말 명심해!";
			link.l1 = "정말 제대로 해 봐야 해 – 오늘은 특별한 날이거든. 내 녀석들이 실수로 네 선술집을 태워도 나한테 울며 오지 마라.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
