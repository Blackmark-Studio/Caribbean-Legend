// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"너는 이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 벌써 세 번째로 이 질문을 꺼내는군...","이봐, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나한테 할 말 없어."),"신경 쓰지 마.","정말로, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심이 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "사실은, 내가 곧 식민지에서 당신에게 산 물건을 싣고 포르토 벨로로 항해할 예정이오. 혹시 가는 길에 내가 처리할 화물이나 일이 있다면 알려주시오... 물론 수수료는 받겠소.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "다시 뵙습니다. 당신의 편지를 포르토 벨로에 전달했습니다. 그곳에서 당신께 답장을 전해 달라고 부탁받았습니다.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "안녕하세요. 저는 포르토 벨로에서 왔습니다. 그곳 항만청의 동료께서 이 편지를 전해 달라고 하셨습니다.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "걱정해 주셔서 감사합니다만, 그런 일은 없습니다. 사실 의뢰 하나가 있었으나, 당신이 정말 며칠 늦었소. 그래서 그 일은 급히 연락선 루거를 보냈소.";
				link.l1 = "알겠소... 뭐, 고맙소.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "배 한 척도 없는 걸 보니, 부유한 상인인가 보군. 흠... 하지만 나는 이 근방에서 함대를 거느린 상인들은 얼굴만 봐도 다 아는데, 자네는 모르겠군. 그러니 미안하지만, 중요한 일은 맡길 수 없네.";
					link.l1 = "알겠소... 뭐, 그래도 고맙소.";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "흠... 할 일이 있소. 하지만 지금은 그대의 배가 적합하지 않구려. 나는 빠르면서도 강력한 배가 필요한데, 그대의 배는 이 조건을 완전히 충족하지 못하오. 적어도 동시에 그렇지는 않소. 그러니 양해해 주시오.";
						link.l1 = "알겠소... 뭐, 고맙소.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "나는 할 일이 있소... 그리고 자네는 좋은 배를 가졌군. 하지만 상선처럼 보이지는 않네. 내가 보기엔 네덜란드 서인도 회사의 장기 면허도 없는 것 같고. 기분 나쁘게 듣지 말게, 자네는 상인 같지 않으니. 내가 그 위험을 감수할 수는 없네.";
							link.l1 = "알겠소... 뭐, 고맙소.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "나는 할 일이 있소... 그리고 자네는 좋은 배를 가졌군. 하지만 자네가 무엇을 거래하려는지 이해가 안 되는군... 자네가 포르토 벨로에 가서 물건을 팔 거라고 했지만, 내가 알기로 자네는 우리 식민지에서 그 물건을 사지 않았잖소. 오해는 말게, 하지만 자네는 상인으로 보이지 않네. 그 위험을 감수할 수 없소.";
								link.l1 = "알겠소... 뭐, 고맙소.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "할 일이 있소. 물론, 나는 그대를 모르는 사람이오... 하지만 솔직히 말해, 나는 함대를 거느린 상인들만 기억하오. 나머지는 전혀 기억나지 않소. 그리고 그대는 장기 면허를 가지고 있으니, 분명 노련한 상인임이 틀림없소. 그런데 그대의 배가 흥미롭군. 왜 프리깃함으로 무역을 하는 것이오?";
								link.l1 = "하, 이건 평범한 프리깃이 아니지. 화물이 가득 차도 아주 빠른 속도를 낼 수 있어. 해적들과 싸우는 것보다 도망치는 게 항상 더 쉽지 않나? 내 배는 일반 상선보다 적재량이 적긴 하지만, 위험은 훨씬 덜하지.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "흠, 하지만 네 말이 맞아! 스페인 놈들은 배를 잘 만들지, 안 그래? 그래, 그래, 이 훌륭한 배가 우리 조선소에서 막 나온 것임을 한눈에 알았지. 그리고 오늘 실제로 들었어, 네가 우리 상인한테서 커피랑 코코아를 한꺼번에 사서 포르토 벨로에 되팔려고 한다고 말이야. 좋은 거래야, 내가 장담하지. 장사에 익숙하지 않은 사람들은 이 물건들이 여기서는 플랜테이션 덕분에 싸고, 포르토 벨로에서는 수요가 많다는 걸 몰라. 거기서부터 본국으로 가거든.";
			link.l1 = "글쎄, 그게 다지, 나리. 몇 페소 가지고는 내 배를 그렇게 멀리까지 끌고 가지 않겠어.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "사실을 말하자면, 자네에게 맡길 일이 있네. 그리고 자네처럼 빠르고, 위급할 때 스스로를 지킬 수 있는 배를 가진 건 아주 다행이지.";
			link.l1 = "잠깐만, 나리... 당신 말은 내가 싸워야 한다는 뜻인가...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "아니, 아니오! 사실 내 부탁은 아주 간단하오. 포르토 벨로 항만청에 편지를 전달해 주면 되오. 편지는 봉인되어 있으니 절대 열어보면 안 되오. 이 일에 대해 아무에게도 말할 필요 없소, 이 서신은... 개인적인 것이오. 직접 전달해야 하오. 기한은 열흘이오. 그 이후에는 아무 의미가 없소.";
			link.l1 = "그렇게 간단해? 그럼 보수는 얼마나 주는 거지?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "오천 페소다. 포르토 벨로에 전령 루거선을 보내지 않아도 되는 대가로 생각하게.";
			link.l1 = "그래서 내 배와 나에 대해 무슨 질문이 있었소?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "신경 쓰지 마시오. 그냥 이 서신이 중요해서 반드시 수신인에게 제대로 전달되어야 하거든. 그러니 별일 아니오. 관료주의지... 평범한 사람에게는 이런 문서가 아무런 흥미도 없을 테니.";
			link.l1 = "좋소, 동의하오. 서류를 여기로 가져오겠소. 내가 포르토 벨로에 도착하는 즉시 당신 동료에게 전달하리다. 열흘 안에 처리할 테니 걱정 마시오.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "잠시만요. 미안합니다, 이름을 완전히 잊어버렸군요. 이름을 다시 말씀해 주시겠습니까? 서류에 적어야 해서요.";
			link.l1 = "내 이름은 Andreas Garcia요.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "감사합니다. 자... 좋습니다. 이 문서를 전달하는 사람은 바로 당신이며, 반드시 수신인에게 직접 전해야 한다는 점을 기억하십시오. 여기 있습니다. 상은 포르토 벨로 항만청장이 수여할 것입니다. 좋은 여행 되십시오!";
			link.l1 = "감사합니다! 이제 실례하겠습니다.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "훌륭하오! 정말 큰 도움이 되었소. 어려움은 없었소?";
			link.l1 = "아니, 아무런 어려움도 없었소. 사실, 당신 동료가 당신을 욕했소. 여기 있는 사람들 모두 구두쇠라며, 사절선 대신 지나가는 상인들에게만 편지를 보내고, 심지어 수신자에게 요금까지 받는다고 했소. 아바나에 민원을 올리겠다고 협박하더군...\n";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "뭐?! 내가 괴짜라고?! 저 자식 자기가 뭐라도 되는 줄 아나? 우선, 네 돈 오천... 아니, 육천 페소나 가져가라! 나 정말 서럽다니까!";
			link.l1 = "감사합니다. 당신에 대해 동료가 오해했다는 게 틀렸다는 걸 알게 되어 다행이군요.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "그리고 두 번째로, 이 악당이 두 달 전에 카라카스에서 포르토 벨로로, 거기서 다시 아바나로 항해한 상선의 유지비를 전부 내게 떠넘겼다는 사실을 잊은 모양이오! 우리는 항해의 두 번째 구간은 그가 비용을 내기로 합의했었지! 그는 빚을 갚지 않았고, 지난달에 다 정산하겠다고 약속만 했소! 그런데도 아직도 내가 구두쇠라니... 그래, 내가 직접 아바나에 그 놈을 고발하는 진정서를 쓰겠소!";
			link.l1 = "음, 자네는 마드리드 궁정의 열정이 있군, 물론 ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "아니, 가만 생각해 보니... 참으로 건방진 녀석이군! 좋아, 다시 상대해 주지... 이제 실례하겠소. 급한 일이 있어서 말이오. 함께 거래해서 즐거웠소!";
			link.l1 = "행운을 빕니다!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "좋소! 자네 덕분에 큰 도움이 되었네. 물론 내가 그들에게 전령 루거선을 보냈고, 그들은 지나가는 배에 답장을 실어 보냈지. 그래... 그런데도 여전히 여기 앉아 있는 우리가 구두쇠라며 불평을 하더군.";
			link.l1 = "글쎄, 아마 심부름꾼에게 줄 돈을 아낀 걸지도 ...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "'아마도'가 아니라 확실하다고 했잖아! 좋아, 상관없어. 자, 일이나 받아. 그리고 지금은 일이 많으니, 실례하겠소.";
			link.l1 = "글쎄, 아마 심부름꾼에게 줄 돈을 아꼈던 모양이지 ...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
