// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해라, 무엇을 원하는가?","우리가 방금 그 이야기를 하고 있었소. 당신이 잊은 모양이군...","오늘만 세 번째로 이 질문을 꺼내시는군요...","이봐, 여긴 상점이야. 사람들은 여기서 물건을 사 간다고. 나 좀 방해하지 마!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 다음 기회에 하도록 하지.","맞아요, 무슨 이유에선지 내가 잊고 있었군요...","그래, 정말로 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "듣게, 작은 새가 벨리즈에서 홍목이랑 코코아 값이 곧 크게 뛸 거라고 알려줬지. 최근에 좋은 거래를 해서 내 주머니에 두블룬을 가득 채웠다네, 헤헤... 이 물건들을 좀 사고 싶은데, 할인 좀 기대해도 되겠나?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "'Admirable'라는 이름의 갤리온이 최근에 식민지에 Gaius Marchais 선장의 지휘 아래 입항했습니다. 말씀해 주시겠소, 그가 여기서 탄약이나 되팔 물품을 비축했을 가능성이 있겠소?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "음, 나리, 물량이 정말 많다면 물론 합리적인 할인에 대해 논의할 수 있습니다.";
			link.l1 = "훌륭하군! 조선소에 곧 새 플루이트가 판매될 거라는 소문을 들었소. 나는 기다렸다가 그 배를 살 생각이오. 내 브리그에서 대포를 전부 떼어냈는데도 이 물건들을 다 싣기엔 창고가 아직도 부족하오! 나중에 다시 들르겠소!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "하! 그 이상한 친구 기억나지! 그 자는 유럽 상인들의 대규모 대상단이 과들루프에 들러 실을 수 있는 만큼의 향신료를 사갈 거라며, 과들루프에 바닐라가 절실히 필요하다는 어리석은 소문을 철석같이 믿었지\n이런 헛소리는 매달 듣지만, 마르셰는 그걸 아주 진지하게 받아들였어. 여기서 일주일을 머물면서 내게 바닐라로 화물창을 가득 채울 만큼 모으라고 했지\n가진 돈을 전부 이 일에 쏟아부은 모양이야. 그 사람 참 안됐지만, 미쳐가고 싶은 자들을 내가 막을 수는 없지.";
			link.l1 = "그럼, 지금 그가 과들루프에 있을 수도 있겠군?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "아마도 그렇겠지. 그자는 상상 속의 '상인들'을 기다리며 그리스도의 재림 때까지 허송세월만 할 테고, 바닐라를 팔아서 손해만 볼 거야. 현명하다면 바닐라 수요가 급등할 때까지, 아니면 더 필요한 곳을 확실히 알게 될 때까지 바스테르에 머무르는 게 좋을 거야.";
			link.l1 = "그래. 고맙다, 네가 큰 도움이 되었어!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
