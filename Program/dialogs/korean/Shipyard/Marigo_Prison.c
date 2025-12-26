// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해라, 듣고 있다";
			link.l1 = "내가 착각했군. 안녕히 가시오.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "여기서 사이먼 모렐을 구금하고 있지. 그는 얼마 전 순찰대에게 슈쿠너가 침몰당한 밀수꾼이야. 그를 만나볼 수 있겠소?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "장교 나리, 나는 필립스버그의 총독 나리께서 보내셨소. 그분께서 내게 이 섬과 주변 해역에서 영국 첩자들을 수색하라고 명하셨지. 각하께서는 또한 자네가 내게 유용한 정보를 줄 수 있다고 하셨네.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "장교님, 실종된 순찰대를 찾았습니다. 영국 첩자들도 찾았고, 그들이 이 섬에 있습니다.";
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
			dialog.text = "그 자가 왜 필요하지, 나리?";
			link.l1 = "그 자에게 말해주고 싶군, 그는 빌어먹을 놈에다 천하의 악당이라고. 교수대에 서게 될 때 그 말이 도움이 되길 바란다.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "하하! 유머 감각이 있군, 나리... 좋아, 이천 페소면 지나가도 된다.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "가져가시오, 장교. 감사합니다!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "흠... 있잖아, 마음이 바뀌었어. 차라리 선술집에서 내 돈을 낭비하겠어.";
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
			dialog.text = "원하시는 대로 하십시오, 다음엔 이런 제안은 없을 것이오.";
			link.l1 = "어차피 난 필요 없어. 그럼, 장교!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "쓸모 있다고? 하! 잠깐, 다시 생각해 보니 너한테 해줄 말이 하나 있군. 우리 순찰대 중 하나가 정글에서 실종됐다. 지금쯤이면 막사로 돌아왔어야 하는데, 앵무새들이랑 노는 게 더 좋은 모양이지. 아니면 정말 무슨 일이 생겼을 수도 있고. 수색 중에 그놈들을 찾게 되면, 지각한 변명이라도 제대로 준비하라고 전해 줘라. 그렇지 않으면 결과가 마음에 안 들 거다... 순찰대 지휘관 이름은 야네스 호프만이다.";
			link.l1 = "그게 다요, 경관?";
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
			link.l1 = "나는 정글의 동굴 근처에서 순찰대를 만났소. 놈들이 나를 멈춰 세우고 어디로, 왜 가는지 물은 다음에 보내주더군. 젠장, 그게 네덜란드 군복을 입은 영국 놈들이 아니었으면 내가 미친놈이지! 또 정글에서 이상한 것도 봤는데, 딱 봐도 덤불에 숨어 있는 알몸 사내들 무리였소. 아마도 영국 습격대가 당신네 순찰대를 무장 해제시키고 군복을 빼앗아 입은 것 같소.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "알다시피, 훈련된 레드코트 부대와 싸울 엄두가 안 나서 대신 당신에게 곧장 보고하러 달려왔소.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "그래, 그래... 동굴이라고? 몇 명이나 셌지?";
			link.l1 = "다섯 명이다. 그래, 그놈들 그 동굴로 들어간 것 같아.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "즉시 동굴로 부대를 보낼 것이오! 선장, 자네가 만난 자들이 정말 영국 첩자라면 마땅한 보상을 받게 될 것이오. 만약 그 놈들을 체포하는 데 당국을 돕고 싶다면 부대에 합류해도 좋소, 추가 보상도 있을 것이오. 이건 모두 총독의 명령이니 말이오. 자, 함께 갈 텐가?\n";
			link.l1 = "아니, 장교 나리, 첩자를 쫓는 건 당신 일이오. 무장한 부하들을 제대로 보내시오, 저 쓰레기들은 너무 위험하니...";
			link.l1.go = "FMQN_7";
			link.l2 = "내가 할 수 있을 것 같소. 내가 도우면 당신 부하들이 첩자들을 더 빨리 찾을 거요.";
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
			dialog.text = "정보가 정확했소, 선장. 우리가 그 놈들을 동굴 안에서 찾았소. 놈들은 항복할 생각이 전혀 없었고, 바로 싸움을 걸어왔지. 결국 전부 처리했소. 실종된 순찰대도 찾았소. 좀 두들겨 맞긴 했지만 모두 무사하오... 필립스버그의 모든 선량한 시민을 대신해 감사하오, 선장. 약속한 대로 경계심에 대한 보상을 주겠소. 자, 받아가시오.";
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
			dialog.text = "좋소. 당신의 도움에 크게 감사하오. 도시 성문으로 가시오, 한 시간 뒤에 징벌대가 그곳에 집결할 것이오.";
			link.l1 = "조언 하나 하겠소, 이번 임무에는 네가 가진 최고의 병사들을 보내는 게 좋을 거요. 그 첩자들은 위험하오.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "걱정 마시오. 필립스버그의 검술 달인 한스 슐트 장교의 지휘 아래, 우리 최고의 노련한 병사들을 보내고 있소.";
			link.l1 = "좋아! 그럼 시간 낭비하지 말자.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
