// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "나한테 볼일이라도 있나? 없어? 그럼 꺼져!";
			link.l1 = "나는 이미 떠난다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "나한테 시킬 일 있냐?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "자취는 잡았지만, 쥐새끼를 굴에서 끌어내려면 돈이 좀 필요해 – 3만 페소 내놔.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "여기, 밀수꾼 시체에서 찾은 이 편지를 봐라";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "끝났다. 노먼 비고와 그의 배는 바다 악마에게 갔지.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "흠... 일거리라, 그랬나? 사실 네가 물어봐서 다행이군. 나는 외부 사람이 필요해. 근처 마을에서 뭔가 알아봐야 하는데, 내 놈들은 거기서 이미 얼굴이 알려져 있거든. 많이는 못 주겠지만, 뭔가는 챙겨줄 거다.";
			link.l1 = "좋아! 임무가 뭐지?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "미안하지만, 몇 푼 안 되는 걸로 위험을 감수하진 않겠다. 잘 가라.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "그럼 잘 들어. 한 달 전에 나는 'Saintblue' 스쿠너의 선장과 노예 200명을 넘기기로 거래를 했지. 그 노예들을 이 지역 농장주에게 팔 생각이었어. 시간이 지났고, 의뢰인은 걱정하기 시작했지. 그런데 어제, 스쿠너가 섬 근처에서 목격됐다는 소식을 들었어. 하지만! 선장은 나타나지 않았지. 오늘 내 의뢰인은 선불금을 돌려달라고 요구했고, 다른 판매자로부터 노예를 사라는 제안을 받았다고 했어. 더 비싸긴 하지만, 노예 전부를 한 번에 넘겨준다고 하더군.";
			link.l1 = "그래서? 네놈 선금 날릴까 봐 내가 며칠 만에 노예 200명을 구해오라고? 겨우 동전 몇 푼 때문에?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "당연히 아니지. 내가 바보처럼 보여? 어차피 그 놈이 준 선불은 돌려줄 생각 없어. 하지만 그에게 넘긴 노예들이 내 것이라는 증거가 필요해. 그 놈한테 새 거래를 제안한 자들을 찾아내면 네놈한테 만 페소를 주지. 거래할래?";
			link.l1 = "나도 끼지. 의심 가는 놈이라도 있나? 누가 그런 짓을 했을 것 같아?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "어림없지. 딴 놈이나 찾아봐라.\n고작 만 냥? 미안하지만 그걸로는 안 돼.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "내게 뭔가 생각이 있었으면, 네놈 따위한테 절대 일 안 맡겼지. 그놈들은 이미 죽었을 거다. 하지만 난 저 자식들이 어떻게 'Saintblue'의 화물과 내 의뢰인에 대해 알게 됐는지 궁금하단 말이다. 놈들한텐 꽤 쉬운 일이었던 것 같군. 이제 알겠어?";
			link.l1 = "그래, 누군가 네 놈을 배신했지.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "그래, 맞아! 내가 그놈을 찾고 있지. 내 경쟁자들을 죽이거나 내 노예들을 돌려받는 건 네 우선순위가 아니야. 내가 필요한 건 그 쥐새끼, 아니, 솔직히 말해서 그놈의 머리를 꼬챙이에 꽂아오는 거다. 이제 내 부하들이 네 임무에 대해 아무것도 몰라야 하는 이유를 알겠지? 누가 정보를 팔아넘기는지 알아낼 때까지 난 모두를 의심할 거다. 그리고 솔직히, 난 그런 상황을 원하지 않아...";
			link.l1 = "알겠다. 그럼 조용히 움직이겠다. 가는 중이다.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "삼만이라고? 꽤 큰 돈이군... 지금 내가 줄 수 있는 건 5,000페소뿐이다, 그게 전부야. 그리고 돈 들고 튈 생각은 꿈도 꾸지 마라, 잡히면 바로 근처 울타리에 매달아 죽여버릴 테니까! 알겠어?";
			link.l1 = "좋아, 그럼 오천 내놔...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "가져가. 네가 뭘 찾아오는지 결과를 기다리고 있다.";
			link.l1 = "다 잘 될 거다.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "하! 좋은 소식이군! 네가 해낼 줄 알았다. 흥미로운 정보가 있어.";
			link.l1 = "일은 끝냈으니 내 만 냥 내놔.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "그래, 여기 네 보상이다. 하지만 도망치지 마라, 할 일이 하나 더 있다.\n파이퍼는 '셉티마' 루거의 노먼 비고 선원이다. 노먼 비고가 우리 중 하나라 해도 분명히 쥐새끼다. 최근에 그 녀석이 이 섬 근처 바다에서 목격됐지. 네 임무는 이 쥐새끼를 바다 악마에게 보내는 거다. 처음에도 나를 실망시키지 않았으니, 이것도 네가 처리해줬으면 한다. 15,000페소를 주겠다. 어때, 할래?";
			link.l1 = "내가 맡지! 배신자 노먼 비고는 죽은 목숨이다.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "있잖아, 난 그 일에 끼고 싶지 않아... 어차피 시간도 없어. 미안하지만, 난 간다.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "알고 있다, 알고 있어. 내 부하들이 전투를 지켜봤고, 이미 네가 완벽하게 이긴 걸 보고했다. 좋아, 네 일 잘 해냈다. 약속한 15,000페소다. 그리고 고맙다, 네 덕분에 큰 도움이 됐지.";
			link.l1 = "괜찮아, 도와줄 수 있어서 기뻤어! 하지만 이제 가봐야 해, 여기 너무 오래 있었고 할 일이 많거든. 잘 있어!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
