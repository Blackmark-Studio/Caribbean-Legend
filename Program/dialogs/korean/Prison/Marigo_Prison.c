// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해라, 듣고 있다";
			link.l1 = "내가 착각했군. 잘 가라.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "여기서 사이먼 모렐을 구금하고 있지. 그는 얼마 전에 순찰대에게 슈쿠너가 침몰당한 밀수꾼이야. 내가 그를 만날 수 있겠나?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "장교 나리, 나는 필립스버그의 마인헤르 총독께서 보내셨소. 총독께서 내게 영국 첩자를 찾으라고 섬과 근해를 습격하라고 하셨소. 각하께서는 자네가 내게 유용한 정보를 줄 수 있다고도 말씀하셨지.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "장교님, 실종된 순찰대를 찾았습니다. 영국 첩자들도 발견했는데, 그들이 이 섬에 있습니다.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "또 나야, 장교. 첩자들을 붙잡았나?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "그를 왜 필요로 하시오, 나리?";
			link.l1 = "그 자식한테 그가 빌어먹을 개자식이자 악당이라고 말해주고 싶어. 교수대에 설 때 그 말이 도움이 되길 바란다.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "하하! 유머 감각이 있군, 나리... 좋아, 이천 페소 내면 가도 된다.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "가져가시오, 장교. 고맙소!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "흠... 있잖아, 마음이 바뀌었어. 차라리 선술집에서 돈을 낭비하겠어.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "천만에... 어서 가!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "원하시는 대로 하십시오, 다음번엔 이런 제안은 없을 것이오.";
			link.l1 = "어차피 필요 없어. 잘 있어, 장교!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "쓸모 있다고? 하! 다시 생각해보니, 잠깐. 너한테 쓸만한 정보를 하나 주지. 우리 순찰대 중 한 팀이 정글에서 실종됐다. 지금쯤이면 막사로 돌아왔어야 하는데, 앵무새랑 노는 게 더 좋은 모양이지. 아니면 정말 무슨 일이 생겼을 수도 있고. 수색 중에 그들을 찾게 되면, 늦은 이유에 대해 변명이라도 제대로 준비하라고 전해라. 그렇지 않으면 뒷감당이 힘들 테니... 그 순찰대의 지휘관 이름은 야네스 호프만이다.";
			link.l1 = "그게 전부인가, 경관?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "그래, 젠장. 미안하지만 더 이상 해줄 말이 없어. 행운을 빌지, 선장.";
			link.l1 = "감사합니다...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "뭐라고?! 농담하는 거 아니겠지. 보고하라!";
			link.l1 = "나는 정글에 있는 동굴 근처에서 순찰대를 만났소. 놈들이 나를 멈춰 세우고 어디로, 왜 가는지 물어보더니 그냥 보내줬지. 젠장, 그놈들이 네덜란드 군복을 입은 영국 놈들이 아니면 내가 미친놈이지! 그리고 정글에서 이상한 것도 봤는데, 덤불 속에 벌거벗은 남자들이 무리지어 숨어 있는 것처럼 보였소. 내 생각엔 영국 습격대가 네 순찰대를 무장 해제시키고 군복을 빼앗아 입은 것 같소.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "알다시피, 훈련된 붉은 군복 놈들과 싸울 엄두는 못 냈으니, 대신 이렇게 보고하러 급히 달려왔소.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "그래, 그래... 동굴이라고? 몇 명이나 셌지?";
			link.l1 = "다섯 명이다. 그리고 그래, 그놈들 저 동굴로 들어간 것 같아.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "즉시 부하들을 동굴로 보낼 것이오! 선장, 그대가 만난 자들이 정말 영국 첩자라면 마땅한 보상을 받게 될 것이오. 만약 그 놈들을 체포하는 데 당국을 돕고 싶다면 부대에 합류해도 좋소, 추가 보상도 받을 수 있지. 이건 모두 총독의 명령이오. 자, 함께 가겠소?\n";
			link.l1 = "아니, 장교 나리, 첩자를 쫓는 건 당신 일이오. 무장한 부하들을 제대로 보내시오, 저 놈들은 너무 위험하니까...";
			link.l1.go = "FMQN_7";
			link.l2 = "그렇게 할 수 있을 것 같소. 내가 도우면 자네 부하들이 첩자들을 더 빨리 찾을 거요.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "선장의 선택이오, 조언은 참고하겠소. 작전 결과를 듣고 싶으면 내일 다시 찾아오시오.";
			link.l1 = "내일 보자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "정보가 정확했소, 선장. 우리가 그 놈들을 동굴 안에서 찾았소. 놈들은 전혀 항복할 생각이 없었고, 곧바로 싸움을 걸어왔지. 결국 전부 처리했소. 실종된 순찰대도 찾았소. 좀 맞긴 했지만 모두 무사하오... 필립스버그의 모든 선량한 시민을 대표해 감사드리오, 선장. 약속한 대로 경계심에 대한 보상을 드릴 것이오. 자, 받아주시오.";
			link.l1 = "감사합니다!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "신트마르턴에서는 언제나 환영받는 손님이오. 이제 실례하겠소, 다른 볼일이 있어서.";
			link.l1 = "나도 그래. 잘 가.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "좋소. 당신의 도움에 크게 감사하오. 도시 성문으로 가시오, 한 시간 후에 징벌대가 그곳에 집결할 것이오.";
			link.l1 = "작은 충고 하나 하지. 이번 임무엔 네가 가진 최고의 병사들을 보내는 게 좋을 거다. 그 첩자들은 위험하거든.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "걱정 마시오. 우리 필립스버그 최고의 검객 한스 슐트 장교의 지휘 아래 가장 노련한 병사들을 보내고 있소.";
			link.l1 = "좋아! 그럼 시간 낭비하지 말자.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
