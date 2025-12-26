// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있습니까?","무엇을 도와드릴까요?"),"얼마 전에 그 질문을 나에게 하려고 했었지...","그래, 맞춰볼까... 또 뱅뱅 돌고 있는 거지?","이봐, 여기서 재정은 내가 맡고 있어, 질문엔 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"으음, 내 기억이 다 어디로 갔지...","맞췄군, 미안하네...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "마인헤르, 다소 특이한 용건이 있소. 최근에 가이우스 마르셰라는 프랑스 사략선장이 당신께 금제 성광과 금제 향로, 두 가지 특별한 물건을 팔았다는 사실을 알고 있소. 그 물건들을 내가 사고 싶소.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "나는 당신께 금화가 든 작은 궤짝을 가져왔습니다.";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "아, 네! 물론 그들을 기억합니다! 정말 독특했고, 더 중요한 건 값비싼 물건들이었죠. 하지만 선장, 너무 늦으셨습니다. 이제는 더 이상 가지고 있지 않습니다. 이미 팔아버렸거든요.";
			link.l1 = "믿을 수가 없군! 그런데 그런 교회 용품에 누가 관심을 가졌소? 마인헤르, 누구에게 팔았소? 내가 다시 사오고 싶은데...";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "흠, 내가 왜 내 고객들의 이름을 너한테 줘야 하지?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "어쩌면 내가 마티아스 벡 총독의 눈에 좋은 친구라서, 당신을 위해 그에게 적절한 허가를 부탁할 수도 있기 때문일까요?";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "아마 내가 네덜란드 서인도 회사와 훌륭한 관계를 맺고 있고, 이 군도에 있는 많은 네덜란드 정착민들에게 큰 도움을 주었기 때문일지도 모르겠군?";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "내가 돈을 낼 거라서 그런가?";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "아, 그래, 맞지 "+GetFullName(pchar)+", 총독 본인의 친구이자 루카스 로덴부르크의 범죄 음모를 밝혀낸 분이시군요... 그걸 어찌 잊겠습니까? 물론 말씀드리겠습니다.";
			link.l1 = "그렇다면, 경청하겠습니다.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "아, 그렇군, 네가 맞아 "+GetFullName(pchar)+", 해적 '유령선'의 위대한 정복자. 그걸 어찌 잊겠소? 물론이지, 말해주겠소.";
			link.l1 = "그렇다면, 경청하겠습니다.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "좋소, 그러면. 금화 더블룬으로 가득 찬 궤짝을 내놓는다면, 당신보다 먼저 그 물건을 산 자들에 대해 이야기해 주지.";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "여기 있습니다. 저에게 아주 소중한 물건들이에요...";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "알겠소, 당신이 원하는 걸 가져오겠소. 그 물건들은 내게 아주 소중한 것들이오...";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("You've given a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "훌륭하군. 그렇다면 정보를 좀 나눠주지.";
			link.l1 = "잘 듣고 있소.";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "금으로 된 향로는 롤란드 모지스라는 자, 일명 '롤리 더 캡'이라는 이름으로 더 잘 알려진 사내가 샀소. 도대체 그 도살업자가 왜 귀한 교회 물건을 필요로 했는지는 이해가 안 되지만, 어찌 된 일인지 그는 그것을 보고 형언할 수 없을 만큼 기뻐하더이다... 그런데 말이오, 당신이 직접 롤리를 만날 일은 없을 것 같소.";
			link.l1 = "왜 그렇습니까?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "이 열정적인 영국 상인 약탈자가 최근 자신의 스쿠너를 콜로넬 폭스의 손아귀로 곧장 몰고 들어갔기 때문이오. 그가 누구인지 아시오? ";
			link.l1 = "틀림없지! 앤티가의 세인트 존스에 있는 'Sea Foxes'의 사령관이...";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "그렇다면 왜 우리가 불쌍한 롤랑드를 다시는 볼 수 없게 되었는지 이해하시겠군요. 대령이 그의 승무원 중 살아남은 자들과 함께 그의 스쿠너를 압수해서 세인트 존스로 넘겼습니다. 그곳에서 그들은 아마 이미 목에 밧줄이 걸렸을 겁니다.";
			link.l1 = "알겠습니다. 그리고 성광은요?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "그 성체현시대는 얼마 전에 쿠마나의 벨린다 데 리베로 나리께서 구입하셨소. 아주 유명한 나리로, 쿠마나 총독 페르난도 데 비예가스 본인의 친척이기도 하오. 아마 교회에 선물로 바치고 싶으셨던 것 같소.";
			link.l1 = "벨린다 데 리베로 나리? 쿠마나에서 만날 수 있지?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "틀림없어. 그녀가 직접 윌렘스타트에서 곧장 집으로 간다고 했거든.";
			link.l1 = "알겠습니다. 고맙소, "+npchar.name+", 정말 큰 도움이 되었소!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "언제든지 오십시오, 나리. 가끔 들러 주시기 바랍니다!";
			link.l1 = "부유한 지갑과 얕은 머리를 가진 손님들이 많이 오길 바라오... 하하!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
