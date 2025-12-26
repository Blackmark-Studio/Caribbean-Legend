// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문이 "+GetCityName(npchar.city)+" 대기 중이오. 무엇을 알고 싶은가?","우리가 바로 그 얘기를 하고 있었지. 너는 잊어버린 모양이군...","오늘만 벌써 세 번째로 이 질문을 꺼내는군...","너, 앵무새처럼 똑같은 말만 반복하고 있잖아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음에.","맞아, 내가 왜인지 잊어버렸네...","그래, 정말 이번이 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "이봐, 프랑수아 곤티에는 어디서 찾을 수 있지? 이미 토르투가에 도착했어야 했잖아.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "앙리 티보를 찾고 있어. 어디서 그를 찾을 수 있지?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "앙리 티보를 찾고 있어. 어디서 그를 찾을 수 있지?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "말해 봐, '산타 마르가리타'라는 이름의 갤리온이 최근에 네 식민지에 들른 적 있나? 혹시 사략선의 전리품으로?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "이봐, 친구, 나 가스파르 파르망티에를 찾고 있는데, 어디서 찾을 수 있지?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "조금만 도와줄 수 있겠나, 친구? Joep van der Vink이라는 남자를 찾고 있는데, 아는가?";
				link.l1.go = "PZ_1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "프랑수아 곤티에? 그게 누군데? 난 그런 이름의 남자는 모른다.";
			link.l1 = "그는 코르벳 '의 선장이야"+pchar.questTemp.Slavetrader.ShipName+"'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "나는 전혀 모르겠어. 그리고 그 이름의 코르벳이 우리 항구에 들어온 적은 없다고 확실히 말할 수 있어.";
			link.l1 = "좋아, 그럼 요즘 마을에 외지인 본 적 있어?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "좋은 질문이군! 여긴 시골 마을이 아니라 항구 도시야. 낯선 놈들이 매일같이 드나들지. 그런데 이상한 다섯 녀석들 얘기는 들었어. 항상 뭉쳐 다니고 칼을 빼놓지 않더라고.\n순찰대도 그놈들에 대해 수소문했지만 별 소득은 없었지. 하지만 확실한 건, 그놈들이 코르벳을 타고 온 건 아니라는 거야. 그런 배는 근처에서 본 적 없거든, 알겠어?";
			link.l1 = "흠... 알겠소. 고맙소, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "티보 나리는 토르투가에서 유명한 인물이오. 그의 저택은 항만청 근처에 있소. 선술집을 나서면 곧장 항구 쪽으로 가시오. 항구로 이어지는 아치에 다가가서, 교차로에서 왼쪽으로 돌고, 길 끝까지 쭉 내려가면 붉은 지붕의 2층짜리 돌 건물을 만나게 될 것이오. 그곳이 바로 티보 나리의 저택이오.";
			link.l1 = "고마워! 내가 그를 찾아가 볼게...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "오늘은 티보 나리가 아주 인기 많군, 총독의 심부름꾼도 방금 여기로 달려왔어. 그 사람도 관심이 있더라고. 그렇게 찾기 힘든가? 티보 나리는 꽤 오래 전부터 2층에서 내 방을 빌려 쓰고 있어, 저택이 따로 있는데도 말이야. 왜 필요한지는 모르겠지만, 들어오는 건 자주 보는데 나가는 건 거의 못 봤어. 그리고 저녁에만 거기 있지.";
			link.l1 = "어쩌면 지금 여기 있을지도 몰라.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "아니. 그는 오늘 저녁 여덟 시까지 돌아오지 않겠다고 했어. 그의 저택에서 찾아볼 수도 있겠지만, 거기서 그를 만나긴 힘들 거야. 내가 그가 순찰 루거선을 타고 바다로 나가는 걸 봤거든.";
				link.l1 = "고마워! 나중에 들러서 그를 볼게.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "그래. 원하면 올라와도 돼.";
				link.l1 = "고마워! 내가 그를 찾아가 볼게...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "배 이름은 전혀 모르겠어, '산타 마르가리타'였는지 '카스티야의 창녀'였는지, 아무튼 스페인 갈레온을 끌고 들어왔지. 그것도 슬루프가 잡아온 거라니까! 이게 진짜 제대로 된 항해지! 가이우스 마르셰 선장이 이틀째 술집에서 자랑하고 있더라고 - 첫 항해에 이런 전리품이라니!\n그래, 정말 용감한 짓이지. 병사 하나 없이 교회 쥐새끼들만 가득한 갈레온에 올라탔다니. 그 교황쟁이 놈들은 남의 걸 챙기는 놈들에 대해 뭐라 했는지 까먹은 모양이야...";
			link.l1 = "그래, 하느님은 스스로 돕는 자를 돕는다고 하지, 그건 위그노들이 자주 하는 말이지. 그 행운의 선장을 어떻게 하면 볼 수 있겠어? 여기 토르투가에 있나?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "아, 누가 알겠어. 내 선술집에서 그 녀석 본 지도 오래됐지. 술이 깨자마자 상금으로 번쩍이는 새 배를 사더니 미친놈처럼 갑판 위를 뛰어다녔어. 지금 Marchais가 어디 있는지 전혀 모르겠어. 어쩌면 토르투가에 있거나, 아니면 바다에 있겠지.";
			link.l1 = "알겠어. 그래, 이야기 고마워, 친구!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "언제든지요, 나리. 우리 사랑받는 선장님을 돕게 되어 항상 기쁩니다 "+pchar.name+", 생피에르의 구세주! 나중에 또 들르시오!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "가스파르가 너희들 사이에서 점점 더 인기 많아지는 것 같군. 그의 집은 성벽 옆에 있어. 선술집에서 왼쪽으로 돌아 항구 쪽으로 가다가, 거기까지 가지 말고 다시 왼쪽으로 돌아. 곧장 가다가 오른쪽으로 꺾으면 돼. 2층짜리 집이야.";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ_1":
			dialog.text = "그런 사람은 처음 듣는데.";
			link.l1 = "어쩌면 다른 이름으로 불릴지도 몰라. 혹시 '반텐' 브리그의 선장으로 들어본 적 있나?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "나도 그 브리그에 대해 들어본 적 없어.";
			link.l1 = "그가 최근에 여기 있었다고 들었어. 은화 좀 쥐어주면 기억이 좀 더 또렷해지지 않을까?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "글쎄, 그 얘기를 어디서 들었는지 스스로 생각해 봐. 하지만 네 은화는 기꺼이 받지.";
			link.l1 = "이번엔 은화가 없군. 잘 가라.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
