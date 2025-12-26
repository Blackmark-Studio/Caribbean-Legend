// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문이 "+GetCityName(npchar.city)+" 대기 중이오. 무엇을 알고 싶은가?","바로 그 얘기를 하고 있었지. 네가 까먹은 모양이군...","오늘만 세 번째로 이 질문을 꺼내는군...","너, 앵무새처럼 똑같은 말만 반복하고 있잖아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 다음 기회에.","그래, 무슨 이유에선지 잊어버렸군...","그래, 정말로 이번이 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "섬에서 심각한 문제가 있었다고 들었어... 노예들 때문인가?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "그 비열한 놈 바트 포르투갈놈이 드디어 정의의 심판을 받았다고 들었어! 지금 감옥에 있나? 처형이 언제인지 알아? 꼭 가서 보고 싶어, 그 쓰레기한테 따질 게 있거든...";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "들어봐, "+npchar.name+", 최근에 새로 온 예쁜 여종업원이 있다던데... 벌써 사라졌다고?";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "말해 봐, "+npchar.name+", 그 밤에 베시가 사라졌을 때, 근처에서 수상한 사람을 봤나? 혹시 누군가와 이야기하고 있던 건 아니었어?";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{			
				sld = CharacterFromID("Villemstad_waitress");
					if (CheckAttribute(sld, "model") && sld.model != "Marquesa")
					{
						link.l1 = "음, "+npchar.name+", 좋은 소식이오 – 자네 소중한 웨이트리스는 무사히 살아 있네. 럼주를 다시 채워야겠군, 곧 사람들이 돌아올 테니.";
						link.l1.go = "TBP_Tavern3_21";
					}
					else
					{
						link.l1 = "음, "+npchar.name+", 끝났어 – 네 소중한 웨이트리스가 돌아왔으니 럼주 다시 쟁여둬. 곧 사람들이 다시 몰려올 테니까.";
						link.l1.go = "TBP_Tavern3_21_1";
					}
				
			}
			//<-- Тайна Бетси Прайс
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "그래, 이런 난장판은 처음이야... 천 명이 넘는 흑인들이 반란을 일으켰지. 두 개의 플랜테이션이 완전히 불타 버렸고, 주인들도 모두 살해당했어. 사령관은 노예들이 도시를 공격하러 올까 봐 계엄령을 내렸지. 이 모든 게 타망고라는 숫놈과 이사우리라는 암놈, 두 흑인 때문에 시작된 일이야...\n";
			link.l1 = "꽤나 극적인데. 전부 다 말해 봐, 그 흑인들은 누구지?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "타망고와 이자우라는 블렌하임 플랜테이션의 노예였어, 그곳이 처음 불타버린 플랜테이션이지. 이 두 흑인들은 서로를 사랑했어. 그런데 플랜터의 아들 레온시오가 유럽에서 와서는 그 여자를 탐냈지. 그는 이자우라를 자기 첩으로 삼으려 했어. 흑인 남자 타망고는 그 생각이 마음에 들지 않았고, 이자우라 역시 마찬가지였지. 그녀는 정말로 그 흑인 악마를 사랑했으니까. 타망고는 아프리카에서 무슨 추장 같은 존재였대... 죄보다 더 검고, 도끼를 들면 죽음보다 무서운 거인이라 다른 흑인들도 그를 두려워하고 존경했지. 그래서 이 남자가 다른 노예들을 이끌고 반란을 일으켰어. 그들은 밤에 경비병들을 습격했고, 큰 집 밖에 있던 백인들은 물론, 물라토들까지 전부 죽였지. 그리고 이자우라가 플랜테이션의 문을 열어주자 반란자들이 안에 있던 모두를 죽였어. 블렌하임은 완전히 불타버렸지. 그 후 노예들은 정글로 도망쳐 사라졌어...\n";
			link.l1 = "이봐, 이거야말로 소설 한 편 거리 아니겠어! 고대 로마에서나 볼 법한 제대로 된 노예 반란이잖아. 그런데 그걸 어떻게 다 알아낸 거야?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "소문이란 게 넘쳐나지, 나리. 럼주만 있으면 입이 풀린다네, 그저 귀만 기울이면 되지...";
			link.l1 = "그래서 그 일은 어떻게 끝났지? 그 흑인들을 찾았나?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "하, 말도 안 돼! 증원군이 겨우 도착할 때까지 아무도 정글에 한 발짝도 들여놓지 않았지. 그러다 컴퍼니 군함이 병사 부대를 데리고 와서 섬을 샅샅이 뒤졌어. 도망친 흑인 한 놈의 그림자도, 곱슬머리카락 한 올도 못 찾았지.";
			link.l1 = "이런, 이럴 수가! 흑인 천 명이 그냥 증발해 버렸단 말이야?";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "사실은 물속으로.";
			link.l1 = "무슨 소리를 하는 거야, "+npchar.name+"? 너도 알잖아, 흑인들은 수영 못 한다는 거.";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "헤헤... 이런, 그 흑인들이 그렇게 빨리 상어 밥이 되진 않았지. 사실은, 반란 다음 날 밤에 부두에서 바크 한 척이 사라졌어. 만약 그게 타망고와 그의 흑인 녀석들 짓이 아니었다면, 내가 몸을 까맣게 칠하고 밴조 치며 춤이라도 추겠네! 그래서 이제 그놈들이 섬에 없는 거야.";
			link.l1 = "허, 이제 별별 소리를 다 듣는구만, "+npchar.name+". 네가 반쯤 야생인 흑인들이 돛을 다루고 항해까지 할 수 있다고 믿으라는 거냐? 차라리 기니에서 원숭이 떼가 배를 몰고 들어오는 걸 기대하겠다.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "나도 믿지 않았소, 마인헤르, 하지만 사라진 배가 증거 아니겠소. 어쩌면 그 흑인들 중 하나가 예전에 배에서 집사로 일하면서 항해 기술을 배웠을지도 모르지. 아니면 흑마법을 썼을지도, 누가 알겠소! 또 들르시오,\n "+pchar.name+", 다음번엔 더 많은 이야기를 들려주지.";
			link.l1 = "고마워! 자, 이제 슬슬 가봐야겠다.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "그래, 맞아. 그 해적을 잡았지. 그런데 어떻게 잡혔는지 믿을 수 있겠어? 바다 한가운데서 혼자 작은 배에 타 있다가 붙잡혔대. 쥐들하고 같이 선창에 던져질 때까지 아무 소리도 안 냈다더군. 정말 우습지 않아? 그렇게 위험한 해적이 그렇게 얼간이처럼 잡히다니!";
			link.l1 = "그런데 왜 그가 바다에 혼자 있었던 거지?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "아마 자기 졸개들이랑 갈라서기로 했겠지, 의심할 여지 없어... 전리품을 공평하게 나누지 못했나 봐. 이제 그는 회사 놈들 손아귀에 들어갔고, 그 자식들은 농담 따윈 안 받아주지. 들리는 말로는 그가 회사 배 중 하나와 귀중한 뭔가를 손에 넣었다더군. 지금까지 목에 밧줄이 안 걸린 것도, 그놈들한테서 뭔가 정보를 빼내려는 속셈 때문이래.";
			link.l1 = "그래서, 그의 처형이 언제인지 알고 있나?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "아무도 몰라. 내 생각엔 회사가 원하는 걸 알아내면, 저놈 목에 밧줄을 걸겠지. 그 포르투갈 녀석은 지금 믿을 만한 경비 아래 감옥에 있어\n최근엔 그놈의 보스운도 여기로 데려왔어. 그 자식 얘긴 더 놀라웠지; 필립스버그에서 네덜란드 놈들에게 자진해서 잡혔다더군. 그래서 지금은 전 선장 바로 옆 감방에 처박혀 이웃이 됐지, 크크...";
			link.l1 = "기적도 일어나는군! 좋아, 소식 잘 지켜보겠어. 그 교수형은 놓치고 싶지 않으니까. 잘 가,\n "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "아, 선장님, 그 애를 직접 봤더라면! 베츠라고... 그 우아함, 그 미소! 남자들이 그저 그녀를 보기 위해 여기 몰려들었지. 그리고 그들이 내 선술집에 두고 간 은화들... 그런데 사흘 전부터 일하러 오지 않았어. 물론 사람을 그녀 집에 보냈지만, 거기에도 없더군. 집은 엉망이었고, 그녀의 소지품도 다 사라졌어\n이젠 뭘 생각해야 할지 모르겠어. 경비병들은 늘 그렇듯이 그냥 어깨만 으쓱했지. 실종된 처녀 찾는 것보다 더 중요한 일이 있다나 뭐라나. 그냥 어디 나갔다가 곧 돌아올 거라고 하더군. 선장님, 혹시 그녀를 찾아줄 수 있겠소? 그녀를 다시 데려오면 백 더블룬을 드리겠소. 난 그녀를 잃을 수 없어, 알겠소? 진짜 보물 같은 아이라 반드시 되찾아야 해!";
			link.l1 = "한번 알아보지. 그녀가 사라지기 전에 이상하게 행동했거나 나쁜 소식을 들은 적이 있나?";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "아마 도망친 여자애를 찾아달라고? 난 더 중요한 일이 있어. 네가 알아서 해.";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "사라지기 전 마지막 날, 그녀는 기분이 아주 좋아 보였어, 심지어 행복해 보이기까지 했지! 아무 문제의 기미도 없었고, 떠난다는 말 한마디도 없었어. 그냥 흔적도 없이 사라졌지!";
			link.l1 = "흥미롭군... 그녀의 집은 어디에 있지?";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "그 여자는 저 위쪽 길에 살았어, 파란 발코니가 있는 저택 맞은편 집 뒤에 있는 오두막에서 말이야. 여기서 멀지 않아.";
			link.l1 = "그럼, 시간 낭비하지 않겠소. 뭔가 찾으면 알려주겠소.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "수상해? 그녀 주변에는 항상 구혼자들이 몰려 있었고, 각자 나름대로 수상쩍었지! 그녀는 아주 요염했고, 관심을 끄는 법을 잘 알았어.";
			link.l1 = "그 정도는 나도 알았지"+GetSexPhrase(""," 밖")+" 이미야. 하지만 눈에 띄는 사람이 있었나?";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "흠... 글쎄, 한 명 있었지. 그날 저녁, 그는 그녀에게 보석이 박힌 펜던트를 줬어. 여기 앉아서 밤새 그녀만 바라보며 주위를 맴돌았지.";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "그 펜던트, 혹시 이거 아니야? (거지에게서 산 카메오를 보여준다)";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "보석이 박힌 펜던트라니...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "그거야! 바로 그거지! 선장님, 벌써 뭔가 찾으셨습니까?";
			link.l1 = "자세한 이야기는 나중에, "+npchar.name+", 지금은 지체할 시간이 없어.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Given: Cameo pendant", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "훌륭하군요, 선장님! 다시는 그녀를 못 볼 줄 알았는데. 그래서 어떻게 된 거요? 정말 도망치고 싶었던 건가?";
			link.l1 = "그녀가 과거의 문제들을 좀 처리해야 했다고만 해 두지. 하지만 이제는 다 지난 일인 것 같고, 곧 다시 일터로 돌아올 거야.";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "글쎄, 네 지루한 얼굴만 보느라 잠깐 쉬고 싶었겠지. 하하! 찡그리지 마, 농담이야. 모든 숙녀에겐 작은 비밀쯤은 있어야 하잖아...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "음, 중요한 건 그녀가 다시 일할 수 있게 됐다는 거지. 보상은 충분히 받을 자격이 있소, 선장. 자, 약속대로 여기 금화 백 닢이오. 그리고 이 지도도 가져가시오. 손님 중 한 명이 두고 갔는데 다시 오지 않았거든. 보아하니 보물로 이끄는 지도인 것 같소.";
			link.l1 = "그럼, 내가 확인해 볼게. 고마워.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune":
			dialog.text = "음, 중요한 건 그녀가 다시 일하게 됐다는 거지. 보상은 충분히 받을 자격이 있소, 선장. 자, 여기 있소 – 약속한 대로 100두블룬이오. 그리고 이 지도도 가져가시오. 손님 중 한 명이 두고 갔는데, 다시 오지 않았소. 보아하니 보물로 가는 길을 가리키는 것 같군.";
			link.l1 = "그럼, 내가 확인해 볼게. 고마워.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		
		case "TBP_Tavern3_21_1":
			dialog.text = "내 목숨을 구해줬군, 선장! 다시 그녀를 볼 희망조차 거의 포기했었지... 그런데 대체 무슨 일이 있었던 거야? 정말 도망칠 생각이었던 거야? 나는 직접 물어볼 용기가 없었어.";
			link.l1 = "그녀가 과거에 미처 끝내지 못한 일들을 처리해야 했다고만 해두지. 하지만 이제는 다 지나간 일인 것 같고, 곧 다시 일하러 돌아올 거야.";
			link.l1.go = "TBP_Tavern3_22_leadership_1";
			link.l2 = "글쎄, 그냥 네 지루한 얼굴만 계속 보는 게 힘들어서 잠깐 쉬고 있는 거라고 해두자고. 하하! 그렇게 인상 쓰지 마, 농담이야. 모든 여인에겐 작은 비밀쯤은 있어야지...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership_1":
			dialog.text = "음, 중요한 건 그녀가 다시 일하고 있다는 거지. 보상은 충분히 받을 자격이 있네, 선장. 자, 여기 약속대로 금화 백 개다. 그리고 이 지도도 가져가게. 어떤 손님이 두고 갔는데 다시는 돌아오지 않았어. 보아하니 보물로 이끄는 지도인 것 같군.";
			link.l1 = "알겠어, 내가 확인해 볼게. 고마워.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune_1":
			dialog.text = "음, 중요한 건 그녀가 다시 일하고 있다는 거지. 보상은 충분히 받을 자격이 있소, 선장. 자, 약속대로 100두블론이오. 그리고 이 지도도 가져가시오. 어떤 손님이 두고 갔는데 다시는 돌아오지 않았소. 보아하니 보물로 이끄는 지도 같군.";
			link.l1 = "알겠어, 내가 확인해 볼게. 고마워.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
