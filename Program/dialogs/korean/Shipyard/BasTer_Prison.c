// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해라, 듣고 있다.";
			link.l1 = "내가 착각했군. 잘 가라.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "인디언 한 명이 체포되어 있다네. 그자는 모스크바인 파데이에게 잡혔지. 내가 그와 이야기해도 되겠나?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "말해 보시오, 정말 이 인디언을 교수형에 처할 생각이오? 그렇게 작은 죄에 너무 가혹한 처벌 아닌가?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "또 나요, 교도소장. 모스크바인 파데이가 인디언을 풀어달라고 탄원서를 썼소. 여기 있소.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "지역 상점 주인의 부탁으로 왔소, 그의 이름은 "+pchar.questTemp.Shadowtrader.Tradername+". 그가 이 편지를 전해 달라고 했소.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "또 나야. 내가 결정적인 증거를 가지고 있어. "+pchar.questTemp.Shadowtrader.Tradername+" 맞다.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Longway라는 이름의 남자를 찾고 있소. 당신도 그를 찾고 있다고 들었소, 장교 나리. 혹시 그를 찾는 데 성과가 있었소, 아니면 단서라도 잡았소?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "아-아, 파데이가 자기 이야기를 했군? 내가 그를 보는 걸 막을 이유는 없네, 나리. 그 붉은 피부 놈을 보러 온 사람이 자네가 처음이 아니야. 뭐, 열흘 뒤면 모든 시민이 그를 구경할 수 있을 거야. 우리가 그놈을 태양 아래 매달아 말릴 테니까...";
			link.l1 = "그래서, 감옥에 들어가도 되나?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "이미 말했듯이, '그걸 금지할 이유가 없소.' 어서 가시오.";
			link.l1 = "고마워!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "여기 처음이지, 나리? 유럽에서 막 온 건가? 식민지 사정을 잘 모르는군. 이번 처형은 프랑스 식민지인의 재산을 넘보는 붉은 피부 놈들에게 본보기가 될 거다. 게다가 파데이 본인도 강력히 원하고 있어. 그는 이곳에서 아주 존경받는 인물이자 우리 총독의 절친이기도 하지.";
			link.l1 = "처벌을 좀 줄일 방법이 있소? 아직도 너무 가혹하다고 생각하오...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "아, 철학 따위는 집어치워! 정말 그 인디언의 운명이 궁금하다면 파데이에게 가서 물어봐. 파데이가 석방 청원서를 써 오면, 우리가 풀어주겠다.";
			link.l1 = "알겠습니다, 장교님. 파데이에게 가겠습니다.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(읽으면서) 흠... 이 파데이는 이상한 놈이군... 공개 처형을 요구하더니, 이제는 이 인디언을 풀어달라고 하네... 뭐, 총독 친구란 놈들이 다 그렇지. 좋아, 가서 이 붉은놈 데려가라.";
			link.l1 = "고맙소, 장교!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "또 그거야 "+pchar.questTemp.Shadowtrader.Tradername+" 그놈의 불평 또 시작이군! 좋아, 이번엔 뭔지 한번 볼까... (읽어본다)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "또다시 터무니없는 추측뿐이고, 확실한 증거는 하나도 없군! 좋아. 그에게 이렇게 전하시오. 이런 정도로는 내가 경비병들에게 경계 태세를 알리고 마을을 샅샅이 뒤지라고 명령할 수 없다고.";
			link.l1 = "내가 그에게 그렇게 전하길 원하나?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "그래, 그리고 가능하다면 한 글자도 틀리지 말고 그대로 전하라. 그 자는 내가 무슨 뜻인지 알 것이다. 이 성가신 놈에게 답장 쓰느라 종이 낭비는 안 하겠다.";
			link.l1 = "알겠소. 그럼 이만.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "그대가 모았다고 주장하는 그 '확실한' 증거란 게 대체 뭔가?";
			link.l1 = "나는 밀수업자들과 그들의 비공식 상점을 통해 물건을 사는 거래를 했다. 그들의 연락책이 오늘 밤 항만청 사무실로 와서 나를 그들이 말하는 '상점'으로 데려갈 거다.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "흠... 음, 훌륭한 일 했소, 선장! 이제 다음 단계로 나아가지. 우리 사람이 그들의 모임에 잠입해서 은신처를 찾아내고 전부 체포할 것이오. 주도적으로 나서줘서 고맙소!";
			link.l1 = "언제든 도와드릴 수 있어 기쁩니다. 분명 작전이 성공할 거라 확신합니다.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "누구? 롱... 웨이? 최근에 우리 마을에 영국인은 본 적이 없는데.";
			link.l1 = "아니, 롱웨이는... 중국인이오.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "그래, 그래. 그런데 그대는 왜 그 롱웨이라는 자를 찾고 있소, 나리?";
			link.l1 = "그는 내 친구다. 무슨 일이 있었는지 이미 들었네 - 안타까운 오해일 뿐이니 안심하게.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "그를 찾는 이유는 군도가에 악명 높은 범죄자이기 때문이오.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "아, 오해가 있었군. 우리가 그 자리에서 그를 바로잡으려던 건 아니었어. 일단은 그냥 대화를 좀 해보려고 했던 거지... 시작부터 말이야. 그런데 네놈의 저 성질 더러운 노란 놈이 도시 경비병 몇 명을 베어버렸을 뿐만 아니라, 정글로 그를 쫓아간 부대까지 모조리 도륙해 버렸더군.";
			link.l1 = "또 다른 부대를 보낼 생각이오? 내가 당신 부하들과 함께 가서 그와 이야기하고, 진정시키고, 또 다른 참사를 막을 수 있소. 살인이 멈추고 롱웨이가 영원히 도시를 떠난다면 그걸로 충분하겠소?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "보통 때라면 네 말에 동의할 수도 있겠지. 하지만 이번엔 사정이 달라. 죽은 자들 중에 장교가 있었어. 유망한 젊은 중위였고, 각하께서 총애하던 인물이었지. 마을 전체가 애도에 잠겼다네. 그냥 못 본 척하거나 대충 넘어갈 수 없어. 이해하겠나?";
			link.l1 = "완벽히 이해했습니다. 제 친구의 행동에 대해 사과드립니다. 더 이상 폐를 끼치지 않겠습니다.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "있잖아, 정글에서 무슨 일이 벌어지는지 신만이 아실 거야. 그 남자들을 죽인 게 누구든 될 수 있지.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "그럼 누가 장교가 이끄는 순찰대 전체를 쓰러뜨릴 수 있었다고 생각하나?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(믿을 만한) 도적들, 또 누가 있겠어? 부끄럽지만, 나도 최근에 큰 무리에게서 간신히 도망쳤다네.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "하지만 내가 어떻게 알겠어? 누구든 될 수 있지—도적, 해적, 첩자...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "헤, 그럴 만도 하지, 선장. 그 덩치라면 말이야. 요즘 우리 섬에 저런 악당들이 들끓고 있지...";
			link.l1 = "정확히 그렇지! 그러니까, 그놈들이 순찰대랑 불쌍한 소위까지 몰살시켰을 수도 있겠군.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "안타깝게도, 그럴 수도 있지.";
			link.l1 = "정확히 그렇소. 그러니 다시 한번 부탁하오, 다음 수색대에 나도 합류하게 해주시오. 롱웨이는 내 말을 들을 것이고, 그렇게 하면 더 이상의 희생을 막을 수 있소.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "좋소. 하지만 아직도 한 가지 '하지만'이 남았소, 나리.";
			link.l1 = "그게 뭐지?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "정글에서 있었던 일과는 달리, 도시에서 네 친구의 죄는 명확하게 입증되었지. 그냥 넘어갈 수는 없어. 그러니 그가 살아서 도시를 떠나길 원한다면, 이 죽음들에 대한 대가를 치러야 할 거다.";
			link.l1 = "좋소. 비용이 얼마나 드는가, 장교 나리?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "삼백 두블룬이다. 그 돈은 시장 바닥의 잡놈들이 아니라 도시로 들어갈 거다.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "물론이지. 삼백 두블룬이오 - 여기 있다.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "이번엔 내 더블룬을 마을에 가져오지 않았어. 하지만 꺼내오게 해준다면...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "훌륭하군. 책임감을 입증했어. 우리는 다음 분대의 브리핑을 막 마무리하는 중이야. 네가 그 분대에 합류하는 걸 허가하지.";
			link.l1 = "감사합니다. 안녕히 계십시오, 장교 나리.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "나도 바보는 아니지. 네가 도망치려는 건 두블룬 때문이 아니라, 네 소중한 중국놈 때문이라는 거 다 안다.";
			link.l1 = "내가 맹세하마, 롱웨이와 함께 이 마을을 떠나지 않겠소.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "말, 말... 네 잡담에 질렸어, 선장. 우리가 저 빌어먹을 누런 피부 놈을 직접 잡기 전엔 넌 어디도 못 가.";
			link.l1 = "당장 롱웨이를 죽이지 않겠다고 약속한다면 명령을 따르겠소, 장교 나리.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "하지만 내가 오늘 직접 이 도시의 법을 어겼단 말이오?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "그렇다면 너는 모르는 거군. 난 지금 내 직감대로 간다 – 그 중국놈은 반드시 잡아야 해, 무슨 수를 써서라도.";
			link.l1 = "지금 네가 갖고 있는 촉이란 건가? 하지만 롱웨이가 정글에서 모두를 죽였다는 증거는 없잖아.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "그의 무죄를 증명할 증거라도 있나? 없어? 그럼 네 노란 피부 놈을 성인인 양 만들지 마라. 내 말 알겠나?";
			link.l1 = "완벽히 이해했습니다. 제 친구의 행동에 대해 사과드립니다. 더 이상 폐를 끼치지 않겠습니다.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "아직은 보내드릴 수 없겠소, 선장.";
			link.l1 = "무슨 뜻이지?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "내 말은, 이 롱웨이가 네 친구라면 네가 그놈을 쫓아가서 같이 도망치려 할 수도 있다는 거다. 그러니 우리가 직접 이 누런 피부의 도살자를 잡을 때까지 널 붙잡아 둘 수밖에 없겠군.";
			link.l1 = "당장 롱웨이를 죽이지 않겠다고 약속한다면 명령을 따르겠소, 경관 나리.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "하지만 내가 오늘 직접 이 도시의 법을 어겼단 말이오?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "아무것도 약속할 수 없소. 네 친구가 무슨 꿍꿍이를 품고 있는지, 우리가 나타나면 또 무슨 학살을 벌일지 누가 알겠나. 그동안 호화로운 감방에서 잘 지내시오, 선장.";
			link.l1 = "웃기군...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "알아두시오, 나는 자네 개인적으로는 아무 감정도 없소. 그리고 자네 말이 맞소 – 자네는 아무 죄도 짓지 않았지. 하지만 자네의 노란 피부 친구가 정의를 피해 도망치지 못하게 해야 하오.";
			link.l1 = "그렇다면 이런 가짜 짓거리로 내가 붙잡히는 일은 절대 없을 거라는 걸 알아둬.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "그렇다면, 너를 조용히 만들어야겠군, 나리.";
			}
			else
			{
				dialog.text = "이젠 더 못 참겠다! 하사, 분대를 이끌고 저 빌어먹을 동굴로 가서 중국 놈들을 찾아내라! 이 자식은 내가 직접 처리하겠다...";
			}
			link.l1 = "네가 그럴 리가 없지.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "현상금 사냥꾼이라, 그렇군. 원래 너희 같은 놈들이랑 엮이는 건 내키지 않지만, 이번엔 이해관계가 맞으니 내게도 이득이지. 듣자 하니 저 누런 피부 놈이 악명 높은 살인자라더군. 내 부하들을 마을에서도, 정글에서도 여럿 죽였지.";
			link.l1 = "나는 지금까지 그 녀석을 군도 전역에서 쫓아다니고 있었지.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "빌어먹을 악당 놈! 이렇게 하자: 내가 다른 병력을 모을 테니, 너는 그들과 함께 가라. 이번엔 저놈이 도망칠 곳이 없으니, 네가 도와주면 성공 확률이 더 높아질 거다. 하지만 내게서 보상은 기대하지 마라 – 넌 현상금 사냥꾼이니, 네 보수는 널 고용한 놈에게서 받을 일이다. 내가 너랑 협력하게 해주는 것만으로도 감사해야 할 거다.";
			link.l1 = "그 말이 맞군. 나중에 보자, 장교. 네 부하들이 우리 중국 친구와 다시 맞붙고도 살아남는다면, 어떻게 됐는지 알려주지.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "맞아. 너희 둘, 서로 아는 사이인가 보군? 서로 어떤 관계지?";
			link.l1 = " 그는 내 배의 항해사고, 그리고...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "그를 찾는 이유는 그가 군도에서 악명 높은 범죄자이기 때문이오.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "저 자식은 지도보다 총을 더 잘 다루지. 네가 데리고 다니는 그 중국놈이 뭘 저질렀는지 알고나 있나?";
			link.l1 = "솔직히 말하면, 아니오. 방금 막 입항해서 수색을 시작했거든요. 분명 오해였을 겁니다.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "정확하다. 그를 그렇게까지 원한다면, 너는 그에게 어떤 존재지? 상관없다 – 중요한 건 네가 이 도시에 온 목적이다.";
			link.l1 = "불법적인 건 아무것도 없습니다, 나리. 그런데 “이제 더는 상관없다”는 말은 무슨 뜻입니까? 혹시 그가...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "그래. 그는 묘지에서 좀 떨어진 언덕 중 하나 뒤에 묻혔지. 성직자들이 이교도에게 제대로 된 기독교식 장례를 허락하지 않았거든.";
			link.l1 = "비밀이 아니라면, 어떻게 된 일이오?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "아주 간단하다 - 그 자가 도시에 도착해서 끝도 없이 돌아다니며 기웃거렸지. 우리가 그에게 접근해서 여기서 뭘 하는지 알아보려 했는데, 놈이 우리 사람 몇을 죽이고 정글로 도망쳤다네. 내가 수색대를 몇 번이나 보냈지만, 놈이 전부 쓸어버렸지! 결국 우리는 그 놈을 동굴에 몰아넣었고, 사수들이 나머지를 처리했다네.";
			link.l1 = "그리고 그가 뭘 찾고 있었는지도 모른다는 건가? 있잖아, 전에 이런 짓을 한 적이 한 번도 없었어. 원래 내 배에서 항해사였거든. 그런데 나한테서 훔쳐 달아났지.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "그냥 깜빡했지, 그래. 너도 그 자식한테 당했구나? 그거 좋은 교훈이 됐겠군, 선장. 이제는 믿을 수 없는 놈은 상대하지 말아야 한다는 걸 알겠지. 노란 피부 가진 놈은 절대 믿지 마라—내 말 명심해!";
			link.l1 = "알겠소, 명심하겠소. 그 자에 대해 뭔가 알아냈소?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "오, 도둑맞은 물건을 되찾고 싶다고? 그놈 주머니에 은화가 좀 있었는데, 네 걸 훔쳤다면 이미 다 써버렸을 거다. 그리고 다른 서류들도 있었지... 네 배의 항해일지에서 나온 건가? 우리도 도통 알아볼 수 없더라 - 암호 같은 거였나? 전부 피로 뒤덮여 있어서 멀쩡한 부분도 알아볼 수가 없었어.";
			link.l1 = "어, 네. 감사합니다. 내 일지와 일기가 다른 사람 손에 들어가면 어떻게 될지 항상 걱정했거든요...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "그래서 그 일 때문에 복잡한 암호까지 만들어야 했단 말이오? 시간과 노력이 아깝지 않았소? 자, 여기 있소. 그리고 은에 관해서는... 화내지 말구려, 도시로 돌려보냈소. 그 중국놈이 그날 내 부하들을 여럿 땅에 묻었거든.";
			link.l1 = "그렇다면 더 이상 고집하지 않겠소. 안녕히 계시오.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
