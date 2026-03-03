// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해라, 듣고 있다";
			link.l1 = "내가 착각했군. 잘 가라.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "토르투가에 온 목적이 무엇이오, 선장?";
			link.l1 = "제발 부탁이오! 내 동료를 도와주면, 당신이 묻는 모든 질문에 답하겠소!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "당신처럼 중요한 사람이, 온 감옥이 총소리를 들은 직후에 경호원도 없이 여기 온 거야?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "네가 대답을 미루는 동안, 그는 피를 흘리며 죽어가고 있다. 질문을 다시 묻겠다.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "무슨 일이 있었는지 충분히 알고 있소. 다시 한번 묻겠소.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "마지막 기회요, 선장.";
			link.l1 = "총독이 내게 맡긴 임무를 수행 중이다!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "너도 잘 알다시피 나는 내 배의 선장이며, 계약으로 일하지. 그리고 1년에 몇 번씩 네 멋진 섬을 방문하잖아!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "의심은 했지만 완전히 확신하지는 못했지. 운이 좋군, 며칠 전에 캡스터빌에서 중요한 회의가 열렸거든. 아주 영향력 있는 사람들이 합의를 이뤄냈지. 그래서 이제 너는 내 적이 아니야.";
			link.l1 = "우리를 도와줄 수 있겠소?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "즉시 풀어주겠다. 네 동료는 배로 옮겨져 치료를 받을 것이다.";
			link.l1 = "감사합니다...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "거의 좌초할 뻔했군, Charles! 나가. 적어도 한 달 동안은 Tortuga에 돌아오지 마라. 소문이 잠잠해지고 분노가 가라앉을 때까지 기다려.";
			link.l1 = "그러지. 잘 가라!";
			link.l1.go = "exit";
			link.l2 = "아무 설명도 안 할 거야? 조금도? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "누군가가 너를 신고했다. 네가 광신적인 가톨릭 신자라서 우리 아름다운 섬에 와서 고귀한 총독을 해치려 했다고 하더군.";
			link.l1 = "나는 광신자가 아니야!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "능숙하게 썼으니 믿어라. 난 이런 건 잘하지 – 최고의 비방문은 적어도 약간의 진실이 담겨 있는 법이지.";
			link.l1 = "누가 보고서를 썼지?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "누가 그 살인자를 감옥에 들여보냈지?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "누군가 네놈을 바로 라로슈 지하의 위그노 고문대로 보내는 대신 며칠간 감옥에 쳐박아 두길 원했지.\n그만해라, 샤를. 나가라. 당장 눈앞에 있는 일부터 처리하고, 그 다음엔... 뭐, 내 말 알겠지!";
			link.l1 = "네. 그렇게 하겠습니다. 안녕히 계십시오, 교도소장님.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "내가 했다.";
			link.l1 = "내가 여기서 떠나기 전에 다른 놈을 불러오는 게 좋을 거다.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "듣고 있소, 교도소장.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "나는 너한테 아무것도 설명해 줄 의무가 없어, Charles. 내 손에 잡힌 걸 다행으로 여겨라. 내 직속 상관 손에 들어갔으면 어땠을지 생각해 봐라. 그리고 이런 소동에 대한 보상도 네가 아니라 네 상관이 해줄 거라는 사실에 감사해라.";
				link.l1 = "그래... 너는 내 상사를 나만큼 잘 모르지. 그럼, 잘 있어라, 교도소장.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "있지, 말해주지. 특별 주둔지 연금 기금에 후하게, 세금도 없이 기부가 들어왔거든. 감사의 표시로, 그 기부자는 악명 높은 범죄자의 신속하고 합법적인 처형에 참여할 수 있도록 허락받았지!";
				link.l1 = "내 장교?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "내 친구?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "나는 너한테 아무것도 설명해 줄 의무가 없어, Charles. 내 손아귀에 들어온 걸 다행으로 여겨라. 내 상관 손에 들어갔으면 어땠을지 생각해 봐. 그리고 네가 아니라 네 상관이 이 모든 소동에 대한 보상을 해줄 거란 사실도 감사하게 여겨라.";
				link.l1 = "으으으으응... 너는 내 상사를 나만큼 잘 모르지. 그럼, 감옥장.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "있지? 말해 주지. 특별 주둔지 연금 기금에 후하게, 세금 없이 기부가 들어왔거든. 감사의 표시로, 그 기부자는 악명 높은 범죄자의 신속하고 합법적인 처형에 참여할 수 있도록 허락받았지!";
				link.l1 = "내 장교?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "내 친구?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "나가라, Charles. 그리고 이 쓰레기도 데리고 가라. 자네의 동료 선택... 실망스럽군.";
			link.l1 = "적어도 네... 후원자가 어디 있는지 말해라?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "본토에서. 잘 가시오, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "당신에 대한 보고가 들어왔소. 아주 불쾌한 내용이오. 선장, 누가 당신을 함정에 빠뜨린 게 분명하오, 하지만... 나는 내 권한으로 당신을 여기서 몇 주 더 가둘 수 있고, 당신 친구는 죽게 내버려둘 수도 있소. 단, 만약...";
			link.l1 = "얼마지?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "누가 나를 함정에 빠뜨린 거지? 네가 그 살인자를 감옥에 들여보냈나?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "토르투가 주둔지 연금 기금에 현지 대금업자를 통해 오백 두블룬을 입금해 주십시오.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" 그리고 이 섬의 고위급 부인과 엮여서 예전에 일으킨 소동 값으로 백 더블룬을 추가하지.";
			}
			link.l1 = "이 망할 문 어서 열어!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "너 때문에 이미 내 시간 너무 많이 뺏겼다. 돈꾼한테 가서 토르투가 주둔군 연금 기금에 500두블룬을 입금해라.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" 그리고 이 섬의 고위 귀부인과 엮여서 예전에 일으킨 소동에 대한 값으로 금화 백 닢을 더 내라.";
			}
			link.l1 = "이 망할 문 어서 열어라!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "자금은 입금됐다. 에르퀼은 어디 있지?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "우리는 그에게 응급처치를 하고 당신 배로 보냈소. 그 악당은 질긴 놈이라 아마 살아남을 거요. 잘 가시오, 선장. 당분간 우리 섬에서 다시 마주치지 않길 바라오!";
			link.l1 = "이런 대접을 받고 나니, 여기엔 다시는 얼씬도 안 하겠소! 안녕히 계시오, 교도소장.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
