// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문이 "+GetCityName(npchar.city)+" 대기 중이오. 무엇을 알고 싶으시오?","우리가 방금 그 얘기를 하고 있었지. 너는 잊어버린 모양이군...","오늘만 세 번째로 이 질문을 꺼내는군...","너, 앵무새처럼 똑같은 말만 반복하네...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 다음 기회에.","그래, 뭔가 이유가 있었는지 내가 잊어버렸군...","그래, 정말로 이번이 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "혹시 프랑수아 곤티에가 이 마을에 들른 적 있소? 그는 코르벳선 '"+pchar.questTemp.Slavetrader.ShipName+"', 만약을 위해서...' ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "말해 봐, 친구. 돈 디에고 데 몬토야는 어디서 찾을 수 있지? 내가 늦은 건가? 벌써 본토로 떠났나?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "이봐, 혹시 요아킴 메리먼이라는 이름의 남자가 여기 들른 적 있나? 중년의 의사고, 포르투갈 사람에 콧수염과 엠페러드 턱수염, 날카로운 눈빛을 가진 자야. 혹시 방을 빌리려고 했던 건 아닐까?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "아하, 그 음침한 녀석 말인가? 그래, 내 가게에 들렀었지. 한 가지 알려주지: 그자는 오레곤-앤-하스콘과 약속이 있었어. 특허를 신청했지. 하지만 잘 안 풀려서 떠났어.";
			Link.l1 = "그가 어디로 항해했는지 아시오? 내가 포르토 벨로부터 쭉 뒤쫓고 있는데 도무지 찾을 수가 없소.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "그에게서 뭘 원하지? 그는 외부인을 두려워해서 항상 남들 눈을 피해 다녀. 무장한 낯선 사람만 보면 바로 칼을 뽑지. 네 명의 경호원들한테 둘러싸여서만 돌아다녀. 혹시, 그가 그렇게 경계하는 사람이 너냐?";
			Link.l1 = "나리, 사람들이 그 말을 자꾸 반복해서 하네요! 내가 무슨 살인자처럼 보이나? 그는 내 오랜 친구야, 나는 그냥 그에게 전할 소식이 있어서 급할 뿐이야. 이제 더 이상 숨을 필요 없다는 걸 알면 그 친구도 무척 기뻐할 거야—이제 아무도 그를 찾지 않으니까.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "그가 숨을 필요가 없다고? 하하하! 아바나를 떠나기 하루 전, 정글에서 한 무리의 악당들이 그를 죽이려고 했지... 물론, 그에게도 자기 사람들이 있었고, 순식간에 그 놈들을 고깃덩어리로 만들어 버렸어. 그런데 네가 지금 와서 한다는 말이...";
			Link.l1 = "아, 그만 좀 해. 아마 그냥 동네 건달들이 지갑이나 털려고 했던 거겠지. 정글에 얼마나 많은 악당들이 돌아다니는지 너도 알잖아. 그래서 그 녀석은 어디로 갔는데?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "글쎄, 그가 관저에서 멀리, 오랫동안 쫓겨난 뒤로는 계속 자기 나라 놈들, 개구리 먹는 놈들에게 자수하겠다고 떠들더군. 토르투가로 떠났어, 무슨 도제롱이라는 놈을 찾아서... 또 자기 애인 얘기도 중얼거리던데, 그건 잘 못 알아듣겠더라.";
			Link.l1 = "그래, 토르투가인가? 훌륭해! 거기서 그 자를 꼭 잡길 바라지. 고마워, "+npchar.name+", 큰 도움이 되었어. 잘 가.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "흠... 프랑스 놈이 왜 돈 디에고에게 관심을 가지겠어, 응?";
			link.l1 = "내가 프랑스인이라는 건 중요하지 않아. 중요한 건 이 문서가 종교재판관의 서명이 있다는 거지. 한번 봐... 이제 알겠어? 나는 디에고에게 전할 긴급한 메시지가 있어.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "아하, 그럼 당신은 빈첸토 신부님의 일을 돕는 사람이었군? 그럼 이야기가 달라지지. 돈 디에고 데 몬토야는 이틀 전에 함대를 이끌고 떠났다가, 곧 자신의 커리어 러거를 타고 돌아왔어. 그의 배 중 하나가 쿠바 남쪽 암초에 좌초돼서, 오늘 내내 수리 자재를 사들이고 있었지\n남쪽 만을 확인해 봐. 거기에 배와 그 사람 본인이 있을 거야. 아직 구멍을 다 막지는 못했을 거다.";
			link.l1 = "고마워, 친구! 정말 큰 도움이 됐어!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "전혀요, 언제든지요. 예수회 형제를 돕는 건 언제나 기쁜 일입니다.";
			link.l1 = "그래, 팍스 보비스쿰이니 뭐니 다 알겠다고.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "악마만 알지, 친구. 아마 도착했을 수도 있지만, 난 모른다. 미안하다.";
			link.l1 = "알겠소. 안타깝군. 계속해서 찾아보겠소...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
